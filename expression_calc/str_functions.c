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
  while (*str && isspace((int)(*str)))
    str++;   // ���������� ��� ���������� �������

  // ��������� ��� ��� ������� - ��� �� ����� ������ � ����� '//'
  return (*str && *str == '/' && *(str + 1) && *(str + 1) == '/');
}

// 1 - ���� � ������ �������� �������� ������ (()
int is_bracket_error(char* str)
{
  int nest = 0;                       // ������� �������� ������
  while (*str)
  {
    if (*str == '(')        nest++;   // ����������� ������
    else if (*str == ')')   nest--;   // ����������� ������

    if (nest < 0)  
      return 1;                       // ����������� ������ �����������
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

// �������� ������� � ������� strFrom -> strTo, � ���������� number
void str_copy_fix_len(char const* strFrom, char* strTo, unsigned int number)
{ 
  while (number--)
    *(strTo++) = *(strFrom++);
}

// ���������� 1 ������ [A�Z] -> [a�z], ��� �� ������
char LowerChar(char c) { 
  if (c >= 'A' && c <= 'Z') c += 32;
  return c;
}

// ���������� 1 ������ [a�z] -> [A�Z], ��� �� ������
char UpperChar(char c) { 
  if (c >= 'a' && c <= 'z') c -= 32;
  return c;
}

// �������� ������� ������ [A�Z] -> �� ������� �� [a�z]
void LowerCase(char str[]) { 
  for (int pos = 0; str[pos]; pos++)
    str[pos] = LowerChar(str[pos]);
}

// �������� ������� ������ [a�z] -> [A�Z]
void UpperCase(char str[]) { 
  for (int pos = 0; str[pos]; pos++)
    str[pos] = UpperChar(str[pos]);
}

// ������� ��������� � ������ ������� X, ��� ����� ������ '\0'
char* str_find_char(char const* str, char x, int start) 
{
  str += start;                          // �������� �� ������ ������
  while (*str)
    if (x == (*str)) return (char*)str;  // ����� ����� ������� ���������� �
    else str++;
  return (char*)str;                     // ��� ����� ����� ����� ������ '\0'
}


// ����� str[start...end] -> ���������� � ������ subStr
// ����� ������  '\0' ����� �� ����������� � � subStr �� �����������
void str_sopy_substr(char str[], int start, int end, char subStr[]) 
{
  for (int pos = 0; start <= end; subStr[pos++] = str[start++]) {}
}


// �� str ���������� ����� [start...end], ������� ������ ���������� <--
void str_remove_substr(char str[], int start, int end) 
{
  int p1 = start, p2 = end + 1;
  do {}		// ����������, ���� �� ��������� ������ '\0'
  while (str[p1++] = str[p2++]);
}

// �������� � ������ str : word -��-> replace 
// (!!! ���������� �� ������ ��������� ��� ����� word !)
// �.�. ������ str - ����� ������ �����������, �� �������������
// ������� - ���������� �����
int str_replace_all(char str[], char word[], char replace[]) 
{
  int replaced = 0,                     // ���������� ������������ �����
      word_len = str_lenght(word), 
   replace_len = str_lenght(replace);
  
  // �������� �� ����� ��������� �����
  if (replace_len > word_len) replace_len = word_len; 
  int delta = word_len - replace_len;	 // ������� � ����� (��� ���������� replace)
  

  int pos = 0;
  while(str[pos])
  {
    if (str_compare_fix_len(&str[pos], word, word_len))
    {
      str_sopy_substr(replace, 0, replace_len - 1, &str[pos]);
      replaced++;
      if (delta)         // ����� ������ �����, ���������� �������� ������
        str_remove_substr(str, pos + replace_len, pos + replace_len + delta - 1);
      pos += replace_len;
    }
    else pos++;
  }
  return replaced;
}

// �������� ������ �� '\0' �������, ���������� ��������� �� strTo
char* str_copy_str(char strFrom[], char strTo[]) 
{
  int pos = 0;
  do {} while (strTo[pos++] = strFrom[pos]);
  return strTo; // ��� ��������
}


// 1 - ���� � str �������� ����� (����� ��� ���������� � result)
// ����������� ����� � ������� ����� - ������� - ','
// Advanced feature - � �������� ������ 0 ����� ������ ����� ������ !
int is_binary_digit(char* str, double* result)
{
  unsigned int str_len = str_lenght(str);
  if (str_len < 2)
    return 0;

  if (*str == '0' && (*(str + 1) == 'b' || *(str + 1) == 'b'))
  {
    // ���������� �� 0b ��� 0B - ������� ��� �������� ������
    *result = 0;
    double multiply = 2.;
    double x = 0;
    str += 2; // ���������� ������ ��� �������
    while (*str && *str != ',') // �� ����� ������ ��� ���������� �������
    {
      x *= 2;
      x += (*str == '1');    // ������ ���� ����� ���� ����� ������ !!! ��� ����
      str++;
    }
    if(*str++ == ',') // ���� ������� �����
    {
      multiply = 0.5;
      while (*str) // �� ����� ������
      { 
        // ������ ���� ����� ���� ����� ������ !!! ��� ����
        x += (*str == '1') ? multiply : 0;
        multiply /= 2;
        str++;
      }
    }
    *result = x;
    return 1;
  }
  
  return 0;
}