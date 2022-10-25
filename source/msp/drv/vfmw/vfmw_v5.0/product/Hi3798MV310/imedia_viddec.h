#ifndef __IMEDIA_VIDDEC_H__
#define __IMEDIA_VIDDEC_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif    /* __cpluscplus*/
#endif    /* __cpluscplus*/

#include "imedia_common.h"
#include "imedia_error.h"

#pragma pack(push, 1)
/*****************************************************************************************
 * ��Ƶ����ģ�鳣����������
 *****************************************************************************************/
#define MAX_DELAY_FRAME     6
#define MAX_DISPLAY_FRAME   MAX_DELAY_FRAME
#define MAX_META_DATA_COUNT 4

/*========================================================================================
* ��Ƶ����ģ��Debug��־
=======================================================================================*/
#define DEBUG_NOTHING     0x00
#define DEBUG_PIC_INFO    0x01
#define DEBUG_MB_INFO     0x02
#define DEBUG_DCT_COF     0x04
#define DEBUG_START_CODE  0x08
#define DEBUG_ERROR       0x10
#define DEBUG_REF_MANAGE  0x20
#define DEBUG_BUF_MANAGE  0x40

/*!��Ƶ����ģ��Ԫ���ݽ���״̬ */
typedef enum ENUM_IVIDDEC_META_DATA_STATUS
{
    META_DATA_NOT_FOUND = 0,      /**< ��δ�ҵ�Ԫ���� */
    META_DATA_FOUND,              /**< ���ҵ�Ԫ���� */
    META_DATA_FOUND_ONLY_SPS,     /**< ���ҵ�H264(SPS), MPEG4(VOS) */
    META_DATA_FOUND_ONLY_PPS,     /**< ���ҵ�H264(PPS), MPEG4(VOL) */
} ENUM_IVIDDEC_META_DATA_STATUS;

/*!��Ƶ����ģ�龲̬���� */
/**< ��ͨ��ProbeHeader�ӿڲ�ѯ���������ֵ�������ֵ���� */
typedef struct STRU_IVIDDEC_PARAMS
{
    UINT8 *pucBuf;

    UINT16 usMaxWidth;        /**< ���֧�ֵĿ�ȣ�Range[32-1920] */
    UINT16 usMaxHeight;       /**< ���֧�ֵĸ߶ȣ�Range[16-1088] */
    UINT16 usMaxRefFrame;     /**< ���ο�֡������Range[0-16]��һ������������ */
    UINT16 usMaxFrameBufNum;  /**< YUV����󻺴�֡����Range[3-32] */

    ENUM_IVIDEO_CODEC_PROFILE    eProfile;        /**< profile idc�������ֶΣ�һ��ûʵ�� */
    ENUM_IVIDEO_CODEC_LEVEL      eLevel;          /**< level idc�������ֶΣ�һ��ûʵ�� */
    ENUM_IVIDEO_COLOR_SPACE_TYPE eColorSpaceType; /**< ����ͼ��ĸ�ʽ (YUV420, YUV422, etc)��Ŀǰ����MPEG2֧��YUV422֮�⣬����codec��ֻ֧��YUV420 */

    /**< ���в�����Ҫ�ֶ����� */
    INT32  iFlags;             /**< �㷨ͨ�����ñ����ϣ�����ֵ��0�������imedia_common.h��ģ�鹫�����ñ��
                                    ��1���أ� IMEDIA_FLAG_DISABLE_ASM      ����Ż��رձ��
                                    ��2���أ� IMEDIA_FLAG_CALC_FPS         ͨ������ͳ��ʹ�ܱ��
                                    ��9���أ� IMEDIA_FLAG_DEBLOCK_FILTER   �����˲����(����)
                                    ��10���أ�IMEDIA_FLAG_ERROR_RESILIENCE �������ر��(����)
                                    �������ظ�ģ����ʱ��δʹ�� */

    BOOL   bForceOutYUV420Flag; /**< ��������������YUV420��YUV422����Ŀǰ������ֻ֧��YUV420[����ֵ��ֵΪ1] */

    /**< ��ǰͨ���ڴ����ʼ��ַ����С */
    INT32 iBufLength;

} STRU_IVIDDEC_PARAMS;

/*!��Ƶ����ģ������Ԫ���ݽṹ������ͷ��ͼ��ͷ�ȵȣ� */
typedef struct STRU_IVIDDEC_META_DATA
{
    UINT8 *apucMetaData[MAX_META_DATA_COUNT];    /**< Ԫ����ָ������ */
    UINT16 ausMetaDataLen[MAX_META_DATA_COUNT];  /**< Ԫ���ݳ��ȣ�Range[0-1024] */
    INT32 iNumMetaData;                          /**< Ԫ���ݸ�����Range[0-4] */
} STRU_IVIDDEC_META_DATA;

