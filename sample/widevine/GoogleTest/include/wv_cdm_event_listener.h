// Copyright 2012 Google Inc. All Rights Reserved.

#ifndef WVCDM_CORE_WV_CDM_EVENT_LISTENER_H_
#define WVCDM_CORE_WV_CDM_EVENT_LISTENER_H_

#include "wv_cdm_types.h"

namespace wvcdm {

// Listener for events from the Content Decryption Module.
class WvCdmEventListener {
 public:
  WvCdmEventListener() {}
  virtual ~WvCdmEventListener() {}

  virtual void OnSessionRenewalNeeded(const CdmSessionId& session_id) = 0;
  virtual void OnSessionKeysChange(const CdmSessionId& session_id,
                                   const CdmKeyStatusMap& keys_status,
                                   bool has_new_usable_key) = 0;
  // Note that a |new_expiry_time_seconds| of 0 represents never expired
  // license.
  virtual void OnExpirationUpdate(const CdmSessionId& session_id,
                                  int64_t new_expiry_time_seconds) = 0;

 private:
  CORE_DISALLOW_COPY_AND_ASSIGN(WvCdmEventListener);
};

}  // namespace wvcdm

#endif  // WVCDM_CORE_WV_CDM_EVENT_LISTENER_H_
