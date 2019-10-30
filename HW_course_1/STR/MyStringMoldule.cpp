// Челнокова Екатерина, гр 3630102/90004
// общие строковые функции - реализация
#include ".\MyStringModule.h"

int IsAlNum(char c); 
// определяет, что является допустимой буквой в данной задаче
// реализовано в основном модуле

int StrLenght(char str[]) {  // длина строки до '\0'
	int len = 0;
	while (str[len]) len++;
	return len;
}

char LowerChar(char c) { // возвращает 1 символ [A–Z] -> [a–z], или не меняет
	if (c >= 'A' && c <= 'Z') c += 32;
	return c;
}

char UpperChar(char c) { // возвращает 1 символ [a–z] -> [A–Z], или не меняет
	if (c >= 'a' && c <= 'z') c -= 32;
	return c;
}

void LowerCase(char str[]) { // заменяет символы строки [A–Z] -> на аналоги из [a–z]
	for (int pos = 0; str[pos]; pos++)
		str[pos] = LowerChar(str[pos]);
}

void UpperCase(char str[]) { // заменяет символы строки [a–z] -> [A–Z]
	for (int pos = 0; str[pos]; pos++)
		str[pos] = UpperChar(str[pos]);
}

void SwapCase(char str[]) { // меняет регистр букв [a–z] <-> [A–Z]
	for (int pos = 0; str[pos]; pos++) {
		char sym = str[pos];
		if (sym >= 'a' && sym <= 'z') str[pos] -= 32;
		else if (sym >= 'A' && sym <= 'Z') str[pos] += 32;
	}
}

void CopySubStr(char str[], int start, int end, char subStr[]) {
	// кусок str[start...end] -> записывает в начало subStr
	// конец строки  '\0' никак не проверяется и в subStr не дополняется
	for (int pos = 0; start <= end; subStr[pos++] = str[start++]) {}
}

char * CopyStr(char strFrom[], char strTo[]) {
	// копирует строку до '\0' включая, возвращает указатель на strTo
	int pos = 0;
	do {} 
	while (strTo[pos++] = strFrom[pos]);
	return strTo; // для удобства
}

void RemoveSubStr(char str[], int start, int end) {
	// из str вырезается кусок [start...end], остаток строки сдвигается
	int p1 = start, p2 = end + 1;
	do {}		// копировать, пока на скопируем символ '\0'
	while (str[p1++] = str[p2++]);
}

int CompareStr(char str1[], char str2[], int len) {
	// сравнивает строки на длину len символов, возврат = 1 - равны, 0 - нет
	for (int i = 0; i < len; i++)	// до первого несовпадения
		if (str1[i] != str2[i]) return 0;
	return 1; // всё совпало
}

int CompareStrIgnoreCase(char str1[], char str2[], int len) {
	// сравнивает строки на длину len символов, [a-z] == [A-Z]
	// возврат = 1 - равны, 0 - нет
	for (int i = 0; i < len; i++)	// до первого несовпадения
		if (LowerChar(str1[i]) != LowerChar(str2[i])) return 0;
	return 1; // всё совпало
}

int RemoveAll(char str[], char subStr[]) {
	// удаляет все вхождения subStr, возвращает количество удалений
	int deleted = 0;
	int subLen = StrLenght(subStr);
	for (int pos = 0; str[pos]; pos++)
		if (CompareStr(&str[pos], subStr, subLen)) {
			RemoveSubStr(str, pos, pos + subLen - 1);
			deleted ++;
		}
	return deleted;
}

int RemoveAllWords(char str[], char word[]) {
	// удаляет все вхождения word, возвращает количество удалений
	// в отличии от RemoveAll удаляет только целые слова, вокруг - разделители или концы строки
	int deleted = 0;
	int subLen = StrLenght(word);
	for (int pos = FindNextWord(str, 0); str[pos]; ) {
		if (CompareStr(&str[pos], word, subLen) && !IsAlNum(str[pos + subLen])) {
			RemoveSubStr(str, pos, pos + subLen - 1);
			deleted++;
		}
		pos = FindNextWord(str, FindNextSeparator(str, pos));
	}
	return deleted;
}

int ReplaceAllWords(char str[], char word[], char replace[]) {
	// заменяет в строке str цельное слово word (вокруг - разделители или концы строки)
	// word -на-> replace (!!! заменяется не больше сиимволов чем длина word !)
	// т.е. строка str - может только сокращаться, НЕ УВЕЛИЧИВАЕТСЯ
	// возврат - количество замен

	int replaced = 0;
	int wordLen = StrLenght(word), replaceLen = StrLenght(replace);
	if (replaceLen > wordLen) replaceLen = wordLen; // образаем по длине исходного слова
	int delta = wordLen - replaceLen;				// разница в длине (уже обрезаного replace)
	for (int pos = FindNextWord(str, 0); str[pos]; ) {
		if (CompareStr(&str[pos], word, replaceLen) && !IsAlNum(str[pos + wordLen])) {
			CopySubStr(replace, 0, replaceLen-1, &str[pos]);
			replaced++;
			if (delta)  // слова разной длины, необходима подрезка строки
				RemoveSubStr(str, pos + replaceLen, pos + replaceLen + delta - 1);
		}
		pos = FindNextWord(str, FindNextSeparator(str, pos));
	}
	return replaced;
}

