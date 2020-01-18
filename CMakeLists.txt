cmake_minimum_required(VERSION 3.8.2)

project(TaskScheduler)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /std:c++17")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++17")
endif()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(TaskScheduler)
add_subdirectory(UnitTest)
add_subdirectory(ThirdParty/googletest/googletest EXCLUDE_FROM_ALL)

