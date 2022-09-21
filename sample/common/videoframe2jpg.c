#include <cutils/log.h>
#define printf ALOGE
#include <string.h>

#include "hi_type.h"
#include "hi_jpge_api.h"
#include "hi_jpge_type.h"
#include "hi_jpge_errcode.h"
#include "hi_common.h"
#include "hi_unf_video.h"



///////////////////////////////////////////////////////////////////////////////
/* save RGBA to bmp file
 */
typedef struct BMP
{
    uint8_t   BM[2];
    uint32_t  fsize;
    uint16_t  resv0;
    uint16_t  resv1;
    uint32_t  offset;
    uint32_t  resv2;
    uint32_t  w;
    uint32_t  h;
    uint16_t  resv3;
    uint16_t  resv4;
    uint32_t  resv5;
    uint32_t  datasize;
    uint32_t  resv6;
    uint32_t  resv7;
    uint32_t  resv8;
    uint32_t  resv9;
}BMP_header;

static void RGBA2bmp(const char *filename, HI_CHAR* buffer, HI_U32 w, HI_U32 h, int bits)
{
    printf("[%4zu]  IN  %s",__LINE__,__FUNCTION__);
    int x,y,v;
    FILE *f;
    char fname[256];
    snprintf(fname, sizeof(fname), "%s.bmp", filename);
    BMP_header bmp;

    bmp.BM[0]   = 'B';
    bmp.BM[1]   = 'M';
    bmp.fsize= w*h*4+54;
    bmp.resv0= 0;
    bmp.resv1= 0;
    bmp.offset= 54;
    bmp.resv2= 0x28;
    bmp.w    = w;
    bmp.h    = h;
    bmp.resv3= 0x01;
    bmp.resv4= bits;//8,16,32
    bmp.resv5= 0x00;
    bmp.datasize= w*h;
    bmp.resv6= 0;
    bmp.resv7= 0;
    bmp.resv8= 0;
    bmp.resv9= 0;

    f = fopen(fname, "wb");
    if (!f) {
        perror(fname);
        return;
    }
    fwrite(&bmp.BM,2,1,f);
    fwrite(&bmp.fsize,4,1,f);
    fwrite(&bmp.resv0,2,1,f);
    fwrite(&bmp.resv1,2,1,f);
    fwrite(&bmp.offset,4,1,f);
    fwrite(&bmp.resv2,4,1,f);
    fwrite(&bmp.w    ,4,1,f);
    fwrite(&bmp.h    ,4,1,f);
    fwrite(&bmp.resv3,2,1,f);
    fwrite(&bmp.resv4,2,1,f);
    fwrite(&bmp.resv5,4,1,f);
    fwrite(&bmp.datasize,4,1,f);
    fwrite(&bmp.resv6,4,1,f);
    fwrite(&bmp.resv7,4,1,f);
    fwrite(&bmp.resv8,4,1,f);
    fwrite(&bmp.resv9,4,1,f);

    for(x=h-1;x>=0;x--)
        fwrite((uint8_t*)((uint8_t*)(buffer)+x*w*4), w*4,1, f);
    fclose(f);

    printf("[%4zu]  IN  %s",__LINE__,__FUNCTION__);
}



///////////////////////////////////////////////////////////////////////////////
#define JPGE_COMPONENT_NUM             3
#define JPGE_INPUT_FMT_YUV420          0
#define JPGE_INPUT_SAMPLE_SEMIPLANNAR  0

typedef struct tagJPGE_INPUT_S
{
    HI_U32  u32YuvSampleType;
    HI_U32  u32YuvFmtType;
    HI_U32  u32Qlevel;

    HI_U32  u32Width[JPGE_COMPONENT_NUM];
    HI_U32  u32Height[JPGE_COMPONENT_NUM];
    HI_U32  u32Stride[JPGE_COMPONENT_NUM];
    HI_U32  u32Size[JPGE_COMPONENT_NUM];
    HI_U32  u32PhyBuf[JPGE_COMPONENT_NUM];
    HI_CHAR *pVirBuf[JPGE_COMPONENT_NUM];

    HI_U32  u32OutSize;
    HI_U32  u32OutPhyBuf;
    HI_CHAR *pOutVirBuf;

}JPGE_INPUT_S;

