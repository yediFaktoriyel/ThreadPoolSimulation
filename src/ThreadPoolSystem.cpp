//============================================================================
// Name       	: ThreadPoolSystem.cpp
// Author      : Burak Akkanat & Ahmet Ozan Sivri
// Version     : 1.0
// Copyright   : -
// Description : SE 311 TERM PROJECT
//============================================================================

#include <iostream>
#include "ThreadPoolSystem.h"
#include <vector>
#include <string>
using namespace std;


int main() {

	concreteThreadPool* _threadPool = concreteThreadPool:: getThreadPool(10);
	MemoryManager* _memoryManager = new MemoryManager();
	_threadPool->setMemoryManager(_memoryManager);
	cout << _threadPool->getIdleCount() << endl;

	Thread* _thread1 = _threadPool->getFromIdle(0);
	Thread* _thread2 = _threadPool->getFromIdle(1);
	Thread* _thread3 = _threadPool->getFromIdle(2);
	Thread* _thread4 = _threadPool->getFromIdle(3);
	Task* _task1 = new Task(0001, 420);
	Task* _task2 = new Task(0001, 500);
	Task* _task3 = new Task(0001, 300);
	Task* _task4 = new Task(0001, 400);

	_threadPool->assignThreadToTask(_thread1, _task1);
	cout << _threadPool->getIdleCount() << endl;
	cout << endl;

	cout << "Allocated Memory: " << _thread1->getAllocatedMemory() << " Priority: " << _thread1->getPriority() << " ID: " << _thread1->getThreadID()
				<< " State: " << _thread1->getThreadState() << " Used Memory: " << _thread1->getUsedMemory() << endl;

	_threadPool->runThread(_thread1);
	cout << "Allocated Memory: " << _thread1->getAllocatedMemory() << " Priority: " << _thread1->getPriority() << " ID: " << _thread1->getThreadID()
			<< " State: " << _thread1->getThreadState() << " Used Memory: " << _thread1->getUsedMemory() << endl;

	_threadPool->assignThreadToTask(_thread2, _task2);
	_threadPool->assignThreadToTask(_thread3, _task3);
	_threadPool->assignThreadToTask(_thread4, _task4);

	AbstractIterator* _iterator = _threadPool->CreateIdleIterator();
	findThread(*_iterator, _thread1);

	delete _threadPool;
	delete _memoryManager;
	delete _thread1;
	delete _thread2;
	delete _thread3;
	delete _thread4;
	delete _task1;
	delete _task2;
	delete _task3;
	delete _task4;
	delete _iterator;

	return 0;
}
