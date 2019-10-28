// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <stdio.h>

// calc_variables.c
// ��� ������� ��� ������ � ����������� 
// � ����������� ������ ��� �� ��������

// ������� 2 ��������� ��� �������� ���������� � ��� �������

// ---------------------------------------------------------------------------
// ������ ��������� ���������� var_name, return - ��� ������
// ���� �� ��������� �������
int variable_make(char* var_name, double value)
{
  printf("[VAR <%s>==%g]\n", var_name, value);
  return 0;
}

// ---------------------------------------------------------------------------
// ������ ���������� ���������� var_name, return - ��� ������
// ���� �� ��������� �������
int variable_make_global(char* var_name, double value)
{
  printf("[GL_VAR <%s>==%g]\n", var_name, value);
  return 0;
}

// ---------------------------------------------------------------------------
// �������� ���������� var_name -> *value,  - ��� ������
// ���� �� �������    return 0 - �� �������, 1 - ���� �����
int variable_get(char* var_name, double *value)
{
  *value = 0;
  return 0;
}

// ---------------------------------------------------------------------------
// �������� ��������� (��� ����� ������) ����������, return - ��� ������
// ���� �� �������
int variable_clear_local(void)
{

  return 0;
}

// ---------------------------------------------------------------------------
// �������� ���������� (��� ��������� �����) ����������, return - ��� ������
// ���� �� �������
int variable_clear_global(void)
{

  return 0;
}