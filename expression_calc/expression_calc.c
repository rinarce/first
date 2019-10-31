// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

// expression_calc.cpp

#include <stdio.h>
#include <locale.h>               // для русских букв
#include <windows.h>              // для русских букв

#include "common_defs.h"          // общие определения


int main(int arg_count, char* arg_values[]) { 
  
  setlocale(LC_ALL, "Russian");   // для русских букв
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);

  // Корректность параметров -------------------------------------------
  // перенаправление не передаётся в аргументы коммандной строки, 
  // 1й параметр - имя программы => значит допустимо максимум 2 аргумента
  if (arg_count > 2) {
    PrintLine(stdout, "", CALC_ERR_ARGS, 0);
    return 1;
  }

  // Открытие файлов ---------------------------------------------------
  FILE*  inputStream = stdin;     // поток ввода
  FILE* outputStream = stdout;    // в стандартный вывод
  if (arg_count == 2) {           // задано имя файла входных данных
    if (fopen_s(&inputStream, arg_values[1], "r")) { 
      PrintLine(outputStream, arg_values[1], CALC_ERR_OPEN_FILE, 0);
      return 2;                   // не удалось открыть файл входных данных
    }
  }
 
  // Цикл обработки строк  -------------------------------------------
  char* inputLine;                // очередная строка до символа \n

  while (1) {
    calc_err_t error = ReadInputLine(inputStream, &inputLine);
    
    if (CALC_LINE_THE_END == error)
      break;                      // конец входного потока - выход
    if (CALC_ERR_INPUT == error || NULL == inputLine)  
      PrintLine(outputStream, "", CALC_ERR_INPUT, 0);
    else {                        // успешно прочитана строка
      double result = 0;          // результат выражения
      error = ProcessLine(inputLine, &result);  
      PrintLine(outputStream, inputLine, error, result);
    }
    free(inputLine);              // строка обработана, больше не нужна
  }

  // Освобождение памяти ---------------------------------------------
  VariableClearGlobal();          // удалить созданные глобальные переменные
  
  // Закрытие файлов --------------------------------------------------
  if (inputStream != stdin)     
    fclose(inputStream);
  if (outputStream != stdout)     // на случай переделки вывода в файл
    fclose(outputStream); 
  return 0;
}
