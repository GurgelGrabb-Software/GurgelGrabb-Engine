cmake_minimum_required(VERSION 3.8)

set(GG_VER 0.0.1)
set(ROOTDIR ${CMAKE_SOURCE_DIR})

project(
    GG_Engine_Suite
    VERSION ${GG_VER}
    DESCRIPTION "Full GG Engine Suite"
    LANGUAGES CXX
)

add_subdirectory(Source/GG)

