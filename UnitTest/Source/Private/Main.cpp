#include "gtest/gtest.h"
#include "TaskScheduler.h"

#include <atomic>
#include <random>

TEST( TaskScheduler, 01_ParallelSum )
{
	TaskScheduler taskScheduler;
	GroupHandle taskGroup = taskScheduler.GetTaskGroup( );

	class AddOneTask
	{
	public:
		void DoTask( )
		{
			m_result += 1;
		}

		AddOneTask( std::atomic<int>& result ) : m_result( result ) {}
	private:
		std::atomic<int>& m_result;
	};

	std::atomic<int> result = 0;
	for ( int i = 0; i < 1000000; ++i )
	{
		taskScheduler.Run( taskGroup, Task<AddOneTask>::Create( result ) );
	}

	taskScheduler.Wait( taskGroup );

	ASSERT_EQ( result, 1000000 );
}

TEST( TaskScheduler, 02_IsComplete )
{
	TaskScheduler taskScheduler;
	GroupHandle taskGroup = taskScheduler.GetTaskGroup( );

	class NullTask
	{
	public:
		void DoTask( ) { }
	};

	for ( int i = 0; i < 1000000; ++i )
	{
		taskScheduler.Run( taskGroup, Task<NullTask>::Create( ) );
	}

	ASSERT_TRUE( taskScheduler.Wait( taskGroup ) );

	ASSERT_TRUE( taskScheduler.IsComplete( taskGroup ) );

	GroupHandle newGroup = taskScheduler.GetTaskGroup( );

	ASSERT_EQ( taskGroup.m_groupIndex, newGroup.m_groupIndex );
	ASSERT_NE( taskGroup, newGroup );

	ASSERT_FALSE( taskScheduler.IsComplete( newGroup ) );

	for ( int i = 0; i < 1000000; ++i )
	{
		taskScheduler.Run( taskGroup, Task<NullTask>::Create( ) );
	}

	ASSERT_TRUE( taskScheduler.Wait( newGroup ) );

	ASSERT_TRUE( taskScheduler.IsComplete( newGroup ) );
}

TEST( TaskScheduler, 03_WaitAll )
{
	TaskScheduler taskScheduler;
	GroupHandle taskGroup[4];

	for ( int i = 0; i < 4; ++i )
	{
		taskGroup[i] = taskScheduler.GetTaskGroup( );
	}

	std::random_device rd;
	std::mt19937 mt( rd() );
	std::uniform_int_distribution<int> uniform( 0, 3 );

	class NullTask
	{
	public:
		void DoTask( ) { }
	};

	for ( int i = 0; i < 1000000; ++i )
	{
		taskScheduler.Run( taskGroup[uniform( mt )], Task<NullTask>::Create( ) );
	}

	taskScheduler.WaitAll( );

	for ( int i = 0; i < 4; ++i )
	{
		ASSERT_TRUE( taskScheduler.IsComplete( taskGroup[i] ) );
	}
}