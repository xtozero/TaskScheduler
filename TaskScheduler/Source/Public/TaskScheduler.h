#ifndef _TASK_SCHEDULER_H_
#define _TASK_SCHEDULER_H_

#include <atomic>
#include <mutex>

using WorkerFunc = void (*)( void* );
struct GroupHandle
{
	size_t m_groupIndex;
	size_t m_id;
};

struct Task
{
	WorkerFunc m_func;
	void* m_context;
};

struct TaskGroup;
struct Worker;

class TaskScheduler
{
public:
	GroupHandle GetTaskGroup( size_t reserveSize );

	void Run( GroupHandle handle, WorkerFunc func, void* context );

	void Wait( GroupHandle handle );
	void WaitAll( );

	bool IsComplete( GroupHandle handle ) const;

	TaskScheduler( );
	~TaskScheduler( );
	TaskScheduler( const TaskScheduler& ) = delete;
	TaskScheduler& operator=( const TaskScheduler& ) = delete;
	TaskScheduler( TaskScheduler&& ) = delete;
	TaskScheduler& operator=( TaskScheduler&& ) = delete;

private:
	TaskGroup* m_taskGroups = nullptr;
	size_t m_maxTaskGroup = 4;
	size_t m_workerCount = 1;
	Worker* m_workers = nullptr;
	volatile bool m_shutdown = false;

	friend void WorkerThread( TaskScheduler* scheduler, Worker* worker );
};

#endif