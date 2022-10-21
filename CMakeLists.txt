cmake_minimum_required(VERSION 3.17)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source. Please remove CMakeCache.txt and the CMakeFiles/ directory. Then build out-of-source.")
endif()

project(ereolenwrapper
    VERSION 0.1.0
    LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(APPLE)
add_compile_options(-mmacosx-version-min=10.15)
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_EXPORT_COMPILE_COMMANDS "YES")

############################
##  Modules and scripts   ##
############################

# Standard CMake modules
include(CTest)                          # Must be called before adding tests but after calling project(). This automatically calls enable_testing() and configures ctest targets when using Make/Ninja
include(CMakeDependentOption)           # This is a really useful scripts that creates options that depends on other options. It can even be used with generator expressions !
include(GNUInstallDirs)                 # This will define the default values for installation directories (all platforms even if named GNU)
include(InstallRequiredSystemLibraries) # Tell CMake that the `install` target needs to install required system libraries (eg: Windows SDK)
include(CMakePackageConfigHelpers)      # Helper to create relocatable packages

# Custom modules and scripts
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake") # Make our cmake scripts available

###############
##  Options  ##
###############

option(ENABLE_INSTALL
    "Should ${PROJECT_NAME} be added to the install list? Useful if included using add_subdirectory." ON)
option(ENABLE_TESTING "Should unit tests be compiled?" ON)
option(ENABLE_LUA "Should the Lua interface be compiled?" OFF)
option(EXPORT_UTIL "Export utility headers" OFF)
option(ENABLE_PI_CODE "Enable position-independent code" ON)
option(ENABLE_COMPILE_STATIC "Compile library as STATIC" OFF)


set(${PROJECT_NAME}_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
    CACHE STRING "Path to install ${PROJECT_NAME} Config*.cmake files to.")

####################
##  Dependencies  ##
####################
find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(cpr REQUIRED)
if(ENABLE_TESTING)
    find_package(GTest REQUIRED)
    include(GoogleTest)
    enable_testing()
endif()
if(ENABLE_LUA)
    include(FindLua)
    find_package(Lua 5.1 REQUIRED)
    add_definitions(-DCOMPILE_LUA)
endif()


###############
##  Targets  ##
###############

# Use the project root to find includes
include_directories(${PROJECT_SOURCE_DIR})
add_subdirectory(src)

if(ENABLE_PI_CODE)
    set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()
###############
## Packaging ##
###############


if(ENABLE_INSTALL)
    write_basic_package_version_file(
        ${PROJECT_NAME}ConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion)

    configure_package_config_file(
        ${PROJECT_SOURCE_DIR}/cmake/Config.cmake.in
        ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        INSTALL_DESTINATION ${${PROJECT_NAME}_INSTALL_CMAKEDIR}
        NO_SET_AND_CHECK_MACRO
        NO_CHECK_REQUIRED_COMPONENTS_MACRO)


    set(INSTALL_TARGETS ereolenwrapper)
    set(INSTALL_SRC_DIR src/main/.)
    set(INSTALL_EXCLUDES )

    if (ENABLE_TESTING)
        set(INSTALL_SRC_DIR src)
        set(INSTALL_TARGETS ${INSTALL_TARGETS} ereolenwrappertests)
        set_target_properties(ereolenwrappertests PROPERTIES OUTPUT_NAME "ereolenwrapper" ) 
        set(EXPORT_UTIL ON)
    endif()
    if(EXPORT_UTIL)
    else()
        set(INSTALL_EXCLUDES ${INSTALL_EXCLUDES} PATTERN util EXCLUDE)
    endif()

    #if(ENABLE_LUA)
    #else()
    set(INSTALL_EXCLUDES ${INSTALL_EXCLUDES} PATTERN lua EXCLUDE)
    #endif()


    install(
            TARGETS ${INSTALL_TARGETS}
            EXPORT ${PROJECT_NAME}_Targets
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


    install(DIRECTORY ${INSTALL_SRC_DIR}
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ereol
            FILES_MATCHING
            PATTERN *.h
            ${INSTALL_EXCLUDES}
            )


    install(
        EXPORT ${PROJECT_NAME}_Targets
        NAMESPACE ${PROJECT_NAME}::
        FILE ${PROJECT_NAME}Targets.cmake
        DESTINATION ${${PROJECT_NAME}_INSTALL_CMAKEDIR})

    install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION ${${PROJECT_NAME}_INSTALL_CMAKEDIR})
endif()
