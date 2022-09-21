/******************************************************************************

                  版权所有 (C), 2001-2014, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_proxy_arp.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年7月29日
  最近修改   :
  功能描述   : PROXY ARP
  函数列表   :
  修改历史   :
  1.日    期   : 2014年7月29日
    作    者   : 
    修改内容   : create

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oal_net.h"
#include "wlan_spec.h"
#include "hmac_vap.h"
#include "hmac_ext_if.h"
#include "hmac_proxy_arp.h"
#include "hmac_rx_data.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_PROXYARP_C

/*lint -e778*/ /*lint -e572*/
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/


/*****************************************************************************
 函 数 名  : hmac_proxy_get_mac_by_ipv4
 功能描述  : 通过ipv4的地址获取mac
 输入参数  : pst_hmac_vap: hmac_vap指针
             ul_ipv4:ipv4地址
 输出参数  : puc_mac:mac地址
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_get_mac_by_ipv4(mac_vap_stru *pst_mac_vap, oal_uint32 ul_ipv4, oal_uint8 *puc_mac)
{
    oal_uint32                  ul_user_hash_value;
    hmac_proxy_ipv4_hash_stru  *pst_hash;
    oal_dlist_head_stru        *pst_entry;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap)
                  || (OAL_PTR_NULL == puc_mac)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYARP, "{mac_vap_find_user_by_macaddr::param null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_user_hash_value = HMAC_PROXY_IPV4_HASH(ul_ipv4);

    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_mac_vap->pst_vap_proxyarp->ast_ipv4_head[ul_user_hash_value]))
    {
        pst_hash = (hmac_proxy_ipv4_hash_stru *)pst_entry;
        if (pst_hash->ul_ipv4 != ul_ipv4)
        {
            continue;
        }

        oal_memcopy(puc_mac, pst_hash->auc_mac, WLAN_MAC_ADDR_LEN);

        return OAL_SUCC;
    }

    return OAL_FAIL;
}


/*****************************************************************************
 函 数 名  : hmac_proxy_remove_ipv4
 功能描述  : 将ipv4的地址从hash表中删除
 输入参数  : pst_hmac_vap: hmac_vap指针
             ul_ipv4:ipv4地址
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_remove_ipv4(mac_vap_stru *pst_mac_vap, oal_uint32 ul_ipv4)
{
    oal_uint32                  ul_user_hash_value;
    oal_dlist_head_stru        *pst_entry;
    hmac_proxy_ipv4_hash_stru  *pst_hash;
    oal_dlist_head_stru        *pst_dlist_tmp      = OAL_PTR_NULL;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYARP, "{hmac_proxy_remove_ipv4::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (0 == pst_mac_vap->pst_vap_proxyarp->uc_ipv4_num)
    {
        return OAL_SUCC;
    }

    ul_user_hash_value = HMAC_PROXY_IPV4_HASH(ul_ipv4);

    OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry, pst_dlist_tmp, &(pst_mac_vap->pst_vap_proxyarp->ast_ipv4_head[ul_user_hash_value]))
    {
        pst_hash = (hmac_proxy_ipv4_hash_stru *)pst_entry;

        if (pst_hash->ul_ipv4 != ul_ipv4)
        {
            continue;
        }
        oal_dlist_delete_entry(pst_entry);
        OAL_MEM_FREE(pst_hash, OAL_TRUE);
        pst_mac_vap->pst_vap_proxyarp->uc_ipv4_num--;
        return OAL_SUCC;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : hmac_proxy_add_ipv4
 功能描述  : 将ipv4的地址加入hash表，并记录相应的mac地址
 输入参数  : pst_hmac_vap: hmac_vap指针
             ul_ipv4:ipv4地址
             puc_mac:mac地址
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_add_ipv4(mac_vap_stru *pst_mac_vap, oal_uint32 ul_ipv4, oal_uint8 *puc_mac)
{
    oal_uint32                  ul_user_hash_value;
    hmac_proxy_ipv4_hash_stru  *pst_hash;
    oal_err_code_enum_uint32    en_exist;
    oal_uint8                   auc_mac[OAL_MAC_ADDR_LEN];

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap)
                  || (OAL_PTR_NULL == puc_mac)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYARP, "{hmac_proxy_add_ipv4::param null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 查询是否存在 */
    en_exist = hmac_proxy_get_mac_by_ipv4(pst_mac_vap, ul_ipv4, auc_mac);
    if (OAL_SUCC == en_exist)
    {
        if (!oal_memcmp(auc_mac, puc_mac, OAL_MAC_ADDR_LEN))
        {
            return OAL_SUCC;
        }
        /* 如果来自不同的mac，则将前面记录的结点删除，后面流程将新的结点加入 */
        hmac_proxy_remove_ipv4(pst_mac_vap, ul_ipv4);
    }

    if (MAC_VAP_USER_HASH_MAX_VALUE <= pst_mac_vap->pst_vap_proxyarp->uc_ipv4_num)
    {
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    /* 申请内存 */
    pst_hash = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(hmac_proxy_ipv4_hash_stru), OAL_TRUE);
    if (OAL_PTR_NULL == pst_hash)
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYARP, "hmac_proxy_add_ipv4 err! melloc err!");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 填写 */
    pst_hash->ul_ipv4 = ul_ipv4;
    oal_memcopy(pst_hash->auc_mac, puc_mac, OAL_MAC_ADDR_LEN);

    /* 加入hash表 */
    ul_user_hash_value = HMAC_PROXY_IPV4_HASH(ul_ipv4);
    oal_dlist_add_head(&(pst_hash->st_entry), &(pst_mac_vap->pst_vap_proxyarp->ast_ipv4_head[ul_user_hash_value]));
    pst_mac_vap->pst_vap_proxyarp->uc_ipv4_num++;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_proxy_get_mac_by_ipv6
 功能描述  : 通过ipv6的地址获取mac
 输入参数  : pst_hmac_vap: hmac_vap指针
             puc_ipv6:ipv6地址
 输出参数  : puc_mac:mac地址
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_get_mac_by_ipv6(mac_vap_stru *pst_mac_vap, oal_in6_addr *pst_ipv6, oal_uint8 *puc_mac)
{
    oal_uint32                  ul_user_hash_value;
    hmac_proxy_ipv6_hash_stru  *pst_hash;
    oal_dlist_head_stru        *pst_entry;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap)
                  || (OAL_PTR_NULL == pst_ipv6)
                  || (OAL_PTR_NULL == puc_mac)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYARP, "{hmac_proxy_get_mac_by_ipv6::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_user_hash_value = HMAC_PROXY_IPV6_HASH(pst_ipv6);

    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_mac_vap->pst_vap_proxyarp->ast_ipv6_head[ul_user_hash_value]))
    {
        pst_hash = (hmac_proxy_ipv6_hash_stru *)pst_entry;

        if (oal_memcmp(pst_ipv6, &pst_hash->st_ipv6, OAL_SIZEOF(oal_in6_addr)))
        {
            continue;
        }
        oal_memcopy(puc_mac, pst_hash->auc_mac, WLAN_MAC_ADDR_LEN);
        return OAL_SUCC;
    }

    return OAL_FAIL;
}

