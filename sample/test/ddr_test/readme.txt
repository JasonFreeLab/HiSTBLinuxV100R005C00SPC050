usage£º
Usage: ./sample_performance format ts_file1 ts_file2
        format  - 2160P_60, 2160P_50, 2160P_25,1080P_60, 1080P_50, 1080i_60, 1080i_50, 720P_60, 720P_50, 576P_50, 480P_60, PAL. default 1080i_50
		
        for Hi3798mv200: 
            ts_file1 should be a 4KP60 stream,  
            ts_file2 should be 1080i60 stream,
            format should be 2160P60
example:
        ./sample_performance 1080i_50 ./cctv1.ts ./cctv1.ts 


note£º
1. the encoded data is dropped without being saved to the files.
2. the gpu should be open while compiling the whole sdk
3. if you want to copy this sample to the boad: 
	1) besides the sample image, the sample/res/ddr_test also need to be copyed the board; 
	2) check and change macros GPU_SOURCE_FILENAME_VS_ES20T4 GPU_SOURCE_FILENAME_VS_ES20T4_GLASS GPU_SOURCE_FILENAME_VS_ES20T4_BGRND GPU_SOURCE_FILENAME_VS_STPETERS in hi_gpu.c
	3) check and change macros PIC_FILENAME in hi_osd.c
4. 	ts_file1 and ts_file2 could be located on the flash, mounted u_disk or nfs files

