#pragma once

#include <stdlib.h>

// выделяет место для строки размером (size + 1)
char* AllocateString(unsigned int size);

// длина строки до '\0'
unsigned int str_lenght(char const* str);

// 1 - если в строке только всевозможные пробелы ( \t\n\v\f\r)
int is_only_spaces(char* str);

// 1 - если в строке первые значащие символы //
int is_comment(char* str);

// 1 - если в строке нарушена парность скобок (()
int is_bracket_error(char* str);

// сравнивает строки на длину distance, возврат 1 если равны, 0 иначе
int str_compare_fix_len(char const* str1, char const* str2, unsigned int distance);

// копирует символы в строках strFrom -> strTo, в количестве number
void str_copy_fix_len(char const* strFrom, char* strTo, unsigned int number);

// подсчЄт пробелов
unsigned int str_count_spaces(char const* str);

// подсчЄт непробелов
unsigned int str_count_non_spaces(char const* str);

// из str удаляет все пробелы -> в новую созданную строку
char* str_remove_spaces(char const* str);

// возвращает 1 символ [AЦZ] -> [aЦz], или не меняет
char LowerChar(char c);

// возвращает 1 символ [aЦz] -> [AЦZ], или не меняет
char UpperChar(char c);

// заменяет символы строки [AЦZ] -> на аналоги из [aЦz]
void LowerCase(char str[]);

// заменяет символы строки [aЦz] -> [AЦZ]
void UpperCase(char str[]); 

// находит вхождение в строку символа X, или конец строки '\0'
char* str_find_char(char const* str, char x, int start);

// заменяет в строке str : word -на-> replace 
// (!!! заменяется не больше сиимволов чем длина word !)
// т.е. строка str - может только сокращаться (простой сдвиг конца строки)
// но не удлиняться. Возврат - количество замен
int str_replace_all(char str[], char word[], char replace[]);

// копирует строку до '\0' включая, возвращает указатель на strTo
char* str_copy_str(char strFrom[], char strTo[]);

// 1 - если в str двоичное число (тогда его возвращает в result)
// разделитель целой и дробной части - русский - ','
int is_binary_digit(char* str, double* result);

