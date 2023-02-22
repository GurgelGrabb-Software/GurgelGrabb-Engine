cmake_minimum_required(VERSION 3.8)

set(GG_VER 0.0.1)
set(ROOTDIR ${CMAKE_SOURCE_DIR})
set(OUTDIR ${ROOTDIR}/Output)
set(LIBDIR ${OUTDIR}/Lib)
set(EXEDIR ${OUTDIR}/Bin)
set(EXT_LIBDIR ${ROOTDIR}/ThirdParty/Lib)

set( GLFW_DIR ${ROOTDIR}/ThirdParty/GLFW/include )  
set( GLAD_DIR ${ROOTDIR}/ThirdParty/GLAD)
set( GLM_DIR ${ROOTDIR}/ThirdParty/GLMath)

message( "GLFW dir: ${GLFW_DIR}")
message( "glad dir: ${GLAD_DIR}" )
message( "GLM dir: ${GLM_DIR}" )


project(
    GG_Engine_Suite
    VERSION ${GG_VER}
    DESCRIPTION "Full GG Engine Suite"
    LANGUAGES CXX
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${LIBDIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${EXEDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${EXEDIR})

add_subdirectory(Source/GG)
add_subdirectory(ThirdParty/GLFW)

