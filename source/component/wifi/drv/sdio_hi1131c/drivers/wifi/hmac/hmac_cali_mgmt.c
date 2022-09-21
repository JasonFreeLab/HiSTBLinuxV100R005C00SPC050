/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_main.c
  版 本 号   : 初稿
  作    者   : 唐慧超
  生成日期   : 2012年9月18日
  最近修改   :
  功能描述   : HMAC模块初始化与卸载
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月18日
    作    者   : 唐慧超
    修改内容   : 创建文件

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif
#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "hmac_cali_mgmt.h"
#include "oal_kernel_file.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_CALI_MGMT_C

extern oal_uint32 wlan_pm_close(oal_void);
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/*****************************************************************************
  3 函数实现
*****************************************************************************/
oal_void hmac_add_bound(oal_uint32 *pul_number, oal_uint32 ul_bound)
{
    *pul_number = *pul_number + 1;

    if (*pul_number > (ul_bound - 1))
    {
        *pul_number -= ul_bound;
    }
}

/*lint -e571*/
/*lint -e801*/
#ifdef _PRE_WLAN_FEATURE_5G
OAL_STATIC oal_int32 hmac_print_cail_result(oal_uint8 uc_cali_chn_idx,
                                                  oal_int8 *pc_print_buff,
                                                  oal_uint32 ul_remainder_len,
                                                  oal_cali_param_stru *pst_cali_data)
{
    oal_int8 *pc_string;

    pc_string = (uc_cali_chn_idx < OAL_5G_20M_CHANNEL_NUM)
        ? "5G 20M cali data index:%d, rx_dc_comp:0x%x, s_digital_rxdc_cmp_i:0x%x, us_digital_rxdc_cmp_q:0x%x \n"
          "5G 20M tx_power upc_ppa_cmp:0x%x, upc_mx_cmp:0x%x, atx_pwr_cmp:0x%x,  ppf:0x%x \n"
          "5G 20M tx_dc i:%u,  q:%u, tx_iq p:%u  e:%u \n"
        : "5G 80M cali data index:%d, rx_dc_comp:0x%x, s_digital_rxdc_cmp_i:0x%x, us_digital_rxdc_cmp_q:0x%x \n"
          "5G 80M tx_power upc_ppa_cmp:0x%x, upc_mx_cmp:0x%x, atx_pwr_cmp:0x%x,  ppf:0x%x \n"
          "5G 80M tx_dc i:%u,  q:%u, tx_iq p:%u  e:%u \n" ;
    return OAL_SPRINTF(pc_print_buff, ul_remainder_len, pc_string,
                    uc_cali_chn_idx,
                    pst_cali_data->ast_5Gcali_param[uc_cali_chn_idx].g_st_cali_rx_dc_cmp_5G.us_analog_rxdc_cmp,
                    pst_cali_data->ast_5Gcali_param[uc_cali_chn_idx].g_st_cali_rx_dc_cmp_5G.us_digital_rxdc_cmp_i,
                    pst_cali_data->ast_5Gcali_param[uc_cali_chn_idx].g_st_cali_rx_dc_cmp_5G.us_digital_rxdc_cmp_q,
                    pst_cali_data->ast_5Gcali_param[uc_cali_chn_idx].g_st_cali_tx_power_cmp_5G.upc_ppa_cmp,
                    pst_cali_data->ast_5Gcali_param[uc_cali_chn_idx].g_st_cali_tx_power_cmp_5G.upc_mx_cmp,
                    (oal_uint8)pst_cali_data->ast_5Gcali_param[uc_cali_chn_idx].g_st_cali_tx_power_cmp_5G.ac_atx_pwr_cmp,
                    pst_cali_data->ast_5Gcali_param[uc_cali_chn_idx].g_st_ppf_cmp_val.uc_ppf_val,
                    pst_cali_data->ast_5Gcali_param[uc_cali_chn_idx].g_st_txdc_cmp_val.us_txdc_cmp_i,
                    pst_cali_data->ast_5Gcali_param[uc_cali_chn_idx].g_st_txdc_cmp_val.us_txdc_cmp_q,
                    pst_cali_data->ast_5Gcali_param[uc_cali_chn_idx].g_st_txiq_cmp_val_5G.us_txiq_cmp_p,
                    pst_cali_data->ast_5Gcali_param[uc_cali_chn_idx].g_st_txiq_cmp_val_5G.us_txiq_cmp_e);
}
#endif