/*****************************************************************************
 函 数 名  : hmac_proxy_remove_ipv6
 功能描述  : 将ipv6的地址从hash表中删除
 输入参数  : pst_hmac_vap: hmac_vap指针
             ul_ipv6:ipv6地址
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_remove_ipv6(mac_vap_stru *pst_mac_vap, oal_in6_addr *pst_ipv6)
{
    oal_uint32                  ul_user_hash_value;
    oal_dlist_head_stru        *pst_entry;
    hmac_proxy_ipv6_hash_stru  *pst_hash;
    oal_dlist_head_stru        *pst_dlist_tmp      = OAL_PTR_NULL;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYARP, "{hmac_proxy_remove_ipv4::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (0 == pst_mac_vap->pst_vap_proxyarp->uc_ipv6_num)
    {
        return OAL_SUCC;
    }

    ul_user_hash_value = HMAC_PROXY_IPV6_HASH(pst_ipv6);

    OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry, pst_dlist_tmp, &(pst_mac_vap->pst_vap_proxyarp->ast_ipv6_head[ul_user_hash_value]))
    {
        pst_hash = (hmac_proxy_ipv6_hash_stru *)pst_entry;

        if (oal_memcmp(pst_ipv6, &pst_hash->st_ipv6, OAL_SIZEOF(oal_in6_addr)))
        {
            continue;
        }
        oal_dlist_delete_entry(pst_entry);
        OAL_MEM_FREE(pst_hash, OAL_TRUE);
        pst_mac_vap->pst_vap_proxyarp->uc_ipv6_num--;
        return OAL_SUCC;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : hmac_proxy_add_ipv6
 功能描述  : 将ipv6的地址加入hash表，并记录相应的mac地址
 输入参数  : pst_hmac_vap: hmac_vap指针
             puc_ipv6:ipv6地址
             puc_mac:mac地址
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_add_ipv6(mac_vap_stru *pst_mac_vap, oal_in6_addr *pst_ipv6, oal_uint8 *puc_mac)
{
    oal_uint32                  ul_user_hash_value;
    hmac_proxy_ipv6_hash_stru  *pst_hash;
    oal_err_code_enum_uint32    en_exist;
    oal_uint8                   auc_mac[OAL_MAC_ADDR_LEN];
    oal_uint8                   auc_ipv6_zero_addr[16] = {0};

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap)
                  || (OAL_PTR_NULL == puc_mac)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYARP, "{hmac_proxy_add_ipv6::param null.}");

        return OAL_ERR_CODE_PROXY_ND_LEARN_USR_FAIL_INCOMP;
    }

    if (!oal_memcmp(auc_ipv6_zero_addr, pst_ipv6, OAL_SIZEOF(oal_in6_addr)))
    {
        return OAL_ERR_CODE_PROXY_ND_LEARN_USR_SUCC_COMP;
    }

    /* 查询是否存在,如果存在，看是否来自同一个mac */
    en_exist = hmac_proxy_get_mac_by_ipv6(pst_mac_vap, pst_ipv6, auc_mac);
    if (OAL_SUCC == en_exist)
    {
        if (!oal_memcmp(auc_mac, puc_mac, OAL_MAC_ADDR_LEN))
        {
            return OAL_ERR_CODE_PROXY_ND_LEARN_USR_SUCC_COMP;
        }

        /* 如果来自不同的mac，则将前面记录的结点删除，后面流程将新的结点加入 */
        hmac_proxy_remove_ipv6(pst_mac_vap, pst_ipv6);
    }

    if (MAC_VAP_USER_HASH_MAX_VALUE <= pst_mac_vap->pst_vap_proxyarp->uc_ipv6_num)
    {
        return OAL_ERR_CODE_PROXY_ND_LEARN_USR_FAIL_INCOMP;
    }

    /* 申请 */
    pst_hash = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(hmac_proxy_ipv6_hash_stru), OAL_TRUE);
    if (OAL_PTR_NULL == pst_hash)
    {
        return OAL_ERR_CODE_PROXY_ND_LEARN_USR_FAIL_INCOMP;
    }

    /* 填写 */
    pst_hash->st_ipv6 = *pst_ipv6;
    oal_memcopy(pst_hash->auc_mac, puc_mac, OAL_MAC_ADDR_LEN);

    /* 加入hash表 */
    ul_user_hash_value  = 0;
    ul_user_hash_value = HMAC_PROXY_IPV6_HASH(&pst_hash->st_ipv6);
    oal_dlist_add_head(&(pst_hash->st_entry), &pst_mac_vap->pst_vap_proxyarp->ast_ipv6_head[ul_user_hash_value]);
    pst_mac_vap->pst_vap_proxyarp->uc_ipv6_num++;
    return OAL_ERR_CODE_PROXY_ND_LEARN_USR_SUCC_COMP;
}

/*****************************************************************************
 函 数 名  : hmac_proxy_remove_mac
 功能描述  : 通过mac地址将对应ipv4和ipv6 结点删除
 输入参数  : pst_mac_vap: mac_vap指针
             puc_mac:mac地址
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_remove_mac(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac)
{
    oal_dlist_head_stru        *pst_entry;
    hmac_proxy_ipv4_hash_stru  *pst_hash_ipv4;
    hmac_proxy_ipv6_hash_stru  *pst_hash_ipv6;
    oal_dlist_head_stru        *pst_dlist_tmp      = OAL_PTR_NULL;
    oal_uint32                  ul_loop = 0;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYARP, "{hmac_proxy_remove_mac::vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_LIKELY(OAL_PTR_NULL == pst_mac_vap->pst_vap_proxyarp))
    {
        OAM_INFO_LOG0(0, OAM_SF_PROXYARP, "{hmac_proxy_remove_mac::proxyarp null.}");
        return OAL_SUCC;
    }

    if (WLAN_VAP_MODE_BSS_AP != pst_mac_vap->en_vap_mode)
    {
        return OAL_SUCC;
    }

    if (0 < pst_mac_vap->pst_vap_proxyarp->uc_ipv6_num)
    {
        for (ul_loop = 0; ul_loop < MAC_VAP_USER_HASH_MAX_VALUE; ul_loop++)
        {
            OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry, pst_dlist_tmp, &(pst_mac_vap->pst_vap_proxyarp->ast_ipv6_head[ul_loop]))
            {
                pst_hash_ipv6 = (hmac_proxy_ipv6_hash_stru *)pst_entry;
                if (oal_memcmp(puc_mac, &pst_hash_ipv6->auc_mac, OAL_MAC_ADDR_LEN))
                {
                    continue;
                }

                oal_dlist_delete_entry(pst_entry);
                OAL_MEM_FREE(pst_hash_ipv6, OAL_TRUE);
                pst_mac_vap->pst_vap_proxyarp->uc_ipv6_num--;
                break;
            }
        }
    }

    if (0 < pst_mac_vap->pst_vap_proxyarp->uc_ipv4_num)
    {
        for (ul_loop = 0; ul_loop < MAC_VAP_USER_HASH_MAX_VALUE; ul_loop++)
        {
            OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry, pst_dlist_tmp, &(pst_mac_vap->pst_vap_proxyarp->ast_ipv4_head[ul_loop]))
            {
                pst_hash_ipv4 = (hmac_proxy_ipv4_hash_stru *)pst_entry;
                if (oal_memcmp(puc_mac, &pst_hash_ipv4->auc_mac, OAL_MAC_ADDR_LEN))
                {
                    continue;
                }

                oal_dlist_delete_entry(pst_entry);
                OAL_MEM_FREE(pst_hash_ipv4, OAL_TRUE);
                pst_mac_vap->pst_vap_proxyarp->uc_ipv4_num--;
                break;
            }
        }
    }
    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : hmac_proxy_debug_record
 功能描述  : 记录调试信息
 输入参数  : pst_mac_vap: hmac_vap指针
             puc_mac_src: mac指针
             puc_mac_dst: mac指针
             uc_dir:帧的发送方向 0-空口 1-eth
             uc_type:帧类型
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
#ifdef _PRE_DEBUG_MODE
oal_void hmac_proxy_debug_record(mac_vap_stru *pst_mac_vap, mac_ether_header_stru *pst_eth_hdr, oal_uint16 us_type, oal_err_code_enum_uint32 en_rst)
{
    mac_vap_proxyarp_stru           *pst_vap_proxyarp;
    oal_uint32                       ul_idx;
    if(OAL_ERR_CODE_PROXY_OTHER_INCOMP == en_rst)
    {
        return;
    }

    if (OAL_PTR_NULL == pst_mac_vap->pst_vap_proxyarp)
    {
        return;
    }

    pst_vap_proxyarp = pst_mac_vap->pst_vap_proxyarp;
    ul_idx = pst_vap_proxyarp->us_idx_cur % MAC_VAP_USER_HASH_MAX_VALUE;

    /* 记录以太头 */
    pst_vap_proxyarp->ast_vap_proxyarp_dbg[ul_idx].st_eth_hdr = *pst_eth_hdr;
    pst_vap_proxyarp->ast_vap_proxyarp_dbg[ul_idx].us_type = us_type;
    pst_vap_proxyarp->ast_vap_proxyarp_dbg[ul_idx].en_rst = en_rst;
    pst_vap_proxyarp->ast_vap_proxyarp_dbg[ul_idx].us_proxy_num = pst_vap_proxyarp->us_idx_cur;
    pst_vap_proxyarp->us_idx_cur++;
}
#endif

