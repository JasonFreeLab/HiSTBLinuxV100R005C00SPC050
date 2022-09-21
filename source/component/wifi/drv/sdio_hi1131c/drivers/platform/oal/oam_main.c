#include "oam_ext_if.h"
oal_uint32  oam_report_80211_mcast_get_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_mcast_direction,
                                        oam_user_track_frame_type_enum_uint8    en_frame_type,
                                        oal_switch_enum_uint8                  *pen_frame_switch,
                                        oal_switch_enum_uint8                  *pen_cb_switch,
                                        oal_switch_enum_uint8                  *pen_dscr_switch)
{
    return 1;
}

oal_uint32  oam_report_beacon(
                                    oal_uint8     *puc_beacon_hdr_addr,
                                    oal_uint8      uc_beacon_hdr_len,
                                    oal_uint8     *puc_beacon_body_addr,
                                    oal_uint16     us_beacon_len,
                                    oam_ota_frame_direction_type_enum_uint8 en_beacon_direction)
{
    return 1;
}


oal_uint32  oam_report_80211_probe_get_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_probereq_direction,
                                        oal_switch_enum_uint8                  *pen_frame_switch,
                                        oal_switch_enum_uint8                  *pen_cb_switch,
                                        oal_switch_enum_uint8                  *pen_dscr_switch)
{
    return 1;
}

oal_uint32  oam_report_80211_ucast_get_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_ucast_direction,
                                        oam_user_track_frame_type_enum_uint8    en_frame_type,
                                        oal_switch_enum_uint8                  *pen_frame_switch,
                                        oal_switch_enum_uint8                  *pen_cb_switch,
                                        oal_switch_enum_uint8                  *pen_dscr_switch,
                                        oal_uint16                              us_user_idx)
 {
    return 1;
 }

 oal_uint32  oam_report_netbuf_cb(oal_uint8  *puc_user_mac_addr,
                                       oal_uint8  *puc_netbuf_cb,
                                       oam_ota_type_enum_uint8 en_ota_type)
 {
    return 1;
 }

oal_uint32  oam_report_80211_frame(
                        oal_uint8     *puc_user_macaddr,
                        oal_uint8     *puc_mac_hdr_addr,
                        oal_uint8      uc_mac_hdr_len,
                        oal_uint8     *puc_mac_body_addr,
                        oal_uint16     us_mac_frame_len,
                        oam_ota_frame_direction_type_enum_uint8  en_frame_direction)
{
    return 1;
}
//oal_uint8 g_auc_bcast_addr[WLAN_MAC_ADDR_LEN]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

oal_int32 OAL_PRINT_NLOGS(
        const oal_int8* pfunc_local_name,
        oal_uint16      us_file_no,
        oal_uint16      us_line_no,
        void*           pfunc_addr,
        oal_uint8       uc_vap_id,
        oal_uint8       en_feature_id,
        oal_uint8       clog_level,
        oal_int8*       fmt,
        oal_uint p1, oal_uint p2, oal_uint p3, oal_uint p4)
{
    return OAL_SUCC;
}

oam_stat_info_stru g_st_stat_info;

oal_uint32  oam_stats_clear_user_stat_info(oal_uint16   us_usr_id)
{
    return OAL_SUCC;
}

#if 0
oal_uint32  oam_print(oal_int8 *pc_string)
{
    return OAL_SUCC;
}
#endif

oal_uint32  oam_event_set_switch(
                oal_uint8               uc_vap_id,
                oal_switch_enum_uint8   en_switch_type)
{
    return OAL_SUCC;
}

oal_uint32 oam_report_eth_frame_set_switch(oal_uint16               us_user_idx,
                                                   oal_switch_enum_uint8    en_switch,
                                       oam_ota_frame_direction_type_enum_uint8 en_eth_direction)
{
    return OAL_SUCC;
}

oal_uint32  oam_report_80211_ucast_set_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_ucast_direction,
                                        oam_user_track_frame_type_enum_uint8    en_frame_type,
                                        oal_switch_enum_uint8                   en_frame_switch,
                                        oal_switch_enum_uint8                   en_cb_switch,
                                        oal_switch_enum_uint8                   en_dscr_switch,
                                        oal_uint16                              us_user_idx)
{
   return OAL_SUCC;
}

oal_uint32  oam_report_80211_mcast_set_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_mcast_direction,
                                        oam_user_track_frame_type_enum_uint8    en_frame_type,
                                        oal_switch_enum_uint8                   en_frame_switch,
                                        oal_switch_enum_uint8                   en_cb_switch,
                                        oal_switch_enum_uint8                   en_dscr_switch)
{
    return OAL_SUCC;
}

