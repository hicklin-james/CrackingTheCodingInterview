#include <iostream>
#include <iterator>     // std::advance
#include <set>
#include <queue>
#include <string>
#include <vector>
#include <utility>
#include <climits>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

template < class T >
void print_vector(vector<T> my_vector) {

	for (int i = 0; i < my_vector.size(); i++) {
		cout << "|" << my_vector.at(i);
	}
	cout << "|\n";
}

/**
Bubble Sort:

While the array is not sorted:
	1. Compare the first value with the second
	2. Swap the values if neccessary
		2.1 If two pairs are swapped, mark a flag that indicates
		    we need to do another sweep of the array
	3. Repeat with next pair, until the end of the array
	4. If we made any swaps, repeat this algorithm.

Worst case runtime: O(n^2)
Worst case space complexity: O(1)
**/
void bubbleSort(vector<int> &vector_to_sort) {

	if (vector_to_sort.size() == 0) {
		return;
	}

	bool flag = false;
	for (int i = 0; i < vector_to_sort.size()-1; i++) {
		if (vector_to_sort[i] > vector_to_sort[i+1]) {
			int temp = vector_to_sort[i];
			vector_to_sort[i] = vector_to_sort[i+1];
			vector_to_sort[i+1] = temp;
			flag = true;
		}
	}
	if (flag)
		bubbleSort(vector_to_sort);

	return;

}

/**
Selection Sort:

While the array is not sorted:
	1. Scan the array for the smallest value
	2. Move it to the front
	3. Find the next smallest value and move it
	4. Continue until sorted

Worst case runtime: O(n^2)
Worst case space complexity: O(n)
**/
void selectionSort(vector<int> &vector_to_sort) {

	for (int i = 0; i < vector_to_sort.size(); i++) {
		// find the index of the smallest value
		int min_index = i;
		for (int s = i; s < vector_to_sort.size(); s++) {
			if (vector_to_sort[s] < vector_to_sort[min_index])
				min_index = s;
		}
		// move it to the ith position;
		int temp = vector_to_sort[i];
		vector_to_sort[i] = vector_to_sort[min_index];
		vector_to_sort[min_index] = temp;
	}

}

/**
Merge Sort:

While the array is not sorted:
	1. Sort each pair of elements
	2. Sort every 4 elements by merging the pairs
	3. Etc.

Wost case runtime: O(nlogn)
Worst case space complexity: O(n)
**/
template < class T >
vector<T> combineVectors(vector<T> vec1, vector<T> vec2) {
	//print_vector(vec1);
	//print_vector(vec2);

	vector<T> combinedVector;

	int i = 0;
	int j = 0;
	while (i < vec1.size() && j < vec2.size()) {
		if (vec1.at(i) > vec2.at(j)) {
			combinedVector.push_back(vec2.at(j));
			j++;
		}
		else {
			combinedVector.push_back(vec1.at(i));
			i++;
		}
	}
	if (i == vec1.size()) {
		while (j != vec2.size()) {
			combinedVector.push_back(vec2.at(j));
			j++;
		}
	}
	if (j == vec2.size()) {
		while (i != vec1.size()) {
			combinedVector.push_back(vec1.at(i));
			i++;
		}
	}
	//print_vector(combinedVector);
	return combinedVector;
}

template < class T >
vector<T> mergeSort(vector<T> vector_to_sort) {

	if (vector_to_sort.size() <= 1) {
		return vector_to_sort;
	}
	vector<T> ls;
	vector<T> rs;
	for (int i = 0; i < vector_to_sort.size(); i++) {
		if (i < vector_to_sort.size() / 2) {
			ls.push_back(vector_to_sort.at(i));
		}
		else {
			rs.push_back(vector_to_sort.at(i));
		}
	}
	vector<T> left = mergeSort(ls);
	vector<T> right = mergeSort(rs);
	vector<T> combined = combineVectors(left, right);

	return combined;
}

