#ifndef __IMEDIA_ERROR_H__
#define __IMEDIA_ERROR_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif    /* __cpluscplus*/
#endif    /* __cpluscplus*/

/** ģ�鷵��ֵö�����Ͷ��� */
typedef enum ENUM_IMEDIA_RETURN
{
    IMEDIA_RET_SUCCESS = 0,             /**< �������� */

    /** ���������ⷵ�� */
    IMEDIA_RET_PARAM_NULL = 0x0100,     /**< ����ָ��Ϊ�� */
    IMEDIA_RET_PARAM_INVALID,           /**< ������Ч */
    IMEDIA_RET_PARAM_IN_VALUE_NULL,     /**< �������ֵָ��Ϊ�� */
    IMEDIA_RET_PARAM_IN_VALUE_INVALID,  /**< �������ֵ��Ч */
    IMEDIA_RET_PARAM_OUT_VALUE_NULL,    /**< �������ֵָ��Ϊ�� */
    IMEDIA_RET_PARAM_OUT_VALUE_INVALID, /**< �������ֵ��Ч */
    IMEDIA_RET_PARAM_NOT_ENOUGH,        /**< �������� */

    IMEDIA_RET_PARAM_OTHER = 0x01FF,    /**< �������������� */

    /** ���������ⷵ�� */
    IMEDIA_RET_OBJ_NULL = 0x0200,       /**< ����ָ��Ϊ�� */
    IMEDIA_RET_OBJ_BAD_MASK,            /**< ���������ٻ� */
    IMEDIA_RET_OBJ_INVALID,             /**< ��Ч���� */
    IMEDIA_RET_OBJ_NOT_FOUND,           /**< ����û�ҵ� */
    IMEDIA_RET_OBJ_CREATE_FAIL,         /**< ���󴴽�ʧ�� */
    IMEDIA_RET_OBJ_NOT_INIT,            /**< ����δ��ʼ�� */
    IMEDIA_RET_OBJ_DELETE_FAIL,         /**< ����ɾ��ʧ�� */

    IMEDIA_RET_OBJ_OTHER = 0x02FF,      /**< �������������� */

    /** ���棨�����������ⷵ�� */
    IMEDIA_RET_MEM_MALLOC_FAIL = 0x0400,/**< �ڴ����ʧ�� */
    IMEDIA_RET_MEM_FREE_FAIL,           /**< �ڴ��ͷ�ʧ�� */
    IMEDIA_RET_BUF_NULL,                /**< ����ָ��Ϊ�� */
    IMEDIA_RET_BUF_BAD_MASK,            /**< ���������ٻ� */
    IMEDIA_RET_BUF_INVALID,             /**< ������Ч���޷�ʶ���ʽ */
    IMEDIA_RET_BUF_OVER_FLOW,           /**< ������� */
    IMEDIA_RET_BUF_ADDR_NOT_ALIGN,      /**< �����ַδ���� */
    IMEDIA_RET_BUF_SIZE_NOT_ALIGN,      /**< �����Сδ���� */
    IMEDIA_RET_BUF_SIZE_NOT_ENOUGH,     /**< �����С���� */

    IMEDIA_RET_BUF_OTHER = 0x04FF,      /**< �������������� */

    /** �ļ����������ⷵ�� */
    IMEDIA_RET_FILE_OPEN_FAIL = 0x0800, /**< ���ļ�ʧ�� */
    IMEDIA_RET_FILE_READ_FAIL,          /**< �ļ���ȡʧ�� */
    IMEDIA_RET_FILE_WRITE_FAIL,         /**< �ļ�д��ʧ�� */
    IMEDIA_RET_FILE_CLOSE_FAIL,         /**< �ر��ļ�ʧ�� */

    IMEDIA_RET_FILE_OTHER = 0x08FF,     /**< �ļ��������������� */

    /** �������������ⷵ�� */
    IMEDIA_RET_CMD_INVALID = 0x1000,

    /** ���ⷵ�� */
    IMEDIA_RET_DECODE_INTERRUPT = 0x2000,

    /** ������� ���ز�֧�� */
    IMEDIA_RET_DECODE_NOT_SUPPORT = 0x3000,

    IMEDIA_RET_ENCODE_INTERRUPT,

    /** �������ⷵ�� */
    IMEDIA_RET_OTHER = 0x8000,
} ENUM_IMEDIA_RETURN;

/** �㷨�����ö�����Ͷ��� */
/**
typedef struct STRU_IMEDIA_ERROR_CODE
{
    unsigned char CodecID;
    unsigned char SEQHeader : 4;
    unsigned char PicHeader : 4;
    unsigned char SliceHeader : 4;
    unsigned char MBHeader : 4;
    unsigned char Residual : 4;
    unsigned char Reserved : 4;
} STRU_IMEDIA_ERROR_CODE;*/

