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

#ifndef ST_AUDIO_SERVER_H
#define ST_AUDIO_SERVER_H

#include <mutex>
#include <unordered_map>
#include <pthread.h>
#include "accesstoken_kit.h"
#include "ipc_skeleton.h"
#include "iremote_stub.h"
#include "system_ability.h"
#include "audio_system_manager.h"
#include "audio_manager_base.h"

namespace OHOS {
namespace AudioStandard {
class AudioServer : public SystemAbility, public AudioManagerStub {
    DECLARE_SYSTEM_ABILITY(AudioServer);
public:
    DISALLOW_COPY_AND_MOVE(AudioServer);
    explicit AudioServer(int32_t systemAbilityId, bool runOnCreate = true);
    virtual ~AudioServer() = default;
    void OnDump() override;
    void OnStart() override;
    void OnStop() override;
    int32_t GetMaxVolume(AudioSystemManager::AudioVolumeType volumeType) override;
    int32_t GetMinVolume(AudioSystemManager::AudioVolumeType volumeType) override;
    int32_t SetMicrophoneMute(bool isMute) override;
    bool IsMicrophoneMute() override;
    int32_t SetAudioScene(AudioScene audioScene, DeviceType activeDevice) override;
    std::vector<sptr<AudioDeviceDescriptor>> GetDevices(DeviceFlag deviceFlag) override;
    static void *paDaemonThread(void *arg);
    void SetAudioParameter(const std::string &key, const std::string &value) override;
    const std::string GetAudioParameter(const std::string &key) override;
    const char *RetrieveCookie(int32_t &size) override;
    uint64_t GetTransactionId(DeviceType deviceType, DeviceRole deviceRole) override;
    int32_t UpdateActiveDeviceRoute(DeviceType type, DeviceFlag flag) override;

private:
    bool VerifyClientPermission(const std::string &permissionName);

    static constexpr int32_t MAX_VOLUME = 15;
    static constexpr int32_t MIN_VOLUME = 0;
    static std::unordered_map<int, float> AudioStreamVolumeMap;
    static std::map<std::string, std::string> audioParameters;
    pthread_t m_paDaemonThread;
    AudioScene audioScene_ = AUDIO_SCENE_DEFAULT;
};
} // namespace AudioStandard
} // namespace OHOS
#endif // ST_AUDIO_SERVER_H
