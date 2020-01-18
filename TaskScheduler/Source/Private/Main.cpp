#include "TaskScheduler.h"

#include <atomic>
#include <iostream>

int main( )
{
	TaskScheduler taskScheduler;
	GroupHandle taskGroup = taskScheduler.GetTaskGroup( 1000000 );

	std::atomic<int> result = 0;
	for ( int i = 0; i < 1000000; ++i )
	{
		taskScheduler.Run( taskGroup, 
			[]( void* ctx ) { *static_cast<std::atomic<int>*>( ctx ) += 1; },
			&result );
	}

	taskScheduler.Wait( taskGroup );

	if ( taskScheduler.IsComplete( taskGroup ) )
	{
		std::cout << "task complete : ";
	}

	std::cout << result << std::endl;

	return 0;
}