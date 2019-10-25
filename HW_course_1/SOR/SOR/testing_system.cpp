﻿#include <stdio.h>
#include "testing_system.h"

// !! закомментить после проверки корректности всех алгоритмов
#define CHECK_SORTED   // проверять массив после работы алгоритма?

// для замеров времени
// repo https://gist.github.com/Randl/45bcca59720f661fa033a67d5f44bff0 
// description https://habr.com/ru/post/282301/
#include "getCPUTime.c"         // CPU time in mseconds


// для экономии времени не будем создавать массивы каждый тест
int test_array[ARRAY_MAX_SIZE] = { 0 };

#ifdef CHECK_SORTED // в этом массиве заведомо правильно отсортировано
  int etalon_array[ARRAY_MAX_SIZE] = { 0 };
#endif // CHECK_SORTED

// заполнить массив случайными числами
void FillRandom(int array[], int size)
{
  for (int i = 0; i < size; i++)
    array[i] = rand() - RAND_MAX/2; // пусть будут и отрицательные тоже
}

void CopyArray(int from[], int copy[], int size)
{
  for (int i = 0; i < size; i++)
    copy[i] = from[i];
}

// возврат 0 - если массивы равны
int CompareArrays(int array1[], int array2[], int size)
{ 
  for (int i = 0; i < size; i++)
    if (array1[i] != array2[i]) 
      return (array1[i] - array2[i]);   // до первого несовпадения
  return 0;
}

// функция сравнения целых чисел для qsort()
int cmpInt(const void* a, const void* b)
{
  return *(int*)a - *(int*)b;
}

// Для контроля правильности алгоритмов сортировки 
void etalon_sort(int array[], int size)
{
  qsort(array, size, sizeof(int), cmpInt);
}

// Многократный тест для одного заданного размера массива
// возвращает общее время за  times  раз вызовов сортировки
double test_pass(sort_func_t fun, int size, int times, const char* algorithm_name)
{
  double spend_time = 0;
  
  for (int i = times; i; i--)
  { 
    FillRandom(test_array, size); // массив случайных чисел

#ifdef CHECK_SORTED
    // Эталонный массив и эталонная сортировка 
    // -- можно отключить после проверки всех алгоритмов
    CopyArray(test_array, etalon_array, size);
    etalon_sort(etalon_array, size); 
#endif // CHECK_SORTED



    double startTime, endTime;    // замер времени - старт
    startTime = getCPUTime();
    
    fun(test_array, size);        // тут вызов проверяемого алгоритма
    
    endTime = getCPUTime();       // замер времени - стоп
    spend_time += (endTime - startTime);

#ifdef CHECK_SORTED
    // проверяем правильность (отключить после успешного прохождения 
    if(CompareArrays(test_array, etalon_array, size))
       fprintf(stderr, "Bad sort implementation function [%s] array [%d]\n", 
               algorithm_name, size);
#endif // CHECK_SORTED

  }
  return spend_time;
}


// Тестирует алгоритм на массивах разного размера, результат в CSV файл
void test_algorithm(sort_func_t fun, const char* algorithm_name, FILE* out_file)
{
  srand(INIT_RAND);
  double total_time = 0;
  double brutto_time = getCPUTime();
  fprintf(out_file, "%-40s%s", algorithm_name, OUT_SEPARATOR);

  for (int size = ARRAY_MIN_SIZE; size < ARRAY_MAX_SIZE; size += ARRAY_SIZE_STEP)
  {
    double pass_time = test_pass(fun, size, TEST_REPEAT, algorithm_name);
    total_time += pass_time;
    // на экран
    printf("T: [%6d] %8.1f\n", size, pass_time);
    // в файл CSV - только результат
    fprintf(out_file, "%8.1f%s", pass_time, OUT_SEPARATOR);
  }
  
  // суммарное время алгоритма (за все размеры) 
  // будет в последнем элементе строки
  printf("Total <%s>: %f ms (brutto %f ms)\n", 
    algorithm_name, total_time, getCPUTime()-brutto_time);
  fprintf(out_file, " %f\n", total_time);
}



// формирую в файле первую строку, там будут значения 
// размер массива на каждом шаге тестирования.
void test_MakeFirstLine(FILE* out_file)
{ // формирует в файле первую строку
  fprintf(out_file, "Array size%32s", OUT_SEPARATOR);

  // цикл такой же как в функции тестирования алгоритма
  for (int size = ARRAY_MIN_SIZE; size < ARRAY_MAX_SIZE; size += ARRAY_SIZE_STEP)
  { // печатаю размер тестового массива
    fprintf(out_file, "%8d%s", size, OUT_SEPARATOR);
  }
  fprintf(out_file, " Total\n");
}