/*****************************************************************************
 函 数 名  : hmac_proxy_arp_rcv_req
 功能描述  : 处理接收到的arp req
 输入参数  : pst_hmac_vap: hmac_vap指针
             pst_arp_hdr:skb指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_arp_rcv_req(mac_vap_stru *pst_mac_vap, oal_net_device_stru *pst_dev, oal_eth_arphdr_stru *pst_arp_hdr)
{

    oal_uint32                  ul_src_ipv4 = 0;
    oal_uint8                   auc_src_mac[ETHER_ADDR_LEN];
    oal_uint32                  ul_tgt_ipv4 = 0;
    oal_uint8                   auc_tgt_mac[ETHER_ADDR_LEN];
    oal_uint16                  us_usr_idx;
    oal_err_code_enum_uint32    en_err = OAL_SUCC;
    oal_netbuf_stru            *pst_netbuff;
    oal_uint32                  ul_ret = 0;

    oal_err_code_enum_uint32    en_rst = 0;
    mac_ether_header_stru       st_eth_hdr;
    oal_memcopy(auc_src_mac, pst_arp_hdr->auc_ar_sha, ETHER_ADDR_LEN);
    oal_memcopy(&ul_src_ipv4, pst_arp_hdr->auc_ar_sip, ETH_SENDER_IP_ADDR_LEN);
    oal_memcopy(&ul_tgt_ipv4, pst_arp_hdr->auc_ar_tip, ETH_TARGET_IP_ADDR_LEN);

    /* GARP,进行地址学习 */
    if (ul_src_ipv4 == ul_tgt_ipv4)
    {
        //hmac_proxy_learn();
        if (OAL_SUCC != mac_vap_find_user_by_macaddr(pst_mac_vap, auc_src_mac, &us_usr_idx))
        {
            return OAL_ERR_CODE_PROXY_ARP_LEARN_USR_NOTEXIST_COMP;
        }

        hmac_proxy_add_ipv4(pst_mac_vap, ul_src_ipv4, auc_src_mac);

        return OAL_ERR_CODE_PROXY_ARP_LEARN_USR_COMP;
    }

    /* 将目的地址不是本BSS的ARP REQ过滤掉 */
    en_err = hmac_proxy_get_mac_by_ipv4(pst_mac_vap, ul_tgt_ipv4, auc_tgt_mac);
    if (OAL_SUCC != en_err)
    {
        return OAL_ERR_CODE_PROXY_ARP_FINDUSR_ERR_COMP;
    }


    pst_netbuff = oal_arp_create(OAL_ARPOP_REPLY, ETHER_TYPE_ARP, ul_src_ipv4, pst_dev, ul_tgt_ipv4,
                                         auc_src_mac, auc_tgt_mac, auc_src_mac);
    if (!pst_netbuff)
    {
        return OAL_ERR_CODE_PROXY_ARP_CREATE_FAIL_COMP;
    }

    pst_netbuff->dev = pst_dev;

#ifdef _PRE_WLAN_DFT_DUMP_FRAME
    oal_netbuf_pull(pst_netbuff, 14);
    hmac_rx_report_eth_frame(pst_mac_vap, pst_netbuff);
    oal_netbuf_push(pst_netbuff, 14);
#endif


    /* 记录一下，用来做后面的打印 */
    st_eth_hdr = *(mac_ether_header_stru *)oal_netbuf_data(pst_netbuff);

    /* 找到用户，使用空口发送 */
    if (OAL_SUCC == mac_vap_find_user_by_macaddr(pst_mac_vap, auc_src_mac, &us_usr_idx))
    {
        /* data指针指向的是以太头 */
        ul_ret = hmac_tx_lan_to_wlan(pst_mac_vap, pst_netbuff);
        if (OAL_SUCC != ul_ret)
        {

            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PROXYARP, "{hmac_proxy_arp_rcv_req 2wlan Err[%u]!!}", ul_ret);
            oal_netbuf_free(pst_netbuff);
            pst_netbuff = OAL_PTR_NULL;
        }

        en_rst = OAL_ERR_CODE_PROXY_ARP_REPLY2BSS_COMP;
    }
    else
    {
        /* 送给网桥，需要pull一下，让data指针指向arp头 */
        OAL_NETBUF_PROTOCOL(pst_netbuff) = oal_eth_type_trans(pst_netbuff, pst_dev);

        /* 交给网桥*/
        ul_ret = (oal_uint32)oal_netif_rx(pst_netbuff);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PROXYARP, "{hmac_proxy_arp_rcv_req 2br Err[%u]!!}", ul_ret);
        }

        en_rst = OAL_ERR_CODE_PROXY_ARP_REPLY2ETH_COMP;

    }

#ifdef _PRE_DEBUG_MODE
    hmac_proxy_debug_record(pst_mac_vap, &st_eth_hdr, OAL_ARPOP_REPLY, en_rst);
#endif
    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_PROXYARP, "hmac_proxy_arp_rcv_req! s:%x->d:%x type %x, result %u!",
                        st_eth_hdr.auc_ether_shost[ETHER_ADDR_LEN - 1],
                        st_eth_hdr.auc_ether_dhost[ETHER_ADDR_LEN - 1],
                        OAL_ARPOP_REPLY,
                        en_rst);

    return en_rst;
}

/*****************************************************************************
 函 数 名  : hmac_proxy_arp_rcv_reply
 功能描述  : 处理接收到的arp reply
 输入参数  : pst_hmac_vap: hmac_vap指针
             oal_netbuf_stru:skb指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_arp_rcv_reply(mac_vap_stru *pst_mac_vap, oal_eth_arphdr_stru *pst_arp_hdr, oal_uint8 uc_is_mcst)
{
    oal_uint16                  us_usr_idx = 0;
    if (uc_is_mcst)
    {
        return OAL_ERR_CODE_PROXY_ARP_REPLY_MCAST_COMP;
    }

    /* 如果接口上线不发GARP,通过arp reply将arp reply发送端的ip和mac记下来 */
    if (OAL_SUCC == mac_vap_find_user_by_macaddr(pst_mac_vap, pst_arp_hdr->auc_ar_sha, &us_usr_idx))
    {
        hmac_proxy_add_ipv4(pst_mac_vap, *(oal_uint32 *)pst_arp_hdr->auc_ar_sip, pst_arp_hdr->auc_ar_sha);
    }

    return OAL_ERR_CODE_PROXY_ARP_REPLY_INCOMP;
}

