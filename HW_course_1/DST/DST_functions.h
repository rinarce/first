#ifndef DST_FUNCTIONS_H_INCLUDED__
#define DST_FUNCTIONS_H_INCLUDED__
#pragma once


char* AllocateString(unsigned int size);
// �������� ����� ��� ������ �������� (size + 1)

unsigned int DST_InputStr(char** str, char const* text);
// ������ ������ ������������ �����, �������������� �������� ������
// � *str ���������� ��������� �� ������, return ���������� ����� ������

char* ExtractWords(char const* str, char const* newSeparator);
// ����� ������, ����� �� str ��������� ����� ������������

char* ExtractUniqueWords(char const* str, char const* newSeparator);
// ����� ������, ���������� ����� �� str ��������� ����� ������������

char* ExtractLetters(char const* str, char const* newSeparator);
// ����� ������, ����� �� str ��������� ����� ������������

char* ExtractUniqueLetters(char const* str, char const* newSeparator);
// ����� ������, ���������� ����� �� str ��������� ����� ������������

char* STR_GetOnlyLetters(char const* str);
// �� str ����� ������ ����� � ����� ��������� ������

char* FindMirrors(char const* str, char const* newSeparator);
// ����� ������, �� str ������� ����������� � ������� 
// ��� ��������� ������� 1, ������� ���� � ���������� ����,
// ��� ��������� ����� ������������

char* FindMaskWords(char const* str, char const* mask, char const* newSeparator);
// ����� ������, ��� ��������� �� str �� ����� ������, ��������� ����� ������������

char* ConvertRussian(char const* str);
// ����� ������, �������������� ������� ��������, 
// �� �������� - ������ ��� �� �� 29 ����� 2016 �. N 4271

char* FindChains(char const* str, char const* newSeparator);
// ����� ������, ������� ����� ������� - ��������� �����
// ���� 2 ����� ��������� ����� ������ � ������ �������

int STR_Joint_Separ_Str(char** str, char const* separator, char const* appendStr);
// ��������� ������ str, �������� � ��� + separator + appendStr
// separator ����������� ������ ���� str �� ������
// ���������� ����� ������������

char* STR_JustifyLeft(char* str, unsigned width);
// ������� - ����� ������, ��� str ������� �� ������ ������� width
// ��������� �������� ������ ���������� �� ���� ������, ������������ - �����
// ����� �������� - \n, ���� ����� > width, ��� ����������� �� �����

char* STR_JustifyWidth(char* str, unsigned width);
// ������� - ����� ������, ��� str ������� �� ������ ������� width
// ������������- �� ������, ������� ���������� ��������
// ����� �������� - \n, ���� ����� > width, ��� ����������� �� �����

#endif DST_FUNCTIONS_H_INCLUDED__