#include <iostream>
using namespace std;
#include <stack>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <chrono>    
#include <vector>
namespace sortlib {
	using namespace std;
	template <class T>
	void GenerateRandomList(T array[], T Max, T Size)
	{
		srand((unsigned)time(0));

		for (int i = 0; i < Size; i++)
		{
			array[i] = (rand() % Max);
		}

	}
	template <class T>
	void InsertionSort(T arr[], int n)
	{
		int i, j;
		T temp;

		for (int i = 1; i < n; ++i)
		{

			temp = arr[i];
			j = i - 1;

			while (j >= 0 && arr[j] > temp)
			{
				arr[j + 1] = arr[j];
				j = j - 1;
			}

			arr[j + 1] = temp;

		}
	}
	template <class T>
	void selectionSort(T array, int size) {
		for (int i = 0; i < size - 1; ++i) {
			int smallest = i;
			int temp;
			// first index of remaining array

			// loop to find index of smallest element
			for (int index = i + 1; index < size; ++index) {
				if (array[index] < array[smallest])
					smallest = index;
			}
			temp = array[smallest];
			array[smallest] = array[i];
			array[i] = temp;
		}
	}
	template<class T>
	void BubbleSort(T arr[], int n)
	{
		for (int i = 0; i < n - 1; ++i) {
			for (int j = 0; j < n - i - 1; ++j) {
				if (arr[j] > arr[j + 1]) {
					T temp = arr[j + 1];
					arr[j + 1] = arr[j];
					arr[j] = temp;
				}
			}
		}
	}
	template<class T>
	void ShellSort(T arr[], T N)
	{
		for (int gap = N / 2; gap > 0; gap /= 2)
		{
			for (int i = gap; i < N; i += 1)
			{
				//sort sub lists created by applying gap 
				int temp = arr[i];

				int j;
				for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
					arr[j] = arr[j - gap];

				arr[j] = temp;
			}
		}
	}
	template<class T>
	void Merge(T arr[], int start, int end)
	{

		// x: start index of first half [start, mid]
		// y: start index of second half [mid+1, end]
		// z: start index of temp
		// temp: temporary vector to store the merged array
		int z, x, y, mid;
		vector<T> temp(end - start + 1);
		mid = (start + end) / 2;
		z = 0;
		x = start;
		y = mid + 1;

		while (x <= mid && y <= end)
		{
			if (arr[x] < arr[y])
			{
				temp[z] = arr[x];
				++x, ++z;
			}
			else
			{
				temp[z] = arr[y];
				++y, ++z;
			}
		}

		while (x <= mid)
		{
			temp[z] = arr[x];
			++x, ++z;
		}

		while (y <= end)
		{
			temp[z] = arr[y];
			++y, ++z;
		}

		// write the merged sequence back to the original array
		for (int i = start; i <= end; ++i)
		{
			arr[i] = temp[i - start];
		}

	}
	template<class T>
	void MergeSort(T arr[], int start, int end)//in display start 0 and end size -1
	{

		if (start < end)
		{
			int mid = (start + end) / 2;
			MergeSort(arr, start, mid); // merge sort the elements in range [start, mid]
			MergeSort(arr, mid + 1, end); // merge sort the elements in range [mid+1, end]
			Merge(arr, start, end);   // merge the above 2 componenets
		}

	}
	template <class T>
	int Partition(T arr[], int start, int end) {

		int pivot = end;
		int j = start;
		for (int i = start; i < end; ++i) {
			if (arr[i] < arr[pivot]) {
				swap(arr[i], arr[j]);
				++j;
			}
		}
		swap(arr[j], arr[pivot]);
		return j;

	}
	template <class T >
	void QuickSort(T arr[], int start, int end) //in display nafs el merge sort
	{

		if (start < end) {
			int p = Partition(arr, start, end);
			QuickSort(arr, start, p - 1);
			QuickSort(arr, p + 1, end);
		}

	}
	template <class T>
	void CountSort(T array[], T size) {
		int output[50000];
		int count[50000];
		int max = array[0];

		// Find the largest element of the array
		for (int i = 1; i < size; i++) {
			if (array[i] > max)
				max = array[i];
		}

		// Initialize count array with all zeros.
		for (int i = 0; i <= max; ++i) {
			count[i] = 0;
		}

		// Store the count of each element
		for (int i = 0; i < size; i++) {
			count[array[i]]++;
		}

		// Store the cummulative count of each array
		for (int i = 1; i <= max; i++) {
			count[i] += count[i - 1];
		}

		// Find the index of each element of the original array in count array, and
		// place the elements in output array
		for (int i = size - 1; i >= 0; i--) {
			output[count[array[i]] - 1] = array[i];
			count[array[i]]--;
		}

		// Copy the sorted elements into original array
		for (int i = 0; i < size; i++) {
			array[i] = output[i];
		}
	}
	template <class T>
	void Display(T arr, int n)
	{
		cout << "sort :" << endl;
		for (int i = 0; i < n; i++)
		{
			cout << arr[i] << endl;
		}
	}
}
int main()
{

	int Arr[50000];
	int Arr2[50000];
	int size=0;

	cout << "Enter the array size: ";
	cin >> size;

	srand(time(NULL));

	for (int i = 0; i < size; i++)
	{
		int rnumber = rand() % 5;
		Arr[i] = rnumber;
		Arr2[i] = rnumber;
	}


		auto start = sortlib::chrono::high_resolution_clock::now(); // start timer
		// sort array using the sort function
		sortlib::InsertionSort(Arr, size);
		auto end = sortlib::chrono::high_resolution_clock::now(); // end timer
		auto duration = sortlib::chrono::duration_cast<sortlib::chrono::milliseconds>(end - start);

		cout << "Insertion Sort array in " << duration.count() << " miliseconds." << endl;

		for (int i = 0; i < size; i++)
		{
			Arr[i] = Arr2[i];
		}
	
		auto start2 = sortlib::chrono::high_resolution_clock::now();
	sortlib::selectionSort(Arr, size);
	auto end2 = sortlib::chrono::high_resolution_clock::now();
	  auto duration2 = sortlib::chrono::duration_cast<sortlib::chrono::milliseconds>(end2 - start2);

	cout << "Selection Sort array in " << duration2.count() << " miliseconds." << endl;

	for (int i = 0; i < size; i++)
	{
		Arr[i] = Arr2[i];
	}

	auto start3 = sortlib::chrono::high_resolution_clock::now();
	sortlib::BubbleSort(Arr, size);
	auto end3 = sortlib::chrono::high_resolution_clock::now();
	auto duration3 = sortlib::chrono::duration_cast<sortlib::chrono::milliseconds>(end3 - start3);

	cout << "Bubble Sort array in " << duration3.count() << " miliseconds." << endl;
	for (int i = 0; i < size; i++)
	{
		Arr[i] = Arr2[i];
	}

	auto start4 = sortlib::chrono::high_resolution_clock::now();
	sortlib::ShellSort(Arr, size);
	auto end4 = sortlib::chrono::high_resolution_clock::now();
	auto duration4 = sortlib::chrono::duration_cast<sortlib::chrono::milliseconds>(end4 - start4);
	cout << "Shell Sort array in " << duration4.count() << " miliseconds." << endl;

	for (int i = 0; i < size; i++)
	{
		Arr[i] = Arr2[i];
	}

	auto start5 = sortlib::chrono::high_resolution_clock::now();
	sortlib::CountSort(Arr, size);
	auto end5 = sortlib::chrono::high_resolution_clock::now();
	auto duration5 = sortlib::chrono::duration_cast<sortlib::chrono::milliseconds>(end5 - start5);
	cout << "Count Sort array in " << duration5.count() << " miliseconds." << endl;


	for (int i = 0; i < size; i++)
	{
		Arr[i] = Arr2[i];
	}

	auto start6 = sortlib::chrono::high_resolution_clock::now();
	sortlib::MergeSort(Arr,0,size-1);
	auto end6 = sortlib::chrono::high_resolution_clock::now();
	auto duration6 = sortlib::chrono::duration_cast<sortlib::chrono::milliseconds>(end6 - start6);
	cout << "Merge Sort array in " << duration6.count() << " miliseconds." << endl;
	for (int i = 0; i < size; i++)
	{
		Arr[i] = Arr2[i];
	}

	auto start7 = sortlib::chrono::high_resolution_clock::now();
	sortlib::QuickSort(Arr, 0, size - 1);
	auto end7 = sortlib::chrono::high_resolution_clock::now();
	auto duration7 = sortlib::chrono::duration_cast<sortlib::chrono::milliseconds>(end7 - start7);
	cout << "Quick Sort array in " << duration7.count() << " miliseconds." << endl;
}
