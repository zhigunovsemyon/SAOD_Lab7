# CMakeList.txt : CMake project for SAOD_Lab7, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (SAOD_Lab7 "main.cc" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SAOD_Lab7 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
