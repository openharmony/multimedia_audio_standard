/*
 * Copyright (C) 2021 Huawei Device Co., Ltd.
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
#ifndef AUDIO_INFO_H
#define AUDIO_INFO_H

#ifdef __MUSL__
#include <stdint.h>
#endif // __MUSL__

#include <vector>
#include <unistd.h>

namespace OHOS {
namespace AudioStandard {
enum DeviceFlag {
    /**
     * Device flag none.
     */
    DEVICE_FLAG_NONE = -1,
    /**
     * Indicates all output audio devices.
     */
    OUTPUT_DEVICES_FLAG = 1,
    /**
     * Indicates all input audio devices.
     */
    INPUT_DEVICES_FLAG = 2,
    /**
     * Indicates all audio devices.
     */
    ALL_DEVICES_FLAG = 3,
    /**
     * Device flag max count.
     */
    DEVICE_FLAG_MAX
};

enum DeviceRole {
    /**
     * Device role none.
     */
    DEVICE_ROLE_NONE = -1,
    /**
     * Input device role.
     */
    INPUT_DEVICE = 1,
    /**
     * Output device role.
     */
    OUTPUT_DEVICE = 2,
    /**
     * Device role max count.
     */
    DEVICE_ROLE_MAX
};

enum DeviceType {
    /**
     * Indicates device type none.
     */
    DEVICE_TYPE_NONE = -1,
    /**
     * Indicates invalid device
     */
    DEVICE_TYPE_INVALID = 0,
    /**
     * Indicates earpiece
     */
    DEVICE_TYPE_EARPIECE = 1,
    /**
     * Indicates a speaker built in a device.
     */
    DEVICE_TYPE_SPEAKER = 2,
    /**
     * Indicates a headset, which is the combination of a pair of headphones and a microphone.
     */
    DEVICE_TYPE_WIRED_HEADSET = 3,
    /**
     * Indicates a Bluetooth device used for telephony.
     */
    DEVICE_TYPE_BLUETOOTH_SCO = 7,
    /**
     * Indicates a Bluetooth device supporting the Advanced Audio Distribution Profile (A2DP).
     */
    DEVICE_TYPE_BLUETOOTH_A2DP = 8,
    /**
     * Indicates a microphone built in a device.
     */
    DEVICE_TYPE_MIC = 15,
    /**
     * Indicates device type max count.
     */
    DEVICE_TYPE_MAX
};

enum ActiveDeviceType {
    ACTIVE_DEVICE_TYPE_NONE = -1,
    SPEAKER = 2,
    BLUETOOTH_SCO = 7,
    ACTIVE_DEVICE_TYPE_MAX
};

enum AudioStreamType {
    /**
     * Indicates audio streams default.
     */
    STREAM_DEFAULT = -1,
    /**
     * Indicates audio streams for system sounds.
     */
    STREAM_SYSTEM = 0,
    /**
     * Indicates audio streams for music playback.
     */
    STREAM_MUSIC = 1,
    /**
     * Indicates audio streams for ringtones.
     */
    STREAM_RING = 2,
    /**
     * Indicates audio streams media.
     */
    STREAM_MEDIA = 3,
    /**
     * Indicates audio streams of voices in calls.
     */
    STREAM_VOICE_CALL = 4,
    /**
     * Indicates Audio streams for voice assistant
     */
    STREAM_VOICE_ASSISTANT = 5,
    /**
     * Indicates audio streams for alarms.
     */
    STREAM_ALARM = 6,
    /**
     * Indicates audio streams for notifications.
     */
    STREAM_NOTIFICATION = 7,
    /**
     * Indicates audio streams for voice calls routed through a connected Bluetooth device.
     */
    STREAM_BLUETOOTH_SCO = 8,
    /**
     * Indicates audio streams for enforced audible.
     */
    STREAM_ENFORCED_AUDIBLE = 9,
    /**
     * Indicates audio streams for dual-tone multi-frequency (DTMF) tones.
     */
    STREAM_DTMF = 10,
    /**
     * Indicates audio streams exclusively transmitted through the speaker (text-to-speech) of a device.
     */
    STREAM_TTS =  11,
    /**
     * Indicates audio streams used for prompts in terms of accessibility.
     */
    STREAM_ACCESSIBILITY = 12
};

enum AudioEncodingType {
    ENCODING_PCM = 0,
    ENCODING_AAC, // Currently not supported
    ENCODING_INVALID
};

// Ringer Mode
enum AudioRingerMode {
    RINGER_MODE_NORMAL = 0,
    RINGER_MODE_SILENT = 1,
    RINGER_MODE_VIBRATE = 2
};

// format
enum AudioSampleFormat {
    SAMPLE_U8 = 8,
    SAMPLE_S16LE = 16,
    SAMPLE_S24LE = 24,
    SAMPLE_S32LE = 32,
    INVALID_WIDTH = -1
};

// channel
enum AudioChannel {
    MONO = 1,
    STEREO
};

