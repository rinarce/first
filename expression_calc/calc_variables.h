#pragma once

// ---------------------------------------------------------------------------
// ��������� ��� ����������
// ---------------------------------------------------------------------------

// ������ ��������� ���������� var_name, return - ��� ������
int variable_make(char const* var_name, double const value);

// ������ ���������� ���������� var_name, return - ��� ������
int variable_make_global(char const* var_name, double const value);

// �������� �������� ���������� var_name -> *value, 
// return 0 - �� �������, 1 - ���� �����
int variable_get(char const* var_name, double* value);

// �������� ��������� (��� ����� ������) ���������� 
void variable_clear_local(void);

// �������� ���������� (��� ��������� �����) ����������
void variable_clear_global(void);
