#ifndef MYLINUX_DALVIK_HEAP_H
#define MYLINUX_DALVIK_HEAP_H

#include "dalvik_types.h"
#include "dalvik_status.h"

DalvikStatus dalvikHeapInitialize(DalvikHeap *heap, size_t initial_size);
void *dalvikHeapAllocate(DalvikHeap *heap, size_t size);
void dalvikHeapFree(DalvikHeap *heap, void *pointer);
size_t dalvikHeapGetUsed(DalvikHeap *heap);
size_t dalvikHeapGetCapacity(DalvikHeap *heap);

#endif
