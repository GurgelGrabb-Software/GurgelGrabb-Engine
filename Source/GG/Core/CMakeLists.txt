cmake_minimum_required(VERSION 3.8)

set(INCDIR ${ROOTDIR}/Include/GG/Core)
set(SRCDIR ${ROOTDIR}/Source/GG/Core)

set (H 
    ${INCDIR}/Engine.h)
set (CPP 
    ${SRCDIR}/Engine.cpp)

set (SOURCE
    ${H}
    ${CPP}
)

add_library( 
    Core STATIC 
    ${SOURCE})

set_target_properties(Core PROPERTIES 
    DEBUG_POSTFIX "-d" 
    OUTPUT_NAME "GG-Core" )

source_group("Headers" ${H})
source_group("Code" ${CPP})

target_include_directories( Core PUBLIC ${ROOTDIR}/Include )
target_link_libraries( Core PRIVATE Rendering )