/******************************************************************************

  Copyright (C), 2015-2016, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : es20_common.c
  Version       : Initial Draft
  Author        : Hisilicon Device Chipset Key Technologies GPU group
  Created       : 2015/11/19
  Description   :
  History       :
  1.Date        : 2016/05/25
    Author      :
    Modification: group review file
  2.Date        : 2016/06/03
    Author      :
    Modification: change MMZ_Malloc method
  3.Date        : 2016/06/22
    Author      :
    Modification: modify HI_COMMON_DestroyPixmapFromMmz @ Midgard 64Bit compatibility

******************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/time.h>

#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "hifb.h"
#include "hi_dbe.h"
#include "es20_common.h"

#include "mpi_mmz.h"

#ifdef FRAMEBUFFER_DEVICE_OPEN
#include "hi_unf_disp.h"
#include "hi_adp_mpi.h"

int HI_COMMON_OpenFramebufferDevice(int width, int height, display_format display_fmt)
{
    HIFB_ALPHA_S stAlpha;
    struct fb_var_screeninfo vinfo;
    const char* file = "/dev/fb0";
    int fd, err;

    HIADP_Disp_Init(HI_UNF_ENC_FMT_1080P_60);

    HI_UNF_DISP_SetVirtualScreen(HI_UNF_DISPLAY1, width, height);

    HI_SYS_Init();
    HI_UNF_DISP_Init();

    memset(&stAlpha, 0, sizeof(stAlpha));
    stAlpha.bAlphaEnable  = HI_TRUE;
    stAlpha.bAlphaChannel = HI_TRUE;
    stAlpha.u8Alpha0 = 0xff;
    stAlpha.u8Alpha1 = 0xff;
    stAlpha.u8GlobalAlpha = 0x90;

    fd = open(file, O_RDWR, 0);
    if (-1 == fd)
    {
        fprintf(stderr, "open /dev/fb0 failed\n");
        return -1;
    }

    if (ioctl(fd, FBIOPUT_ALPHA_HIFB, &stAlpha) < 0)
    {
        fprintf(stderr, "Unable to set alpha!\n");
        return -1;
    }

    if ((err = ioctl(fd, FBIOGET_VSCREENINFO, &vinfo)) < 0)
    {
        fprintf(stderr, "Unable to FBIOGET_VSCREENINFO!, err=0x%x\n", err);
        return -1;
    }

    switch(display_fmt)
    {
        case DISPLAY_FORMAT_RGB565:
            vinfo.bits_per_pixel = 16;
            vinfo.red.length    = 5;
            vinfo.green.length  = 6;
            vinfo.blue.length   = 5;
            vinfo.blue.offset  = 0;
            vinfo.green.offset = 5;
            vinfo.red.offset = 11;
            break;

        case DISPLAY_FORMAT_ARGB8888:
            vinfo.bits_per_pixel = 32;
            vinfo.red.length    = 8;
            vinfo.green.length  = 8;
            vinfo.blue.length   = 8;
            vinfo.transp.length = 8;
            vinfo.blue.offset  = 0;
            vinfo.green.offset = 8;
            vinfo.red.offset = 16;
            vinfo.transp.offset = 24;
            break;

        case DISPLAY_FORMAT_ARGB4444:
            vinfo.bits_per_pixel = 16;
            vinfo.red.length    = 4;
            vinfo.green.length  = 4;
            vinfo.blue.length   = 4;
            vinfo.transp.length = 4;
            vinfo.blue.offset  = 0;
            vinfo.green.offset = 4;
            vinfo.red.offset = 8;
            vinfo.transp.offset = 12;
            break;

        case DISPLAY_FORMAT_ARGB1555:
            vinfo.bits_per_pixel = 16;
            vinfo.red.length    = 5;
            vinfo.green.length  = 5;
            vinfo.blue.length   = 5;
            vinfo.transp.length = 1;
            vinfo.blue.offset  = 0;
            vinfo.green.offset = 5;
            vinfo.red.offset = 10;
            vinfo.transp.offset = 15;
            break;

        default:
            fprintf(stderr, "display format invalid\n");
            return -1;
            break;
    }

    vinfo.xres = vinfo.xres_virtual = width;
    vinfo.yres = height;
    vinfo.yres_virtual = 2 * vinfo.yres;

    if ((err = ioctl(fd, FBIOPUT_VSCREENINFO, &vinfo)) < 0)
    {
        fprintf(stderr, "Unable to set double buffer mode!, err=0x%x\n", err);
        vinfo.yres_virtual = vinfo.yres;
        if ((err = ioctl(fd, FBIOPUT_VSCREENINFO, &vinfo)) < 0)
        {
            fprintf(stderr, "Unable to FBIOPUT_VSCREENINFO!, err=0x%x\n", err);
            return -1;
        }

        return -1;
    }

    return fd;
}

void HI_COMMON_CloseFramebufferDevice(int fd)
{
    close(fd);

    HIADP_Disp_DeInit();

    HI_SYS_DeInit();
}
#endif

/*EGL API Function*/

