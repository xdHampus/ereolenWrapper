#add_executable(ereolenwrapper ereolenwrapper.cpp)
set(additionalSources )

if (ENABLE_LUA)
	set(additionalSources ${additionalSources} lua/LuaInterface.cpp lua/LuaInterface.h)
endif()

set (LIBRARY_INST_TYPE SHARED)
if (ENABLE_COMPILE_STATIC)
    set (LIBRARY_INST_TYPE STATIC)
endif()


add_library(${PROJECT_NAME} ${LIBRARY_INST_TYPE}
	${additionalSources}
	ApiEnv.h    ApiEnv.cpp
	Auth.h      Auth.cpp
	Profile.h   Profile.cpp
	Item.h      Item.cpp

	model/ChecklistItem.h   model/ChecklistItem.cpp
	model/Library.h         model/Library.cpp
	model/LibraryProfile.h  model/LibraryProfile.cpp
	model/LoanActive.h      model/LoanActive.cpp
	model/LoanHistorical.h  model/LoanHistorical.cpp
	model/LoanIdentifier.h  model/LoanIdentifier.cpp
	model/Reservation.h     model/Reservation.cpp
	model/RpcPayload.h      model/RpcPayload.cpp
	model/Token.h           model/Token.cpp
	model/Contributor.h     model/Contributor.cpp
	model/Record.h          model/Record.cpp
	model/Facet.h           model/Facet.cpp
	model/QuerySettings.h   model/QuerySettings.cpp
	model/Term.h            model/Term.cpp
	model/Language.h        model/Language.cpp
	model/MediaType.h       model/MediaType.cpp
	model/RecordType.h      model/RecordType.cpp
	model/PageResult.h      model/PageResult.cpp
	model/Response.h        model/Response.cpp
	model/Review.h          model/Review.cpp

	util/JSONHelper.h
	util/ApiCaller.h
	util/ErrorResponse.h
	util/HelperFunctions.h

)

target_sources(${PROJECT_NAME} PRIVATE
		ereolenwrapper.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE $<BUILD_INTERFACE:cpr::cpr>)
if(ENABLE_LUA)
	target_link_libraries(${PROJECT_NAME} PRIVATE ${LUA_LIBRARIES})
	target_include_directories(${PROJECT_NAME} PRIVATE ${LUA_INCLUDE_DIR})
	find_path(LUABRIDGE_INCLUDE_DIRS "LuaBridge/LuaBridge.h")
	target_include_directories(${PROJECT_NAME} PRIVATE ${LUABRIDGE_INCLUDE_DIRS})
endif()
if(ENABLE_LIBGOUROU)
	target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBGOUROU_LIBRARIES})
	target_include_directories(${PROJECT_NAME} PRIVATE ${LIBGOUROU_INCLUDE_DIR})
endif()