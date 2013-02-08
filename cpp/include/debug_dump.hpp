#undef debug_dump
#undef debug_stream

#ifdef NDEBUG
#define debug_dump(arg) do{ std::cerr << arg << std::endl;}while(0)
#define debug_dump(arg, cond) do{if(cond) std::cerr << arg << std::endl;}while(0)
#define debug_stream(arg, os) do{os << arg << std::endl;}while(0)
#define debug_stream(arg, os, cond) do{if(cond) os << arg << std::endl;}whjile(0)
#else
#define debug_dump(arg) ((void)0)
#define debug_dump(arg, cond)  ((void)0)
#define debug_stream(arg, os) ((void)0)
#define debug_stream(arg, os, cond) ((void)0)
#endif