#if defined(EGL_API_FBDEV)

NativeDisplayType HI_COMMON_CreateNativeDisplay(void)
{
    return (NativeDisplayType)EGL_DEFAULT_DISPLAY;
}

void HI_COMMON_DestroyNativeDisplay(NativeDisplayType native_display)
{
    return;
}

NativeWindowType HI_COMMON_CreateNativeWindow(int width,int height)
{
    fbdev_window * fb_window = (fbdev_window *)malloc(sizeof(fbdev_window));

    fb_window->width = width;
    fb_window->height = height;

    return (NativeWindowType)fb_window;
}

void HI_COMMON_DestroyNativeWindow(NativeWindowType native_window)
{
    fbdev_window *window = (fbdev_window*)native_window;
    free(window);
}

#if defined(EGL_API_UTGARD)

NativePixmapType HI_COMMON_CreateNativePixmap(unsigned int phy_addr, int width,int height, unsigned char red_size,
          unsigned char green_size,unsigned char blue_size, unsigned char alpha_size, unsigned char luminance_size)
{
    struct fbdev_dma_buf *pixmap_dma = (struct fbdev_dma_buf *)malloc(sizeof(struct fbdev_dma_buf));
    fbdev_pixmap *pixmap = (fbdev_pixmap*)malloc(sizeof(fbdev_pixmap));

    pixmap->flags = (fbdev_pixmap_flags)0;
    pixmap->width = width;
    pixmap->height = height;
    pixmap->red_size = red_size;
    pixmap->green_size = green_size;
    pixmap->blue_size = blue_size;
    pixmap->alpha_size = alpha_size;
    pixmap->luminance_size = luminance_size;
    pixmap->buffer_size = pixmap->red_size + pixmap->green_size + pixmap->blue_size + pixmap->alpha_size + pixmap->luminance_size;
    pixmap->bytes_per_pixel = pixmap->buffer_size / 8;

    pixmap_dma->size = width * height * pixmap->bytes_per_pixel;
    pixmap_dma->fd = HI_COMMON_WrapDmaBufFD(phy_addr, pixmap_dma->size);

    pixmap->data = (unsigned short *)pixmap_dma;
    pixmap->flags = (fbdev_pixmap_flags)(pixmap->flags | FBDEV_PIXMAP_DMA_BUF);

    return (NativePixmapType)pixmap;
}

#elif defined(EGL_API_MIDGARD)

