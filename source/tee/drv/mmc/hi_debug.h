#ifndef HI_DEBUG
#define HI_DEBUG

#ifdef CONFIG_DEBUG
#  include <trace.h>
#  define ASSERT(_p) if (!(_p)) { \
	printf("%s(%s,%d):assert:(%s)\n", __FILE__, __FUNCTION__, __LINE__, #_p); \
	dump_stack();}
#  define ASSERT1(_p, _fmt, args...) if (!(_p)) { \
	printf("%s(%s,%d):assert:(%s)\n" _fmt, __FILE__, __FUNCTION__, __LINE__, #_p, ##args); \
	dump_stack();}
#else
#  define ASSERT(_p)
#  define ASSERT1(_p, _fmt, args...)
#endif

#define pr_error(_fmt, args...)  	printf(MOULE_NAME "*** " _fmt, ##args)
#define pr_warn(_fmt, args...)   	printf(MOULE_NAME "!!! " _fmt, ##args)
#define pr_info(_fmt, args...)   	printf(MOULE_NAME _fmt, ##args)
#define pr_debug(_fmt, args...)  	printf(MOULE_NAME "debug! " _fmt, ##args)

#endif
