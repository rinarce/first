#include "pch.h"
#include <stdlib.h>
#include "sort_methods.h"

// -----------------------------------------------------------
// Стандартная функция Си qsort() как пример
int _cmpInt(const void* a, const void* b)
{ 
  return *(int*)a - *(int*)b;   // функция сравнения целых чисел для qsort()
}

// Стандартная функция Си qsort()
extern void EtalonSort(int array[], int size)
{ // Обёртка для единообразного вызова сортировок
  qsort(array, size, sizeof(int), _cmpInt); 
}

// -----------------------------------------------------------
// Пузырьком вариант 1
extern  void _bubbleSort_1(int array[], int size)
{
  int temp;
  // Сортировка массива пузырьком
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (array[j] > array[j + 1]) {
        // меняем элементы местами
        temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }
}

// -----------------------------------------------------------
// Пузырьком вариант 2 - указатели вместо массивов
extern  void _bubbleSort_2(int array[], int size)
{
  int temp;
  int* start = array, * end = array + size, * i, * j;
  int* j_end = end - 1;
  // Сортировка массива пузырьком
  for (i = start; i < end; i++, j_end--) {
    for (j = start; j < j_end; j++) {
      if (*j > * (j + 1)) {
        // меняем элементы местами
        temp = *j;
        *j = *(j + 1);
        *(j + 1) = temp;
      }

    }
  }
}

// -----------------------------------------------------------
// Выбором
extern  void _selectSort_1(int array[], int size)
{
  for (int i = size - 1; i; i--)
  { // начнём с конца, просто так, до второго элемента
    int max = array[i];               // пока примем его за максимальный
    unsigned max_ind = i;             // это индекс максимального элемента
    for (int j = i - 1; j >= 0; j--)  // проверим все элементы левее
      if (array[j] > max)
      {
        max = array[j];
        max_ind = j;
      }
    if (max_ind != i)
    {
      int temp = array[i];
      array[i] = array[max_ind];
      array[max_ind] = temp;
    }
  }
}

// -----------------------------------------------------------
// Слиянием вариант 1         // http://kvodo.ru/mergesort.html 
// С дополнительной памятью, выделяю память на каждом слиянии

void Merge_1(int array[], int first, int last)
{ //функция, сливающая массивы 
  int middle, start, final, j;
  // выделяю вспомогательный массив (размер неоптимален -
  // (размер - по последнему элементу, чтоб не пересчитывать индексы)
  int* mas = (int*)malloc((last + 1) * sizeof(int));
  middle = (first + last) / 2;         //вычисление среднего элемента
  start = first;                       //начало левой части
  final = middle + 1;                  //начало правой части
  for (j = first; j <= last; j++)      //выполнять от начала до конца
    if ((start <= middle)
      && ((final > last) || (array[start] < array[final])))
    {
      mas[j] = array[start];
      start++;
    }
    else
    {
      mas[j] = array[final];
      final++;
    }
  //возвращение результата в список
  for (j = first; j <= last; j++) array[j] = mas[j];
  free(mas);
};

void MergeSort_1(int array[], int first, int last)
{
  //first, last – номера первого и последнего элементов соответственно
  if (first < last)
  {
    MergeSort_1(array, first, (first + last) / 2);     //сортировка левой части
    MergeSort_1(array, (first + last) / 2 + 1, last);  //сортировка правой части
    Merge_1(array, first, last);                       //слияние двух частей
  }
}

// Обёртка для единообразного вызова сортировок
extern void _mergeSort_1(int array[], int size)
{
  MergeSort_1(array, 0, size - 1);
}


// -----------------------------------------------------------
// Слиянием вариант 2         // http://kvodo.ru/mergesort.html 
// С дополнительной памятью, попробую выделять память только 1 раз
static int* tempo = NULL;
void Merge_2(int array[], int first, int last)
{
  int middle, start, final, j;
  int* mas = tempo;
  middle = (first + last) / 2;         //вычисление среднего элемента
  start = first;                       //начало левой части
  final = middle + 1;                  //начало правой части
  for (j = first; j <= last; j++)      //выполнять от начала до конца
    if ((start <= middle)
      && ((final > last) || (array[start] < array[final])))
    {
      mas[j] = array[start];
      start++;
    }
    else
    {
      mas[j] = array[final];
      final++;
    }
  //возвращение результата в список
  for (j = first; j <= last; j++) array[j] = mas[j];

};

