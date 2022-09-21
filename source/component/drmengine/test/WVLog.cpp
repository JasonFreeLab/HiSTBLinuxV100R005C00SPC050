#include "WVLog.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace wvdrm {

LogLevel g_cutoff = LOG_VERBOSE;

void InitLogging_Drm() {}

void Log_Drm(const char* file, int line, LogLevel level, const char* fmt, ...) {
  const char* severities[] = { "ERROR", "WARN", "INFO", "DEBUG", "VERBOSE" };
  if (level >= sizeof(severities) / sizeof(*severities)) {
    fprintf(stderr, "[FATAL:%s(%d)] Invalid log priority level: %d\n",
            file, line, level);
    return;
  }
  if (level > g_cutoff) return;

  fprintf(stderr, "[%s:%s(%d)] ", severities[level], file, line);

  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);

  putc('\n', stderr);
  fflush(stderr);
}

}  // namespace wvcdm

