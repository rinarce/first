#pragma once

// ---------------------------------------------------------------------------
// ��������� ��� ����������
// ---------------------------------------------------------------------------

// ������ ��������� ���������� var_name, return - ��� ������
int variable_make(char* var_name, double value);

// ������ ���������� ���������� var_name, return - ��� ������
int variable_make_global(char* var_name, double value);

// �������� �������� ���������� var_name -> *value, 
// return 0 - �� �������, 1 - ���� �����
int variable_get(char* var_name, double* value);

// �������� ��������� (��� ����� ������) ���������� 
void variable_clear_local(void);

// �������� ���������� (��� ��������� �����) ����������
void variable_clear_global(void);
