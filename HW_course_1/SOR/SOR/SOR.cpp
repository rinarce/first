// SOR.cpp :

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <locale.h>
#include "SOR.h"              // описание структур для dll
#include "testing_system.h"   // тестирующие и отчётные функции

#define OUTPUT_FILE     "result.csv"



typedef sort_info_t* (*type_GetSortList)(int* count);

int main(int argc, char* argv[])
{
  setlocale(LC_ALL, "Russian");
  SetConsoleCP(1251);         // для ввода русских букв
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
  
  // Получаем массив с адресами функций сортировки
  int num_sortings = 0;
  sort_info_t* sortings = get_SortList(&num_sortings);
  if (NULL == sortings) {
    printf("Fail get sorting functions");
    return 1;
  }
  printf("Imported %d types of sort\n", num_sortings);
  printf("Суммарное время в сек для %d сортировок массива случайных чисел\n[размер массива] Время\n", TEST_REPEAT);



  // Пытаемся открыть файл для записи результатов тестирования
  FILE* f_out;
  errno_t err = fopen_s(&f_out, OUTPUT_FILE, "w");
  if (err)  {
    printf("Fail open output file [%s]", OUTPUT_FILE);
    return err;
  }

  // формирую в файле первую строку, там будут значения 
  // размер массива на каждом шаге тестирования.
  test_MakeFirstLine(f_out);

  // Тестируем методы сортировки
  for (int i = 0; i < num_sortings; i++)
  {
    const char* s_name = sortings[i].name;
    sort_func_t sort_func = sortings[i].sort;
  
    printf("\nTest <%s>\n", s_name);
    test_algorithm(sort_func, s_name, f_out);

  }
  
  fclose(f_out);
  int x = getchar();
  return 0;
}