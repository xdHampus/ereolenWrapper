file(GLOB SOURCES ./*.c)
#add_executable(release ${SOURCES})
add_library(release STATIC ${SOURCES})
target_include_directories(release PUBLIC ${CMAKE_CURRENT_LIST_DIR})