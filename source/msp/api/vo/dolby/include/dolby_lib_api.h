/******************************************************************************

  Copyright (C), 2001-2015, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : mpi_vo.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2015/10/13
  Description   :
  History       :
  1.Date        : 2015/10/13
    Author      : t00177539
    Modification: Created file

*******************************************************************************/
#include <rpu_ext_config.h>
#include <rpu_api_common.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "KdmTypeFxp_hisi.h"


/*-----------------------------------------------------------------------------+
 |                            golbal Test define
 +----------------------------------------------------------------------------*/
//#define METADATA_TEST_READ_BIN_WRITE_BIN
//#define METADATA_TEST_WRITWE_BIN

//#define DOLBY_REG_SELF_TEST
//#define DOLBY_REG_TEST_WRITE_BIN 



/*-----------------------------------------------------------------------------+
 |                            golbal API
 +----------------------------------------------------------------------------*/

typedef enum {
    false = 0,
    true = 1,
}bool;

#define R2020_R_X    35400
#define R2020_R_Y    14600
#define R2020_G_X     8500
#define R2020_G_Y    39850
#define R2020_B_X     6550
#define R2020_B_Y     2300
#define R2020_D65_X  15635
#define R2020_D65_Y  16450
#define SDR_DEFAULT_GAMMA      39322 /* 39322 = Gamma 2.4 */
#define SDR_DEFAULT_MIN_LUM     1310 /*     1310 = 0.005 nits*/
#define SDR_DEFAULT_MAX_LUM 26214400 /* 26214400 =   100 nits */
#define SDR_DEFAULT_MIN_LUM_BASE_10000      50 /*   0.005 nits*/
#define SDR_DEFAULT_MAX_LUM_BASE_10000 1000000 /*     100 nits */
#define HDR10_DEFAULT_MIN_LUM_BASE_10000       50 /*   0.005 nits*/
#define HDR10_DEFAULT_MAX_LUM_BASE_10000 40000000 /*    4000 nits */

typedef struct hiRPU_S
{
    unsigned char *p_rpu_addr;
    unsigned int  rpu_len;
}RPU_S;

typedef enum {
  chroma_420 = 0,
  chroma_422,
  chroma_444,
} chroma_format_t;

typedef enum {
  range_narrow = 0, // head
  range_full  = 1, // will be the in data type(bits) range
  range_sdi = 2, // pq
} range_t;

typedef enum priority_mode_e
{
    VIDEO_PRIORITY = 0,
    GRAPHIC_PRIORITY = 1
} priority_mode_t;

typedef struct hdr10_param_s
{
    uint32_t min_display_mastering_luminance; /**< @brief */
    uint32_t max_display_mastering_luminance; /**< @brief */
    uint16_t Rx;                              /**< @brief */
    uint16_t Ry;                              /**< @brief */
    uint16_t Gx;                              /**< @brief */
    uint16_t Gy;                              /**< @brief */
    uint16_t Bx;                              /**< @brief */
    uint16_t By;                              /**< @brief */
    uint16_t Wx;                              /**< @brief */
    uint16_t Wy;                              /**< @brief */
    uint16_t max_content_light_level;         /**< @brief */
    uint16_t max_pic_average_light_level;     /**< @brief */
} hdr10_param_t;

/*! @brief HDR10 infoframe data structure.
           This is the data structure used for the HDR10 infoframe.
           Details for each entry can be found in CEA-861.3
*/
typedef struct hdr_10_infoframe_s
{
    uint8_t infoframe_type_code      ;
    uint8_t infoframe_version_number ;
    uint8_t length_of_info_frame     ;
    uint8_t data_byte_1              ;
    uint8_t data_byte_2              ;
    uint8_t display_primaries_x_0_LSB;
    uint8_t display_primaries_x_0_MSB;
    uint8_t display_primaries_y_0_LSB;
    uint8_t display_primaries_y_0_MSB;
    uint8_t display_primaries_x_1_LSB;
    uint8_t display_primaries_x_1_MSB;
    uint8_t display_primaries_y_1_LSB;
    uint8_t display_primaries_y_1_MSB;
    uint8_t display_primaries_x_2_LSB;
    uint8_t display_primaries_x_2_MSB;
    uint8_t display_primaries_y_2_LSB;
    uint8_t display_primaries_y_2_MSB;
    uint8_t white_point_x_LSB        ;
    uint8_t white_point_x_MSB        ;
    uint8_t white_point_y_LSB        ;
    uint8_t white_point_y_MSB        ;
    uint8_t max_display_mastering_luminance_LSB;
    uint8_t max_display_mastering_luminance_MSB;
    uint8_t min_display_mastering_luminance_LSB;
    uint8_t min_display_mastering_luminance_MSB;
    uint8_t max_content_light_level_LSB        ;
    uint8_t max_content_light_level_MSB        ;
    uint8_t max_frame_average_light_level_LSB  ;
    uint8_t max_frame_average_light_level_MSB  ;
} hdr_10_infoframe_t;

