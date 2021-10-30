#pragma once


namespace MergeHeapSort
{
	class Pair
	{
		friend class MinHeap;
		int key, begin, end;

	public:
		Pair(int key = 0, int begin = 0, int end = 0) :key(key), begin(begin), end(end) {}
		int& getKey() { return key; }
		int& getBegin() { return begin; }
		int& getEnd() { return end; }
	};

	class MinHeap
	{
	private:
		Pair* arr = nullptr;
		int maxSize;
		int heapSize;
		static int Left(int node) { return (2 * node + 1); }
		static int Right(int node) { return (2 * node + 2); }
		static int Parent(int node) { return (node - 1) / 2; }
		void FixHeap(int node);
	public:
		MinHeap(int max);
		MinHeap(Pair* other, int k);
		int Min() { return arr[0].key; }
		Pair DeleteMin();
		void insert(Pair& item);
		int& getSize() { return heapSize; }
		~MinHeap();
	};


	
}