#define IMEDIA_ERROR_MASK_CODEC_ID 0xFF000000
#define IMEDIA_ERROR_MASK_SEQ      0x00F00000
#define IMEDIA_ERROR_MASK_PIC      0x000F0000
#define IMEDIA_ERROR_MASK_SLICE    0x0000F000
#define IMEDIA_ERROR_MASK_MB       0x00000F00
#define IMEDIA_ERROR_MASK_RESIDUAL 0x000000F0
#define IMEDIA_ERROR_MASK_RESERVED 0x0000000F

#define IMEDIA_ERROR_BITS_CODEC_ID 24
#define IMEDIA_ERROR_BITS_SEQ      20
#define IMEDIA_ERROR_BITS_PIC      16
#define IMEDIA_ERROR_BITS_SLICE    12
#define IMEDIA_ERROR_BITS_MB       8
#define IMEDIA_ERROR_BITS_RESIDUAL 4
#define IMEDIA_ERROR_BITS_RESERVED 0

#define IMEDIA_SET_ERR_CODEC_ID(c, e) ((c) |= ((e)<<IMEDIA_ERROR_BITS_CODEC_ID))
#define IMEDIA_SET_ERR_SEQ(c, e)      ((c) |= ((e)<<IMEDIA_ERROR_BITS_SEQ))
#define IMEDIA_SET_ERR_PIC(c, e)      ((c) |= ((e)<<IMEDIA_ERROR_BITS_PIC))
#define IMEDIA_SET_ERR_SLICE(c, e)    ((c) |= ((e)<<IMEDIA_ERROR_BITS_SLICE))
#define IMEDIA_SET_ERR_MB(c, e)       ((c) |= ((e)<<IMEDIA_ERROR_BITS_MB))
#define IMEDIA_SET_ERR_RESIDUAL(c, e) ((c) |= ((e)<<IMEDIA_ERROR_BITS_RESIDUAL))

#define IMEDIA_GET_ERR_CODEC_ID(e)    (((e) & IMEDIA_ERROR_MASK_CODEC_ID) >> IMEDIA_ERROR_BITS_CODEC_ID)
#define IMEDIA_GET_ERR_SEQ(e)         (((e) & IMEDIA_ERROR_MASK_SEQ) >> IMEDIA_ERROR_BITS_SEQ)
#define IMEDIA_GET_ERR_PIC(e)         (((e) & IMEDIA_ERROR_MASK_PIC) >> IMEDIA_ERROR_BITS_PIC)
#define IMEDIA_GET_ERR_SLICE(e)       (((e) & IMEDIA_ERROR_MASK_SLICE) >> IMEDIA_ERROR_BITS_SLICE)
#define IMEDIA_GET_ERR_MB(e)          (((e) & IMEDIA_ERROR_MASK_MB) >> IMEDIA_ERROR_BITS_MB)
#define IMEDIA_GET_ERR_RESIDUAL(e)    (((e) & IMEDIA_ERROR_MASK_RESIDUAL) >> IMEDIA_ERROR_BITS_RESIDUAL)
#define IMEDIA_GET_ERR_RESERVED(e)     ((e) & IMEDIA_ERROR_MASK_RESERVED)

/**����ͷ�����ö������*/
typedef enum ENUM_IMEDIA_ERROR_SEQ
{
    IMEDIA_ERR_SEQ_NO_ERROR = 0,
    IMEDIA_ERR_SEQ_PROFILE_LEVEL,          /**< �޴��� */
    IMEDIA_ERR_SEQ_BIT_DEPTH,              /**< luma/chroma bit_depth����� */
    IMEDIA_ERR_SEQ_FRAME_NUM,              /**< ͼ��֡������������֡�����ο�֡���� */
    IMEDIA_ERR_SEQ_SIZE,                   /**< ͼ��ߴ������ */
    IMEDIA_ERR_SEQ_TIME_FRAMERATE,         /**< ͼ��ʱ�����֡������� */
    IMEDIA_ERR_SEQ_COLOR_SPACE,            /**< ɫ�ȿռ���� */
    IMEDIA_ERR_SEQ_ID,                     /**< ������id����� */
    IMEDIA_ERR_SEQ_QUANT,                  /**< ��������������������� */
    IMEDIA_ERR_SEQ_MARKER,                 /**< ���ܿ��أ�������λ����� */
    IMEDIA_ERR_SEQ_SHAPE,                  /**< ͼ����״����� */

    IMEDIA_ERR_SEQ_OTHER = 0x0F,           /**< �������� */
} ENUM_IMEDIA_ERROR_SEQ;

