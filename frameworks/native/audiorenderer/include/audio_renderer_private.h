/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AUDIO_RENDERER_PRIVATE_H
#define AUDIO_RENDERER_PRIVATE_H

#include "audio_interrupt_callback.h"
#include "audio_renderer.h"
#include "audio_stream.h"
#include "audio_renderer_proxy_obj.h"

namespace OHOS {
namespace AudioStandard {
constexpr uint32_t INVALID_SESSION_ID = static_cast<uint32_t>(-1);

class AudioRendererPrivate : public AudioRenderer {
public:
    int32_t GetFrameCount(uint32_t &frameCount) const override;
    int32_t GetLatency(uint64_t &latency) const override;
    int32_t SetParams(const AudioRendererParams params) override;
    int32_t GetParams(AudioRendererParams &params) const override;
    int32_t GetRendererInfo(AudioRendererInfo &rendererInfo) const override;
    int32_t GetStreamInfo(AudioStreamInfo &streamInfo) const override;
    bool Start() override;
    int32_t Write(uint8_t *buffer, size_t bufferSize) override;
    RendererState GetStatus() const override;
    bool GetAudioTime(Timestamp &timestamp, Timestamp::Timestampbase base) const override;
    bool Drain() const override;
    bool Pause() const override;
    bool Stop() const override;
    bool Flush() const override;
    bool Release() const override;
    int32_t GetBufferSize(size_t &bufferSize) const override;
    int32_t SetAudioRendererDesc(AudioRendererDesc audioRendererDesc) const override;
    int32_t SetStreamType(AudioStreamType audioStreamType) const override;
    int32_t SetVolume(float volume) const override;
    float GetVolume() const override;
    int32_t SetRenderRate(AudioRendererRate renderRate) const override;
    AudioRendererRate GetRenderRate() const override;
    int32_t SetRendererCallback(const std::shared_ptr<AudioRendererCallback> &callback) override;
    int32_t SetRendererPositionCallback(int64_t markPosition,
        const std::shared_ptr<RendererPositionCallback> &callback) override;
    void UnsetRendererPositionCallback() override;
    int32_t SetRendererPeriodPositionCallback(int64_t frameNumber,
        const std::shared_ptr<RendererPeriodPositionCallback> &callback) override;
    void UnsetRendererPeriodPositionCallback() override;
    int32_t SetBufferDuration(uint64_t bufferDuration) const override;
    int32_t SetRenderMode(AudioRenderMode renderMode) const override;
    AudioRenderMode GetRenderMode() const override;
    int32_t SetRendererWriteCallback(const std::shared_ptr<AudioRendererWriteCallback> &callback) override;
    int32_t GetBufferDesc(BufferDesc &bufDesc) const override;
    int32_t Enqueue(const BufferDesc &bufDesc) const override;
    int32_t Clear() const override;
    int32_t GetBufQueueState(BufferQueueState &bufState) const override;
    void SetApplicationCachePath(const std::string cachePath) override;
    void SetInterruptMode(InterruptMode mode) override;

    AudioRendererInfo rendererInfo_ = {};

    explicit AudioRendererPrivate(AudioStreamType audioStreamType, const AppInfo &appInfo);
    ~AudioRendererPrivate();

private:
    static std::map<pid_t, std::map<AudioStreamType, AudioInterrupt>> sharedInterrupts_;
    std::shared_ptr<AudioStream> audioStream_;
    std::shared_ptr<AudioInterruptCallback> audioInterruptCallback_ = nullptr;
    std::shared_ptr<AudioStreamCallback> audioStreamCallback_ = nullptr;
    AppInfo appInfo_ = {};
    AudioInterrupt audioInterrupt_ =
        {STREAM_USAGE_UNKNOWN, CONTENT_TYPE_UNKNOWN, AudioStreamType::STREAM_DEFAULT, 0};
     AudioInterrupt sharedInterrupt_ =
        {STREAM_USAGE_UNKNOWN, CONTENT_TYPE_UNKNOWN, AudioStreamType::STREAM_DEFAULT, 0};
    uint32_t sessionID_ = INVALID_SESSION_ID;
    AudioStandard::InterruptMode mode_ = AudioStandard::InterruptMode::SHARE_MODE;
    std::shared_ptr<AudioRendererProxyObj> rendererProxyObj_;
};

class AudioInterruptCallbackImpl : public AudioInterruptCallback {
public:
    explicit AudioInterruptCallbackImpl(const std::shared_ptr<AudioStream> &audioStream,
        const AudioInterrupt &audioInterrupt);
    virtual ~AudioInterruptCallbackImpl();

    void OnInterrupt(const InterruptEventInternal &interruptEvent) override;
    void SaveCallback(const std::weak_ptr<AudioRendererCallback> &callback);
private:
    void NotifyEvent(const InterruptEvent &interruptEvent);
    void HandleAndNotifyForcedEvent(const InterruptEventInternal &interruptEvent);
    void NotifyForcePausedToResume(const InterruptEventInternal &interruptEvent);
    bool HandleForceDucking(const InterruptEventInternal &interruptEvent);
    std::shared_ptr<AudioStream> audioStream_;
    std::weak_ptr<AudioRendererCallback> callback_;
    std::shared_ptr<AudioRendererCallback> cb_;
    AudioInterrupt audioInterrupt_ {};
    bool isForcePaused_ = false;
    bool isForceDucked_ = false;
    float instanceVolBeforeDucking_ = 0.2f;
};

class AudioStreamCallbackRenderer : public AudioStreamCallback {
public:
    virtual ~AudioStreamCallbackRenderer() = default;

    void OnStateChange(const State state) override;
    void SaveCallback(const std::weak_ptr<AudioRendererCallback> &callback);
private:
    std::weak_ptr<AudioRendererCallback> callback_;
};
}  // namespace AudioStandard
}  // namespace OHOS
#endif // AUDIO_RENDERER_PRIVATE_H