NativePixmapType HI_COMMON_CreateNativePixmap(unsigned int phy_addr, int width,int height, uint64_t pixmap_format)
{
    int i;
    struct egl_linux_pixmap *pixmap_dma = (struct egl_linux_pixmap*)malloc(sizeof(struct egl_linux_pixmap));

    memset(pixmap_dma, 0, sizeof(*pixmap_dma));

    for(i = 0; i < 3; i++)
    {
        pixmap_dma->handles[i].fd = -1;
    }

    pixmap_dma->width = width;
    pixmap_dma->height = height;

    switch(pixmap_format)
    {
        case EGL_PIXMAP_FORMAT_ARGB8888:
            pixmap_dma->planes[0].stride = width * 4;
            pixmap_dma->planes[0].size = pixmap_dma->planes[0].stride * height;
            pixmap_dma->planes[0].offset = 0;
            pixmap_dma->handles[0].fd = HI_COMMON_WrapDmaBufFD(phy_addr, pixmap_dma->planes[0].size);
            break;

        case EGL_PIXMAP_FORMAT_NV21_BT709_WIDE:
            pixmap_dma->planes[0].stride = width * 1;
            pixmap_dma->planes[0].size = pixmap_dma->planes[0].stride * height;
            pixmap_dma->planes[0].offset = 0;
            pixmap_dma->handles[0].fd = HI_COMMON_WrapDmaBufFD(phy_addr, pixmap_dma->planes[0].size);

            pixmap_dma->planes[1].stride = width * 1;
            pixmap_dma->planes[1].size = pixmap_dma->planes[0].stride * height/2;
            pixmap_dma->planes[1].offset = 0;
            pixmap_dma->handles[1].fd = HI_COMMON_WrapDmaBufFD(phy_addr + pixmap_dma->planes[0].size, pixmap_dma->planes[1].size);
            break;

        default:
            fprintf(stderr, "pixmap format 0x%x is not support\n", pixmap_format);
    }

    pixmap_dma->pixmap_format = pixmap_format;

    return (NativePixmapType)egl_create_pixmap_ID_mapping(pixmap_dma);
}

#endif

void HI_COMMON_DestroyNativePixmap(NativePixmapType native_pixmap)
{
#if defined(EGL_API_UTGARD)

    struct fbdev_dma_buf *pixmap_dma;
    fbdev_pixmap *fbpixmap = (fbdev_pixmap *)native_pixmap;

    pixmap_dma = (struct fbdev_dma_buf *)(fbpixmap->data);
    close(pixmap_dma->fd);

    free(fbpixmap);

#elif defined(EGL_API_MIDGARD)

    int i;
    struct egl_linux_pixmap *pixmap_dma = (struct egl_linux_pixmap *)egl_lookup_pixmap_ID_mapping((int)(unsigned long)native_pixmap);

    egl_destroy_pixmap_ID_mapping((int)(unsigned long)native_pixmap);

    for(i = 0; i < 3; i++)
    {
        close(pixmap_dma->handles[i].fd);
    }

    free(pixmap_dma);

#endif
}

#elif defined(EGL_API_DIRECTFB)

static IDirectFB *pdfb;
static IDirectFBDisplayLayer *pdfb_layer;

NativeDisplayType HI_COMMON_CreateDFBNativeDisplay(int width, int height, DFBSurfacePixelFormat pixelformat)
{
    int ret;
    DFBDisplayLayerConfig dfb_layer_config;

    int argc = 0;
    char **argv = (char**)malloc(sizeof(char**));

    ret = DirectFBInit(&argc, &argv);
    ASSERT_EQUAL(ret, DFB_OK);

    ret = DirectFBCreate(&pdfb);
    ASSERT_EQUAL(ret, DFB_OK);

    ret = pdfb->GetDisplayLayer(pdfb, DLID_PRIMARY, &pdfb_layer);
    ASSERT_EQUAL(ret, DFB_OK);

    ret = pdfb_layer->SetCooperativeLevel(pdfb_layer, DLSCL_ADMINISTRATIVE);
    ASSERT_EQUAL(ret, DFB_OK);

    ret = pdfb_layer->GetConfiguration(pdfb_layer, &dfb_layer_config);
    ASSERT_EQUAL(ret, DFB_OK);

    dfb_layer_config.flags = (DFBDisplayLayerConfigFlags)(DLCONF_WIDTH | DLCONF_HEIGHT | DLCONF_PIXELFORMAT);
    dfb_layer_config.width = width;
    dfb_layer_config.height = height;
    dfb_layer_config.pixelformat = pixelformat;

    ret = pdfb_layer->SetConfiguration(pdfb_layer, &dfb_layer_config);
    ASSERT_EQUAL(ret, DFB_OK);

    fprintf(stderr, "create directfb layer = %p\n", pdfb_layer);

    return (NativeDisplayType)pdfb_layer;
}

