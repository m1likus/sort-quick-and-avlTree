#include <iostream>
#include "quickSort.hpp"
#include "avlTree.hpp"
#include <algorithm>

void quickSort(double* ar, int n) {
	quick(ar, 0, n - 1);
}

template<typename T>
void avlSort(T* ar, int n) {
	avlTree<T> tree(ar, n);
	ar = tree.avlTreeContent();
}

bool check(double* ar, int n)
{
	for (int i = 0; i < n - 1; i++)
		if (ar[i + 1] < ar[i])
			return false;
	return true;
}

double* copyAr(double* ar, int n) {
	double* newArray = new double[n];
	for (int i = 0; i < n; i++) {
		newArray[i] = ar[i];
	}
	return newArray;
}



int main() {
	const int n = 1000;
	double* ar1 = new double[n];
	for (int i = 0; i < n; i++) {
		ar1[i] = ((rand() % 2000) / 10.0) - 100;
	}

	quickSort(ar1, n);

	if (check(ar1,n))
		std::cout << "good";
	return 0;
}

