#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
/*
* args1: fbl.bin --  supplied by hisilicon
* args2: mode --- 0: parse the fbl.bin to get the  four parts below
                           1: replace the Ext Key Area
                           2: replace the Ext Key Area Signature
                           4: replace the Ext Params Area
                           8: replace the Ext Params Area Signature
                           above modes could be or if more than one part need replaced
* args3: part1 file -- if mode==0, no need; if others value, the first parts files.
* args4: part2 file -- only mode includes two or more parts, this is valided.
* args5: part3 file -- only mode includes three or more parts, this is valided.
* args6: part4 file -- only mode includes four parts, this is valided.
* example
    ./fbl_ctrl fbl.bin 0
            -- parse the fbl.bin and get Ext Key Area(Ext_Key.bin), Ext Key Area Signature(Ext_Key_Sig.bin),
                                                    Ext Params Area(Ext_Para.bin), Ext Params Area Signature(Ext_Para_Sig.bin)
   ./fbl_ctrl fbl.bin 2   Ext_Key_Sig.bin
            -- replace the Ext Key Area Signature using Ext_Key_Sig.bin
    ./fbl_ctrl fbl.bin 10   Ext_Key_Sig.bin Ext_Para_Sig.bin
            -- replace the Ext Key Area Signature using Ext_Key_Sig.bin; replace the Ext Params Area Signature using Ext_Para_Sig.bin
*/

#define EXT_KEY_AREA_LENGTH     (0x220)
#define EXT_KEY_SIGN_LENGTH     (0x100)
#define EXT_PARAM_AREA_LENGTH   (0x25E0)
#define EXT_PARAM_SIGN_LENGTH   (0x100)

#define KEY_MASK        (1)
#define KEY_SIG_MASK    (2)
#define PARAM_MASK      (4)
#define PARAM_SIG_MASK  (8)

#define FBL_HEADER_LENGTH       (0x3000)
#define FBL_AUX_AREA_OFFSET     (0x218)
#define FBL_BOOT_AREA_OFFSET    (0x408)
#define FBL_EXTEND_FLAG_OFFSET  (0x40C)
#define FBL_EXTEND_AREA_FALG    (0x2a13c812)
#define FBL_READ_ONE_WORD_POS(fileFd, pBuf, ReadOffset)\
    do{\
        fseek(fileFd, ReadOffset, SEEK_SET);\
        if (4 != fread(pBuf, 1, 4, fileFd))\
        {\
            perror("read error:");\
            printf("[%s_%d]read(0x%x) failed!\n", __FUNCTION__, __LINE__, ReadOffset);\
            fclose(fileFd); \
            return -1;}\
    }while(0)

