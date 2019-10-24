#pragma once

// Стандартная функция Си qsort() как пример
extern void EtalonSort(int array[], int size);


// Пузырьком вариант 1
extern void _bubbleSort_1(int array[], int size);
// Пузырьком вариант 2 - указатели вместо массивов
extern void _bubbleSort_2(int array[], int size);


// Выбором
extern void _selectSort_1(int array[], int size);


// Слиянием вариант 1         // http://kvodo.ru/mergesort.html 
// С дополнительной памятью, выделяю память на каждом слиянии
extern void _mergeSort_1(int array[], int size);

// Слиянием вариант 2         // http://kvodo.ru/mergesort.html 
// С дополнительной памятью, попробую выделять память только 1 раз
extern void _mergeSort_2(int array[], int size);

// Слиянием вариант 3 
// алгоритм отсюда // https://ru.wikipedia.org/wiki/Сортировка_слиянием
// с доп памятью, память выделяю 1 раз вначале 
extern void _mergeSort_wiki(int array[], int size);

// Быстрая сортировка  («qsort») Чарльз Хоар
// вариант // http://kvodo.ru/quicksort.html
extern void _qiuckSort_Hoare(int array[], int size);

// Быстрая сортировка  («qsort») Чарльз Хоар
// вариант // http://kvodo.ru/quicksort.html
// вариант - для малых размеров переходить на другую сортировку
extern void _qiuckSort_Hoare_2(int array[], int size);


// Гномья сортировка Hamid Sarbazi-Azad
extern void gnomeSort(int array[], int size);

//сортировка Шелла
extern void ShellSort(int array[], int size);

//сортировка Шелла   /* Пример из книги Герберта Шилдта */
// https://ru.wikibooks.org/wiki/Реализации_алгоритмов/Сортировка/Шелла
// фиксированные значения расстояния между сравнениями
extern void ShellSort_2(int array[], int size);

//сортировка Шелла // расстояния между сравнениями по формуле Роберта Седжвика
// https://ru.wikibooks.org/wiki/Реализации_алгоритмов/Сортировка/Шелла
extern void ShellSort_3(int array[], int size);

//сортировка расчёска 
// https://ru.wikipedia.org/wiki/Сортировка_расчёской
extern void combSort(int array[], int size);

//сортировка расчёска
// http://rosettacode.org/wiki/Sorting_algorithms/Comb_sort
extern void CombSort_2(int a[], int nElements);

// Radix sort
// http://rosettacode.org/wiki/Sorting_algorithms/Radix_sort
extern void Radix_Sort(int array[], int size);




