// DST.c
#include <stdio.h>
#include <locale.h>
#include <windows.h>          // для ввода кирилицы
#include <stdlib.h>           // для выделения памяти

#include "DST_functions.h"
#define DST_SEPARATOR ", "

int main() {
  setlocale(LC_ALL, "Russian");
  SetConsoleCP(1251);         // для ввода русских букв
  SetConsoleOutputCP(1251);
  
  char* str;                  // очередная введённая строка
  char* mask;                 // маска для DST–6-7
  char* result;               // новая строка - результат выполнения каждого задания
  char* paragraph = NULL;     // накапливаю все строки str, \n заменён на пробел
  unsigned int strLen;

  while (strLen = DstInputStr(&str, "Введите строку :")) // пока не введена пустая строка
  {
    DstInputStr(&mask, " Введите маску :");

    printf("\nDST–0               (Введено) : %s\n", str);

    result = ExtractWords(str, DST_SEPARATOR);
    printf("DST–1            (Выбор слов) : %s\n", result);
    free(result);

    result = ExtractUniqueWords(str, DST_SEPARATOR);
    printf("DST–2      (Уникальные слова) : %s\n", result);
    free(result);

    result = ExtractLetters(str, DST_SEPARATOR);
    printf("DST–3            (Выбор букв) : %s\n", result);
    free(result);

    result = ExtractUniqueLetters(str, DST_SEPARATOR);
    printf("DST–4      (Уникальные буквы) : %s\n", result);
    free(result);

    result = StrGetOnlyLetters(str);
    printf("DST–50         (Только буквы) : %s\n", result);
    free(result);

    //result = FindMirrors(str, DST_SEPARATOR);
    //printf("DST–51 (Зеркальные подстроки) : %s\n", result);
    //free(result);

    result = FindMaskWords(str, mask, DST_SEPARATOR);
    printf("DST–6-7      (Поиск по маске) : %s\n", result);
    free(result);

    //result = FindChains(str, DST_SEPARATOR);
    //printf("DST–8         (Поиск цепочек) : %s\n", result);
    //free(result);

    result = ConvertRussian(str);
    printf("DST–10       (Транслитерация) : %s\n", result);
    free(result);

    // накапливаем строки в одной строке paragraph, разделены пробелом
    StrJointSeparStr(&paragraph, " ", str);

    free(str);
    free(mask);
    printf("\n");
  }

  return 0;  // пока не запускать 11 и 12  
  { // Задания на выравнивание параграфа
    int width = 0;
    printf("\nDST-11/12       Ширина абзаца : ");
    scanf_s("%u", &width);

    result = StrJustifyLeft(paragraph, width);
    printf("DST–11   (Выравнивание влево) :\n%s\n\n", result);
    free(result);

    result = StrJustifyWidth(paragraph, width);
    printf("DST–12            (По ширине) :\n%s\n\n", result);
    free(result);

    free(paragraph);
  }
  return 0;
}
