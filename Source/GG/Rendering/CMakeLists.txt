cmake_minimum_required(VERSION 3.8)

set(INCDIR ${ROOTDIR}/Include/GG/Rendering)
set(SRCDIR ${ROOTDIR}/Source/GG/Rendering)

set (H 
   ${INCDIR}/Window.h )
set (CPP 
    ${SRCDIR}/RenderingCore.cpp
    ${SRCDIR}/Window.cpp 
   )

set (SOURCE
    ${H}
    ${CPP}
)

add_library( 
    Rendering STATIC 
    ${SOURCE})

set_target_properties(Rendering PROPERTIES 
    DEBUG_POSTFIX "-d" 
    OUTPUT_NAME "GG-Rendering"
    CXX_STANDARD 20 )

source_group("Headers" ${H})
source_group("Code" ${CPP})


target_include_directories( Rendering PUBLIC ${ROOTDIR}/Include PUBLIC ${GLAD_DIR} PUBLIC ${GLFW_DIR} )

target_link_libraries(Rendering PUBLIC glfw)