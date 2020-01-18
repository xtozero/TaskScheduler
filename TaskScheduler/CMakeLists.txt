set(HEADER
	"./Source/Public/TaskScheduler.h"
)

set (SOURCE
	"./Source/Private/Main.cpp"
	"./Source/Private/TaskScheduler.cpp"
)

include_directories(Source/Public)

add_executable(TaskScheduler ${HEADER} ${SOURCE})

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	target_link_libraries(TaskScheduler ${CMAKE_THREAD_LIBS_INIT})
endif()