#include <stdio.h>
#include <stdlib.h>
#include "testing_system.h"

// !! закомментить после проверки корректности всех алгоритмов
#define CHECK_SORTED   // проверять массив после работы алгоритма?

// для замеров времени
// repo https://gist.github.com/Randl/45bcca59720f661fa033a67d5f44bff0 
// description https://habr.com/ru/post/282301/
#include "getCPUTime.h"         // CPU time in mseconds


// для экономии времени не будем создавать массивы каждый тест
int s_testArray[ARRAY_MAX_SIZE] = { 0 };

#ifdef CHECK_SORTED // в этом массиве заведомо правильно отсортировано
int s_properArray[ARRAY_MAX_SIZE] = { 0 };
#endif // CHECK_SORTED

// заполнить массив случайными числами
void FillRandom(int array[], int size)
{
  for (int index = 0; index < size; ++index)
    array[index] = rand() - RAND_MAX/2; // пусть будут и отрицательные тоже
}

void CopyArray(int from[], int copy[], int size)
{
  for (int index = 0; index < size; ++index)
    copy[index] = from[index];
}

// возврат 0 - если массивы равны
int CompareArrays(int array1[], int array2[], int size)
{ 
  for (int index = 0; index < size; ++index)
    if (array1[index] != array2[index])
      return (array1[index] - array2[index]);   // до первого несовпадения
  return 0;
}

// функция сравнения целых чисел для qsort()
int cmpInt(const void* a, const void* b)
{
  return *(int*)a - *(int*)b;
}

// Для контроля правильности алгоритмов сортировки 
void ProperSort(int array[], int size)
{
  qsort(array, size, sizeof(int), cmpInt);
}

// Многократный тест для одного заданного размера массива
// возвращает общее время за  times  раз вызовов сортировки
double test_pass(sort_func_t fun, int size, int times, const char* algorithm_name)
{
  double spend_time = 0;
  
  for (int test = times; test; --test)
  { 
    FillRandom(s_testArray, size); // массив случайных чисел

#ifdef CHECK_SORTED
    // Эталонный массив и эталонная сортировка 
    // -- можно отключить после проверки всех алгоритмов
    CopyArray(s_testArray, s_properArray, size);
    ProperSort(s_properArray, size); 
#endif // CHECK_SORTED



    double startTime, endTime;    // замер времени - старт
    startTime = getCPUTime();
    
    fun(s_testArray, size);        // тут вызов проверяемого алгоритма
    
    endTime = getCPUTime();       // замер времени - стоп
    spend_time += (endTime - startTime);

#ifdef CHECK_SORTED
    // проверяем правильность (отключить после успешного прохождения 
    if(CompareArrays(s_testArray, s_properArray, size))
       fprintf(stderr, "Bad sort implementation function [%s] array [%d]\n", 
               algorithm_name, size);
#endif // CHECK_SORTED

  }
  return spend_time;
}


// Тестирует алгоритм на массивах разного размера, результат в CSV файл
void TestAlgorithm(sort_func_t fun, const char* algorithmName, FILE* outFile)
{
  srand(INIT_RAND);
  double total_time = 0;
  double brutto_time = getCPUTime();
  fprintf(outFile, "%-40s%s", algorithmName, OUT_SEPARATOR);

  for (int size = ARRAY_MIN_SIZE; size < ARRAY_MAX_SIZE; size += ARRAY_SIZE_STEP)
  {
    double pass_time = test_pass(fun, size, TEST_REPEAT, algorithmName);
    total_time += pass_time;
    // на экран
    printf("T: [%6d] %8.1f\n", size, pass_time);
    // в файл CSV - только результат
    fprintf(outFile, "%8.1f%s", pass_time, OUT_SEPARATOR);
  }
  
  // суммарное время алгоритма (за все размеры) 
  // будет в последнем элементе строки
  printf("Total <%s>: %f ms (brutto %f ms)\n", 
    algorithmName, total_time, getCPUTime()-brutto_time);
  fprintf(outFile, " %f\n", total_time);
}



// формирую в файле первую строку, там будут значения 
// размер массива на каждом шаге тестирования.
void TestMakeFirstLine(FILE* out_file)
{ // формирует в файле первую строку
  fprintf(out_file, "Array size%32s", OUT_SEPARATOR);

  // цикл такой же как в функции тестирования алгоритма
  for (int size = ARRAY_MIN_SIZE; size < ARRAY_MAX_SIZE; size += ARRAY_SIZE_STEP)
  { // печатаю размер тестового массива
    fprintf(out_file, "%8d%s", size, OUT_SEPARATOR);
  }
  fprintf(out_file, " Total\n");
}