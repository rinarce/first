#include "sorts.h"

static void _buggySort(int array[], int size)
{
  int i;
  for (i = 0; i < size; ++i)
    array[i] = 0;
}

static sort_info_t s_sortList[] = 
{
  {_buggySort, SORT_INSERTION, SORT_QUADRATIC, "buggy" },
};

__declspec(dllexport) sort_info_t* GetSortList(int* count)
{
   *count = sizeof(s_sortList) / sizeof(s_sortList[0]);
   return s_sortList;
}