vector<int> combineSortedVectors(vector<int> vec1, vector<int> vec2, int pivot_val) {

	vec1.push_back(pivot_val);
	for (int i = 0; i < vec2.size(); i++) {
		vec1.push_back(vec2.at(i));
	}
	return vec1;
}


/**
Quick Sort:

While not sorted:
	1. Pick a random element as the pivot
	2. Run Quick Sort on each half separately

Worst case runtime: O(n^2) --- BUT average runtime is O(nlogn)
Worst case space complexity: O(logn)

This method implements an in place sort
**/
template < class T >
void quickSort(vector<T> &vector_to_sort, int low, int high) {

	if (low < high) {
	  	//cout << "low: high: " << low << " " << high << "\n";
		int pivot_index = rand() % (high-low) + low;
		//cout << pivot_index << "\n";

		//vector<int> ls;
		//vector<int> rs;
		T val = vector_to_sort.at(pivot_index);
		T temp = vector_to_sort[high];
		vector_to_sort[high] = vector_to_sort[pivot_index];
		vector_to_sort[pivot_index] = temp;
		int storeIndex = low;
		for (int i = low; i < high; i++) {
			if (vector_to_sort.at(i) <= val) {
				temp = vector_to_sort[i];
				vector_to_sort[i] = vector_to_sort[storeIndex];
				vector_to_sort[storeIndex] = temp;
				storeIndex++;
			}
		}

		temp = vector_to_sort[storeIndex];
		vector_to_sort[storeIndex] = vector_to_sort[high];
		vector_to_sort[high] = temp;

		quickSort(vector_to_sort, low, storeIndex-1);
		quickSort(vector_to_sort, storeIndex+1, high);
	}

	return;
}

/** 
Bucket Sort:

While not sorted:
	1. Partition the array into a finite number of buckets
	2. Sort each bucket individually
	3. Combine the buckets
**/
vector<int> bucketSort(vector<int> vector_to_sort, int buckets) {

	vector<int> to_return;
	vector<int> last_bucket;
	//cout << "\nSIZE: " << vector_to_sort.size() << "\n";
	if (vector_to_sort.size() == 0)
		return to_return;
	if (vector_to_sort.size() == 1) {
		to_return.push_back(vector_to_sort.front());
		return to_return;
	}

	int index_counter = 0;
	int bucket_counter = 0;
	int partition_size = vector_to_sort.size() / buckets;
	while (bucket_counter <= buckets) {
		vector<int> current_bucket;
		for (int s = 0, i = index_counter; s < partition_size && i < vector_to_sort.size(); i++,s++) {
			current_bucket.push_back(vector_to_sort.at(i));
		}
		//print_vector(current_bucket);
		current_bucket = bucketSort(current_bucket, buckets);
		index_counter += partition_size;
		bucket_counter++;
		to_return = combineVectors(to_return, current_bucket);
		//print_vector(to_return);
	}

	return to_return;
}

void printCStyleArray(int *arr, int size) {

	int i = 0;
	while (i < size) {
		std::cout << "|" << arr[i];
		i++;
	}
	std::cout << "|\n";
}

/**
You are given two sorted arrays, A and B, and A has a large enough buffer at the end to hold B. 
Write a method to merge B into A in sorted order.
**/

void mergeCStyleArray(int *A, int *B, int Asize, int Bsize) {

	int i = Asize-1;
	int j = Bsize-1;
	int k = (Asize+Bsize)-1;

	while (i >= 0 && j >= 0) {
		//cout << "A: " << A[i] << " " << "B: " <<  B[j] << "\n";
		if (A[i] > B[j]) {
			A[k--] = A[i--];
			//cout << "A: " << A[i] << " " << "B: " <<  B[j] << "\n";
		}
		else {
			A[k--] = B[j--];
		}
	}
	//cout << "I: J: " << i << " " << j << "\n";
	while (j >= 0) {
		A[k--] = B[j--];
	}
}

