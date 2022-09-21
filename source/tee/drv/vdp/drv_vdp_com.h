#ifndef __DRV_VDP_COM_H__
#define __DRV_VDP_COM_H__



/* Add cgms/mcvn data struct defination */

typedef enum hiDRV_DISPLAY_E
{
    HI_DRV_DISPLAY_0 = 0,
    HI_DRV_DISPLAY_1,
    HI_DRV_DISPLAY_2,
    HI_DRV_DISPLAY_BUTT
}HI_DRV_DISPLAY_E;

typedef enum hiDRV_DISP_FMT_E
{
    HI_DRV_DISP_FMT_1080P_60 = 0,         /**<1080p 60 Hz*/
    HI_DRV_DISP_FMT_1080P_50,         /**<1080p 50 Hz*/
    HI_DRV_DISP_FMT_1080P_30,         /**<1080p 30 Hz*/
    HI_DRV_DISP_FMT_1080P_25,         /**<1080p 25 Hz*/
    HI_DRV_DISP_FMT_1080P_24,         /**<1080p 24 Hz*/

    HI_DRV_DISP_FMT_1080i_60,         /**<1080i 60 Hz*/
    HI_DRV_DISP_FMT_1080i_50,         /**<1080i 60 Hz*/

    HI_DRV_DISP_FMT_720P_60,          /**<720p 60 Hz*/
    HI_DRV_DISP_FMT_720P_50,          /**<720p 50 Hz */

    HI_DRV_DISP_FMT_576P_50,          /**<576p 50 Hz*/
    HI_DRV_DISP_FMT_480P_60,          /**<480p 60 Hz*/

    HI_DRV_DISP_FMT_PAL,              /* B D G H I PAL */
    HI_DRV_DISP_FMT_PAL_B,            /* B PAL£¬ Australia */
    HI_DRV_DISP_FMT_PAL_B1,           /* B1 PAL, Hungary */
    HI_DRV_DISP_FMT_PAL_D,            /* D PAL, China */
    HI_DRV_DISP_FMT_PAL_D1,           /* D1 PAL£¬ Poland */
    HI_DRV_DISP_FMT_PAL_G,            /* G PAL£¬ Europe */
    HI_DRV_DISP_FMT_PAL_H,            /* H PAL£¬ Europe */
    HI_DRV_DISP_FMT_PAL_K,            /* K PAL£¬ Europe */
    HI_DRV_DISP_FMT_PAL_I,            /* I PAL£¬U.K. */
    HI_DRV_DISP_FMT_PAL_N,            /* N PAL, Jamaica/Uruguay */
    HI_DRV_DISP_FMT_PAL_Nc,           /* Nc PAL, Argentina:21 */

    HI_DRV_DISP_FMT_PAL_M,            /* M PAL, 525 lines */
    HI_DRV_DISP_FMT_PAL_60,           /* 60 PAL */
    HI_DRV_DISP_FMT_NTSC,             /* (M)NTSC       */
    HI_DRV_DISP_FMT_NTSC_J,           /* NTSC-J        */
    HI_DRV_DISP_FMT_NTSC_443,          /* (M)PAL        */

    HI_DRV_DISP_FMT_SECAM_SIN,      /**< SECAM_SIN*/
    HI_DRV_DISP_FMT_SECAM_COS,      /**< SECAM_COS*/
    HI_DRV_DISP_FMT_SECAM_L,        /**< France*/
    HI_DRV_DISP_FMT_SECAM_B,        /**< Middle East*/
    HI_DRV_DISP_FMT_SECAM_G,        /**< Middle East*/
    HI_DRV_DISP_FMT_SECAM_D,        /**< Eastern Europe*/
    HI_DRV_DISP_FMT_SECAM_K,        /**< Eastern Europe*/
    HI_DRV_DISP_FMT_SECAM_H,        /**< Line SECAM:34*/

    HI_DRV_DISP_FMT_1440x576i_50,
    HI_DRV_DISP_FMT_1440x480i_60, /*sequnce:36*/

    HI_DRV_DISP_FMT_1080P_24_FP,
    HI_DRV_DISP_FMT_720P_60_FP,
    HI_DRV_DISP_FMT_720P_50_FP,

    HI_DRV_DISP_FMT_861D_640X480_60,
    HI_DRV_DISP_FMT_VESA_800X600_60,
    HI_DRV_DISP_FMT_VESA_1024X768_60,
    HI_DRV_DISP_FMT_VESA_1280X720_60,
    HI_DRV_DISP_FMT_VESA_1280X800_60,
    HI_DRV_DISP_FMT_VESA_1280X1024_60,
    HI_DRV_DISP_FMT_VESA_1360X768_60,         //Rowe
    HI_DRV_DISP_FMT_VESA_1366X768_60,
    HI_DRV_DISP_FMT_VESA_1400X1050_60,        //Rowe
    HI_DRV_DISP_FMT_VESA_1440X900_60,
    HI_DRV_DISP_FMT_VESA_1440X900_60_RB,
    HI_DRV_DISP_FMT_VESA_1600X900_60_RB,
    HI_DRV_DISP_FMT_VESA_1600X1200_60,
    HI_DRV_DISP_FMT_VESA_1680X1050_60,       //Rowe
    HI_DRV_DISP_FMT_VESA_1680X1050_60_RB,       //Rowe
    HI_DRV_DISP_FMT_VESA_1920X1080_60,
    HI_DRV_DISP_FMT_VESA_1920X1200_60,
    HI_DRV_DISP_FMT_VESA_1920X1440_60,
    HI_DRV_DISP_FMT_VESA_2048X1152_60,
    HI_DRV_DISP_FMT_VESA_2560X1440_60_RB,
    HI_DRV_DISP_FMT_VESA_2560X1600_60_RB, /*sequence:60*/

    HI_DRV_DISP_FMT_3840X2160_24,/*reserve for extention*/
    HI_DRV_DISP_FMT_3840X2160_25,
    HI_DRV_DISP_FMT_3840X2160_30,
    HI_DRV_DISP_FMT_3840X2160_50,
    HI_DRV_DISP_FMT_3840X2160_60,

    HI_DRV_DISP_FMT_4096X2160_24,/*reserve for extention*/
    HI_DRV_DISP_FMT_4096X2160_25,
    HI_DRV_DISP_FMT_4096X2160_30,
    HI_DRV_DISP_FMT_4096X2160_50,
    HI_DRV_DISP_FMT_4096X2160_60,

    HI_DRV_DISP_FMT_3840X2160_23_976,
    HI_DRV_DISP_FMT_3840X2160_29_97,
    HI_DRV_DISP_FMT_720P_59_94,
    HI_DRV_DISP_FMT_1080P_59_94,
    HI_DRV_DISP_FMT_1080P_29_97,
    HI_DRV_DISP_FMT_1080P_23_976,
    HI_DRV_DISP_FMT_1080i_59_94,

    //ADD
    HI_DRV_DISP_FMT_CUSTOM,
    HI_DRV_DISP_FMT_BUTT
} HI_DRV_DISP_FMT_E;





#endif

