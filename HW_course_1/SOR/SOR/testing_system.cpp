#include <stdio.h>
#include "testing_system.h"

typedef void (*sort_func_t)(int array[], int size);

// repo https://gist.github.com/Randl/45bcca59720f661fa033a67d5f44bff0 
// description https://habr.com/ru/post/282301/
#include "getCPUTime.c"         // CPU time in seconds
/*  double startTime, endTime;
    startTime = getCPUTime();
    ...
    endTime = getCPUTime();
    fprintf(stderr, "CPU time used = %lf\n", (endTime - startTime));
*/


int test_array[ARRAY_MAX_SIZE] = { 0 };
int etalon_array[ARRAY_MAX_SIZE] = { 0 };

void FillRandom(int array[], int size)
{
  for (int i = 0; i < size; i++)
    array[i] = (int)rand();
}

void CopyArray(int from[], int copy[], int size)
{
  for (int i = 0; i < size; i++)
    copy[i] = from[i];
}

int CompareArrays(int array1[], int array2[], int size)
{ // 0 - если массивы равны
  for (int i = 0; i < size; i++)
    if (array1[i] != array2[i]) 
      return (array1[i] - array2[i]);
  return 0;
}

int cmpInt(const void* a, const void* b)
{ // функция сравнения целых чисел для qsort()
  return *(int*)a - *(int*)b;
}

void EtalonSort(int array[], int size)
{
  qsort(array, size, sizeof(int), cmpInt);
}


double test_pass(sort_func_t fun, int size, int times, const char* algorithm)
{
  double spend_time = 0;
  
  for (int i = times; i; i--)
  {
    FillRandom(test_array, size);
    CopyArray(test_array, etalon_array, size);
    EtalonSort(etalon_array, size);

    double startTime, endTime;
    startTime = getCPUTime();
    
    fun(test_array, size);
    
    endTime = getCPUTime();
    spend_time += (endTime - startTime);

    // Пока не проверяем правильность
    if(CompareArrays(test_array, etalon_array, size))
       fprintf(stderr, "Bad sort implementation function [%s] array [%d]\n", 
               algorithm, size);

  }
  return spend_time;
}

void test_algorithm(sort_func_t fun, const char* algorithm, FILE* out_file)
{
  srand(INIT_RAND);
  double total_time = 0;
  double brutto_time = getCPUTime();
  fprintf(out_file, "%s%s", algorithm, OUT_SEPARATOR);

  for (int size = ARRAY_MIN_SIZE; size < ARRAY_MAX_SIZE; size += ARRAY_SIZE_STEP)
  {
    double pass_time = test_pass(fun, size, TEST_REPEAT, algorithm);
    total_time += pass_time;
    printf("T: [%5d] %f sec\n", size, pass_time);
    fprintf(out_file, "%f%s", pass_time, OUT_SEPARATOR);
  }
  
  printf("Total <%s>: %f sec (brutto %f sec)", 
    algorithm, total_time, getCPUTime()-brutto_time);
  fprintf(out_file, "%f\n", total_time);
}

void test_MakeFirstLine(FILE* out_file)
{ // формирует в файле первую строку
  fprintf(out_file, "Array size%s", OUT_SEPARATOR);
  for (int size = ARRAY_MIN_SIZE; size < ARRAY_MAX_SIZE; size += ARRAY_SIZE_STEP)
  {
    fprintf(out_file, "%7d%s", size, OUT_SEPARATOR);
  }
  fprintf(out_file, "Total\n");
}