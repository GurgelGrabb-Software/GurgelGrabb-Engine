cmake_minimum_required( VERSION 3.8 )

set(INCDIR ${ROOTDIR}/Include/GG/App)
set(SRCDIR ${ROOTDIR}/Source/GG/App)

set (SOURCE
    ${SRCDIR}/Main.cpp
    )

add_executable( 
    Application 
    ${SOURCE})

set_target_properties(Application PROPERTIES 
    DEBUG_POSTFIX "-d" 
    OUTPUT_NAME "GG-App"
    CXX_STANDARD 20 )

target_include_directories(Application PUBLIC ${ROOTDIR}/Include PUBLIC ${GLM_DIR} )
target_link_libraries( Application PRIVATE Core )