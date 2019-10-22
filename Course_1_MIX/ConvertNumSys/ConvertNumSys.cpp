// BaseConverter.cpp -  Numeral System Converter
// переводит длинные числа из одной Системы Счисления в другую СС

// идея обратной записи и функции деления и % - но тут намного проще
// http://cppalgo.blogspot.com/2010/05/blog-post.html 


//#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)   // for use scanf in VisualStudio

#include <stdio.h>
#define MAX_LEN 10001
#include "Functions.h"


int main()
{
  int NS_From, NS_To;           // СС из какой и в какую перевод
  scanf("%d %d", &NS_From, &NS_To);

  char a_input[MAX_LEN] = { 0 };
  scanf("%s", &a_input);        // исходное очень длинное число
  int a_len = StrLenght(a_input);
  if (a_len == 0)               // во второй строчке ничего нет
    return 0;

  // будем хранить в массиве числа (не символы) от младших разрядов к старшим
  convertToBig(a_input, a_len);

  // здесь накапливаем цифры результата (тоже в обратном порядке)
  // максимальная СС 36, минимальная 2 => 36 влезает в 6 двоичных цифр с запасом
  char result[6 * MAX_LEN] = { 0 };
  int result_len = 0;

  do
  {     // последовательно делим на новое основание СС, запоминаем остатки
        // ответ - остатки от деления в обратном порядке
    result[result_len++] = BigDivide(a_input, a_len, NS_From, NS_To);

    // при деление число уменьшается, образуются ведущие нули
    // избавляемся от них (кроме последнего)
    while (a_len > 1 && a_input[a_len - 1] == 0)
      a_len--;

  } while (isBigNum_lessThan(a_input, a_len, NS_From, NS_To));
  // если == 0  -- всё, число закончилось

  printBig(result, result_len); printf("\n");
  return 0;
}