int checkFblFile(char *pszFileName, int *pbNake)
{
    FILE *fpFbl = NULL;
    int bNake = 0;
    int length = 0;
    int readLen = 0;
    int AuxAreaLen = 0;
    int BootAreaLen = 0;
    int ret = 0;
    unsigned int ExtendAreaFlag = 0;
    
    if (NULL == pszFileName)
    {
        printf("NULL for fbl filename!\n");
        return -1;
    }
    
    fpFbl = fopen(pszFileName, "rb+");
    if (NULL == fpFbl)
    {
        perror("open failed:");
        ret = -1;
        goto EXIT;
    }
    
    fseek(fpFbl, 0, SEEK_END);
    length = ftell(fpFbl);
    if (length < FBL_HEADER_LENGTH)
    {
        printf("Invalid fbl file!\n");
        ret = -1;
        goto EXIT;
    }

    FBL_READ_ONE_WORD_POS(fpFbl, &AuxAreaLen, FBL_AUX_AREA_OFFSET);
    FBL_READ_ONE_WORD_POS(fpFbl, &BootAreaLen, FBL_BOOT_AREA_OFFSET);
    FBL_READ_ONE_WORD_POS(fpFbl, &ExtendAreaFlag, FBL_EXTEND_FLAG_OFFSET);
    

    if (FBL_EXTEND_AREA_FALG != ExtendAreaFlag)
    {
        printf("Invalid fbl file(0x%08x)!\n", ExtendAreaFlag);
        ret = -1;
        goto EXIT;
    }

    if (length == FBL_HEADER_LENGTH + AuxAreaLen + BootAreaLen)
    {
        bNake = 1;
    }
    else if (length != 0x2A00 + FBL_HEADER_LENGTH + AuxAreaLen + BootAreaLen)
    {
        ret = -1;
    }
    
    if ((0 == ret) && (NULL != pbNake))
    {
        *pbNake = bNake;
    }
EXIT:
    if (NULL!= fpFbl)
    {
        fclose(fpFbl);
        fpFbl = NULL;
    }

    return ret;
}
int checkArgs(int argc, char* argv[])
{
    int mode = 0;
    int numReplace = 0;
    if (3 > argc)
    { return -1; }
    mode = strtol(argv[2], NULL, 0);
    
    if (0 == mode)
    {
        if (3 != argc)
        { return -1; }
        else
        { return 0; }
    }
    if (0 != (mode & KEY_MASK))
    {
        numReplace++;
    }
    
    if (0 != (mode & KEY_SIG_MASK))
    {
        numReplace++;
    }
    
    if (0 != (mode & PARAM_MASK))
    {
        numReplace++;
    }
    
    if (0 != (mode & PARAM_SIG_MASK))
    {
        numReplace++;
    }
    
    printf("mode = %d; argc = %d; numReplace = %d\n", mode, argc, numReplace);
    if ((3 + numReplace) != argc)
    { return -1; }
    else
    { return 0; }
}
void printUsage(int argc, char* argv[])
{
    printf("Usage: %s fbl_file mode [part1_file] [part2_file] [part3_file] [part4_file]\n"
           "\tfbl_file --  supplied by hisilicon \n"
           "\tmode --- 0: parse the fbl_file to get the  four parts\n"
           "\t         1: replace the Ext Key Area\n"
           "\t         2: replace the Ext Key Area Signature\n"
           "\t         4: replace the Ext Params Area\n"
           "\t         8: replace the Ext Params Area Signature\n"
           "\t         above modes could be or if more than one part need replaced\n"
           "note: for more than one part: the file order is:\n"
           "\tExt Key Area, Ext Key Area Signature, Ext Params Area, Ext Params Area Signature\n",
           argv[0]);
    printf("example:\n %s 0\n"
           "\t-- parse the fbl.bin and get Ext Key Area(Ext_Key.bin), Ext Key Area Signature(Ext_Key_Sig.bin),\n"
           "\t                             Ext Params Area(Ext_Para.bin), Ext Params Area Signature(Ext_Para_Sig.bin)\n", argv[0]);
    printf("%s  2   Ext_Key_Sig.bin\n"
           "\t-- replace the Ext Key Area Signature using Ext_Key_Sig.bin", argv[0]);
    printf("%s 10   Ext_Key_Sig.bin Ext_Para_Sig.bin\n"
           "\t-- replace the Ext Key Area Signature using Ext_Key_Sig.bin; replace the Ext Params Area Signature using Ext_Para_Sig.bin", argv[0]);
    return;
}
int parseFbl(char* pszFblName)
{
    FILE *fpFbl = NULL;
    FILE *fpPart = NULL;
    char szPartName[256];
    char *pBuf = NULL;
    int ret = 0;
    int length = EXT_KEY_AREA_LENGTH + EXT_KEY_SIGN_LENGTH + EXT_PARAM_AREA_LENGTH + EXT_PARAM_SIGN_LENGTH;
    int len = 0;
    int offset = 0;

    if (NULL == pszFblName)
    {
        printf("NULL for fbl filename!\n");
        ret = -1;
        goto EXIT;
    }
    
    pBuf = (char *)malloc(length);
    if (NULL == pBuf)
    {
        perror("malloc failed:");
        ret = -1;
        goto EXIT;
    }
    memset(pBuf, 0x00, length);

    fpFbl = fopen(pszFblName, "rb+");
    if (NULL == fpFbl)
    {
        perror("open failed:");
        ret = -1;
        goto EXIT;
    }
    
    fseek(fpFbl, -1*length, SEEK_END);
    len = fread(pBuf, 1, length, fpFbl);
    if (len != length)
    {
        printf("read fbl file failed!want:%d;actual:%d\n", length, len);
        ret = -1;
        goto EXIT;
    }
    
    memset(szPartName, 0x00, 256*sizeof(char));
    snprintf(szPartName, 255, "%s_Ext_Key.bin", pszFblName);
    fpPart = fopen(szPartName, "wb+");
    if (NULL == fpPart)
    {
        perror("open file failed:");
        ret = -1;
        goto EXIT;
    }

    len = fwrite(pBuf + offset, 1, EXT_KEY_AREA_LENGTH, fpPart);
    if (EXT_KEY_AREA_LENGTH != len)
    {
        perror("write file failed:");
        ret = -1;
        goto EXIT;
    }
    fflush(fpPart);
    fclose(fpPart);
    fpPart = NULL;
    offset += EXT_KEY_AREA_LENGTH;
    
    memset(szPartName, 0x00, 256*sizeof(char));
    snprintf(szPartName, 255, "%s_Ext_Key_Sig.bin", pszFblName);
    fpPart = fopen(szPartName, "wb+");
    if (NULL == fpPart)
    {
        perror("open file failed:");
        ret = -1;
        goto EXIT;
    }

    len = fwrite(pBuf + offset, 1, EXT_KEY_SIGN_LENGTH, fpPart);
    if (EXT_KEY_SIGN_LENGTH != len)
    {
        perror("write file failed:");
        ret = -1;
        goto EXIT;
    }
    fflush(fpPart);
    fclose(fpPart);
    fpPart = NULL;
    offset += EXT_KEY_SIGN_LENGTH;

    memset(szPartName, 0x00, 256*sizeof(char));
    snprintf(szPartName, 255, "%s_Ext_Param.bin", pszFblName);
    fpPart = fopen(szPartName, "wb+");
    if (NULL == fpPart)
    {
        perror("open file failed:");
        ret = -1;
        goto EXIT;
    }

    len = fwrite(pBuf + offset, 1, EXT_PARAM_AREA_LENGTH, fpPart);
    if (EXT_PARAM_AREA_LENGTH != len)
    {
        perror("write file failed:");
        ret = -1;
        goto EXIT;
    }
    fflush(fpPart);
    fclose(fpPart);
    fpPart = NULL;
    offset += EXT_PARAM_AREA_LENGTH;

    memset(szPartName, 0x00, 256*sizeof(char));
    snprintf(szPartName, 255, "%s_Ext_Param_Sig.bin", pszFblName);
    fpPart = fopen(szPartName, "wb+");
    if (NULL == fpPart)
    {
        perror("open file failed:");
        ret = -1;
        goto EXIT;
    }

    len = fwrite(pBuf + offset, 1, EXT_PARAM_SIGN_LENGTH, fpPart);
    if (EXT_PARAM_SIGN_LENGTH != len)
    {
        perror("write file failed:");
        ret = -1;
        goto EXIT;
    }
    fflush(fpPart);
    fclose(fpPart);
    fpPart = NULL;
    
EXIT:
    if (NULL != fpFbl)
    {
        fclose(fpFbl);
        fpFbl = NULL;
    }
    if (NULL != fpPart)
    {
        fclose(fpPart);
        fpPart = NULL;
    }
    if (NULL != pBuf)
    {
        free(pBuf);
        pBuf = NULL;
    }
    return ret;
}

