// Copyright 2013 Google Inc. All Rights Reserved.

#ifndef WVCDM_CORE_CDM_CLIENT_PROPERTY_SET_H_
#define WVCDM_CORE_CDM_CLIENT_PROPERTY_SET_H_

#include <stdint.h>
#include <string>
#include <vector>

namespace wvcdm {

class CdmClientPropertySet {
 public:
  virtual ~CdmClientPropertySet() {}

  virtual const std::string& security_level() const = 0;
  virtual bool use_privacy_mode() const = 0;
  virtual const std::string& service_certificate() const = 0;
  virtual void set_service_certificate(const std::string& cert) = 0;
  virtual bool is_session_sharing_enabled() const = 0;
  virtual uint32_t session_sharing_id() const = 0;
  virtual void set_session_sharing_id(uint32_t id) = 0;
  virtual const std::string& app_id() const = 0;
};

}  // namespace wvcdm

#endif  // WVCDM_CORE_CDM_CLIENT_PROPERTY_SET_H_
