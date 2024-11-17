/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: aidl-cpp /media/iti/468469bc-700b-47e2-ad57-0efb9731e806/android-14.0.0_r67/device/brcm/rpi4/haltest/gpio/interfaces/com/nada/gpio/IGpioService.aidl /media/iti/468469bc-700b-47e2-ad57-0efb9731e806/android-14.0.0_r67/device/brcm/rpi4/haltest/gpio/interfaces/com/nada/gpio/ /media/iti/468469bc-700b-47e2-ad57-0efb9731e806/android-14.0.0_r67/device/brcm/rpi4/haltest/gpio/interfaces/com/nada/gpio/com/nada/gpio/IGpioService.cpp
 */
#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace com {
namespace nada {
namespace gpio {
class IGpioServiceDelegator;

class IGpioService : public ::android::IInterface {
public:
  typedef IGpioServiceDelegator DefaultDelegator;
  DECLARE_META_INTERFACE(GpioService)
  virtual ::android::binder::Status setGpioState(int32_t pin, bool value, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getGpioState(int32_t pin, bool* _aidl_return) = 0;
};  // class IGpioService

class IGpioServiceDefault : public IGpioService {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status setGpioState(int32_t /*pin*/, bool /*value*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getGpioState(int32_t /*pin*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
};  // class IGpioServiceDefault
}  // namespace gpio
}  // namespace nada
}  // namespace com
