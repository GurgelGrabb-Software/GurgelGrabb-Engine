cmake_minimum_required(VERSION 3.8)

set(INCDIR ${ROOTDIR}/Include/GG/Core)
set(SRCDIR ${ROOTDIR}/Source/GG/Core)

set (H 
    ${INCDIR}/Engine.h
    ${INCDIR}/Objects/Object.h
    ${INCDIR}/Objects/Component.h
    ${INCDIR}/Utility/Logging.h
    ${INCDIR}/Service/ServiceInterface.h
    ${INCDIR}/Service/ServiceProviderInterface.h
    ${SRCDIR}/Service/ServiceProvider.h)
    
set (CPP 
    ${SRCDIR}/Engine.cpp
    ${SRCDIR}/Objects/Object.cpp
    ${SRCDIR}/Utility/Logging.cpp
    ${SRCDIR}/Service/ServiceProvider.cpp )

set (SOURCE
    ${H}
    ${CPP}
)

add_library( 
    Core STATIC 
    ${SOURCE})

set_target_properties(Core PROPERTIES 
    DEBUG_POSTFIX "-d" 
    OUTPUT_NAME "GG-Core"
    CXX_STANDARD 20 )

source_group("Headers" ${H})
source_group("Code" ${CPP})

target_include_directories( Core PUBLIC ${ROOTDIR}/Include )
target_link_libraries( Core PRIVATE Rendering )