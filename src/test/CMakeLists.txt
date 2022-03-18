

if(ENABLE_TESTING)
    add_executable(ereolenwrappertests ereolenWrapperTests.cpp)
    target_sources(ereolenwrappertests PRIVATE
            ereolenWrapperTests.cpp
            Secrets.cpp Secrets.h
            AuthTests.cpp ApiEnvTests.cpp ProfileTests.cpp
            )
    target_link_libraries(ereolenwrappertests PRIVATE ereolenwrapper gtest gmock gtest_main)
    gtest_discover_tests(ereolenwrappertests)
endif()
