project("My Awesome Tested Project" C) 
cmake_minimum_required(VERSION 3.0)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

find_package(unity 2.5.2 REQUIRED)
find_package(ereolenwrapper REQUIRED)


include(CTest)

add_executable(ereolenwrapperctests 
test_runners/all_tests.c
TestProductionCode.c 
StructTests.c 
test_runners/TestProductionCode_Runner.c 
test_runners/StructTests_Runner.c 
)

target_link_libraries(ereolenwrapperctests unity::framework ereolenwrapper::ereolenwrapper)
add_test(test_meh ereolenwrapperctests)

install(
    TARGETS ereolenwrapperctests
    EXPORT ${PROJECT_NAME}_Targets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})