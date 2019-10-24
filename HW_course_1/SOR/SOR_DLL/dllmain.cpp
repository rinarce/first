// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include "sort_methods.h"

static sort_info_t s_sortList[] =
{
  {EtalonSort, SORT_QUICK, SORT_QUASILINEAR, "Sample - C standard qsort" },

  {_mergeSort_1, SORT_MERGE, SORT_QUASILINEAR, "Merge 1 - malloc every pass" },
  {_mergeSort_2, SORT_MERGE, SORT_QUASILINEAR, "Merge 2 - malloc 1 time" },
  {_mergeSort_wiki, SORT_MERGE, SORT_QUASILINEAR, "Merge wiki - malloc 1 time" },
  {_qiuckSort_Hoare, SORT_QUICK, SORT_QUASILINEAR, "Quick - Charles Antony Hoare" },

// ---------------------------------------------------------
// !!!! раскомментировать медленные алгоритмы перед релизом !!!!!!!!!!!
//  {_bubbleSort_1, SORT_BUBBLE, SORT_QUADRATIC, "Bubble 1" },
//  {_bubbleSort_2, SORT_BUBBLE, SORT_QUADRATIC, "Bubble 2" },
  
//  {_selectSort_1, SORT_SELECTION, SORT_QUADRATIC, "Selection 1" },

};

__declspec(dllexport) sort_info_t* GetSortList(int* count)
{
  *count = sizeof(s_sortList) / sizeof(s_sortList[0]);
  return s_sortList;
}
