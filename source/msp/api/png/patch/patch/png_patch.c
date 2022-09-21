#ifdef HIPNG_ACCELERATE
#include "hipng_accelerate.h"
#endif

#ifdef HI_ADVCA_FUNCTION_RELEASE
#define png_chunk_report(png_ptr, message, error) png_chunk_report(png_ptr, "", error)
#ifdef PNGZ_MSG_CAST
#undef PNGZ_MSG_CAST
#endif
#if ZLIB_VERNUM < 0x1260
#  define PNGZ_MSG_CAST(s) png_constcast(char*,"")
#else
#  define PNGZ_MSG_CAST(s) ("")
#endif

#ifdef PNG_WARNINGS_SUPPORTED
#undef PNG_WARNINGS_SUPPORTED
#endif
#endif

#ifdef CONFIG_GFX_MEM_MMZ
void hipng_free_data(png_const_structrp png_ptr, png_inforp info_ptr)
{
    HI_U32 u32Phyaddr;
    HI_U32 u32Size;
    HI_S32 s32Ret;
	HI_U32 row;

    if (png_ptr->private_ptr)
    {
        HI_BOOL bMmu;

#ifdef HIGFX_COMMON
        s32Ret = HI_GFX_GetPhyaddr((HI_VOID*)info_ptr->row_pointers[0], &u32Phyaddr, &u32Size, &bMmu);
#else
        s32Ret = HI_MMZ_GetPhyaddr(info_ptr->row_pointers[0], (HI_CHAR*)&u32Phyaddr, &u32Size);
#endif
        if (s32Ret < 0)
		{
		    for (row = 0; row < info_ptr->height; row++)
			{
                png_free(png_ptr, info_ptr->row_pointers[row]);
				info_ptr->row_pointers[row] = NULL;
			}
		}
		else
        {
#ifdef HIGFX_COMMON
            HI_GFX_Unmap(u32Phyaddr, bMmu);
			HI_GFX_FreeMem(u32Phyaddr, bMmu);
#else
            HI_MMZ_Unmap(u32Phyaddr);
			HI_MMZ_Delete(u32Phyaddr);
#endif
            for (row = 0; row < (int)info_ptr->height; row++)
			{
			    info_ptr->row_pointers[row] = NULL;
		    }
		}
    }
}
#endif