#pragma once
template<typename T>
void swap(T* a, T* b) {
  T temp = *a;
  *a = *b;
  *b = temp;
}
template<typename T>
void quick(T* ar, const int start, const int end) {
  int l = start;
  int r = end;
  T pivot = ar[(l + r) / 2];
  while (l <= r) {
    while (ar[l] < pivot) l++;
    while (ar[r] > pivot) r--;
    if (l <= r) swap(&ar[l++], &ar[r--]);
  }
  if (start < r) quick(ar, start, r);
  if (end > l) quick(ar, l, end);
}

