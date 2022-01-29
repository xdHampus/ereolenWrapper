#add_executable(ereolenwrapper ereolenwrapper.cpp)
add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE 
	ereolenwrapper.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