extern oal_uint32 band_5g_enabled;
oal_void hmac_dump_cali_result(oal_void)
{
    oal_cali_param_stru *pst_cali_data;
    oal_uint8            uc_cali_chn_idx;
#ifdef _PRE_WLAN_FEATURE_5G
    oal_uint32           ul_string_len;
    oal_int32            l_string_tmp_len;
    oal_int8            *pc_print_buff;
#endif
    pst_cali_data = (oal_cali_param_stru *)get_cali_data_buf_addr();

    OAM_WARNING_LOG4(0, OAM_SF_CFG, "rc code RC:0x%x, R:0x%x, C:0x%x, check_hw_status:0x%x",
            pst_cali_data->st_bfgn_cali_data.g_uc_rc_cmp_code,
            pst_cali_data->st_bfgn_cali_data.g_uc_r_cmp_code,
            pst_cali_data->st_bfgn_cali_data.g_uc_c_cmp_code,
            pst_cali_data->ul_check_hw_status);
    for (uc_cali_chn_idx = 0; uc_cali_chn_idx < OAL_2G_CHANNEL_NUM; uc_cali_chn_idx++)
    {
        OAM_WARNING_LOG4(0, OAM_SF_CFG, "2G cali data index:%u, rx_dc_comp: 0x%x, us_digital_rxdc_cmp_i:0x%x, us_digital_rxdc_cmp_q:0x%x",
                uc_cali_chn_idx,
                pst_cali_data->ast_2Gcali_param[uc_cali_chn_idx].g_st_cali_rx_dc_cmp_2G.us_analog_rxdc_cmp,
                pst_cali_data->ast_2Gcali_param[uc_cali_chn_idx].g_st_cali_rx_dc_cmp_2G.us_digital_rxdc_cmp_i,
                pst_cali_data->ast_2Gcali_param[uc_cali_chn_idx].g_st_cali_rx_dc_cmp_2G.us_digital_rxdc_cmp_q);

        OAM_WARNING_LOG4(0, OAM_SF_CFG, "2G cali data index:%u, upc_ppa_cmp:0x%x, ac_atx_pwr_cmp:0x%x, dtx_pwr_cmp:0x%x",
                uc_cali_chn_idx,
                pst_cali_data->ast_2Gcali_param[uc_cali_chn_idx].g_st_cali_tx_power_cmp_2G.upc_ppa_cmp,
                (oal_uint8)pst_cali_data->ast_2Gcali_param[uc_cali_chn_idx].g_st_cali_tx_power_cmp_2G.ac_atx_pwr_cmp,
                (oal_uint8)pst_cali_data->ast_2Gcali_param[uc_cali_chn_idx].g_st_cali_tx_power_cmp_2G.dtx_pwr_cmp);

        OAM_WARNING_LOG4(0, OAM_SF_CFG, " 2G tx_dc i:%u q:%u, tx_iq p:%u  e:%u",
                pst_cali_data->ast_2Gcali_param[uc_cali_chn_idx].g_st_txdc_cmp_val.us_txdc_cmp_i,
                pst_cali_data->ast_2Gcali_param[uc_cali_chn_idx].g_st_txdc_cmp_val.us_txdc_cmp_q,
                pst_cali_data->ast_2Gcali_param[uc_cali_chn_idx].g_st_txiq_cmp_val_2G.us_txiq_cmp_p,
                pst_cali_data->ast_2Gcali_param[uc_cali_chn_idx].g_st_txiq_cmp_val_2G.us_txiq_cmp_e);

    }

#ifdef _PRE_WLAN_FEATURE_5G
    if (OAL_FALSE == band_5g_enabled)
    {
        return;
    }

    pc_print_buff = (oal_int8 *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAM_REPORT_MAX_STRING_LEN, OAL_TRUE);
    if (OAL_PTR_NULL == pc_print_buff)
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{hmac_dump_cali_result::pc_print_buff null.}", OAM_REPORT_MAX_STRING_LEN);
        return;
    }

    OAL_MEMZERO(pc_print_buff, OAM_REPORT_MAX_STRING_LEN);
    ul_string_len    = 0;

    for (uc_cali_chn_idx = 0; uc_cali_chn_idx < OAL_5G_20M_CHANNEL_NUM; uc_cali_chn_idx++)
    {
        l_string_tmp_len = hmac_print_cail_result(uc_cali_chn_idx, pc_print_buff + ul_string_len, (OAM_REPORT_MAX_STRING_LEN - ul_string_len - 1), pst_cali_data);
        if (l_string_tmp_len < 0)
        {
            goto sprint_fail;
        }
        ul_string_len += (oal_uint32)l_string_tmp_len;

    }
    pc_print_buff[OAM_REPORT_MAX_STRING_LEN-1] = '\0';
    oam_print(pc_print_buff);

    /* 上述日志量超过OAM_REPORT_MAX_STRING_LEN，分多次oam_print */
    OAL_MEMZERO(pc_print_buff, OAM_REPORT_MAX_STRING_LEN);
    ul_string_len    = 0;

    for (uc_cali_chn_idx = OAL_5G_20M_CHANNEL_NUM; uc_cali_chn_idx < OAL_5G_CHANNEL_NUM; uc_cali_chn_idx++)
    {
        l_string_tmp_len = hmac_print_cail_result(uc_cali_chn_idx, pc_print_buff + ul_string_len, (OAM_REPORT_MAX_STRING_LEN - ul_string_len - 1), pst_cali_data);
        if (l_string_tmp_len < 0)
        {
            goto sprint_fail;
        }
        ul_string_len += (oal_uint32)l_string_tmp_len;

    }
    pc_print_buff[OAM_REPORT_MAX_STRING_LEN-1] = '\0';
    oam_print(pc_print_buff);

    /* 上述日志量超过OAM_REPORT_MAX_STRING_LEN，分多次oam_print */
    OAL_MEMZERO(pc_print_buff, OAM_REPORT_MAX_STRING_LEN);
    ul_string_len    = 0;

