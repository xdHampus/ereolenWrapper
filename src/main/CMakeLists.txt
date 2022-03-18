#add_executable(ereolenwrapper ereolenwrapper.cpp)
add_library(${PROJECT_NAME} STATIC structs/LibraryProfile.h structs/LoanActive.h structs/RpcPayload.h structs/Library.h ApiEnv.cpp structs/Token.h structs/ChecklistItem.h structs/LoanHistorical.h structs/LoanIdentifier.h structs/Reservation.h)

target_sources(${PROJECT_NAME} PRIVATE
		ereolenwrapper.cpp
		ApiEnv.h
		Auth.cpp Auth.h
		Profile.cpp Profile.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE $<BUILD_INTERFACE:cpr::cpr>)
