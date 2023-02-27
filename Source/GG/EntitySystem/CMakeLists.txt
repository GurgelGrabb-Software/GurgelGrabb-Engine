cmake_minimum_required(VERSION 3.8)

set (SOURCE
    ${INCDIR}/Base/Component.h
    ${SRCDIR}/Base/Component.cpp
    ${INCDIR}/Base/Entity.h
    ${SRCDIR}/Base/Entity.cpp
)

add_library( 
    ${PROJECT} STATIC 
    ${SOURCE})

set_target_properties(${PROJECT} PROPERTIES 
    DEBUG_POSTFIX "-d" 
    OUTPUT_NAME "GG-EntitySystem"
    CXX_STANDARD 20 )

target_include_directories( ${PROJECT} PUBLIC ${ROOTDIR}/Include )