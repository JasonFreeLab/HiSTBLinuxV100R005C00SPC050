Introduction: Sample of playing the of the local ts file through TSIO
Purpose: sample_tsio_tsplay file [vo_format]
      file: TS file path
      vo_format: video output mode in high definition. Value range: 1080P_60|1080P_50|1080i_60|[1080i_50]|720P_60|720P_50. Default value: 1080i_50
                The standard definition mode is set automatically inside based on the high definition mode.
Command: sample_tsio_tsplay ./test.ts

Introduction:  Sample of playing the live stream through TSIO
Purpose: sample_tsio_dvbplay freq srate [qamtype or polarization] [vo_format]
      Fields [qamtype or polarization] and [vo_format] are optional.
      qamtype or polarization:
          For cable, used as qamtype, value can be 16|32|[64]|128|256|512 defaut[64]
          For satellite, used as polarization, value can be [0] horizontal | 1 vertical defaut[0]
      vo_format:
          The value of vo_format can be 1080P_60, 1080P_50, 1080i_60, 1080i_50, 720P_60, or 720P_50. The default value is 
          1080i_50.
Command: sample_tsio_dvbplay 618 6875 64

Introduction: Sample of bulk stream through TSIO
Purpose: sample_tsio_bulk file
				file: bulk file path
Command: sample_tsio_bulk ./test.bulk
