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

#ifndef AUDIO_CAPTURER_FILE_SOURCE_H
#define AUDIO_CAPTURER_FILE_SOURCE_H

#include "audio_info.h"

#include <cstdio>
#include <list>

namespace OHOS {
namespace AudioStandard {
class AudioCapturerFileSource {
public:
    int32_t Init(const char *filePath);
    void DeInit(void);
    int32_t Start(void);
    int32_t Stop(void);
    int32_t CaptureFrame(char *frame, uint64_t requestBytes, uint64_t &replyBytes);
    static AudioCapturerFileSource *GetInstance(void);
private:
    AudioCapturerFileSource();
    ~AudioCapturerFileSource();
    FILE *filePtr = nullptr;
};
}  // namespace AudioStandard
}  // namespace OHOS
#endif // AUDIO_CAPTURER_FILE_SOURCE_H
