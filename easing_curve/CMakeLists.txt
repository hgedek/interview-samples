get_filename_component(exercise ${CMAKE_CURRENT_SOURCE_DIR} NAME)

cmake_minimum_required(VERSION 3.10)

project(${exercise} CXX)

set(CMAKE_BUILD_TYPE Debug)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file (GLOB SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

file (GLOB TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)

if (TESTING)
    add_executable(${exercise}_test ${TEST_SOURCES} ${SOURCES})
    set(executable ${exercise}_test)
else() 
    add_executable(${exercise} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp ${SOURCES})
    set(executable ${exercise})
endif()

set_target_properties(${executable} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED OFF
    CXX_EXTENSIONS OFF)

if ("{CMAKE_CXX_COMPILER_ID}" MATCHES "(GNU|Clang)")
    set_target_properties(${executable} PROPERTIES
        COMPILE_FLAGS "-Wall -Wextra -Wpedantic -Werror")
endif() 

if ($(MSVC))
    set_target_properties(${executable} PROPERTIES COMPILE_DEFINITIONS_DEBUG_SCL_SECURE_NO_WARNINGS)
endif()

if (TESTING)
    add_custom_target(testing ALL DEPENDS ${executable} COMMAND ${executable})
endif()
