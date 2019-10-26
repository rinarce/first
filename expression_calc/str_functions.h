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

// подсчёт пробелов
unsigned int str_count_spaces(char* str);

// подсчёт непробелов
unsigned int str_count_non_spaces(char* str);

// из str удаляет все пробелы -> в новую созданную строку
char* str_remove_spaces(char const* str);


