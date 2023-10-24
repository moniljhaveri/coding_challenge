# CMakeList.txt : CMake project for wc, include source and define
# project specific logic here.
project(wc)

# Add source to this project's executable.
cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)


add_library(libFileProperties "${CMAKE_CURRENT_SOURCE_DIR}/FileProperties.h" "${CMAKE_CURRENT_SOURCE_DIR}/FileProperties.cpp")

add_executable (wc "wc.h" "wc.cpp")
target_link_libraries(wc libFileProperties)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET wc PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