/*!��Ƶ����ģ������Ԫ���ݽ���������� */
typedef struct STRU_IVIDDEC_META_DATA_OUT_ARGS
{
    UINT32 uiBytesConsumed;                 /**< �ѽ����������ֽ��� */
    ENUM_IVIDDEC_META_DATA_STATUS eStatus;  /**< Ԫ���ݽ���״̬��Ӧ�ò��ʼ��ΪMETA_DATA_NOT_FOUND��֮�����probeheaderʱ�����ٽ����޸� */
    STRU_IVIDDEC_META_DATA stMetaData;      /**< Ԫ���ݵ�ַ������Ӧ�ò����ռ䱣����������process�ӿ�ʹ�� */
    STRU_IVIDEO_STREAM_INFO stStreamInfo;   /**< ����Ԫ���ݺ��ȡ����Ϣ */
} STRU_IVIDDEC_META_DATA_OUT_ARGS;

/*!��Ƶ����ģ��������� */
typedef struct STRU_IVIDDEC_IN_ARGS
{
    UINT8 *pucBuf;                         /**< ��������ʼ��ַ */

    UINT32 uiNumBytes;                     /**< �������ֽ���,���Ϊ64M�ֽ� */
    ENUM_BITSTREAM_STATUS eBitstreamStatus;/**< ����״̬�����Ա�ʶ������λ����Ϣ */
    INT64  iPTS;                           /**< ������Ӧ��ʱ��� */

    STRU_IVIDDEC_META_DATA *pstMetaData;   /**< ProbeHeader��ȡ����Ӧ�ò㱣��������Ԫ���ݵ�ַ */
} STRU_IVIDDEC_IN_ARGS;

/*!��Ƶ����ģ��������� */
typedef struct STRU_IVIDDEC_OUT_ARGS
{
    BOOL   bLastFrameFlag;             /**< �Ƿ�Ϊ���һ֡��� */
    INT32  iErrorCode;                 /**< �㷨�ڲ��Ĵ����� */
    UINT32 uiBytesConsumed;            /**< �ѽ����������ֽ��� ,��=0��*/
    UINT32 uiDisplayID;                /**< ��ʾ˳���ţ��ӵ�ǰ��Ƭ��ʼλ�ÿ�ʼ���㣬�����ڼ���ʱ�� */
    INT64  iPTS;                       /**< ��ǰ֡��Ӧ��ʱ��� */
    ENUM_IVIDEO_FRAME_TYPE eFrameType; /**< Դ�������е�ǰ֡�ı������� */
    STRU_IVIDEO_PICTURE stPicture;     /**< ���ͼ��������Ϣ��ģ���ڲ�����ռ䣬Ӧ�ò������ͷţ� */
} STRU_IVIDDEC_OUT_ARGS;

/*!��Ƶ����ģ���������� */
typedef struct STRU_IVIDDEC_STREAM
{
    UINT8 *pucBuf;              /**< ��������ʼ��ַ */
    UINT32 uiNumBytes;          /**< �������ֽ���,���Ϊ64M�ֽ� */
    INT64  iPTS;                /**< ������Ӧ��ʱ��� */

} STRU_IVIDDEC_STREAM;

/*!��Ƶ����ģ��֡����������� */
typedef struct STRU_IVIDDEC_FRAME_PARSE_OUT_ARGS
{
    INT32  iErrorCode;          /**< �㷨�ڲ��Ĵ����� */
    UINT32 uiBytesConsumed;     /**< �ѽ����������ֽ��� */
    STRU_IVIDDEC_STREAM stFrame;/**< ֡����������Ϣ */

} STRU_IVIDDEC_FRAME_PARSE_OUT_ARGS;


/*!����ͨ��״̬��Ϣ */
typedef struct STRU_IVIDDEC_STATUS
{
    ENUM_IVIDEO_CODEC_STATUS eCodecStatus; /**< �㷨ͨ��״̬ */
    INT32  iErrorCode;        /**< ������ */
    UINT32 uiTotalErrors;     /**< �ѷ��������쳣���ܴ��� */
    UINT32 uiDecIFrames;      /**< �ѽ����I֡���� */
    UINT32 uiDecPFrames;      /**< �ѽ����P֡���� */
    UINT32 uiDecBFrames;      /**< �ѽ����B֡���� */
    UINT32 uiDisplayedFrames; /**< ����ʾ֡������ */
    UINT32 uiInUsedBufNum;    /**< ��ʹ�õ�YUV BUF���� */
    UINT32 uiFreeBufNum;      /**< ���е�YUV BUF���� */
    UINT32 uiAvgFps;          /**< ƽ������FPS * 1000���ڿ������ܼ����Ǻ����Ч */
} STRU_IVIDDEC_STATUS;

