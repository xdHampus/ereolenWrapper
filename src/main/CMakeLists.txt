#add_executable(ereolenwrapper ereolenwrapper.cpp)
add_library(${PROJECT_NAME} SHARED 
	ApiEnv.h ApiEnv.cpp 
	Auth.h Auth.cpp
	Profile.h Profile.cpp 
	structs/ChecklistItem.h structs/ChecklistItem.cpp 
	structs/Library.h 
	structs/LibraryProfile.h 
	structs/LoanActive.h structs/LoanActive.cpp
	structs/LoanHistorical.h structs/LoanHistorical.cpp
	structs/LoanIdentifier.h structs/LoanIdentifier.cpp 
	structs/Reservation.h structs/Reservation.cpp
	structs/RpcPayload.h structs/RpcPayload.cpp 
	structs/Token.h structs/Token.cpp 
	structs/Contributor.h
	structs/Language.h
	structs/MediaType.h 
	structs/Product.h 
	structs/ProductType.h 

	util/InterfaceUtilC.h util/InterfaceUtilC.cpp
)

set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

target_sources(${PROJECT_NAME} PRIVATE
		ereolenwrapper.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE $<BUILD_INTERFACE:cpr::cpr>)
