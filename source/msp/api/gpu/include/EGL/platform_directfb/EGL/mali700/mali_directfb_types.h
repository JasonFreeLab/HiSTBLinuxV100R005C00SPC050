/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2014-2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */
#ifndef _MALI_FBDEV_TYPES_H_
#define _MALI_FBDEV_TYPES_H_

#if MALI_USE_UMP
#include <ump/ump.h>
#endif

typedef struct fbdev_window
{
	unsigned short width;
	unsigned short height;
} fbdev_window;

typedef union mem_handle
{
#if MALI_USE_UMP
	ump_handle ump_mem_handle; /* ump handle to memory*/
#endif
	int fd;                    /* fd to dma memory */
} mem_handle;


typedef enum fbdev_pixmap_format
{
	EGL_PIXMAP_FORMAT_BGR565 = 0x7bcd0000,
	EGL_PIXMAP_FORMAT_RGB565,
	EGL_PIXMAP_FORMAT_BGR565_AFBC,
	EGL_PIXMAP_FORMAT_RGB565_AFBC,
	EGL_PIXMAP_FORMAT_BGR565_AFBC_SPLITBLK,
	EGL_PIXMAP_FORMAT_RGB565_AFBC_SPLITBLK,
	EGL_PIXMAP_FORMAT_BGR565_AFBC_WIDEBLK,
	EGL_PIXMAP_FORMAT_RGB565_AFBC_WIDEBLK,
	EGL_PIXMAP_FORMAT_ABGR8888,
	EGL_PIXMAP_FORMAT_ARGB8888,
	EGL_PIXMAP_FORMAT_BGRA8888,
	EGL_PIXMAP_FORMAT_RGBA8888,
	EGL_PIXMAP_FORMAT_ABGR8888_AFBC,
	EGL_PIXMAP_FORMAT_XBGR8888_AFBC,
	EGL_PIXMAP_FORMAT_ARGB8888_AFBC,
	EGL_PIXMAP_FORMAT_BGRA8888_AFBC,
	EGL_PIXMAP_FORMAT_RGBA8888_AFBC,
	EGL_PIXMAP_FORMAT_ABGR8888_AFBC_SPLITBLK,
	EGL_PIXMAP_FORMAT_XBGR8888_AFBC_SPLITBLK,
	EGL_PIXMAP_FORMAT_ARGB8888_AFBC_SPLITBLK,
	EGL_PIXMAP_FORMAT_BGRA8888_AFBC_SPLITBLK,
	EGL_PIXMAP_FORMAT_RGBA8888_AFBC_SPLITBLK,
	EGL_PIXMAP_FORMAT_ABGR8888_AFBC_SPLITBLK_WIDEBLK,
	EGL_PIXMAP_FORMAT_XBGR8888_AFBC_SPLITBLK_WIDEBLK,
	EGL_PIXMAP_FORMAT_ARGB8888_AFBC_SPLITBLK_WIDEBLK,
	EGL_PIXMAP_FORMAT_BGRA8888_AFBC_SPLITBLK_WIDEBLK,
	EGL_PIXMAP_FORMAT_RGBA8888_AFBC_SPLITBLK_WIDEBLK,
	EGL_PIXMAP_FORMAT_XBGR8888,
	EGL_PIXMAP_FORMAT_XRGB8888,
	EGL_PIXMAP_FORMAT_BGRX8888,
	EGL_PIXMAP_FORMAT_RGBX8888,
	EGL_PIXMAP_FORMAT_BGR888,
	EGL_PIXMAP_FORMAT_RGB888,
	EGL_PIXMAP_FORMAT_BGR888_AFBC,
	EGL_PIXMAP_FORMAT_RGB888_AFBC,
	EGL_PIXMAP_FORMAT_BGR888_AFBC_SPLITBLK,
	EGL_PIXMAP_FORMAT_RGB888_AFBC_SPLITBLK,
	EGL_PIXMAP_FORMAT_BGR888_AFBC_SPLITBLK_WIDEBLK,
	EGL_PIXMAP_FORMAT_RGB888_AFBC_SPLITBLK_WIDEBLK,
	EGL_PIXMAP_FORMAT_ABGR4444,
	EGL_PIXMAP_FORMAT_ABGR4444_AFBC,
	EGL_PIXMAP_FORMAT_ARGB4444,
	EGL_PIXMAP_FORMAT_BGRA4444,
	EGL_PIXMAP_FORMAT_RGBA4444,
	EGL_PIXMAP_FORMAT_ABGR1555,
	EGL_PIXMAP_FORMAT_ABGR1555_AFBC,
	EGL_PIXMAP_FORMAT_ARGB1555,
	EGL_PIXMAP_FORMAT_BGRA5551,
	EGL_PIXMAP_FORMAT_RGBA5551,
	EGL_PIXMAP_FORMAT_L8,
	EGL_PIXMAP_FORMAT_YV12_BT601_NARROW,
	EGL_PIXMAP_FORMAT_YV12_BT601_WIDE,
	EGL_PIXMAP_FORMAT_YV12_BT709_NARROW,
	EGL_PIXMAP_FORMAT_YV12_BT709_WIDE,
	EGL_PIXMAP_FORMAT_NV12_BT601_NARROW,
	EGL_PIXMAP_FORMAT_NV12_BT601_WIDE,
	EGL_PIXMAP_FORMAT_NV12_BT709_NARROW,
	EGL_PIXMAP_FORMAT_NV12_BT709_WIDE,
	EGL_PIXMAP_FORMAT_YUYV_BT601_NARROW,
	EGL_PIXMAP_FORMAT_YUYV_BT601_WIDE,
	EGL_PIXMAP_FORMAT_YUYV_BT709_NARROW,
	EGL_PIXMAP_FORMAT_YUYV_BT709_WIDE,
	EGL_PIXMAP_FORMAT_NV21_BT601_NARROW,
	EGL_PIXMAP_FORMAT_NV21_BT601_WIDE,
	EGL_PIXMAP_FORMAT_NV21_BT709_NARROW,
	EGL_PIXMAP_FORMAT_NV21_BT709_WIDE,
	EGL_PIXMAP_FORMAT_NV16_BT601_NARROW,
	EGL_PIXMAP_FORMAT_NV16_BT601_WIDE,
	EGL_PIXMAP_FORMAT_NV16_BT709_NARROW,
	EGL_PIXMAP_FORMAT_NV16_BT709_WIDE,
	EGL_PIXMAP_FORMAT_YUV420_8BIT_BT601_NARROW_AFBC,
	EGL_PIXMAP_FORMAT_YUV420_8BIT_BT601_WIDE_AFBC,
	EGL_PIXMAP_FORMAT_YUV420_8BIT_BT709_NARROW_AFBC,
	EGL_PIXMAP_FORMAT_YUV420_8BIT_BT709_WIDE_AFBC,
	EGL_PIXMAP_FORMAT_YUV422_8BIT_BT601_NARROW_AFBC,
	EGL_PIXMAP_FORMAT_YUV422_8BIT_BT601_WIDE_AFBC,
	EGL_PIXMAP_FORMAT_YUV422_8BIT_BT709_NARROW_AFBC,
	EGL_PIXMAP_FORMAT_YUV422_8BIT_BT709_WIDE_AFBC,
	EGL_PIXMAP_FORMAT_YUV420_8BIT_BT601_NARROW_AFBC_SPLITBLK,
	EGL_PIXMAP_FORMAT_YUV420_8BIT_BT601_WIDE_AFBC_SPLITBLK,
	EGL_PIXMAP_FORMAT_YUV420_8BIT_BT709_NARROW_AFBC_SPLITBLK,
	EGL_PIXMAP_FORMAT_YUV420_8BIT_BT709_WIDE_AFBC_SPLITBLK,
	EGL_PIXMAP_FORMAT_YUV420_8BIT_BT601_NARROW_AFBC_WIDEBLK,
	EGL_PIXMAP_FORMAT_YUV420_8BIT_BT601_WIDE_AFBC_WIDEBLK,
	EGL_PIXMAP_FORMAT_YUV420_8BIT_BT709_NARROW_AFBC_WIDEBLK,
	EGL_PIXMAP_FORMAT_YUV420_8BIT_BT709_WIDE_AFBC_WIDEBLK,
	EGL_PIXMAP_FORMAT_YUV422_8BIT_BT601_NARROW_AFBC_WIDEBLK,
	EGL_PIXMAP_FORMAT_YUV422_8BIT_BT601_WIDE_AFBC_WIDEBLK,
	EGL_PIXMAP_FORMAT_YUV422_8BIT_BT709_NARROW_AFBC_WIDEBLK,
	EGL_PIXMAP_FORMAT_YUV422_8BIT_BT709_WIDE_AFBC_WIDEBLK,
	EGL_PIXMAP_FORMAT_Y0L2,
	EGL_PIXMAP_FORMAT_P010,
	EGL_PIXMAP_FORMAT_P210,
	EGL_PIXMAP_FORMAT_Y210,
	EGL_PIXMAP_FORMAT_Y410,
	EGL_PIXMAP_FORMAT_YUV420_10BIT_AFBC,
	EGL_PIXMAP_FORMAT_YUV422_10BIT_AFBC,
	EGL_PIXMAP_FORMAT_YUV420_10BIT_AFBC_WIDEBLK,
	EGL_PIXMAP_FORMAT_YUV422_10BIT_AFBC_WIDEBLK,
	EGL_PIXMAP_FORMAT_sABGR8888,
	EGL_PIXMAP_FORMAT_sARGB8888,
	EGL_PIXMAP_FORMAT_sXBGR8888,
	EGL_PIXMAP_FORMAT_BUTT

}fbdev_pixmap_format;

