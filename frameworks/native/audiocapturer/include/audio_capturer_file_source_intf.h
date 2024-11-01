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

#ifndef AUDIO_CAPTURER_FILE_SOURCE_INTF_H
#define AUDIO_CAPTURER_FILE_SOURCE_INTF_H

#ifdef __cplusplus
extern "C" {
#endif
int32_t AudioCapturerFileSourceInit(const char* filePath);
void AudioCapturerFileSourceDeInit(void);
int32_t AudioCapturerFileSourceStart(void);
int32_t AudioCapturerFileSourceStop(void);
int32_t AudioCapturerFileSourceFrame(char *frame, uint64_t requestBytes, uint64_t *replyBytes);
int32_t AudioCapturerFileSourceSetVolume(float left, float right);
bool AudioCapturerFileSourceIsMuteRequired(void);
int32_t AudioCapturerFileSourceSetMute(bool);
int32_t AudioCapturerFileSourceGetVolume(float *left, float *right);
#ifdef __cplusplus
}
#endif

#endif  // AUDIO_CAPTURER_FILE_SOURCE_INTF_H