/*****************************************************************************
 函 数 名  : hmac_proxy_arp
 功能描述  : 处理接收到的arp req和arp reply
 输入参数  : pst_hmac_vap: hmac_vap指针
             oal_netbuf_stru:skb指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_arp(mac_vap_stru *pst_mac_vap, oal_net_device_stru *pst_dev, oal_netbuf_stru *pst_buf)
{
    mac_ether_header_stru       *pst_ether_hdr; /* 以太网头 */
    oal_uint32                   ul_arp_hdr_len = 0;
    oal_eth_arphdr_stru         *pst_arp_hdr;
    oal_uint8                    uc_is_mcst = 0;
    mac_ether_header_stru       st_eth_hdr;

    pst_ether_hdr   = (mac_ether_header_stru *)oal_netbuf_data(pst_buf);
    pst_arp_hdr     = (oal_eth_arphdr_stru *)(pst_ether_hdr + 1);

    ul_arp_hdr_len       = OAL_SIZEOF(oal_eth_arphdr_stru) + OAL_SIZEOF(mac_ether_header_stru);

    /* 此处判断skb中，是否已经有足够的空间保存了eth hdr + arp hdr的信息 */
    if (!oal_pskb_may_pull(pst_buf, ul_arp_hdr_len))
    {
        return OAL_ERR_CODE_PROXY_ARP_INVLD_SKB_INCOMP;
    }

    st_eth_hdr = *(mac_ether_header_stru *)oal_netbuf_data(pst_buf);
#ifdef _PRE_DEBUG_MODE
    hmac_proxy_debug_record(pst_mac_vap, &st_eth_hdr, pst_arp_hdr->us_ar_op, 0);
#endif
    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_PROXYARP, "hmac_proxy_arp! s:%x->d:%x type %x, result %u!",
                        st_eth_hdr.auc_ether_shost[ETHER_ADDR_LEN - 1],
                        st_eth_hdr.auc_ether_dhost[ETHER_ADDR_LEN - 1],
                        pst_arp_hdr->us_ar_op,
                        0);

    if (OAL_HOST2NET_SHORT(OAL_ARPOP_REQUEST) == pst_arp_hdr->us_ar_op)
    {
        return hmac_proxy_arp_rcv_req(pst_mac_vap, pst_dev, pst_arp_hdr);
    }
    else if (OAL_HOST2NET_SHORT(OAL_ARPOP_REPLY) == pst_arp_hdr->us_ar_op)
    {
        uc_is_mcst = ETHER_IS_MULTICAST(pst_ether_hdr->auc_ether_dhost);
        return hmac_proxy_arp_rcv_reply(pst_mac_vap, pst_arp_hdr, uc_is_mcst);
    }

    return OAL_ERR_CODE_PROXY_ARP_NOT_REQ_REPLY_INCOMP;
}

/*****************************************************************************
 函 数 名  : hmac_proxy_nd_learn_from_ns
 功能描述  : 通过DAD学习地址
 输入参数  : pst_hmac_vap: hmac_vap指针
             oal_netbuf_stru:skb指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_nd_learn_from_ns(mac_vap_stru *pst_mac_vap, oal_in6_addr *pst_ipv6_src, oal_uint8 *puc_mac_src)
{
    oal_uint16                  us_usr_idx = 0;
    oal_uint8                   auc_mac[ETHER_ADDR_LEN];
    oal_err_code_enum_uint32    en_err = OAL_SUCC;

    if (OAL_SUCC != mac_vap_find_user_by_macaddr(pst_mac_vap, puc_mac_src, &us_usr_idx))
    {
        return OAL_ERR_CODE_PROXY_ND_LEARN_USR_NOTEXIST_COMP;
    }

    /* 检查ipv6的地址已经存在,并且mac地址不相等，则将此帧发送出去，进行DAD检测 */
    en_err = hmac_proxy_get_mac_by_ipv6(pst_mac_vap, pst_ipv6_src, auc_mac);
    if ((OAL_SUCC == en_err)
        && (oal_memcmp(puc_mac_src, auc_mac, OAL_MAC_ADDR_LEN)))
    {
        return OAL_ERR_CODE_PROXY_ND_LEARN_USR_ALREADY_EXIST_INCOMP;
    }

    return hmac_proxy_add_ipv6(pst_mac_vap, pst_ipv6_src, puc_mac_src);
}

/*****************************************************************************
 函 数 名  : hmac_proxy_create_na
 功能描述  : 构造NA，用以代理回复NS
 输入参数  : pst_hmac_vap: hmac_vap指针
             pst_ether_hdr:指向接收到skb的以太头
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 说     明 :
 修改历史      :
  1.日    期   : 2014年7月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
 oal_netbuf_stru *hmac_proxy_create_na(oal_net_device_stru *pst_net_dev, oal_uint8 *puc_src_mac, oal_uint8 *puc_dst_mac, oal_uint8 *puc_src_ipv6, oal_uint8 *puc_dst_ipv6)
{
    oal_netbuf_stru             *pst_netbuff = OAL_PTR_NULL;
    oal_uint32                   ul_size = 0;
    oal_ipv6hdr_stru            *pst_ipv6;
    oal_nd_msg_stru             *pst_nd;

    /* sizeof(oal_nd_msg_stru)比实际多了4字节，最后加8字节是因为NA的option长8字节。add by: */
    ul_size = OAL_LL_ALLOCATED_SPACE(pst_net_dev) + sizeof(oal_ipv6hdr_stru) + (sizeof(oal_nd_msg_stru) - 4) + 8;
    pst_netbuff  = oal_netbuf_alloc(ul_size, 0, WLAN_MEM_NETBUF_ALIGN);
    if (OAL_PTR_NULL == pst_netbuff)
    {
        return OAL_PTR_NULL;
    }

    pst_netbuff->dev = pst_net_dev;
    pst_netbuff->protocol = OAL_HOST2NET_SHORT(ETHER_TYPE_IPV6);
    oal_netbuf_reserve(pst_netbuff, OAL_LL_ALLOCATED_SPACE(pst_net_dev));

    pst_ipv6 = (oal_ipv6hdr_stru *)oal_netbuf_put(pst_netbuff, OAL_SIZEOF(oal_ipv6hdr_stru));

    /* skb->len加上nd_msg的长度 */
    oal_netbuf_put(pst_netbuff, (sizeof(oal_nd_msg_stru) - 4) + 8);
    pst_nd = (oal_nd_msg_stru *)(pst_ipv6 + 1);

    /* 1. 填写以太头 */
    if (oal_dev_hard_header(pst_netbuff, pst_netbuff->dev, ETHER_TYPE_IPV6, puc_dst_mac,
                                        puc_src_mac, pst_netbuff->len) < 0)
    {
        oal_netbuf_free(pst_netbuff);
        return OAL_PTR_NULL;
    }

    /* 2. 填写IPV6头 */
    *(oal_uint32 *)pst_ipv6 = OAL_HOST2NET_LONG(0x60000000);
    pst_ipv6->payload_len = OAL_HOST2NET_SHORT((sizeof(oal_nd_msg_stru) - 4) + 8);
    pst_ipv6->nexthdr = OAL_IPPROTO_ICMPV6;
    pst_ipv6->hop_limit = 0xff;
    oal_ipv6_addr_copy(&pst_ipv6->daddr, (oal_in6_addr *)puc_dst_ipv6);
    oal_ipv6_addr_copy(&pst_ipv6->saddr, (oal_in6_addr *)puc_src_ipv6);

    /* 3. 填写ICMPV6 邻居发现协议的NA*/
    OAL_MEMZERO(&pst_nd->icmph, OAL_SIZEOF(oal_icmp6hdr_stru));
    pst_nd->icmph.icmp6_type = OAL_NDISC_NEIGHBOUR_ADVERTISEMENT;
    pst_nd->icmph.icmp6_solicited = 1;
    oal_ipv6_addr_copy(&pst_nd->target, (oal_in6_addr *)puc_src_ipv6);
    /* ICMPv6 选项 */
    pst_nd->opt[0] = OAL_ND_OPT_TARGET_LL_ADDR;
    /*lint -e415*/ /*lint -e416*/
    pst_nd->opt[1] = 1;
    oal_memcopy(&pst_nd->opt[2], puc_src_mac, OAL_MAC_ADDR_LEN);
    /*lint +e415*/ /*lint +e416*/
    pst_nd->icmph.icmp6_cksum = oal_csum_ipv6_magic(&pst_ipv6->saddr,
                &pst_ipv6->daddr, (OAL_SIZEOF(*pst_nd) - 4) + 8, OAL_IPPROTO_ICMPV6,
                oal_csum_partial(&pst_nd->icmph, (OAL_SIZEOF(*pst_nd) - 4) + 8, 0));

    return pst_netbuff;
}

