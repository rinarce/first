#include <stdio.h>
#include <stdlib.h>           // для выделения памяти
          
// #define DEBUG                 // Отладка
#define DST_BUFFER_SIZE 5     // порции считывания строки

unsigned int STR_Lenght(char const* str) {  // длина строки до '\0'
  int len = 0;
  if (NULL != str)
    while (*str++) len++;
  return len;
}

int STR_IsEmpty(char const* str)
{ // 1 - если строка пустая, иначе 0
  return ((NULL != str) && *str) ? 0 : 1;
}

int IsAlNum(char c) {
  // определяет, что является допустимой буквой в данной задаче
  // 1 - если [A–Z] или [a–z] или [0–9], иначе - 0
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

char* STR_FindNextWord(char const* str) {
  // возвращает указатель на следующую букву в str или на конец строки
  while (*str && !IsAlNum(*str)) str++;
  return (char*)str;
}

char* STR_FindNextSeparator(char const* str) {
  // возвращает указатель на следующую НЕбукву в str или на конец строки
  while (*str && IsAlNum(*str)) str++;
  return (char*)str;
}

int STR_Compare_FixLen(char const* str1, char const* str2, unsigned int distance)
{ // сравнивает строки на длину distance, возврат 1 если равны, 0 иначе
  while (distance--)
    if (*(str1++) != *(str2++)) // до первого несовпадения
      return 0;
  return 1;
}

void STR_TransliterateSym(char* str)
{  // транслитерация 1 русского символа, в строке должно быть минимум 5 байта длины
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

int STR_CompareByMask(char const* str, char const* mask)
{ // сравнивает строку с маской, возврат 1 если подходит, 0 иначе
  // пробую рекурсию ? - любой символ, * - любая группа символов или ничего
  if (*str == 0 && *mask == 0)
    return 1;                 // одновременно дошли до конца обоих строк
  if (*str == 0)
  {                           // строка закончилась, шанс есть только для '*'
    if (*mask == '*')
      return STR_CompareByMask(str, mask+1);  // укорачиваем маску на *
    else return 0;
  }
  else if (*mask == '?' || *mask == *str)     // символы совпали или шаблон '?'
    return STR_CompareByMask(str+1, mask+1);  // укорачиваем обе строки
  else if (*mask == '*')
  { // тут анализ шаблона '*' проверяем варианты, если срабытывает, то сразу возврат
    
    // вариант 1 - продвигаем только строку, шаблон остаётся на '*'
    if (STR_CompareByMask(str+1, mask)) return 1;
      
    // вариант 2 - продвигаем обе строки
    if (STR_CompareByMask(str+1, mask+1)) return 1;
    
    // вариант 3 - продвигаем маску, сразу возвращаем результат
    return STR_CompareByMask(str, mask+1);
  }
  else return 0; // не совпали символы, или закончилась маска, а строка нет
}

int STR_FindWord(char const* str, char* word, unsigned int pos)
{ // ищет в строке str с позиции pos слово word
  // return - позиция (от начала строки) или -1 == не найдено
  char const* str_ptr = str + pos;
  int word_len = STR_Lenght(word);
  int str_len = STR_Lenght(str);
  if (word_len && str_len)
  {  
    char const* limit = str + str_len - word_len;  // до куда искать
    while (str_ptr <= limit)
    {
      str_ptr = STR_FindNextWord(str_ptr);
      if (!(*str_ptr))  // закончились слова в строке
        break;
      if (STR_Compare_FixLen(str_ptr, word, word_len)) // совпало начало
        // за найденым идёт разделитель, слово не продолжается
        if (! IsAlNum(*(str_ptr + word_len))) 
          return (str_ptr - str); // слово найдено
      str_ptr = STR_FindNextSeparator(str_ptr);
    }
  }
  return -1;
}

int STR_FindSubStr(char const* str, char* subStr, unsigned int pos)
{ // ищет в строке str с позиции pos подстроку subStr 
  // return - позиция (от начала строки) или -1 == не найдено
  char const* str_ptr = str + pos;
  int subStr_len = STR_Lenght(subStr);
  int str_len = STR_Lenght(str);
  if (subStr_len && str_len)
  {
    char const* limit = str + str_len - subStr_len;  // до куда искать
    while (str_ptr <= limit)                         // поиск
    { 
      if(STR_Compare_FixLen(str_ptr, subStr, subStr_len))
          return (str_ptr - str);                    // нашли
      str_ptr++;
    }
  }
  return -1;                                        // не нашли
}

unsigned int WordLen(char const* str) {
  // возвращает длину слова от начала str
  return STR_FindNextSeparator(str) - str; 
}

unsigned int CountWords(char const* str) {
  // возвращает количество слов в str
  unsigned int counter = 0;
  while(*(str = STR_FindNextWord(str))) // пока не найден конец строки \0
  { 
    counter++;
    str = STR_FindNextSeparator(str);
  }
  return counter;
}

unsigned int CountSymbols(char const* str) {
  // возвращает количество букв в str
  unsigned int counter = 0;
  while (*str)
    counter += IsAlNum(*str++);
  return counter;
}

unsigned int CountChar(char const* str, char x) {
  // считает вхождение в строку символа X
  unsigned int counter = 0;
  while (*str)
    if(x == (*str++)) counter++;
  return counter;
}

char* FindChar(char const* str, char x, int start) {
  // находит вхождение в строку символа X, или конец строки '\0'
  str += start;     // от начала строки
  while (*str)
    if (x == (*str)) return (char*)str;  // вернёт адрес первого найденного Х
    else str++;
  return (char*)str;  // тут вернёт адрес концы строки '\0'
}

unsigned int CountSeparators(char const* str) {
  // возвращает количество НЕбукв в str
  unsigned int counter = 0;
  while (*str)
    counter += IsAlNum(*str++) ? 0 : 1;
  return counter;
}

char* AllocateString(unsigned int size)
{ // выделяет место для строки размером (size + 1)
  char* new_str = (char*)malloc(size + 1);
  if(NULL != new_str)
    *new_str = '\0';   // на всякий случай в начале делаем конец строки
  return new_str;
}

char* CopyString(char const* str)
{ // Создаёт новую строку == str
  unsigned int str_size = STR_Lenght(str);
  char* new_str = (char*)malloc(str_size + 1);
  if (NULL != new_str)
  {
    char const* pOrigin = str;
    char* pNew = new_str;
    // копируем, последний скопированный будет конец строки '\0'
    while (*(pNew++) = *(pOrigin++)) {};  
  }
  return new_str;
}

char* STR_GetChars(char const* str, int start, int end)
{ // Создаёт новую строку == str[start...end]
  if (start > end) return NULL;
  unsigned int str_size = end - start;
  char* new_str = (char*)malloc(str_size + 1);
  if (NULL != new_str)
  {
    char const* pOrigin = str + start;
    char const* pEnd = str + end;
    char* pNew = new_str;
    // копируем, последний скопированный будет конец строки '\0'
    while (pOrigin <= pEnd && *pOrigin)  // копируем кусок [start..end] или до конца '\0'
      { *(pNew++) = *(pOrigin++); }
    pNew = '\0';   // конец строки
  }
  return new_str;
}

char* OnlyOneSpace(char const* str)
{ // Создаёт новую строку == str, несколько пробелов подряд заменяются на один
  // В начале строки пробелы удаляются
  unsigned int str_size = STR_Lenght(str);
  // выделяю место по длнине оригинала
  char* new_str = (char*)malloc(str_size + 1);
  if (NULL != new_str)
  {
    char const* pOrigin = str;
    char* pNew = new_str;
    int isPredSpase = 1;    // считаю, что пробелы в начале строки не нужны
    do
    {
      if (*pOrigin == ' ')  // найден пробел
      {
        if (!isPredSpase)   // пробел копируем только если перед ним был НЕпробел
          { *(pNew++) = *(pOrigin++); }
        else
          { pOrigin++; }    // был пробел => не копируем, просто сдвигаем указатель
        isPredSpase = 1;    // запомнить, что был пробел
      }
      else
      {
        *(pNew++) = *(pOrigin++);  // копируем не пробел
        isPredSpase = 0;  // запомнить, что был не пробел
      }
    } while (*pOrigin);   // копируем, пока не конец строки
    *pNew = '\0';         // конец строки
  }
  // строка возможно сократилась, перераспределить память ? или не надо ?? не буду
  // new_str = (char*)realloc(new_str, STR_Lenght(new_str) + 1);
  return new_str;
}

void CopySymbols(char const* strFrom, char* strTo, unsigned int number)
{ // копирует символы в строках strFrom -> strTo, в количестве number
  while (number--)
    *(strTo++) = *(strFrom++);
}

unsigned int DST_InputStr(char** str, char const* text)
// вводит строку произвольной длины, самостоятельно выделяет память
// в *str возвращает указатель на строку, return возвращает длину строки
{
  printf("%s", text);
  char* result_str = NULL;  // Это указатель на итоговую строку, тут накапливаем ввод
  unsigned int str_len = 0; // Накапливаем длину строки, в конце - возвращаем
  char buffer[DST_BUFFER_SIZE + 1] = { 0 }; // Для порций ввода
  
  while (1)  // считываем строку порциями размера DST_BUFFER_SIZE
  {
    // fgets читает на 1 символ меньше, так как в конце всегда добавляет '\0'
    unsigned int input_len = STR_Lenght(fgets(buffer, DST_BUFFER_SIZE + 1, stdin));

#ifdef DEBUG    
    printf("\nПрочитано %u символов ", input_len);
#endif

    if (buffer[input_len - 1] == '\n')
    {
      buffer[--input_len] = '\0';  // заменяем '\n' -> '\0', уменьшаем длину
#ifdef DEBUG
      printf(" {CR найден [%u], удалён} ", input_len);
#endif
    }

#ifdef DEBUG
    printf("\"%s\"\n", buffer); 
#endif
    // просим новый кусок памяти
    char * new_str = (char*)realloc(result_str, str_len + input_len + 1);
    
    if (NULL == new_str)  // выделение памяти не удалось, возвращаем что есть
    { printf("No more memory\n");
      break;
    }
    else 
    {
      result_str = new_str;                   //  результат возможно уже в другом месте
      // первые ячейки уже заполнены, сместиться на длину имеющейся строки 
      char* res_pointer = result_str + str_len;  
      char* in_pointer = buffer;                  // добавляем очередную порцию из buffer
      while (*res_pointer++ = *in_pointer++) {};  // копируем пока не '\0' в конце buffer

      str_len += input_len;  // новая длина строки
#ifdef DEBUG
      printf("Пока введено %u символов, \"%s\"\n", str_len, result_str);
#endif
      // использован не весь входной буфер => ввод закончен
      if (input_len < DST_BUFFER_SIZE)
        break;
    }
  }
  *str = result_str;
  return str_len;
}

int STR_Joint_Separ_Str(char** str, char const* separator, char const* appendStr)
{ // расширяет строку str, добавляя к ней + separator + appendStr
  // separator добавляется только если str не пустая
  // возвращает длину добавленного

  unsigned int origin_len = STR_Lenght(*str);
  unsigned int separator_len = STR_Lenght(separator);
  unsigned int append_len = STR_Lenght(appendStr);
  unsigned int new_len = 
     (origin_len ? origin_len + separator_len : 0) + append_len + 1;
  char* new_memory = (char*)realloc(*str, new_len);
  if (NULL == new_memory)
    return 0;
  *str = new_memory;   // возможно указатель изменился
  char* str_ptr = new_memory + origin_len;  // добавляем от конца имеющегося

  if (origin_len)      //  для непустой строки вставляем разделители
    while (*separator)
      *str_ptr++ = *separator++;

  while (*appendStr)   // копируем 2ю строку
    *str_ptr++ = *appendStr++;
  *str_ptr = '\0';     // коней строки

  return (origin_len ? separator_len : 0) + append_len;
}

char* STR_GetFirstWord(char const* str)
{ // из str выдаёт первое слово в новую созданную строку, или NULL
  char* word_ptr = STR_FindNextWord(str);
  if (! *word_ptr)                 // слов не найдено
    return NULL;
  char* word_end = STR_FindNextSeparator(word_ptr);
  unsigned int word_len = word_end - word_ptr;

  char* new_string = (char*)malloc(word_len + 1);   // выделние памяти
  if (NULL == new_string)         // выделение памяти не удалось
    return NULL;

  char* new_str_ptr = new_string; // копирование
  while (word_len--)
    *(new_str_ptr++) = *(word_ptr++);
  *new_str_ptr = '\0';            //  конец строки
  return new_string;
}

char* STR_GetOnlyLetters(char const* str)
{ // из str выдаёт только буквы в новую созданную строку
  unsigned int letters = CountSymbols(str);

  char* new_string = (char*)malloc(letters + 1);
  if (NULL == new_string)         // выделение памяти не удалось
    return NULL;

  char* new_str_ptr = new_string; // копирование
  char const* old_str_ptr = str;
  while (*old_str_ptr)            // пока не конец строки
    if (IsAlNum(*old_str_ptr))    //   копируем только буквы
      *(new_str_ptr++) = *(old_str_ptr++);
    else
      old_str_ptr++;              // небуква - пропускаем
  
  *new_str_ptr = '\0';            //  конец строки
  return new_string;
}

char* STR_ReverseInStr(char *str, int start, int end)
{ // str[start...end] <- str[end...start] , т.е. в обратном порядке
  char* p1 = str + start;
  char* p2 = str + end;
  while (p1 < p2) 
  {
    char temp = *p1;
    *(p1++) = *p2;
    *(p2--) = temp;
  }
  return str;  // возврат строки на всякий случай
}

char* STR_ReverseAllStr(char* str)
{ // Реверс строки
  char* p1 = str;
  char* p2 = str + STR_Lenght(str) - 1;
  while (p1 < p2)
  {
    char temp = *p1;
    *(p1++) = *p2;
    *(p2--) = temp;
  }
  return str;  // возврат строки на всякий случай
}

// XXXXXXXXXXXXXXXXX   ЗАДАНИЯ     XXXXXXXXXXXXXXXXXXXXXXXX

char* ExtractLetters(char const* str, char const* newSeparator)
{ // новая строка, БУКВЫ из str разделены новым разделителем
  unsigned int sepLenght = STR_Lenght(newSeparator);
  int symbols = CountSymbols(str);
  unsigned int new_string_size = symbols ? (symbols + (symbols - 1) * sepLenght) : 0;
  char* result = AllocateString(new_string_size);
  if (NULL == result)  // выделение памяти не удалось
    return result;
  char* result_p = result;
  int wasFirstWord = 0;

  while (*str)
  {
    if (IsAlNum(*str))
    {
      if (wasFirstWord++)  // разделителя не будет только перед первым словом
      {   
        CopySymbols(newSeparator, result_p, sepLenght);
        result_p += sepLenght;
      }
      *result_p++ = *str; // тут копируем символ в новую строку
    }
    str++;                // следующий символ
  }
  *result_p = '\0';       // конец строки
  return result;
}

char* ExtractWords(char const* str, char const* newSeparator)
{ // новая строка, СЛОВА из str разделены новым разделителем
  char const* str_ptr = str;
  char* next_word = NULL; // очередное слово (выделено отдельно)
  char* result = AllocateString(0);    // тут накапливаем результат
 
  while (next_word = STR_GetFirstWord(str_ptr))
  {
    unsigned int next_word_len = STR_Lenght(next_word);
    int added = STR_Joint_Separ_Str(&result, newSeparator, next_word);

    free(next_word);      // удаляем слово, оно уже не нужно
    if (!added)  // добавление не удалось, возвращаем всё что есть
      break;
    // смещаем указатель - находим начало слова, от него - конец слова
    str_ptr = STR_FindNextWord(str_ptr) + next_word_len;
  }
  return result;
}

char* ExtractUniqueWords(char const* str, char const* newSeparator)
{ // новая строка, УНИКАЛЬНЫЕ СЛОВА из str разделены новым разделителем
  char const* str_ptr = str;
  char* next_word = NULL; // очередное слово (выделено отдельно)
  char* result = AllocateString(0);    // тут накапливаем результат

  while (next_word = STR_GetFirstWord(str_ptr))
  {
    unsigned int next_word_len = STR_Lenght(next_word);

    if (STR_FindWord(result, next_word, 0) == -1) 
    { // слова ещё не было в строке
      int added = STR_Joint_Separ_Str(&result, newSeparator, next_word);
      if (!added)  // добавление не удалось, возвращаем всё что есть
      {
        free(next_word);      // удаляем слово, оно уже не нужно
        break;
      }
    }
    free(next_word);      // удаляем слово, оно уже не нужно
    // смещаем указатель - находим начало слова, от него - конец слова
    str_ptr = STR_FindNextWord(str_ptr) + next_word_len; 
  }
  return result;
}

char* ExtractUniqueLetters(char const* str, char const* newSeparator)
{ // новая строка, УНИКАЛЬНЫЕ БУКВЫ из str разделены новым разделителем
  char const* str_ptr = str;
  char* result = AllocateString(0);    // тут накапливаем результат
  char letter[] = "x";    // не создаём каждый раз строку, используем эту

  while (*(str_ptr = STR_FindNextWord(str_ptr)))
  {
    letter[0] = *str_ptr; // строка из одной буквы
    if (STR_FindWord(result, letter, 0) == -1)
    { // слова ещё не было в строке
      int added = STR_Joint_Separ_Str(&result, newSeparator, letter);
      if (!added)  // добавление не удалось, возвращаем всё что есть
        break;
    }
    str_ptr++;    // смещаем указатель - на следующую букву
  }
  return result;
}

char* FindMirrors(char const* str, char const* newSeparator)
{ // новая строка, из str удалены разделители и найдены 
  // все подстроки длиннее 1, которые есть в зеркальном виде,
  // они разделены новым разделителем
  
  char* result = AllocateString(0);          // тут накапливаем результат
  char* str_syms = STR_GetOnlyLetters(str);  // тут только буквы
  if (NULL == str_syms)                      // букв нет
    return result;
  unsigned int syms_len = STR_Lenght(str_syms);
  // не буду создавать каждый раз новые строки в цикле
  char* buff = AllocateString(syms_len);

  char* str_ptr = str_syms; // начнём с первого символа
  
  while (syms_len) // будем уменьшать оставшуюся длину
  { // создаём подстроки начиная от str_ptr и до конца строки длиной > 1
    for (unsigned int i = 2; i <= syms_len; i++)
    {
      CopySymbols(str_ptr, buff, i);                // скопировали в buff
      STR_ReverseInStr(buff, 0, i - 1);             // отзеркалили
      *(buff + i) = '\0';                           // конец строки

      if (STR_FindSubStr(str_syms, buff, 0) != -1)  // ищем во всей строке символов
      { // нашли, проверим, может слово уже есть в строке результата
        STR_ReverseInStr(buff, 0, i - 1);           // отзеркалили обратно
        if (STR_FindWord(result, buff, 0) == -1)    // это новое слово
          if (!STR_Joint_Separ_Str(&result, newSeparator, buff))
          { // сбой формирования результата, вернуть что есть
            free(buff);
            free(str_syms);
            return result;
          }
      }
    }
    str_ptr++;                   // анализировать со следующего символа
    syms_len--;                             // осталось до конца строки
  }
  free(str_syms);   // строка букв больше не нужна
  free(buff);
  return result;
}

char* FindMaskWords(char const* str, char const* mask, char const* newSeparator)
{ // новая строка, все подстроки из str по маске поиска, разделены новым разделителем
  char const* str_ptr = str;
  char* next_word = NULL; // очередное слово (выделено отдельно)
  char* result = AllocateString(0);    // тут накапливаем результат

  while (next_word = STR_GetFirstWord(str_ptr))
  {
    unsigned int next_word_len = STR_Lenght(next_word);
    if (STR_CompareByMask(next_word, mask))    // подходит по маске ?
      if (! STR_Joint_Separ_Str(&result, newSeparator, next_word))  
      { // добавление не удалось, возвращаем всё что есть
        free(next_word);      // удаляем слово, оно уже не нужно
        break;
      }
    free(next_word);      // удаляем слово, оно уже не нужно
    // смещаем указатель - находим начало слова, от него - конец слова
    str_ptr = STR_FindNextWord(str_ptr) + next_word_len;
  }
  return result;
}

char* ConvertRussian(char const* str)
{ // новая строка, транслитерация русских символов, 
  // по правилам - ПРИКАЗ МИД РФ от 29 марта 2016 г. N 4271

  char const* str_ptr = str;
  char* result = AllocateString(0);    // тут накапливаем результат
  char letter[5] = { 0 };    // не создаём каждый раз строку, используем эту

  while (*str_ptr)
  {
    letter[0] = *str_ptr; // строка из одной буквы
    letter[1] = '\0';
    STR_TransliterateSym(letter);
    int added = STR_Joint_Separ_Str(&result, "", letter);
    if (!added)  // добавление не удалось, возвращаем всё что есть
      break;
    str_ptr++;    // смещаем указатель - на следующую букву
  }
  return result;
}

// tele logo gole elemengo gote noga gano ngotole
char* STR_MakeChain(char * first_word, char * second_word)
{ // пытается состыковать слова для FindChains, иначе NULL
  char* result = NULL;
  unsigned int f_len = STR_Lenght(first_word);
  unsigned int s_len = STR_Lenght(second_word);
   
  // будем проверять слова на совпадение, постепенно сдвигая второе слово вправо
  // сдвигать, пока хотябы 2 символа перекрываются - максимально (f_len - 2)
  // первое слово должно дойти до конца, а второе - не закончится раньше первого
  // 
  for (unsigned second_shift = 0; second_shift <= (f_len - 2); second_shift++)
  {
    char* f_ptr = first_word + second_shift;  // сдвиг второго слова отражается на первом :-)
    char* s_ptr = second_word;

    // пока не кончилось первое слово И идёт совпадение
    while (*f_ptr && (*(f_ptr) == *(s_ptr))) { 
      f_ptr++; 
      s_ptr++;
    }

    if ((*f_ptr) == 0) // достигнут конец первого слова, а не найдено различие
    { // второе слово полностью, первое - только символы вначале, т.е. до second_shift
#ifdef DEBUG
      printf(" == shift >> [%d] ", second_shift);
#endif // DEBUG
      result = AllocateString(s_len + second_shift);
      // первое слово - копируем то, что не входит во второе
      if (second_shift) CopySymbols(first_word, result, second_shift);
      CopySymbols(second_word, result + second_shift, s_len + 1); // с концом строки 0
      break; // дальше не искать, первым будет найдено самое длинное совпадение
    }
  }
  return result;
}

char* FindChains(char const* str, char const* newSeparator)
{ // новая строка, задание Поиск цепочек - склеивает слова
  // если 2 слова совпадают конец одного и начало другого (более 1 символа)

  char* first_word = NULL;   // очередное слово (выделено отдельно)
  char* second_word = NULL;  // очередное слово (выделено отдельно)
  char* next_word = NULL;    // новое составное слово (выделено отдельно)
  char* result = AllocateString(0);    // тут накапливаем результат

  // тут будут слова из строки
  char* words = ExtractWords(str, newSeparator);

  // Просто проверю каждый с каждым :-)
  char* first_p = words;
  unsigned first_num = 0; // будем считать слова, чтобы не соединять слово само с собой
  while (first_word = STR_GetFirstWord(first_p))
  {
    first_num++; // новое первое слово
    unsigned int first_word_len = STR_Lenght(first_word);
    if (first_word_len > 1)
    {
      // тут цикл проверка сочетания со всеми остальными
      char* second_p = words;
      unsigned second_num = 0;
      while (second_word = STR_GetFirstWord(second_p))
      {
        second_num++;
        unsigned int second_word_len = STR_Lenght(second_word);
        if (second_word_len > 1)
        {
          if (first_num != second_num) // не проверяем слово само с собой
          { 
#ifdef DEBUG
            printf("\n[%s] + [%s]", first_word, second_word);
#endif // DEBUG

            if (NULL != (next_word = STR_MakeChain(first_word, second_word)))
            { // удалось сделать цепочку
#ifdef DEBUG
              printf(" == FOUND [%s] ", next_word);
#endif // DEBUG
              if (STR_FindWord(result, next_word, 0) == -1)
              { // слова ещё не было в строке
                int added = STR_Joint_Separ_Str(&result, newSeparator, next_word);
                if (!added)  // добавление не удалось, возвращаем всё что есть
                {
                  free(first_word);
                  free(second_word);
                  free(next_word);      // удаляем слово, оно уже не нужно
                  break;
                }
              }
              free(next_word);
            }
          }
        }
        free(second_word);
        second_p = STR_FindNextWord(second_p) + second_word_len;
      }
    }
    free(first_word);      // удаляем слово, оно уже не нужно
    // смещаем указатель - находим начало слова, от него - конец слова
    first_p = STR_FindNextWord(first_p) + first_word_len;
  }
  return result;
}

char* STR_JustifyLeft(char* str, unsigned width)
{ // возврат - новая строка, где str разбита на строки шириной width
  // несколько пробелов подряд заменяются на один пробел, выравнование - влево
  // между строками - \n, если слово > width, оно разбивается на куски

  char* cropSP = OnlyOneSpace(str); // сокращаю подряд идущие пробелы

#ifdef DEBUG
  printf("\n Source string\n%s\n", cropSP);
  char* ruller = "0123456789";
  for (unsigned i = 0; i < width; i++)
    printf("%c", *(ruller + i % 10));     // добавить линейку
  printf("\n");
#endif // DEBUG


  char* result = NULL;
  char* result_ptr = result;
  unsigned result_len = 0;
  char* ptr = cropSP;
  unsigned count_in_line = 0;
 
  while (*ptr) // до конца строки
  {
    char* nextWord = STR_FindNextWord(ptr);   // следующее слово
    unsigned sepWidth = nextWord - ptr;       // символов до слова
    if (sepWidth) // есть разделители
    {
      // надо добавить это + возможно несколько '\n'
      unsigned add_length = sepWidth + (count_in_line + sepWidth) / width;
      unsigned count_added = 0;
      char* new_result = (char*)realloc(result, result_len + add_length + 1);
      if (NULL == new_result) break;
      
      result = new_result;
      result_ptr = result + result_len;

      for (int i = sepWidth; i; i--) // копируем разделители
      {
        if (count_in_line == 0 && *ptr == ' ') // если пробел попал в начало строки не добавлять его
          ptr++;
        else
        {
          *result_ptr++ = *ptr++;       // тут копирование символа
          count_added++;
          if (++count_in_line >= width) // увеличиваем счётчик символов в строке
          {
            // если в конце строчки был пробел удалить его
            if (*(result_ptr - 1) == ' ')
              *(result_ptr - 1) = '\n';
            else
            {
              *result_ptr++ = '\n';       // начать новую строку
              count_added++;
            }
            count_in_line = 0;
          }
        }
      }
      result_len += count_added;
    }

    if (*ptr) // это ещё слово, а не конец строки
    { // 3 варианта
      char* next_separ = STR_FindNextSeparator(ptr);
      unsigned word_len = next_separ - ptr;
      
      // слово не помещается в строке 
      if (count_in_line + word_len > width)
        if (word_len < width)     //слово меньше ширины строки, 
          // ставим счётчик символов в строке на конец строки,
          count_in_line = width;
      // иначе, либо слово помещается, очень хорошо
      // либо слово шире строки, будем его разбивать

      unsigned add_length = word_len + (count_in_line + word_len) / width;
      char* new_result = (char*)realloc(result, result_len + add_length + 1);
      if (NULL == new_result)  break;
      result = new_result;
      result_ptr = result + result_len;
      unsigned count_added = 0;
      
      for (int i = word_len; i; i--) // копируем 
      {
        if (count_in_line == width)  // конец строки
        {
          // если в конце строчки был пробел удалить его
          if (*(result_ptr - 1) == ' ')
            *(result_ptr - 1) = '\n';
          else
          {
            *result_ptr++ = '\n';       // начать новую строку
            count_added++;
          }
          count_in_line = 0;
        }
        count_in_line++;
        *result_ptr++ = *ptr++;       // тут копирование символа
        count_added++;
      }
      result_len += count_added;
    }
  }

  free(cropSP);
  *result_ptr = '\0';
  return result;
}

char* STR_JustifyWidth(char* str, unsigned width)
{ // возврат - новая строка, где str разбита на строки шириной width
  // выравнивание- по ширине, изменяя количество пробелов
  // между строками - \n, если слово > width, оно разбивается на куски
  
  char* cropSP = OnlyOneSpace(str);   // сокращу пробелы, чтоб не мешались
  if (NULL == cropSP) return NULL;

  char* buffer = (char*)malloc(width + 2);   // тут буду формировать очередную строчку
  if (NULL == buffer) return NULL;    // +1 для '\n'   и   +1 для '\0'

  // сначала разобью на строчки с выравниванием влево, 
  // потом выравняю по ширине каждую строчку
  char* str_j_left = STR_JustifyLeft(cropSP, width);
  free(cropSP);                       // это уже не нужно
  if (NULL == str_j_left) return NULL;
  
  // количество строчек, возьму с запасом +1 если последняя строчка не полная
  int num_lines = CountChar(str_j_left, '\n') + 1;
  // сколько байт нужно, если все строчки будут длиной width + '\n'
  int result_len = num_lines * (width + 1) + 1;   // + конец строки '\0'

  char* result = (char*)malloc(result_len);
  if (NULL == result) { free(str_j_left); return NULL; }
  
  char* ptr = str_j_left;
  char* result_ptr = result;
 
  while (*ptr) //до конца строки
  {
    char* nextCR = FindChar(ptr, '\n', 0);  // следующий '\n' или конец строки '\0'
    if (*nextCR == '\0')
    { // последнюю строчку не выравнивать, просто скопирую
      while (*ptr) *(result_ptr++) = *(ptr++); // тут копирование
      break;
    }
      
    unsigned int line_len = nextCR - ptr;
    CopySymbols(ptr, buffer, line_len);     // скопирую в буфер очередную строку(без \n)
    *(buffer + line_len) = '\0';            // дополню признаком конца строки

#ifdef DEBUG
      printf("\nBUFFER [%s] длина %d", buffer, line_len);
#endif // DEBUG

    if (line_len < width)                   // строку надо расширить
    {
      unsigned int countSpace = CountChar(buffer, ' '); // считаем пробелы в этой строке
      unsigned delta = width - line_len;                // сколько всего добавить пробелов
      if (countSpace) // в строке есть пробелы, будем их увеличивать
      {
        unsigned plusSP = delta / countSpace;      // сколько добавить к каждому имеющемуся пробелу
        unsigned plusSP_special = delta - plusSP * countSpace; // это остаток, добавлять не к каждому
        int count_in_line = 0;
        for (unsigned i = 0; i < line_len; i++)
        {
          if (buffer[i] != ' ')
          { *(result_ptr++) = buffer[i];
#ifdef DEBUG
              printf("%c", buffer[i]);
#endif // DEBUG
            
          }
          else
          { 
            count_in_line++;                    // считаем промежутки
            for (unsigned j = 0; j <= plusSP; j++)   // в этом промежутке пробел стал больше
            { *(result_ptr++) = ' ';
#ifdef DEBUG
                printf("#"); // добавлен пробел из числа "как у всех промежутков"
#endif // DEBUG                
               
            }
            // вот тут раскидываются пробелы неравномерно, не в каждый промежуток
            if (plusSP_special && count_in_line * plusSP_special % countSpace == 0)
            {
#ifdef DEBUG
                printf("*");   // этот пробел "особенный, не как все"
#endif // DEBUG                         
              *(result_ptr++) = ' '; // доплонительный пробел
            }
          }
        }
      }
      else  // в строке 1 слово и нет пробелов, допишем их в конец
      {     // или не дополнять пробелам ?? дополню
        unsigned int delta = width - line_len;
        while (delta--)
          *(buffer + line_len + delta) = ' ';
        // в буфере строка, но без \n \0
        CopySymbols(buffer, result_ptr, width); // в резалт её
        result_ptr += width;                    // сдвину указатель в резалт
#ifdef DEBUG
          printf("\nBUFFER [%s] just add %d SP", buffer, width-line_len);
#endif // DEBUG

      }
    }
    else
    { // в буфере строка нужной длины, но без \n \0
      CopySymbols(buffer, result_ptr, width); // в резалт её
      result_ptr += width;                    // сдвину указатель в резалт

#ifdef DEBUG
        printf("\nBUFFER [%s] do nothing", buffer);
#endif // DEBUG
    }        
    *(result_ptr++) = '\n';                 // добавить перевод строки
    ptr += line_len;      // сдвинуть указатель в исходной строке
    if (*ptr == '\n')     // сдвинуть ещё, если там \n
      ptr++;
  }
 
  free(str_j_left);
  *result_ptr = '\0';  // добавить конец строки
  return result;
}
