功能描述一：展示本地TS流播放功能(支持选择MS12解码通路)
命令格式：sample_tsplay_ms12 file [vo_format] [bUseMS12]
参数说明：file：ts文件路径
          [vo_format]：输出制式，取值为1080P_60, 1080P_50, 1080i_60, 1080i_50, 720P_60, or 720P_50，缺省值为1080i_50
		  [bUseMS12]:  是否选择MS12解码通路，取值为 0 Adec解码通路，1 MS12解码通路。
		               注：MS12支持AAC/DDP音频协议，如果音频编码协议，MS12解码通路不支持，将自动选择到Adec解码通路。
命令参考：sample_tsplay ./test.ts 1080i_50 1          

MS12解码通路选择策略：
    sample参考代码包括两种选择MS12解码通路的方法，由宏ROUTE_MS12_METHOD_A/ROUTE_MS12_METHOD_B控制，用户可以参考。
	ROUTE_MS12_METHOD_A：（建议方法）
	                     识别到码流Format，根据用户意愿，进行相应MS12的Format转换。转换之前需要查询系统是否支持该MS12 Format。
	                     例如：识别到的Format（FORMAT_AAC）,如需要切换到MS12解码通路，先查询FORMAT_MS12_AAC是否支持，如支持将FORMAT_AAC修改为FORMAT_MS12_AAC。
	ROUTE_MS12_METHOD_B：
	                     识别码流Format，并转换为音频CodecID后，根据用户意愿，进行相应MS12 CodecID转换（篡改）。转换之前需要查询系统是否支持该MS12 Format。	                     
                             例如：识别到的Format（FORMAT_AAC）,并转换为AudioCodecID（HA_AUDIO_ID_AAC），如需要切换到MS12解码通路，先查询FORMAT_MS12_AAC是否支持，如支持将HA_AUDIO_ID_AAC修改为HA_AUDIO_ID_MS12_AAC。 

						 
功能描述二：展示本地MS12多路播放功能
命令格式：sample_ms12_mixer ts_file  [tts tts_file] [system uiaudio_file]
参数说明：file：ts文件路径
          tts:  创建tts播放通路
          system：创建ui audio播放通路
		  
命令参考: ./sample_ms12_mixer ./test.ts 
          ./sample_ms12_mixer null tts ./tts_48k_2ch.pcm
          ./sample_ms12_mixer null system  ./uiaudio_48_2ch.pcm
          ./sample_ms12_mixer ./test.ts  tts ./tts_48k_2ch.pcm system ./uiaudio_48_2ch.pcm

