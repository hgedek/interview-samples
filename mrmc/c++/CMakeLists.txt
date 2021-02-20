cmake_minimum_required(VERSION 3.10)

project(samples CXX)

set(CMAKE_BUILD_TYPE Debug)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file (GLOB SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

add_executable(samples ${SOURCES})
set(executable samples)

set_target_properties(${executable} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED OFF
    CXX_EXTENSIONS OFF)

if ("{CMAKE_CXX_COMPILER_ID}" MATCHES "(GNU|Clang)")
    set_target_properties(${executable} PROPERTIES
        COMPILE_FLAGS "-Wall -Wextra -Wpedantic -Werror")
endif() 

if ($(MSVC))
    set_target_properties(${executable} PROPERTIES COMPILE_DEFINITIONS_DEBUG_SCL_SECURE_NO_WARNINGS)
endif()

add_custom_target(testing ALL DEPENDS ${executable} COMMAND ${executable})

