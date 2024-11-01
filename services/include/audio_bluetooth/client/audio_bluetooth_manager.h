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

#ifndef AUDIO_BLUETOOTH_MANAGERI_H
#define AUDIO_BLUETOOTH_MANAGERI_H

#include "bluetooth_a2dp_codec.h"
#include "bluetooth_a2dp_a2dpCodecInfo.h"
#include "bluetooth_a2dp_a2dpCodecStatus.h"
#include "bluetooth_hfp_ag.h"
#include "idevice_status_observer.h"
#include "raw_address.h"

namespace OHOS {
namespace Bluetooth {
using namespace bluetooth;

typedef struct BtA2dpAudioCallback {
    void (*OnPlayingStatusChanged)(const RawAddress &device, int playingState, int error);
    void (*OnConfigurationChanged)(const RawAddress &device, const BluetoothA2dpCodecInfo &info, int error);
    void (*OnConnectionStateChanged)(const RawAddress &device, int state);
} BtA2dpAudioCallback;

int GetPlayingState();
RawAddress& GetDevice();
int32_t GetProxy();
int32_t RegisterObserver(AudioStandard::IDeviceStatusObserver &observer);
void DeRegisterObserver();

class HandsFreeGatewayListener : public HandsFreeAudioGatewayObserver {
public:
    HandsFreeGatewayListener() = default;
    virtual ~HandsFreeGatewayListener() = default;

    void OnScoStateChanged(const BluetoothRemoteDevice &device, int state);
    void OnConnectionStateChanged(const BluetoothRemoteDevice &device, int state) {}
    void OnActiveDeviceChanged(const BluetoothRemoteDevice &device) {}
    void OnHfEnhancedDriverSafetyChanged(const BluetoothRemoteDevice &device, int indValue) {}
};

class HandsFreeAudioGatewayManager {
public:
    HandsFreeAudioGatewayManager() = default;
    virtual ~HandsFreeAudioGatewayManager() = default;
    static void RegisterBluetoothScoAgListener();
    static void UnregisterBluetoothScoAgListener();

private:
    static HandsFreeAudioGateway *handsFreeAgInstance_;
    static HandsFreeGatewayListener hfpAgObserver_;
};
}
}
#endif  // AUDIO_BLUETOOTH_MANAGERI_H
