// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <stdlib.h>
#include <ctype.h>  // isspace()
#include "str_functions.h"

// длина строки до '\0'
unsigned int StrLenght(char const* str) {
  int len = 0;
  if (NULL != str)          // проверка, что указатель корректен
    while (*str++) ++len;
  return len;
}

// 1 - если в строке только всевозможные пробелы ( \t\n\v\f\r)
int IsOnlySpaces(char const* str) {
  while (*str)
    if (!isspace((int)(*str++)))  
      return 0;             // найден не пробел
  return 1;
}

// 1 - если в строке первые значащие символы //
int IsComment(char const* str) {
  while (*str && isspace((int)(*str)))
    ++str;                  // пропустить все незначащие символы

  // проверяем что оба символа - это не конец строки и равны '//'
  return (*str && *str == '/' && *(str + 1) && *(str + 1) == '/');
}

// 1 - если в строке нарушена парность скобок (()
int IsBracketError(char const* str) {
  int nest = 0;             // счётчик открытых скобок
  while (*str) {
    if (*str == '(')        
      ++nest;               // открывающая скобка
    else if (*str == ')')   
      --nest;               // закрывающая скобка
    if (nest < 0)         
      return 1;             // закрывающая раньше открывающей
    ++str;
  }
  return nest;              // если >0 - остались незакрытые скобки
}


// сравнивает строки на длину distance, возврат 1 если равны, 0 иначе
int StrCompareFixLen(char const* str1, char const* str2, unsigned int distance) {
  if (NULL == str1 || NULL == str2) 
    return 0;               // ошибочные указатели
  while (distance--) {
    if (*(str1) != *(str2))  
      return 0;             // до первого несовпадения
    else {  
      ++str1;  
      ++str2;  
    }
  }
  return 1;
}

// сравнивает строки, возврат 1 если равны, 0 иначе
int StrCompare(char const* str1, char const* str2) {
  if (NULL == str1 || NULL == str2) 
    return 0;               // ошибочные указатели
  do { 
    if (*(str1++) != *(str2++))   
      return 0;             // до первого несовпадения
  } while (*str1);          // до конца строки str1
  
  if (*str2 == '\0')  
    return 1;               // вторая строка тоже закончилась
  else                
    return 0;
}

// подсчёт пробелов
unsigned int StrCountSpaces(char const* str) { 
  unsigned count = 0;
  while (*str)
    if (isspace((int)(*str++)))
      ++count;
  return count;
}

// подсчёт непробелов
unsigned int StrCountNonSpaces(char const* str) {
  unsigned count = 0;
  while (*str)
    if (!isspace((int)(*str++)))
      ++count;
  return count;
}

// из str удаляет все пробелы -> в новую созданную строку
char* StrRemoveSpaces(char const* str) { 
  unsigned int newLen = StrCountNonSpaces(str);
  char* newString = (char*)malloc(newLen + 1);
  
  if (NULL == newString)
    return NULL;

  char* newStrPtr = newString;
  char const* oldStrPtr = str;
  
  while (*oldStrPtr)            // пока не конец строки
    if (!isspace(*oldStrPtr))   // копируем не пробел
      *(newStrPtr++) = *(oldStrPtr++);
    else
      ++oldStrPtr;              // пробел - пропускаем

  *newStrPtr = '\0';            //  конец строки
  return newString;
}


// копирует символы в строках strFrom -> strTo, в количестве number
void StrCopyFixLen(char const* strFrom, char* strTo, unsigned int number) { 
  while (number--)
    *(strTo++) = *(strFrom++);
}


// кусок str[start...end] -> записывает в начало subStr
// конец строки  '\0' никак не проверяется и в subStr не дополняется
void _strCopySubstr(char const str[], int start, int end, char subStr[]) {
  for (int pos = 0; start <= end; subStr[pos++] = str[start++]) {
  };
}

// из куска str[start...end] создаётся новая строка
char * StrMakeSubstr(char const str[], int start, int end) {
  char* newStr = (char*)malloc(end - start + 1);
  char* newStrPtr = newStr;
  if (NULL != newStr) {
    while (start <= end)
      *(newStrPtr++) = str[start++];
    *newStrPtr = '\0';                // конец строки
  }
  return newStr;
}

// из str вырезается кусок [start...end], остаток строки сдвигается <--
void _strRemoveSubstr(char str[], int start, int end) {
  int p1 = start, p2 = end + 1;
  do { 
    str[p1] = str[p2++]; 
  } while (str[p1++]);                // копировать, пока на скопируем символ '\0'
}


// заменяет в строке str : word -на-> replace 
// (!!! заменяется не больше сиимволов чем длина word !)
// т.е. строка str - может только сокращаться (простой сдвиг конца строки)
// но не удлиняться. Возврат - количество замен
int StrReplaceAll(char str[], char const word[], char const replace[]) {
  int replaced = 0,                   // количество произведённых замен
       wordLen = StrLenght(word), 
    replaceLen = StrLenght(replace);
  
  if (replaceLen > wordLen)           // образаем по длине исходного слова
    replaceLen = wordLen; 
  int delta = wordLen - replaceLen;	  // разница в длине (уже обрезаного replace)
  
  int pos = 0;
  while(str[pos]) {
    if (StrCompareFixLen(&str[pos], word, wordLen)) {
      _strCopySubstr(replace, 0, replaceLen - 1, &str[pos]);
      ++replaced;
      if (delta)                      // слова разной длины, необходим сдвиг
        _strRemoveSubstr(str, pos + replaceLen, pos + replaceLen + delta - 1);
      pos += replaceLen;
    }
    else 
      ++pos;
  }
  return replaced;
}


// копирует строку до '\0' включая, возвращает указатель на strTo
char* StrCopyStr(char const strFrom[], char strTo[]) {
  int pos = 0;
  do {   
    strTo[pos] = strFrom[pos];    
  } while (strTo[pos++]);
  return strTo;
}


// 1 - если в str двоичное число (тогда его возвращает в result)
// разделитель целой и дробной части - русский - ','
// Advanced feature - в двоичных вместо 0 можно писать любой символ !
int IsBinaryDigit(char const* str, double* result) {
  if (StrLenght(str) < 2)  
    return 0;

  if (*str == '0' && (*(str + 1) == 'b' || *(str + 1) == 'B')) {
    // начинается на 0b или 0B - считаем это двоичным числом
    double multiply = 2.;
    double x = 0;
    str += 2;                    // пропустить первые два символа
    while (*str && *str != ',') {// до конца строки или десятичной запятой
      x *= 2;
      x += (*str == '1');        // вместо нуля может быть любой символ !!! это фича
      str++;
    }
    if (*str++ == ',') {         // есть дробная часть
      multiply = 0.5;
      while (*str) {            // до конца строки
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