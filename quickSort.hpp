#pragma once
#include <iostream>
#include <ctime>
#include <malloc.h>
#include <algorithm>
#include <locale.h>
#include <stdio.h>
#include <cstdlib>

//void swap(double* a, double* b) {
//	double temp = *a;
//	*b = *a;
//	*a = temp;
//}

void quick(double* ar, int start, int end) {
	int l = start;
	int r = end;
	double pivot = ar[(l + r) / 2];
	while (l <= r) {
		while (ar[l] < pivot) l++;
		while (ar[r] > pivot) r--;
		if (l <= r) std::swap(ar[l++], ar[r--]);
	}
	if (start < r) quick(ar, start, r);
	if (end > l) quick(ar, l, end);
}