/**
Write a method to sort an array of strings so that all the anagrams are next to each other.
Actual sorting just uses quicksort, but operators are overloaded so that comparisons are 
based on string with chars sorted in alphabetical order.
**/
class StringWithAnagramComparer {
	public:
	string string_value;
	StringWithAnagramComparer(string val) { string_value = val;}

	friend bool operator == (StringWithAnagramComparer S1, StringWithAnagramComparer S2);
	friend bool operator > (StringWithAnagramComparer S1, StringWithAnagramComparer S2);
	friend bool operator < (StringWithAnagramComparer S1, StringWithAnagramComparer S2);
	friend bool operator >= (StringWithAnagramComparer S1, StringWithAnagramComparer S2);
	friend bool operator >= (StringWithAnagramComparer S1, StringWithAnagramComparer S2);
	friend bool operator != (StringWithAnagramComparer S1, StringWithAnagramComparer S2);
	friend ostream& operator<<(ostream& os, const StringWithAnagramComparer S1);

	void sortStringByChars() {
		std::vector<char> charvect1(string_value.begin(), string_value.end()); 
		quickSort(charvect1, 0, charvect1.size()-1);
		std::string str1(charvect1.begin(),charvect1.end());
		string_value = str1;
	}
};

ostream& operator << (ostream& os, const StringWithAnagramComparer S1) {
	os << S1.string_value;
	return os;
}

bool operator == (StringWithAnagramComparer S1, StringWithAnagramComparer S2)
{
	S1.sortStringByChars();
	S2.sortStringByChars();
	return (S1.string_value == S2.string_value);
}
bool operator >= (StringWithAnagramComparer S1, StringWithAnagramComparer S2)
{
	S1.sortStringByChars();
	S2.sortStringByChars();
	return (S1.string_value >= S2.string_value);
}
bool operator <= (StringWithAnagramComparer S1, StringWithAnagramComparer S2)
{
	S1.sortStringByChars();
	S2.sortStringByChars();
	return (S1.string_value <= S2.string_value);
}
bool operator > (StringWithAnagramComparer S1, StringWithAnagramComparer S2)
{
	S1.sortStringByChars();
	S2.sortStringByChars();
	return (S1.string_value > S2.string_value);
}
bool operator < (StringWithAnagramComparer S1, StringWithAnagramComparer S2)
{
	S1.sortStringByChars();
	S2.sortStringByChars();
	return (S1.string_value < S2.string_value);
}
bool operator != (StringWithAnagramComparer S1, StringWithAnagramComparer S2)
{
	S1.sortStringByChars();
	S2.sortStringByChars();
	return (S1.string_value != S2.string_value);
}

/** 
Given a sorted array of n integers that has been rotated an unknown number of times, give an O(log n) algorithm 
that finds an element in the array. You may assume that the array was originally sorted in increasing order.
**/
template < class T >
int findElementAfterRotations(std::vector<T> vector_to_search, T key) {
	int size = vector_to_search.size();
	int l = 0;
	int r = size-1;
	while (l <= r) {
		int half = l + ((r-l)/2);
		//cout << "\nl: " << l << " r: " << r << " half: " << half << "\n";
		if (vector_to_search[half] == key)
			return half;
		if (vector_to_search[half] > vector_to_search[l]) {
			// left side is already sorted
			if (vector_to_search[half] > key && vector_to_search[l] <= key) {
				// key is on the left side
				//cout << "Its on the left\n";
				r = half-1;
			}
			else {
				// key is on the right side
				l = half+1;
			}
		}
		else {
			// right side is already sorted
			if (vector_to_search[half] < key && vector_to_search[r] >= key) {
				// key is on the right
				l = half+1;
			}
			else {
				// key is on the left side
				r = half-1;
			}
		}
	}
	return -1;
}