void HI_COMMON_DestroyDFBNativeDisplay(void)
{
    int ret;

    ret = pdfb_layer->Release(pdfb_layer);
    ASSERT_EQUAL(ret, DFB_OK);

    ret = pdfb->Release(pdfb);
    ASSERT_EQUAL(ret, DFB_OK);
}

NativeWindowType HI_COMMON_CreateDFBNativeWindow(int x, int y, int width, int height, DFBSurfacePixelFormat pixelformat, IDirectFBWindow **pdfb_window)
{
    int ret;
    DFBWindowDescription  dfb_window_desc;
    IDirectFBWindow *dfb_window;
    IDirectFBSurface *dfb_window_surface ;

    memset(&dfb_window_desc, 0, sizeof(DFBWindowDescription) );

    dfb_window_desc.flags  = (DFBWindowDescriptionFlags)(DWDESC_POSX | DWDESC_POSY | DWDESC_WIDTH | DWDESC_HEIGHT \
    					| DWDESC_PIXELFORMAT | DWDESC_OPTIONS | DWDESC_CAPS | DWDESC_SURFACE_CAPS);
    dfb_window_desc.posx   = 0;
    dfb_window_desc.posy   = 0;
    dfb_window_desc.width  = width;
    dfb_window_desc.height = height;
    if(pixelformat != DSPF_RGB16)
    {
        dfb_window_desc.options = DWOP_ALPHACHANNEL;
        dfb_window_desc.caps = DWCAPS_ALPHACHANNEL;
    }

    dfb_window_desc.caps = (DFBWindowCapabilities)((int)dfb_window_desc.caps | DWCAPS_DOUBLEBUFFER);
    dfb_window_desc.pixelformat = pixelformat;
    dfb_window_desc.surface_caps = (DFBSurfaceCapabilities)(DSCAPS_PRIMARY | DSCAPS_VIDEOONLY | DSCAPS_DOUBLE);

    ret = pdfb_layer->CreateWindow(pdfb_layer, &dfb_window_desc, &dfb_window);
    ASSERT_EQUAL(ret, DFB_OK);

    ret = dfb_window->SetOpacity( dfb_window, 0xff);
    ASSERT_EQUAL(ret, DFB_OK);

    ret = dfb_window->GetSurface(dfb_window, &dfb_window_surface);
    ASSERT_EQUAL(ret, DFB_OK);

    *pdfb_window = dfb_window;

    fprintf(stderr, "create directfb window = %p\n", dfb_window_surface);

    return (NativeWindowType)dfb_window_surface;
}

void HI_COMMON_DestroyDFBNativeWindow(NativeWindowType native_window, IDirectFBWindow *dfb_window)
{
    IDirectFBSurface *dfb_window_surface = (IDirectFBSurface*)native_window;
    int ret;

    ret = dfb_window_surface->Release(dfb_window_surface);
    ASSERT_EQUAL(ret, DFB_OK);

    dfb_window->Release(dfb_window);
    ASSERT_EQUAL(ret, DFB_OK);

    return;
}

EGLNativePixmapType HI_COMMON_CreateDFBNativePixmap(int width, int height, DFBSurfacePixelFormat pixelformat)
{
    int ret;
    IDirectFBSurface *pdfb_pixmap;
    DFBSurfaceDescription dfb_surface_dec;

    dfb_surface_dec.flags = (DFBSurfaceDescriptionFlags)(DSDESC_CAPS | DSDESC_WIDTH | DSDESC_HEIGHT | DSDESC_PIXELFORMAT);
    dfb_surface_dec.caps = (DFBSurfaceCapabilities)DSCAPS_VIDEOONLY;

    dfb_surface_dec.width = width;
    dfb_surface_dec.height = height;
    dfb_surface_dec.pixelformat = pixelformat;

    ret = pdfb->CreateSurface(pdfb, &dfb_surface_dec, &pdfb_pixmap);
    ASSERT_EQUAL(ret, DFB_OK);

    fprintf(stderr, "create directfb pixmap = %p\n", pdfb_pixmap);

    return (EGLNativePixmapType)pdfb_pixmap;
}

