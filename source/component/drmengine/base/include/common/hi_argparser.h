/******************************************************************************

  Copyright (C), 2005-2006, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_argparser.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2005/7/1
  Last Modified :
  Description   : Argument parser
  Function List :
  History       :
  1.Date        : 2005/7/27
    Author      : T41030
    Modification: Created file

  2.Date        : 2006/4/7
    Author      : q63946
    Modification: modify for HI3510 Demo
******************************************************************************/

#ifndef __HI_ARGPARSER_H__
#define __HI_ARGPARSER_H__

//#include "hi_head.h"

#include "hi_type.h"
//#include "svr_debug.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define TABL "    "
//#ifndef HI_ADVCA_FUNCTION_RELEASE

typedef enum hiARG_TYPE_E
{
    /** ARG_TYPE_NO_PARA和ARG_TYPE_NO_OPT是互斥选项*/
    /** ARG_TYPE_STRING、ARG_TYPE_CHAR、ARG_TYPE_INT、ARG_TYPE_FLOAT 是互斥选项*/
    ARG_TYPE_MUST       = 0x1,   /*是否是必须选项*/
    ARG_TYPE_NO_OPT     = 0x2,   /*允许没有选项(-XXX), 只有一个参数值*/
    ARG_TYPE_NO_PARA    = 0x4,   /*单个, 不带参数*/
    ARG_TYPE_STRING     = 0x8,   /*字符串*/
    ARG_TYPE_CHAR       = 0x10,  /*字符型*/
    ARG_TYPE_INT        = 0x20,  /*整型*/
    ARG_TYPE_INT64      = 0x40,  /*64位整型*/
    ARG_TYPE_FLOAT      = 0x80,  /*浮点型*/
    ARG_TYPE_HELP       = 0x100, /**/
    ARG_TYPE_SINGLE     = 0x200, /*存在该选项，则不能设置其他选项，否则返回解析错误*/
    ARG_TYPE_END        = 0x400,
    ARG_TYPE_BUTT       = 0x800,
    ARG_TYPE_4BYTE      = 0xFFFFFFFF
} ARG_TYPE_E;

typedef struct hiARGOPT_STRUCT_S
{
    const HI_CHAR*        pszOpt;         /** Option 名字,如:"cmd -XXX"中的"XXX" */
    HI_U32          u32Type;        /** Use demo_arg_type,可以同时选择几个值的按位或,
                                        如:ARG_TYPE_MUST|ARG_TYPE_NO_OPT|ARG_TYPE_STRING
                                        代表该选项为必须输入值且可以不输入选项,值为字符串型数据.
                                    */
    const HI_CHAR*        pszValueRegion; /** 可选值或取值范围,范围的正确性由应用负责,
                                        如果该值为空则代表输入值由应用解析.
                                        1)可选值方式      :   "1|2|3|all";
                                            该方式适用于:string,char,int
                                        2)取值范围方式    :   "0~10","1~","~12","a~z","a~";
                                            该方式适用于:char,int,float
                                        3)可选取值范围方式:   "~-12|0~10|20","~a|c~e|x~y|X~Y";
                                            该方式适用于:int,char,float
                                        string  只能用 1)方式;
                                        float,char,int可用 1)2)3)方式
                                    */
    HI_CHAR         s8Isset;        /** 1: be set, 0 not set */
    HI_U8           au8resv[3];
    const HI_CHAR*        pszHelpMsg;
    HI_VOID*        pValue;
    HI_U32          u32ValueBuffersize;/*pValue指向空间长度*/
} ARG_OPT_S;

HI_S32  HI_ARG_Parser(int argc, const char **argv, ARG_OPT_S *opts);
HI_VOID HI_ARG_PrintOpt(ARG_OPT_S *pOpt);

HI_VOID HI_ARG_StrToArg(HI_CHAR* pSrc, int* argc, HI_CHAR** argv);
HI_VOID HI_ARG_ClearOpts(ARG_OPT_S *opts);
HI_VOID HI_ARG_PrintHelp(HI_U32 u32Handle, ARG_OPT_S *opts);
HI_S32  HI_ARG_OptIsSet(const HI_CHAR *opt_name, ARG_OPT_S *opts);

//#endif/*HI_ADVCA_FUNCTION_RELEASE*/

#define ARG_S4 "    "     /*4 space*/
#define HI_ARG_MAX_OPT_NAME_LEN (256) // define option name length for strncmp

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* ARGPARSER_H__ */
