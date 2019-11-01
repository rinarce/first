// SOR.cpp :

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <locale.h>
#include "SOR.h"              // описание структур для dll
#include "testing_system.h"   // тестирующие и отчётные функции

#define OUTPUT_FILE     "result.csv"

// Описание функции, которая вернёт из dll указатель на 
// список функций сортировки  sort_info_t  и число этих фунций  func_count
typedef sort_info_t* (*type_GetSortList)(int* func_count);

int main(int argc, char* argv[])
{ // для русских букв и запятая в выводе float
  setlocale(LC_ALL, "Russian");
  SetConsoleCP(1251);     
  SetConsoleOutputCP(1251);

  // Загружаем DLL
  HINSTANCE hDllInstance = LoadLibraryW(L"SOR_DLL.dll");
  if (NULL == hDllInstance)  {
    printf("Fail load DLL");
    return 1;
  }
  
  // Получаем функцию, которая выдаёт указатель на массив функций сортировки
  type_GetSortList get_SortList = (type_GetSortList)GetProcAddress(hDllInstance, "GetSortList");
  if (NULL == get_SortList)  {
    printf("Fail import function [GetSortList]");
    return 1;
  }
  
  // Получаем массив с адресами функций сортировки и их именами
  int num_sortings = 0;
  sort_info_t* sortings = get_SortList(&num_sortings);
  if (NULL == sortings) {
    printf("Fail get sorting functions");
    return 1;
  }
  printf("\nImported %d types of sort\n", num_sortings);
  printf("Суммарное время в ms для %d сортировок массива случайных чисел\n"
         "[размер массива] Время ms\n", TEST_REPEAT);


  // Пытаемся открыть файл для записи результатов тестирования
  FILE* file_out;
  errno_t err = fopen_s(&file_out, OUTPUT_FILE, "w");
  if (err)  {
    printf("Fail open output file [%s]", OUTPUT_FILE);
    return err;
  }

  // формирую в файле первую строку, там будут значения 
  // размер массива на каждом шаге тестирования.
  TestMakeFirstLine(file_out);


  // Тестируем методы сортировки
  for (int i = 0; i < num_sortings; i++)
  {
    const char* sort_name = sortings[i].name;
    sort_func_t sort_func = sortings[i].sort;
  
    printf("\nTest <%s>\n", sort_name);
    TestAlgorithm(sort_func, sort_name, file_out);   // тестирование тут
  }
  
  fclose(file_out);
  int x = getchar();
  return 0;
}