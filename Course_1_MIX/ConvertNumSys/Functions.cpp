#include <stdio.h>

int StrLenght(char str[]) {  // длина строки до '\0'
    int len = 0;
    while (str[len]) len++;
    return len;
}

char convert_36_10(char sym)
{   // превращает символ char '0'-'9A'-'Z'  ->  в число char 0-35
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

void convertToBig(char array[], int len)
{   // в массиве array длинное число записанное символами 0..9A..Z
    // преобразуем символы в числа 0--35 и перевернём порядок цифр 
    // от младших разрядов к старшим
    int start = 0;
    int end = len - 1;
    while (start <= end)    // идём с обоих краёв массива до середины
    {                       // середину тоже меняем, для конвертации
      char temp = convert_36_10(array[start]);
      array[start++] = convert_36_10(array[end]);
      array[end--] = temp;
    }
}

void printBig(char array[], int len)
{   // в массиве array длинное число от младших разрядов к старшим
    // преобразуем цифры 0--35 в символы 0..9A..Z и перевернём порядок цифр 
    char digits36[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int pos = len - 1;

    while (pos > 0 && !array[pos]) 
      pos--; // избавимся от ведущих нулей, кроме последнего (если == 0)
    
    for (; pos >= 0; pos--) // печатаем число
      printf("%c", digits36[array[pos]]);
}


int isBigNum_lessThan(char array[], int len, int NS, int x)
{ // если длинное число в массиве меньше X => то возвращает его значение [0...X)
  // иначе -1
    int bigValue = 0;
    for (int i = len - 1; i >= 0; i--)      // формула Горнера
    {
        bigValue = bigValue * NS + array[i];
        if (bigValue >= x) return -1;
    }
    return bigValue;  
}


int BigDivide(char a[], int a_len, int NS, int divisor) 
{ // в массиве A длинное число в СС NS (первые a_len элементов в обратном порядке)
  // делим его на divisor результат будет там же (возможно появление 0..0 в старших)
  // возвращает остаток от деления
    int rest = 0;
    for (int i = a_len - 1; i >= 0; i--) // школьное деление, от старших разрядов
    {
        int cur = rest * NS + a[i];
        a[i] = cur / divisor;
        rest = cur % divisor;
    }
    return rest;
}
