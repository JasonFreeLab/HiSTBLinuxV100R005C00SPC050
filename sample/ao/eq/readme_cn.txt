功能描述: 设置peq参数
linux   命令格式: ./sample_peqconfig [port]
Android 命令格式：  sample_peqconfig [port]
参数说明：如下是不同port口对应的值
          DAC0   = 0
          I2S0   = 1
          I2S1   = 2
          SPDIF0 = 3
          HDMI0  = 4
          ARC0   = 5
          DAC1   = 80
          DAC2   = 81
          DAC3   = 82
          ALL    = 32767

linux   例子: ./sample_peqconfig 0
Android 例子：sample_peqconfig 0

注意事项：不同的滤波器对应不同的范围
          <1> HP:(高通滤波器)：    q值： 7
                                   freq: 20 ~ 4000
                                   gain: -15000 ~ 15000

          <2> LP:(低通滤波器)：    q值： 7
                                   freq: 4000 ~ 22000
                                   gain: -15000 ~ 15000

          <3> HS:(高频搁架滤波器)：q值： 7 ~ 10
                                   freq: 4000 ~ 22000
                                   gain: -15000 ~ 15000

          <4> LS:(低频搁架滤波器)：q值：7 ~ 10
                                   freq: 20~ 4000
                                   gain: -15000 ~ 15000

          <5> PK:(峰值滤波器)：    q值： 5 ~ 10
                                   freq:  20 ~ 22000
                                   gain: -15000 ~ 15000
============================================================================================

功能描述: 设置geq参数
linux   命令格式: ./sample_geqconfig
Andorid 命令格式：sample_geqconfig

linux   例子: ./sample_geqconfig
Android 例子：sample_geqconfig

注意事项：无
