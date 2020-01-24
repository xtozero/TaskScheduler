set (HEADER)
 
set (SOURCE
	"./Source/Private/Main.cpp"
)
 
enable_testing()
 
include_directories(../ThirdParty/googletest/googletest/include)
include_directories(../TaskScheduler/Source/Public)
 
FIND_PACKAGE(Threads)
 
add_executable(unit_test ${HEADER} ${SOURCE})
 
target_link_libraries(unit_test gtest_main ${CMAKE_THREAD_LIBS_INIT} TaskScheduler)
 
add_test(NAME unit_test COMMAND unit_test)