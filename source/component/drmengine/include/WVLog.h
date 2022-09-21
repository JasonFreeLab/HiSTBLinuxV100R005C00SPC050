#ifndef WV_LOG_H_
#define WV_LOG_H_

namespace wvdrm {

// Simple logging class. The implementation is platform dependent.

typedef enum {
  LOG_ERROR,
  LOG_WARN,
  LOG_INFO,
  LOG_DEBUG,
  LOG_VERBOSE
} LogLevel;

extern LogLevel g_cutoff;

// Enable/disable verbose logging (LOGV).
// This function is supplied for cases where the system layer does not
// initialize logging.  This is also needed to initialize logging in
// unit tests.
void InitLogging_Drm();

void Log_Drm(const char* file, int line, LogLevel level, const char* fmt, ...);

// Log APIs
#define LOGE_DRM(...) Log_Drm(__FILE__, __LINE__, wvdrm::LOG_ERROR, __VA_ARGS__)
#ifdef DRMENGINE_DEBUG
#define LOGW_DRM(...) Log_Drm(__FILE__, __LINE__, wvdrm::LOG_WARN, __VA_ARGS__)
#define LOGI_DRM(...) Log_Drm(__FILE__, __LINE__, wvdrm::LOG_INFO, __VA_ARGS__)
#define LOGD_DRM(...) Log_Drm(__FILE__, __LINE__, wvdrm::LOG_DEBUG, __VA_ARGS__)
#define LOGV_DRM(...) Log_Drm(__FILE__, __LINE__, wvdrm::LOG_VERBOSE, __VA_ARGS__)
#else
#define LOGW_DRM(...)
#define LOGI_DRM(...)
#define LOGD_DRM(...)
#define LOGV_DRM(...)
#endif

}  // namespace wvcdm

#endif  // WVCDM_CORE_LOG_H_