typedef struct egl_linux_pixmap
{
	int width, height;

	struct
	{
		/** @brief The line stride of each plane.
		 * For each plane required by the format, the number of bytes from one line of samples to the next. Other entries in
		 * the array should be 0.
		 */
		khronos_usize_t stride;
		/** @brief The byte size of each plane.
		 * For each plane required by the format, the number of bytes taken up by that plane. That includes any space wasted
		 * in partially-used blocks.
		 */
		khronos_usize_t size;
		/** @brief The offset from the memory handle to each plane.
		 * For each plane required by the format, the number of bytes from the start of the UMP region to the start of that
		 * plane. Other entries in the array should be 0.
		 */
		khronos_usize_t offset;
	}
	planes[3];

	/** An integer that specifies the format of the pixmap. Its meaning is known by tpi and winsys. */
	uint64_t pixmap_format;

	/** Three buffers that can be used by this pixmap. In case of RGB pixmap only the first one is going to be
	 * used. In case of YUV pixmap all three of them can be used for storing Y, U and V color coordinates separately.*/
	mem_handle handles[3];
} egl_linux_pixmap;

typedef struct dummy_display
{
	int width;
	int height;
	int bytes_per_pixel;
	int red_mask;
	int green_mask;
	int blue_mask;
	int alpha_mask;
	unsigned char *front_buffer;
} dummy_display;

/** Converts a pixmap ID to the corresponding pixmap structure.
 *
 * @param[in] id The pixmap ID to lookup
 *
 * @return A pointer to the pixmap structure or NULL on failure
 */
egl_linux_pixmap* egl_lookup_pixmap_ID_mapping(int32_t id);

/** Creates a pixmap ID from a pixmap structure.
 *
 * @param[in] pixmap
 *
 * @return The pixmap ID or -1 on failure
 */
int32_t egl_create_pixmap_ID_mapping(egl_linux_pixmap* pixmap);

/** Destroy a pixmap ID to pixmap structure mapping. The caller is responsible for
 *  destroying the pixmap structure.
 *
 * @param[in] id The pixmap ID for which the corresponding
 *               mapping should be destroyed
 *
 * @return EGL_TRUE on success or EGL_FALSE on failure
 */
unsigned int egl_destroy_pixmap_ID_mapping(int32_t id);

#endif /* _MALI_FBDEV_TYPES_H_ */
