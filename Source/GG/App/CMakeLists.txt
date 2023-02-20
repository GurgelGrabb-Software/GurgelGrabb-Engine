cmake_minimum_required( VERSION 3.8 )

set(INCDIR ${ROOTDIR}/Include/GG/App)
set(SRCDIR ${ROOTDIR}/Source/GG/App)

set(H 
    "")

set(CPP
    ${SRCDIR}/Main.cpp)

set (SOURCE
    ${H}
    ${CPP})

add_executable( 
    Application 
    ${SOURCE})

set_target_properties(Application PROPERTIES 
    DEBUG_POSTFIX "-d" 
    OUTPUT_NAME "GG-App"
    CXX_STANDARD 20 )

source_group("Headers" ${H})
source_group("Code" ${CPP})

target_include_directories(Application PUBLIC ${ROOTDIR}/Include )
target_link_libraries( Application PRIVATE Core )