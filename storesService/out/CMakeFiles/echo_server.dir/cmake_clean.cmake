FILE(REMOVE_RECURSE
  "echo.pb.cc"
  "echo.pb.h"
  "CMakeFiles/echo_server.dir/server.cpp.o"
  "CMakeFiles/echo_server.dir/echo.pb.cc.o"
  "echo_server.pdb"
  "echo_server"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang CXX)
  INCLUDE(CMakeFiles/echo_server.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
