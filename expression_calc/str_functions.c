#include <stdlib.h>
#include <ctype.h>  // ��� isspace()

// �������� ����� ��� ������ �������� (size + 1)
char* AllocateString(unsigned int size)
{ 
  char* new_str = (char*)malloc(size + 1);
  if (NULL != new_str)
    *new_str = '\0';   // �� ������ ������ � ������ ������ ����� ������
  return new_str;
}

// ����� ������ �� '\0'
unsigned int str_lenght(char const* str) 
{
  int len = 0;
  if (NULL != str)          // ��������, ��� ��������� ���������
    while (*str++) len++;
  return len;
}

// 1 - ���� � ������ ������ ������������ ������� ( \t\n\v\f\r)
int is_only_spaces(char* str)
{
  while (*str)
    if (!isspace((int)(*str++)))
      return 0;
  return 1;
}

// 1 - ���� � ������ ������ �������� ������� //
int is_comment(char* str)
{
  while (*str)
    if (!isspace((int)(*str)))   // ���������� ��� ���������� �������
      break;
    else str++;

  // ��������� ��� ��� ������� - ��� �� ����� ������ � ����� '//'
  if (*str && *str == '/' && *(str + 1) && *(str + 1) == '/')
    return 1;
  else return 0;
}

// 1 - ���� � ������ �������� �������� ������ (()
int is_bracket_error(char* str)
{
  int nest = 0;                       // ������� �������� ������
  while (*str)
  {
    if (*str == '(')        nest++;   // ����������� ������
    else if (*str == ')')   nest--;   // ����������� ������

    if (nest < 0)  return 1;          // ����������� ������ �����������

    str++;
  }
  return nest;            // ���� >0 - �������� ���������� ������
}


// ���������� ������ �� ����� distance, ������� 1 ���� �����, 0 �����
int str_compare_fix_len(char const* str1, char const* str2, unsigned int distance)
{
  while (distance--)
    if (*(str1++) != *(str2++)) // �� ������� ������������
      return 0;
  return 1;
}

// ������� ��������
unsigned int str_count_spaces(char const* str)
{ 
  unsigned count = 0;
  while (*str)
    if (isspace((int)(*str++)))
      count++;
  return count;
}

// ������� ����������
unsigned int str_count_non_spaces(char const* str)
{
  unsigned count = 0;
  while (*str)
    if (!isspace((int)(*str++)))
      count++;
  return count;
}

// �� str ������� ��� ������� -> � ����� ��������� ������
char* str_remove_spaces(char const* str)
{ 
  unsigned int new_len = str_count_non_spaces(str);
  char* new_string = (char*)malloc(new_len + 1);
  
  if (NULL == new_string)         // ��������� ������ �� �������
    return NULL;

  char* new_str_ptr = new_string; // �����������
  char const* old_str_ptr = str;
  
  while (*old_str_ptr)            // ���� �� ����� ������
    if (!isspace(*old_str_ptr))   // �������� �� ������
      *(new_str_ptr++) = *(old_str_ptr++);
    else
      old_str_ptr++;              // ������ - ����������

  *new_str_ptr = '\0';            //  ����� ������
  return new_string;
}
