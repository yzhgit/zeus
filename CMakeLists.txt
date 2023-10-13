cmake_minimum_required(VERSION 3.13)

# Only set the cxx_standard if it is not set by someone else
if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)

# Set the project name and language
project(
  zeus
  VERSION 0.0.1
  LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB SRCS src/zeus/*.cpp)

add_library(zeus ${SRCS})

target_include_directories(zeus PRIVATE
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_compile_definitions(zeus PRIVATE ZEUS_BASE_PRIVATE)
