cmake_minimum_required(VERSION 3.8)

file(GLOB_RECURSE SRC TRUE ${SRCDIR}/ "*.cpp" "*.h")
file(GLOB_RECURSE API TRUE ${INCDIR}/ "*.h")

set(SOURCE 
    ${SRC}
    ${API} )

add_library( 
    ${PROJECT} STATIC 
    ${SOURCE})

set_target_properties(${PROJECT} PROPERTIES 
    DEBUG_POSTFIX "-d" 
    OUTPUT_NAME "GG-Rendering"
    CXX_STANDARD 20 )

target_compile_features(${PROJECT} PUBLIC cxx_std_20)

target_include_directories( ${PROJECT} PUBLIC ${ROOTDIR}/Include PUBLIC ${GLAD_DIR} PUBLIC ${GLFW_DIR} PUBLIC ${GLM_DIR} PUBLIC ${STB_DIR} PUBLIC ${FMT_DIR} )

target_link_libraries(${PROJECT} PUBLIC glfw)