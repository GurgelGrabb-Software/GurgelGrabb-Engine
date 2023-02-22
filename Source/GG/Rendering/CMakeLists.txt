cmake_minimum_required(VERSION 3.8)

set(INCDIR ${ROOTDIR}/Include/GG/Rendering)
set(SRCDIR ${ROOTDIR}/Source/GG/Rendering)

set (SOURCE
   ${INCDIR}/GLInclude.h
   ${SRCDIR}/GLSetup.cpp

   ${INCDIR}/Shader.h
   ${SRCDIR}/Shader.cpp

   ${INCDIR}/ShaderProgram.h
   ${SRCDIR}/ShaderProgram.cpp

   ${INCDIR}/Window.h
   ${SRCDIR}/Window.cpp
   
   ${INCDIR}/VertexBuffer.h
   ${SRCDIR}/VertexBuffer.cpp
)

add_library( 
    Rendering STATIC 
    ${SOURCE})

set_target_properties(Rendering PROPERTIES 
    DEBUG_POSTFIX "-d" 
    OUTPUT_NAME "GG-Rendering"
    CXX_STANDARD 20 )

target_include_directories( Rendering PUBLIC ${ROOTDIR}/Include PUBLIC ${GLAD_DIR} PUBLIC ${GLFW_DIR} PUBLIC ${GLM_DIR} )

target_link_libraries(Rendering PUBLIC glfw)