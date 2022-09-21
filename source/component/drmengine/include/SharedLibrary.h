#ifndef SHARED_LIBRARY_H_
#define SHARED_LIBRARY_H_

#include <string>
#include "hi_type.h"
#include "WVLog.h"

namespace drmengine {

class SharedLibrary
{
public:
    SharedLibrary(const std::string& path);
    virtual ~SharedLibrary(void);

    HI_BOOL operator!() const;
    HI_VOID* lookup(const char* symbol) const;
    const HI_CHAR* lastError() const;

private:
    HI_VOID* m_pLibHandle;
};

}

#endif