/*!����ͨ�������ڴ���Ϣ */
typedef struct STRU_IVIDDEC_MEMORY_INFO
{
    UINT16  usWidth;                                /**< ����ռ����õ���ͼ��Ŀ��[32-1920] */
    UINT16  usHeight;                               /**< ����ռ����õ���ͼ��Ŀ��[16-1088] */
    UINT16  usBufNum;                               /**< ������ͼ����� */
    ENUM_IVIDEO_COLOR_SPACE_TYPE eColorFormat;        /**< ͼ���ɫ�ȿռ䣺422��420�� */
} STRU_IVIDDEC_MEMORY_INFO;

/*****************************************************************************************
 * ��Ƶ����ģ��ӿ�
 *****************************************************************************************/

/*****************************************************************************************
* ����˵�����������н���Ԫ�������ͣ�ͬһ�ļ�ֻ���ڿ�ʼ�����㷨ͨ��ǰ���ü��ɡ�
* ���������
*     eCodecType �㷨���ͣ������ENUM_IVIDEO_CODEC_TYPE����
*     pstInArgs  ���������Ϣ
* ���������
*     pstOutArgs ���������Ϣ
* �� �� ֵ��0-�ɹ�������ֵ������ֵ���塣
*****************************************************************************************/
EXPORT_API INT32 IMedia_Viddec_ProbeHeader(ENUM_IVIDEO_CODEC_TYPE eCodecType, STRU_IMEDIA_SINGLE_BUFFER *pstInArgs, STRU_IVIDDEC_META_DATA_OUT_ARGS *pstOutArgs);

/*****************************************************************************************
* ����˵����Ѱ�ʽ����㷨������ڴ��С��
* ���������
*     eCodecType �㷨���ͣ������ENUM_IVIDEO_CODEC_TYPE����
*     pstMemInfo     ͼ�������ȡ� ͼ�����߸߶ȡ����ͼ������Լ�ɫ�ȿռ����Ϣ
* ���������
*      piSize       ������������ܵ��ڴ��С
* �� �� ֵ��0-�ɹ�������ֵ������ֵ���塣
*****************************************************************************************/
EXPORT_API INT32 IMedia_Viddec_QueryMemSize(ENUM_IVIDEO_CODEC_TYPE eCodecType, STRU_IVIDDEC_MEMORY_INFO *pstMemInfo , INT32 *piSize);

/*****************************************************************************************
* ����˵���������㷨ͨ����
* ���������
*     eCodecType �㷨���ͣ������ENUM_IVIDEO_CODEC_TYPE����
*     params     ָ��洢ͼ���һЩ������Ϣ�Ľṹ�壨����ͼ��Ŀ�ߵȣ�
* ���������
*      pctx       �㷨ͨ�����ָ��
* �� �� ֵ��0-�ɹ�������ֵ������ֵ���塣
*****************************************************************************************/
EXPORT_API INT32 IMedia_Viddec_Create(ENUM_IVIDEO_CODEC_TYPE eCodecType, STRU_IVIDDEC_PARAMS *pstParams, IMEDIA_CODEC_CTX *pctx);

/*****************************************************************************************
* ����˵�����㷨ͨ�����ƺ�����
* ���������
*     ctx       �㷨ͨ�����
*     cmd:      ���Ʋ�����������
*         IMEDIA_GET_VERSION     ��ȡ�汾��Ϣ                  wparam(STRU_IMEDIA_VERSION*)         lparam(NULL)
*         IMEDIA_GET_STATUS      ��ȡ�㷨ͨ��״̬��Ϣ          wparam(STRU_IVIDDEC_STATUS*)         lparam(NULL)
*         IMEDIA_GET_STREAM_INFO ��ȡ�㷨ͨ����ǰ������Ϣ      wparam(STRU_IVIDEO_STREAM_INFO*)     lparam(NULL)
*         IMEDIA_GET_PARAMS      ��ȡ�㷨ͨ���Ĳ�����Ϣ        wparam(STRU_IVIDDEC_PARAMS*)         lparam(NULL)
*         IMEDIA_SET_DEBUG_FLAG  ���õ������ݱ��              wparam(int*)                         lparam(NULL)
*         IMEDIA_FLUSH           ����㷨ͨ����cache��Ϣ       wparam(NULL)                         lparam(NULL)
*         IMEDIA_RESET           ��λ�㷨ͨ��                  wparam(NULL)                         lparam(NULL)
*         IMEDIA_PICTURE_RELEASE �ͷŽ���ģ�������YUV֡����Ȩ wparam(STRU_IVIDEO_PICTURE*)         lparam(NULL)
*     wparam    ÿ�������Ӧ�������ͣ�����Ϊ��������
*     lparam    ÿ�������Ӧ�������ͣ�����Ϊ��������
* ���������
*     wparam    ÿ�������Ӧ�������ͣ�����Ϊ��������
*     lparam    ÿ�������Ӧ�������ͣ�����Ϊ��������
* �� �� ֵ��0-�ɹ�������ֵ������ֵ���塣
*****************************************************************************************/
EXPORT_API INT32 IMedia_Viddec_Control(IMEDIA_CODEC_CTX ctx, ENUM_IMEDIA_CMD cmd, void *wparam, void *lparam);


