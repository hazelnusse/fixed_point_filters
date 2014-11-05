cmake_minimum_required(VERSION 2.8)
project(EMBEDDED_FILTER CXX)
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -std=c11 -Wall -Werror -Weffc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb3")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -ggdb3")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
    "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
    FORCE)
endif()

find_package(GTest REQUIRED)
enable_testing()

add_subdirectory(tests)

