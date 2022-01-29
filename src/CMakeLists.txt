add_executable(ereolenwrapper ereolenwrapper.cpp)
#target_sources(ereolenwrapper PRIVATE 
#
#)

target_link_libraries(ereolenwrapper PRIVATE nlohmann_json::nlohmann_json)


if(ENABLE_TESTING)
    add_executable(simple_test)
    target_sources(simple_test PRIVATE simple_test.cc)
    target_link_libraries(simple_test PRIVATE simple gtest gmock gtest_main)
    gtest_discover_tests(simple_test)
endif()
