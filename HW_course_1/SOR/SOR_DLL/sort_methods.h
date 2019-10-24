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
