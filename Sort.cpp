#include<iostream>
#include<vector>
#include <ctime>
#include <algorithm> 
using namespace std;
void printVec(const vector<int>& testVec);
void selectionSort(vector<int> testVec);
void insertionSort(vector<int> testVec);
void shellSort(vector<int> testVec);
void merge(vector<int>& testVec, int left, int middle, int right);
void mergesort(vector<int>& testVec, int left, int right);
void mergesort(vector<int> testVec);
int min(int x, int y);
void bottomUPMergesort(vector<int> testVec);
void quicksort(vector<int> testVec);
void quicksort(vector<int>& testVec, int left, int right);
int quick(vector<int>& testVec, int left, int right);
int main() {
	clock_t start, end;
	int n = 10000;
	vector<int> testVec = vector<int>(n, 0);
	for (int i = 0; i < n; ++i) {
		testVec[i] = n-i;
	}
	
	//vector<int> testVec = { 9,7,8,6,5,3,2,1,4,0,21,20,18,19,17,15,16,14,11,13,12,10 };
	random_shuffle(testVec.begin(), testVec.end());
	start = clock();
	selectionSort(testVec);
	end = clock();
	cout << end - start << " MS" << endl;

	start = clock();
	insertionSort(testVec);
	end = clock();
	cout << end - start << " MS" << endl;

	start = clock();
	shellSort(testVec);
	end = clock();
	cout << end - start << " MS" << endl;

	start = clock();
	mergesort(testVec);
	end = clock();
	cout << end - start << " MS" << endl;

	start = clock();
	bottomUPMergesort(testVec);
	end = clock();
	cout << end - start << " MS" << endl;

	start = clock();
	quicksort(testVec);
	end = clock();
	cout << end - start << " MS" << endl;
}
void printVec(const vector<int>& testVec) {
	for (auto i : testVec) {
		cout << i << " ";
	}
	cout << endl;
}
void selectionSort(vector<int> testVec) {
	for (int i = 0; i < testVec.size(); ++i) {
		int min = i;
		for (int j = i + 1; j < testVec.size(); ++j) {
			if (testVec[min] > testVec[j]) {
				min = j;
			}
		}
		swap(testVec[i], testVec[min]);
	}
	//printVec(testVec);
}
void insertionSort(vector<int> testVec) {
	for (int i = 0; i < testVec.size(); ++i) {
		for (int j = i; j > 0; --j) {
			if (testVec[j] > testVec[j - 1]) {
				break;
			}
			swap(testVec[j], testVec[j - 1]);
		}
	}
	//printVec(testVec);
}
void shellSort(vector<int> testVec) {
	int length = testVec.size();
	int h = 1;
	while (h < length / 3) {
		h = 3 * h + 1;
	}
	while (h >= 1) {
		for (int i = 0; i < testVec.size(); ++i) {
			for (int j = i; j > 0; j = j - h) {
				if (testVec[j] > testVec[j - 1]) {
					break;
				}
				swap(testVec[j], testVec[j - 1]);
			}
		}
		h = h / 3;
	}
	//printVec(testVec);
}
void mergesort(vector<int> testVec) {
	mergesort(testVec, 0, testVec.size() - 1);
	//printVec(testVec);
}
void mergesort(vector<int>& testVec, int left, int right) {
	if (left >= right) {
		return;
	}
	int temp = (left + right) / 2;
	mergesort(testVec, left, temp);
	mergesort(testVec, temp + 1, right);
	merge(testVec, left, temp, right);
}
void merge(vector<int>& testVec, int left, int middle, int right) {
	vector<int> temp(right - left + 1, 0);
	for (int i = left; i <= right; ++i) {
		temp[i - left] = testVec[i];
	}
	int i = 0, j = middle + 1 - left;
	for (int k = left; k <= right; ++k) {
		if (i + left > middle) {
			testVec[k] = temp[j++];
		}
		else if (j + left > right) {
			testVec[k] = temp[i++];
		}
		else if (temp[i] < temp[j]) {
			testVec[k] = temp[i++];
		}
		else {
			testVec[k] = temp[j++];
		}
	}
}
int min(int x, int y) {
	if (x < y) {
		return x;
	}
	return y;
}
void bottomUPMergesort(vector<int> testVec) {
	for (int i = 1; i < testVec.size(); i = i * 2) {
		for (int j = 0; j < testVec.size() - i; j = j + 2 * i) {
			merge(testVec, j, j + i - 1, min(j + 2 * i - 1, testVec.size() - 1));
		}
	}
	//printVec(testVec);
}
void quicksort(vector<int> testVec) {
	quicksort(testVec, 0, testVec.size() - 1);
	//printVec(testVec);
}
void quicksort(vector<int>& testVec,int left, int right) {
	if (left > right) {
		return;
	}
	int middle = quick(testVec, left, right);
	quicksort(testVec, left, middle - 1);
	quicksort(testVec, middle + 1, right);
}
int quick(vector<int>& testVec, int left, int right) {
	int i = left, j = right + 1, temp = testVec[left];
	while (true) {
		while(i < right && testVec[++i]<temp){}
		while(j > left  && testVec[--j]>temp){}
		if (i >= j) break;
		swap(testVec[i], testVec[j]);
	}
	swap(testVec[left], testVec[j]);
	return j;
}
