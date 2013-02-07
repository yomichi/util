#undef debug_dump
#undef debug_stream

#ifdef DEBUG_DUMP
#define debug_dump(arg) std::cerr << arg << std::endl
#define debug_dump(arg, cond) if(cond) std::cerr << arg << std::endl
#define debug_stream(arg, os) os << arg << std::endl
#define debug_stream(arg, os, cond) if(cond) os << arg << std::endl
#else
#define debug_dump(arg) ((void)0)
#define debug_dump(arg, cond)  ((void)0)
#define debug_stream(arg, os) ((void)0)
#define debug_stream(arg, os, cond) ((void)0)
#endif

