#pragma once

#include <stdio.h>
#include <stdlib.h>             // ��� ��������� ������

#define DST_BUFFER_SIZE 10      // ������ ���������� ������ (��������� � ������!)
//#define DEBUG_IO                // ������� �����, ���������������� ��������������!


// 1 - ��������� ��������� ������ �������� ��� ������ ������
// 0 - ���� (�������� ������ 1 ��� �������� - ��� ����� � �������)
int is_command_line_wrong(int arg_count, char* arg_values[]);


// return - 0 == OK    1 == ������ �������� �������� �����
// input_file - ���� ������ ���� � ���������� ������, �� �� ��������� �� ����
// ����� input_file = stdin  - ���� �� ������, ��� ���� ������������� (���� ������� windows)
int detect_input_stream(int arg_count, char* arg_values[], FILE** input_file);


// ������ ������ ������������ �����, �������������� �������� ������
// � *str ���������� ��������� �� ������, return = ����� ������
// \n � ����� ����������, �� ��������� � ����� (����� == 0 - ����� ������ �����)
unsigned int read_input_line(FILE* input_stream, char** str);


// �������� ������ ���������� ��������� == ���������
void print_expression(FILE* output_stream, char* input_line, double result);


// �������� ������ ����������� 
void print_comment(FILE* output_stream, char* input_line);


// �������� ������ ��� �������� �������� 
void print_spaces(FILE* output_stream, char* input_line);


// �������� ������ ������ (� ������ ������ \n)
void print_empty(FILE* output_stream, char* input_line);


// �������� ������ � �������
void print_error(FILE* output_stream, char* input_line, int error_code);