#ifdef _PRE_WLAN_NEW_IQ
    for (uc_cali_chn_idx = 0; uc_cali_chn_idx < OAL_5G_20M_CHANNEL_NUM; uc_cali_chn_idx++)
    {
        l_string_tmp_len = OAL_SPRINTF(pc_print_buff + ul_string_len, (OAM_REPORT_MAX_STRING_LEN - ul_string_len - 1),
            "uc_cali_chn_idx:%d \n"
            "RX_IQ udelay1:0x%x, udelay2:0x%x, alpha:0x%x, beta:0x%x \n",
            uc_cali_chn_idx,
            pst_cali_data->ast_new_rxiq_cmp_val_5G[uc_cali_chn_idx].ul_rxiq_cmp_u1,
            pst_cali_data->ast_new_rxiq_cmp_val_5G[uc_cali_chn_idx].ul_rxiq_cmp_u2,
            pst_cali_data->ast_new_rxiq_cmp_val_5G[uc_cali_chn_idx].ul_rxiq_cmp_alpha,
            pst_cali_data->ast_new_rxiq_cmp_val_5G[uc_cali_chn_idx].ul_rxiq_cmp_beta);
        if (l_string_tmp_len < 0)
        {
            goto sprint_fail;
        }
        ul_string_len += (oal_uint32)l_string_tmp_len;
    }
    pc_print_buff[OAM_REPORT_MAX_STRING_LEN-1] = '\0';
    oam_print(pc_print_buff);
#endif

    OAL_MEM_FREE(pc_print_buff, OAL_TRUE);
    return;

sprint_fail:
    OAM_WARNING_LOG0(0, OAM_SF_CFG, "{hmac_dump_cali_result:: OAL_SPRINTF return error!}");
    pc_print_buff[OAM_REPORT_MAX_STRING_LEN-1] = '\0';
    oam_print(pc_print_buff);
    OAL_MEM_FREE(pc_print_buff, OAL_TRUE);

    return;
#endif
}
/*lint +e801*/
/*lint +e571*/

