

if(ENABLE_TESTING)
    add_executable(ereolenwrappertests)
    target_sources(ereolenwrappertests PRIVATE ereolenWrapperTests.cpp)
    target_link_libraries(ereolenwrappertests PRIVATE ereolenwrapper gtest gmock gtest_main)
    gtest_discover_tests(ereolenwrappertests)
endif()
