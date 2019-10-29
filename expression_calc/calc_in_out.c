// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "calc_in_out.h"
#include "calc_process.h"     // for error codes
#include "str_functions.h"


// ---------------------------------------------------------------------------
// return - 0 == OK    1 == ошибка открытия входного файла
// input_file - если указан файл в коммандной строке, то он откроется на ввод
// иначе input_file = stdin  - файл не указан, или ввод перенаправлен (этим займётся windows)
int detect_input_stream(int arg_count, char* arg_values[], FILE** input_file)
{
  if (arg_count == 1) {             // входной файл не задан
    *input_file = stdin;
    return 0;                       // OK
  }
  fopen_s(input_file, arg_values[1], "r");
  return (NULL == *input_file);     // 0 - открыт успешно, 1 - нет (== NULL)
}


// ---------------------------------------------------------------------------
// вводит строку произвольной длины, самостоятельно выделяет память
// в *str возвращает указатель на строку, return = длина строки
// \n в конце обрезается, но считается в длине (длина == 0 - конец потока ввода)
unsigned int read_input_line(FILE* input_stream, char** str)
{
  char* result_str = NULL;  // Это указатель на итоговую строку, тут накапливаем ввод
  unsigned int str_len = 0; // Накапливаем длину строки, в конце - возвращаем
  char buffer[DST_BUFFER_SIZE + 1] = { 0 };     // Для порций ввода

  while (1)  // считываем строку порциями размера DST_BUFFER_SIZE
  {
    // fgets читает на 1 символ меньше, так как в конце всегда добавляет '\0'
    unsigned int input_len = str_lenght(fgets(buffer, DST_BUFFER_SIZE + 1, input_stream));

    if (buffer[input_len - 1] == '\n')    // отрезаем '\n'
        buffer[input_len - 1] = '\0';  

    // просим новый кусок памяти
    char* new_str = (char*)realloc(result_str, str_len + input_len + 1);

    if (NULL == new_str)  // выделение памяти не удалось, возвращаем что есть
      break;              // ПЕРЕДЕЛАТЬ НА ПЕРЕДАЧУ ОШИБКИ НАВЕРХ ХХХХХХХХХХХХХХХХХХХХХХХХ
    else
    {
      result_str = new_str;                  //  результат возможно уже в другом месте

      // первые ячейки уже заполнены, сместиться на длину имеющейся строки 
      char* res_pointer = result_str + str_len;
      
      char* in_pointer = buffer;             // добавляем очередную порцию из buffer
      do { *res_pointer = *in_pointer++;  }  // копируем пока не '\0' в конце buffer
      while (*res_pointer++);


      str_len += input_len;  // новая длина строки

                             // использован не весь входной буфер => ввод закончен
      if (input_len < DST_BUFFER_SIZE)
        break;
    }
  }

  *str = result_str;
  return str_len;
}

// ---------------------------------------------------------------------------
// печатает строку правильное выражение == результат
void print_expression(FILE* output_stream, char* input_line, double result)
{
  fprintf(output_stream, "%s == %g\n", input_line, result);
}

// печатает строку комментарий 
void print_comment(FILE* output_stream, char* input_line)
{
  fprintf(output_stream, "%s\n", input_line);
}

// печатает строку без значащих символов 
void print_spaces(FILE* output_stream, char* input_line)
{
  fprintf(output_stream, "%s\n", input_line);
}

// печатает строку пустую (в строке только \n)
void print_empty(FILE* output_stream)
{
  fprintf(output_stream, "\n");
}

// ---------------------------------------------------------------------------
// печатает строку с ошибкой
void print_error(FILE* output_stream, char* input_line, int error_code)
{
  fprintf(output_stream, "%s == ERROR: ", input_line);
  switch (error_code)
  {
  case CALC_ERR_MEMORY:
    fprintf(output_stream, "not enough memory.\n");
    break;
  case CALC_ERR_ZERO_DIV:
    fprintf(output_stream, "divide by 0.\n");
    break;
  case CALC_ERR_BRACKETS:
    fprintf(output_stream, "brackets mismatch.\n");
    break;
  case CALC_ERR_OTHER:
    fprintf(output_stream, "other error.\n");
    break;
  case CALC_ERR_X:
    fprintf(output_stream, "jet not defined error !!!!! \n");
    break;
  case CALC_ERR_SQRT_N:
    fprintf(output_stream, "square root from negative number.\n");
    break;
  case CALC_ERR_PARSE:
    fprintf(output_stream, "Can't parse line.\n");
    break;
  case CALC_ERR_ALGO:
    fprintf(output_stream, "ASSERT. Something wrong in algorithm.\n");
    break;
  case CALC_ERR_EVAL:
    fprintf(output_stream, "Can't evaluate number.\n");
    break;
  case CALC_ERR_VARS:
    fprintf(output_stream, "Variables.\n");
    break;

  default:
    fprintf(output_stream, "not recognized error type.\n");
    break;
  }
}