/*****************************************************************************
 函 数 名  : hmac_proxy_get_mac_from_opt
 功能描述  : 从icmpv6 option中获取ipv6地址
 输入参数  : puc_opt:  ipmpv6 option指针
             l_optlen: ipmpv6 option长度
             en_src:   标识获取源链路地址还是目的链路地址 1-源 0-目的
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 说     明 :
 修改历史      :
  1.日    期   : 2014年7月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
/*lint  -e574*/
oal_uint8 *hmac_proxy_get_mac_from_opt(oal_uint8 *puc_opt, oal_int32 l_optlen, oal_bool_enum_uint8 en_src)
{
    oal_nd_opt_hdr *pst_ndopt;
    oal_int32       l_ndoptlen;
    oal_uint32      ul_offset;
    oal_int32       l_optlen_tmp;

    pst_ndopt = (oal_nd_opt_hdr *)puc_opt;
    l_optlen_tmp = l_optlen;

    while (0 < l_optlen_tmp)
    {
        if (l_optlen_tmp < (oal_int32)OAL_SIZEOF(oal_nd_opt_hdr))
        {
            return OAL_PTR_NULL;
        }
        l_ndoptlen = pst_ndopt->nd_opt_len << 3;
        if (l_optlen_tmp < l_ndoptlen || l_ndoptlen == 0)
        {
            return OAL_PTR_NULL;
        }

        switch (pst_ndopt->nd_opt_type)
        {
            case OAL_ND_OPT_TARGET_LL_ADDR: /* NA中使用 */
            {
                if (!en_src)
                {
                    return (oal_uint8 *)(pst_ndopt + 1);
                }

                break;
            }

            /* 发送者的链路层地址 */
            case OAL_ND_OPT_SOURCE_LL_ADDR:/* NS中使用 */
            {
                if (en_src)
                {
                    return (oal_uint8 *)(pst_ndopt + 1);
                }

                break;
            }
            default:
            {
                OAM_WARNING_LOG1(0, OAM_SF_PROXYARP, "{hmac_proxy_get_mac_from_opt::type [%d].}", pst_ndopt->nd_opt_type);
                break;
            }
        }

        l_optlen_tmp -= l_ndoptlen;
        ul_offset = (oal_uint32)l_ndoptlen;
        pst_ndopt = (oal_nd_opt_hdr *)((oal_uint8 *)pst_ndopt + ul_offset);
    }

    return OAL_PTR_NULL;
}
/*lint  +e574*/

/*****************************************************************************
 函 数 名  : hmac_proxy_nd_rcv_ns
 功能描述  : 处理接收到的NS
 输入参数  : pst_hmac_vap: hmac_vap指针
             oal_netbuf_stru:skb指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 说     明 :构造NA时，注意: NS源->NA目的
                            NS目的->NA源
 修改历史      :
  1.日    期   : 2014年7月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_nd_rcv_ns(mac_vap_stru *pst_mac_vap, oal_net_device_stru *pst_dev, mac_ether_header_stru *pst_ether_hdr, oal_int32 l_opt_len)
{
    oal_ipv6hdr_stru        *pst_ipv6_hdr;
    oal_int32                l_src_type;
    oal_int32                l_dst_type;
    oal_nd_msg_stru         *pst_msg;
    oal_uint8               *pst_src_mac;
    oal_uint8                ast_dst_mac[ETHER_ADDR_LEN];
    oal_netbuf_stru         *pst_netbuff;
    oal_uint16               us_idx;
    oal_uint32               ul_ret;
    oal_int32                l_netifrx_rst;
    oal_err_code_enum_uint32 en_rst;
    mac_ether_header_stru    st_eth_hdr;

    pst_ipv6_hdr        = (oal_ipv6hdr_stru *)(pst_ether_hdr + 1);
    l_src_type          = oal_ipv6_addr_type(&pst_ipv6_hdr->saddr);
    l_dst_type          = oal_ipv6_addr_type(&pst_ipv6_hdr->daddr);
    pst_msg             = (oal_nd_msg_stru *)(pst_ipv6_hdr + 1);

    /* DAD检测 */
    if ((l_src_type == (oal_int32)OAL_IPV6_ADDR_ANY) && (l_dst_type & (oal_int32)OAL_IPV6_ADDR_MULTICAST))
    {
        return hmac_proxy_nd_learn_from_ns(pst_mac_vap, &pst_msg->target, pst_ether_hdr->auc_ether_shost);
    }

    /* 获取NS的icmpv6选项中携带的mac地址，即此帧发送者的mac地址 */
    pst_src_mac = hmac_proxy_get_mac_from_opt(pst_msg->opt, l_opt_len, OAL_TRUE);
    if (OAL_PTR_NULL == pst_src_mac)
    {
        return OAL_ERR_CODE_PROXY_ND_NS_OPT_INVLD_COMP;
    }

    if (OAL_SUCC != hmac_proxy_get_mac_by_ipv6(pst_mac_vap, &pst_msg->target, ast_dst_mac))
    {
        return OAL_ERR_CODE_PROXY_ND_NS_FINDUSR_ERR_COMP;
    }

    /* 构造NA*/
    pst_netbuff = hmac_proxy_create_na(pst_dev, ast_dst_mac, pst_src_mac, (oal_uint8 *)&pst_msg->target, (oal_uint8 *)&pst_ipv6_hdr->saddr);
    if (OAL_PTR_NULL == pst_netbuff)
    {
        return OAL_ERR_CODE_PROXY_ND_NS_CREATE_NA_FAIL_COMP;
    }

#ifdef _PRE_WLAN_DFT_DUMP_FRAME
    oal_netbuf_pull(pst_netbuff, 14);
    hmac_rx_report_eth_frame(pst_mac_vap, pst_netbuff);
    oal_netbuf_push(pst_netbuff, 14);
#endif

    st_eth_hdr = *(mac_ether_header_stru *)oal_netbuf_data(pst_netbuff);

    /* 没找到将skb上桥，找到了就直接空口发送 */
    if (OAL_SUCC == mac_vap_find_user_by_macaddr(pst_mac_vap, pst_src_mac, &us_idx))
    {
        ul_ret = hmac_tx_lan_to_wlan(pst_mac_vap, pst_netbuff);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PROXYARP, "{hmac_proxy_nd_rcv_ns 2wlan Err[%u]!!}", ul_ret);

            oal_netbuf_free(pst_netbuff);

            pst_netbuff = OAL_PTR_NULL;
        }

        en_rst = OAL_ERR_CODE_PROXY_ND_NS_REPLY_NA2BSS_COMP;
    }
    else
    {
        OAL_NETBUF_PROTOCOL(pst_netbuff) = oal_eth_type_trans(pst_netbuff, pst_dev);

        l_netifrx_rst = oal_netif_rx(pst_netbuff);
        if (OAL_SUCC != l_netifrx_rst)
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PROXYARP, "{hmac_proxy_nd_rcv_ns 2br Err[%d]!!}", l_netifrx_rst);
        }

        en_rst = OAL_ERR_CODE_PROXY_ND_NS_REPLY_NA2ETH_COMP;
    }

#ifdef _PRE_DEBUG_MODE
    hmac_proxy_debug_record(pst_mac_vap, &st_eth_hdr, OAL_NDISC_NEIGHBOUR_ADVERTISEMENT, en_rst);
