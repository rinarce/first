#pragma once
#include <time.h>
#include "SOR.h"

#define ARRAY_MIN_SIZE  100     // минимальный размер массива
#define ARRAY_MAX_SIZE  50000   // максимальный
#define ARRAY_SIZE_STEP 2019    // шаг приращения размера массива
#define TEST_REPEAT     10       // каждый тест проводить X раз
#define INIT_RAND       12345   // для инициализации генератора случайных чисел
#define OUT_SEPARATOR   "; "


void test_MakeFirstLine(FILE* out_file);

void test_algorithm(sort_func_t fun, const char* algorithm, FILE* out_file);



