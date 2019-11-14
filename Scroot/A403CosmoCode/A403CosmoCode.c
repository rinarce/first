#include <stdio.h>              // A403CosmoCode.c 
#pragma warning(disable:4996)   // for use scanf in VisualStudio

#define MAX_LINE_LEN    50001   // +1      
#define MAX_LINES_COUNT    20     
//#define DEBUG_PRINT(x)    x   // исполнять то что в скобках (отладочную печать)
//#define DEBUG_PRINT(x)        // игнорировать всё в скобках  (отладочную печать)


// преобразует 16ричный символ 0..9A..F --> число 0..15
char _convert0F(char x) {
  if      ('0' <= x && x <= '9')   return x - '0';
  else if ('A' <= x && x <= 'F')   return x - 'A' + 10;
  else if ('a' <= x && x <= 'f')   return x - 'a' + 10;
  else                             return 0; // верну хоть что-то
}

// в строке 2 первых символа 16ричные символы, возврат - char байт из них
char _convert2Hex(char const* str) {
  char digit1 = *str,         // 1й символ
       digit2 = *(str + 1);   // 2й символ
  return (char)(_convert0F(digit1) * 16 + _convert0F(digit2));
}


int main()
{
  static char decoded[MAX_LINE_LEN]     = { 0 };  // расшифрованная строка
  static char  buffer[MAX_LINE_LEN * 2] = { 0 };  // буфер для 16ричных кодированных строк
  char key = 0xAA;                                // ключ
  int nLines = 0;                                 // число строк
  int messageLen = 0;                             // длина одного сообщения
  int line_i, buff_i;
  
  scanf("%d%d", &nLines, &messageLen);

  // ввод строки с кодом -> сразу расшифровка -> сразу вывод каждой строки
  for (line_i = 0; line_i < nLines; ++line_i) {

    scanf("%s", &buffer);                                             
                                // каждые 2 символа кода 16ричного вида -> 1 символ байт
    for (buff_i = 0; buff_i < messageLen * 2; buff_i += 2)          // сдвиг индекса по 2
      decoded[buff_i / 2] = _convert2Hex(&buffer[buff_i]) ^ key;    // сразу расшифровка

    printf("%s\n", decoded);    // символ конца строки \0 не будет затираться в массиве decoded[]
  }
   return 0;
}