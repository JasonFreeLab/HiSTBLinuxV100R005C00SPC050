import os
cdm_top = os.path.abspath(os.path.dirname(__file__))
platform_top = cdm_top[0:cdm_top.find('sample')]
print '-------------platform_top = %s' % platform_top
print '-------------cdm_top = %s' % cdm_top

cdm_cflags = '-DZLIB_SHARED -DZLIB -DOPENSSL_THREADS  '+'-I'+platform_top+'source/rootfs/protobuf/include '+'-march=armv7-a -mcpu=cortex-a9 -mfloat-abi=softfp -mfpu=vfpv3-d16 -DOPENSSL_NO_STATIC_ENGINE -ldl -fPIC'
print '----------------cdm_cflags = %s' % cdm_cflags

cdm_cxxflags = '-DZLIB_SHARED -DZLIB -DOPENSSL_THREADS  '+'-I'+platform_top+'source/rootfs/protobuf/include '+'-I'+platform_top+'source/component/openssl/include '+'-I'+platform_top+'base/include '+'-I'+platform_top+'source/tee/core/trustedcore/libteec/inc '+'-I'+platform_top+'source/common/include '+'-I'+platform_top+'source/msp/include '+'-I'+platform_top+'source/common/api/include '+'-march=armv7-a -mcpu=cortex-a9 -mfloat-abi=softfp -mfpu=vfpv3-d16 -DOPENSSL_NO_STATIC_ENGINE -ldl -fPIC'

cdm_ldflags = '-L'+platform_top+'out/hi3798cv200/hi3798cv2dmb_tee/lib/share '+'-L'+platform_top+'source/rootfs/protobuf/lib '+'-L'+platform_top+'out/hi3798cv200/hi3798cv2dmb_tee/lib/static '+'-L'+platform_top+'source/component/widevine/lib'

export_variables = {
  'CC': 'arm-histbv310-linux-gcc',
  'CXX': 'arm-histbv310-linux-g++',
  'AR': 'arm-histbv310-linux-ar',
  'LD' : 'arm-histbv310-linux-ld',
  'CFLAGS': cdm_cflags,
  'CXXFLAGS': cdm_cxxflags,
  'LDFLAGS': cdm_ldflags,
}
