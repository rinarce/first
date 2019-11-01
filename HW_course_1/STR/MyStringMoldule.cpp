// ��������� ���������, �� 3630102/90004
// ����� ��������� ������� - ����������
#include ".\MyStringModule.h"

int CharIsAlNum(char c); 
// ����������, ��� �������� ���������� ������ � ������ ������
// ����������� � �������� ������

int StrLenght(char str[]) {  // ����� ������ �� '\0'
	int len = 0;
	while (str[len]) len++;
	return len;
}

char LowerChar(char c) { // ���������� 1 ������ [A�Z] -> [a�z], ��� �� ������
	if (c >= 'A' && c <= 'Z') c += 32;
	return c;
}

char UpperChar(char c) { // ���������� 1 ������ [a�z] -> [A�Z], ��� �� ������
	if (c >= 'a' && c <= 'z') c -= 32;
	return c;
}

void LowerCase(char str[]) { // �������� ������� ������ [A�Z] -> �� ������� �� [a�z]
	for (int pos = 0; str[pos]; pos++)
		str[pos] = LowerChar(str[pos]);
}

void UpperCase(char str[]) { // �������� ������� ������ [a�z] -> [A�Z]
	for (int pos = 0; str[pos]; pos++)
		str[pos] = UpperChar(str[pos]);
}

void SwapCase(char str[]) { // ������ ������� ���� [a�z] <-> [A�Z]
	for (int pos = 0; str[pos]; pos++) {
		char sym = str[pos];
		if (sym >= 'a' && sym <= 'z') str[pos] -= 32;
		else if (sym >= 'A' && sym <= 'Z') str[pos] += 32;
	}
}

void CopySubStr(char str[], int start, int end, char subStr[]) {
	// ����� str[start...end] -> ���������� � ������ subStr
	// ����� ������  '\0' ����� �� ����������� � � subStr �� �����������
	for (int pos = 0; start <= end; subStr[pos++] = str[start++]) {}
}

char * CopyStr(char strFrom[], char strTo[]) {
	// �������� ������ �� '\0' �������, ���������� ��������� �� strTo
	int pos = 0;
	do {} 
	while (strTo[pos++] = strFrom[pos]);
	return strTo; // ��� ��������
}

void RemoveSubStr(char str[], int start, int end) {
	// �� str ���������� ����� [start...end], ������� ������ ����������
	int p1 = start, p2 = end + 1;
	do {}		// ����������, ���� �� ��������� ������ '\0'
	while (str[p1++] = str[p2++]);
}

int CompareStr(char str1[], char str2[], int len) {
	// ���������� ������ �� ����� len ��������, ������� = 1 - �����, 0 - ���
	for (int i = 0; i < len; i++)	// �� ������� ������������
		if (str1[i] != str2[i]) return 0;
	return 1; // �� �������
}

int CompareStrIgnoreCase(char str1[], char str2[], int len) {
	// ���������� ������ �� ����� len ��������, [a-z] == [A-Z]
	// ������� = 1 - �����, 0 - ���
	for (int i = 0; i < len; i++)	// �� ������� ������������
		if (LowerChar(str1[i]) != LowerChar(str2[i])) return 0;
	return 1; // �� �������
}

int RemoveAll(char str[], char subStr[]) {
	// ������� ��� ��������� subStr, ���������� ���������� ��������
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
	// ������� ��� ��������� word, ���������� ���������� ��������
	// � ������� �� RemoveAll ������� ������ ����� �����, ������ - ����������� ��� ����� ������
	int deleted = 0;
	int subLen = StrLenght(word);
	for (int pos = FindNextWord(str, 0); str[pos]; ) {
		if (CompareStr(&str[pos], word, subLen) && !CharIsAlNum(str[pos + subLen])) {
			RemoveSubStr(str, pos, pos + subLen - 1);
			deleted++;
		}
		pos = FindNextWord(str, FindNextSeparator(str, pos));
	}
	return deleted;
}

int ReplaceAllWords(char str[], char word[], char replace[]) {
	// �������� � ������ str ������� ����� word (������ - ����������� ��� ����� ������)
	// word -��-> replace (!!! ���������� �� ������ ��������� ��� ����� word !)
	// �.�. ������ str - ����� ������ �����������, �� �������������
	// ������� - ���������� �����

	int replaced = 0;
	int wordLen = StrLenght(word), replaceLen = StrLenght(replace);
	if (replaceLen > wordLen) replaceLen = wordLen; // �������� �� ����� ��������� �����
	int delta = wordLen - replaceLen;				// ������� � ����� (��� ���������� replace)
	for (int pos = FindNextWord(str, 0); str[pos]; ) {
		if (CompareStr(&str[pos], word, replaceLen) && !CharIsAlNum(str[pos + wordLen])) {
			CopySubStr(replace, 0, replaceLen-1, &str[pos]);
			replaced++;
			if (delta)  // ����� ������ �����, ���������� �������� ������
				RemoveSubStr(str, pos + replaceLen, pos + replaceLen + delta - 1);
		}
		pos = FindNextWord(str, FindNextSeparator(str, pos));
	}
	return replaced;
}