/* Save JPEG_Struct to jpg file
 * input : JPEG_Struct, file full patch tobe saved
 * output: HI_FAILURE/HI_SUCCESS
 */
 static HI_S32 JPEG_EncToFile(HI_CHAR *pEncFileName,JPGE_INPUT_S *pstInputInfo)
{
    FILE* pOutFile     = NULL;
    HI_S32 s32Ret      = HI_SUCCESS;
    HI_U32 u32NeedSize = 0;
    Jpge_EncCfg_S EncCfg;
    Jpge_EncIn_S  EncIn;
    Jpge_EncOut_S EncOut;
    HI_U32 u32EncHandle = 0;

    s32Ret = HI_JPGE_Open();
    if(HI_SUCCESS != s32Ret){
        printf("\nHI_JPGE_Open FAILURE\n");
        return HI_FAILURE;
    }

    //Set encoder config
    EncCfg.FrameWidth    = pstInputInfo->u32Width[0];
    EncCfg.FrameHeight   = pstInputInfo->u32Height[0];
    EncCfg.YuvSampleType = pstInputInfo->u32YuvFmtType;
    EncCfg.YuvStoreType  = pstInputInfo->u32YuvSampleType;
    EncCfg.Qlevel        = pstInputInfo->u32Qlevel;
    EncCfg.RotationAngle = 0;
    EncCfg.SlcSplitEn    = 0;
    EncCfg.SplitSize     = 0;

    s32Ret = HI_JPGE_Create(&u32EncHandle,&EncCfg);
    if( HI_SUCCESS != s32Ret ){
        printf("\nHI_JPGE_Create FAILURE, s32Ret=0x%x\n", s32Ret);
        goto ERROR1;
    }

    //Set encoder INput info
    memset(&EncIn,0,sizeof(Jpge_EncIn_S));

    EncIn.BusViY     = pstInputInfo->u32PhyBuf[0];
    EncIn.BusViC     = pstInputInfo->u32PhyBuf[1];
    EncIn.BusViV     = pstInputInfo->u32PhyBuf[2];
    EncIn.ViYStride  = pstInputInfo->u32Stride[0];
    EncIn.ViCStride  = pstInputInfo->u32Stride[1];

    EncIn.BusOutBuf  = pstInputInfo->u32OutPhyBuf;
    EncIn.pOutBuf    = (HI_U8*)pstInputInfo->pOutVirBuf;
    EncIn.OutBufSize = pstInputInfo->u32OutSize;

    memset(&EncOut,0,sizeof(Jpge_EncOut_S));

    //hint the input info
    printf("\n=======================================================\n");
    printf("EncCfg.FrameWidth          = %d\n",EncCfg.FrameWidth);
    printf("EncCfg.FrameHeight         = %d\n",EncCfg.FrameHeight);
    printf("EncCfg.YuvSampleType       = %d\n",EncCfg.YuvSampleType);
    printf("EncCfg.YuvStoreType        = %d\n",EncCfg.YuvStoreType);
    printf("EncCfg.Qlevel              = %d\n",EncCfg.Qlevel);
    printf("EncIn.ViYStride            = %d\n",EncIn.ViYStride);
    printf("EncIn.ViCStride            = %d\n",EncIn.ViCStride);
    printf("=======================================================\n");

    s32Ret = HI_JPGE_Encode(u32EncHandle, &EncIn, &EncOut);
    if (HI_SUCCESS != s32Ret){
        printf("\nHI_JPGE_Encode failure \n");
        goto ERROR0;
    }

    u32NeedSize = (HI_S32)((HI_U32)EncOut.pStream - (HI_U32)pstInputInfo->pOutVirBuf) + EncOut.StrmSize;
    if(u32NeedSize > pstInputInfo->u32OutSize){
        printf("\nthe output memory size is too small\n");
        goto ERROR0;
    }else{
        printf("\n=======================================================\n");
        printf("should need buffer size  = %d\n", u32NeedSize);
        printf("alloc out buffer size    = %d\n",pstInputInfo->u32OutSize);
        printf("=======================================================\n");
    }

    //save to file
    if ((pOutFile = fopen(pEncFileName, "wb+")) == NULL) {
        printf("\ncan't open write to jpeg file\n");
        goto ERROR0;
    }
    fwrite(EncOut.pStream,1,EncOut.StrmSize,pOutFile);
    if(NULL != pOutFile){
        fclose(pOutFile);
        pOutFile = NULL;
    }
    //hit output info
    printf("\n-------> save file: %s OK. n",pEncFileName);
    printf("\n=======================================================\n");
    printf("EncOut.pStream   = 0x%p\n", EncOut.pStream);
    printf("EncOut.StrmSize  = %d\n",EncOut.StrmSize);
    printf("=======================================================\n");

    s32Ret = HI_JPGE_Destroy(u32EncHandle);
    if (HI_SUCCESS != s32Ret){
        printf("\nHI_JPGE_Destroy FAILURE\n");
        goto ERROR1;
    }

    HI_JPGE_Close();

    return HI_SUCCESS;


ERROR0:
    HI_JPGE_Destroy(u32EncHandle);

ERROR1:
    HI_JPGE_Close();

    if(NULL != pOutFile){
        fclose(pOutFile);
        pOutFile = NULL;
    }

    return HI_FAILURE;
}