oal_uint32  hmac_save_cali_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru          *pst_event;
    hal_cali_hal2hmac_event_stru    *pst_cali_save_event;
    hal_cali_hal2hmac_payload_stru *pst_pay_load;
    oal_uint8 *puc_start_addr;
    oal_uint32 ul_copy_len;
    oal_update_cali_channel_stru *pst_update_cali_channel;
    oal_cali_param_stru *pst_cali_data;
    oal_uint32                      ul_remain_len;
    oal_uint32                      ul_netbuf_len;
    //oal_uint8  *puc_content;
    //oal_uint32 ul_byte;

    pst_cali_data = (oal_cali_param_stru *)get_cali_data_buf_addr();

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
    pst_cali_save_event = (hal_cali_hal2hmac_event_stru *)pst_event->auc_event_data;

    pst_pay_load  = (hal_cali_hal2hmac_payload_stru *)OAL_NETBUF_DATA(pst_cali_save_event->pst_netbuf);
    pst_update_cali_channel = &pst_cali_data->st_cali_update_info;
    //pst_update_cali_channel->ul_cali_time = 0;

    //OAL_IO_PRINT("pst_update_cali_channel->ul_cali_time %d : \r\n", pst_update_cali_channel->ul_cali_time);
    ul_netbuf_len = OAL_NETBUF_LEN(pst_cali_save_event->pst_netbuf);

    if ((pst_update_cali_channel->ul_cali_time == 0) && (g_uc_netdev_is_open == OAL_FALSE))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{hmac_save_cali_event: wlan_pm_close,g_uc_netdev_is_open = FALSE!\r\n.}");
        wlan_pm_close();
    }
    //OAL_IO_PRINT("hmac_save_cali_event : first cali packet idx:pst_pay_load->ul_packet_idx %d\r\n", pst_pay_load->ul_packet_idx);
    OAM_WARNING_LOG1(0, 0, "hmac_save_cali_event : first cali packet idx:pst_pay_load->ul_packet_idx %d\r\n", pst_pay_load->ul_packet_idx);

    puc_start_addr = ((oal_uint8 *)pst_cali_data->ast_2Gcali_param) + ((ul_netbuf_len - 4) * pst_pay_load->ul_packet_idx);
    ul_remain_len = OAL_WIFI_CALI_DATA_UPLOAD_LEN;
    ul_remain_len = ul_remain_len - (ul_netbuf_len - 4) * pst_pay_load->ul_packet_idx;
    //OAL_IO_PRINT("hmac_save_cali_event : ul_remain_len%d \r\n", ul_remain_len);

    //OAM_ERROR_LOG1(0, 0, "hmac_save_cali_event : ul_remain_len%d \r\n", ul_remain_len);
    //OAL_IO_PRINT("hmac_save_cali_event : WLAN_LARGE_NETBUF_SIZE %d\r\n", ul_netbuf_len);

    if (ul_remain_len <= ul_netbuf_len - 4)
    {
        //OAL_IO_PRINT("hmac_save_cali_event : last packet");
        ul_copy_len = ul_remain_len;
    }
    else
    {
        ul_copy_len = ul_netbuf_len - 4;
    }

    oal_memcopy(puc_start_addr, pst_pay_load->auc_payoald, ul_copy_len);

    if (ul_remain_len <= ul_netbuf_len - 4)
    {
        pst_update_cali_channel->ul_cali_time++;
        pst_update_cali_channel->en_update_bt = OAL_FALSE;
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_save_cali_event: : last packet ul_cali_time %d}", pst_update_cali_channel->ul_cali_time);
    }

    hmac_dump_cali_result();
