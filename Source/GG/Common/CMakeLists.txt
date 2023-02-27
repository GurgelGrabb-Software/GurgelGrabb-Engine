cmake_minimum_required(VERSION 3.8)

set (SOURCE
    ${INCDIR}/Container/List.h
    ${INCDIR}/Helpers/MemUtil.h
)

add_library( 
    ${PROJECT} INTERFACE
    ${SOURCE})

set_target_properties(${PROJECT} PROPERTIES 
    CXX_STANDARD 20 )

target_compile_features(${PROJECT} INTERFACE cxx_std_20)
target_include_directories( ${PROJECT} INTERFACE ${ROOTDIR}/Include)