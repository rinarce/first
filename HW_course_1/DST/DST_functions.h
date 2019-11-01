#ifndef DST_FUNCTIONS_H_INCLUDED__
#define DST_FUNCTIONS_H_INCLUDED__
#pragma once

// вводит строку произвольной длины, самостоятельно выделяет память
// в *str возвращает указатель на строку, return возвращает длину строки
unsigned int DstInputStr(char** str, char const* text);

// новая строка, слова из str разделены новым разделителем
char* ExtractWords(char const* str, char const* newSeparator);

// новая строка, УНИКАЛЬНЫЕ СЛОВА из str разделены новым разделителем
char* ExtractUniqueWords(char const* str, char const* newSeparator);

// новая строка, буквы из str разделены новым разделителем
char* ExtractLetters(char const* str, char const* newSeparator);

// новая строка, УНИКАЛЬНЫЕ БУКВЫ из str разделены новым разделителем
char* ExtractUniqueLetters(char const* str, char const* newSeparator);

// из str выдаёт только буквы в новую созданную строку
char* StrGetOnlyLetters(char const* str);

// новая строка, из str удалены разделители и найдены 
// все подстроки длиннее 1, которые есть в зеркальном виде,
// они разделены новым разделителем
char* FindMirrors(char const* str, char const* newSeparator);

// новая строка, все подстроки из str по маске поиска, разделены новым разделителем
char* FindMaskWords(char const* str, char const* mask, char const* newSeparator);

// новая строка, транслитерация русских символов, 
// по правилам - ПРИКАЗ МИД РФ от 29 марта 2016 г. N 4271
char* ConvertRussian(char const* str);

// новая строка, задание Поиск цепочек - склеивает слова
// если 2 слова совпадают конец одного и начало другого
char* FindChains(char const* str, char const* newSeparator);

// расширяет строку str, добавляя к ней + separator + appendStr
// separator добавляется только если str не пустая
// возвращает длину добавленного
int StrJointSeparStr(char** str, char const* separator, char const* appendStr);

// возврат - новая строка, где str разбита на строки шириной width
// несколько пробелов подряд заменяются на один пробел, выравнование - влево
// между строками - \n, если слово > width, оно разбивается на куски
char* StrJustifyLeft(char* str, unsigned width);

// возврат - новая строка, где str разбита на строки шириной width
// выравнивание- по ширине, изменяя количество пробелов
// между строками - \n, если слово > width, оно разбивается на куски
char* StrJustifyWidth(char* str, unsigned width);

#endif DST_FUNCTIONS_H_INCLUDED__