#include <stdio.h>
#include <stdlib.h> 
#include "DST_functions.h"
          
//#define DEBUG                 // Отладка
#define DST_BUFFER_SIZE 10     // порции считывания строки

// длина строки до '\0'
unsigned int _strLenght(char const* str) {  
  int lenght = 0;
  if (NULL != str)
    while (*str++) 
      lenght++;
  return lenght;
}

// находит вхождение в строку символа, или конец строки '\0'
char* _strFindChar(char const* str, char symbol, int start) 
{
  str += start;                               // смещение от начала строки
  while (*str)
    if (symbol == (*str)) 
      return (char*)str;  // вернёт адрес первого найденного
    else 
      ++str;
  return (char*)str;                          // тут вернёт адрес концы строки '\0'
}

// 1 - если строка пустая (ни обного символа), иначе 0
int _strIsEmpty(char const* str) { 
  return ((NULL != str) && *str) ? 0 : 1;
}

// определяет, что является допустимой буквой в данной задаче
// 1 - если [A–Z] или [a–z] или [0–9], иначе - 0
int _charIsAlNum(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

// возвращает указатель на следующую букву в str или на конец строки
char* _strFindNextWord(char const* str) {
  while (*str && !_charIsAlNum(*str)) 
    str++;
  return (char*)str;
}

// возвращает указатель на следующую НЕбукву в str или на конец строки
char* _strFindNextSeparator(char const* str) {
  while (*str && _charIsAlNum(*str)) 
    str++;
  return (char*)str;
}

// сравнивает строки на длину distance, возврат 1 если равны, 0 иначе
int _strCompareFixLen(char const* str1, char const* str2, unsigned int distance) { 
  while (distance--)
    if (*(str1++) != *(str2++))   // до первого несовпадения
      return 0;
  return 1;
}

// транслитерация 1 русского символа, в строке должно быть минимум 5 байта длины
void _charTransliterate(char* str) {  
   // по правилам - ПРИКАЗ МИД РФ от 29 марта 2016 г. N 4271
  switch (*str)
  {
  case 'а': str[0] = 'a'; str[1] = '\0'; break;
  case 'А': str[0] = 'A'; str[1] = '\0'; break;
  case 'б': str[0] = 'b'; str[1] = '\0'; break;
  case 'Б': str[0] = 'B'; str[1] = '\0'; break;
  case 'в': str[0] = 'v'; str[1] = '\0'; break;
  case 'В': str[0] = 'V'; str[1] = '\0'; break;
  case 'г': str[0] = 'g'; str[1] = '\0'; break;
  case 'Г': str[0] = 'G'; str[1] = '\0'; break;
  case 'д': str[0] = 'd'; str[1] = '\0'; break;
  case 'Д': str[0] = 'D'; str[1] = '\0'; break;
  case 'е':
  case 'ё': str[0] = 'e'; str[1] = '\0'; break;
  case 'Е': 
  case 'Ё': str[0] = 'E'; str[1] = '\0'; break;
  case 'ж': str[0] = 'z'; str[1] = 'h'; break; str[2] = '\0'; break;
  case 'Ж': str[0] = 'Z'; str[1] = 'h'; break; str[2] = '\0'; break;
  case 'з': str[0] = 'z'; str[1] = '\0'; break;
  case 'З': str[0] = 'Z'; str[1] = '\0'; break;
  case 'и':
  case 'й': str[0] = 'i'; str[1] = '\0'; break;
  case 'И':
  case 'Й': str[0] = 'I'; str[1] = '\0'; break;
  case 'к': str[0] = 'k'; str[1] = '\0'; break;
  case 'К': str[0] = 'K'; str[1] = '\0'; break;
  case 'л': str[0] = 'l'; str[1] = '\0'; break;
  case 'Л': str[0] = 'L'; str[1] = '\0'; break;
  case 'м': str[0] = 'm'; str[1] = '\0'; break;
  case 'М': str[0] = 'M'; str[1] = '\0'; break;
  case 'н': str[0] = 'n'; str[1] = '\0'; break;
  case 'Н': str[0] = 'N'; str[1] = '\0'; break;
  case 'о': str[0] = 'o'; str[1] = '\0'; break;
  case 'О': str[0] = 'O'; str[1] = '\0'; break;
  case 'п': str[0] = 'p'; str[1] = '\0'; break;
  case 'П': str[0] = 'P'; str[1] = '\0'; break;
  case 'р': str[0] = 'r'; str[1] = '\0'; break;
  case 'Р': str[0] = 'R'; str[1] = '\0'; break;
  case 'с': str[0] = 's'; str[1] = '\0'; break;
  case 'С': str[0] = 'S'; str[1] = '\0'; break;
  case 'т': str[0] = 't'; str[1] = '\0'; break;
  case 'Т': str[0] = 'T'; str[1] = '\0'; break;
  case 'у': str[0] = 'u'; str[1] = '\0'; break;
  case 'У': str[0] = 'U'; str[1] = '\0'; break;
  case 'ф': str[0] = 'f'; str[1] = '\0'; break;
  case 'Ф': str[0] = 'F'; str[1] = '\0'; break;
  case 'х': str[0] = 'k'; str[1] = 'h'; str[2] = '\0'; break;
  case 'Х': str[0] = 'K'; str[1] = 'h'; str[2] = '\0'; break;
  case 'ц': str[0] = 't'; str[1] = 's'; str[2] = '\0'; break;
  case 'Ц': str[0] = 'T'; str[1] = 's'; str[2] = '\0'; break;
  case 'ч': str[0] = 'c'; str[1] = 'h'; str[2] = '\0'; break;
  case 'Ч': str[0] = 'C'; str[1] = 'h'; str[2] = '\0'; break;
  case 'ш': str[0] = 's'; str[1] = 'h'; str[2] = '\0'; break;
  case 'Ш': str[0] = 'S'; str[1] = 'h'; str[2] = '\0'; break;
  case 'щ': str[0] = 's'; str[1] = 'h'; str[2] = 'c'; str[3] = 'h'; str[4] = '\0'; break;
  case 'Щ': str[0] = 'S'; str[1] = 'h'; str[2] = 'c'; str[3] = 'h'; str[4] = '\0'; break;
  case 'ы': str[0] = 'y'; str[1] = '\0'; break;
  case 'Ы': str[0] = 'Y'; str[1] = '\0'; break;
  case 'ъ': str[0] = 'i'; str[1] = 'e'; str[2] = '\0'; break;
  case 'Ъ': str[0] = 'I'; str[1] = 'e'; str[2] = '\0'; break;
  case 'ь': str[0] = '\''; str[1] = '\0'; break; // в приказе ьЬ не определены
  case 'Ь': str[0] = '\''; str[1] = '\0'; break; // используем '
  case 'э': str[0] = 'e'; str[1] = '\0'; break;
  case 'Э': str[0] = 'E'; str[1] = '\0'; break;
  case 'ю': str[0] = 'i'; str[1] = 'u'; str[2] = '\0'; break;
  case 'Ю': str[0] = 'I'; str[1] = 'u'; str[2] = '\0'; break;
  case 'я': str[0] = 'i'; str[1] = 'a'; str[2] = '\0'; break;
  case 'Я': str[0] = 'I'; str[1] = 'a'; str[2] = '\0'; break;
  default:
    break;
  }
}

  // сравнивает строку с маской, возврат 1 если подходит, 0 иначе
  // пробую рекурсию ? - любой символ, * - любая группа символов или ничего
int _strCompareWithMask(char const* str, char const* mask) { 
  if (*str == 0 && *mask == 0)
    return 1;                 // одновременно дошли до конца обоих строк
  if (*str == 0) {            // строка закончилась, шанс есть только для '*'
    if (*mask == '*')
      return _strCompareWithMask(str, mask+1);  // укорачиваем маску на *
    else 
      return 0;
  }
  else if (*mask == '?' || *mask == *str)     // символы совпали или шаблон '?'
    return _strCompareWithMask(str+1, mask+1);  // укорачиваем обе строки
  else if (*mask == '*')  { 
    // тут анализ шаблона '*' проверяем варианты, если срабытывает, то сразу возврат
    // вариант 1 - продвигаем только строку, шаблон остаётся на '*'
    if (_strCompareWithMask(str+1, mask)) 
      return 1;
      
    // вариант 2 - продвигаем обе строки
    if (_strCompareWithMask(str+1, mask+1)) 
      return 1;
    
    // вариант 3 - продвигаем маску, сразу возвращаем результат
    return _strCompareWithMask(str, mask+1);
  }
  else 
    return 0; // не совпали символы, или закончилась маска, а строка нет
}

// ищет в строке str с позиции pos слово word
// return - позиция (от начала строки) или -1 == не найдено
int _strFindWord(char const* str, char* word, unsigned int pos) {  
  char const* strPtr = str + pos;
  int wordLen = _strLenght(word);
  int str_len = _strLenght(str);
  if (wordLen && str_len) {  
    char const* limit = str + str_len - wordLen;  // до куда искать
    while (strPtr <= limit) {
      strPtr = _strFindNextWord(strPtr);
      if (!(*strPtr))  // закончились слова в строке
        break;
      if (_strCompareFixLen(strPtr, word, wordLen)) // совпало начало
        // за найденым идёт разделитель, слово не продолжается
        if (! _charIsAlNum(*(strPtr + wordLen))) 
          return (strPtr - str); // слово найдено
      strPtr = _strFindNextSeparator(strPtr);
    }
  }
  return -1;
}

// ищет в строке str с позиции pos подстроку subStr 
// return - позиция (от начала строки) или -1 == не найдено
int _strFindSubStr(char const* str, char* subStr, unsigned int pos) { 
  char const* strPtr = str + pos;
  int subStrLen = _strLenght(subStr);
  int strLen = _strLenght(str);
  if (subStrLen && strLen)  {
    char const* limit = str + strLen - subStrLen;   // до куда искать
    while (strPtr <= limit) {                       // поиск
      if(_strCompareFixLen(strPtr, subStr, subStrLen))
          return (strPtr - str);                    // нашли
      strPtr++;
    }
  }
  return -1;                                        // не нашли
}

// возвращает длину слова от начала str
unsigned int _strFirstWordLen(char const* str) {
  return _strFindNextSeparator(str) - str; 
}

// возвращает количество слов в str
unsigned int _strCountWords(char const* str) {
  unsigned int counter = 0;
  while(*(str = _strFindNextWord(str))) { // пока не найден конец строки \0
    counter++;
    str = _strFindNextSeparator(str);
  }
  return counter;
}

// возвращает количество букв в str
unsigned int _strCountSymbols(char const* str) {
  unsigned int counter = 0;
  while (*str)
    counter += _charIsAlNum(*str++);
  return counter;
}

// возвращает количество НЕбукв в str
unsigned int _strCountSeparators(char const* str) {
  unsigned int counter = 0;
  while (*str)
    counter += _charIsAlNum(*str++) ? 0 : 1;
  return counter;
}

// считает вхождение в строку символа X
unsigned int _strCountChar(char const* str, char x) {
  unsigned int counter = 0;
  while (*str)
    if(x == (*str++)) 
      counter++;
  return counter;
}

// выделяет место для строки размером (size + 1)
char* _strAllocate(unsigned int size) { 
  char* new_str = (char*)malloc(size + 1);
  if(NULL != new_str)
    *new_str = '\0';   // на всякий случай в начале делаем конец строки
  return new_str;
}

// Создаёт новую строку == str
char* _strCopyString(char const* str) { 
  unsigned int str_size = _strLenght(str);
  char* new_str = (char*)malloc(str_size + 1);
  if (NULL != new_str) {
    char const* pOrigin = str;
    char* pNew = new_str;
    // копируем, последний скопированный будет конец строки '\0'
    while (*(pNew++) = *(pOrigin++)) {
    };  
  }
  return new_str;
}

// Создаёт новую строку == str[start...end]
char* _strNewSubStr(char const* str, int start, int end) { 
  if (start > end) 
    return NULL;
  unsigned int strSize = end - start;
  char* new_str = (char*)malloc(strSize + 1);
  if (NULL != new_str) {
    char const* pOrigin = str + start;
    char const* pEnd = str + end;
    char* pNew = new_str;
    // копируем, последний скопированный будет конец строки '\0'
    while (pOrigin <= pEnd && *pOrigin)  // копируем кусок [start..end] или до конца '\0'
      *(pNew++) = *(pOrigin++); 
    pNew = '\0';   // конец строки
  }
  return new_str;
}

// Создаёт новую строку == str, несколько пробелов подряд заменяются на один
// В начале строки пробелы удаляются
char* _strOnlyOneSpace(char const* str) { 
  unsigned int strSize = _strLenght(str);
  // выделяю место по длнине оригинала
  char* newStr = (char*)malloc(strSize + 1);
  if (NULL != newStr) {
    char const* pOrigin = str;
    char* pNew = newStr;
    int isPredSpase = 1;      // считаю, что пробелы в начале строки не нужны
    do {
      if (*pOrigin == ' ') {  // найден пробел
        if (!isPredSpase)     // пробел копируем только если перед ним был НЕпробел
          *(pNew++) = *(pOrigin++); 
        else  
          pOrigin++;          // был пробел => не копируем, просто сдвигаем указатель
        isPredSpase = 1;      // запомнить, что был пробел
      }
      else {
        *(pNew++) = *(pOrigin++);  // копируем не пробел
        isPredSpase = 0;      // запомнить, что был не пробел
      }
    } while (*pOrigin);       // копируем, пока не конец строки
    *pNew = '\0';             // конец строки
  }
  // строка возможно сократилась, перераспределить память ? или не надо ?? не буду
  // newStr = (char*)realloc(newStr, _strLenght(newStr) + 1);
  return newStr;
}

// копирует символы в строках strFrom -> strTo, в количестве number
void _strCopySymbols(char const* strFrom, char* strTo, unsigned int number) { 
  while (number--)
    *(strTo++) = *(strFrom++);
}

// вводит строку произвольной длины, самостоятельно выделяет память
// в *str возвращает указатель на строку, return возвращает длину строки
unsigned int DstInputStr(char** str, char const* text) {
  printf("%s", text);
  char* result_str = NULL;  // Это указатель на итоговую строку, тут накапливаем ввод
  unsigned int str_len = 0; // Накапливаем длину строки, в конце - возвращаем
  char buffer[DST_BUFFER_SIZE + 1] = { 0 }; // Для порций ввода
  
  while (1) { // считываем строку порциями размера DST_BUFFER_SIZE
    // fgets читает на 1 символ меньше, так как в конце всегда добавляет '\0'
    unsigned int input_len = _strLenght(fgets(buffer, DST_BUFFER_SIZE + 1, stdin));

#ifdef DEBUG    
    printf("\nПрочитано %u [%s]", input_len, buffer);
#endif

    if (buffer[input_len - 1] == '\n')
      buffer[--input_len] = '\0';  // заменяем '\n' -> '\0', уменьшаем длину

    char * new_str = (char*)realloc(result_str, str_len + input_len + 1);
    if (NULL == new_str)  { // выделение памяти не удалось, возвращаем что есть
      printf("No more memory\n");
      break;
    }
    else {
      result_str = new_str;                       //  результат возможно уже в другом месте
      // первые ячейки уже заполнены, сместиться на длину имеющейся строки 
      char* res_pointer = result_str + str_len;  
      char* in_pointer = buffer;                  // добавляем очередную порцию из buffer
      while (*res_pointer++ = *in_pointer++) {
      };  // копируем пока не '\0' в конце buffer

      str_len += input_len;                       // новая длина строки
      
      if (input_len < DST_BUFFER_SIZE)            // использован не весь входной буфер => ввод закончен
        break;
    }
  }
  *str = result_str;
  return str_len;
}


// расширяет строку str, добавляя к ней + separator + appendStr
// separator добавляется только если str не пустая
// возвращает длину добавленного
int StrJointSeparStr(char** str, char const* separator, char const* appendStr) { 
  unsigned int originLen = _strLenght(*str);
  unsigned int separatorLen = _strLenght(separator);
  unsigned int appendLen = _strLenght(appendStr);
  unsigned int newLen =  (originLen ? originLen + separatorLen : 0) + appendLen + 1;
  char* newMemory = (char*)realloc(*str, newLen);
  if (NULL == newMemory)
    return 0;
  *str = newMemory;   // возможно указатель изменился
  char* strPtr = newMemory + originLen;  // добавляем от конца имеющегося

  if (originLen)      //  для непустой строки вставляем разделители
    while (*separator)
      *strPtr++ = *separator++;

  while (*appendStr)   // копируем 2ю строку
    *strPtr++ = *appendStr++;
  *strPtr = '\0';     // коней строки

  return (originLen ? separatorLen : 0) + appendLen;
}

// из str выдаёт первое слово в новую созданную строку, или NULL
char* _strGetFirstWord(char const* str) { 
  char* wordPtr = _strFindNextWord(str);
  if (! *wordPtr)                 // слов не найдено
    return NULL;
  char* wordEnd = _strFindNextSeparator(wordPtr);
  unsigned int wordLen = wordEnd - wordPtr;

  char* newString = (char*)malloc(wordLen + 1);   // выделние памяти
  if (NULL == newString)          // выделение памяти не удалось
    return NULL;

  char* newStrPtr = newString;    // копирование
  while (wordLen--)
    *(newStrPtr++) = *(wordPtr++);
  *newStrPtr = '\0';              //  конец строки
  return newString;
}

// из str выдаёт только буквы в новую созданную строку
char* StrGetOnlyLetters(char const* str) { 
  unsigned int letters = _strCountSymbols(str);

  char* newString = (char*)malloc(letters + 1);
  if (NULL == newString)          // выделение памяти не удалось
    return NULL;

  char* newStrPtr = newString;    // копирование
  char const* oldStrPtr = str;
  while (*oldStrPtr)              // пока не конец строки
    if (_charIsAlNum(*oldStrPtr)) //   копируем только буквы
      *(newStrPtr++) = *(oldStrPtr++);
    else
      oldStrPtr++;                // небуква - пропускаем
  
  *newStrPtr = '\0';              //  конец строки
  return newString;
}

// str[start...end] <- str[end...start] , т.е. в обратном порядке
char* _strReverseInStr(char *str, int start, int end) { 
  char* p1 = str + start;
  char* p2 = str + end;
  while (p1 < p2) {
    char temp = *p1;
    *(p1++) = *p2;
    *(p2--) = temp;
  }
  return str;
}

// Реверс строки
char* _strReverseAllStr(char* str) { 
  char* p1 = str;
  char* p2 = str + _strLenght(str) - 1;
  while (p1 < p2)
  {
    char temp = *p1;
    *(p1++) = *p2;
    *(p2--) = temp;
  }
  return str;
}

// XXXXXXXXXXXXXXXXX   ЗАДАНИЯ     XXXXXXXXXXXXXXXXXXXXXXXX

// новая строка, БУКВЫ из str разделены новым разделителем
char* ExtractLetters(char const* str, char const* newSeparator){ 
  unsigned int sepLenght = _strLenght(newSeparator);
  int symbols = _strCountSymbols(str);
  unsigned int newStringSize = symbols ? (symbols + (symbols - 1) * sepLenght) : 0;
  char* result = _strAllocate(newStringSize);
  if (NULL == result)  // выделение памяти не удалось
    return result;
  char* resultPtr = result;
  int wasFirstWord = 0;

  while (*str) {
    if (_charIsAlNum(*str)) {
      if (wasFirstWord++) { // разделителя не будет только перед первым словом
        _strCopySymbols(newSeparator, resultPtr, sepLenght);
        resultPtr += sepLenght;
      }
      *resultPtr++ = *str; // тут копируем символ в новую строку
    }
    str++;                // следующий символ
  }
  *resultPtr = '\0';       // конец строки
  return result;
}

// новая строка, СЛОВА из str разделены новым разделителем
char* ExtractWords(char const* str, char const* newSeparator) { 
  char const* strPtr = str;
  char* nextWord = NULL; // очередное слово (выделено отдельно)
  char* result = _strAllocate(0);    // тут накапливаем результат
 
  while (nextWord = _strGetFirstWord(strPtr)) {
    unsigned int nextWordLen = _strLenght(nextWord);
    int added = StrJointSeparStr(&result, newSeparator, nextWord);

    free(nextWord);      // удаляем слово, оно уже не нужно
    if (!added)  // добавление не удалось, возвращаем всё что есть
      break;
    // смещаем указатель - находим начало слова, от него - конец слова
    strPtr = _strFindNextWord(strPtr) + nextWordLen;
  }
  return result;
}


// новая строка, УНИКАЛЬНЫЕ СЛОВА из str разделены новым разделителем
char* ExtractUniqueWords(char const* str, char const* newSeparator) { 
  char const* strPtr = str;
  char* nextWord = NULL; // очередное слово (выделено отдельно)
  char* result = _strAllocate(0);    // тут накапливаем результат

  while (nextWord = _strGetFirstWord(strPtr)) {
    unsigned int nextWordLen = _strLenght(nextWord);

    if (_strFindWord(result, nextWord, 0) == -1) { // слова ещё не было в строке
      int added = StrJointSeparStr(&result, newSeparator, nextWord);
      if (!added) { // добавление не удалось, возвращаем всё что есть
        free(nextWord);      // удаляем слово, оно уже не нужно
        break;
      }
    }
    free(nextWord);      // удаляем слово, оно уже не нужно
    // смещаем указатель - находим начало слова, от него - конец слова
    strPtr = _strFindNextWord(strPtr) + nextWordLen; 
  }
  return result;
}


// новая строка, УНИКАЛЬНЫЕ БУКВЫ из str разделены новым разделителем
char* ExtractUniqueLetters(char const* str, char const* newSeparator) { 
  char const* strPtr = str;
  char* result = _strAllocate(0);    // тут накапливаем результат
  char letter[] = "x";    // не создаём каждый раз строку, используем эту

  while (*(strPtr = _strFindNextWord(strPtr))) {
    letter[0] = *strPtr; // строка из одной буквы
    if (_strFindWord(result, letter, 0) == -1) { // слова ещё не было в строке
      int added = StrJointSeparStr(&result, newSeparator, letter);
      if (!added)  // добавление не удалось, возвращаем всё что есть
        break;
    }
    strPtr++;    // смещаем указатель - на следующую букву
  }
  return result;
}


// новая строка, из str удалены разделители и найдены 
// все подстроки длиннее 1, которые есть в зеркальном виде,
// они разделены новым разделителем
char* FindMirrors(char const* str, char const* newSeparator) { 
  char* result = _strAllocate(0);          // тут накапливаем результат
  char* strSyms = StrGetOnlyLetters(str);  // тут только буквы
  if (NULL == strSyms)                      // букв нет
    return result;
  unsigned int symsLen = _strLenght(strSyms);
  // не буду создавать каждый раз новые строки в цикле
  char* buff = _strAllocate(symsLen);

  char* strPtr = strSyms; // начнём с первого символа
  
  while (symsLen) {       // будем уменьшать оставшуюся длину
    // создаём подстроки начиная от strPtr и до конца строки длиной > 1
    for (unsigned int len = 2; len <= symsLen; ++len) {
      _strCopySymbols(strPtr, buff, len);           // скопировали в buff
      _strReverseInStr(buff, 0, len - 1);           // отзеркалили
      *(buff + len) = '\0';                         // конец строки

      if (_strFindSubStr(strSyms, buff, 0) != -1) { // ищем во всей строке символов
       // нашли, проверим, может слово уже есть в строке результата
        _strReverseInStr(buff, 0, len - 1);         // отзеркалили обратно
        if (_strFindWord(result, buff, 0) == -1)    // это новое слово
          if (!StrJointSeparStr(&result, newSeparator, buff)) {
            // сбой формирования результата, вернуть что есть
            free(buff);
            free(strSyms);
            return result;
          }
      }
    }
    strPtr++;                   // анализировать со следующего символа
    symsLen--;                             // осталось до конца строки
  }
  free(strSyms);   // строка букв больше не нужна
  free(buff);
  return result;
}


// новая строка, все подстроки из str по маске поиска, разделены новым разделителем
char* FindMaskWords(char const* str, char const* mask, char const* newSeparator) { 
  char const* strPtr = str;
  char* nextWord = NULL; // очередное слово (выделено отдельно)
  char* result = _strAllocate(0);    // тут накапливаем результат

  while (nextWord = _strGetFirstWord(strPtr)) {
    unsigned int nextwordLen = _strLenght(nextWord);
    if (_strCompareWithMask(nextWord, mask))    // подходит по маске ?
      if (! StrJointSeparStr(&result, newSeparator, nextWord)) {
        // добавление не удалось, возвращаем всё что есть
        free(nextWord);      // удаляем слово, оно уже не нужно
        break;
      }
    free(nextWord);      // удаляем слово, оно уже не нужно
    // смещаем указатель - находим начало слова, от него - конец слова
    strPtr = _strFindNextWord(strPtr) + nextwordLen;
  }
  return result;
}


// новая строка, транслитерация русских символов, 
// по правилам - ПРИКАЗ МИД РФ от 29 марта 2016 г. N 4271
char* ConvertRussian(char const* str) { 
  char const* strPtr = str;
  char* result = _strAllocate(0);     // тут накапливаем результат
  char letter[5] = { 0 };             // не создаём каждый раз строку, используем эту

  while (*strPtr) {
    letter[0] = *strPtr;              // строка из одной буквы
    letter[1] = '\0';
    _charTransliterate(letter);
    int added = StrJointSeparStr(&result, "", letter);
    if (!added)                       // добавление не удалось, возвращаем всё что есть
      break;
    strPtr++;                         // смещаем указатель - на следующую букву
  }
  return result;
}

// пытается состыковать слова для FindChains, иначе NULL
char* _strTryMakeChain(char * firstWord, char * secondWord) { 
  char* result = NULL;
  unsigned int f_len = _strLenght(firstWord);
  unsigned int s_len = _strLenght(secondWord);
   
  // будем проверять слова на совпадение, постепенно сдвигая второе слово вправо
  // сдвигать, пока хотябы 2 символа перекрываются - максимально (f_len - 2)
  // первое слово должно дойти до конца, а второе - не закончится раньше первого
  // 
  for (unsigned second_shift = 0; second_shift <= (f_len - 2); second_shift++)
  {
    char* fPtr = firstWord + second_shift;  // сдвиг второго слова отражается на первом :-)
    char* sPtr = secondWord;

    // пока не кончилось первое слово И идёт совпадение
    while (*fPtr && (*(fPtr) == *(sPtr))) { 
      fPtr++; 
      sPtr++;
    }

    if ((*fPtr) == 0) { // достигнут конец первого слова, а не найдено различие
      // второе слово полностью, первое - только символы вначале, т.е. до second_shift
#ifdef DEBUG
      printf(" == shift >> [%d] ", second_shift);
#endif // DEBUG
      result = _strAllocate(s_len + second_shift);
      // первое слово - копируем то, что не входит во второе
      if (second_shift) 
        _strCopySymbols(firstWord, result, second_shift);
      _strCopySymbols(secondWord, result + second_shift, s_len + 1); // с концом строки 0
      break; // дальше не искать, первым будет найдено самое длинное совпадение
    }
  }
  return result;
}


// новая строка, задание Поиск цепочек - склеивает слова
// если 2 слова совпадают конец одного и начало другого (более 1 символа)
char* FindChains(char const* str, char const* newSeparator) { 
  char* firstWord = NULL;           // очередное слово (выделено отдельно)
  char* secondWord = NULL;          // очередное слово (выделено отдельно)
  char* nextWord = NULL;            // новое составное слово (выделено отдельно)
  char* result = _strAllocate(0);   // тут накапливаем результат

  char* words = ExtractWords(str, newSeparator);    // выделим слова из строки

  // Просто проверю каждый с каждым :-)
  char* firstPtr = words;
  unsigned firstIndex = 0; // будем считать слова, чтобы не соединять слово само с собой
  while (firstWord = _strGetFirstWord(firstPtr)) {
    firstIndex++;                                   // новое первое слово
    unsigned int firstWordLen = _strLenght(firstWord);
    if (firstWordLen > 1) {                         // однобуквенные слова не участвуют
      // тут цикл проверка сочетания со всеми остальными
      char* secondPtr = words;
      unsigned secondIndex = 0;
      while (secondWord = _strGetFirstWord(secondPtr)) {
        secondIndex++;
        unsigned int secondwordLen = _strLenght(secondWord);
        if (secondwordLen > 1) {
          if (firstIndex != secondIndex) {          // не проверяем слово само с собой
#ifdef DEBUG
            printf("\n[%s] + [%s]", firstWord, secondWord);
#endif // DEBUG
            if (NULL != (nextWord = _strTryMakeChain(firstWord, secondWord))) { 
              // удалось сделать цепочку
#ifdef DEBUG
              printf(" == FOUND [%s] ", nextWord);
#endif // DEBUG
              if (_strFindWord(result, nextWord, 0) == -1) { // слова ещё не было в строке
                int added = StrJointSeparStr(&result, newSeparator, nextWord);
                if (!added) { // добавление не удалось, возвращаем всё что есть
                  free(firstWord);
                  free(secondWord);
                  free(nextWord);      // удаляем слово, оно уже не нужно
                  break;
                }
              }
              free(nextWord);
            }
          }
        }
        free(secondWord);
        secondPtr = _strFindNextWord(secondPtr) + secondwordLen;
      }
    }
    free(firstWord);      // удаляем слово, оно уже не нужно
    // смещаем указатель - находим начало слова, от него - конец слова
    firstPtr = _strFindNextWord(firstPtr) + firstWordLen;
  }
  return result;
}


// возврат - новая строка, где str разбита на строки шириной width
// несколько пробелов подряд заменяются на один пробел, выравнование - влево
// между строками - \n, если слово > width, оно разбивается на куски
char* StrJustifyLeft(char* str, unsigned width) { 
  char* cropSP = _strOnlyOneSpace(str);       // сокращаю подряд идущие пробелы
  char* ptr = cropSP;
  char* result = NULL;                        // параграф - строки разделённые \n
  char* resultPtr = result;   
  unsigned resultLen = 0;                     // счётчик символов в параграфе (с \n)
  unsigned countInLine = 0;                   // счётчик символов в каждой строке текста
 
  while (*ptr) {                              // до конца строки
    char* nextWord = _strFindNextWord(ptr);   // следующее слово
    unsigned sepWidth = nextWord - ptr;       // символов до слова
    if (sepWidth) {                           // есть разделители
      // надо добавить это + возможно несколько '\n'
      unsigned addLength = sepWidth + (countInLine + sepWidth) / width;
      unsigned countAdded = 0;
      char* newResult = (char*)realloc(result, resultLen + addLength + 1);
      if (NULL == newResult) 
        break;

      result = newResult;
      resultPtr = result + resultLen;

      for (int i = sepWidth; i; i--) {        // копируем разделители
        if (countInLine == 0 && *ptr == ' ')  // если пробел попал в начало строки не добавлять его
          ptr++;
        else {
          *resultPtr++ = *ptr++;              // тут копирование символа
          countAdded++;
          if (++countInLine >= width) {       // увеличиваем счётчик символов в строке
            if (*(resultPtr - 1) == ' ')      // если в конце строчки был пробел удалить его
              *(resultPtr - 1) = '\n';
            else {
              *resultPtr++ = '\n';            // начать новую строку
              countAdded++;
            }
            countInLine = 0;
          }
        }
      }
      resultLen += countAdded;
    }

    if (*ptr) { // это ещё слово, а не конец строки
      // 3 варианта
      char* nextSepar = _strFindNextSeparator(ptr);
      unsigned wordLen = nextSepar - ptr;
      
      if (countInLine + wordLen > width)  // 1. слово не помещается в строке 
        if (wordLen < width)              // слово меньше ширины строки 
          countInLine = width;            // ставим счётчик символов в строке на конец строки,

      // 2. иначе, либо слово помещается, очень хорошо
      // 3. либо слово шире строки - разбивать надо в любом случае, начнём на этой строке

      unsigned addLength = wordLen + (countInLine + wordLen) / width;
      char* newResult = (char*)realloc(result, resultLen + addLength + 1);
      if (NULL == newResult)  
        break;
      result = newResult;
      resultPtr = result + resultLen;
      unsigned countAdded = 0;
      
      for (int i = wordLen; i; i--) {     // копируем 
        if (countInLine == width) {       // конец строки
          if (*(resultPtr - 1) == ' ')    // если в конце строчки был пробел удалить его
            *(resultPtr - 1) = '\n';
          else {
            *resultPtr++ = '\n';          // начать новую строку
            countAdded++;
          }
          countInLine = 0;
        }
        countInLine++;
        *resultPtr++ = *ptr++;            // тут копирование символа
        countAdded++;
      }
      resultLen += countAdded;
    }
  }
  free(cropSP);
  *resultPtr = '\0';
  return result;
}


// возврат - новая строка, где str разбита на строки шириной width
// выравнивание- по ширине, изменяя количество пробелов
// между строками - \n, если слово > width, оно разбивается на куски
char* StrJustifyWidth(char* str, unsigned width) { 
  char* cropSP = _strOnlyOneSpace(str);       // сокращу пробелы, чтоб не мешались
  if (NULL == cropSP) 
    return NULL;

  char* buffer = (char*)malloc(width + 2);    // тут буду формировать очередную строчку
  if (NULL == buffer) 
    return NULL;    // +1 для '\n'   и   +1 для '\0'

  // сначала разобью на строчки с выравниванием влево, 
  // потом выравняю по ширине каждую строчку
  char* strJistifiedLeft = StrJustifyLeft(cropSP, width);
  free(cropSP);                               // это уже не нужно
  if (NULL == strJistifiedLeft) 
    return NULL;
  
  // количество строчек, возьму с запасом +1 если последняя строчка не полная
  int numLines = _strCountChar(strJistifiedLeft, '\n') + 1;
  // сколько байт нужно, если все строчки будут длиной width + '\n'
  int resultLen = numLines * (width + 1) + 1;   // + конец строки '\0'

  char* result = (char*)malloc(resultLen);
  if (NULL == result) { 
    free(strJistifiedLeft); 
    return NULL; 
  }
  
  char* ptr = strJistifiedLeft;
  char* resultPtr = result;
 
  while (*ptr) { //до конца строки
    char* nextCR = _strFindChar(ptr, '\n', 0);  // следующий '\n' или конец строки '\0'
    if (*nextCR == '\0') { // последнюю строчку не выравнивать, просто скопирую
      while (*ptr) *(resultPtr++) = *(ptr++); // тут копирование
      break;
    }
      
    unsigned int lineLen = nextCR - ptr;
    _strCopySymbols(ptr, buffer, lineLen);     // скопирую в буфер очередную строку(без \n)
    *(buffer + lineLen) = '\0';            // дополню признаком конца строки

#ifdef DEBUG
      printf("\nBUFFER [%s] длина %d", buffer, lineLen);
#endif // DEBUG

    if (lineLen < width) {                  // строку надо расширить
      unsigned int countSpace = _strCountChar(buffer, ' '); // считаем пробелы в этой строке
      unsigned delta = width - lineLen;                // сколько всего добавить пробелов
      
      if (countSpace) { // в строке есть пробелы, будем их увеличивать
        unsigned plusSP = delta / countSpace;      // сколько добавить к каждому имеющемуся пробелу
        unsigned plusSP_special = delta - plusSP * countSpace; // это остаток, добавлять не к каждому
        int countInLine = 0;

        for (unsigned indexInLine = 0; indexInLine < lineLen; ++indexInLine) {
          if (buffer[indexInLine] != ' ') {
            *(resultPtr++) = buffer[indexInLine];
#ifdef DEBUG
              printf("%c", buffer[indexInLine]);
#endif // DEBUG
            
          }
          else { 
            countInLine++;                            // считаем промежутки
            for (unsigned j = 0; j <= plusSP; j++) {  // в этом промежутке пробел стал больше
              *(resultPtr++) = ' ';
#ifdef DEBUG
                printf("#"); // добавлен пробел из числа "как у всех промежутков"
#endif // DEBUG                
               
            }
            // вот тут раскидываются пробелы неравномерно, не в каждый промежуток
            if (plusSP_special && countInLine * plusSP_special % countSpace == 0) {
#ifdef DEBUG
                printf("*");   // этот пробел "особенный, не как все"
#endif // DEBUG                         
              *(resultPtr++) = ' '; // доплонительный пробел
            }
          }
        }
      }
      else  // в строке 1 слово и нет пробелов, допишем их в конец
      {     // или не дополнять пробелам ?? дополню
        unsigned int delta = width - lineLen;
        while (delta--)
          *(buffer + lineLen + delta) = ' ';
        // в буфере строка, но без \n \0
        _strCopySymbols(buffer, resultPtr, width); // в резалт её
        resultPtr += width;                    // сдвину указатель в резалт
#ifdef DEBUG
          printf("\nBUFFER [%s] just add %d SP", buffer, width-lineLen);
#endif // DEBUG
      }
    }
    else  {   // в буфере строка нужной длины, но без \n \0
      _strCopySymbols(buffer, resultPtr, width);  // в резалт её
      resultPtr += width;                         // сдвину указатель в резалт
#ifdef DEBUG
        printf("\nBUFFER [%s] do nothing", buffer);
#endif // DEBUG
    }        
    *(resultPtr++) = '\n';                        // добавить перевод строки
    ptr += lineLen;                               // сдвинуть указатель в исходной строке
    if (*ptr == '\n')                             // сдвинуть ещё, если там \n
      ptr++;
  }
   free(strJistifiedLeft);
  *resultPtr = '\0';  
  return result;
}
