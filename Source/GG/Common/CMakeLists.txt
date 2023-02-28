cmake_minimum_required(VERSION 3.8)

file(GLOB_RECURSE SRC TRUE ${SRCDIR}/ "*.cpp" "*.h")
file(GLOB_RECURSE API TRUE ${INCDIR}/ "*.h")

set(SOURCE 
    ${SRC}
    ${API} )

add_library( 
    ${PROJECT} INTERFACE
    ${SOURCE})

set_target_properties(${PROJECT} PROPERTIES 
    CXX_STANDARD 20 )

target_compile_features(${PROJECT} INTERFACE cxx_std_20)
target_include_directories( ${PROJECT} INTERFACE ${ROOTDIR}/Include)