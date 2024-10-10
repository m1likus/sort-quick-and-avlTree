#include <iostream>
#include "quickSort.hpp"
#include "avlTree.hpp"

template<typename T>
void quickSort(T* ar, const int n) {
	quick(ar, 0, n - 1);
}
template<typename T>
void avlTreeSort(T* ar, const int n) {
	AvlTree<T> tree;
	tree.AvlTreeFilling(ar, n);
	tree.AvlTreeContent(ar);
}
template<typename T>
bool check(T* ar, int n){
	for (int i = 0; i < n - 1; i++) {
		if (ar[i + 1] < ar[i]) {
			return false;
		}
	}
	return true;
}
template<typename T>
void printArray(T* array, const int n) {
	for (int i = 0; i < n; i++) {
		std::cout << array[i] << " ";
	}
	std::cout << "\n";
}

int main() {
	time_t time(NULL);
	srand(time);

	//Testing quickSort;
	{
		const int n = 100000;
		double* array = new double[n];
		for (int i = 0; i < n; i++) {
			array[i] = ((rand() % 20000) / 10.0) - 1000;
		}

		quickSort(array, n);

		if (check(array, n)) {
			std::cout << "Quick sort worked well\n";
		}
		else {
			printArray(array, n);
		}
	}
	//Testing avlTreeSort;
	{
		const int n = 100000;
		double* array = new double[n];
		for (int i = 0; i < n; i++) {
			array[i] = ((rand() % 20000) / 10.0) - 1000;
		}

		avlTreeSort(array, n);

		if (check(array, n)) {
			std::cout << "AvlTree sort worked well\n";
		}
		else {
			printArray(array, n);
		}
	}
}