void HI_COMMON_DestroyDFBNativePixmap(NativePixmapType native_pixmap)
{
    int ret;
    IDirectFBSurface *pdfb_pixmap = (IDirectFBSurface*)native_pixmap;

    ret = pdfb_pixmap->Release(pdfb_pixmap);
    ASSERT_EQUAL(ret, DFB_OK);

    return;
}

#endif

/*OpenGL ES API Function*/

unsigned int HI_COMMON_CreateShader(const char * shader_path, unsigned int shader_type)
{
    unsigned int shader_id;
    char* shader_data;
    int compiled;

    shader_data = (char *)HI_COMMON_LoadFile(shader_path, 0, 0, "r");

    shader_id = glCreateShader(shader_type);
    glShaderSource(shader_id, 1, (const char**) &shader_data, NULL);
    glCompileShader(shader_id);

    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled);
    ASSERT_EQUAL(compiled, GL_TRUE);

    free(shader_data);

    return shader_id;
}

void HI_COMMON_DestroyShader(unsigned int shader_id)
{
    glDeleteShader(shader_id);
}

unsigned int HI_COMMON_CreateProgram(unsigned int vshader_id, unsigned int fshader_id)
{
    unsigned int program_id;
    int ret = GL_FALSE;

    program_id = glCreateProgram();
    glAttachShader(program_id, vshader_id);
    glAttachShader(program_id, fshader_id);
    glLinkProgram(program_id);

    glGetProgramiv(program_id, GL_LINK_STATUS, &ret);
    ASSERT_EQUAL(ret, GL_TRUE);

    glUseProgram(program_id);

    return program_id;
}

void HI_COMMON_DestroyProgram(unsigned int program_id)
{
    glDeleteProgram(program_id);
}

unsigned int HI_COMMON_CreateTexture(unsigned int tex_num, unsigned int tex_target, int tex_wrap_mode, int tex_filter)
{
    unsigned int texture_id;

    glActiveTexture(tex_num);
    glGenTextures(1, &texture_id);
    glBindTexture(tex_target, texture_id);

    glTexParameteri(tex_target, GL_TEXTURE_WRAP_S, tex_wrap_mode);
    glTexParameteri(tex_target, GL_TEXTURE_WRAP_T, tex_wrap_mode);
    glTexParameteri(tex_target, GL_TEXTURE_MIN_FILTER, tex_filter);
    glTexParameteri(tex_target, GL_TEXTURE_MAG_FILTER, tex_filter);

    return texture_id;
}

void HI_COMMON_DestroyTexture(unsigned int texture_id)
{
    glDeleteTextures(1, &texture_id);
}

unsigned int HI_COMMON_CreateBuffer(unsigned int buffer_type, GLsizeiptr size, const void *data)
{
    unsigned int buffer_id;

    glGenBuffers(1, &buffer_id);
    glBindBuffer(buffer_type, buffer_id);
    glBufferData(buffer_type, size, data, GL_STATIC_DRAW);

    return buffer_id;
}

void HI_COMMON_DestroyBuffer(unsigned int buffer_id)
{
    glDeleteBuffers(1, &buffer_id);
}

unsigned int HI_COMMON_CreateFBO(unsigned int texture_id, unsigned int tex_target, unsigned int attachment)
{
    int ret;
    unsigned int fbo_id;

    glGenFramebuffers(1, &fbo_id);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, tex_target, texture_id, 0);
    ret = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    ASSERT_EQUAL(ret, GL_FRAMEBUFFER_COMPLETE);

    return fbo_id;
}

void HI_COMMON_DestroyFBO(unsigned int fbo_id)
{
    glDeleteFramebuffers(1, &fbo_id);
}

/*Other Function*/

int HI_COMMON_WrapDmaBufFD(unsigned int physical_address, unsigned int size)
{
    struct hidbe_ioctl_wrap phywrap;
    int dmabuf_fd;

    int fd = open("/dev/hi_dbe", O_RDWR);

    phywrap.dbe_phyaddr = physical_address;
    phywrap.dbe_size = size;
    phywrap.dbe_smmuflag = 0;

    dmabuf_fd = ioctl(fd, DBE_COMMAND_WRAP_ADDRESS, &phywrap);

    fprintf(stderr, "IN~ mem fd = 0x%x\n", dmabuf_fd);

    return dmabuf_fd;
}

