#pragma once

// Челнокова Екатерина, гр 3630102/90004
// общие строковые функции - заголовки

int IsAlNum(char c);
// определяет, что является допустимой буквой в данной задаче
// реализовано в основном модуле

int StrLenght(char str[]); 
// длина строки до '\0'

void CopySubStr(char str[], int start, int end, char subStr[]); 
// кусок str[start...end] -> записывает в начало subStr
// конец строки  '\0' никак не проверяется и в subStr не дополняется

char* CopyStr(char strFrom[], char strTo[]);
// копирует строку до '\0' включая, возвращает указатель на strTo

void RemoveSubStr(char str[], int start, int end);
// из str вырезается кусок [start...end], остаток строки сдвигается

int RemoveAll(char str[], char subStr[]);
// удаляет все вхождения subStr, возвращает количество удалений

int RemoveAllWords(char str[], char word[]);
// удаляет все вхождения word, возвращает количество удалений
// в отличии от RemoveAll удаляет только целые слова, вокруг - разделители / концы строки

int ReplaceAllWords(char str[], char word[], char replace[]);
// заменяет в строке str цельное слово word (вокруг - разделители или концы строки)
// -на-> replace (! заменяется не больше сиимволов чем длина word)
// т.е. строка str - может только сокращаться, НЕ УВЕЛИЧИВАЕТСЯ
// возврат - количество замен


int RemoveSeparators(char str[]);
// Удаляет все НЕбуквы (IsAlNum() == 0), возвращает количество удалённых символов

int RemoveSymbols(char str[]);
// Удаляет все буквы (IsAlNum() == 1), возвращает количество удалённых символов

int CompareStr(char str1[], char str2[], int len);
// сравнивает строки на длину len символов
// возврат = 1 - равны, 0 - нет

int CompareStrIgnoreCase(char str1[], char str2[], int len);
// сравнивает строки на длину len символов, [a-z] == [A-Z] 	
// возврат = 1 - равны, 0 - нет

char LowerChar(char c); 
// возвращает 1 символ [A–Z] -> [a–z], или не меняет

char UpperChar(char c);
// возвращает 1 символ [a–z] -> [A–Z], или не меняет

void LowerCase(char str[]);
// заменяет символы строки [A–Z] -> на аналоги из [a–z]

void UpperCase(char str[]);
// заменяет символы строки [a–z] -> [A–Z]

void SwapCase(char str[]); 
// меняет регистр букв [a–z] <-> [A–Z]

void TitleCase(char str[]);
// Делает заглавными первые буквы слов, остальные строчными [a–z] <-> [A–Z]

int FindWordEnd(char str[], int start);
// в строке с позиции start, находит позицию последней буквы слова

int FindNextWord(char str[], int pos);
// в str с позиции pos, находит позицию следующей буквы или конца строки

int FindNextSeparator(char str[], int pos); 
// в str с позиции pos, находит позицию следующей НЕбуквы или конца строки

void ReverseInStr(char str[], int start, int end);
// str[start...end] <- str[end...start] , т.е. в обратном порядке

void Reverse(char str[]);
// разворачивает строку задом наперёд

void ShiftLeftInStr(char str[], int start, int end, int shift);
// на участке [start...end] символы циклически сдвигаются влево, к началу строки
// shift - величина сдвига, обрезаем по модулю длины этого участка

void ShiftRightInStr(char str[], int start, int end, int shift);
// на участке [start...end] символы циклически сдвигаются вправо, к концу строки
// shift - величина сдвига, обрезаем по модулю длины этого участка

void FillStr(char str[], int start, int end, char filler);
// заполняет str[start...end] символом filler
