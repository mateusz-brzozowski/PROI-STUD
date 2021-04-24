include(GoogleTest)

if(WIN32)
    find_package(GTest CONFIG REQUIRED)
    set(GTest_LIBRARIES GTest::gtest GTest::gtest_main)
else()
    pkg_check_modules(GTest REQUIRED gtest_main)
    include_directories(${GTest_INCLUDE_DIRS})
endif()

add_executable(proi_auto_tests dummy_test.cpp)
target_link_libraries(proi_auto_tests PRIVATE ${GTest_LIBRARIES})
gtest_discover_tests(proi_auto_tests)
