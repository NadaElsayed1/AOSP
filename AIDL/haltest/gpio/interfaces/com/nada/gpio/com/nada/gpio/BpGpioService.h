/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: aidl-cpp /media/iti/468469bc-700b-47e2-ad57-0efb9731e806/android-14.0.0_r67/device/brcm/rpi4/haltest/gpio/interfaces/com/nada/gpio/IGpioService.aidl /media/iti/468469bc-700b-47e2-ad57-0efb9731e806/android-14.0.0_r67/device/brcm/rpi4/haltest/gpio/interfaces/com/nada/gpio/ /media/iti/468469bc-700b-47e2-ad57-0efb9731e806/android-14.0.0_r67/device/brcm/rpi4/haltest/gpio/interfaces/com/nada/gpio/com/nada/gpio/IGpioService.cpp
 */
#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/nada/gpio/IGpioService.h>

namespace com {
namespace nada {
namespace gpio {
class BpGpioService : public ::android::BpInterface<IGpioService> {
public:
  explicit BpGpioService(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpGpioService() = default;
  ::android::binder::Status setGpioState(int32_t pin, bool value, bool* _aidl_return) override;
  ::android::binder::Status getGpioState(int32_t pin, bool* _aidl_return) override;
};  // class BpGpioService
}  // namespace gpio
}  // namespace nada
}  // namespace com