void MergeSort_2(int array[], int first, int last)
{
  //first, last – номера первого и последнего элементов соответственно
  if (first < last)
  {
    MergeSort_2(array, first, (first + last) / 2);     //сортировка левой части
    MergeSort_2(array, (first + last) / 2 + 1, last);  //сортировка правой части
    Merge_2(array, first, last);                       //слияние двух частей
  }
}

// Обёртка для единообразного вызова сортировок, // и тут выделю память
extern void _mergeSort_2(int array[], int size)
{ // без выделения каждый раз, выделяю 1 раз, 
  // передаю через глобальную переменную tempo
  tempo = (int*)malloc(size * sizeof(int));;
  MergeSort_2(array, 0, size - 1);
  free(tempo);
}


// -----------------------------------------------------------
/** https://ru.wikipedia.org/wiki/Сортировка_слиянием
  * Сортирует массив, используя рекурсивную сортировку слиянием
  * up - указатель на массив, который нужно сортировать
  * down - указатель на массив с, как минимум, таким же размером как у 'up', используется как буфер
  * left - левая граница массива, передайте 0, чтобы сортировать массив с начала
  * right - правая граница массива, передайте длину массива - 1, чтобы сортировать массив до последнего элемента
  * возвращает: указатель на отсортированный массив. Из-за особенностей работы данной реализации
  * отсортированная версия массива может оказаться либо в 'up', либо в 'down'
  **/
int* merge_sort_wiki(int* up, int* down, unsigned int left, unsigned int right)
{
  if (left == right)
  {
    down[left] = up[left];
    return down;
  }

  unsigned int middle = (left + right) / 2;

  // разделяй и сортируй
  int* l_buff = merge_sort_wiki(up, down, left, middle);
  int* r_buff = merge_sort_wiki(up, down, middle + 1, right);

  // слияние двух отсортированных половин
  int* target = l_buff == up ? down : up;

  unsigned int l_cur = left, r_cur = middle + 1;
  for (unsigned int i = left; i <= right; i++)
  {
    if (l_cur <= middle && r_cur <= right)
    {
      if (l_buff[l_cur] < r_buff[r_cur])
      {
        target[i] = l_buff[l_cur];
        l_cur++;
      }
      else
      {
        target[i] = r_buff[r_cur];
        r_cur++;
      }
    }
    else if (l_cur <= middle)
    {
      target[i] = l_buff[l_cur];
      l_cur++;
    }
    else
    {
      target[i] = r_buff[r_cur];
      r_cur++;
    }
  }
  return target;
}

// алгоритм отсюда // https://ru.wikipedia.org/wiki/Сортировка_слиянием
// без выделения массива каждый раз, выделяю 1 раз, */
extern void _mergeSort_wiki(int array[], int size)
{ 
  int* temp = (int*)malloc(size * sizeof(int));
  int* result = merge_sort_wiki(array, temp, 0, size - 1);

  // особенности данной реализации - результат может быть в любом массиве из 2х
  if (result == temp) // тут результат не там где надо
    for (int i = 0; i < size; i++)
      array[i] = result[i];
  free(temp);
}


// -----------------------------------------------------------
// Быстрая сортировка  («qsort») Чарльз Хоар (Charles Antony Richard Hoare)
// вариант // http://kvodo.ru/quicksort.html
void qiuckSort_Hoare(int* mas, int first, int last)
{
  int mid, count;
  int f = first, l = last;
  mid = mas[(f + l) / 2]; //вычисление опорного элемента
  do
  {
    while (mas[f] < mid) f++;
    while (mas[l] > mid) l--;
    if (f <= l) //перестановка элементов
    {
      count = mas[f];
      mas[f] = mas[l];
      mas[l] = count;
      f++;
      l--;
    }
  } while (f < l);
  if (first < l) qiuckSort_Hoare(mas, first, l);
  if (f < last) qiuckSort_Hoare(mas, f, last);
}

// Обёртка для единообразного вызова сортировок,
extern void _qiuckSort_Hoare(int array[], int size)
{
  qiuckSort_Hoare(array, 0, size - 1);
}