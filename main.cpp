#include <iostream>
#include "quickSort.hpp"
#include "avlTree.hpp"
#include <random>
#include <chrono>

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
//Псевдослучайное заполнение массива
template<typename T>
void pseudoRandom(T* array, const int n, int q, int w) {
  std::random_device rd;
  //std::mt19937 gen(rd);
  std::mt19937 gen(0);
  std::uniform_real_distribution<T> distrib(q, w);
  for (int i = 0; i < n; i++) {
	array[i] = distrib(gen);
  }
}
// По возрастанию заполнение массива
template<typename T>
void increasing(T* array, const int n, const int q, const int w) {
  int x = (w - q) / n; //равные промежутки между элементами
  array[0] = q; //первый элемент - нижняя граница
  for (int i = 1; i < n; i++) {
	array[i] = array[i - 1] + x;
  }
}
// По убыванию заполнение массива
template<typename T>
void decreasing(T* array, const int n, const int q, const int w) {
  int x = (w - q) / n; //равные промежутки между элементами
  array[0] = w; //первый элемент - верхняя граница
  for (int i = 1; i < n; i++) {
	array[i] = array[i - 1] - x;
  }
}



int main() {
  // int n; кол-во элементов в исходном массиве a
  // double* a = new double[n]; массив a
  // double q, w; //нижняя и верхняя для значений элементов массива
  // Заполнение массива а
  // 1. Псевдослучайное
  // 2. По неубыванию
  // 3. По невозрастанию
  {
	// Эксперимент 1:
	// q = 1, w = 10^9, n = 1,..., 10^6+1, шаг = 10^4
	// Псевдослучайное заполнение
	int q = 1, w = 1000000000;
	int i = 1;
	while(i < 1000001) {
	  const int n = i;
	  std::cout << n << std::endl;
	  double* a = new double[n];
	  pseudoRandom(a, n, q, w);
	  const auto start{ std::chrono::steady_clock::now() };
	  quickSort(a, n);
	  const auto end{ std::chrono::steady_clock::now() };
	  const std::chrono::duration<double> elapsed_seconds{ end - start };
	  std::cout << elapsed_seconds.count() << std::endl;
	  i = i + 10000;
	}
  }

	//Testing quickSort;
	{
		const int n = 10;
		double* array = new double[n];
		for (int i = 0; i < n; i++) {
			array[i] = ((rand() % 20000) / 10.0) - 1000;
		}

		quickSort(array, n);

		if (check(array, n)) {
		  for (int i = 0; i < n; i++) {
			std::cout << array[i] << " ";
		  }
			std::cout << "Quick sort worked well\n";
		}
		else {
			printArray(array, n);
		}
	}
	//Testing avlTreeSort;
	{
		const int n = 10;
		double* array = new double[n];
		for (int i = 0; i < n; i++) {
			array[i] = ((rand() % 20000) / 10.0) - 1000;
		}

		avlTreeSort(array, n);

		if (check(array, n)) {
		  for (int i = 0; i < n; i++) {
			std::cout << array[i] << " ";
		  }
		std::cout << "AvlTree sort worked well\n";
		}
		else {
			printArray(array, n);
		}
	}
}

