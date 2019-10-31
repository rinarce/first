#ifndef COMMON_DEFS_H_INCLUDED__
#define COMMON_DEFS_H_INCLUDED__
#pragma once

#include <stdio.h>
#include <stdlib.h>               // ��� ��������� ������ � ��.

#define DST_BUFFER_SIZE 100       // ������ ���������� ������ (��������� � ������!)
#define MESSAGE_EN                // ��������� �� ������� �� ����������? ����� �� �������

// --  ������� ��������� ������ ? ������������ ? -----------------------------
#define CALC_USE_BRACKET_MULTIPLY // ������� �� 2(3) (4)5(6) ���������� - ��


// --  ��������� ��������� ������ - ��� ---------------------------------------

typedef enum calc_err_t { // ��������� ��������� ������ - ���
                          // ���������� ���������
  CALC_OK,                // ��� ���������� ���������, ��� ���� ������� ��� ������

                          // ������ ������ ��� ���������
  CALC_LINE_COMMENT,      // ��� �����������
  CALC_LINE_EMPTY,        // ��� ���������� ������ ������
  CALC_LINE_SPACES,       // ��� ������ ��� �������� ��������
                        
                          // ��������� ������ - ��������� ���������
  CALC_ERR_ARGS,          // ������ - ������������ ��������� ��������� ������
  CALC_ERR_OPEN_FILE,     // ������ - �� ������� ������� ������� ����
  CALC_LINE_THE_END,      // �� ������, �� ���������� ����� �����

                          // ���������� ��������� ��� ���Ĩ��� ������
  CALC_ERR_INPUT,         // ������ - �� ������� ������ ��� ������ ������

                          // ���������� ������ � ��������� �� ������
  CALC_ERR_PARSE,         // ������ - �� ����� ������� ���������
  CALC_ERR_EVAL,          // ������ - �������������� � �����
  CALC_ERR_MEMORY,        // ������ - ��������� ������
  CALC_ERR_ZERO_DIV,      // ������ - ������� �� 0
  CALC_ERR_BRACKETS,      // ������ - ���������� ������
  CALC_ERR_SQRT_N,        // ������ - ���������� ������ �� �������������
  CALC_ERR_NAN,           // ������ - NaN - �� �����
  CALC_ERR_INF,           // ������ - Inf - ������������� (�������� 0 � ������������� ^)
  CALC_ERR_ALGO,          // ������ - � ��������� ���-�� ��� �� ���
  CALC_ERR_X,             // ������ - .... ���� �� ���������
  CALC_ERR_VARS,          // ������ - � �����������
  CALC_ERR_VARZ,          // ������ - ���������� ��� �����
  CALC_ERR_VAR_BADNAME,   // ������ - ���������� - ������ ��� - �� �����������
                          // �� �������������� ���������� ��-�� ���������� �����
  CALC_ERR_OTHER,         // ������ - ������
  CALC_ERR_COUNT,         // ������ - ����������� ����� ������������
} calc_err_t;

// --  ���������  ------------------------------------------------------------

#define M_E        2.71828182845904523536
#define M_PI       3.14159265358979323846

// --  �������  --------------------------------------------------------------

// --  ����-�����  -----------------------------------------------------------

// ������ ������ ������������ �����, �������� ������, return = ��� ������
// ��� �������� ������ - ������� �� ����� ������, �������� ���������
calc_err_t ReadInputLine(FILE* input_stream, char** str);

// �������� ������ �� �������� ������, � ������ ���� ������
void PrintLine(FILE* output_stream, char* input_line, calc_err_t error, double result);


// --  ��������� ������  -----------------------------------------------------

// ��������� ������ ���������, ���������� ��� ������ (�� ��� ������) � ���������
calc_err_t ProcessLine (char const* input_line, double* result);

// --  ��������� ������ � �����������  ---------------------------------------

// clear global variables
void VariableClearGlobal(void);

// clear local (for current line) variables
void VariableClearLocal(void);

// create local (for current line) variable
calc_err_t VariableMake(char const* varName, double const value);

// create global variable
calc_err_t VariableMakeGlobal(char const* varName, double const value);

// get value by variable name (if exist), return 0 - variable not exist, 1 - exist
int VariableGet(char const* varName, double* value);

#endif COMMON_DEFS_H_INCLUDED__
