// A402ograblenie.c

#include <stdio.h>

#pragma warning(disable:4996)   // for use scanf in VisualStudio

#define MAX_LINE_LEN    1000    // 1 кБайт на строку 
#define MAX_LINES_COUNT 1000    // 1000 строк * 2 (исход + кодиров) = 2Мбайт
#define KEY_LEN         100     // Длина ключа


typedef struct codedLine {
  int len;
  char origin [MAX_LINE_LEN];   // исходная строка со *
  char coded  [MAX_LINE_LEN];   // закодированная (переведена из шестнадцателричного вида)
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
  /* // без проверок
  if (NULL == hex) 
    return 0;       // не передан нормальный указатель
  if ('\0' == *hex || '\0' == *(hex + 1))
    return 0;       // в строке нет 2х символов, найден конец строки
  */

  // 1й символ
  t = *hex;
  if      ('0' <= t && t <= '9')   digit1 = (int)(t - '0');
  else if ('A' <= t && t <= 'F')   digit1 = (int)(t - 'A' + 10);
  else if ('a' <= t && t <= 'f')   digit1 = (int)(t - 'a' + 10);

  // 2й символ
  t = *(hex + 1);
  if      ('0' <= t && t <= '9')   digit2 = (int)(t - '0');
  else if ('A' <= t && t <= 'F')   digit2 = (int)(t - 'A' + 10);
  else if ('a' <= t && t <= 'f')   digit2 = (int)(t - 'a' + 10);

  //if (-1 == digit1 || -1 == digit2)
  //  return 0; // неподходящие символы - не удалось перекодировать

  return (char)(digit1*16 + digit2); // OK
}



int main()
{
  static codedLine text[MAX_LINES_COUNT] = { 0 };   // тут хранятся строки
  static char key[MAX_LINE_LEN] = { 0 };            // ключ
  static char buffer[MAX_LINE_LEN * 2] = { 0 };
  int nLines = 0;                                   // число строк
  int lineIndex, buffIndex, symIndex, len, keyIndex;
  int keyLen = KEY_LEN;

  scanf("%d", &nLines);

  // ввод оригиналов строк с затёртыми смиволами
  for (lineIndex = 0; lineIndex < nLines; ++lineIndex) {
    scanf("%s", &text[lineIndex].origin);
    // запомню длину строк
    text[lineIndex].len = _strLenght(text[lineIndex].origin);
  }

  // ввод строк с кодом
  for (lineIndex = 0; lineIndex < nLines; ++lineIndex) {
    scanf("%s", &buffer);
    // каждые 2 символа кода 16ричного вида -> 1 символ байт
    for (buffIndex = 0; buffer[buffIndex] != '\0'; ++buffIndex)
      text[lineIndex].coded[buffIndex / 2] = _convert2HexInChar(&buffer[buffIndex]);

    text[lineIndex].coded[buffIndex / 2] = '\0'; // конец строки
  }

  // вычисление ключа в позициях где известны исходные символы
  for (lineIndex = 0; lineIndex < nLines; ++lineIndex) {
    len = text[lineIndex].len;
    for (symIndex = 0; symIndex < len; ++symIndex) {
      if (text[lineIndex].origin[symIndex] != '*')
        key[symIndex] = text[lineIndex].origin[symIndex] ^ text[lineIndex].coded[symIndex];
    }
  }

  // найти ключ в остальных позициях
  for (keyIndex = 0; keyIndex < keyLen; ++keyIndex) {
    if (key[keyIndex] == 0) { // ключ в этой позиции не определён ранее
      // Как-то найти ключ, известно:
      // 1. В этой позиции в какой-то строке исходного текста обязательно будет пробел
      // 2. Ключ и исходный текст в этой позиции - только допустимые символы
      // 3. Предполагая пробел в каждой строке по очереди, определить вариант ключа
      // 4. Посмотреть, даёт ли этот вариант со всеми другими строками допустимые символы
      // 5. Если да - нашли ключ, нет - предполагаем что пробел в другой строке

    }
  }


  // Напечатать ответ

  return 0;
}

