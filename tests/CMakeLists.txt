include(GoogleTest)

if(WIN32)
    find_package(GTest CONFIG REQUIRED)
    set(GTest_LIBRARIES GTest::gtest GTest::gtest_main)
else()
    set(GTest_LIBRARIES gtest gtest_main)
endif()

add_executable(proi_auto_tests dummy_test.cpp)
target_link_libraries(proi_auto_tests PRIVATE ${GTest_LIBRARIES})
gtest_discover_tests(proi_auto_tests)