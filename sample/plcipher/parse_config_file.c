/******************************************************************************
Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name   :  parse_config_file.h
Author        :  Hisilicon multimedia software group
Created      :  2017/04/07
Description :
******************************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "hi_type.h"

#include "parse_config_file.h"


#define COMMENT_CHARACTER   '#'
#define LINE_SIZE    (768)



HI_CHAR g_avariables[MAX_VAR_NUM][MAX_VAR_NAME_LEN + 1];
HI_CHAR g_avalues[MAX_VAR_NUM][MAX_VAR_VALUE_LEN + 1];
HI_S32  g_var_num = 0;

void remove_trailing_chars(HI_CHAR* path, HI_CHAR c)
{
    size_t len;

    len = strlen(path);

    while (len > 0 && path[len - 1] == c)
    { path[--len] = '\0'; }
}

HI_S32 get_key(HI_CHAR** line, HI_CHAR** key, HI_CHAR** value)
{
    HI_CHAR* linepos;
    HI_CHAR* temp;

    linepos = *line;

    if (!linepos)
    {
        return -1;
    }

    /* skip whitespace */
    while (isspace(linepos[0]))
    { linepos++; }

    if (linepos[0] == '\0')
    {
        return -1;
    }

    /* get the key */
    *key = linepos;

    while (1)
    {
        linepos++;

        if (linepos[0] == '\0')
        {
            return -1;
        }

        if (isspace(linepos[0]))
        { break; }

        if (linepos[0] == '=')
        { break; }
    }

    /* terminate key */
    linepos[0] = '\0';

    while (1)
    {
        linepos++;

        if (linepos[0] == '\0')
        {
            return -1;
        }

        if (isspace(linepos[0]))
        { continue; }

        if (linepos[0] == '=')
        { continue; }

        break;
    }


    /* get the value*/
    if (linepos[0] == '"')
    {
        linepos++;
    }
    else
    {
        return -1;
    }

    *value = linepos;

    temp = strchr(linepos, '"');

    if (!temp)
    {
        return -1;
    }

    temp[0] = '\0';
    return 0;
}


HI_S32 parse_config_file(HI_CHAR* path_to_config_file)
{
    HI_CHAR line[LINE_SIZE + 2];
    HI_CHAR* bufline;
    HI_CHAR* linepos;
    HI_CHAR* variable;
    HI_CHAR* value;
    size_t count;
    HI_S32 lineno;
    HI_S32 retval = 0;

    FILE* cfg_file = fopen(path_to_config_file, "r");

    if (NULL == cfg_file)
    {
        printf("Open keyconfig:%s error\n", path_to_config_file);
        goto EXIT;
    }

    /* loop through the whole file */
    lineno = 0;
    while (NULL != fgets(line, sizeof(line), cfg_file))
    {
        lineno++;
        bufline = line;
        count = strlen(line);


        if (count > LINE_SIZE)
        {
            continue;
        }

        /* eat the whitespace */
        while ((count > 0) && isspace(bufline[0]))
        {
            bufline++;
            count--;
        }

        if (count == 0)
        { continue; }

        /* see if this is a comment */
        if (bufline[0] == COMMENT_CHARACTER)
        { continue; }

        memcpy(line, bufline, count);
        line[count] = '\0';

        linepos = line;

        retval = get_key(&linepos, &variable, &value);
        if (retval != 0)
        {
            printf("error parsing %s, line %d:%d", path_to_config_file, lineno, (HI_S32)(linepos - line));
            continue;
        }

        if (g_var_num >= MAX_VAR_NUM)
        {
            printf("too many vars in  %s, line %d:%d", path_to_config_file, lineno, (HI_S32)(linepos - line));
            continue;
        }

        if (strlen(variable) > MAX_VAR_NAME_LEN)
        {
            printf("var name to long %s, line %d:%d", path_to_config_file, lineno, (HI_S32)(linepos - line));
            continue;
        }

        if (strlen(value) > MAX_VAR_VALUE_LEN)
        {
            printf("value to long %s, line %d:%d", path_to_config_file, lineno, (HI_S32)(linepos - line));
            continue;
        }

        strncpy(g_avariables[g_var_num], variable, sizeof(g_avariables[g_var_num]));
        remove_trailing_chars(value, '/');
        strncpy(g_avalues[g_var_num], value, sizeof(g_avalues[g_var_num]));
        g_var_num++;
        continue;

    }

EXIT:
    if (cfg_file != NULL)
    {
        fclose(cfg_file);
    }

    return g_var_num;
}

HI_CHAR* get_config_var(HI_CHAR* var_name)
{
    HI_S32 i;

    for (i = 0; i < g_var_num; i++)
    {
        if (strcasecmp(g_avariables[i], var_name) == 0)
        {
            return g_avalues[i];
        }

    }

    return NULL;

}

HI_S32 get_key_value(HI_CHAR *pName, HI_U8 *pKey, HI_U32 u32keyLen)
{
    HI_CHAR *value = NULL;
    HI_S32 i;
    HI_CHAR cTmpBuf[2];
    HI_S32 read;

    value = get_config_var(pName);
    if (NULL == value)
    {
        return -1;
    }

    read = strlen (value) > (u32keyLen * 2) ? u32keyLen : (strlen (value) / 2);

    for (i = 0; i < read; i++)
    {
        memset(cTmpBuf, 0, sizeof(cTmpBuf));
        memcpy(cTmpBuf, value + i * 2, 2);

        pKey[i] = strtol(cTmpBuf, NULL, 16);
    }


    return 0;
}

HI_S32 get_cwkey_alg_type(HI_UNF_PLCIPHER_ALG_E *penCwKeyType)
{
    HI_CHAR *value = HI_NULL;

    value = get_config_var("CWKEYTYPE");
    if (HI_NULL == value)
    {
        printf("parse CWKEYTYPE failed\n");
        return -1;
    }

    if (0 == strncmp(value, "AES_CBC", sizeof ("AES_CBC")))
    {
        *penCwKeyType = HI_UNF_PLCIPHER_ALG_AES_CBC;
        return 0;
    }
    else if (0 == strncmp(value, "AES_ECB", sizeof ("AES_ECB")))
    {
        *penCwKeyType = HI_UNF_PLCIPHER_ALG_AES_ECB;
        return 0;
    }
    else if (0 == strncmp(value, "AES_IPTV", sizeof ("AES_IPTV")))
    {
        *penCwKeyType = HI_UNF_PLCIPHER_ALG_AES_IPTV;
        return 0;
    }
    else
    {
        printf("Cw key alg type (%s) is not supported\n", value);
    }

    return -1;
}

HI_S32 get_cwkey_oddeven_type(HI_UNF_PLCIPHER_KEY_EVENODD_E *penCwKeyOddEven)
{
    HI_CHAR *value = HI_NULL;

    value = get_config_var("KEYODDOREVEN");
    if (HI_NULL == value)
    {
        printf("parse KEYODDOREVEN failed\n");
        return -1;
    }

    if (0 == strncmp(value, "ODD", sizeof ("ODD")))
    {
        *penCwKeyOddEven = HI_UNF_PLCIPHER_KEY_ODD;
        return 0;
    }
    else if (0 == strncmp(value, "EVEN", sizeof ("EVEN")))
    {
        *penCwKeyOddEven = HI_UNF_PLCIPHER_KEY_EVEN;
        return 0;
    }
    else
    {
        printf("Cw oddeven key type (%s) is not supported\n", value);
    }

    return -1;
}

