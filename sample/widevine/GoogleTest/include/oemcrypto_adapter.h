// Copyright 2013 Google Inc. All Rights Reserved.
//
#ifndef WVCDM_CORE_OEMCRYPTO_ADAPTER_H_
#define WVCDM_CORE_OEMCRYPTO_ADAPTER_H_

#include "OEMCryptoCENC.h"
#include "wv_cdm_types.h"

namespace wvcdm {

// This attempts to open a session at the desired security level.
// If one level is not available, the other will be used instead.
OEMCryptoResult OEMCrypto_OpenSession(OEMCrypto_SESSION* session,
                                      SecurityLevel level);
OEMCryptoResult OEMCrypto_CopyBuffer(
    SecurityLevel level, const uint8_t* data_addr, size_t data_length,
    OEMCrypto_DestBufferDesc* out_buffer, uint8_t subsample_flags);
OEMCryptoResult OEMCrypto_InstallKeybox(const uint8_t* keybox,
                                        size_t keyBoxLength,
                                        SecurityLevel level);
OEMCryptoResult OEMCrypto_IsKeyboxValid(SecurityLevel level);
OEMCryptoResult OEMCrypto_GetDeviceID(uint8_t* deviceID, size_t* idLength,
                                      SecurityLevel level);
OEMCryptoResult OEMCrypto_GetKeyData(uint8_t* keyData, size_t* keyDataLength,
                                     SecurityLevel level);
uint32_t OEMCrypto_APIVersion(SecurityLevel level);
const char* OEMCrypto_SecurityLevel(SecurityLevel level);
OEMCryptoResult OEMCrypto_GetHDCPCapability(SecurityLevel level,
                                            OEMCrypto_HDCP_Capability* current,
                                            OEMCrypto_HDCP_Capability* maximum);
bool OEMCrypto_SupportsUsageTable(SecurityLevel level);
bool OEMCrypto_IsAntiRollbackHwPresent(SecurityLevel level);
OEMCryptoResult OEMCrypto_GetNumberOfOpenSessions(SecurityLevel level,
                                                  size_t* count);
OEMCryptoResult OEMCrypto_GetMaxNumberOfSessions(SecurityLevel level,
                                                 size_t* maximum);
uint8_t OEMCrypto_Security_Patch_Level(SecurityLevel level);
}  // namespace wvcdm

#endif  // WVCDM_CORE_OEMCRYPTO_ADAPTER_H_
