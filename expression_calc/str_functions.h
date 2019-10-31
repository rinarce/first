#ifndef STR_FUNCTIONS_H_INCLUDED__
#define CSTR_FUNCTIONS_H_INCLUDED__
#pragma once

#include <stdlib.h>

// длина строки до '\0'
unsigned int StrLenght(char const* str);

// 1 - если в строке только всевозможные пробелы ( \t\n\v\f\r)
int IsOnlySpaces(char const* str);

// 1 - если в строке первые значащие символы //
int IsComment(char const* str);

// 1 - если в строке нарушена парность скобок (()
int IsBracketError(char const* str);

// сравнивает строки на длину distance, возврат 1 если равны, 0 иначе
int StrCompareFixLen(char const* str1, char const* str2, unsigned int distance);

// сравнивает строки, возврат 1 если равны, 0 иначе
int StrCompare(char const* str1, char const* str2);

// копирует символы в строках strFrom -> strTo, в количестве number
void StrCopyFixLen(char const* strFrom, char* strTo, unsigned int number);

// подсчёт пробелов
unsigned int StrCountSpaces(char const* str);

// подсчёт непробелов
unsigned int StrCountNonSpaces(char const* str);

// из str удаляет все пробелы -> в новую созданную строку
char* StrRemoveSpaces(char const* str);

// заменяет в строке str : word -на-> replace 
// (!!! заменяется не больше сиимволов чем длина word !)
// т.е. строка str - может только сокращаться (простой сдвиг конца строки)
// но не удлиняться. Возврат - количество замен
int StrReplaceAll(char str[], char const word[], char const replace[]);

// копирует строку до '\0' включая, возвращает указатель на strTo
char* StrCopyStr(char const strFrom[], char strTo[]);

// 1 - если в str двоичное число (тогда его возвращает в result)
// разделитель целой и дробной части - русский - ','
int IsBinaryDigit(char const* str, double* result);

// из куска str[start...end] создаётся новая строка
char* StrMakeSubstr(char const str[], int start, int end);

#endif STR_FUNCTIONS_H_INCLUDED__