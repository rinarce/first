#pragma once

enum calc_line_type
{
  CALC_LINE_OK,           // ��� ���������� ���������
  CALC_LINE_COMMENT,      // ��� �����������
  CALC_LINE_EMPTY,        // ��� ���������� ������ ������
  CALC_LINE_SPACES,       // ��� ������ ��� �������� ��������
  CALC_LINE_LAST,
  CALC_LINE_ERR_MEMORY,   // ������ - ��������� ������
  CALC_LINE_ERR_ZERO_DIV, // ������ - ������� �� 0
  CALC_LINE_ERR_BRACKETS, // ������ - ���������� ������
  CALC_LINE_ERR_X,        // ������ - .... ���� �� ���������
  CALC_LINE_ERR_OTHER,    // ������ - ������
  CALC_LINE_ERR_COUNT,    // ������ - ����������� ����� ������������
};

// ��������� ������ ���������, ���������� ��� ������ (�� ��� ������) � ���������
int process_line(char* input_line, double* result);