#endif
    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_PROXYARP, "hmac_proxy_nd_rcv_ns! s:%x->d:%x type %x, result %u!",
                        st_eth_hdr.auc_ether_shost[ETHER_ADDR_LEN - 1],
                        st_eth_hdr.auc_ether_dhost[ETHER_ADDR_LEN - 1],
                        OAL_NDISC_NEIGHBOUR_ADVERTISEMENT,
                        en_rst);

    return en_rst;
}

/*****************************************************************************
 函 数 名  : hmac_proxy_ipv6_addr_is_mcast
 功能描述  : 判断ipv6的地址是不是组播地址
 输入参数  : pst_hmac_vap: hmac_vap指针
             pst_buf:      skb指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 说    明  :ipv6地址 ff02:xxxx:xxxx  最高为ff，表示组播

 修改历史      :
  1.日    期   : 2014年7月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hmac_proxy_ipv6_addr_is_mcast(oal_in6_addr *pst_addr)
{
    return (pst_addr->s6_addr32[0] & OAL_HOST2NET_LONG(0xFF000000)) == OAL_HOST2NET_LONG(0xFF000000);
}

/*****************************************************************************
 函 数 名  : hmac_proxy_nd_rcv_na
 功能描述  : 处理NA
 输入参数  : pst_hmac_vap: hmac_vap指针
             pst_buf:      skb指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 说    明  : 1.NA响应单播请求时S置位,可以带可以不带链路地址
             2.NA响应组播请求时,S不置位，target填成多播，必须要带链路地址
 修改历史      :
  1.日    期   : 2014年7月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_nd_rcv_na(mac_vap_stru *pst_mac_vap, mac_ether_header_stru *pst_ether_hdr, oal_int32 l_opt_len)
{
    oal_ipv6hdr_stru            *pst_ipv6_hdr;
    oal_icmp6hdr_stru           *pst_icmp6;
    oal_bool_enum_uint8          en_solicited;
    oal_nd_msg_stru             *pst_nd;
    oal_uint8                   *puc_src_mac;
    oal_err_code_enum_uint32     en_err;
    oal_uint16                   us_usr_idx = 0;

    pst_ipv6_hdr        = (oal_ipv6hdr_stru *)(pst_ether_hdr + 1);
    pst_icmp6           = (oal_icmp6hdr_stru *)(pst_ipv6_hdr + 1);
    pst_nd              = (oal_nd_msg_stru *)pst_icmp6;

    /* S在响应组播ns时不应该置位 */
    if ((pst_nd->icmph.icmp6_dataun.u_nd_advt.solicited)
    && hmac_proxy_ipv6_addr_is_mcast(&pst_nd->target))
    {
        return OAL_ERR_CODE_PROXY_ND_NA_INVLD_COMP;
    }

    en_solicited = (pst_nd->icmph.icmp6_dataun.u_nd_advt.solicited) && !(hmac_proxy_ipv6_addr_is_mcast(&pst_nd->target));

    puc_src_mac = hmac_proxy_get_mac_from_opt(pst_nd->opt, l_opt_len, OAL_FALSE);
    if (OAL_PTR_NULL == puc_src_mac)
    {
        if (en_solicited)
        {
            return OAL_ERR_CODE_PROXY_ND_NA_UCAST_NOT_LLA_INCOMP;

        }

        return OAL_ERR_CODE_PROXY_ND_NA_MCAST_NOT_LLA_COMP;
    }
    /* 从NA中学习一下地址 */
    if (OAL_SUCC == mac_vap_find_user_by_macaddr(pst_mac_vap, puc_src_mac, &us_usr_idx))
    {
        en_err = hmac_proxy_add_ipv6(pst_mac_vap, &pst_nd->target, puc_src_mac);
        if(OAL_ERR_CODE_PROXY_ND_LEARN_USR_SUCC_COMP != en_err)
        {
            return en_err;
        }
    }

    if (en_solicited)
    {
        return OAL_ERR_CODE_PROXY_ND_NA_SOLICITED_INCOMP;
    }

    return OAL_ERR_CODE_PROXY_ND_NA_UNSOLICITED_COMP;

}

/*****************************************************************************
 函 数 名  : hmac_proxy_nd
 功能描述  : 处理接收到的NS和NA
 输入参数  : pst_hmac_vap: hmac_vap指针
             oal_netbuf_stru:skb指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_nd(mac_vap_stru *pst_mac_vap, oal_net_device_stru *pst_dev, oal_netbuf_stru *pst_buf)
{
    mac_ether_header_stru       *pst_ether_hdr; /* 以太网头 */
    oal_ipv6hdr_stru            *pst_ipv6_hdr;
    oal_icmp6hdr_stru           *pst_icmp6;
    oal_uint32                   ul_hdr_len;
    oal_uint32                   ul_opt_len;         /* icmpv6选项的长度 */
    pst_ether_hdr   = (mac_ether_header_stru *)oal_netbuf_data(pst_buf);
    pst_ipv6_hdr    = (oal_ipv6hdr_stru *)(pst_ether_hdr + 1);
    pst_icmp6       = (oal_icmp6hdr_stru *)(pst_ipv6_hdr + 1);

    ul_hdr_len       = OAL_SIZEOF(oal_ipv6hdr_stru) + OAL_SIZEOF(mac_ether_header_stru);
    if (!oal_pskb_may_pull(pst_buf, ul_hdr_len))
    {
        return OAL_ERR_CODE_PROXY_ND_INVLD_SKB1_INCOMP;
    }

    ul_opt_len = pst_buf->len - ul_hdr_len - (OAL_SIZEOF(oal_nd_msg_stru) - 4);

    if (OAL_IPPROTO_ICMPV6 != pst_ipv6_hdr->nexthdr)
    {
        return OAL_ERR_CODE_PROXY_ND_NOT_ICMPV6_INCOMP;
    }

    ul_hdr_len += OAL_SIZEOF(oal_icmp6hdr_stru);
    if (!oal_pskb_may_pull(pst_buf, ul_hdr_len))
    {
        return OAL_ERR_CODE_PROXY_ND_INVLD_SKB2_INCOMP;
    }

    if ((OAL_NDISC_NEIGHBOUR_SOLICITATION == pst_icmp6->icmp6_type))
    {
        return hmac_proxy_nd_rcv_ns(pst_mac_vap, pst_dev, pst_ether_hdr, (oal_int32)ul_opt_len);
    }
    else if (OAL_NDISC_NEIGHBOUR_ADVERTISEMENT == pst_icmp6->icmp6_type)
    {
        return hmac_proxy_nd_rcv_na(pst_mac_vap, pst_ether_hdr, (oal_int32)ul_opt_len);
    }

    return OAL_ERR_CODE_PROXY_ND_ICMPV6_NOT_NSNA_INCOMP;

}

