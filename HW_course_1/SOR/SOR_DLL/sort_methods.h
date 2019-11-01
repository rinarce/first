#ifndef SORT_METHODS_H_INCLUDED__
#define SORT_METHODS_H_INCLUDED__
#pragma once


// Стандартная функция Си qsort() как пример
extern void ProperSort(int array[], int size);


// Пузырьком вариант 1
extern void BubbleSort1(int array[], int size);
// Пузырьком вариант 2 - указатели вместо массивов
extern void BubbleSort2(int array[], int size);


// Вставками http://rosettacode.org/wiki/Sorting_algorithms/Insertion_sort
extern void InsertionSort(int array[], int size);


// Гномья сортировка Hamid Sarbazi-Azad
extern void GnomeSort(int array[], int size);


// Выбором
extern void SelectSort1(int array[], int size);


// Слиянием вариант 1         // http://kvodo.ru/mergesort.html 
// С дополнительной памятью, выделяю память на каждом слиянии
extern void MergeSort1(int array[], int size);

// Слиянием вариант 2         // http://kvodo.ru/mergesort.html 
// С дополнительной памятью, попробую выделять память только 1 раз
extern void merge_sort_2(int array[], int size);

// Слиянием вариант 3 
// алгоритм отсюда // https://ru.wikipedia.org/wiki/Сортировка_слиянием
// с доп памятью, память выделяю 1 раз вначале 
extern void MergeSortWiki(int array[], int size);


// Быстрая сортировка  («qsort») Чарльз Хоар
// вариант // http://kvodo.ru/quicksort.html
extern void QiuckSortHoare(int array[], int size);

// Быстрая сортировка  («qsort») Чарльз Хоар
// вариант // http://kvodo.ru/quicksort.html
// вариант - для малых размеров переходить на другую сортировку
extern void QiuckSortHoare2(int array[], int size);


// сортировка Шелла
extern void ShellSort(int array[], int size);

// сортировка Шелла   /* Пример из книги Герберта Шилдта */
// https://ru.wikibooks.org/wiki/Реализации_алгоритмов/Сортировка/Шелла
// фиксированные значения расстояния между сравнениями
extern void ShellSort2(int array[], int size);

// сортировка Шелла // расстояния между сравнениями по формуле Роберта Седжвика
// https://ru.wikibooks.org/wiki/Реализации_алгоритмов/Сортировка/Шелла
extern void ShellSort3(int array[], int size);


// сортировка расчёска 
// https://ru.wikipedia.org/wiki/Сортировка_расчёской
extern void CombSort(int array[], int size);

// сортировка расчёска
// http://rosettacode.org/wiki/Sorting_algorithms/Comb_sort
extern void CombSort2(int a[], int nElements);


// Radix sort
// http://rosettacode.org/wiki/Sorting_algorithms/Radix_sort
extern void RadixSort(int array[], int size);


// Пирамидальная https://www.codelab.ru/task/PyramidSort/
extern void PyramidSort(int array[], int size);


// Heap sort 
// http://rosettacode.org/wiki/Sorting_algorithms/Heapsort
extern void HeapSort(int array[], int size);

#endif SORT_METHODS_H_INCLUDED__