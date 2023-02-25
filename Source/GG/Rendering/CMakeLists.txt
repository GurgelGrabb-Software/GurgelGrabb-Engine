cmake_minimum_required(VERSION 3.8)

set (SOURCE
   ${INCDIR}/GLInclude.h
   ${SRCDIR}/GLSetup.cpp

   ${INCDIR}/RenderTypes.h
   ${SRCDIR}/RenderTypes.cpp

   ${INCDIR}/ShaderParser.h
   ${SRCDIR}/ShaderParser.cpp

   ${INCDIR}/Shader.h
   ${SRCDIR}/Shader.cpp

   ${INCDIR}/ShaderProgram.h
   ${SRCDIR}/ShaderProgram.cpp

   ${INCDIR}/Window.h
   ${SRCDIR}/Window.cpp
   
   ${INCDIR}/VertexBuffer.h
   ${SRCDIR}/VertexBuffer.cpp

   ${INCDIR}/GraphicsUtilities.h
   ${SRCDIR}/GraphicsUtilities.cpp

   ${INCDIR}/Image.h
   ${SRCDIR}/Image.cpp
)

add_library( 
    ${PROJECT} STATIC 
    ${SOURCE})

set_target_properties(${PROJECT} PROPERTIES 
    DEBUG_POSTFIX "-d" 
    OUTPUT_NAME "GG-Rendering"
    CXX_STANDARD 20 )

target_include_directories( ${PROJECT} PUBLIC ${ROOTDIR}/Include PUBLIC ${GLAD_DIR} PUBLIC ${GLFW_DIR} PUBLIC ${GLM_DIR} PUBLIC ${STB_DIR} )

target_link_libraries(${PROJECT} PUBLIC glfw)