// sampling rate
enum AudioSamplingRate {
    SAMPLE_RATE_8000 = 8000,
    SAMPLE_RATE_11025 = 11025,
    SAMPLE_RATE_12000 = 12000,
    SAMPLE_RATE_16000 = 16000,
    SAMPLE_RATE_22050 = 22050,
    SAMPLE_RATE_24000 = 24000,
    SAMPLE_RATE_32000 = 32000,
    SAMPLE_RATE_44100 = 44100,
    SAMPLE_RATE_48000 = 48000,
    SAMPLE_RATE_64000 = 64000,
    SAMPLE_RATE_96000 = 96000
};

typedef enum {
    /** Invalid audio source */
    AUDIO_SOURCE_INVALID = -1,
    /** Default audio source */
    AUDIO_SOURCE_DEFAULT = 0,
    /** Microphone */
    AUDIO_MIC = 1,
    /** Uplink voice */
    AUDIO_VOICE_UPLINK = 2,
    /** Downlink voice */
    AUDIO_VOICE_DOWNLINK = 3,
    /** Voice call */
    AUDIO_VOICE_CALL = 4,
    /** Camcorder */
    AUDIO_CAMCORDER = 5,
    /** Voice recognition */
    AUDIO_VOICE_RECOGNITION = 6,
    /** Voice communication */
    AUDIO_VOICE_COMMUNICATION = 7,
    /** Remote submix */
    AUDIO_REMOTE_SUBMIX = 8,
    /** Unprocessed audio */
    AUDIO_UNPROCESSED = 9,
    /** Voice performance */
    AUDIO_VOICE_PERFORMANCE = 10,
    /** Echo reference */
    AUDIO_ECHO_REFERENCE = 1997,
    /** Radio tuner */
    AUDIO_RADIO_TUNER = 1998,
    /** Hotword */
    AUDIO_HOTWORD = 1999,
    /** Extended remote submix */
    AUDIO_REMOTE_SUBMIX_EXTEND = 10007,
} AudioSourceType;

struct AudioStreamParams {
    uint32_t samplingRate;
    uint8_t encoding;
    uint8_t format;
    uint8_t channels;
};

/**
* Enumerates the audio content type.
*/
enum ContentType {
    CONTENT_TYPE_UNKNOWN = 0,
    CONTENT_TYPE_SPEECH = 1,
    CONTENT_TYPE_MUSIC = 2,
    CONTENT_TYPE_MOVIE = 3,
    CONTENT_TYPE_SONIFICATION = 4,
};

/**
* Enumerates the stream usage.
*/
enum StreamUsage {
    STREAM_USAGE_UNKNOWN = 0,
    STREAM_USAGE_MEDIA = 1,
    STREAM_USAGE_VOICE_COMMUNICATION = 2,
    STREAM_USAGE_NOTIFICATION_RINGTONE = 3,
    STREAM_USAGE_VOICE_ASSISTANT = 4,
};

enum InterruptType {
    INTERRUPT_TYPE_BEGIN = 1,
    INTERRUPT_TYPE_END = 2,
};

enum InterruptHint {
    INTERRUPT_HINT_NONE = 0,
    INTERRUPT_HINT_RESUME,
    INTERRUPT_HINT_PAUSE,
    INTERRUPT_HINT_STOP,
    INTERRUPT_HINT_DUCK,
    INTERRUPT_HINT_UNDUCK
};

enum InterruptActionType {
    TYPE_ACTIVATED = 1,
    TYPE_INTERRUPTED = 2,
    TYPE_DEACTIVATED = 3
};

struct InterruptAction {
    InterruptActionType actionType;
    InterruptType interruptType;
    InterruptHint interruptHint;
};

struct AudioInterrupt {
    StreamUsage streamUsage;
    ContentType contentType;
    AudioStreamType streamType;
    int32_t sessionID;
};

struct AudioParameters {
    AudioSampleFormat format;
    AudioChannel channels;
    AudioSamplingRate samplingRate;
    AudioEncodingType encoding;
    ContentType contentType;
    StreamUsage usage;
    DeviceRole deviceRole;
    DeviceType deviceType;
};

// Supported audio parameters for both renderer and capturer
const std::vector<AudioSampleFormat> AUDIO_SUPPORTED_FORMATS {
    SAMPLE_U8,
    SAMPLE_S16LE,
    SAMPLE_S24LE,
    SAMPLE_S32LE
};

const std::vector<AudioChannel> AUDIO_SUPPORTED_CHANNELS {
    MONO,
    STEREO
};

const std::vector<AudioEncodingType> AUDIO_SUPPORTED_ENCODING_TYPES {
    ENCODING_PCM
};

const std::vector<AudioSamplingRate> AUDIO_SUPPORTED_SAMPLING_RATES {
    SAMPLE_RATE_8000,
    SAMPLE_RATE_11025,
    SAMPLE_RATE_12000,
    SAMPLE_RATE_16000,
    SAMPLE_RATE_22050,
    SAMPLE_RATE_24000,
    SAMPLE_RATE_32000,
    SAMPLE_RATE_44100,
    SAMPLE_RATE_48000,
    SAMPLE_RATE_64000,
    SAMPLE_RATE_96000
};

typedef uint32_t AudioIOHandle;
} // namespace AudioStandard
} // namespace OHOS
#endif // AUDIO_INFO_H
