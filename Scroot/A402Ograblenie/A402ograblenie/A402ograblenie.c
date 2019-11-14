#include <stdio.h>              // A402ograblenie.c
#pragma warning(disable:4996)   // for use scanf in VisualStudio

#define MAX_LINE_LEN    513     // +1      
#define MAX_LINES_COUNT 20       
#define DEBUG_PRINT(x)  x       // исполнять то что в скобках (отладочную печать)
//#define DEBUG_PRINT(x)          // игнорировать всё в скобках  (отладочную печать)


typedef struct codedLine {      // в структуре храню стразу обе строки
  char origin [MAX_LINE_LEN];   // исходная строка со ****
  char coded  [MAX_LINE_LEN];   // закодированная (переведена из 16ричного вида)
} codedLine;


// return 1, если латинская буква или пробел
int _isLetterOrSpace(char c) {
  if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ')
    return 1;
  return 0;
}

// преобразует 16ричный символ 0..9A..F --> число 0..15
char _convert0F(char x) {
  if      ('0' <= x && x <= '9')   return x - '0';
  else if ('A' <= x && x <= 'F')   return x - 'A' + 10;
  else if ('a' <= x && x <= 'f')   return x - 'a' + 10;
  else                             return 0;  // верну хоть что-то
}

// в строке 2 первых символа 16ричные символы, возврат - char байт из них
char _convert2Hex(char const* str) {
  char digit1 = *str,         // 1й символ
       digit2 = *(str + 1);   // 2й символ
  return (char)(_convert0F(digit1) * 16 + _convert0F(digit2));
}


int main()
{
  static codedLine text[MAX_LINES_COUNT]  = { 0 };  // тут хранятся строки
  static char       key[MAX_LINE_LEN]     = { 0 };  // ключ
  static char    buffer[MAX_LINE_LEN * 2] = { 0 };  // буфер для 16ричных кодированных строк
  int nLines = 0;                                   // число строк
  int messageLen = 0;                               // длина одного сообщения
  int line_i, buff_i, sym_i, key_i, index, goodKey; // это i для циклов и прочие вспомогательные  
  char keySymbol;
  
  // --- ВВОД -----------------------------------------------------------------
  scanf("%d%d", &nLines, &messageLen);
  
  // ввод строк с кодом
  for (line_i = 0; line_i < nLines; ++line_i) {
    scanf("%s", &buffer);
    // каждые 2 символа кода 16ричного вида -> 1 символ байт
    for (buff_i = 0; buff_i < messageLen * 2; buff_i += 2)            // сдвиг индекса по 2
      text[line_i].coded[buff_i / 2] = _convert2Hex(&buffer[buff_i]); // а тут делим на 2
  }

  // ввод оригиналов строк с затёртыми смиволами
  for (line_i = 0; line_i < nLines; ++line_i)
    scanf("%s", &text[line_i].origin);


  // --- РАСШИФРОВКА ----------------------------------------------------------
  DEBUG_PRINT (printf("\n\n Step 1 \n");)
  // вычисление ключа в позициях где известны исходные символы
  for (line_i = 0; line_i < nLines; ++line_i) {
    DEBUG_PRINT (printf("\n%.2d > %s\n     ", line_i, text[line_i].origin);)
    for (sym_i = 0; sym_i < messageLen; ++sym_i) {
      if (text[line_i].origin[sym_i] != '*')  // не звёздочка, можно вычислить ключ
        key[sym_i] = text[line_i].origin[sym_i] ^ text[line_i].coded[sym_i];
      DEBUG_PRINT(printf("%c", key[sym_i]);)
    }
  }

  DEBUG_PRINT(printf("\n\n Step 2 \n");)
  // Как-то найти ключ в остальных позициях строки, известно:
  // 1. В этой позиции в какой-то строке исходного текста обязательно будет пробел
  // 2. Исходный текст в этой позиции - только допустимые символы - буквы или пробел
  // 3. Предполагая пробел в каждой строке по очереди, определяю вариант ключа
  // 4. Посмотрю, даёт ли этот вариант со всеми другими строками допустимые символы
  // 5. Если да - ключ найден, нет - предполагаю что пробел в другой строке

  for (key_i = 0; key_i < messageLen; ++key_i) {
    if (key[key_i] == 0) {          // ключ в этой позиции не определён ранее
      DEBUG_PRINT(printf("\nFinding key[%2d]", key_i);)
                                    // предположим пробел в какой-то строке line_i по очереди
      for (line_i = 0; line_i < nLines; ++line_i) {
                                    // если пробел в этой строке, то ключ будет вот такой
        keySymbol = ' ' ^ text[line_i].coded[key_i];
        DEBUG_PRINT(printf("\nLine [%d] give key[%c] decode ->", line_i, keySymbol);)
        
        goodKey = 1;                // проверим все остальные строки ;-) используя этот ключ
        for (index = 0; index < nLines; ++index) {
          DEBUG_PRINT(printf("[%c]", text[index].coded[key_i] ^ keySymbol);)
          if (!_isLetterOrSpace(text[index].coded[key_i] ^ keySymbol)) {
            goodKey = 0;            // если хоть в одной строке даст неправильную расшифровку
            DEBUG_PRINT(printf(" xxx bad!");)
            break;                  // дальше не проверять
          }
        }
        if (goodKey) {              // во всех строках получилось что-то осмысленное => ключ найден
          key[key_i] = keySymbol;
          DEBUG_PRINT(printf("\nKEY [%2d] FOUND = [%c]\n", key_i, keySymbol);)
          break;                    // для ключа в позиции key_i - остальные строки не проверять
        }
      }
    }
  }
  DEBUG_PRINT(printf("\n\n--- KEY ---\n[%s]\n\n --- RESULT ---\n\n", key);)
  // --- ВЫВОД ----------------------------------------------------------------
  for (key_i = 0; key_i < messageLen; ++key_i)   
    printf("%X", key[key_i]);                     // Ключ в 16ричном
  printf("\n");                                   // конец ключа 
  
  for (line_i = 0; line_i < nLines; ++line_i) {   // Расшифровать все строки
    for (sym_i = 0; sym_i < messageLen; ++sym_i) 
      printf("%c", text[line_i].coded[sym_i] ^ key[sym_i]);
    printf("\n");                                 // конец каждой строки 
  }
  return 0;
}
