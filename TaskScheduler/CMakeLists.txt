set(HEADER
	"./Source/Public/TaskScheduler.h"
)

set (SOURCE
	"./Source/Private/Main.cpp"
	"./Source/Private/TaskScheduler.cpp"
)

include_directories(Source/Public)

FIND_PACKAGE (Threads)

add_executable(TaskScheduler ${HEADER} ${SOURCE})

target_link_libraries(TaskScheduler ${CMAKE_THREAD_LIBS_INIT})