void * HI_COMMON_LoadFile(const char *f_path, unsigned long skip, unsigned long f_size, const char *f_type)
{
    /* read resource file */
    unsigned char *retval = NULL;
    FILE *fptr = NULL;

    fptr = fopen(f_path, f_type);
    if (fptr == NULL)
    {
        fprintf(stderr, "Can not open file: %s\n", f_path);
        return NULL;
    }

    /* auto check file size when size is 0 */
    if(f_size == 0)
    {
        fseek(fptr, 0, SEEK_END);
        f_size = ftell(fptr);
    }
    fseek(fptr, skip, SEEK_SET);

    do
    {
        if((retval = (unsigned char *)malloc(sizeof(unsigned char) * f_size + 1)) == NULL)
        {
            fprintf(stderr, "malloc failed\n");
            break;
        }

        memset(retval, 0, f_size+1);

        if(fread(retval, sizeof(unsigned char), f_size, fptr) != f_size)
        {
            fprintf(stderr, "read failed\n");
            break;
        }

        fclose(fptr);
        return retval;
    }while (0);

    /* error handle */
    fprintf(stderr, "error while read resource file!\n");

    fclose(fptr);
    free(retval);

    return NULL;
}

void HI_COMMON_ModifyVirtualMemory(void **vir_addr, unsigned int color, unsigned long size)
{
    int i = 0;
    unsigned int *viraddr = (unsigned int*)*vir_addr;

    for(i=0; i < size; i++)
    {
        *viraddr = color;
        viraddr++;
    }
}

void HI_COMMON_PostMemoryToFramebuffer(void *virtual_addr, int memsize)
{
    struct fb_fix_screeninfo finfo;
    struct fb_var_screeninfo vinfo;
    unsigned long mapped_memlen = 0;
    void * mapped_mem = NULL;

    int console_fd = open("/dev/fb0", O_RDWR, 0);
    if (-1 == console_fd)
    {
        fprintf(stderr, "open /dev/fb0 failed\n");
        return;
    }

    /* Get the fix screen info of hardware */
    if (ioctl(console_fd, FBIOGET_FSCREENINFO, &finfo) < 0)
    {
        fprintf(stderr, "Couldn't get console hardware info\n");
        goto CLOSEFD;
    }

    mapped_memlen = finfo.smem_len;
    if(memsize > mapped_memlen)
    {
        fprintf(stderr, "out of memsize !\n");
        goto CLOSEFD;
    }

    mapped_mem = mmap(NULL, mapped_memlen, PROT_READ | PROT_WRITE, MAP_SHARED, console_fd, 0);
    if(mapped_mem == (char *)-1)
    {
        fprintf(stderr, "Unable to memory map the video hardware\n");
        mapped_mem = NULL;
        goto CLOSEFD;
    }

    /* Determine the current screen depth */
    if (ioctl(console_fd, FBIOGET_VSCREENINFO, &vinfo) < 0)
    {
        fprintf(stderr, "Couldn't get vscreeninfo\n");
        goto UNMAP;
    }

    memcpy(mapped_mem, virtual_addr, memsize);

UNMAP:
    munmap(mapped_mem, mapped_memlen);

CLOSEFD:
    close(console_fd);
}

HI_MMZ_BUF_S * HI_COMMON_CreateMMZMemory(unsigned int size)
{
    HI_MMZ_BUF_S *pBuf = (HI_MMZ_BUF_S*)malloc(sizeof(HI_MMZ_BUF_S));

    memset(pBuf, 0, sizeof(HI_MMZ_BUF_S));

    snprintf((*pBuf).bufname, 8, "%s", "buf_pixmap");

    (*pBuf).bufsize = size;
    HI_MPI_MMZ_Malloc(pBuf);

    return pBuf;
}

void HI_COMMON_DestroyMMZMemory(HI_MMZ_BUF_S *pBuf)
{
    HI_MPI_MMZ_Free(pBuf);
}