/*****************************************************************************
 函 数 名  : hmac_proxy_is_need_drop
 功能描述  : 根据错误码决定是否要将处理的skb释放掉
 输入参数  : en_rst-错误码
 输出参数  : 无
 返 回 值  : 0/1--不需要释放/需要释放
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 hmac_proxy_is_need_drop(oal_err_code_enum_uint32 en_rst)
{
    oal_bool_enum_uint8      en_is_need_drop = OAL_FALSE;

    switch (en_rst)
    {
        case OAL_ERR_CODE_PROXY_ARP_LEARN_USR_COMP:
        //case OAL_ERR_CODE_PROXY_ARP_FINDUSR_ERR_COMP:
        case OAL_ERR_CODE_PROXY_ARP_REPLY2BSS_COMP:
        case OAL_ERR_CODE_PROXY_ARP_CREATE_FAIL_COMP:
        case OAL_ERR_CODE_PROXY_ARP_REPLY2ETH_COMP:
        case OAL_ERR_CODE_PROXY_ARP_REPLY_MCAST_COMP:
        case OAL_ERR_CODE_PROXY_ND_LEARN_USR_SUCC_COMP:
        case OAL_ERR_CODE_PROXY_ND_NS_OPT_INVLD_COMP:
        //case OAL_ERR_CODE_PROXY_ND_NS_FINDUSR_ERR_COMP:
        case OAL_ERR_CODE_PROXY_ND_NS_CREATE_NA_FAIL_COMP:
        case OAL_ERR_CODE_PROXY_ND_NS_REPLY_NA2BSS_COMP:
		case OAL_ERR_CODE_PROXY_ND_NS_REPLY_NA2ETH_COMP:
        case OAL_ERR_CODE_PROXY_ARP_LEARN_USR_NOTEXIST_COMP:
        case OAL_ERR_CODE_PROXY_ND_LEARN_USR_NOTEXIST_COMP:		/* 此处和A的流程有点不一样,A此处不drop，继续后面的流程 */
        case OAL_ERR_CODE_PROXY_ND_NA_INVLD_COMP:
        case OAL_ERR_CODE_PROXY_ND_NA_MCAST_NOT_LLA_COMP:
        case OAL_ERR_CODE_PROXY_ND_NA_UNSOLICITED_COMP:
        {
           en_is_need_drop = OAL_TRUE;
           break;
        }
        case OAL_ERR_CODE_PROXY_ARP_FINDUSR_ERR_COMP:
        case OAL_ERR_CODE_PROXY_ARP_REPLY_INCOMP:
        case OAL_ERR_CODE_PROXY_ARP_INVLD_SKB_INCOMP:
        case OAL_ERR_CODE_PROXY_ND_LEARN_USR_ALREADY_EXIST_INCOMP:
        case OAL_ERR_CODE_PROXY_ND_LEARN_USR_FAIL_INCOMP:
        case OAL_ERR_CODE_PROXY_ARP_NOT_REQ_REPLY_INCOMP:
        case OAL_ERR_CODE_PROXY_ND_NA_UCAST_NOT_LLA_INCOMP:
        case OAL_ERR_CODE_PROXY_ND_NA_DUP_ADDR_INCOMP:
        case OAL_ERR_CODE_PROXY_ND_NA_SOLICITED_INCOMP:
        case OAL_ERR_CODE_PROXY_ND_INVLD_SKB1_INCOMP:
        case OAL_ERR_CODE_PROXY_ND_NOT_ICMPV6_INCOMP:
        case OAL_ERR_CODE_PROXY_ND_INVLD_SKB2_INCOMP:
        case OAL_ERR_CODE_PROXY_ND_ICMPV6_NOT_NSNA_INCOMP:
        case OAL_ERR_CODE_PROXY_OTHER_INCOMP:
        case OAL_ERR_CODE_PROXY_ND_NS_FINDUSR_ERR_COMP:
        {
            en_is_need_drop = OAL_FALSE;
            break;
        }
        default:
        {
            break;
        }
    }
    return en_is_need_drop;
}

/*****************************************************************************
 函 数 名  : hmac_proxy_arp_proc
 功能描述  : AP进行ARP和ND代理的主入口函数
 输入参数  : pst_mac_vap: mac_vap指针
             oal_netbuf_stru:skb指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8 hmac_proxy_arp_proc(hmac_vap_stru *pst_hmac_vap, oal_netbuf_stru *pst_buf)
{
    mac_ether_header_stru      *pst_ether_hdr; /* 以太网头 */
    oal_uint16                  us_ether_type;
    oal_err_code_enum_uint32    en_rst = OAL_SUCC;
    mac_vap_stru               *pst_mac_vap;
#ifdef _PRE_DEBUG_MODE
    mac_ether_header_stru       st_eth_hdr;
#endif

    OAM_INFO_LOG0(0, OAM_SF_PROXYARP, "{hmac_proxy_arp_proc!}");
    pst_ether_hdr   = (mac_ether_header_stru *)oal_netbuf_data(pst_buf);
    us_ether_type      = pst_ether_hdr->us_ether_type;

#ifdef _PRE_DEBUG_MODE
    /* 由于netbuff有可能会被释放，所以此处需要先记录一下 */
    st_eth_hdr = *pst_ether_hdr;
#endif
    pst_mac_vap = &pst_hmac_vap->st_vap_base_info;

    switch(us_ether_type)
    {
        case OAL_HOST2NET_SHORT(ETHER_TYPE_ARP):
        {
            en_rst = hmac_proxy_arp(pst_mac_vap, pst_hmac_vap->pst_net_device, pst_buf);

            break;
        }
        case OAL_HOST2NET_SHORT(ETHER_TYPE_IPV6):
        {
            en_rst = hmac_proxy_nd(pst_mac_vap, pst_hmac_vap->pst_net_device, pst_buf);

            break;
        }
        default:
        {
            return OAL_FALSE;
        }
    }

#ifdef _PRE_DEBUG_MODE
    hmac_proxy_debug_record(pst_mac_vap, &st_eth_hdr, us_ether_type, en_rst);
    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_PROXYARP, "hmac_proxy_arp_proc! s:%x->d:%x type %x, result %u!",
                        st_eth_hdr.auc_ether_shost[ETHER_ADDR_LEN - 1],
                        st_eth_hdr.auc_ether_dhost[ETHER_ADDR_LEN - 1],
                        us_ether_type,
                        en_rst);
#endif

    return hmac_proxy_is_need_drop(en_rst);
}

/*****************************************************************************
 函 数 名  : hmac_proxy_arp_init
 功能描述  : 初始化proxy特性所需要的结构
 输入参数  : pst_mac_vap: mac_vap指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_proxy_arp_init(mac_vap_stru *pst_mac_vap)
{
    oal_uint32              ul_loop = 0;

    if ((WLAN_VAP_MODE_BSS_AP != pst_mac_vap->en_vap_mode)
     || (OAL_PTR_NULL != pst_mac_vap->pst_vap_proxyarp))
    {
        return;
    }


    /* 申请内存 */
    pst_mac_vap->pst_vap_proxyarp = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(mac_vap_proxyarp_stru), OAL_TRUE);
    if (OAL_PTR_NULL == pst_mac_vap->pst_vap_proxyarp)
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYARP, "hmac_proxy_arp_init err! malloc err!");
        return;
    }

    OAL_MEMZERO(pst_mac_vap->pst_vap_proxyarp, OAL_SIZEOF(mac_vap_proxyarp_stru));

    for (ul_loop = 0; ul_loop < MAC_VAP_USER_HASH_MAX_VALUE; ul_loop++)
    {
        oal_dlist_init_head(&(pst_mac_vap->pst_vap_proxyarp->ast_ipv4_head[ul_loop]));
    }

    for (ul_loop = 0; ul_loop < MAC_VAP_USER_HASH_MAX_VALUE; ul_loop++)
    {
        oal_dlist_init_head(&(pst_mac_vap->pst_vap_proxyarp->ast_ipv6_head[ul_loop]));
    }
}

