//============================================================================
// Name        : ThreadPoolSystem.h
// Author      : Burak Akkanat & Ahmet Ozan Sivri
// Version     : 1.0
// Copyright   : -
// Description : SE 311 TERM PROJECT
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

#ifndef THREADPOOLSYSTEM_H_
#define THREADPOOLSYSTEM_H_

class ThreadPool;
class MemoryManager;

//The class which is representing tasks to be run within threads.
//#TODO: SET THREAD WITH THREAD ID ETCUpda
class Task{

public:

	Task(int _taskID, double _requiredMemory) : requiredMemory(_requiredMemory), taskID(_taskID),
												threadID(0){};
	~Task(){};

	void setTaskID(int _taskID){
		taskID = _taskID;
	}

	void setThreadID(int _threadID){
		threadID = _threadID;
	}

	void setRequiredMemory(double _requiredMemory){
		requiredMemory = _requiredMemory;
	}

	int getTaskID(){
		return taskID;
	}

	int getThreadID(){
		return threadID;
	}

	double getRequiredMemory(){
		return requiredMemory;
	}

private:

	double requiredMemory;
	int taskID;
	int threadID;

};

//This abstract class is representing the threads with required variables and a task within.

class Thread{

public:

	virtual void run() = 0;
	virtual ~Thread(){};

	int getThreadID(){
		return threadID;
	}

	int getPriority(){
		return priority;
	}

	double getAllocatedMemory(){
		return allocatedMemory;
	}

	double getUsedMemory(){
		return usedMemory;
	}

	string getThreadState(){
		return threadState;
	}

	Task* getRunningTask(){
	  	return runningTask;
	 }

	void setThreadID(int _threadID){
		threadID = _threadID;
	}

	void setPriority(int _priority){
		priority = _priority;
	}

	void setAllocatedMemory(double _allocatedMemory){
		allocatedMemory = _allocatedMemory;
	}

	void setUsedMemory(){
		if(runningTask != NULL)
			usedMemory = runningTask->getRequiredMemory();
		else
			usedMemory = 0;
	}

	void setThreadState(string _threadState){
		threadState = _threadState;
	}

	//This method sets (adds) the task to be run into thread. Then it changes state and used memory.

	void setTask(Task* _task){
		runningTask = _task;
		setUsedMemory();
		setThreadState("BUSY");
	}

private:

	int threadID;
	int priority;
	double allocatedMemory;
	double usedMemory = 0;				//Represents memory of the attached task
	string threadState = "IDLE";		//IDLE or BUSY
	Task* runningTask;

};

//This is the concrete thread for HThread:

class HThread : public Thread{

public:

	HThread(int ID) : threadID(ID), runningTask(NULL) {};

	//This method executes the task within thread. When task is run then its removed from thread.

	void run(){
		setTask(NULL);
		setUsedMemory();
		setThreadState("IDLE");
	}

	int getThreadID(){
		return threadID;
	}

	int getPriority(){
		return priority;
	}

	double getAllocatedMemory(){
		return allocatedMemory;
	}

	double getUsedMemory(){
		return usedMemory;
	}

	string getThreadState(){
		return threadState;
	}

	Task* getTask(){
	  	return runningTask;
	 }

	void setThreadID(int _threadID){
		threadID = _threadID;
	}

	void setPriority(int _priority){
		priority = _priority;
	}

	void setAllocatedMemory(double _allocatedMemory){
		allocatedMemory = _allocatedMemory;
	}

	void setUsedMemory(){
		if(runningTask != NULL)
			usedMemory = runningTask->getRequiredMemory();
		else
			usedMemory = 0;
	}

	void setThreadState(string _threadState){
		threadState = _threadState;
	}

	//This method attaches a task to thread then changes it to BUSY state and sets used memory to task memo

	void setTask(Task* _task){
		runningTask = _task;
		cout << runningTask->getTaskID() << endl;
		setUsedMemory();
		setThreadState("BUSY");
	}

private:

	int threadID;
	int priority = 1;
	double allocatedMemory = 512;
	double usedMemory = 0;
	string threadState = "IDLE";
	Task* runningTask;

};

//This is the concrete thread for LThread:

class LThread : public Thread{

public:

	LThread(int ID) : threadID(ID), runningTask(NULL) {};

	//This method executes the task within thread. When task is run then its removed from thread.

	void run(){
		setTask(NULL);
		setUsedMemory();
		setThreadState("IDLE");
	}

	int getThreadID(){
		return threadID;
	}

	int getPriority(){
		return priority;
	}

	double getAllocatedMemory(){
		return allocatedMemory;
	}

	double getUsedMemory(){
		return usedMemory;
	}

