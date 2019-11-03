// BaseConverter.cpp -  Numeral System Converter
// переводит длинные числа из одной Системы Счисления в другую СС

// идея обратной записи и функции деления и % - но тут намного проще
// http://cppalgo.blogspot.com/2010/05/blog-post.html 


#pragma warning(disable:4996)   // for use scanf in VisualStudio

#include <stdio.h>
#define MAX_LEN 10001

#include <stdio.h>


// длина строки до '\0'
int StrLenght(char const * str) {  
    int len = 0;
    if (NULL != str)          // проверка, что указатель корректен
      while (*str++) ++len;
    return len;
  }


// превращает символ char '0'-'9A'-'Z'  ->  в число char 0-35
char convert_36_10(char const sym) {  
  static char convertTable[] =  // static - не создавать каждый раз
  { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,    // 0-15
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,    // 16-31
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,    // 32-47
     0, 1, 2, 3, 4, 5, 6, 7, 8, 9,-1,-1,-1,-1,-1,-1,    // 48-63  тут цифры 
    -1,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,    // 64-79  A-Z
    25,26,27,28,29,30,31,32,33,34,35,-1,-1,-1,-1,-1,    // 80-95
    -1,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,    // 96-111 a-z
    25,26,27,28,29,30,31,32,33,34,35,-1,-1,-1,-1,-1     // 112-127
  }; // -1 признак ошибочного ввода, пока никак не обрабатывается ;-)
  return convertTable[sym]; // только 0-127
}


// в массиве array длинное число записанное символами 0..9A..Z
// преобразуем символы в числа 0--35 и перевернём порядок цифр 
// от младших разрядов к старшим
void convertToBig(char array[], int len) {   
  int start = 0;
  int end = len - 1;
  while (start <= end) {   // идём с обоих краёв массива до середины
                           // середину тоже меняем, для конвертации
    char temp = convert_36_10(array[start]);
    array[start++] = convert_36_10(array[end]);
    array[end--] = temp;
  }
}

// в массиве array длинное число от младших разрядов к старшим
// преобразуем цифры 0--35 в символы 0..9A..Z и перевернём порядок цифр 
void printBig(char array[], int len) {
  char digits36[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int digitIndex = len - 1;  // старшие разряды в конце 

  while (digitIndex > 0 && array[digitIndex] == 0)
    --digitIndex;                     // избавимся от ведущих нулей, кроме последнего (если == 0)

  for (; digitIndex >= 0; --digitIndex)             // печатаем число
    printf("%c", digits36[array[digitIndex]]);
}

// если длинное число в массиве меньше X => то возвращает его значение [0...X)
// иначе -1
int isBigNum_lessThan(char array[], int len, int NS, int x) { 
  int bigValue = 0;
  for (int digitIndex = len - 1; digitIndex >= 0; --digitIndex) {     // формула Горнера
    bigValue = bigValue * NS + array[digitIndex];
    if (bigValue >= x) return -1;
  }
  return bigValue;
}


// в массиве A длинное число в СС NS (первые a_len элементов в обратном порядке)
// делим его на divisor результат будет там же (возможно появление 0..0 в старших)
// возвращает остаток от деления
int BigDivide(char a[], int a_len, int NS, int divisor) { 
  int rest = 0;
  for (int digitIndex = a_len - 1; digitIndex >= 0; --digitIndex) { // школьное деление, от старших разрядов
    int cur = rest * NS + a[digitIndex];
    a[digitIndex] = cur / divisor;
    rest = cur % divisor;
  }
  return rest;
}



int main() {
  int NS_From, NS_To;             // СС из какой и в какую перевод
  scanf("%d %d", &NS_From, &NS_To);

  char a_input[MAX_LEN] = { 0 };  // исходное очень длинное число
  scanf("%s", &a_input);        
  int a_len = StrLenght(a_input);
  if (a_len == 0)                 // во второй строчке ничего нет
    return 0;

  // будем хранить в массиве числа (не символы) от младших разрядов к старшим
  convertToBig(a_input, a_len);

  // здесь накапливаем цифры результата (тоже в обратном порядке)
  // максимальная СС 36, минимальная 2 => 36 влезает в 6 двоичных цифр с запасом
  char result[6 * MAX_LEN] = { 0 };
  int result_len = 0;

  do  { // последовательно делим на новое основание СС, запоминаем остатки
        // ответ - остатки от деления в обратном порядке
    result[result_len++] = BigDivide(a_input, a_len, NS_From, NS_To);

    // при деление число уменьшается, образуются ведущие нули
    // избавляемся от них (кроме последнего)
    while (a_len > 1 && a_input[a_len - 1] == 0)
      --a_len;

  } while (isBigNum_lessThan(a_input, a_len, NS_From, NS_To));
  // если == 0  -- всё, число закончилось

  printBig(result, result_len); printf("\n");
  return 0;
}