oal_uint32  oam_report_80211_probe_set_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_probe_direction,
                                        oal_switch_enum_uint8                   en_frame_switch,
                                        oal_switch_enum_uint8                   en_cb_switch,
                                        oal_switch_enum_uint8                   en_dscr_switch)
{
    return OAL_SUCC;
}

oal_uint32  oam_ota_set_beacon_switch(
                  oal_uint8                                   uc_vap_id,
                  oam_sdt_print_beacon_rxdscr_type_enum_uint8 en_switch_type)
{
    return OAL_SUCC;
}
oal_uint32  oam_ota_set_rx_dscr_switch(
                                                      oal_uint8             uc_vap_id,
                                                      oal_switch_enum_uint8 en_switch_type)
{
    return OAL_SUCC;
}

oal_uint32  oam_report_set_all_switch(oal_switch_enum_uint8 en_switch)
{
   return OAL_SUCC;
}

oal_uint32  oam_set_output_type(oam_output_type_enum_uint8 en_output_type)
{
    return OAL_SUCC;
}

oal_uint32  oam_report_dhcp_arp_set_switch(oal_switch_enum_uint8 en_switch)
{
    return OAL_SUCC;
}

oal_uint32  oam_get_output_type(oam_output_type_enum_uint8 *pen_output_type)
{
    return OAL_SUCC;
}

oal_uint32  oam_ota_report(
                           oal_uint8     *puc_param_one_addr,
                           oal_uint16     us_param_one_len,
                           oal_uint8     *puc_param_two_addr,
                           oal_uint16     us_param_two_len,
                           oam_ota_type_enum_uint8  en_ota_type)
{
    return OAL_SUCC;
}

oal_uint32  oam_stats_clear_vap_stat_info(oal_uint8   uc_vap_id)
{
    return OAL_SUCC;
}

oal_uint32  oam_report_eth_frame_get_switch(
                                 oal_uint16             us_user_idx,
                                 oam_ota_frame_direction_type_enum_uint8 en_eth_direction,
                                 oal_switch_enum_uint8  *pen_eth_switch)
{
    return OAL_SUCC;
}

oal_uint32  oam_report_eth_frame(oal_uint8               *puc_user_mac_addr,
                                       oal_uint8               *puc_eth_frame_hdr_addr,
                                       oal_uint16               us_eth_frame_len,
                                       oam_ota_frame_direction_type_enum_uint8 en_eth_frame_direction)
{
    return OAL_SUCC;
}

oal_switch_enum_uint8  oam_report_dhcp_arp_get_switch(oal_void)
{
    return 1;
}

oal_uint32  oam_report_dft_params(oal_uint8  *puc_user_mac_addr,
                                        oal_uint8  *puc_param,
                                        oal_uint16      us_param_len,
                                        oam_ota_type_enum_uint8 en_type)
{
     return OAL_ERR_CODE_INVALID_CONFIG;
}

typedef oal_uint32 (* p_oam_customize_init_func)(oal_void);
oal_void  oam_register_init_hook(oam_msg_moduleid_enum_uint8 en_moduleid,  p_oam_customize_init_func p_func)
{

}

oal_void oam_wal_func_fook_register(oam_wal_func_hook_stru *pfun_st_oam_wal_hook)
{

}

oal_netbuf_stru *oam_alloc_data2sdt(oal_uint16  us_data_len)
{
  return NULL;
}

oal_uint32 oam_report_data2sdt(oal_netbuf_stru *pst_netbuf,
                               oam_data_type_enum_uint8 en_type,
                               oam_primid_type_enum_uint8 en_prim)
{
    return OAL_SUCC;
}
oam_sdt_func_hook_stru          g_st_oam_sdt_func_hook;

oal_void  oam_stats_clear_stat_info(oal_void)
{

}

oal_uint32  oam_stats_report_info_to_sdt(oam_ota_type_enum_uint8 en_ota_type)
{
    return 1;
}

oal_uint32  oam_stats_report_usr_info(oal_uint16  us_usr_id)
{
    return 1;
}

oal_uint32 oam_log_set_ratelimit_param(
                oam_ratelimit_type_enum_uint8  en_ratelimit_type,
                oam_ratelimit_stru *pst_printk_ratelimit)
{
    return 1;
}

oal_uint32  oam_log_console_printk(
                oal_uint16                       us_file_no,
                oal_uint16                       us_line_num,
                const oal_int8                  *pc_func_name,
                const oal_int8                  *pc_fmt,
                ...)

{
    return 1;
}