typedef struct edid_info_s
{
    int edid_min;
    int edid_max;
}edid_info_t;

typedef enum {
    display_out_sdr_normal,
    display_out_sdr_authentication,
    display_out_hdr10,
    display_out_dolby_ipt,
    display_out_dolby_yuv,
}display_out_type_t;

typedef struct target_info_s{
    uint32_t w,h;
    int16_t Contrast, Brightness;
    display_out_type_t tgt_type;
}target_info_t;

typedef enum {
    src_video_sdr,
    src_video_hdr10,
    src_video_dolby_yuv,
    src_video_dolby_ipt,
}src_video_type_t;

typedef struct src_videoinfo_s{
    uint32_t w,h;
    uint32_t bits;
    RPU_S   stRpu;
    chroma_format_t  chroma_format;
    range_t   range_type;
    int dovi_src_min;    /*dovi_src_min   Minimum source display luminance from DoVi metadata, in 12-bit PQ encoding*/
    int dovi_src_max;  /*dovi_src_max  Maximum source display luminance from DoVi metadata, in 12-bit PQ encoding*/
    src_video_type_t video_type;
    hdr10_param_t   hdr10_param;
}src_videoinfo_t;

typedef struct src_grcinfo_s{
    uint32_t w,h;
    int graphics_on;
    int graphic_min;
    int graphic_max;
}src_grcinfo_t;

typedef struct dolby_vision_info_s{
	char *pbuild_time;
    char *pversion;
    char *puser_name;
    uint32_t user_id[4];
}dolby_vision_info_t;

/*-----------------------------------------------------------------------------+
 |                            abstract structures for mpi
 +----------------------------------------------------------------------------*/
typedef struct hiMETADATA_OVER_HDMI_S
{
    dm_metadata_t  *p_buf_addr;
    unsigned int   update_len;
}METADATA_OVER_HDMI_S;

typedef struct hiDOLBY_CONFIG_S
{
    rpu_ext_config_fixpt_main_t *p_composer;
    dm_metadata_t               *p_dm_metadata;
    DmKsFxp_t                   *p_dm_ks_reg;
    hdr_10_infoframe_t          *p_hdr10_info_frame;
    METADATA_OVER_HDMI_S         stHdmi_metadata;
}DOLBY_CONFIG_S;



/*-----------------------------------------------------------------------------+
 |                            Metadata Parser API
 +----------------------------------------------------------------------------*/
#define METADATA_NULL_ADDR              0x80000001
#define METADATA_MALLOC_FAILURE         0x80000002
#define METADATA_OPENFILE_FAILURE       0x80000003
#define METADATA_INIT_FAILURE           0x80000004
#define METADATA_PARSE_FAILURE          0x80000005
extern int metadata_parser_init(void);
extern int metadata_parser_deinit(void);
extern int metadata_parser_process(char *p_rpu_buf,
                                             uint32_t rpu_len,
        rpu_ext_config_fixpt_main_t *p_composer_data,
                                             dm_metadata_t *p_dm_data,
                                             char *p_md_bin);

int set_medata_debug_dir(char *p_input_rpu_name, char *p_out_dir);

/*-----------------------------------------------------------------------------+
 |                            Metadata update over hdmi API
 +----------------------------------------------------------------------------*/
extern void bypass_metadata_update (dm_metadata_t         *p_dm_md,
                                              dm_metadata_t         *p_dm_md_hdmi,
                                              signal_color_space_e  output_color_space,
                                              signal_range_e        output_signal_range,
                                              priority_mode_t       priority_mode,
                                              int                   edid_min,
                                              int                   edid_max,
                                              int                   f_graphic_on,
                                              uint32_t             *p_length);

extern void get_dolby_output_metadata(dm_metadata_t  *p_dm_md,
                                                uint32_t *p_length);

/*! @brief Get the HDR10 infor frame
 *  @param[in]  input_format         Input format
 *  @param[in]  *p_hdr10_param       For HDR10 input these parameters need to be provided, otherwise this parameter shall be NULL.
 *  @param[in]  *p_dm_md             Source DM Metadata
                                     Only needed in case case of DoVi input. NULL otherwise
 *  @param[out] *p_info_frame        HDR10 info frame
 *  @return
 *      @li 0       success
 *      @li <0      error
 */
extern int get_hdr10_info_frame(src_video_type_t input_format,
                                        hdr10_param_t* p_hdr10_param,
                                        dm_metadata_t *p_dm_md,
                                        hdr_10_infoframe_t* p_info_frame);
