cmake_minimum_required(VERSION 3.8)

set(INCDIR ${ROOTDIR}/Include/GG/Rendering)
set(SRCDIR ${ROOTDIR}/Source/GG/Rendering)

set (H 
   ${INCDIR}/Window.h )
set (CPP 
   ${SRCDIR}/Window.cpp )

set (SOURCE
    ${H}
    ${CPP}
)

add_library( 
    Rendering STATIC 
    ${SOURCE})

set_target_properties(Core PROPERTIES 
    DEBUG_POSTFIX "-d" 
    OUTPUT_NAME "GG-Rendering" )

source_group("Headers" ${H})
source_group("Code" ${CPP})

target_include_directories( Rendering PUBLIC ${ROOTDIR}/Include )
target_include_directories( Rendering PUBLIC ${EXT_INCDIR}/SDL )

if (WIN32)
    target_link_libraries(Rendering debug ${EXT_LIBDIR}/SDL2-d.lib)
    target_link_libraries(Rendering optimized ${EXT_LIBDIR}/SDL2.lib)
endif (WIN32)