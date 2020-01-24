set(HEADER
	"./Source/Public/TaskScheduler.h"
)

set (SOURCE
	"./Source/Private/TaskScheduler.cpp"
)

include_directories(Source/Public)

FIND_PACKAGE(Threads)

add_library(TaskScheduler STATIC ${HEADER} ${SOURCE})

target_link_libraries(TaskScheduler ${CMAKE_THREAD_LIBS_INIT})