/*-----------------------------------------------------------------------------+
 |                            Dolby register  API
 +----------------------------------------------------------------------------*/
extern int reg_init(void);
extern int reg_deinit(void);

/*! @brief Commits the
 *  @param[in]  *p_src_dm_metadata   Source DM Metadata
 *  @param[in]  *p_src_comp_metadata Source Composer Metadata
 *  @param[in]  video_info           VideoFrame info
 *  @param[out] *p_dst_comp_reg      Generic Register Mapping for Composer.
 *  @param[out] *p_dst_dm_reg        Generic Register Mapping for DM.
 *  @return
 *      @li 0       success
 *      @li <0      error
 */
extern int commit_reg(dm_metadata_t *p_src_dm_metadata,
                    DmKsFxp_t *p_dst_dm_reg,
                    src_videoinfo_t *p_video_info,
                    display_out_type_t output_format,
                    priority_mode_t priority_mode,
                    bool f_graphics_on);

/* w,h must equal with video_info.w&h */
extern int set_display_config(target_info_t tgt_info);

extern int set_reg_debug_dir(char *p_dm_in_file, char *p_out_dir);

extern int set_grc_config(src_grcinfo_t grc_info);

extern int get_dolby_vision_info(dolby_vision_info_t *pdolby_vision_info);


typedef int (* FN_DOLBY_metadata_parser_init)(void);

typedef int (* FN_DOLBY_metadata_parser_deinit)(void);

typedef int (* FN_DOLBY_metadata_parser_process)(char *p_rpu_buf, uint32_t rpu_len,
                                    rpu_ext_config_fixpt_main_t *p_composer_data,
                                    dm_metadata_t *p_dm_data, char *p_md_bin);

typedef void (* FN_DOLBY_bypass_metadata_update)(dm_metadata_t         *p_dm_md,
                                                  dm_metadata_t         *p_dm_md_hdmi,
                                                  signal_color_space_e  output_color_space,
                                                  signal_range_e        output_signal_range,
                                                  priority_mode_t       priority_mode,
                                                  int                   edid_min,
                                                  int                   edid_max,
                                                  int                   f_graphic_on,
                                                  uint32_t             *p_length);

typedef void (*FN_DOLBY_get_dolby_output_metadata)(dm_metadata_t  *p_dm_md,
                                                            uint32_t *p_length);

typedef int (*FN_DOLBY_get_hdr10_info_frame)(src_video_type_t input_format,
                                                     hdr10_param_t* p_hdr10_param,
                                                     dm_metadata_t *p_dm_md,
                                                     hdr_10_infoframe_t* p_info_frame);

typedef int (* FN_DOLBY_reg_init)(void);
typedef int (* FN_DOLBY_reg_deinit)(void);


/*
typedef int (* FN_DOLBY_commit_reg)(dm_metadata_t *p_src_dm_metadata,
                                    DmKsFxp_t *p_dst_dm_reg,
                                    src_videoinfo_t video_info);
*/

typedef int (* FN_DOLBY_commit_reg)(dm_metadata_t *p_src_dm_metadata,
                                         DmKsFxp_t *p_dst_dm_reg,
                                         src_videoinfo_t *p_video_info,
                                         display_out_type_t output_format,
                                         priority_mode_t priority_mode,
                                         bool f_graphics_on);


typedef int (* FN_DOLBY_set_display_config)(target_info_t tgt_info);
typedef int (* FN_DOLBY_set_grc_config)(src_grcinfo_t grc_info);
typedef int (* FN_DOLBY_get_dolby_vision_info)(dolby_vision_info_t *pdolby_vision_info);

typedef struct
{
    FN_DOLBY_metadata_parser_init      pfnMetadata_parser_init;
    FN_DOLBY_metadata_parser_deinit    pfnMetadata_parser_deinit;
    FN_DOLBY_metadata_parser_process   pfnMetadata_parser_process;

    FN_DOLBY_bypass_metadata_update    pfnBypass_metadata_update;

    FN_DOLBY_reg_init                  pfnReg_init;
    FN_DOLBY_reg_deinit                pfnReg_deinit;
    FN_DOLBY_commit_reg                pfnCommit_reg;
    FN_DOLBY_set_display_config        pfnSet_display_config;
    FN_DOLBY_set_grc_config            pfnSet_grc_config;
	FN_DOLBY_get_dolby_vision_info     pfnget_dolby_vision_info;

	FN_DOLBY_get_dolby_output_metadata pfnGet_dolby_output_metadata;
	FN_DOLBY_get_hdr10_info_frame      pfnGet_hdr10_info_frame;
}DOLBY_FUNC_ENTRY_S;