#if 0

    puc_content = (oal_uint8 *)pst_cali_data->ast_2Gcali_param;

    OAM_ERROR_LOG1(0, 0, "hmac_save_cali_event : calidata len%d \r\n", OAL_SIZEOF(oal_cali_param_stru) - 8);
    for (ul_byte = 0; ul_byte < OAL_SIZEOF(oal_cali_param_stru) - 8; ul_byte+=4)
    {

        OAL_IO_PRINT("%02X %02X %02X %02X\r\n", puc_content[ul_byte], puc_content[ul_byte+1],
                      puc_content[ul_byte+2], puc_content[ul_byte+3]);
    }

    else
    {
        puc_start_addr = pst_pay_load->auc_payoald;
        oal_memcopy(&g_st_cali_control.g_ast_5Gcali_param[pst_update_cali_channel->uc_5g_chan_idx1],
                    puc_start_addr,
                    OAL_SIZEOF(oal_5Gcali_param_stru));

        puc_start_addr += OAL_SIZEOF(oal_5Gcali_param_stru);
        oal_memcopy(&g_st_cali_control.g_ast_5Gcali_param[pst_update_cali_channel->uc_5g_chan_idx1 + HAL_5G_20M_CHANNEL_NUM],
                    puc_start_addr,
                    OAL_SIZEOF(oal_5Gcali_param_stru));

        if (pst_update_cali_channel->en_update_bt == OAL_TRUE)
        {
            puc_start_addr += OAL_SIZEOF(oal_5Gcali_param_stru);
            oal_memcopy(&g_st_cali_control.st_bt_cali_comp,
                        pst_pay_load,
                        OAL_SIZEOF(oal_bt_cali_comp_stru));
        }

        pst_update_cali_channel->ul_cali_time++;
        hmac_add_bound((oal_uint32 *)&pst_update_cali_channel->uc_2g_band_idx, HAL_2G_CHANNEL_NUM + 1);

        if (HAL_2G_CHANNEL_NUM == pst_update_cali_channel->uc_2g_band_idx)
        {
            pst_update_cali_channel->en_update_bt = OAL_TRUE;
        }
        else
        {
            pst_update_cali_channel->en_update_bt = OAL_FALSE;
        }

        hmac_add_bound((oal_uint32 *)&pst_update_cali_channel->uc_5g_chan_idx1, HAL_5G_20M_CHANNEL_NUM);

        while (mac_is_channel_idx_valid(MAC_RC_START_FREQ_5, pst_update_cali_channel->uc_5g_chan_idx1))
        {
            hmac_add_bound((oal_uint32 *)&pst_update_cali_channel->uc_5g_chan_idx1, HAL_5G_20M_CHANNEL_NUM);
        }
    }

#endif

    oal_netbuf_free(pst_cali_save_event->pst_netbuf);

    return OAL_SUCC;
}

oal_uint32 hmac_send_cali_data(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    frw_event_mem_stru       *pst_event_mem;
    frw_event_stru           *pst_event;
    dmac_tx_event_stru       *pst_dpd_event;
    oal_netbuf_stru          *pst_netbuf_cali_data;
    oal_uint8                *puc_cali_data;
    oal_cali_param_stru      *pst_cali_data;

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG2(0, OAM_SF_CALIBRATE, "{hmac_dpd_data_processed_send::param null, %p %p.}", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_tx_event_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CALIBRATE, "{hmac_scan_proc_scan_req_event::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_IO_PRINT("{hmac_send_cali_data.start}\r\n");

    pst_netbuf_cali_data = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF,WLAN_LARGE_NETBUF_SIZE, OAL_NETBUF_PRIORITY_MID);
    if (OAL_PTR_NULL == pst_netbuf_cali_data)
    {
       FRW_EVENT_FREE(pst_event_mem);
       OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE,"{hmac_dpd_data_processed_send::pst_netbuf_scan_result null.}");

       return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CTX,
                       DMAC_WLAN_CTX_EVENT_SUB_TYPE_CALI_HMAC2DMAC,
                       OAL_SIZEOF(dmac_tx_event_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    OAL_MEMZERO(oal_netbuf_cb(pst_netbuf_cali_data), OAL_TX_CB_LEN);

    pst_cali_data = (oal_cali_param_stru *)get_cali_data_buf_addr();
    hmac_dump_cali_result();
    puc_param = (oal_uint8 *)(pst_cali_data->ast_2Gcali_param);

    puc_cali_data = (oal_uint8 *)(OAL_NETBUF_DATA(pst_netbuf_cali_data));
    oal_memcopy(puc_cali_data, puc_param, OAL_SIZEOF(pst_cali_data->ast_2Gcali_param));

    pst_dpd_event               = (dmac_tx_event_stru *)pst_event->auc_event_data;
    pst_dpd_event->pst_netbuf   = pst_netbuf_cali_data;
    pst_dpd_event->us_frame_len = OAL_SIZEOF(pst_cali_data->ast_2Gcali_param);

    frw_event_dispatch_event(pst_event_mem);

    oal_netbuf_free(pst_netbuf_cali_data);
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}


#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

