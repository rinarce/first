#pragma once
#include <time.h>
#include "SOR.h"

#define ARRAY_MIN_SIZE  100     // ����������� ������ �������
#define ARRAY_MAX_SIZE  30000   // ������������
#define ARRAY_SIZE_STEP 2019    // ��� ���������� ������� �������
#define TEST_REPEAT     5       // ������ ���� ��������� 5 ���
#define INIT_RAND       12345   // ��� ������������� ���������� ��������� �����
#define OUT_SEPARATOR   "; "


void test_MakeFirstLine(FILE* out_file);

void test_algorithm(sort_func_t fun, const char* algorithm, FILE* out_file);