int main() {
	
	cout << "\nBubble Sort\n";
	int myints0[] = {5,6,7,3,4,9,11,23,13,15,16,17,55,44,33,579};
  	vector<int> my_vector0 (myints0, myints0 + sizeof(myints0) / sizeof(int) );

	print_vector(my_vector0);
	bubbleSort(my_vector0);
	print_vector(my_vector0);

	cout << "\nSelection Sort\n";

	int myints1[] = {5,6,7,3,4,9,11,23,13,15,16,17,55,44,33,579};
  	vector<int> my_vector1 (myints1, myints1 + sizeof(myints1) / sizeof(int) );

	print_vector(my_vector1);
	selectionSort(my_vector1);
	print_vector(my_vector1);

	cout << "\nMerge Sort\n";

	int myints2[] = {5,6,7,3,4,9,11,23,13,15,16,17,55,44,33,579};
  	vector<int> my_vector2 (myints2, myints2 + sizeof(myints2) / sizeof(int) );

	print_vector(my_vector2);
	my_vector2 = mergeSort(my_vector2);
	print_vector(my_vector2);

	cout << "\nQuick Sort\n";

	//initialize random seed: 
  	srand (time(NULL));

	int myints3[] = {5,6,7,3,4,9,11,23,13,15,16,17,55,44,33,579};
  	vector<int> my_vector3 (myints3, myints3 + sizeof(myints3) / sizeof(int) );

	print_vector(my_vector3);
	quickSort(my_vector3, 0, my_vector3.size()-1);
	print_vector(my_vector3);
	
	cout << "\nBucket Sort\n";

	int myints4[] = {5,6,7,3,4,9,11,23,13,15,16,17,55,44,33,579};
  	vector<int> my_vector4 (myints4, myints4 + sizeof(myints4) / sizeof(int) );

	print_vector(my_vector4);
	my_vector4 = bucketSort(my_vector4, 2);
	print_vector(my_vector4);

	cout << "\nOnto the Questions!\n\n";

	cout << "9.1\n";
	int arr1[5] = {3,4,5,6,7};
	int arr2[10] = {1,2,8,9,10,0,0,0,0,0};
	std::cout << "Array 1:\n";
	printCStyleArray(arr1, 5);
	std::cout << "Array 2:\n";
	printCStyleArray(arr2, 5);
	mergeCStyleArray(arr2, arr1, 5, 5);
	std::cout << "Merged array:\n";
	printCStyleArray(arr2, 10);

	cout << "\n9.2\n";
	// Note that this type of initialization requires c++11

	std::vector<string> initStrings = {"abcd", "acbd", "gfdr", "adcb", "fghj"};
	std::vector<StringWithAnagramComparer> string_vec;
	for (int i = 0; i < initStrings.size(); i++) {
		StringWithAnagramComparer newString(initStrings[i]);
		string_vec.push_back(newString);
	}

	cout << "Before sorting:\n";
	print_vector(string_vec);
	//StringWithAnagramComparer test1("abcd");
	//StringWithAnagramComparer test2("bcda");
	//if (test1 == test2)
	//	cout << "YES\n";
	quickSort(string_vec, 0, string_vec.size() - 1);
	cout << "After sorting:\n";
	print_vector(string_vec);

	cout << "\n9.3\n";
	vector<int> vector_to_search = {4,5,6,7,8,9,1,2,3};

	cout << "Rotated Vector:\n";
	print_vector(vector_to_search);
	cout << "1 is at index: " << findElementAfterRotations(vector_to_search,1) << "\n";
	cout << "2 is at index: " << findElementAfterRotations(vector_to_search,2) << "\n";
	cout << "3 is at index: " << findElementAfterRotations(vector_to_search,3) << "\n";
	cout << "4 is at index: " << findElementAfterRotations(vector_to_search,4) << "\n";
	cout << "5 is at index: " << findElementAfterRotations(vector_to_search,5) << "\n";
	cout << "6 is at index: " << findElementAfterRotations(vector_to_search,6) << "\n";
	cout << "7 is at index: " << findElementAfterRotations(vector_to_search,7) << "\n";
	cout << "8 is at index: " << findElementAfterRotations(vector_to_search,8) << "\n";
	cout << "9 is at index: " << findElementAfterRotations(vector_to_search,9) << "\n";


	return 0;
}