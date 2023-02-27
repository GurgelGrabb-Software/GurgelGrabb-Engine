cmake_minimum_required( VERSION 3.8 )


set (SOURCE
    ${SRCDIR}/Main.cpp
    )

add_executable( 
    ${PROJECT}
    ${SOURCE})

set_target_properties(${PROJECT} PROPERTIES 
    DEBUG_POSTFIX "-d" 
    OUTPUT_NAME "GG-App"
    CXX_STANDARD 20 )

target_compile_features(${PROJECT} PUBLIC cxx_std_20)

target_include_directories(${PROJECT} PUBLIC ${ROOTDIR}/Include PUBLIC ${GLM_DIR} PUBLIC ${FMT_DIR} )
target_link_libraries( ${PROJECT} PRIVATE Core )