int FindWordEnd(char str[], int start) {
	// в строке с позиции start, находит позицию последней буквы слова
	int end = start;
	while ((str[end]) && IsAlNum(str[end])) end++;
	// сейчас end указывает на небукву или конец строки \0,
	return --end;   // поэтому уменьшаем end
}

int FindNextWord(char str[], int pos) {
	// в str с позиции pos, находит позицию следующей буквы или конца строки
	while ((str[pos]) && ! IsAlNum(str[pos])) pos++;
	return pos;
}

int FindNextSeparator(char str[], int pos) {
	// в str с позиции pos, находит позицию следующей НЕбуквы или конца строки
	while ((str[pos]) && IsAlNum(str[pos])) pos++;
	return pos;
}

void ReverseInStr(char str[], int start, int end) {
	// str[start...end] <- str[end...start] , т.е. в обратном порядке
	while (start <= end) {
		char temp = str[start];
		str[start++] = str[end];
		str[end--] = temp;
	}
}

void ShiftLeftInStr(char str[], int start, int end, int shift) {
	// на участке [start...end] символы циклически сдвигаются влево, к началу строки
	// shift - величина сдвига, обрезаем по модулю длины этого участка
    // https://codelib.ru/task/cycle_shift/ вариант 3
	int intervalLen = end - start + 1;
	if (intervalLen <= 1) return;
	shift = shift % (intervalLen);
	if (! shift) return;	// ничего не делать
	
	// для удобства индексации новый адрес с начала интервала [start...end]
	char * interval = &str[start];		
	//  пример для shift = 3, intervalLen = 8, индексы [0...7]
	//	012 34567	   
    //  210             1. reverse[0..2]
    //      76543       2. reverse[3..7]
	//	345 67012       3. reverse[0..7] all interval
    ReverseInStr(interval, 0, shift - 1);
    ReverseInStr(interval, shift, intervalLen - 1);
    ReverseInStr(interval, 0, intervalLen - 1);
}


void ShiftRightInStr(char str[], int start, int end, int shift) {
    // на участке [start...end] символы циклически сдвигаются вправо, к концу строки
    // shift - величина сдвига, обрезаем по модулю длины этого участка
    int intervalLen = end - start + 1;
    if (intervalLen <= 1) return;
    shift = shift % (intervalLen);
    if (!shift) return;	// ничего не делать
    // сводим к сдвигу влево
    ShiftLeftInStr(str, start, end, intervalLen - shift);
}

void Reverse(char str[]) { // разворачивает строку задом наперёд
	ReverseInStr(str, 0, StrLenght(str) - 1);
}

int RemoveSeparators(char str[]) {
	// Удаляет все НЕбуквы (IsAlNum() == 0), возвращает количество удалённых символов
	int deleted = 0;
	for (int pos = FindNextSeparator(str, 0); str[pos]; ) {
		int next = FindNextWord(str, pos); // cлед буква или конец строки
		RemoveSubStr(str, pos, next - 1);
		deleted += next - pos;
		// ищем следующее или конец строки, с места с которого удалили
		pos = FindNextSeparator(str, pos);
	}
	return deleted;
}

int RemoveSymbols(char str[]) {
	// Удаляет все буквы (IsAlNum() == 1), возвращает количество удалённых символов
	int deleted = 0;
	for (int pos = FindNextWord(str, 0); str[pos]; ) {
		int next = FindNextSeparator(str, pos); // cлед НЕбуква или конец строки
		RemoveSubStr(str, pos, next - 1);
		deleted += next - pos;
		// ищем следующее или конец строки, с места с которого удалили
		pos = FindNextWord(str, pos);
	}
	return deleted;
}

void TitleCase(char str[]) {
	// Делает заглавными первые буквы слов. остальные строчными
	// сначала сделаем все строчными, потом выделим заглавные
	LowerCase(str);
	for (int pos = FindNextWord(str, 0); str[pos]; ) {
		str[pos] = UpperChar(str[pos]);
		pos = FindNextWord(str, FindNextSeparator(str, pos));
	}
}

void FillStr(char str[], int start, int end, char filler) {
	// заполняет str[start...end] символом filler
	while (start <= end)
		str[start++] = filler;
}


// находит вхождение в строку символа X, или конец строки '\0'
char* str_find_char(char const* str, char x, int start) 
{
  str += start;                          // смещение от начала строки
  while (*str)
    if (x == (*str)) return (char*)str;  // вернёт адрес первого найденного Х
    else ++str;
  return (char*)str;                     // тут вернёт адрес концы строки '\0'
}