/* Save VideoFrame to jpeg file using hardware encoder
 * IN:  Video Frame, file full patch to saved
 * ret: status, HI_FAILURE/ HI_SUCCESS
 */
int EncodeFrame_HI_JPEG(HI_UNF_VIDEO_FRAME_INFO_S *pstFrame, HI_CHAR *DstFile)
{
    printf("\n[%d] [%s] IN\n",__LINE__,__FUNCTION__);
    HI_S32 s32Ret              = HI_SUCCESS;
    HI_CHAR strModuleNameIn[]  = "JpegEnc_IN";
    HI_CHAR strModuleNameOut[] = "JpegEnc_OUT";
    HI_U32  u32PhyBuf_Reserved = 0;
    JPGE_INPUT_S   stJpgeInput;
    memset(&stJpgeInput,0,sizeof(JPGE_INPUT_S));

    stJpgeInput.u32Width[0]  = pstFrame->u32Width; //picture width
    stJpgeInput.u32Height[0] = pstFrame->u32Height; //picture height
    stJpgeInput.u32Stride[0] = stJpgeInput.u32Width[0]; //stright height
    stJpgeInput.u32Size[0]   = stJpgeInput.u32Stride[0] * stJpgeInput.u32Height[0]; //Y length

    stJpgeInput.u32Width[1]  = stJpgeInput.u32Width[0]  >> 1; //UV
    stJpgeInput.u32Height[1] = stJpgeInput.u32Height[0] >> 1; //UV
    stJpgeInput.u32Stride[1] = stJpgeInput.u32Stride[0];
    stJpgeInput.u32Size[1]   = stJpgeInput.u32Stride[1] * stJpgeInput.u32Height[1]; //UV length

    // get yuv420sp data
    stJpgeInput.u32PhyBuf[0] = (HI_U32)HI_MMZ_New(stJpgeInput.u32Size[0] + stJpgeInput.u32Size[1], 64, NULL, strModuleNameIn);
    u32PhyBuf_Reserved = stJpgeInput.u32PhyBuf[0];
    if (0 == stJpgeInput.u32PhyBuf[0]) {
        printf("HI_MMZ_New failure! size(%zu), block(%s) \n", \
                (stJpgeInput.u32Size[0] + stJpgeInput.u32Size[1]), strModuleNameIn);
        goto FINISHED;
    }
    stJpgeInput.pVirBuf[0] = (HI_CHAR*)HI_MMZ_Map(stJpgeInput.u32PhyBuf[0], HI_FALSE);
    if (NULL == stJpgeInput.pVirBuf[0]) {
        printf("HI_MMZ_Map failure! u32PhyBuf(%zu),", stJpgeInput.u32PhyBuf[0]);
        goto FINISHED;
    }

    u32PhyBuf_Reserved = stJpgeInput.u32PhyBuf[0];
    stJpgeInput.u32PhyBuf[1] = stJpgeInput.u32PhyBuf[0] + stJpgeInput.u32Size[0];
    stJpgeInput.pVirBuf[1]   = stJpgeInput.pVirBuf[0]   + stJpgeInput.u32Size[0];

    stJpgeInput.u32PhyBuf[0] = pstFrame->stVideoFrameAddr[0].u32YAddr;
    stJpgeInput.u32PhyBuf[1] = pstFrame->stVideoFrameAddr[0].u32CAddr;

    // alloc output buffer, equal y size
    stJpgeInput.u32OutSize   = stJpgeInput.u32Size[0];

    stJpgeInput.u32OutPhyBuf = (HI_U32)HI_MMZ_New(stJpgeInput.u32OutSize, 64, NULL, strModuleNameOut);
    if(0 == stJpgeInput.u32OutPhyBuf){
        printf("HI_MMZ_New failure! size(%zu), block(%s) \n", \
                (stJpgeInput.u32OutSize), strModuleNameOut);
        goto FINISHED;
    }
    stJpgeInput.pOutVirBuf = (HI_CHAR*)HI_MMZ_Map(stJpgeInput.u32OutPhyBuf, HI_FALSE);
    if(NULL == stJpgeInput.pOutVirBuf){
        printf("HI_MMZ_Map failure! u32PhyBuf(%zu) \n", stJpgeInput.u32OutPhyBuf);
        goto FINISHED;
    }

    stJpgeInput.u32YuvFmtType    = JPGE_INPUT_FMT_YUV420;
    stJpgeInput.u32YuvSampleType = JPGE_INPUT_SAMPLE_SEMIPLANNAR;
    stJpgeInput.u32Qlevel        = 80;


    printf("\n[%d] -------->JPEG_EncToFile start\n",__LINE__);

    s32Ret = JPEG_EncToFile(DstFile, &stJpgeInput);
    if(HI_SUCCESS != s32Ret){
        printf("JPEG_EncToFile failure\n");
    }else{
        printf("------->JPEG_EncToFile success\n");
    }
    printf("\n[%d] --------->JPEG_EncToFile finished\n",__LINE__);

    // free stream buffer
    HI_MMZ_Unmap(stJpgeInput.u32OutPhyBuf);
    HI_MMZ_Delete(stJpgeInput.u32OutPhyBuf);
    stJpgeInput.u32OutPhyBuf = 0;
    stJpgeInput.pOutVirBuf   = NULL;

    // stJpgeInput.u32PhyBuf[0] has been changed after encoding
    //HI_MMZ_Unmap(stJpgeInput.u32PhyBuf[0]);
    HI_MMZ_Unmap(u32PhyBuf_Reserved);
    //HI_MMZ_Delete(stJpgeInput.u32PhyBuf[0]);
    HI_MMZ_Delete(u32PhyBuf_Reserved);
    stJpgeInput.u32PhyBuf[0] = 0;
    stJpgeInput.pVirBuf[0]   = NULL;

    printf("\n[%d] [%s] OUT\n",__LINE__,__FUNCTION__);
    return HI_SUCCESS;

FINISHED:
    if(NULL != stJpgeInput.pOutVirBuf){
        HI_MMZ_Unmap(stJpgeInput.u32OutPhyBuf);
        stJpgeInput.pOutVirBuf   = NULL;
    }

    if(0 != stJpgeInput.u32OutPhyBuf){
        HI_MMZ_Delete(stJpgeInput.u32OutPhyBuf);
        stJpgeInput.u32OutPhyBuf = 0;
    }

    if(NULL != stJpgeInput.pVirBuf[0]){
        HI_MMZ_Unmap(stJpgeInput.u32PhyBuf[0]);
        stJpgeInput.pVirBuf[0]   = NULL;
    }

    if(0 != stJpgeInput.u32PhyBuf[0]){
        HI_MMZ_Delete(stJpgeInput.u32PhyBuf[0]);
        stJpgeInput.u32PhyBuf[0] = 0;
    }

    printf("\n[%d] [%s] OUT\n",__LINE__,__FUNCTION__);
    return HI_FAILURE;
}


