include(GoogleTest)

if(WIN32)
    find_package(GTest CONFIG REQUIRED)
    set(GTest_LIBRARIES GTest::gtest GTest::gtest_main)
else()
    pkg_check_modules(GTest REQUIRED gtest_main)
    include_directories(${GTest_INCLUDE_DIRS})
endif()

add_executable(proi_auto_tests tools.cpp scenarios.cpp)
target_link_libraries(proi_auto_tests PRIVATE ${GTest_LIBRARIES} ${SDL2_LIBRARIES})
target_link_libraries(proi_auto_tests PRIVATE proi_auto_logic)
gtest_discover_tests(proi_auto_tests)
