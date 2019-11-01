#pragma once

// ��������� ���������, �� 3630102/90004
// ����� ��������� ������� - ���������

int CharIsAlNum(char c);
// ����������, ��� �������� ���������� ������ � ������ ������
// ����������� � �������� ������

int StrLenght(char str[]); 
// ����� ������ �� '\0'

void CopySubStr(char str[], int start, int end, char subStr[]); 
// ����� str[start...end] -> ���������� � ������ subStr
// ����� ������  '\0' ����� �� ����������� � � subStr �� �����������

char* CopyStr(char strFrom[], char strTo[]);
// �������� ������ �� '\0' �������, ���������� ��������� �� strTo

void RemoveSubStr(char str[], int start, int end);
// �� str ���������� ����� [start...end], ������� ������ ����������

int RemoveAll(char str[], char subStr[]);
// ������� ��� ��������� subStr, ���������� ���������� ��������

int RemoveAllWords(char str[], char word[]);
// ������� ��� ��������� word, ���������� ���������� ��������
// � ������� �� RemoveAll ������� ������ ����� �����, ������ - ����������� / ����� ������

int ReplaceAllWords(char str[], char word[], char replace[]);
// �������� � ������ str ������� ����� word (������ - ����������� ��� ����� ������)
// -��-> replace (! ���������� �� ������ ��������� ��� ����� word)
// �.�. ������ str - ����� ������ �����������, �� �������������
// ������� - ���������� �����


int RemoveSeparators(char str[]);
// ������� ��� ������� (_charIsAlNum() == 0), ���������� ���������� �������� ��������

int RemoveSymbols(char str[]);
// ������� ��� ����� (_charIsAlNum() == 1), ���������� ���������� �������� ��������

int CompareStr(char str1[], char str2[], int len);
// ���������� ������ �� ����� len ��������
// ������� = 1 - �����, 0 - ���

int CompareStrIgnoreCase(char str1[], char str2[], int len);
// ���������� ������ �� ����� len ��������, [a-z] == [A-Z] 	
// ������� = 1 - �����, 0 - ���

char LowerChar(char c); 
// ���������� 1 ������ [A�Z] -> [a�z], ��� �� ������

char UpperChar(char c);
// ���������� 1 ������ [a�z] -> [A�Z], ��� �� ������

void LowerCase(char str[]);
// �������� ������� ������ [A�Z] -> �� ������� �� [a�z]

void UpperCase(char str[]);
// �������� ������� ������ [a�z] -> [A�Z]

void SwapCase(char str[]); 
// ������ ������� ���� [a�z] <-> [A�Z]

void TitleCase(char str[]);
// ������ ���������� ������ ����� ����, ��������� ��������� [a�z] <-> [A�Z]

int FindWordEnd(char str[], int start);
// � ������ � ������� start, ������� ������� ��������� ����� �����

int FindNextWord(char str[], int pos);
// � str � ������� pos, ������� ������� ��������� ����� ��� ����� ������

int FindNextSeparator(char str[], int pos); 
// � str � ������� pos, ������� ������� ��������� ������� ��� ����� ������

void ReverseInStr(char str[], int start, int end);
// str[start...end] <- str[end...start] , �.�. � �������� �������

void Reverse(char str[]);
// ������������� ������ ����� ������

void ShiftLeftInStr(char str[], int start, int end, int shift);
// �� ������� [start...end] ������� ���������� ���������� �����, � ������ ������
// shift - �������� ������, �������� �� ������ ����� ����� �������

void ShiftRightInStr(char str[], int start, int end, int shift);
// �� ������� [start...end] ������� ���������� ���������� ������, � ����� ������
// shift - �������� ������, �������� �� ������ ����� ����� �������

void FillStr(char str[], int start, int end, char filler);
// ��������� str[start...end] �������� filler
