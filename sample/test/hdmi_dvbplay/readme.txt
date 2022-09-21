Purpose: to test the commands of the hdmi. External transport streams (TSs) need to be read.
sample_hdmi_dvbplay
    Command: sample_hdmi_dvbplay freq srate [qamtype or polarization] [vo_format]
        Fields [qamtype or polarization] and [vo_format] are optional.
            qamtype or polarization:
                For cable, used as qamtype, value can be 16|32|[64]|128|256|512 defaut[64]
                For satellite, used as polarization, value can be [0] horizontal | 1 vertical defaut[0]
            vo_format:
                The value of vo_format can be 1080P_60, 1080P_50, 1080i_60, 1080i_50, 720P_60, or 720P_50. The default value is 1080i_50.

   When the program is running, enter h to query the HDMI items that can be tested.
   For example,
hdmi_cmd >h
    help          list all command we provide
    q             quit sample test
    hdmi_debug    Display all relative status
    hdmi_deepcolor    set video deepcolor mode
    hdmi_xvycc        set video xvYCC output
    hdmi_video_timing set video output timing format
    hdmi_color_mode   set video color output(RGB/YCbCr)
    hdmi_a_freq       set audio output frequence
    hdmi_a_mute       set audio output mute/unmute
    hdmi_a_downsample set audio output downsample
    hdmi_av_mute      set video&audio mute/unmute
    hdmi_a_compress set audio output compress/uncompress type of PCM, AC3, DTS...
    hdmi_hdcp         set HDCP, to be define
    hdmi_cec          set CEC command, to be define
    dvb num           change to play program num

  Each of the preceding commands can be run individually.
  For example, you can run the hdmi_video_timing 0 command to set video timing to 1080p_60.
