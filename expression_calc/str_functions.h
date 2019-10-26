#pragma once

#include <stdlib.h>

// �������� ����� ��� ������ �������� (size + 1)
char* AllocateString(unsigned int size);

// ����� ������ �� '\0'
unsigned int str_lenght(char const* str);

// 1 - ���� � ������ ������ ������������ ������� ( \t\n\v\f\r)
int is_only_spaces(char* str);

// 1 - ���� � ������ ������ �������� ������� //
int is_comment(char* str);

// 1 - ���� � ������ �������� �������� ������ (()
int is_bracket_error(char* str);

// ���������� ������ �� ����� distance, ������� 1 ���� �����, 0 �����
int str_compare_fix_len(char const* str1, char const* str2, unsigned int distance);

// �������� ������� � ������� strFrom -> strTo, � ���������� number
void str_copy_fix_len(char const* strFrom, char* strTo, unsigned int number);

// ������� ��������
unsigned int str_count_spaces(char* str);

// ������� ����������
unsigned int str_count_non_spaces(char* str);

// �� str ������� ��� ������� -> � ����� ��������� ������
char* str_remove_spaces(char const* str);

// ���������� 1 ������ [A�Z] -> [a�z], ��� �� ������
char LowerChar(char c);

// ���������� 1 ������ [a�z] -> [A�Z], ��� �� ������
char UpperChar(char c);

// �������� ������� ������ [A�Z] -> �� ������� �� [a�z]
void LowerCase(char str[]);

// �������� ������� ������ [a�z] -> [A�Z]
void UpperCase(char str[]); 



