# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/ToooDo_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/ToooDo_autogen.dir/ParseCache.txt"
  "ToooDo_autogen"
  )
endif()
