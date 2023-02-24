cmake_minimum_required(VERSION 3.8)

set(INCDIR ${ROOTDIR}/Include/GG/GGTL)

set (SOURCE
    ${INCDIR}/List.h
    ${INCDIR}/MemUtil.h
)

add_library( 
    ggtl INTERFACE 
    ${SOURCE})

set_target_properties(ggtl PROPERTIES 
    CXX_STANDARD 20 )

target_include_directories( ggtl INTERFACE ${ROOTDIR}/Include)