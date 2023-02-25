cmake_minimum_required(VERSION 3.8)

set(SRCDIR ${ROOTDIR}/Test/Common)
set(SOURCE
    ${SRCDIR}/Container/List.cpp
)



add_executable(CommonTests
    ${SOURCE}
)
target_link_libraries( CommonTests PUBLIC GTest::gtest_main )
target_include_directories(CommonTests PUBLIC ${EXT_DIR}/googletest/googletest/include PUBLIC ${ROOTDIR}/Include/)
include(GoogleTest)
gtest_discover_tests(CommonTests)

