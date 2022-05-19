#add_executable(ereolenwrapper ereolenwrapper.cpp)
add_library(${PROJECT_NAME} SHARED 
	ApiEnv.h ApiEnv.cpp 
	Auth.h Auth.cpp
	Profile.h Profile.cpp 
	model/ChecklistItem.h model/ChecklistItem.cpp 
	model/Library.h 
	model/LibraryProfile.h 
	model/LoanActive.h model/LoanActive.cpp
	model/LoanHistorical.h model/LoanHistorical.cpp
	model/LoanIdentifier.h model/LoanIdentifier.cpp 
	model/Reservation.h model/Reservation.cpp
	model/RpcPayload.h model/RpcPayload.cpp 
	model/Token.h model/Token.cpp 
	model/Contributor.h
	model/Language.h
	model/MediaType.h 
	model/Product.h 
	model/ProductType.h 

	util/InterfaceUtilC.h util/InterfaceUtilC.cpp
)

set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

target_sources(${PROJECT_NAME} PRIVATE
		ereolenwrapper.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE $<BUILD_INTERFACE:cpr::cpr>)