	string getThreadState(){
		return threadState;
	}

	Task* getTask(){
		return runningTask;
	 }

	void setThreadID(int _threadID){
		threadID = _threadID;
	}

	void setPriority(int _priority){
		priority = _priority;
	}

	void setAllocatedMemory(double _allocatedMemory){
		allocatedMemory = _allocatedMemory;
	}

	void setUsedMemory(){
		if(runningTask != NULL)
			usedMemory = runningTask->getRequiredMemory();
		else
			usedMemory = 0;
	}

	void setThreadState(string _threadState){
		threadState = _threadState;
	}

	//This method attaches a task to thread then changes it to BUSY state and sets used memory to task memo

	void setTask(Task* _task){
		runningTask = _task;
		setUsedMemory();
		setThreadState("BUSY");
	}

private:

	int threadID;
	int priority = 5;
	double allocatedMemory = 256;
	double usedMemory = 0;
	string threadState = "IDLE";
	Task* runningTask;

};

//The "Abstract Iterator" for Iterator Pattern

class AbstractIterator {
public:

	virtual void First() = 0;
	virtual void Next() = 0;
    virtual bool IsDone () const = 0;
	virtual Thread* CurrentItem() const = 0 ;
	virtual ~AbstractIterator(){};

protected:

	AbstractIterator(){};

};

class ThreadPool;

// Since we have two vectors for busy and idle threads, we needed two concrete iterators.

//This class is the concrete iterator for idle thread vector:

class IdleIterator : public AbstractIterator {

public:

	IdleIterator(const ThreadPool* threadPool);
	void First();
    void Next();
    Thread* CurrentItem() const;
	bool IsDone() const;

private:

	const ThreadPool* _threadPool;
	int _current;
};

//This class is the concrete iterator for busy thread vector:

class BusyIterator : public AbstractIterator {

public:

	BusyIterator(const ThreadPool* threadPool);
	void First();
    void Next();
    Thread* CurrentItem() const;
	bool IsDone() const;

private:

	const ThreadPool* _threadPool;
	int _current;
};

class Mutex {   // Stub to manage a mutex.
};

class Lock {	// Stub for thread synchronization lock.

public:

	Lock(Mutex& m) : mutex(m) { // Stub to acquire the mutex
		cout << "Acquired Lock for thread pool instantiation..." << endl;
	}

	~Lock() { // Stub to release the mutex
		cout << "Releasing Lock..." << endl << endl;
	}

private:

	Mutex & mutex;

};

class Command;

/*ThreadPool class which implements the following:
 *  "Abstract Subject" for Observer Pattern
 *  "Abstract Aggregate" for Iterator Pattern
 *  "Abstract Template" for Template Pattern
 *  "User" for Command Pattern
 *  and applies Singleton Pattern
 *  */

//#TODO: HANDLE INITIAL THREAD AMOUNT AND MEMORYMANAGER = NULL IN CONSTRUCTOR

class ThreadPool{

public:

	//Since we have only one observer, there is no need to create Attach and Detach but only Notify
	//which sends the thread to observer and informs whether thread has been assigned a task
	//or executed one:
	virtual void Notify(Thread* _thread, int condition) = 0;

	//Adds a thread to either of vectors:
	virtual void addToIdle(Thread* _thread) = 0;
	virtual void addToBusy(Thread* _thread) = 0;

	//Sets the Memory Manager which is the Observer for this class:
	virtual void setMemoryManager(MemoryManager* _memoryManager) = 0;

	//Since we are going to create two concrete iterators, we created two virtual iterators:
	virtual AbstractIterator* CreateIdleIterator() = 0;
	virtual AbstractIterator* CreateBusyIterator() = 0;

	//All the concrete iterator methods are doubled for same reason:
	virtual int getIdleCount () const = 0;
	virtual int getBusyCount () const = 0;
	virtual Thread * getFromBusy(int index) const = 0;
	virtual Thread * getFromIdle(int index) const = 0;

	virtual ~ThreadPool(){};

	//This is the template method of thread creation. All primitive methods are called within.

	Thread* threadCreate(int ID, double _allocatedMemory, int _priority){

		Thread* _thread;

		if(_allocatedMemory == 512){
			_thread = new HThread(ID);
			_thread->setThreadID(ID);

			AllocateMemory(_thread, _allocatedMemory);
			createEntryToPool(_thread);
			assignPriority(_thread, _priority);

			cout << "Creating thread with" << " ID: " << _thread->getThreadID() << " Memory: " << _thread->getAllocatedMemory()
								<< " Priority: " << _thread->getPriority() << endl;
		}

		else if(_allocatedMemory == 256) {
			_thread = new LThread(ID);
			_thread->setThreadID(ID);

			AllocateMemory(_thread, _allocatedMemory);
			createEntryToPool(_thread);
			assignPriority(_thread, _priority);
		}
		else{
			cout << "Invalid input for thread creation." << endl;
			return NULL;
		}
		return _thread;
	}

protected:

