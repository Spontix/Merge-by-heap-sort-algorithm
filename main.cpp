/*תרגיל תכנות מס' 2 במבני נתונים תשפ"א סמסטר ב
Eliran Shimonov
208434951
Amit gutfeld
313161481*/

#include <iostream>
#include "MinHeap.h"
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;
using namespace MergeHeapSort;

void moveToArr(ifstream& input, int* arr, int size)
{
	int index = 0;
	
	if (!size)
	{
		input.close();
		delete[] arr;
		throw "Empty Arr";
	}
	while (!input.eof()&&size-1!=index)
	{
		input >> arr[index];
		if (!input.good())
		{
			input.close();
			delete[] arr;
			throw "File syntac error";
		}
		index++;
	}
	input >> arr[index];
	index++;
	if (size != index)
	{
		input.close();
		delete[] arr;
		throw "Not enough numbers";
	}
	else if(!input.eof())
	{
		input.close();
		delete[] arr;
		throw "Small size error";
	}
		
}
void swap(int* arr, int a, int b)
{
	int temp = arr[b];
	arr[b] = arr[a];
	arr[a] = temp;
}
void writeToFile(ofstream& output, int* arr, int size)
{
	int index = 0;
	while (index < size - 1)
	{
		output << arr[index] << endl;
		index++;
	}
	output << arr[index];
}

int partition(int* array, int left, int right)
{
	int pivot = left;
	while (left < right)
	{
		if (pivot == left)
		{
			if (array[pivot] > array[right])
			{
				swap(array, pivot, right);
				pivot = right;
				left++;
			}
			else
			{
				right--;
			}
		}
		else
		{
			if (array[pivot] < array[left])
			{
				swap(array, pivot, left);
				pivot = left;
				right--;
			}
			else
			{
				left++;
			}
		}
	}
	return pivot;
}

void quickSort(int* arr, int low, int high)
{
	if (low < high)
	{
		int pivot = partition(arr, low, high);

		quickSort(arr, low, pivot - 1);
		quickSort(arr, pivot + 1, high);
	}
}

void merge1(int* newArr, int n, int* arr, int k)
{
	
	int index = 0;
	Pair* numArr = new Pair[k];
	int NmodK = n % k;
	for (int i = 0; i < k; i++)
	{
		int s = NmodK > 0;
		if (s)
			NmodK--;
		numArr[i].getKey() = arr[index];//insert the minimum number		
		numArr[i].getBegin() = index;
		index += (n / k) + s;// insert the index 
		numArr[i].getEnd() = index;
	}
	MinHeap Heap(numArr, k);
	for (int i = 0; i < n; i++)
	{
		Pair Temp = Heap.DeleteMin();

		newArr[i] = Temp.getKey();
		if (Temp.getBegin() < Temp.getEnd() - 1)
		{
			Temp.getKey() = arr[++(Temp.getBegin())];
			Heap.insert(Temp);
		}
	}
}

void HeapSort(int* arr, int n, int k)
{

	if (n < k)
	{
		quickSort(arr, 0, n - 1);
		return;
	}
	int beginIndex = 0;
	int NmodK = n % k;
	for (int i = 0; i < k; i++)
	{
		int s = NmodK > 0;
		if (s)
			NmodK--;
		HeapSort(arr + beginIndex, (n / k) + s, k);
		beginIndex += (n / k) + s;
	}
	int* newArr = new int[n];
	merge1(newArr, n, arr, k);
	for (int i = 0; i < n; i++)
		arr[i] = newArr[i];
	delete[] newArr;

}

int main()
{
	int n, k;
	cin >> n;
	cin >> k;
	int* arr = new int[n];
	string inputFileName;
	string outputFileName;
	cin >> inputFileName;
	cin >> outputFileName;
	ifstream input(inputFileName);
   ofstream output(outputFileName);
   try
   {
	   if (k < 1)
		   throw "Negative K";
	   moveToArr(input, arr, n);//good
	   HeapSort(arr, n, k);
	   writeToFile(output, arr, n);
   }
   catch (const char* error) { 
	   cout << error << endl;
	   
   }
   output.close();
   input.close();
}

