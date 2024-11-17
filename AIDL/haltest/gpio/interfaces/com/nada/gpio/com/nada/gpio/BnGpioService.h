/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: aidl-cpp /media/iti/468469bc-700b-47e2-ad57-0efb9731e806/android-14.0.0_r67/device/brcm/rpi4/haltest/gpio/interfaces/com/nada/gpio/IGpioService.aidl /media/iti/468469bc-700b-47e2-ad57-0efb9731e806/android-14.0.0_r67/device/brcm/rpi4/haltest/gpio/interfaces/com/nada/gpio/ /media/iti/468469bc-700b-47e2-ad57-0efb9731e806/android-14.0.0_r67/device/brcm/rpi4/haltest/gpio/interfaces/com/nada/gpio/com/nada/gpio/IGpioService.cpp
 */
#pragma once

#include <binder/IInterface.h>
#include <com/nada/gpio/IGpioService.h>
#include <binder/Delegate.h>
#include <com/nada/gpio/BnGpioService.h>


namespace com {
namespace nada {
namespace gpio {
class BnGpioService : public ::android::BnInterface<IGpioService> {
public:
  static constexpr uint32_t TRANSACTION_setGpioState = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getGpioState = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  explicit BnGpioService();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnGpioService

class IGpioServiceDelegator : public BnGpioService {
public:
  explicit IGpioServiceDelegator(const ::android::sp<IGpioService> &impl) : _aidl_delegate(impl) {}

  ::android::sp<IGpioService> getImpl() { return _aidl_delegate; }
  ::android::binder::Status setGpioState(int32_t pin, bool value, bool* _aidl_return) override {
    return _aidl_delegate->setGpioState(pin, value, _aidl_return);
  }
  ::android::binder::Status getGpioState(int32_t pin, bool* _aidl_return) override {
    return _aidl_delegate->getGpioState(pin, _aidl_return);
  }
private:
  ::android::sp<IGpioService> _aidl_delegate;
};  // class IGpioServiceDelegator
}  // namespace gpio
}  // namespace nada
}  // namespace com