/* use TDE convert YUV 2 RGBA8888
 * convert and stretch
 * org size: from VideoFrame
 * target size: from DstRect
 */
static HI_S32 YUV2RGBA8888andStretch(HI_UNF_VIDEO_FRAME_INFO_S *pstFrame, HI_U32 u32PhyAddr, HI_RECT_S *pstDstRect)
{
    HI_S32              s32Ret;
    TDE2_SURFACE_S      TDEDstSurface;
    TDE2_MBOPT_S        stMbOpt;
    TDE2_MB_S           TDESrcSurface;
    TDE_HANDLE          s32Handle;
    TDE2_RECT_S SrcRect = {0, 0, pstFrame->u32Width, pstFrame->u32Height};

    TDE2_RECT_S DstRect;


    memset(&TDEDstSurface,0,sizeof(TDEDstSurface));
    memset(&stMbOpt,0,sizeof(stMbOpt));
    memset(&TDESrcSurface,0,sizeof(TDESrcSurface));


    // set the src surface
    TDESrcSurface.enMbFmt       = TDE2_MB_COLOR_FMT_JPG_YCbCr420MBP;
    TDESrcSurface.u32YPhyAddr   = pstFrame->stVideoFrameAddr[0].u32YAddr;
    TDESrcSurface.u32CbCrPhyAddr = pstFrame->stVideoFrameAddr[0].u32CAddr;
    TDESrcSurface.u32YStride    = pstFrame->stVideoFrameAddr[0].u32YStride;
    TDESrcSurface.u32CbCrStride = pstFrame->stVideoFrameAddr[0].u32CStride;
    TDESrcSurface.u32YWidth     = pstFrame->u32Width;
    TDESrcSurface.u32YHeight    = pstFrame->u32Height;


    // set the dst surface
    TDEDstSurface.u32PhyAddr = u32PhyAddr;
    TDEDstSurface.enColorFmt = TDE2_COLOR_FMT_ABGR8888;
    TDEDstSurface.u32Width  = pstDstRect->s32Width;
    TDEDstSurface.u32Height = pstDstRect->s32Height;

    TDEDstSurface.u32Stride = pstDstRect->s32Width*4;
    TDEDstSurface.pu8ClutPhyAddr = NULL;
    TDEDstSurface.bYCbCrClut = HI_FALSE;


    TDEDstSurface.u32CbCrPhyAddr = 0;
    TDEDstSurface.u32CbCrStride  = 0;

    TDEDstSurface.bAlphaMax255  = HI_TRUE;
    TDEDstSurface.bAlphaExt1555 = HI_FALSE;
    TDEDstSurface.u8Alpha0 = 0;
    TDEDstSurface.u8Alpha1 = 255;


    if (HI_NULL != pstDstRect)
    {
        DstRect.s32Xpos = pstDstRect->s32X;
        DstRect.s32Ypos = pstDstRect->s32Y;
        DstRect.u32Width = pstDstRect->s32Width;
        DstRect.u32Height = pstDstRect->s32Height;
    }
    else
    {
        DstRect.s32Xpos = 0;
        DstRect.s32Ypos = 0;
        DstRect.u32Width =  pstFrame->u32Width;
        DstRect.u32Height = pstFrame->u32Height;
    }

    s32Handle = HI_TDE2_BeginJob();
    if (s32Handle == HI_ERR_TDE_INVALID_HANDLE)
    {
        printf("begin jop failed\n");
        goto FINISHED;
    }

    stMbOpt.enResize = TDE2_MBRESIZE_QUALITY_LOW;    //enable scale

    s32Ret = HI_TDE2_MbBlit(s32Handle, &TDESrcSurface, &SrcRect, &TDEDstSurface, &DstRect, &stMbOpt);
    if (HI_SUCCESS != s32Ret)
    {
        printf("Mbblit failed: %x\n",s32Ret);
        (HI_VOID)HI_TDE2_EndJob(s32Handle, HI_FALSE, HI_TRUE, 100);
        goto FINISHED;
    }

    s32Ret = HI_TDE2_EndJob(s32Handle, HI_FALSE, HI_TRUE, 100);
    if ((HI_SUCCESS != s32Ret) && (HI_ERR_TDE_JOB_TIMEOUT != s32Ret))
    {
        printf("end job failed\n");
        goto FINISHED;
    }

    s32Ret = HI_TDE2_WaitForDone(s32Handle);
    if (HI_ERR_TDE_QUERY_TIMEOUT == s32Ret)
    {
        printf("wait for done time out");
        goto FINISHED;
    }

FINISHED:
    return HI_SUCCESS;
}


