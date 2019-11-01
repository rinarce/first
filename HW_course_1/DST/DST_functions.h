#ifndef DST_FUNCTIONS_H_INCLUDED__
#define DST_FUNCTIONS_H_INCLUDED__
#pragma once


char* AllocateString(unsigned int size);
// выделяет место для строки размером (size + 1)

unsigned int DST_InputStr(char** str, char const* text);
// вводит строку произвольной длины, самостоятельно выделяет память
// в *str возвращает указатель на строку, return возвращает длину строки

char* ExtractWords(char const* str, char const* newSeparator);
// новая строка, слова из str разделены новым разделителем

char* ExtractUniqueWords(char const* str, char const* newSeparator);
// новая строка, УНИКАЛЬНЫЕ СЛОВА из str разделены новым разделителем

char* ExtractLetters(char const* str, char const* newSeparator);
// новая строка, буквы из str разделены новым разделителем

char* ExtractUniqueLetters(char const* str, char const* newSeparator);
// новая строка, УНИКАЛЬНЫЕ БУКВЫ из str разделены новым разделителем

char* STR_GetOnlyLetters(char const* str);
// из str выдаёт только буквы в новую созданную строку

char* FindMirrors(char const* str, char const* newSeparator);
// новая строка, из str удалены разделители и найдены 
// все подстроки длиннее 1, которые есть в зеркальном виде,
// они разделены новым разделителем

char* FindMaskWords(char const* str, char const* mask, char const* newSeparator);
// новая строка, все подстроки из str по маске поиска, разделены новым разделителем

char* ConvertRussian(char const* str);
// новая строка, транслитерация русских символов, 
// по правилам - ПРИКАЗ МИД РФ от 29 марта 2016 г. N 4271

char* FindChains(char const* str, char const* newSeparator);
// новая строка, задание Поиск цепочек - склеивает слова
// если 2 слова совпадают конец одного и начало другого

int STR_Joint_Separ_Str(char** str, char const* separator, char const* appendStr);
// расширяет строку str, добавляя к ней + separator + appendStr
// separator добавляется только если str не пустая
// возвращает длину добавленного

char* STR_JustifyLeft(char* str, unsigned width);
// возврат - новая строка, где str разбита на строки шириной width
// несколько пробелов подряд заменяются на один пробел, выравнование - влево
// между строками - \n, если слово > width, оно разбивается на куски

char* STR_JustifyWidth(char* str, unsigned width);
// возврат - новая строка, где str разбита на строки шириной width
// выравнивание- по ширине, изменяя количество пробелов
// между строками - \n, если слово > width, оно разбивается на куски

#endif DST_FUNCTIONS_H_INCLUDED__