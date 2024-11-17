/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: aidl-cpp /media/iti/468469bc-700b-47e2-ad57-0efb9731e806/android-14.0.0_r67/device/brcm/rpi4/haltest/gpio/interfaces/com/nada/gpio/IGpioService.aidl /media/iti/468469bc-700b-47e2-ad57-0efb9731e806/android-14.0.0_r67/device/brcm/rpi4/haltest/gpio/interfaces/com/nada/gpio/ /media/iti/468469bc-700b-47e2-ad57-0efb9731e806/android-14.0.0_r67/device/brcm/rpi4/haltest/gpio/interfaces/com/nada/gpio/com/nada/gpio/IGpioService.cpp
 */
#include <com/nada/gpio/IGpioService.h>
#include <com/nada/gpio/BpGpioService.h>
namespace com {
namespace nada {
namespace gpio {
DO_NOT_DIRECTLY_USE_ME_IMPLEMENT_META_INTERFACE(GpioService, "com.nada.gpio.IGpioService")
}  // namespace gpio
}  // namespace nada
}  // namespace com
#include <com/nada/gpio/BpGpioService.h>
#include <com/nada/gpio/BnGpioService.h>
#include <binder/Parcel.h>

namespace com {
namespace nada {
namespace gpio {

BpGpioService::BpGpioService(const ::android::sp<::android::IBinder>& _aidl_impl)
    : BpInterface<IGpioService>(_aidl_impl){
}

::android::binder::Status BpGpioService::setGpioState(int32_t pin, bool value, bool* _aidl_return) {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeInt32(pin);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeBool(value);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnGpioService::TRANSACTION_setGpioState, _aidl_data, &_aidl_reply, 0);
  if (_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && IGpioService::getDefaultImpl()) [[unlikely]] {
     return IGpioService::getDefaultImpl()->setGpioState(pin, value, _aidl_return);
  }
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_status.readFromParcel(_aidl_reply);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  if (!_aidl_status.isOk()) {
    return _aidl_status;
  }
  _aidl_ret_status = _aidl_reply.readBool(_aidl_return);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

::android::binder::Status BpGpioService::getGpioState(int32_t pin, bool* _aidl_return) {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeInt32(pin);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnGpioService::TRANSACTION_getGpioState, _aidl_data, &_aidl_reply, 0);
  if (_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && IGpioService::getDefaultImpl()) [[unlikely]] {
     return IGpioService::getDefaultImpl()->getGpioState(pin, _aidl_return);
  }
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_status.readFromParcel(_aidl_reply);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  if (!_aidl_status.isOk()) {
    return _aidl_status;
  }
  _aidl_ret_status = _aidl_reply.readBool(_aidl_return);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

}  // namespace gpio
}  // namespace nada
}  // namespace com
#include <com/nada/gpio/BnGpioService.h>
#include <binder/Parcel.h>
#include <binder/Stability.h>

namespace com {
namespace nada {
namespace gpio {

BnGpioService::BnGpioService()
{
  ::android::internal::Stability::markCompilationUnit(this);
}

::android::status_t BnGpioService::onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) {
  ::android::status_t _aidl_ret_status = ::android::OK;
  switch (_aidl_code) {
  case BnGpioService::TRANSACTION_setGpioState:
  {
    int32_t in_pin;
    bool in_value;
    bool _aidl_return;
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    _aidl_ret_status = _aidl_data.readInt32(&in_pin);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    _aidl_ret_status = _aidl_data.readBool(&in_value);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    ::android::binder::Status _aidl_status(setGpioState(in_pin, in_value, &_aidl_return));
    _aidl_ret_status = _aidl_status.writeToParcel(_aidl_reply);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (!_aidl_status.isOk()) {
      break;
    }
    _aidl_ret_status = _aidl_reply->writeBool(_aidl_return);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
  }
  break;
  case BnGpioService::TRANSACTION_getGpioState:
  {
    int32_t in_pin;
    bool _aidl_return;
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    _aidl_ret_status = _aidl_data.readInt32(&in_pin);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    ::android::binder::Status _aidl_status(getGpioState(in_pin, &_aidl_return));
    _aidl_ret_status = _aidl_status.writeToParcel(_aidl_reply);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (!_aidl_status.isOk()) {
      break;
    }
    _aidl_ret_status = _aidl_reply->writeBool(_aidl_return);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
  }
  break;
  default:
  {
    _aidl_ret_status = ::android::BBinder::onTransact(_aidl_code, _aidl_data, _aidl_reply, _aidl_flags);
  }
  break;
  }
  if (_aidl_ret_status == ::android::UNEXPECTED_NULL) {
    _aidl_ret_status = ::android::binder::Status::fromExceptionCode(::android::binder::Status::EX_NULL_POINTER).writeOverParcel(_aidl_reply);
  }
  return _aidl_ret_status;
}

}  // namespace gpio
}  // namespace nada
}  // namespace com
