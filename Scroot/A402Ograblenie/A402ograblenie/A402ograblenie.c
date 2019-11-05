// A402ograblenie.c

#include <stdio.h>

#define MAX_LINE_LEN    1000  // 1 кБайт на строку 
#define MAX_LINES_COUNT 1000  // 1000 строк * 2 (исход + кодиров) = 2Мбайт

typedef struct codedLine {
  int len;
  char origin [MAX_LINE_LEN];     // исходная строка со *
  char coded  [MAX_LINE_LEN];     // закодированная (переведена из шестнадцателричного вида)
} codedLine;


// длина строки до '\0'
unsigned int _strLenght(char const* str) {
  int lenght = 0;
  if (NULL != str)
    while (*str++)
      lenght++;
  return lenght;
}



// return 1 = лат буквы + пробел
int _charIsLetterOrSpace(char c) {
  if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ')
    return 1;
  return 0;
}

// return 1 = знаки препинания ".,!?;:-()"  0 = всё остальное
int _charIsSeparator(char c) {
  if (c == '.' || c == ',' || c == '!' || c == '?' || c == ';'
               || c == ':' || c == '-' || c == '(' || c == ')')
    return 1;
  return 0;
}


// получает указатель на строку - 2 первых символа шестначатеричные символы
// возврат - char байт из этих символов
char _convert2HexInChar(char const* hex) {
  int digit1 = -1, 
      digit2 = -1;
  char t;

  if (NULL == hex) 
    return 0;       // не передан нормальный указатель
  if ('\0' == *hex || '\0' == *(hex + 1))
    return 0;       // в строке нет 2х символов, найден конец строки
  
  // 1й символ
  t = *hex;
  if ('0' <= t && t <= '9')   digit1 = (int)(t - '0');
  if ('A' <= t && t <= 'F')   digit1 = (int)(t - 'A' + 10);
  if ('a' <= t && t <= 'f')   digit1 = (int)(t - 'a' + 10);

  // 2й символ
  t = *(hex + 1);
  if ('0' <= t && t <= '9')   digit2 = (int)(t - '0');
  if ('A' <= t && t <= 'F')   digit2 = (int)(t - 'A' + 10);
  if ('a' <= t && t <= 'f')   digit2 = (int)(t - 'a' + 10);

  if (-1 == digit1 || -1 == digit2)
    return 0; // неподходящие символы - не удалось перекодировать

  return (char)(digit1*16 + digit2); // OK
}



int main()
{
  static codedLine text[MAX_LINES_COUNT] = { 0 };   // тут хранятся строки
  static char key[MAX_LINE_LEN] = { 0 };            // ключ
  int nLines = 0;                                   // число строк



  return 0;
}

