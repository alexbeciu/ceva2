#include "stdlib.h"
#include "stdio.h"
#include "memory.h"
struct HeapItem
{
	int value;
	int key;
};
struct Heap
{
	HeapItem** elements;
	int heapSize;
	int index;
};

void InitHeap(Heap&, int);
HeapItem* CreateItem(int, int);
void Enqueue(Heap&, int, int);
HeapItem* Dequeue(Heap&);
void ReheapUp(Heap, int, int);
void ReheapDown(Heap, int, int);
void PrintHeap(Heap);

void InitHeap(Heap& heap, int size)
{
	heap.elements = (HeapItem**)malloc(sizeof(HeapItem*)*size);
	heap.heapSize = size;
	heap.index = 0;
	memset(heap.elements, NULL, sizeof(HeapItem*)*size);
}

HeapItem* CreateItem(int key, int data)
{
	HeapItem* item = (HeapItem*)malloc(sizeof(HeapItem));
	item->key = key;
	item->value = data;
	return item;
}

void Enqueue(Heap& heap, int key, int val)
{
	if (heap.index < heap.heapSize)
	{
		HeapItem* item = CreateItem(key, val);
		heap.elements[heap.index] = item;
		ReheapUp(heap, 0, heap.index);
		heap.index++;
		return;
	}
	printf("Heap structure is full!\n");
}

void ReheapUp(Heap heap, int first, int last)
{
	int parinte;
	HeapItem* temp = NULL;
	if (first < last)
	{
		parinte = (last - 1) / 2;
		if (heap.elements[parinte]->key <
			heap.elements[last]->key)
		{
			temp = heap.elements[parinte];
			heap.elements[parinte] = heap.elements[last];
			heap.elements[last] = temp;
			ReheapUp(heap, first, parinte);
		}
	}
}

void PrintHeap(Heap heap)
{
	if (heap.index == 0)
		printf("Heap is empty!\n");
	for (int i = 0; i < heap.index; i++)
		printf("Heap key: %d, value: %d\n",
			heap.elements[i]->key,
			heap.elements[i]->value);
}

void ReheapDown(Heap heap, int current, int last)
{
	int leftChild, rightChild, maxChild;
	HeapItem* temp = NULL;
	leftChild = 2 * current + 1;
	rightChild = 2 * current + 2;
	if (leftChild <= last)
	{
		if (leftChild == last)
			maxChild = leftChild;
		if (heap.elements[leftChild]->key <
			heap.elements[rightChild]->key)
			maxChild = rightChild;
		else
			maxChild = leftChild;

		if (heap.elements[current]->key <
			heap.elements[maxChild]->key)
		{
			temp = heap.elements[current];
			heap.elements[current] = heap.elements[maxChild];
			heap.elements[maxChild] = temp;
		}
		ReheapDown(heap, maxChild, last);
	}
}

HeapItem* Dequeue(Heap& heap)
{
	HeapItem* result = NULL;
	if (heap.index > 0)
	{
		result = heap.elements[0];
		heap.elements[0] = heap.elements[--heap.index];
		//heap.elements[heap.index] = NULL;
		ReheapDown(heap, 0, heap.index - 1);
	}
	return result;
}

void main()
{
	Heap heap;
	InitHeap(heap, 8);
	Enqueue(heap, 20, 345);
	Enqueue(heap, 10, 346);
	Enqueue(heap, 7, 347);
	Enqueue(heap, 8, 348);
	Enqueue(heap, 5, 349);
	Enqueue(heap, 4, 350);
	Enqueue(heap, 3, 351);
	Enqueue(heap, 28, 453);
	PrintHeap(heap);
	HeapItem* item = NULL;
	while ((item = Dequeue(heap)) != NULL)
		printf("Heap key:%d, value:%d\n",
			item->key, item->value);
}