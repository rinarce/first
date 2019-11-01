#ifndef TESTING_SYSTEM_H_INCLUDED__
#define TESTING_SYSTEM_H_INCLUDED__
#pragma once
#include <time.h>
#include "SOR.h"

#define ARRAY_MIN_SIZE  100     // ����������� ������ �������
#define ARRAY_MAX_SIZE  77777   // ������������
#define ARRAY_SIZE_STEP 2019    // ��� ���������� ������� �������
#define TEST_REPEAT     10      // ������ ���� ��������� X ���
#define INIT_RAND       1234    // admin pass ��� ������������� ���������� ��������� �����
#define OUT_SEPARATOR   "; "

// sort_func_t - ��� - �������� ��������� ��� ������� ���������� 
typedef void (*sort_func_t)(int array[], int size);

// �������� � ����� ������ ������, ��� ����� �������� 
// == ������� ������� �� ������ ���� ������������
void TestMakeFirstLine(FILE* out_file);


// ��������� �������� �� �������� ������� �������, ��������� � CSV ����
void TestAlgorithm(sort_func_t fun, const char* algorithm, FILE* out_file);

#endif TESTING_SYSTEM_H_INCLUDED__
