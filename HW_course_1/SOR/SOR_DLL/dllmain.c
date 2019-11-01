// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"            // Visual Studio
#include "sort_methods.h"   // тут функции сортировки

static sort_info_t s_sortList[] =
{
  {ProperSort, SORT_QUICK, SORT_QUASILINEAR, "Sample - C standard qsort" },

//  {MergeSort1, SORT_MERGE, SORT_QUASILINEAR, "Merge 1 - +malloc every pass" },
  {merge_sort_2, SORT_MERGE, SORT_QUASILINEAR, "Merge 2 - +malloc once" },
  {MergeSortWiki, SORT_MERGE, SORT_QUASILINEAR, "Merge wiki - +malloc once" },
  {QiuckSortHoare, SORT_QUICK, SORT_QUASILINEAR, "Quick - Charles Antony Hoare" },
  {QiuckSortHoare2, SORT_QUICK, SORT_QUASILINEAR, "Quick + insertion on small parts" },

// !!!! раскомментировать медленные алгоритмы перед релизом !!!!!!!!!!!
//  {BubbleSort1, SORT_BUBBLE, SORT_QUADRATIC, "Bubble 1" },
//  {BubbleSort2, SORT_BUBBLE, SORT_QUADRATIC, "Bubble 2" },
  
//  {InsertionSort, SORT_INSERTION, SORT_QUADRATIC, "Insertion" },

//  {SelectSort1, SORT_SELECTION, SORT_QUADRATIC, "Selection 1" },
//  {GnomeSort, SORT_INSERTION, SORT_QUADRATIC, "Gnome - Hamid Sarbazi-Azad"},

//  {ShellSort, SORT_SHELL, SORT_SUBQUADRATIC, "Shell - Donald L. Shell"},
  {ShellSort2, SORT_SHELL, SORT_SUBQUADRATIC, "Shell - 9 fix gaps"},
  {ShellSort3, SORT_SHELL, SORT_SUBQUADRATIC, "Shell - up to 40 gaps"},
  
  {CombSort, SORT_COMB, SORT_QUASILINEAR, "Comb Sort" },
  {CombSort2, SORT_COMB, SORT_QUASILINEAR, "Comb Sort" },

  {RadixSort, SORT_RADIX, SORT_LINEAR, "Radix Sort" },

  {PyramidSort, SORT_HEAP, SORT_QUASILINEAR, "Piramid" },
  {HeapSort, SORT_HEAP, SORT_QUASILINEAR, "Heap Sort" },
};


// Возвращает указатель на массив, из которого можно получить
// Функцию сортировик и её имя. count - число элементов 
__declspec(dllexport) sort_info_t* GetSortList(int* count)
{
  *count = sizeof(s_sortList) / sizeof(s_sortList[0]);
  return s_sortList;
}
