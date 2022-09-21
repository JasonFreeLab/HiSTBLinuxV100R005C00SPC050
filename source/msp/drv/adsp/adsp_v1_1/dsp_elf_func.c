
#include "dsp_elf_func.h"
#include "hi_reg_common.h"
#include "drv_adsp_private.h"

HI_S32 ResetELFSection(HI_U32 u32BaseAddr, HI_U32 u32Size)
{
    HI_VOID* pElfAddr = HI_NULL;

    if (u32BaseAddr > HI_PERI_BASE_ADDR)
    {
        pElfAddr = ioremap_nocache(u32BaseAddr, u32Size);
    }
    else
    {
        pElfAddr = phys_to_virt(u32BaseAddr);
    }

    if (HI_NULL == pElfAddr)
    {
        HI_ERR_ADSP("memory mmap failed\n");
        return HI_FAILURE;
    }

    memset(pElfAddr, 0, u32Size);

    if (u32BaseAddr > HI_PERI_BASE_ADDR)
    {
        iounmap(pElfAddr);
    }

    return HI_SUCCESS;
}

HI_S32 MemcpySection(HI_U32* pdst, HI_U32* psrc, HI_U32 ifilesize)
{
    HI_U32 value;
    HI_S32 i;

    HI_U32* udst = pdst ;
    HI_UCHAR* usrc = (HI_UCHAR*)psrc ;
    HI_VIRT_ADDR_T flag  = (HI_VIRT_ADDR_T)pdst ;

    if (flag & 3)
    {
        HI_WARN_ADSP("warning dst address is not align in 32bit\n");
    }

    for (i = 0; i < ((ifilesize + 3) >> 2); i++)
    {
        value   = usrc[0] | (usrc[1] << 8) | (usrc[2] << 16) | (usrc[3] << 24);
        udst[i] = value;
        usrc += 4;
    }

    return HI_SUCCESS;
}

HI_S32 CopyELFSection(HI_UCHAR* pElfAddr)
{
    HI_S32 j;
    Elf32_Ehdr* phdr = (Elf32_Ehdr*)pElfAddr;
    Elf32_Phdr* ppdr = (Elf32_Phdr*)(pElfAddr + phdr->e_phoff);
    HI_VOID* pAddr;

    for ( j = 0 ; j < phdr->e_phnum ; j++)
    {
        if ( ( ppdr[j].p_type == PT_LOAD ) && ( ppdr[j].p_filesz != 0) )
        {

            if (ppdr[j].p_paddr > HI_PERI_BASE_ADDR)
            {
                pAddr = ioremap_nocache(ppdr[j].p_paddr , ppdr[j].p_filesz + 3);
            }
            else
            {
                pAddr = phys_to_virt(ppdr[j].p_paddr);
            }

            if (HI_NULL == pAddr)
            {
                return HI_FAILURE;
            }

            HI_INFO_ADSP("Phy addr: 0x%.8x;size: 0x%.8x, flag(%d)\n", ppdr[j].p_paddr, ppdr[j].p_filesz, ppdr[j].p_paddr > HI_PERI_BASE_ADDR);
            MemcpySection((HI_U32*)pAddr , (HI_U32*)(pElfAddr + ppdr[j].p_offset) , ppdr[j].p_filesz);

            if (ppdr[j].p_paddr > HI_PERI_BASE_ADDR)
            {
                iounmap(pAddr);
            }
        }
    }
    return  0;
}

HI_S32 CheckELFPaser(HI_UCHAR* pElfAddr)
{
    HI_S32 i, j;
    Elf32_Ehdr* phdr = (Elf32_Ehdr*)pElfAddr;
    Elf32_Phdr* ppdr = (Elf32_Phdr*)(pElfAddr + phdr->e_phoff);
    HI_U32* pAddr;

    for (j = 0; j < phdr->e_phnum; j++)
    {
        if ((ppdr[j].p_type == PT_LOAD) && (ppdr[j].p_filesz != 0))
        {
            //将ELF解析出来的物理地址映射到虚拟地址
            if (ppdr[j].p_paddr > HI_PERI_BASE_ADDR)
            {
                pAddr = ioremap_nocache(ppdr[j].p_paddr , ppdr[j].p_filesz + 3);
            }
            else
            {
                pAddr = phys_to_virt( ppdr[j].p_paddr);
            }

            if (HI_NULL == pAddr)
            {
                return HI_FAILURE;
            }

            for (i = 0; i < ppdr[j].p_filesz >> 2; i++)
            {
                //虚拟地址对应的值，与ELF中解析的值比较
                if (pAddr[i] != ((HI_U32*)(pElfAddr + ppdr[j].p_offset))[i])
                {
                    HI_ERR_ADSP("Error addr 0x%x: 0x%x - 0x%x:0x%x \r\n", ppdr[j].p_paddr , pAddr[i], ((HI_U32*)(pElfAddr + ppdr[j].p_offset))[i], ((HI_U32*)(pElfAddr + ppdr[j].p_offset))[i]);
                    if (ppdr[j].p_paddr > HI_PERI_BASE_ADDR)
                    {
                        iounmap(pAddr);
                    }
                    return HI_FAILURE;
                }
            }
            if (ppdr[j].p_paddr > HI_PERI_BASE_ADDR)
            {
                iounmap(pAddr);
            }
        }
    }

    return HI_SUCCESS;
}