/**֡ͷ�����ö������*/
typedef enum ENUM_IMEDIA_ERROR_PIC
{
    IMEDIA_ERR_PIC_NO_ERROR = 0,           /**< �޴��� */
    IMEDIA_ERR_PIC_ID,                     /**< ͼ��id����� */
    IMEDIA_ERR_PIC_SLICE_GROUP_COUNT,      /**< pps ��ָ��slice group�������Ϸ� */
    IMEDIA_ERR_PIC_REF,                    /**< �ο�֡����� */
    IMEDIA_ERR_PIC_FRAME_TYPE,             /**< ͼ����������� */
    IMEDIA_ERR_PIC_MARKER,                 /**< ͼ������ر�־λ����� */
    IMEDIA_ERR_PIC_QP,                     /**< ͼ��QP����� */
    IMEDIA_ERR_PIC_FCODE,                  /**< ͼ��F_CODE����� */

    IMEDIA_ERR_PIC_OTHER = 0x0F,           /**< �������� */
} ENUM_IMEDIA_ERROR_PIC;

/**sliceͷ�����ö������*/
typedef enum ENUM_IMEDIA_ERROR_SLICE
{
    IMEDIA_ERR_SLICE_NO_ERROR = 0,
    IMEDIA_ERR_SLICE_TYPE,                /**< slice type�Ƿ�Ϸ� */
    IMEDIA_ERR_SLICE_ID,                  /**< slice id����� */
    IMEDIA_ERR_SLICE_ADDR,                /**< slice��ַ����� */
    IMEDIA_ERR_SLICE_REF,                 /**< slice�вο�֡������ */
    IMEDIA_ERR_SLICE_VLC,                 /**< slice�ر��������� */
    IMEDIA_ERR_SLICE_WEIGHTED,            /**< ��Ȩ��ز�������� */
    IMEDIA_ERR_SLICE_QP,                  /**< slice qp����� */
    IMEDIA_ERR_SLICE_DEBLOCKING,          /**< deblocking����� */
    IMEDIA_ERR_SLICE_NUM,                 /**< slice��slice��mb��Ŀ����� */
    IMEDIA_ERR_SLICE_BITS,                /**< slice�����ķѱ��������� */
    IMEDIA_ERR_SLICE_MARKER,              /**< �������� */

    IMEDIA_ERR_SLICE_OTHER = 0x0F,        /**< �������� */
} ENUM_IMEDIA_ERROR_SLICE;

/**���ͷ�����ö������*/
typedef enum ENUM_IMEDIA_ERROR_MB
{
    IMEDIA_ERR_MB_NO_ERROR = 0,
    IMEDIA_ERR_MB_SKIP_MB_RUN,         /**< skip_mb_run���Ϸ� */
    IMEDIA_ERR_MB_TYPE,                /**< mb type����� */
    IMEDIA_ERR_MB_MODE,                /**< Ԥ��ģʽ����� */
    IMEDIA_ERR_MB_REF,                 /**< �ο�֡����� */
    IMEDIA_ERR_MB_CBP,                 /**< cbp����� */
    IMEDIA_ERR_MB_QP,                  /**< qp����� */
    IMEDIA_ERR_MB_MV,                  /**< mv����� */
    IMEDIA_ERR_MB_MARKER,              /**< �������� */

    IMEDIA_ERR_MB_OTHER = 0x0F,        /**< ������������� */
} ENUM_IMEDIA_ERROR_MB;

/**�в����ݴ����ö������*/
typedef enum ENUM_IMEDIA_ERROR_RESIDUAL
{
    IMEDIA_ERR_RESIDUAL_NO_ERROR = 0,
    IMEDIA_ERR_RESIDUAL_DC,            /**< DC���� */
    IMEDIA_ERR_RESIDUAL_AC,            /**< AC���� */
    IMEDIA_ERR_RESIDUAL_TOTAL_COEFF,   /**< cavlc������total coeff�������� */
    IMEDIA_ERR_RESIDUAL_ZERO_LEFT,     /**< cavlc������zero left�������� */
    IMEDIA_ERR_RESIDUAL_LEVEL,         /**< �ؽ�����level����� */

    IMEDIA_ERR_RESIDUAL_OTHER = 0x0F,  /**< �������� */
} ENUM_IMEDIA_ERROR_RESIDUAL;

#ifdef __cplusplus
#if __cplusplus
}
#endif    /* __cpluscplus*/
#endif    /* __cpluscplus*/

#endif /**< __IMEDIA_ERROR_H__ */

/************************************************************************
* $Log$
************************************************************************/