int replacePart(char* pszFblName, char* pszPartName, int mode)
{
    int fdFbl = -1;
    int fdPart = -1;
    char* pBuf = NULL;
    int offset = 0;
    int length = 0;
    int fileLen = 0;
    int ret = 0;

    if ((NULL == pszFblName) || (NULL == pszPartName))
    {
        printf("null filename!\n");
        return -1;
    }

    if (access(pszPartName, R_OK))
    {
        perror("invalid part filename:");
        return -1;
    }

    switch (mode)
    {
        case KEY_MASK:
            offset = EXT_KEY_AREA_LENGTH + EXT_KEY_SIGN_LENGTH + EXT_PARAM_AREA_LENGTH + EXT_PARAM_SIGN_LENGTH;
            length = EXT_KEY_AREA_LENGTH;
            break;
        case KEY_SIG_MASK:
            offset = EXT_KEY_SIGN_LENGTH + EXT_PARAM_AREA_LENGTH + EXT_PARAM_SIGN_LENGTH;
            length = EXT_KEY_SIGN_LENGTH;
            break;
        case PARAM_MASK:
            offset = EXT_PARAM_AREA_LENGTH + EXT_PARAM_SIGN_LENGTH;
            length = EXT_PARAM_AREA_LENGTH;
            break;
        case PARAM_SIG_MASK:
            offset = EXT_PARAM_SIGN_LENGTH;
            length = EXT_PARAM_SIGN_LENGTH;
            break;
        default:
            printf("Invalid mode(%d)!\n", mode);
            ret = -1;
            goto EXIT;
    }

    fdFbl = open(pszFblName, O_RDWR);
    if (0 > fdFbl)
    {
        perror("open file failed:");
        ret = -1;
        goto EXIT;
    }

    fdPart = open(pszPartName, O_RDWR);
    if (0 > fdFbl)
    {
        perror("open file failed:");
        ret = -1;
        goto EXIT;
    }

    pBuf = (char*)malloc(length * sizeof(char));
    if (NULL == pBuf)
    {
        perror("malloc failed:");
        ret = -1;
        goto EXIT;
    }

    memset(pBuf, 0x00, length * sizeof(char));
    lseek(fdPart, 0, SEEK_SET);
    fileLen = lseek(fdPart, 0, SEEK_END);
    if (length != fileLen)
    {
        printf("part file(%d) and expect length(%d) are not different!\n", fileLen, length);
        ret = -1;
        goto EXIT;
    }
    lseek(fdPart, 0, SEEK_SET);
    fileLen = read(fdPart, pBuf, length);
    if (fileLen != length)
    {
        printf("read part file failed!want:%d;actual:%d\n", length, fileLen);
        ret = -1;
        goto EXIT;
    }

    lseek(fdFbl, 0, SEEK_SET);
    fileLen = lseek(fdFbl, 0, SEEK_END);
    if (EXT_KEY_AREA_LENGTH + EXT_KEY_SIGN_LENGTH + EXT_PARAM_AREA_LENGTH + EXT_PARAM_SIGN_LENGTH >= fileLen)
    {
        printf("the length(%d) of fbl file is invalid!\n", fileLen);
        ret = -1;
        goto EXIT;
    }
    
    offset = -1*offset;
    lseek(fdFbl, offset, SEEK_END);
    fileLen = write(fdFbl, pBuf, length);
    if (fileLen != length)
    {
        printf("write fbl file failed!want:%d;actual:%d\n", length, fileLen);
        ret = -1;
        goto EXIT;
    }
    
EXIT:
    if (0 <= fdFbl)
    {
        fsync(fdFbl);
        close(fdFbl);
        fdFbl = -1;
    }
    if (0 < fdPart)
    {
        close(fdPart);
        fdPart = -1;
    }
    if (NULL != pBuf)
    {
        memset(pBuf, 0x00, length);
        free(pBuf);
        pBuf = NULL;
    }
    return ret;

}

