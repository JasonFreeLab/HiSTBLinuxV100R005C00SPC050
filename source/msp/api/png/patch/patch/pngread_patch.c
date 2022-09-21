#include "hipng_accelerate.h"

#ifdef CONFIG_GFX_MEM_MMZ
void hipng_alloc_mmz(png_structrp png_ptr, png_inforp info_ptr)
{
    png_uint_32 iptr = 0;
    png_uint_32 u32RowBytes;
    png_uint_32 u32Phyaddr;
    png_voidp *pVir = HI_NULL;
    hipng_struct_hwctl_s *pstHwStruct = (hipng_struct_hwctl_s *)(png_ptr->private_ptr);

    if (pstHwStruct)
    {
        HI_BOOL bMmu;
#ifdef CONFIG_GFX_MMU_SUPPORT
		HI_CHAR *pZoneName = "iommu";
#else
		HI_CHAR *pZoneName = NULL;
#endif

        u32RowBytes = (png_get_rowbytes(png_ptr, info_ptr) + 0xf) & ~0xf;
#ifdef HIGFX_COMMON
        u32Phyaddr = HI_GFX_AllocMem(u32RowBytes * info_ptr->height, 16, pZoneName, HI_NULL, &bMmu);
#else
        u32Phyaddr = (png_uint_32)HI_MMZ_New(u32RowBytes * info_ptr->height, 16, HI_NULL, HI_NULL);
#endif
        if(u32Phyaddr)
        {
#ifdef HIGFX_COMMON
	        pVir = HI_GFX_Map(u32Phyaddr, bMmu);
#else
			pVir = HI_MMZ_Map(u32Phyaddr, 0);
#endif
	        if (NULL == pVir)
	        {
#ifdef HIGFX_COMMON
	            HI_GFX_FreeMem(u32Phyaddr, bMmu);
#else
		    	HI_MMZ_Delete(u32Phyaddr);
#endif
	        }
			else
			{
		        for (iptr = 0; iptr < info_ptr->height; iptr++)
		            info_ptr->row_pointers[iptr] = (png_bytep)pVir + iptr * u32RowBytes;
			}
		}
	 }

	 if (NULL == pVir)
	 {
	    for (iptr = 0; iptr < info_ptr->height; iptr++)
			info_ptr->row_pointers[iptr] = (png_bytep)png_malloc(png_ptr,
				png_get_rowbytes(png_ptr, info_ptr));
	 }

	 return;
}
#endif