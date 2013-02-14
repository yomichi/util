#include "../include/util/debug_dump.hpp"

int main()
{
  debug_dump("hoge", " ", 42);
  debug_dump_if(true, "hoge", " ", 42);
  debug_stream(std::cout, "hoge", " ", 137);
  debug_stream_if(true, std::cout, "hoge", " ", 137);
}

