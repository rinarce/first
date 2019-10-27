#include <stdlib.h>
#include <ctype.h>  // дл€ isspace()

// выдел€ет место дл€ строки размером (size + 1)
char* AllocateString(unsigned int size)
{ 
  char* new_str = (char*)malloc(size + 1);
  if (NULL != new_str)
    *new_str = '\0';   // на вс€кий случай в начале делаем конец строки
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
  while (*str && isspace((int)(*str)))
    str++;   // пропустить все незначащие символы

  // провер€ем что оба символа - это не конец строки и равны '//'
  return (*str && *str == '/' && *(str + 1) && *(str + 1) == '/');
}

// 1 - если в строке нарушена парность скобок (()
int is_bracket_error(char* str)
{
  int nest = 0;                       // счЄтчик открытых скобок
  while (*str)
  {
    if (*str == '(')        nest++;   // открывающа€ скобка
    else if (*str == ')')   nest--;   // закрывающа€ скобка

    if (nest < 0)  
      return 1;                       // закрывающа€ раньше открывающей

    str++;
  }
  return nest;            // если >0 - остались незакрытые скобки
}


// сравнивает строки на длину distance, возврат 1 если равны, 0 иначе
int str_compare_fix_len(char const* str1, char const* str2, unsigned int distance)
{
  while (distance--)
    if (*(str1++) != *(str2++)) // до первого несовпадени€
      return 0;
  return 1;
}

// подсчЄт пробелов
unsigned int str_count_spaces(char const* str)
{ 
  unsigned count = 0;
  while (*str)
    if (isspace((int)(*str++)))
      count++;
  return count;
}

// подсчЄт непробелов
unsigned int str_count_non_spaces(char const* str)
{
  unsigned count = 0;
  while (*str)
    if (!isspace((int)(*str++)))
      count++;
  return count;
}

// из str удал€ет все пробелы -> в новую созданную строку
char* str_remove_spaces(char const* str)
{ 
  unsigned int new_len = str_count_non_spaces(str);
  char* new_string = (char*)malloc(new_len + 1);
  
  if (NULL == new_string)         // выделение пам€ти не удалось
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

// копирует символы в строках strFrom -> strTo, в количестве number
void str_copy_fix_len(char const* strFrom, char* strTo, unsigned int number)
{ 
  while (number--)
    *(strTo++) = *(strFrom++);
}

char LowerChar(char c) { // возвращает 1 символ [AЦZ] -> [aЦz], или не мен€ет
  if (c >= 'A' && c <= 'Z') c += 32;
  return c;
}

char UpperChar(char c) { // возвращает 1 символ [aЦz] -> [AЦZ], или не мен€ет
  if (c >= 'a' && c <= 'z') c -= 32;
  return c;
}

void LowerCase(char str[]) { // замен€ет символы строки [AЦZ] -> на аналоги из [aЦz]
  for (int pos = 0; str[pos]; pos++)
    str[pos] = LowerChar(str[pos]);
}

void UpperCase(char str[]) { // замен€ет символы строки [aЦz] -> [AЦZ]
  for (int pos = 0; str[pos]; pos++)
    str[pos] = UpperChar(str[pos]);
}

// находит вхождение в строку символа X, или конец строки '\0'
char* str_find_char(char const* str, char x, int start) 
{
  str += start;     // от начала строки
  while (*str)
    if (x == (*str)) return (char*)str;  // вернЄт адрес первого найденного ’
    else str++;
  return (char*)str;  // тут вернЄт адрес концы строки '\0'
}
