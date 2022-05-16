project("My Awesome Tested Project" C) 
cmake_minimum_required(VERSION 3.0)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

find_package(unity 2.5.2 REQUIRED)


add_subdirectory(src) 
include(CTest)
add_subdirectory(test) 

install(
    TARGETS release ereolenwrapperctests
    EXPORT ${PROJECT_NAME}_Targets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})