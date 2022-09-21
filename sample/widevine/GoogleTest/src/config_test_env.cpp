// Copyright 2013 Google Inc. All Rights Reserved.

#include "config_test_env.h"

namespace wvcdm {

namespace {

const std::string kWidevineKeySystem = "com.widevine.alpha";

// Content Protection license server (UAT) data
const std::string kCpUatLicenseServer =
    "http://widevine-proxy.appspot.com/proxy";
const std::string kCpClientAuth = "";
const std::string kCpKeyId =
    "00000042"                          // blob size
    "70737368"                          // "pssh"
    "00000000"                          // flags
    "edef8ba979d64acea3c827dcd51d21ed"  // Widevine system id
    "00000022"                          // pssh data size
    // pssh data:
    "08011a0d7769646576696e655f746573"
    "74220f73747265616d696e675f636c69"
    "7031";
const std::string kCpOfflineKeyId =
    "00000040"                          // blob size
    "70737368"                          // "pssh"
    "00000000"                          // flags
    "edef8ba979d64acea3c827dcd51d21ed"  // Widevine system id
    "00000020"                          // pssh data size
    // pssh data:
    "08011a0d7769646576696e655f746573"
    "74220d6f66666c696e655f636c697032";
const std::string kCpUatServiceCertificate =
    "0ABF020803121028703454C008F63618ADE7443DB6C4C8188BE7F99005228E023082010A02"
    "82010100B52112B8D05D023FCC5D95E2C251C1C649B4177CD8D2BEEF355BB06743DE661E3D"
    "2ABC3182B79946D55FDC08DFE95407815E9A6274B322A2C7F5E067BB5F0AC07A89D45AEA94"
    "B2516F075B66EF811D0D26E1B9A6B894F2B9857962AA171C4F66630D3E4C602718897F5E1E"
    "F9B6AAF5AD4DBA2A7E14176DF134A1D3185B5A218AC05A4C41F081EFFF80A3A040C50B09BB"
    "C740EEDCD8F14D675A91980F92CA7DDC646A06ADAD5101F74A0E498CC01F00532BAC217850"
    "BD905E90923656B7DFEFEF42486767F33EF6283D4F4254AB72589390BEE55808F1D668080D"
    "45D893C2BCA2F74D60A0C0D0A0993CEF01604703334C3638139486BC9DAF24FD67A07F9AD9"
    "4302030100013A1273746167696E672E676F6F676C652E636F6D128003983E30352675F40B"
    "A715FC249BDAE5D4AC7249A2666521E43655739529721FF880E0AAEFC5E27BC980DAEADABF"
    "3FC386D084A02C82537848CC753FF497B011A7DA97788A00E2AA6B84CD7D71C07A48EBF616"
    "02CCA5A3F32030A7295C30DA915B91DC18B9BC9593B8DE8BB50F0DEDC12938B8E9E039CDDE"
    "18FA82E81BB032630FE955D85A566CE154300BF6D4C1BD126966356B287D657B18CE63D0EF"
    "D45FC5269E97EAB11CB563E55643B26FF49F109C2101AFCAF35B832F288F0D9D45960E259E"
    "85FB5D24DBD2CF82764C5DD9BF727EFBE9C861F869321F6ADE18905F4D92F9A6DA6536DB84"
    "75871D168E870BB2303CF70C6E9784C93D2DE845AD8262BE7E0D4E2E4A0759CEF82D109D25"
    "92C72429F8C01742BAE2B3DECADBC33C3E5F4BAF5E16ECB74EADBAFCB7C6705F7A9E3B6F39"
    "40383F9C5116D202A20C9229EE969C2519718303B50D0130C3352E06B014D838540F8A0C22"
    "7C0011E0F5B38E4E298ED2CB301EB4564965F55C5D79757A250A4EB9C84AB3E6539F6B6FDF"
    "56899EA29914";

// Content Protection license server (staging) data
const std::string kCpStagingLicenseServer =
    "http://wv-staging-proxy.appspot.com/proxy";
const std::string kCpStagingServiceCertificate =
    "0AC102080312101705B917CC1204868B06333A2F772A8C1882B4829205228E023082010A02"
    "8201010099ED5B3B327DAB5E24EFC3B62A95B598520AD5BCCB37503E0645B814D876B8DF40"
    "510441AD8CE3ADB11BB88C4E725A5E4A9E0795291D58584023A7E1AF0E38A9127939300861"
    "0B6F158C878C7E21BFFBFEEA77E1019E1E5781E8A45F46263D14E60E8058A8607ADCE04FAC"
    "8457B137A8D67CCDEB33705D983A21FB4EECBD4A10CA47490CA47EAA5D438218DDBAF1CADE"
    "3392F13D6FFB6442FD31E1BF40B0C604D1C4BA4C9520A4BF97EEBD60929AFCEEF55BBAF564"
    "E2D0E76CD7C55C73A082B996120B8359EDCE24707082680D6F67C6D82C4AC5F3134490A74E"
    "EC37AF4B2F010C59E82843E2582F0B6B9F5DB0FC5E6EDF64FBD308B4711BCF1250019C9F5A"
    "0902030100013A146C6963656E73652E7769646576696E652E636F6D128003AE347314B5A8"
    "35297F271388FB7BB8CB5277D249823CDDD1DA30B93339511EB3CCBDEA04B944B927C12134"
    "6EFDBDEAC9D413917E6EC176A10438460A503BC1952B9BA4E4CE0FC4BFC20A9808AAAF4BFC"
    "D19C1DCFCDF574CCAC28D1B410416CF9DE8804301CBDB334CAFCD0D40978423A642E54613D"
    "F0AFCF96CA4A9249D855E42B3A703EF1767F6A9BD36D6BF82BE76BBF0CBA4FDE59D2ABCC76"
    "FEB64247B85C431FBCA52266B619FC36979543FCA9CBBDBBFAFA0E1A55E755A3C7BCE655F9"
    "646F582AB9CF70AA08B979F867F63A0B2B7FDB362C5BC4ECD555D85BCAA9C593C383C857D4"
    "9DAAB77E40B7851DDFD24998808E35B258E75D78EAC0CA16F7047304C20D93EDE4E8FF1C6F"
    "17E6243E3F3DA8FC1709870EC45FBA823A263F0CEFA1F7093B1909928326333705043A29BD"
    "A6F9B4342CC8DF543CB1A1182F7C5FFF33F10490FACA5B25360B76015E9C5A06AB8EE02F00"
    "D2E8D5986104AACC4DD475FD96EE9CE4E326F21B83C7058577B38732CDDABC6A6BED13FB0D"
    "49D38A45EB87A5F4";

// Google Play license server data
const std::string kGpLicenseServer =
    "https://jmt17.google.com/video/license/GetCencLicense";
// Test client authorization string.
// NOTE: Append a userdata attribute to place a unique marker that the
// server team can use to track down specific requests during debugging
// e.g., "<existing-client-auth-string>&userdata=<your-ldap>.<your-tag>"
//       "<existing-client-auth-string>&userdata=jbmr2.dev"
const std::string kGpClientAuth =
    "?source=YOUTUBE&video_id=EGHC6OHNbOo&oauth=ya.gtsqawidevine";
const std::string kGpKeyId =
    "00000034"                          // blob size
    "70737368"                          // "pssh"
    "00000000"                          // flags
    "edef8ba979d64acea3c827dcd51d21ed"  // Widevine system id
    "00000014"                          // pssh data size
    // pssh data:
    "08011210e02562e04cd55351b14b3d74"
    "8d36ed8e";
const std::string kGpOfflineKeyId = kGpKeyId;

const std::string kGpClientOfflineQueryParameters = "&offline=true";
const std::string kGpClientOfflineRenewalQueryParameters =
    "&offline=true&renewal=true";
const std::string kGpClientOfflineReleaseQueryParameters =
    "&offline=true&release=true";

// An invalid key id, expected to fail
const std::string kWrongKeyId =
    "00000034"                          // blob size
    "70737368"                          // "pssh"
    "00000000"                          // flags
    "edef8ba979d64acea3c827dcd51d21ed"  // Widevine system id
    "00000014"                          // pssh data size
    // pssh data:
    "0901121094889920e8d6520098577df8"
    "f2dd5546";

// URL of provisioning server (returned by GetProvisioningRequest())
const std::string kProductionProvisioningServerUrl =
    "https://www.googleapis.com/"
    "certificateprovisioning/v1/devicecertificates/create"
    "?key=AIzaSyB-5OLKTx2iU5mko18DfdwK5611JIjbUhE";

const ConfigTestEnv::LicenseServerConfiguration license_servers[] = {
    {kGooglePlayServer, kGpLicenseServer, kGpClientAuth, kGpKeyId,
     kGpOfflineKeyId, ""},
    {kContentProtectionUatServer, kCpUatLicenseServer, kCpClientAuth,
     kCpKeyId, kCpOfflineKeyId, kCpUatServiceCertificate},
    {kContentProtectionStagingServer, kCpStagingLicenseServer,
     kCpClientAuth, kCpKeyId, kCpOfflineKeyId, kCpStagingServiceCertificate},
};

}  // namespace

ConfigTestEnv::ConfigTestEnv(LicenseServerId server_id) { Init(server_id); }

ConfigTestEnv::ConfigTestEnv(LicenseServerId server_id, bool streaming) {
  Init(server_id);
  if (!streaming) key_id_ = license_servers[server_id].offline_key_id;
}

ConfigTestEnv::ConfigTestEnv(LicenseServerId server_id, bool streaming,
                             bool renew, bool release) {
  Init(server_id);
  if (!streaming) {
    key_id_ = license_servers[server_id].offline_key_id;

    if (kGooglePlayServer == server_id) {
      if (renew) {
        client_auth_.append(kGpClientOfflineRenewalQueryParameters);
      } else if (release) {
        client_auth_.append(kGpClientOfflineReleaseQueryParameters);
      } else {
        client_auth_.append(kGpClientOfflineQueryParameters);
      }
    }
  }
}

void ConfigTestEnv::Init(LicenseServerId server_id) {
  client_auth_ = license_servers[server_id].client_tag;
  key_id_ = license_servers[server_id].key_id;
  key_system_ = kWidevineKeySystem;
  license_server_ = license_servers[server_id].url;
  provisioning_server_url_ = kProductionProvisioningServerUrl;
  service_certificate_ = license_servers[server_id].service_certificate;
  wrong_key_id_ = kWrongKeyId;
}

}  // namespace wvcdm
