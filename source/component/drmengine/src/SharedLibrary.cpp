#include <dlfcn.h>

#include "SharedLibrary.h"

namespace drmengine {

SharedLibrary::SharedLibrary(const std::string& path)
{
    LOGI_DRM("dlopen info %s\n",dlerror());
    m_pLibHandle = NULL;
    m_pLibHandle = dlopen(path.c_str(), RTLD_NOW);
    LOGI_DRM("dlopen info %s, m_pLibHandle = 0x%x\n",dlerror(), m_pLibHandle);
}

SharedLibrary::~SharedLibrary(void)
{
    if(NULL != m_pLibHandle)
    {
        dlclose(m_pLibHandle);
        m_pLibHandle = NULL;
    }
}

HI_BOOL SharedLibrary::operator!() const
{
    return (NULL == m_pLibHandle) ? HI_TRUE : HI_FALSE;
}

HI_VOID* SharedLibrary::lookup(const char* symbol) const
{
    if(!m_pLibHandle || NULL == symbol)
    {
        LOGE_DRM("lookup error, handle error!");
        return NULL;
    }

    HI_VOID* pFunc = dlsym(m_pLibHandle, symbol);
    if(NULL == pFunc)
    {
        LOGE_DRM("lookup func %s fail\n",symbol);
    }
    return pFunc;
}

const HI_CHAR* SharedLibrary::lastError() const
{
    const HI_CHAR* error = NULL;
    error = dlerror();
    return error ? error : "No dll error has been occured!";
}

}
