#ifndef DST_FUNCTIONS_H_INCLUDED__
#define DST_FUNCTIONS_H_INCLUDED__
#pragma once

// ������ ������ ������������ �����, �������������� �������� ������
// � *str ���������� ��������� �� ������, return ���������� ����� ������
unsigned int DstInputStr(char** str, char const* text);

// ����� ������, ����� �� str ��������� ����� ������������
char* ExtractWords(char const* str, char const* newSeparator);

// ����� ������, ���������� ����� �� str ��������� ����� ������������
char* ExtractUniqueWords(char const* str, char const* newSeparator);

// ����� ������, ����� �� str ��������� ����� ������������
char* ExtractLetters(char const* str, char const* newSeparator);

// ����� ������, ���������� ����� �� str ��������� ����� ������������
char* ExtractUniqueLetters(char const* str, char const* newSeparator);

// �� str ����� ������ ����� � ����� ��������� ������
char* StrGetOnlyLetters(char const* str);

// ����� ������, �� str ������� ����������� � ������� 
// ��� ��������� ������� 1, ������� ���� � ���������� ����,
// ��� ��������� ����� ������������
char* FindMirrors(char const* str, char const* newSeparator);

// ����� ������, ��� ��������� �� str �� ����� ������, ��������� ����� ������������
char* FindMaskWords(char const* str, char const* mask, char const* newSeparator);

// ����� ������, �������������� ������� ��������, 
// �� �������� - ������ ��� �� �� 29 ����� 2016 �. N 4271
char* ConvertRussian(char const* str);

// ����� ������, ������� ����� ������� - ��������� �����
// ���� 2 ����� ��������� ����� ������ � ������ �������
char* FindChains(char const* str, char const* newSeparator);

// ��������� ������ str, �������� � ��� + separator + appendStr
// separator ����������� ������ ���� str �� ������
// ���������� ����� ������������
int StrJointSeparStr(char** str, char const* separator, char const* appendStr);

// ������� - ����� ������, ��� str ������� �� ������ ������� width
// ��������� �������� ������ ���������� �� ���� ������, ������������ - �����
// ����� �������� - \n, ���� ����� > width, ��� ����������� �� �����
char* StrJustifyLeft(char* str, unsigned width);

// ������� - ����� ������, ��� str ������� �� ������ ������� width
// ������������- �� ������, ������� ���������� ��������
// ����� �������� - \n, ���� ����� > width, ��� ����������� �� �����
char* StrJustifyWidth(char* str, unsigned width);

#endif DST_FUNCTIONS_H_INCLUDED__