int appendPart(char* pszFblName, char* pszPartName)
{
    int fdFbl = -1;
    int fdPart = -1;
    char* pBuf = NULL;
    int offset = 0;
    int length = 0;
    int ret = 0;

    if ((NULL == pszFblName) || (NULL == pszPartName))
    {
        printf("null filename!\n");
        return -1;
    }

    if (access(pszFblName, R_OK | W_OK))
    {
        perror("invalid fbl filename:");
        return -1;
    }

    if (access(pszPartName, R_OK))
    {
        perror("invalid part filename:");
        return -1;
    }

    fdFbl = open(pszFblName, O_RDWR);
    if (0 > fdFbl)
    {
        perror("open file failed:");
        ret = -1;
        goto EXIT;
    }

    fdPart = open(pszPartName, O_RDWR);
    if (0 > fdFbl)
    {
        perror("open file failed:");
        ret = -1;
        goto EXIT;
    }
    length = lseek(fdPart, 0, SEEK_END);
    pBuf = (char*)malloc(length * sizeof(char));
    if (NULL == pBuf)
    {
        perror("malloc failed:");
        ret = -1;
        goto EXIT;
    }

    memset(pBuf, 0x00, length * sizeof(char));
    lseek(fdPart, 0, SEEK_SET);
    if (length != read(fdPart, pBuf, length))
    {
        perror("read part file failed:");
        ret = -1;
        goto EXIT;
    }

    lseek(fdFbl, 0, SEEK_END);
    if (length != write(fdFbl, pBuf, length))
    {
        perror("write fbl file failed:");
        ret = -1;
        goto EXIT;
    }
    
EXIT:
    if (0 <= fdFbl)
    {
        fsync(fdFbl);
        close(fdFbl);
        fdFbl = -1;
    }
    if (0 < fdPart)
    {
        close(fdPart);
        fdPart = -1;
    }
    if (NULL != pBuf)
    {
        memset(pBuf, 0x00, length);
        free(pBuf);
        pBuf = NULL;
    }
    return ret;

}
int main(int argc, char* argv[])
{
    int bParse = 0,bKey = 0,bKeySig = 0, bParam=0, bParamSig = 0;
    int mode = 0,idx = 0, bNake = 0, length = 0, ret = -1;
    char* pszFblName = NULL;
    char* pszKeyName = NULL;
    char* pszKeySigName = NULL;
    char* pszParamName = NULL;
    char* pszParamSigName = NULL;
    char *pBuf = NULL;
    char szNewFblFileName[256];
    FILE *fpOld = NULL;
    FILE *fpNew = NULL;
    
    if (0 != checkArgs(argc, argv))
    {
        printUsage(argc, argv);
        goto EXIT;
    }
    
    mode = strtol(argv[2], NULL, 0);
    pszFblName = argv[1];
    
    if (0 != checkFblFile(pszFblName, &bNake))
    {
        printf("Invalid fbl file!\n");
        goto EXIT;
    }
    printf("[%s_%d] bNake = %d\n", __FUNCTION__, __LINE__, bNake);
    if ((0 == mode) && (0 == bNake))
    {
        printf("the input fbl don't have the ext key or params!\n");
        goto EXIT;
    }

    if ((1 == bNake) && ((KEY_MASK|KEY_SIG_MASK|PARAM_MASK|PARAM_SIG_MASK) != mode))
    {
        printf("only support append the whole 4 part files!\n");
        goto EXIT;
    }
    
    if (mode == 0)
    {
        ret = parseFbl(pszFblName);
        printf("[%s_%d]\n", __FUNCTION__, __LINE__);
        goto EXIT;
    }
    memset(szNewFblFileName, 0x00, 256);
    snprintf(szNewFblFileName, 255, "%s_new.bin", pszFblName);
    fpOld = fopen(pszFblName, "rb+");
    if (NULL == fpOld)
    {
        perror("open file failed:");
        goto EXIT;
    }
    
    fpNew = fopen(szNewFblFileName, "wb+");
    if (NULL == fpNew)
    {
        perror("open file failed:");
        goto FILE_FAILED;
    }

    fseek(fpOld, 0, SEEK_END);
    length = ftell(fpOld);
    pBuf = (char *)malloc(length*sizeof(char));
    if (NULL == pBuf)
    {
        printf("malloc(%d) failed!\n", length);
        goto FILE_FAILED;
    }
    
    memset(pBuf, 0x00, length*sizeof(char));
    fseek(fpOld, 0, SEEK_SET);
    if (length != fread(pBuf, 1, length, fpOld))
    {
        perror("read failed:");
        printf("[%s_%d]:length=%d!\n", __FUNCTION__, __LINE__, length);
        goto FILE_FAILED;
    }
    fseek(fpNew, 0, SEEK_SET);
    if (length != fwrite(pBuf, 1, length, fpNew))
    {
        perror("write failed:");
        goto FILE_FAILED;
    }

    fflush(fpNew);
    free(pBuf);pBuf = NULL;
    fclose(fpOld);fpOld = NULL;
    fclose(fpNew);fpNew = NULL;
    ret = 0;
    if (1 == bNake)
    {
        pszKeyName = argv[3];
        ret = appendPart(szNewFblFileName, pszKeyName);
        pszKeyName = argv[4];
        ret |= appendPart(szNewFblFileName, pszKeyName);
        pszKeyName = argv[5];
        ret |= appendPart(szNewFblFileName, pszKeyName);
        pszKeyName = argv[6];
        ret |= appendPart(szNewFblFileName, pszKeyName);
        goto EXIT;
    }
    
    if (mode & KEY_MASK)
    {
        bKey = 1;
        pszKeyName = argv[3];
        ret |= replacePart(szNewFblFileName, pszKeyName, KEY_MASK);
        idx++;
    }

    if (mode & KEY_SIG_MASK)
    {
        bKeySig = 1;
        pszKeySigName = argv[3 + idx];
        ret |= replacePart(szNewFblFileName, pszKeySigName, KEY_SIG_MASK);
        idx++;
    }

    if (mode & PARAM_MASK)
    {
        bParam = 1;
        pszParamName = argv[3 + idx];
        ret |= replacePart(szNewFblFileName, pszParamName, PARAM_MASK);
        idx++;
    }

    if (mode & PARAM_SIG_MASK)
    {
        bParamSig = 1;
        pszParamSigName = argv[3 + idx];
        ret |= replacePart(szNewFblFileName, pszParamSigName, PARAM_SIG_MASK);
        idx++;
    }
    
FILE_FAILED:
    if (NULL != fpOld)
    {
        fclose(fpOld);
        fpOld = NULL;
    }
    if (NULL != fpNew)
    {
        fclose(fpNew);
        fpNew = NULL;
    }
    if (NULL != pBuf)
    {
        free(pBuf);
    }
    
EXIT:
    if (0 != ret)
    {
        printf("operation failed!please check the input!\n");
        printf("operation failed!please check the input!\n");
        printf("operation failed!please check the input!\n");
        if (0 != mode)
            remove(szNewFblFileName);
        return ret;
    }
    else
    {
        printf("operation success!\n");
        printf("operation success!\n");
        printf("operation success!\n");
        return 0;
    }
}