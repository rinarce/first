// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

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
    while (*str++) ++len;
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
    ++str;   // пропустить все незначащие символы

  // проверяем что оба символа - это не конец строки и равны '//'
  return (*str && *str == '/' && *(str + 1) && *(str + 1) == '/');
}

// 1 - если в строке нарушена парность скобок (()
int is_bracket_error(char* str)
{
  int nest = 0;                       // счётчик открытых скобок
  while (*str)
  {
    if (*str == '(')        ++nest;   // открывающая скобка
    else if (*str == ')')   --nest;   // закрывающая скобка

    if (nest < 0)  
      return 1;                       // закрывающая раньше открывающей
    ++str;
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
      ++count;
  return count;
}

// подсчёт непробелов
unsigned int str_count_non_spaces(char const* str)
{
  unsigned count = 0;
  while (*str)
    if (!isspace((int)(*str++)))
      ++count;
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
      ++old_str_ptr;              // пробел - пропускаем

  *new_str_ptr = '\0';            //  конец строки
  return new_string;
}


// копирует символы в строках strFrom -> strTo, в количестве number
void str_copy_fix_len(char const* strFrom, char* strTo, unsigned int number)
{ 
  while (number--)
    *(strTo++) = *(strFrom++);
}


// возвращает 1 символ [A–Z] -> [a–z], или не меняет
char LowerChar(char c) { 
  if (c >= 'A' && c <= 'Z') c += 32;
  return c;
}

// возвращает 1 символ [a–z] -> [A–Z], или не меняет
char UpperChar(char c) { 
  if (c >= 'a' && c <= 'z') c -= 32;
  return c;
}

// заменяет символы строки [A–Z] -> на аналоги из [a–z]
void LowerCase(char str[]) { 
  for (int pos = 0; str[pos]; ++pos)
    str[pos] = LowerChar(str[pos]);
}

// заменяет символы строки [a–z] -> [A–Z]
void UpperCase(char str[]) { 
  for (int pos = 0; str[pos]; ++pos)
    str[pos] = UpperChar(str[pos]);
}


// находит вхождение в строку символа X, или конец строки '\0'
char* str_find_char(char const* str, char x, int start) 
{
  str += start;                          // смещение от начала строки
  while (*str)
    if (x == (*str)) return (char*)str;  // вернёт адрес первого найденного Х
    else ++str;
  return (char*)str;                     // тут вернёт адрес концы строки '\0'
}


// кусок str[start...end] -> записывает в начало subStr
// конец строки  '\0' никак не проверяется и в subStr не дополняется
void str_copy_substr(char str[], int start, int end, char subStr[]) 
{
  for (int pos = 0; start <= end; subStr[pos++] = str[start++]) {};
}

// из куска str[start...end] создаётся новая строка
char * str_make_substr(char str[], int start, int end)
{
  char*     new_str = (char*)malloc(end - start + 1);
  char* new_str_ptr = new_str;
  if (NULL != new_str)
    while (start <= end)
      *(new_str_ptr++) = str[start++];
  
  *new_str_ptr = '\0';   // конец строки
  return new_str;
}


// из str вырезается кусок [start...end], остаток строки сдвигается <--
void str_remove_substr(char str[], int start, int end) 
{
  int p1 = start, p2 = end + 1;
  do 
  {    str[p1] = str[p2++];    }		// копировать, пока на скопируем символ '\0'
  while (str[p1++]);
}


// заменяет в строке str : word -на-> replace 
// (!!! заменяется не больше сиимволов чем длина word !)
// т.е. строка str - может только сокращаться (простой сдвиг конца строки)
// но не удлиняться. Возврат - количество замен
int str_replace_all(char str[], char word[], char replace[]) 
{
  int replaced = 0,                     // количество произведённых замен
      word_len = str_lenght(word), 
   replace_len = str_lenght(replace);
  
  // образаем по длине исходного слова
  if (replace_len > word_len) replace_len = word_len; 
  int delta = word_len - replace_len;	 // разница в длине (уже обрезаного replace)
  

  int pos = 0;
  while(str[pos])
  {
    if (str_compare_fix_len(&str[pos], word, word_len))
    {
      str_copy_substr(replace, 0, replace_len - 1, &str[pos]);
      ++replaced;
      if (delta)         // слова разной длины, необходима подрезка строки
        str_remove_substr(str, pos + replace_len, pos + replace_len + delta - 1);
      pos += replace_len;
    }
    else ++pos;
  }
  return replaced;
}


// копирует строку до '\0' включая, возвращает указатель на strTo
char* str_copy_str(char strFrom[], char strTo[]) 
{
  int pos = 0;
  do 
  {   strTo[pos] = strFrom[pos];    }
  while (strTo[pos++]);

  return strTo; // для удобства
}


// 1 - если в str двоичное число (тогда его возвращает в result)
// разделитель целой и дробной части - русский - ','
// Advanced feature - в двоичных вместо 0 можно писать любой символ !
int is_binary_digit(char* str, double* result)
{
  unsigned int str_len = str_lenght(str);
  if (str_len < 2)
    return 0;

  if (*str == '0' && (*(str + 1) == 'b' || *(str + 1) == 'B'))
  {
    // начинается на 0b или 0B - считаем это двоичным числом
    double multiply = 2.;
    double x = 0;
    str += 2; // пропустить первые два символа
    while (*str && *str != ',') // до конца строки или десятичной запятой
    {
      x *= 2;
      x += (*str == '1');    // вместо нуля может быть любой символ !!! это фича
      str++;
    }
    if(*str++ == ',') // есть дробная часть
    {
      multiply = 0.5;
      while (*str) // до конца строки
      { 
        // вместо нуля может быть любой символ !!! это фича
        x += (*str == '1') ? multiply : 0;
        multiply /= 2;
        ++str;
      }
    }
    *result = x;
    return 1;
  }
  
  return 0;
}