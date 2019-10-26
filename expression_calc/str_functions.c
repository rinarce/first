#include <stdlib.h>
#include <ctype.h>  // для isspace()

// выделяет место для строки размером (size + 1)
char* AllocateString(unsigned int size)
{ 
  char* new_str = (char*)malloc(size + 1);
  if (NULL != new_str)
    *new_str = '\0';   // на всякий случай в начале делаем конец строки
  return new_str;
}

// длина строки до '\0'
unsigned int str_lenght(char const* str) 
{
  int len = 0;
  if (NULL != str)          // проверка, что указатель корректен
    while (*str++) len++;
  return len;
}

// 1 - если в строке только всевозможные пробелы ( \t\n\v\f\r)
int is_only_spaces(char* str)
{
  while (*str)
    if (!isspace((int)(*str++)))
      return 0;
  return 1;
}

// 1 - если в строке первые значащие символы //
int is_comment(char* str)
{
  while (*str)
    if (!isspace((int)(*str)))   // пропустить все незначащие символы
      break;
    else str++;

  // проверяем что оба символа - это не конец строки и равны '//'
  if (*str && *str == '/' && *(str + 1) && *(str + 1) == '/')
    return 1;
  else return 0;
}

// 1 - если в строке нарушена парность скобок (()
int is_bracket_error(char* str)
{
  int nest = 0;                       // счётчик открытых скобок
  while (*str)
  {
    if (*str == '(')        nest++;   // открывающая скобка
    else if (*str == ')')   nest--;   // закрывающая скобка

    if (nest < 0)  return 1;          // закрывающая раньше открывающей

    str++;
  }
  return nest;            // если >0 - остались незакрытые скобки
}


// сравнивает строки на длину distance, возврат 1 если равны, 0 иначе
int str_compare_fix_len(char const* str1, char const* str2, unsigned int distance)
{
  while (distance--)
    if (*(str1++) != *(str2++)) // до первого несовпадения
      return 0;
  return 1;
}

// подсчёт пробелов
unsigned int str_count_spaces(char const* str)
{ 
  unsigned count = 0;
  while (*str)
    if (isspace((int)(*str++)))
      count++;
  return count;
}

// подсчёт непробелов
unsigned int str_count_non_spaces(char const* str)
{
  unsigned count = 0;
  while (*str)
    if (!isspace((int)(*str++)))
      count++;
  return count;
}

// из str удаляет все пробелы -> в новую созданную строку
char* str_remove_spaces(char const* str)
{ 
  unsigned int new_len = str_count_non_spaces(str);
  char* new_string = (char*)malloc(new_len + 1);
  
  if (NULL == new_string)         // выделение памяти не удалось
    return NULL;

  char* new_str_ptr = new_string; // копирование
  char const* old_str_ptr = str;
  
  while (*old_str_ptr)            // пока не конец строки
    if (!isspace(*old_str_ptr))   // копируем не пробел
      *(new_str_ptr++) = *(old_str_ptr++);
    else
      old_str_ptr++;              // пробел - пропускаем

  *new_str_ptr = '\0';            //  конец строки
  return new_string;
}
