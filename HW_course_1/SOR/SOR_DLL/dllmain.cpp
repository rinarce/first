// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"            // Visual Studio
#include "sort_methods.h"   // тут функции сортировки

static sort_info_t s_sortList[] =
{
  {etalon_sort, SORT_QUICK, SORT_QUASILINEAR, "Sample - C standard qsort" },

//  {merge_sort_1, SORT_MERGE, SORT_QUASILINEAR, "Merge 1 - +malloc every pass" },
  {merge_sort_2, SORT_MERGE, SORT_QUASILINEAR, "Merge 2 - +malloc once" },
  {merge_sort_wiki, SORT_MERGE, SORT_QUASILINEAR, "Merge wiki - +malloc once" },
  {qiuck_sort_Hoare, SORT_QUICK, SORT_QUASILINEAR, "Quick - Charles Antony Hoare" },
  {qiuck_sort_Hoare_2, SORT_QUICK, SORT_QUASILINEAR, "Quick + insertion on small parts" },

// !!!! раскомментировать медленные алгоритмы перед релизом !!!!!!!!!!!
//  {bubble_sort_1, SORT_BUBBLE, SORT_QUADRATIC, "Bubble 1" },
//  {bubble_sort_2, SORT_BUBBLE, SORT_QUADRATIC, "Bubble 2" },
  
//  {insertion_sort, SORT_INSERTION, SORT_QUADRATIC, "Insertion" },

//  {select_sort_1, SORT_SELECTION, SORT_QUADRATIC, "Selection 1" },
//  {gnome_sort, SORT_INSERTION, SORT_QUADRATIC, "Gnome - Hamid Sarbazi-Azad"},

//  {shell_sort, SORT_SHELL, SORT_SUBQUADRATIC, "Shell - Donald L. Shell"},
  {shell_sort_2, SORT_SHELL, SORT_SUBQUADRATIC, "Shell - 9 fix gaps"},
  {shell_sort_3, SORT_SHELL, SORT_SUBQUADRATIC, "Shell - up to 40 gaps"},
  
  {comb_sort, SORT_COMB, SORT_QUASILINEAR, "Comb Sort" },
  {comb_sort_2, SORT_COMB, SORT_QUASILINEAR, "Comb Sort" },

  {radix_sort, SORT_RADIX, SORT_LINEAR, "Radix Sort" },

  {pyramid_sort, SORT_HEAP, SORT_QUASILINEAR, "Piramid" },
  {heap_sort, SORT_HEAP, SORT_QUASILINEAR, "Heap Sort" },
};


// Возвращает указатель на массив, из которого можно получить
// Функцию сортировик и её имя. count - число элементов 
__declspec(dllexport) sort_info_t* GetSortList(int* count)
{
  *count = sizeof(s_sortList) / sizeof(s_sortList[0]);
  return s_sortList;
}
