cmake_minimum_required(VERSION 3.8)


option(GG_BUILD_VERBOSE "Build with high verbosity")
option(BUILD_TESTS "Tests will be built with this config")

if(BUILD_TESTS)
    enable_testing()
endif()

if(GG_BUILD_VERBOSE)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()

# SET GLOBAL VARIABLES
set(GG_VER 0.0.1)
set(ROOTDIR ${CMAKE_SOURCE_DIR})
set(OUTDIR ${ROOTDIR}/Output)
set(LIBDIR ${OUTDIR}/Lib)
set(EXEDIR ${OUTDIR}/Bin)
set(EXT_LIBDIR ${ROOTDIR}/ThirdParty/Lib)

# DEFINE MACROS/FUNCTIONS FOR NEATER LOGGING
macro(PRINT_VAR v)
    message("> ${v} ${${v}}")
endmacro()

macro(LOG_START c)
    message("\n--- ${c} ---")
endmacro()

macro(LOG_MSG msg)
    message("> ${msg}")
endmacro()

message( "=== GG CMAKE START ===" )

# SET COMPILE DEFINITIONS FOR APPLE/WIN32
set(OS_COMPILE_DEF Unknown)
if(APPLE)
set(OS_COMPILE_DEF APPLE)
elseif(WIN32)
set(OS_COMPILE_DEF WIN32)
endif()

LOG_START("OS CMP DEF")
LOG_MSG("OS: ${OS_COMPILE_DEF}")
add_compile_definitions(${OS_COMPILE_DEF})


LOG_START("THIRD PARTY LIB PATHS")
set( GLFW_DIR ${ROOTDIR}/ThirdParty/GLFW/include )  
set( GLAD_DIR ${ROOTDIR}/ThirdParty/GLAD)
set( GLM_DIR ${ROOTDIR}/ThirdParty/GLMath)
set( STB_DIR ${ROOTDIR}/ThirdParty/STB)
set( FMT_DIR ${ROOTDIR}/ThirdParty/FMT/include )
PRINT_VAR(GLFW_DIR)
PRINT_VAR(GLAD_DIR)
PRINT_VAR(GLM_DIR)
PRINT_VAR(FMT_DIR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

LOG_START("CREATE PROJECT")
LOG_MSG("Version ${GG_VER}")
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

LOG_START("ADD GG DIRECTORIES")
add_subdirectory(Source/GG)

LOG_START("ADD THIRD PARTY DIRECTORIES")
add_subdirectory(ThirdParty/GLFW)
add_subdirectory(ThirdParty/FMT)

if(BUILD_TESTS)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory(ThirdParty/googletest)
    add_subdirectory(Test)
endif()

message( "=== GG CMAKE END ===" )