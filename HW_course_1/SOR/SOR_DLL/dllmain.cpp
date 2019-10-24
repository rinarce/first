// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include "sort_methods.h"

static sort_info_t s_sortList[] =
{
  {EtalonSort, SORT_QUICK, SORT_QUASILINEAR, "Sample - C standard qsort" },

  {_mergeSort_1, SORT_MERGE, SORT_QUASILINEAR, "Merge 1 - +malloc every pass" },
  {_mergeSort_2, SORT_MERGE, SORT_QUASILINEAR, "Merge 2 - +malloc once" },
  {_mergeSort_wiki, SORT_MERGE, SORT_QUASILINEAR, "Merge wiki - +malloc once" },
  {_qiuckSort_Hoare, SORT_QUICK, SORT_QUASILINEAR, "Quick - Charles Antony Hoare" },
  {_qiuckSort_Hoare_2, SORT_QUICK, SORT_QUASILINEAR, "Quick 2 - Charles Antony Hoare" },

// !!!! раскомментировать медленные алгоритмы перед релизом !!!!!!!!!!!
//  {_bubbleSort_1, SORT_BUBBLE, SORT_QUADRATIC, "Bubble 1" },
//  {_bubbleSort_2, SORT_BUBBLE, SORT_QUADRATIC, "Bubble 2" },
  
//  {_selectSort_1, SORT_SELECTION, SORT_QUADRATIC, "Selection 1" },
//  {gnomeSort, SORT_INSERTION, SORT_QUADRATIC, "Gnome - Hamid Sarbazi-Azad"},

  {ShellSort, SORT_SHELL, SORT_SUBQUADRATIC, "Shell - Donald L. Shell"},
  {ShellSort_2, SORT_SHELL, SORT_SUBQUADRATIC, "Shell - 8 fix gaps"},
  {ShellSort_3, SORT_SHELL, SORT_SUBQUADRATIC, "Shell - up to 40 gaps"},
  
  {combSort, SORT_COMB, SORT_QUASILINEAR, "Comb Sort" },

};

__declspec(dllexport) sort_info_t* GetSortList(int* count)
{
  *count = sizeof(s_sortList) / sizeof(s_sortList[0]);
  return s_sortList;
}
