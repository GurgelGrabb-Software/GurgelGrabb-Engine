cmake_minimum_required(VERSION 3.8)

set(INCDIR ${ROOTDIR}/Include/GG/Core)
set(SRCDIR ${ROOTDIR}/Source/GG/Core)

set (SOURCE
    ${INCDIR}/Engine.h
    ${SRCDIR}/Engine.cpp

    ${INCDIR}/Objects/Object.h
    ${SRCDIR}/Objects/Object.cpp
    ${INCDIR}/Objects/Component.h

    ${INCDIR}/Math/Mat4x4.h
    ${SRCDIR}/Math/Mat4x4.cpp
    
    ${INCDIR}/Utility/Logging.h
    ${SRCDIR}/Utility/Logging.cpp
    
    ${INCDIR}/Service/ServiceProviderInterface.h
    ${INCDIR}/Service/ServiceInterface.h
    ${SRCDIR}/Service/ServiceProvider.h
    ${SRCDIR}/Service/ServiceProvider.cpp
)

add_library( 
    Core STATIC 
    ${SOURCE})

set_target_properties(Core PROPERTIES 
    DEBUG_POSTFIX "-d" 
    OUTPUT_NAME "GG-Core"
    CXX_STANDARD 20 )

target_include_directories( Core PUBLIC ${ROOTDIR}/Include PUBLIC ${GLM_DIR})
target_link_libraries( Core PRIVATE Rendering )