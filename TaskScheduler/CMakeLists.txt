set(HEADER
	"./Source/Public/TaskScheduler.h"
)

set (SOURCE
	"./Source/Private/Main.cpp"
	"./Source/Private/TaskScheduler.cpp"
)

include_directories(Source/Public)

add_executable(TaskScheduler ${HEADER} ${SOURCE})
