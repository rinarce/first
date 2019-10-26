#include "calc_process.h"
#include <stdlib.h>


// 1 - если в строке только всевозможные пробелы ( \t\n\v\f\r)
int is_only_spaces(char* str)
{
  while (*str)
    if (!isspace((int)(*str++)))
      return 0;
  return 1;
}


// вычисляет строку выражений, возвращает тип строки (ок или ошибка) и результат
int process_line(char* str, double* result)
{
  unsigned str_len = STR_Lenght(str);
  if (str_len == 0)
    return CALC_LINE_EMPTY;
  if (str_len >= 2 && str[0] == '/' && str[1] == '/')
    return CALC_LINE_COMMENT;
  if (is_only_spaces(str))
    return CALC_LINE_SPACES;
  
  // тут обработка
  
  return 0;
}