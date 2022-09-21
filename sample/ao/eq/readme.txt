Purpose: to set peq parameter
linux   Command: ./sample_peqconfig [port]
Android Command:   sample_peqconfig [port]

[port] parameter instruction:
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

For example:
linux  : ./sample_peqconfig 0
Android: sample_peqconfig 0

note: different peq filter types have different range limits
          <1> HP: Q：   7
                  freq: 20 ~ 4000
                  gain: -15000 ~ 15000

          <2> LP: Q：   7
                  freq: 4000 ~ 22000
                  gain: -15000 ~ 15000

          <3> HS: Q：   7 ~ 10
                  freq: 4000 ~ 22000
                  gain: -15000 ~ 15000

          <4> LS: Q：   7 ~ 10
                  freq: 20~ 4000
                  gain: -15000 ~ 15000

          <5> PK: Q：   5 ~ 10
                  freq: 20 ~ 22000
                  gain: -15000 ~ 15000

=========================================================================================
Purpose: to set geq parameter
linux   Command: ./sample_geqconfig
Android Command: sample_geqconfig
