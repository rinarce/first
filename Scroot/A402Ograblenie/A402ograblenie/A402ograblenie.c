#include <stdio.h>              // A402ograblenie.c
#pragma warning(disable:4996)   // for use scanf in VisualStudio

#define MAX_LINE_LEN    520      
#define MAX_LINES_COUNT 21       
#define DEBUG


typedef struct codedLine {
  char origin [MAX_LINE_LEN];   // исходная строка со *
  char coded  [MAX_LINE_LEN];   // закодированная (переведена из шестнадцателричного вида)
} codedLine;


// return 1, если лат буква или пробел
int _charIsLetterOrSpace(char c) {
  if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ')
    return 1;
  return 0;
}


// получает указатель на строку - 2 первых символа шестначатеричные символы
// возврат - char байт из этих символов
char _convert2HexInChar(char const* hex) {
  char digit1, digit2, t;
  t = *hex;                                                 // 1й символ
  if      ('0' <= t && t <= '9')   digit1 = t - '0';
  else if ('A' <= t && t <= 'F')   digit1 = t - 'A' + 10;
  else if ('a' <= t && t <= 'f')   digit1 = t - 'a' + 10;
  t = *(hex + 1);                                           // 2й символ
  if      ('0' <= t && t <= '9')   digit2 = t - '0';
  else if ('A' <= t && t <= 'F')   digit2 = t - 'A' + 10;
  else if ('a' <= t && t <= 'f')   digit2 = t - 'a' + 10;

  return (char)(digit1*16 + digit2); 
}


int main()
{
  static codedLine text[MAX_LINES_COUNT] = { 0 };   // тут хранятся строки
  static char key[MAX_LINE_LEN] = { 0 };            // ключ
  static char buffer[MAX_LINE_LEN * 2] = { 0 };     // буфер для 16ричных кодированных строк
  int nLines = 0;                                   // число строк
  int messageLen = 0;                               // длина одного сообщения
  
  int lineIndex, buffIndex, symIndex, keyIndex, index, goodKey;
  char x;

  scanf("%d%d", &nLines, &messageLen);
  
  // ввод строк с кодом
  for (lineIndex = 0; lineIndex < nLines; ++lineIndex) {
    scanf("%s", &buffer);
    // каждые 2 символа кода 16ричного вида -> 1 символ байт
    for (buffIndex = 0; buffer[buffIndex] != '\0'; buffIndex += 2)
      text[lineIndex].coded[buffIndex / 2] = _convert2HexInChar(&buffer[buffIndex]);
  }

  // ввод оригиналов строк с затёртыми смиволами
  for (lineIndex = 0; lineIndex < nLines; ++lineIndex)
    scanf("%s", &text[lineIndex].origin);


  // РАСШИФРОВКА
  printf("\nStep 1\n");
  // вычисление ключа в позициях где известны исходные символы
  for (lineIndex = 0; lineIndex < nLines; ++lineIndex) {
    printf("\n%.2d >> %s\n      ", lineIndex, text[lineIndex].origin);   
    for (symIndex = 0; symIndex < messageLen; ++symIndex) {
      if (text[lineIndex].origin[symIndex] != '*') // не звёздочка, можно вычислить ключ
        key[symIndex] = text[lineIndex].origin[symIndex] ^ text[lineIndex].coded[symIndex];
      printf("%c", key[symIndex]);
    }
  }

  printf("\n\nStep 2\n");
  // Как-то найти ключ в остальных поициях, известно:
  // 1. В этой позиции в какой-то строке исходного текста обязательно будет пробел
  // 2. Исходный текст в этой позиции - только допустимые символы
  // 3. Предполагая пробел в каждой строке по очереди, определяю вариант ключа
  // 4. Посмотрю, даёт ли этот вариант со всеми другими строками допустимые символы
  // 5. Если да - ключ найден, нет - предполагаю что пробел в другой строке

  for (keyIndex = 0; keyIndex < messageLen; ++keyIndex) {
    if (key[keyIndex] == 0) {             // ключ в этой позиции не определён ранее
      printf("\nFind key[%2d]", keyIndex);
      // предположим пробел в какой-то строке lineIndex
      for (lineIndex = 0; lineIndex < nLines; ++lineIndex) {
        // если пробел в этой строке, то ключ будет вот такой
        x = ' ' ^ text[lineIndex].coded[keyIndex]; 
        printf("\n<line [%d] give key[%c]>", lineIndex, x);

        // проверим все остальные строки ;-) используя этот ключ
        goodKey = 1;
        for (index = 0; index < nLines; ++index) {
          printf("[%c]", text[index].coded[keyIndex] ^ x); 
          if (!_charIsLetterOrSpace(text[index].coded[keyIndex] ^ x)) {
            goodKey = 0;  // если хоть в одной строке даст неправильную расшифровку
            printf(" xxx bad!");
            break;        // дальше не проверять
          }
        }
        if (goodKey) {    // во всех строках получилось что-то осмысленное => ключ найден
          key[keyIndex] = x;
          printf("\nKEY [%2d] FOUND = [%c]\n", keyIndex, x);
          break;          // для ключа в позиции keyIndex - остальные строки не проверять
        }
      }
    }
  }

  printf("\n\n---KEY---\n[%s]\n\n ---RESULT--\n\n", key);

  // Ключ в 16ричном виде
  for (keyIndex = 0; keyIndex < messageLen; ++keyIndex)
    printf("%X", key[keyIndex]);
  printf("\n");       // конец ключа 

  // Расшифровать сообщение
  for (lineIndex = 0; lineIndex < nLines; ++lineIndex) {
    for (symIndex = 0; symIndex < messageLen; ++symIndex) 
      printf("%c", text[lineIndex].coded[symIndex] ^ key[symIndex]);
    printf("\n");     // конец каждой строки 
  }
  return 0;
}
