// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"

static void _buggySort(int array[], int size) // фиктивная сортировка
{
  int i;
  for (i = 0; i < size; ++i)
    array[i] = 0;
}

static void _bubbleSort_1(int array[], int size) // Пузырьком
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

static void _bubbleSort_2(int array[], int size) // Пузырьком, указатели
{
  int temp;
  int* start = array, * end = array + size, * i, * j;
  int * j_end = end - 1;
  // Сортировка массива пузырьком
  for (i = start; i < end; i++, j_end--) {
    for (j = start; j < j_end; j++) {
      if (*j > *(j + 1)) {
        // меняем элементы местами
        temp = *j;
        *j = *(j + 1);
        *(j + 1) = temp;
      }

    }
  }
}





static void _selectSort_1(int array[], int size) // выбором
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


static sort_info_t s_sortList[] =
{
//  {_buggySort, SORT_NA, SORT_LINEAR, "buggy" },
  {_bubbleSort_1, SORT_BUBBLE, SORT_QUADRATIC, "Bubble 1" },
  {_bubbleSort_2, SORT_BUBBLE, SORT_QUADRATIC, "Bubble 2" },
  {_selectSort_1, SORT_SELECTION, SORT_QUADRATIC, "Selection 1" },

};

__declspec(dllexport) sort_info_t* GetSortList(int* count)
{
  *count = sizeof(s_sortList) / sizeof(s_sortList[0]);
  return s_sortList;
}


