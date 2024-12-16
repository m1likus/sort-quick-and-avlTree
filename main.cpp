#include <iostream>
#include "quickSort.hpp"
#include "avlTree.hpp"
#include <random>
#include <chrono>
#include <fstream>

template<typename T>
void quickSort(T* ar, const int n) {
	quick(ar, 0, n - 1);
}
template<typename T>
double avlTreeSort(T* ar, const int n) {
	AvlTree<T> tree;
	const auto start2{ std::chrono::steady_clock::now() };
	tree.AvlTreeFilling(ar, n);
	const auto end2{ std::chrono::steady_clock::now() };
	const std::chrono::duration<double> elapsed_seconds2{ end2 - start2 };
	tree.AvlTreeContent(ar);
	return elapsed_seconds2.count();
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
  //std::random_device rd;
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

template<typename T>
void copyArray(T* array, T* copiedArray, const int n) {
  for (int i = 0; i < n; i++) {
	array[i] = copiedArray[i];
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
  setlocale(LC_ALL, "Russian");
  // Эксперимент 1:
  // q = 1, w = 10^9, n = 1,..., 10^6+1, шаг = 10^4
  {
	// Псевдослучайное заполнение
	const int q = 1, w = 1000000000;
	int i = q;
	std::ofstream f;
	f.open("Experiment1PseudoQuick3.txt", std::ios::out);
	if (f.is_open()) {
	  std::cout << "is open\n";
	}
	while (i < 1000001) {
	  const int n = i;
	  double* a = new double[n];
	  pseudoRandom(a, n, q, w);
	  double* a1 = new double[n];
	  copyArray(a1, a, n);
	  double* a2 = new double[n];
	  copyArray(a2, a, n);

	  const auto start1{ std::chrono::steady_clock::now() };
	  quickSort(a1, n);
	  const auto end1{ std::chrono::steady_clock::now() };
	  const std::chrono::duration<double> elapsed_seconds1{ end1 - start1 };

	  //const double elapsed_seconds2 = avlTreeSort(a2, n);
	  f << elapsed_seconds1.count() << "\n";

	  i = i + 10000;
	  if (!check(a1, n)) {
		std::cout << "quickSort";
		break;
	  }
	  /*if (!check(a2, n)) {
		std::cout << "avlTreeSort";
		break;
	  }*/
	  
	}
	f.close();
  }
  {
	// Заполнение по возрастанию
	const int q = 1, w = 1000000000;
	int i = q;
	std::ofstream f;
	f.open("Experiment1IncreasingQuick3.txt", std::ios::out);
	if (f.is_open()) {
	  std::cout << "is open\n";
	}
	while (i < 1000001) {
	  const int n = i;
	  double* a = new double[n];
	  increasing(a, n, q, w);
	  double* a1 = new double[n];
	  copyArray(a1, a, n);
	  double* a2 = new double[n];
	  copyArray(a2, a, n);

	  const auto start1{ std::chrono::steady_clock::now() };
	  quickSort(a1, n);
	  const auto end1{ std::chrono::steady_clock::now() };
	  const std::chrono::duration<double> elapsed_seconds1{ end1 - start1 };

	  //const double elapsed_seconds2 = avlTreeSort(a2, n);
	  f << elapsed_seconds1.count() << "\n";

	  i = i + 10000;
	  if (!check(a1, n)) {
		std::cout << "quickSort";
		break;
	  }
	  /*if (!check(a2, n)) {
		std::cout << "avlTreeSort";
		break;
	  }*/
	}
	f.close();
  }
  {
	// Заполнение по убыванию
	const int q = 1, w = 1000000000;
	int i = q;
	std::ofstream f;
	f.open("Experiment1DecreasingQuick3.txt", std::ios::out);
	if (f.is_open()) {
	  std::cout << "is open\n";
	}
	while (i < 1000001) {
	  const int n = i;
	  double* a = new double[n];
	  decreasing(a, n, q, w);
	  double* a1 = new double[n];
	  copyArray(a1, a, n);
	  double* a2 = new double[n];
	  copyArray(a2, a, n);

	  const auto start1{ std::chrono::steady_clock::now() };
	  quickSort(a1, n);
	  const auto end1{ std::chrono::steady_clock::now() };
	  const std::chrono::duration<double> elapsed_seconds1{ end1 - start1 };

	  //const double elapsed_seconds2 = avlTreeSort(a2, n);
	  f << elapsed_seconds1.count() << "\n";

	  i = i + 10000;
	  if (!check(a1, n)) {
		std::cout << "quickSort";
		break;
	  }
	  /*if (!check(a2, n)) {
		std::cout << "avlTreeSort";
		break;
	  }*/
	}
	f.close();
  }

  // Эксперимент 2:
  // q = 1, w = 1, ... 100, n = 10^6, шаг = 1
  {
	// Псевдослучайное заполнение
	const int q = 1;
	int w = 1;
	const int  n = 1000000;
	int i = q;
	std::ofstream f;
	f.open("Experiment2PseudoQuick3.txt", std::ios::out);
	if (f.is_open()) {
	  std::cout << "is open\n";
	}
	while (i < 101) {
	  w = i;
	  double* a = new double[n];
	  pseudoRandom(a, n, q, w);
	  double* a1 = new double[n];
	  copyArray(a1, a, n);
	  double* a2 = new double[n];
	  copyArray(a2, a, n);

	  const auto start1{ std::chrono::steady_clock::now() };
	  quickSort(a1, n);
	  const auto end1{ std::chrono::steady_clock::now() };
	  const std::chrono::duration<double> elapsed_seconds1{ end1 - start1 };

	  //const double elapsed_seconds2 = avlTreeSort(a2, n);
	  f << elapsed_seconds1.count() << "\n";

	  i++;
	  if (!check(a1, n)) {
		std::cout << "quickSort";
		break;
	  }
	  /*if (!check(a2, n)) {
		std::cout << "avlTreeSort";
		break;
	  }*/
	}
	f.close();
  }
  {
	// Заполнение по возрастанию
	const int q = 1;
	int w = 1;
	const int  n = 1000000;
	int i = q;
	std::ofstream f;
	f.open("Experiment2IncreasingQuick3.txt", std::ios::out);
	if (f.is_open()) {
	  std::cout << "is open\n";
	}
	while (i < 101) {
	  w = i;
	  double* a = new double[n];
	  increasing(a, n, q, w);
	  double* a1 = new double[n];
	  copyArray(a1, a, n);
	  double* a2 = new double[n];
	  copyArray(a2, a, n);

	  const auto start1{ std::chrono::steady_clock::now() };
	  quickSort(a1, n);
	  const auto end1{ std::chrono::steady_clock::now() };
	  const std::chrono::duration<double> elapsed_seconds1{ end1 - start1 };

	  //const double elapsed_seconds2 = avlTreeSort(a2, n);
	  f << elapsed_seconds1.count() << "\n";

	  i++;
	  if (!check(a1, n)) {
		std::cout << "quickSort";
		break;
	  }
	  /*if (!check(a2, n)) {
		std::cout << "avlTreeSort";
		break;
	  }*/
	}
	f.close();
  }
  {
	// Заполнение по возрастанию
	const int q = 1;
	int w = 1;
	const int  n = 1000000;
	int i = q;
	std::ofstream f;
	f.open("Experiment2DecreasingQuick3.txt", std::ios::out);
	if (f.is_open()) {
	  std::cout << "is open\n";
	}
	while (i < 101) {
	  w = i;
	  double* a = new double[n];
	  decreasing(a, n, q, w);
	  double* a1 = new double[n];
	  copyArray(a1, a, n);
	  double* a2 = new double[n];
	  copyArray(a2, a, n);

	  const auto start1{ std::chrono::steady_clock::now() };
	  quickSort(a1, n);
	  const auto end1{ std::chrono::steady_clock::now() };
	  const std::chrono::duration<double> elapsed_seconds1{ end1 - start1 };

	  //const double elapsed_seconds2 = avlTreeSort(a2, n);
	  f << elapsed_seconds1.count() << "\n";

	  i++;
	  if (!check(a1, n)) {
		std::cout << "quickSort";
		break;
	  }
	  /*if (!check(a2, n)) {
		std::cout << "avlTreeSort";
		break;
	  }*/
	}
	f.close();
  }
}