int FindWordEnd(char str[], int start) {
	// � ������ � ������� start, ������� ������� ��������� ����� �����
	int end = start;
	while ((str[end]) && CharIsAlNum(str[end])) end++;
	// ������ end ��������� �� ������� ��� ����� ������ \0,
	return --end;   // ������� ��������� end
}

int FindNextWord(char str[], int pos) {
	// � str � ������� pos, ������� ������� ��������� ����� ��� ����� ������
	while ((str[pos]) && ! CharIsAlNum(str[pos])) pos++;
	return pos;
}

int FindNextSeparator(char str[], int pos) {
	// � str � ������� pos, ������� ������� ��������� ������� ��� ����� ������
	while ((str[pos]) && CharIsAlNum(str[pos])) pos++;
	return pos;
}

void ReverseInStr(char str[], int start, int end) {
	// str[start...end] <- str[end...start] , �.�. � �������� �������
	while (start <= end) {
		char temp = str[start];
		str[start++] = str[end];
		str[end--] = temp;
	}
}

void ShiftLeftInStr(char str[], int start, int end, int shift) {
	// �� ������� [start...end] ������� ���������� ���������� �����, � ������ ������
	// shift - �������� ������, �������� �� ������ ����� ����� �������
    // https://codelib.ru/task/cycle_shift/ ������� 3
	int intervalLen = end - start + 1;
	if (intervalLen <= 1) return;
	shift = shift % (intervalLen);
	if (! shift) return;	// ������ �� ������
	
	// ��� �������� ���������� ����� ����� � ������ ��������� [start...end]
	char * interval = &str[start];		
	//  ������ ��� shift = 3, intervalLen = 8, ������� [0...7]
	//	012 34567	   
    //  210             1. reverse[0..2]
    //      76543       2. reverse[3..7]
	//	345 67012       3. reverse[0..7] all interval
    ReverseInStr(interval, 0, shift - 1);
    ReverseInStr(interval, shift, intervalLen - 1);
    ReverseInStr(interval, 0, intervalLen - 1);
}


void ShiftRightInStr(char str[], int start, int end, int shift) {
    // �� ������� [start...end] ������� ���������� ���������� ������, � ����� ������
    // shift - �������� ������, �������� �� ������ ����� ����� �������
    int intervalLen = end - start + 1;
    if (intervalLen <= 1) return;
    shift = shift % (intervalLen);
    if (!shift) return;	// ������ �� ������
    // ������ � ������ �����
    ShiftLeftInStr(str, start, end, intervalLen - shift);
}

void Reverse(char str[]) { // ������������� ������ ����� ������
	ReverseInStr(str, 0, StrLenght(str) - 1);
}

int RemoveSeparators(char str[]) {
	// ������� ��� ������� (_charIsAlNum() == 0), ���������� ���������� �������� ��������
	int deleted = 0;
	for (int pos = FindNextSeparator(str, 0); str[pos]; ) {
		int next = FindNextWord(str, pos); // c��� ����� ��� ����� ������
		RemoveSubStr(str, pos, next - 1);
		deleted += next - pos;
		// ���� ��������� ��� ����� ������, � ����� � �������� �������
		pos = FindNextSeparator(str, pos);
	}
	return deleted;
}

int RemoveSymbols(char str[]) {
	// ������� ��� ����� (_charIsAlNum() == 1), ���������� ���������� �������� ��������
	int deleted = 0;
	for (int pos = FindNextWord(str, 0); str[pos]; ) {
		int next = FindNextSeparator(str, pos); // c��� ������� ��� ����� ������
		RemoveSubStr(str, pos, next - 1);
		deleted += next - pos;
		// ���� ��������� ��� ����� ������, � ����� � �������� �������
		pos = FindNextWord(str, pos);
	}
	return deleted;
}

void TitleCase(char str[]) {
	// ������ ���������� ������ ����� ����. ��������� ���������
	// ������� ������� ��� ���������, ����� ������� ���������
	LowerCase(str);
	for (int pos = FindNextWord(str, 0); str[pos]; ) {
		str[pos] = UpperChar(str[pos]);
		pos = FindNextWord(str, FindNextSeparator(str, pos));
	}
}

void FillStr(char str[], int start, int end, char filler) {
	// ��������� str[start...end] �������� filler
	while (start <= end)
		str[start++] = filler;
}


// ������� ��������� � ������ ������� X, ��� ����� ������ '\0'
char* StrFindChar(char const* str, char x, int start) 
{
  str += start;                          // �������� �� ������ ������
  while (*str)
    if (x == (*str)) return (char*)str;  // ����� ����� ������� ���������� �
    else ++str;
  return (char*)str;                     // ��� ����� ����� ����� ������ '\0'
}
