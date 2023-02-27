cmake_minimum_required(VERSION 3.8)

set (SOURCE
    ${INCDIR}/Engine.h
    ${SRCDIR}/Engine.cpp

    ${INCDIR}/Objects/Transform.h
    ${SRCDIR}/Objects/Transform.cpp

    ${INCDIR}/Math/Mat4x4.h
    ${SRCDIR}/Math/Mat4x4.cpp
    ${INCDIR}/Math/Vec3.h
    ${SRCDIR}/Math/Vec3.cpp
    
    ${INCDIR}/Utility/Logging.h
    ${SRCDIR}/Utility/Logging.cpp
    ${INCDIR}/Utility/Timer.h
    ${SRCDIR}/Utility/Timer.cpp
    ${INCDIR}/Utility/StringID.h
    ${SRCDIR}/Utility/StringID.cpp
    
    ${INCDIR}/Threading/WorkFunction.h
    ${INCDIR}/Threading/ThreadPool.h
    ${SRCDIR}/Threading/ThreadPool.cpp
    ${INCDIR}/Threading/ThreadObject.h
    ${SRCDIR}/Threading/ThreadObject.cpp
    
    ${INCDIR}/Messaging/BaseMessage.h
    ${INCDIR}/Messaging/MessageSubscriberList.h
    ${INCDIR}/Messaging/MessageQueue.h
    ${SRCDIR}/Messaging/MessageQueue.cpp
    ${INCDIR}/Messaging/SubscriptionHandle.h
    ${SRCDIR}/Messaging/SubscriptionHandle.cpp
    ${INCDIR}/Messaging/Subscriptions.h
    ${SRCDIR}/Messaging/Subscriptions.cpp
    
    ${INCDIR}/Service/ServiceProviderInterface.h
    ${INCDIR}/Service/ServiceInterface.h
    ${SRCDIR}/Service/ServiceProvider.h
    ${SRCDIR}/Service/ServiceProvider.cpp
)

add_library( 
    ${PROJECT} STATIC 
    ${SOURCE})

set_target_properties(${PROJECT} PROPERTIES 
    DEBUG_POSTFIX "-d" 
    OUTPUT_NAME "GG-Core"
    CXX_STANDARD 20 )

target_include_directories( ${PROJECT} PUBLIC ${ROOTDIR}/Include PUBLIC ${GLM_DIR} PUBLIC ${FMT_DIR})
target_link_libraries( ${PROJECT} 
    PRIVATE Rendering 
    PUBLIC fmt::fmt )