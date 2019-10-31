// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

// expression_calc.cpp 

#include <stdio.h>
#include <locale.h>         // для русских букв
#include <windows.h>        // для русских букв

#include "common_defs.h"    // общие определения


int main(int arg_count, char* arg_values[])
{ 
  // для русских букв
  setlocale(LC_ALL, "Russian");
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);


  // Корректность параметров -------------------------------------------
  // перенаправление не передаётся в аргументы коммандной строки, 
  // 1й параметр - имя программы => значит допустимо максимум 2 аргумента
  if (arg_count > 2)
  {
    print_line(stdout, "", CALC_ERR_ARGS, 0);
    return 1;                         // Допустим только 1 параметр запуска
  }

  
  // Открытие файлов ---------------------------------------------------
  FILE*  input_stream = stdin;        // поток ввода
  FILE* output_stream = stdout;       // в стандартный вывод
  
  if (arg_count == 2)                 // задано имя файла входных данных
  { 
    if (fopen_s(&input_stream, arg_values[1], "r")) 
    { 
      print_line(output_stream, arg_values[1], CALC_ERR_OPEN_FILE, 0);
      return 2;                       // не удалось открыть файл входных данных
    }
  }
 
  // Цикл обработки строк  -------------------------------------------
  char* input_line;               // очередная строка до символа \n
  int error = 0;                  // результат вызовов функции, 0 == OK

  // будем вводить строки, выделяя память динамически
  while (1) // условие выхода - строка нулевого размера => конец потока данных
  {
    unsigned line_len;
    error = read_input_line(input_stream, &input_line, &line_len);
    
    if (error || NULL == input_line)  // Не удалось ввести строку
      print_line(output_stream, "", CALC_ERR_INPUT, 0);
    else if (line_len == 0)           // конец входного потока - выход
      break;
    
    else                              // успешно прочитана строка
    {
      double result = 0;              // результат выражения
      error = process_line(input_line, &result);  
      print_line(output_stream, input_line, error, result);
    }
    free(input_line);                 // строка обработана, больше не нужна
  }

  // Освобождение памяти ---------------------------------------------
  free(input_line); 
  variable_clear_global();            // удалить созданные глобальные переменные
  
  // Закрытие файлов --------------------------------------------------
  if (input_stream != stdin)     fclose(input_stream);

  // на случай переделки вывода в файл
  if (output_stream != stdout)   fclose(output_stream); 
  
  // Удалить      ХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХ
  // int _x = getchar();     // пока для отладки

  return 0;
}
