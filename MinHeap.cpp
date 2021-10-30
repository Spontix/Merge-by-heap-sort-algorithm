#include "MinHeap.h"
#include <iostream>

using namespace std;
using namespace MergeHeapSort;

MinHeap::MinHeap(int max) :maxSize(max), heapSize(0)
{
	arr = new Pair[max];
}

MinHeap::~MinHeap()
{
	delete[]arr;
	arr = nullptr;
}

void MinHeap::FixHeap(int node)
{
	int min;
	int left = Left(node);
	int right = Right(node);

	if ((left < heapSize) && (arr[left].key < arr[node].key))
		min = left;
	else min = node;
	if ((right < heapSize) && (arr[right].key < arr[min].key))
		min = right;

	if (min != node)
	{
		swap(arr[node], arr[min]);
		FixHeap(min);
	}
}

Pair MinHeap::DeleteMin()
{
	if (heapSize < 1)
		throw "ERROR";
	Pair min = arr[0];
	heapSize--;
	arr[0] = arr[heapSize];
	FixHeap(0);
	return min;
}

void MinHeap::insert(Pair& item)
{
	if (heapSize == maxSize)
		throw "ERROR";
	int i = heapSize;
	heapSize++;

	while ((i > 0) && (arr[Parent(i)].key > item.key))
	{
		arr[i] = arr[Parent(i)];
		i = Parent(i);
	}
	arr[i] = item;
}

MinHeap::MinHeap(Pair* other, int k):heapSize(k), maxSize(k)
{
	arr = new Pair[k];
	for (int i = 0; i < k; i++)
		arr[i] = other[i];

	for (int i = k / 2 - 1; i >= 0; i--)
		FixHeap(i);
}