/*****************************************************************************
 函 数 名  : hmac_proxy_exit
 功能描述  : 退出时释放所有内存
 输入参数  : pst_mac_vap: mac_vap指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_proxy_exit(mac_vap_stru *pst_mac_vap)
{
    oal_dlist_head_stru        *pst_entry;
    hmac_proxy_ipv4_hash_stru  *pst_hash_ipv4;
    hmac_proxy_ipv6_hash_stru  *pst_hash_ipv6;
    oal_dlist_head_stru        *pst_dlist_tmp      = OAL_PTR_NULL;
    oal_uint32                  ul_loop = 0;

    if (WLAN_VAP_MODE_BSS_AP != pst_mac_vap->en_vap_mode
     || (OAL_PTR_NULL == pst_mac_vap->pst_vap_proxyarp))
    {
        return;
    }

    for (ul_loop = 0; ul_loop < MAC_VAP_USER_HASH_MAX_VALUE; ul_loop++)
    {
        OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry, pst_dlist_tmp, &(pst_mac_vap->pst_vap_proxyarp->ast_ipv4_head[ul_loop]))
        {
            pst_hash_ipv4 = (hmac_proxy_ipv4_hash_stru *)pst_entry;
            oal_dlist_delete_entry(pst_entry);
            OAL_MEM_FREE(pst_hash_ipv4, OAL_TRUE);
            pst_mac_vap->pst_vap_proxyarp->uc_ipv4_num--;
        }
    }

    for (ul_loop = 0; ul_loop < MAC_VAP_USER_HASH_MAX_VALUE; ul_loop++)
    {
        OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry, pst_dlist_tmp, &(pst_mac_vap->pst_vap_proxyarp->ast_ipv6_head[ul_loop]))
        {
            pst_hash_ipv6 = (hmac_proxy_ipv6_hash_stru *)pst_entry;
            oal_dlist_delete_entry(pst_entry);
            OAL_MEM_FREE(pst_hash_ipv6, OAL_TRUE);
            pst_mac_vap->pst_vap_proxyarp->uc_ipv6_num--;
        }
    }

    OAL_MEM_FREE(pst_mac_vap->pst_vap_proxyarp, OAL_TRUE);
    pst_mac_vap->pst_vap_proxyarp = OAL_PTR_NULL;

}

/*****************************************************************************
 函 数 名  : hmac_proxyarp_on
 功能描述  : 设置proxy arp特性开关
 输入参数  : pst_mac_vap : mac_vap指针
             en_on:开关值 0/1--关/开
 输出参数  :
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_proxyarp_on(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_on)
{
    if ((OAL_PTR_NULL == pst_mac_vap)
    || (WLAN_VAP_MODE_BSS_AP != pst_mac_vap->en_vap_mode))
    {
        return;
    }

    if (en_on)
    {
        hmac_proxy_arp_init(pst_mac_vap);
        pst_mac_vap->pst_vap_proxyarp->en_is_proxyarp = en_on;
        return;
    }

    hmac_proxy_exit(pst_mac_vap);

}

/*****************************************************************************
 函 数 名  : alg_autorate_command_print_rate_set
 功能描述  : 打印proxy arp调试信息
 输入参数  : pst_mac_vap : mac_vap指针
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
#ifdef _PRE_DEBUG_MODE
oal_uint32 hmac_proxy_display_info(mac_vap_stru *pst_mac_vap)
{

    oal_dlist_head_stru             *pst_entry;
    hmac_proxy_ipv4_hash_stru       *pst_hash_ipv4;
    hmac_proxy_ipv6_hash_stru       *pst_hash_ipv6;
    oal_dlist_head_stru             *pst_dlist_tmp      = OAL_PTR_NULL;
    oal_uint32                       ul_loop = 0;
    oal_uint32                       ul_idx = 0;
    mac_vap_proxyarp_debug_stru     *pst_dbg;

    if (WLAN_VAP_MODE_BSS_AP != pst_mac_vap->en_vap_mode)
    {
        OAL_IO_PRINT("Err! Please input this cmd in AP!\n");
        return 0;
    }

    if (OAL_PTR_NULL == pst_mac_vap->pst_vap_proxyarp)
    {
        OAL_IO_PRINT("Err!proxyarp mem alloc fail!\n");
        return 0;
    }

    OAL_IO_PRINT("index\tsrc_mac\t\tdst_mac\t\teth_type\tresult\tfrm_type\n");
    for (ul_loop = 0; ul_loop < MAC_VAP_USER_HASH_MAX_VALUE; ul_loop++)
    {
        pst_dbg = &pst_mac_vap->pst_vap_proxyarp->ast_vap_proxyarp_dbg[ul_loop];

        OAL_IO_PRINT("%u\t%08x%04x\t%08x%04x\t%04x\t\t%u\t0x%x\n", \
                    pst_dbg->us_proxy_num, \
                    OAL_HOST2NET_LONG(*(oal_uint32*)(&pst_dbg->st_eth_hdr.auc_ether_shost[0])),   \
                    OAL_HOST2NET_SHORT(*(oal_uint16*)(&pst_dbg->st_eth_hdr.auc_ether_shost[4])),   \
                    OAL_HOST2NET_LONG(*(oal_uint32*)(&pst_dbg->st_eth_hdr.auc_ether_dhost[0])),   \
                    OAL_HOST2NET_SHORT(*(oal_uint16*)(&pst_dbg->st_eth_hdr.auc_ether_dhost[4])),   \
                    pst_dbg->st_eth_hdr.us_ether_type,\
                    pst_dbg->en_rst,\
                    pst_dbg->us_type);
    }


    OAL_IO_PRINT("\n ********************ipv4 hash***************************\n");
    OAL_IO_PRINT("index\tipaddr\t\tmac\n");
    for (ul_loop = 0; ul_loop < MAC_VAP_USER_HASH_MAX_VALUE; ul_loop++)
    {
        OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry, pst_dlist_tmp, &(pst_mac_vap->pst_vap_proxyarp->ast_ipv4_head[ul_loop]))
        {
            pst_hash_ipv4 = (hmac_proxy_ipv4_hash_stru *)pst_entry;
            OAL_IO_PRINT("%u\t%08x\t%08x%04x\n", \
            ul_idx++,  \
            OAL_HOST2NET_LONG(pst_hash_ipv4->ul_ipv4), \
            OAL_HOST2NET_LONG(*(oal_uint32*)(&pst_hash_ipv4->auc_mac[0])),  \
            OAL_HOST2NET_SHORT(*(oal_uint16*)(&pst_hash_ipv4->auc_mac[4])));
        }
    }

    ul_idx = 0;
	OAL_IO_PRINT("\n ********************ipv6 hash***************************\n");
	OAL_IO_PRINT("index\tipaddr\t\t\t\t\tmac\n");
    for (ul_loop = 0; ul_loop < MAC_VAP_USER_HASH_MAX_VALUE; ul_loop++)
    {
        OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry, pst_dlist_tmp, &(pst_mac_vap->pst_vap_proxyarp->ast_ipv6_head[ul_loop]))
        {
            pst_hash_ipv6 = (hmac_proxy_ipv6_hash_stru *)pst_entry;
			OAL_IO_PRINT("%u\t%08x:%08x:%08x:%08x\t%08x%04x\n", \
            ul_idx++,  \
            OAL_HOST2NET_LONG(*(oal_uint32*)(&pst_hash_ipv6->st_ipv6.in6_u.u6_addr32[0])), \
			OAL_HOST2NET_LONG(*(oal_uint32*)(&pst_hash_ipv6->st_ipv6.in6_u.u6_addr32[1])), \
			OAL_HOST2NET_LONG(*(oal_uint32*)(&pst_hash_ipv6->st_ipv6.in6_u.u6_addr32[2])), \
            OAL_HOST2NET_LONG(*(oal_uint32*)(&pst_hash_ipv6->st_ipv6.in6_u.u6_addr32[3])), \
            OAL_HOST2NET_LONG(*(oal_uint32*)(&pst_hash_ipv6->auc_mac[0])),  \
            OAL_HOST2NET_SHORT(*(oal_uint16*)(&pst_hash_ipv6->auc_mac[4])));
        }
    }

    return OAL_SUCC;
}
#endif

/*lint +e778*/ /*lint +e572*/

/*lint -e19*/
oal_module_symbol(hmac_proxy_arp_proc);
oal_module_symbol(hmac_proxyarp_on);

#ifdef _PRE_DEBUG_MODE
oal_module_symbol(hmac_proxy_display_info);
#endif
/*lint +e19*/


#endif /* #ifdef _PRE_WLAN_FEATURE_PROXY_ARP */


