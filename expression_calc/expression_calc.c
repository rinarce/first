// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

// expression_calc.cpp 

#include <stdio.h>
#include <locale.h>         // для русских букв
#include <windows.h>        // для русских букв

#include "calc_in_out.h"    // ввод-вывод
#include "calc_process.h"   // обработка
#include "calc_variables.h" // очистить глобальные переменные перед выходом



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
    printf("ERROR: bad command line. "
           " Use: expression_calc.exe inpit_file_name\n");
    return 1;
  }

  
  // Открытие файлов ---------------------------------------------------
  FILE*  input_stream = NULL;         // поток ввода
  FILE* output_stream = stdout;       // в стандартный вывод

  if (detect_input_stream(arg_count, arg_values, &input_stream))
  {
    fprintf(output_stream, 
            "ERROR: can't open input file [%s]\n", arg_values[1]);
    return 2;
  }


  // Цикл обработки строк  -------------------------------------------
  char* input_line;               // очередная строка до символа \n
  int error = 0;                  // результат вызовов функции, 0 == OK
  
  // будем вводить строки, выделяя память динамически
  while (1) // условие выхода - строка нулевого размера => конец потока данных
  {
    unsigned line_len;
    error = read_input_line(input_stream, &input_line, &line_len);
    if (error || NULL == input_line)
      print_input_error(output_stream);
    else if (line_len == 0)       // конец входного потока - выход
      break;
    else                          // успешно прочитана строка
    {
      double result = 0;          // результат выражения
      error = process_line(input_line, &result);  // обработать строку
      switch (error)
      {
      case CALC_LINE_OK:          // это корректное выражение
        print_expression(output_stream, input_line, result);
        break;
      case CALC_LINE_COMMENT:     // это комментарий
        print_comment(output_stream, input_line);
        break;
      case CALC_LINE_EMPTY:       // это строка пустая (только \n)
        print_empty(output_stream);
        break;
      case CALC_LINE_SPACES:      // это строка без значащих символов
        print_spaces(output_stream, input_line);
        break;

      default:                    // всё остальное считаем ошибкой
        print_error_v2(output_stream, input_line, error);
        break;
      }
    }
    free(input_line);             // строка обработана, больше не нужна
  }

  // Освобождение памяти ---------------------------------------------
  free(input_line); 
  variable_clear_global();  // удалить созданные глобальные переменные
  
  // Закрытие файлов --------------------------------------------------
  if (input_stream != stdin)     fclose(input_stream);

  // на случай переделки вывода в файл
  if (output_stream != stdout)   fclose(output_stream); 
  
  // Удалить      ХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХ
  // int _x = getchar();     // пока для отладки

  return 0;
}
