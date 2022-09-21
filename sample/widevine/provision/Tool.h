#ifndef __MODULAR_TOOL_H__
#define __MODULAR_TOOL_H__


//#include <iostream>
//#include <fstream>
//mod by sunlei begin
//#include <utils/String8.h>
//#include <utils/Log.h>
  #include <iostream>
  #include <fstream>
//mod by sunlei end

using namespace std;

namespace android {
    class wv_provision {
    public:
        wv_provision();
        ~wv_provision() {}

        int HI_CIPHER_GetRandom(unsigned char *pRand, int len);
        int HI_OTP_Burn_STBRootKey(unsigned char*pKey, int len);

	 //del by sunlei begin
        int HI_Flash_WriteDRMData(char *mtdname, unsigned int u32Offset, char *pBuffer, unsigned int u32BufferSize);
        int HI_Flash_ReadDRMData(char *mtdname, unsigned int u32Offset, char *pBuffer, unsigned int u32BufferSize);
	
	 //del by sunlei end
    private:
        string mWVKeybox;
    };
};


#endif /* __TOOL_H__ */
