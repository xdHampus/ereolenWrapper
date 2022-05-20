project("eReolenWrapper C Interface Tests" C) 
cmake_minimum_required(VERSION 3.0)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

find_package(unity 2.5.2 REQUIRED)
find_package(ereolenwrapper REQUIRED)


include(CTest)

add_executable(ereolenwrapperctests test_runners/all_tests.c
    StructTests.c   test_runners/StructTests_Runner.c 
)

target_link_libraries(ereolenwrapperctests unity::framework ereolenwrapper::ereolenwrapper)
add_test(c_interface_tests ereolenwrapperctests)

install(
    TARGETS ereolenwrapperctests
    EXPORT ${PROJECT_NAME}_Targets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})