	ThreadPool(){};

	//The primitive operations to take part in thread creation..

	virtual void AllocateMemory(Thread* _thread, double _allocatedMemory) = 0;

	virtual void createEntryToPool(Thread* _thread) = 0;

	virtual void assignPriority(Thread* _thread, int _priority) = 0;

private:

	vector<Thread*> idleThreads;
	vector<Thread*> busyThreads;
	MemoryManager* memoryManager;
	int initialThreadAmount;
	static Mutex mutex;

};

//#TODO: THREAD ID PROBLEMÝ

class concreteThreadPool : public ThreadPool{

public:

	//This methods triggers the command class

	void informReceiver(Command* _command);

	void addToIdle(Thread* _thread){
		idleThreads.push_back(_thread);
	}

	void addToBusy(Thread* _thread){
		busyThreads.push_back(_thread);
	}

	//Necessary implementation of pure virtual methods:

	IdleIterator* CreateIdleIterator(){
		return new IdleIterator(this);
	}

	BusyIterator* CreateBusyIterator(){
		return new BusyIterator(this);
	}

	Thread * getFromBusy(int index) const {
		return busyThreads[index];
	}

	Thread * getFromIdle(int index) const {
		return idleThreads[index];
	}

	int getIdleCount() const {
		return idleThreads.size();
	}

	int getBusyCount() const {
		return busyThreads.size();
	}

	//Notify function will be fully constructed later on:

	void Notify(Thread* _thread, int condition);

	void setMemoryManager(MemoryManager* _memoryManager){
		memoryManager = _memoryManager;
	}

	//getInstance method for Singleton:

	static concreteThreadPool* getThreadPool(int _threadAmount){

		if (instance == NULL) {
			 Lock lock(mutex);
			 if (instance == NULL)
				 	cout << "Thread pool instentiated." << endl;
					instance = new concreteThreadPool(_threadAmount);
					for(int i = 0; i < _threadAmount; i++){

						instance->threadCreate(i+100, 512, 1);

					}
		}
		return instance;
	}

	//This method removes a thread from any desired vector:
	//#TODO: MEMORY LEAK HERE:

	void removeFromBusy(Thread* _thread){

		for (unsigned int i= 0; i< busyThreads.size(); i++) {
			if (busyThreads[i]->getThreadID() == _thread->getThreadID()) {
				busyThreads.erase(busyThreads.begin()+i);
				return;
			}
		}
	}

	void removeFromIdle(Thread* _thread){

		for (unsigned int i= 0; i< idleThreads.size(); i++) {
			if (idleThreads[i]->getThreadID() == _thread->getThreadID()) {
				idleThreads.erase(idleThreads.begin()+i);
				return;
			}
		}
	}

	//This method merges a task and a thread together. It then notifies observer since used memory is changed and moves thread to right vector.

	void assignThreadToTask(Thread* _thread, Task* _task){
		_thread->setTask(_task);
		Notify(_thread, 1);
		_task->setThreadID(_thread->getThreadID());
		addToBusy(_thread);
		removeFromIdle(_thread);
	}

	//This is the method for task execution. It then notifies observer for memory usage decrease and moves thread to idle vector if needed.
	//#TODO: MEMORY LEAK HERE:

	void runThread(Thread* _thread){

		cout << "Running task of thread with ID: " << _thread->getThreadID() << endl;

		Notify(_thread, 0);

		_thread->setTask(NULL);
		_thread->setUsedMemory();
		_thread->setThreadState("IDLE");

		if(idleThreads.size() < initialThreadAmount)	//Move vector to idle thread if there is not enough idle vectors
			addToIdle(_thread);

		removeFromBusy(_thread);						//Then remove the thread from busy vector
	}

protected:

	//Implementation of primitive thread creation methods:

	void AllocateMemory(Thread* _thread, double _allocatedMemory){
		_thread->setAllocatedMemory(_allocatedMemory);
	}

	void createEntryToPool(Thread* _thread){
		addToIdle(_thread);
	}

	void assignPriority(Thread* _thread, int _priority){
		_thread->setPriority(_priority);
	}

private:

	//Private constructor for Singleton:
	concreteThreadPool(int _threadAmount): initialThreadAmount(_threadAmount), memoryManager(NULL){};
	//Prevent copying:
	concreteThreadPool (const ThreadPool&);
	ThreadPool& operator=(const ThreadPool&);