/*****************************************************************************************
* ����˵��������֡�����ӿڣ������������н�����һ֡���ݣ�ע�������֡�����п���������������ַ��Ҳ�п������ڲ������ַ����������������һ֡ʱ�ڲ���ƴ�ӣ���
*           �ýӿ��ں�˼ARM�������Ŀ�н��ṩ��Ӧ�ò�������
* ���������
*     ctx        �㷨ͨ�����
*     pstInArgs  ���������Ϣ�����������ĵ�ַ�����ȼ�ʱ����ȣ�
* ���������
*     pstOutArgs ���������Ϣ��֡����ĵ�ַ�ͳ��ȣ�
* �� �� ֵ��0-�ɹ�������ֵ������ֵ���塣
*****************************************************************************************/
EXPORT_API INT32 IMedia_Viddec_FrameParse(IMEDIA_CODEC_CTX ctx, STRU_IVIDDEC_STREAM *pstInArgs, STRU_IVIDDEC_FRAME_PARSE_OUT_ARGS *pstOutArgs);


/*****************************************************************************************
* ����˵��������֡����ӿڣ�ÿ��ֻ����һ֡���ӳ������֡���ظ����øýӿڣ�����������ַ��ֵΪNULL����ֱ�����������ָʾΪ���һ֡ʱ��
* ���������
*     ctx        �㷨ͨ�����
*     pstInArgs  ���������Ϣ����������֡�ĵ�ַ�����ȼ�ʱ����ȣ�
* ���������
*     pstOutArgs ���������Ϣ���������ͼ��������Ϣ��
* �� �� ֵ��0-�ɹ�������ֵ������ֵ���塣
*****************************************************************************************/
EXPORT_API INT32 IMedia_Viddec_FrameDecode(IMEDIA_CODEC_CTX ctx, STRU_IVIDDEC_STREAM *pstInArgs, STRU_IVIDDEC_OUT_ARGS *pstOutArgs);

/*****************************************************************************************
* ����˵������������ӿڣ�����֡������֡���빦�ܣ�ÿ�ε������ֻ���һ֡��ͨ����������ж��Ƿ�Ϊ���һ֡��
*           �ýӿ��ں�˼ARM�������Ŀ�н��ṩ��Ӧ�ò�������
* ���������
*     ctx        �㷨ͨ�����
*     pstInArgs  ���������Ϣ�����������ĵ�ַ�����ȼ�ʱ����ȣ�
* ���������
*     pstOutArgs ���������Ϣ���������ͼ��������Ϣ��
* �� �� ֵ��0-�ɹ�������ֵ������ֵ���塣
*****************************************************************************************/
EXPORT_API INT32 IMedia_Viddec_Process(IMEDIA_CODEC_CTX ctx, STRU_IVIDDEC_IN_ARGS *pstInArgs, STRU_IVIDDEC_OUT_ARGS *pstOutArgs);

/*****************************************************************************************
* ����˵����ɾ���㷨ͨ����
* ���������
*     ctx       �㷨ͨ�����
* �����������
* �� �� ֵ��0-�ɹ�������ֵ������ֵ���塣
*****************************************************************************************/
EXPORT_API INT32 IMedia_Viddec_Delete(IMEDIA_CODEC_CTX ctx);

#pragma pack(pop)

#ifdef __cplusplus
#if __cplusplus
}
#endif    /* __cpluscplus*/
#endif    /* __cpluscplus*/

#endif /**< __IMEDIA_VIDDEC_H__ */

/************************************************************************
* $Log$
************************************************************************/