/* Save VideoFrame to jpeg file using hardware encoder
 * IN:  Video Frame, file full patch to saved
 * ret: status, HI_FAILURE/ HI_SUCCESS
 */
void YUV2RGBAandSave(HI_UNF_VIDEO_FRAME_INFO_S *pstFrame, HI_CHAR *DstFile)
{
    printf("[%4zu]  IN  %s",__LINE__,__FUNCTION__);
    HI_RECT_S               targetRect{0,0,1280,720};
    FILE                    *pOutFile = NULL;

    HI_U32  w  = targetRect.s32Width;
    HI_U32  h = targetRect.s32Height;
    HI_U32  u32PhyAddr=0;
    HI_CHAR *pVirAddr=HI_NULL;
    HI_CHAR strModuleNameIn[]  = "YUV2RGBA_IN";
    HI_CHAR strModuleNameOut[] = "YUV2RGBA_OUT";

    printf("[%4zu]  Alloc MMZ size: %8zu  Name:%s",__LINE__,w*h*4, strModuleNameIn);
    //map phyaddr
    u32PhyAddr = (HI_U32)HI_MMZ_New(w*h*4, 64, NULL, strModuleNameIn);
    if (0 == u32PhyAddr) {
        printf("HI_MMZ_New failure! size(%zu), block(%s) \n", w*h*4, strModuleNameIn);
        goto FINISHED;
    }
    pVirAddr = (HI_CHAR*)HI_MMZ_Map(u32PhyAddr, 1);
    if (HI_NULL == pVirAddr) {
        printf("HI_MMZ_Map failure! u32PhyAddr(%zu),", u32PhyAddr);
        goto FINISHED;
    }

    printf("[%4zu]  Before YUV2RGBA8888andStretch rect(%zu,%zu, %zux%zu)",__LINE__,
    targetRect.s32X, targetRect.s32Y,targetRect.s32Width,targetRect.s32Height);
    YUV2RGBA8888andStretch(pstFrame, u32PhyAddr, &targetRect);
    printf("[%4zu]  After YUV2RGBA8888",__LINE__);
    //RGBA2bmp(DstFile,pVirAddr,u32Width, u32Height,32);


    printf("[%4zu]  Before save to file[%s]",__LINE__,DstFile);
    if ((pOutFile = fopen(DstFile, "wb+")) != NULL) {
        fwrite(pVirAddr, 1, w*h*4, pOutFile);
        if(NULL != pOutFile){
            fclose(pOutFile);
            pOutFile = NULL;
        }
    }else{
        printf("\ncan't open write to jpeg file\n");
    }
    printf("[%4zu]  After save to file[%s]",__LINE__,DstFile);

FINISHED:
    if(NULL != pVirAddr){
        HI_MMZ_Unmap(u32PhyAddr);
    }

    if(0 != u32PhyAddr){
        HI_MMZ_Delete(u32PhyAddr);
    }
    printf("[%4zu]  OUT %s",__LINE__,__FUNCTION__);

    //return 0;
}
