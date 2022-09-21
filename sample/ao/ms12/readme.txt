Introduction 1: Sample of playing the of the local ts file.(support MS12 decoding path)
Purpose: sample_tsplay_ms12 file [vo_format] [bUseMS12]
      file: TS file path
      vo_format: video output mode in high definition. Value range: 1080P_60|1080P_50|1080i_60|[1080i_50]|720P_60|720P_50. Default value: 1080i_50
                The standard definition mode is set automatically inside based on the high definition mode.
      bUseMS12: route Ms12 decoding path or not. 0: no ms12 path. 1: ms12 path.
      
Reference command: sample_tsplay_ms12 ./test.ts 1080i_50 1      

MS12 decoding path route policy:
     There are two methods provided by sample. Selected by macro ROUTE_MS12_METHOD_A/ROUTE_MS12_METHOD_B. you can refer to this.
     
     ROUTE_MS12_METHOD_A: (recommended method)
             According to the user's select, Change the audio stream type identified to corresponding MS12 stream type. Before that, you need to check if this audio stream type is supported.
             for example: FORMAT_AAC being identified, you can change it to FORMAT_MS12_AAC. (FORMAT_MS12_AAC is supportted)
             
     ROUTE_MS12_METHOD_B:
             According to the user's select, Change the audio codec id identified to corresponding MS12 codec id. Before that, you need to check if this audio stream type is supported.
             for example: FORMAT_AAC is identified, and AudioCodecID£¨HA_AUDIO_ID_AAC£©is found, you can change AudioCodecID to HA_AUDIO_ID_MS12_AAC. (FORMAT_MS12_AAC is supportted)
             
             
             
Introduction 2: Sample of ms12 mixing multi sources.
Purpose: sample_ms12_mixer ts_file  [tts tts_file] [system uiaudio_file]
      file: TS file path, if disable, input null
      tts: create tts source
      system: create ui audio source
      
Reference command:  
          ./sample_ms12_mixer ./test.ts 
          ./sample_ms12_mixer null tts ./tts_48k_2ch.pcm
          ./sample_ms12_mixer null system  ./uiaudio_48_2ch.pcm
          ./sample_ms12_mixer ./test.ts  tts ./tts_48k_2ch.pcm system ./uiaudio_48_2ch.pcm  