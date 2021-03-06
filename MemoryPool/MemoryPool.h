#pragma once

#include <cstdio>
#include <cstddef>
#include <cstdlib>
#include <stdint.h>
#include <stdarg.h>
#include <utility>
#include "../Mutex/MutexLock.h"

#define BlockSize 4096

struct Slot{
	Slot* next;
};

class MemoryPool{
private:
	int slot_size;	
		
	Slot* currentBlock;
	Slot* currentSlot;
	Slot* lastSlot;
	Slot* freeSlot;
	
	MutexLock m_freeSlot;
	MutexLock m_other;
	size_t padPointer(char* p,size_t align);
	Slot* allocateBlock();
	Slot* nofree_solve();	

public:
	MemoryPool();
	~MemoryPool();
	void init(int size);	
	Slot* allocate();
	void deallocate(Slot* p);

};

//void *operator new(size_t);
//void operator delete(void *p,size_t size);
void init_memorypool();
void* use_memory(int number);
void free_memory(int number,void *p);
static MemoryPool memorypool[16];
