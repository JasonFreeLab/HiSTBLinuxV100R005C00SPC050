import os
cdm_top = os.path.abspath(os.path.dirname(__file__))
platform_top = cdm_top[0:cdm_top.find('sample')]
print '-------------platform_top = %s' % platform_top
print '-------------cdm_top = %s' % cdm_top

cdm_cflags = '-DZLIB_SHARED -DZLIB -DOPENSSL_THREADS  '
cdm_cflags += '-I'+platform_top+'out/hi3798mv200/hi3798mv2dma_tee/include '
cdm_cflags += '-I'+platform_top+'out/hi3798mv200/hi3798mv2dmb_tee/include '
cdm_cflags += '-I'+platform_top+'out/hi3798mv200/hi3798mv2dmc_tee/include '
cdm_cflags += '-I'+platform_top+'out/hi3798mv200/hi3798mv2dme_tee/include '
cdm_cflags += '-I'+platform_top+'out/hi3798mv200/hi3798mv2dmg_tee/include '
cdm_cflags += '-I'+platform_top+'out/hi3798mv200/hi3798mv2dmp_tee/include '
cdm_cflags += '-I'+platform_top+'out/hi3798mv200/hi3798mv2dma_vmx_ultra_tee/include '
cdm_cflags += '-I'+platform_top+'out/hi3798mv200/hi3798mv2dmb_vmx_ultra_tee/include '
cdm_cflags += '-I'+platform_top+'out/hi3798mv200/hi3798mv2dmc_vmx_ultra_tee/include '
cdm_cflags += '-I'+platform_top+'out/hi3798mv200/hi3798mv2dme_vmx_ultra_tee/include '
cdm_cflags += '-I'+platform_top+'out/hi3798mv200/hi3798mv2dmg_vmx_ultra_tee/include '
cdm_cflags += '-I'+platform_top+'out/hi3798mv200/hi3798mv2dmp_vmx_ultra_tee/include '
print '----------------cdm_cflags = %s' % cdm_cflags

cdm_cxxflags =  '-DZLIB_SHARED -DZLIB -DOPENSSL_THREADS  '
cdm_cxxflags += '-I'+platform_top+'out/hi3798mv200/hi3798mv2dma_tee/include '
cdm_cxxflags += '-I'+platform_top+'out/hi3798mv200/hi3798mv2dmb_tee/include '
cdm_cxxflags += '-I'+platform_top+'out/hi3798mv200/hi3798mv2dmc_tee/include '
cdm_cxxflags += '-I'+platform_top+'out/hi3798mv200/hi3798mv2dmr_tee/include '
cdm_cxxflags += '-I'+platform_top+'out/hi3798mv200/hi3798mv2dmg_tee/include '
cdm_cxxflags += '-I'+platform_top+'out/hi3798mv200/hi3798mv2dmp_tee/include '
cdm_cxxflags += '-I'+platform_top+'out/hi3798mv200/hi3798mv2dma_vmx_ultra_tee/include '
cdm_cxxflags += '-I'+platform_top+'out/hi3798mv200/hi3798mv2dmb_vmx_ultra_tee/include '
cdm_cxxflags += '-I'+platform_top+'out/hi3798mv200/hi3798mv2dmc_vmx_ultra_tee/include '
cdm_cxxflags += '-I'+platform_top+'out/hi3798mv200/hi3798mv2dme_vmx_ultra_tee/include '
cdm_cxxflags += '-I'+platform_top+'out/hi3798mv200/hi3798mv2dmg_vmx_ultra_tee/include '
cdm_cxxflags += '-I'+platform_top+'out/hi3798mv200/hi3798mv2dmp_vmx_ultra_tee/include '
cdm_cxxflags += '-I'+platform_top+'source/component/openssl/include '
cdm_cxxflags += '-I'+platform_top+'base/include '
cdm_cxxflags += '-I'+platform_top+'source/tee/core/libteec/inc '
cdm_cxxflags += '-I'+platform_top+'source/common/include '
cdm_cxxflags += '-I'+platform_top+'source/msp/include '
cdm_cxxflags += '-I'+platform_top+'source/common/api/include '

cdm_ldflags =  '-L'+platform_top+'out/hi3798mv200/hi3798mv2dma_tee/lib/share '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dma_tee/lib/static '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dma_tee/obj/source/rootfs/protobuf/lib '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dmb_tee/lib/share '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dmb_tee/obj/source/rootfs/protobuf/lib '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dmb_tee/lib/static '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dmc_tee/lib/share '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dmc_tee/lib/static '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dmc_tee/obj/source/rootfs/protobuf/lib '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dme_tee/lib/share '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dme_tee/lib/static '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dme_tee/obj/source/rootfs/protobuf/lib '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dmg_tee/lib/share '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dmg_tee/lib/static '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dmg_tee/obj/source/rootfs/protobuf/lib '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dmp_tee/lib/share '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dmp_tee/lib/static '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dmp_tee/obj/source/rootfs/protobuf/lib '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dma_vmx_ultra_tee/lib/share '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dma_vmx_ultra_tee/lib/static '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dma_vmx_ultra_tee/obj/source/rootfs/protobuf/lib '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dmb_vmx_ultra_tee/lib/share '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dmb_vmx_ultra_tee/lib/static '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dmb_vmx_ultra_tee/obj/source/rootfs/protobuf/lib '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dmc_vmx_ultra_tee/lib/share '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dmc_vmx_ultra_tee/lib/static '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dmc_vmx_ultra_tee/obj/source/rootfs/protobuf/lib '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dme_vmx_ultra_tee/lib/share '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dme_vmx_ultra_tee/lib/static '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dme_vmx_ultra_tee/obj/source/rootfs/protobuf/lib '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dmg_vmx_ultra_tee/lib/share '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dmg_vmx_ultra_tee/lib/static '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dmg_vmx_ultra_tee/obj/source/rootfs/protobuf/lib '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dmp_vmx_ultra_tee/lib/share '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dmp_vmx_ultra_tee/lib/static '
cdm_ldflags += '-L'+platform_top+'out/hi3798mv200/hi3798mv2dmp_vmx_ultra_tee/obj/source/rootfs/protobuf/lib '
cdm_ldflags += '-L'+platform_top+'source/component/widevine/lib'

export_variables = {
  'CC': '-gcc',
  'CXX': '-g++',
  'AR': '-ar',
  'LD' : '-ld',
  'CFLAGS': cdm_cflags,
  'CXXFLAGS': cdm_cxxflags,
  'LDFLAGS': cdm_ldflags,
}