	vector<Thread*> idleThreads;
	vector<Thread*> busyThreads;

	MemoryManager* memoryManager;
	vector<Command*> commands;

	static concreteThreadPool* instance;
	static Mutex mutex;

	int initialThreadAmount;

};

Mutex concreteThreadPool::mutex;
concreteThreadPool *concreteThreadPool::instance = 0;

//Construction of methods for IdleIterator and BusyIterator:

IdleIterator::IdleIterator(const ThreadPool *threadPool) :
	_threadPool(threadPool), _current(0) {
}
void IdleIterator::First() {
	_current = 0;
}
void IdleIterator::Next()  {
	_current++;
}

bool IdleIterator::IsDone() const {
	return _current >= _threadPool->getIdleCount();
}

Thread* IdleIterator::CurrentItem() const {
	if(!IsDone())
		return _threadPool->getFromIdle(_current);
	else
		return NULL;
}

BusyIterator::BusyIterator(const ThreadPool *threadPool) :
	_threadPool(threadPool), _current(0) {
}
void BusyIterator::First() {
	_current = 0;
}
void BusyIterator::Next()  {
	_current++;
}

bool BusyIterator::IsDone() const {
	return _current >= _threadPool->getBusyCount();
}

Thread* BusyIterator::CurrentItem() const {
	if(!IsDone())
		return _threadPool->getFromBusy(_current);
	else
		return NULL;
}

//A method that traverses any vector using iterator and returns a desired thread:

Thread* findThread(AbstractIterator& i, Thread* _thread) {
	cout << "Searching for the desired thread..." << endl;

	for(i.First();  !i.IsDone(); i.Next()) {
		if(i.CurrentItem()->getThreadID() == _thread->getThreadID())
			cout << "Thread found. Found thread ID is: " << i.CurrentItem()->getThreadID() <<  endl;
			return i.CurrentItem();
	}
	cout << "Desired thread not found" << endl;
	return NULL;
}

//Observer class which is "Abstract Observer":

class Observer{

public:

	virtual ~Observer(){};
	virtual void Update(Thread* thread, int condition, int MB) = 0;
};

//"Abstract Command" class:

class Command {

public:

	virtual void Execute() = 0;

protected:

	Command(){};
};

//MemoryManager class which is "Concrete Observer":

class MemoryManager: public Observer{

public:

	void Action(int condition, Thread* _thread){

		switch(condition){

		case 0: Update(_thread, 0, _thread->getUsedMemory()); break;

		case 1: Update(_thread, 1, _thread->getUsedMemory()); break;

		}
	}

	//This observer uses pull method to update. It gets a added/executed condition and the MB of the task. Then updates its variables

	void Update(Thread* thread, int condition, int MB){

		switch(condition){

		case 0: cout << "Task with ID " << thread->getThreadID() << " has finished executing. " <<
				thread->getUsedMemory() << " MB of memory released." << endl;
				memoryUsed -= MB;
				cout << "Current memory usage is: " << memoryUsed << " MB" << endl;
				break;

		case 1: cout << "Thread with ID " << thread->getThreadID() << " has been assigned a task of " <<
				MB << " MB." << endl;
				memoryUsed += MB;
				cout << "Current memory usage is: " << memoryUsed << " MB" << endl;
				if(memoryUsed > memoryLimit)
						cout << "!!!WARNING!!! Memory limit exceeded by " << memoryUsed-memoryLimit << "MB" << endl;
				break;
		}
	}

private:

	double memoryUsed;
	double memoryLimit = 1024;
};

//Concrete command method for Memory Manager. It triggers action by giving it required values.

class MemoryManagerCommand : public Command{

public:

	MemoryManagerCommand(MemoryManager* _memoryManager, Thread* _thread, int _condition):
		memoryManager(_memoryManager), thread(_thread), condition(_condition) {}

	void Execute(){
		memoryManager->Action(condition, thread);
	}

private:

	MemoryManager* memoryManager;
	Thread* thread;
	int condition;
};

//Implementation of Notify function which executes the command for Memory Manager to do its job:

void concreteThreadPool :: Notify(Thread* _thread, int condition){
	Command* _command;
	_command = new MemoryManagerCommand(memoryManager, _thread, condition);
	cout << "Notifying Memory Manager about thread activity..." << endl;
	informReceiver(_command);
}

//The method which triggers Memory Manager by executings its command. It also keeps track of the thread activity in commands vector.

void concreteThreadPool :: informReceiver(Command* command){
	command->Execute();
	commands.push_back(command);
}


#endif /* THREADPOOLSYSTEM_H_ */
