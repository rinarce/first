#pragma once
#include <time.h>
#include "SOR.h"

#define ARRAY_MIN_SIZE  100     // минимальный размер массива
#define ARRAY_MAX_SIZE  77777   // максимальный
#define ARRAY_SIZE_STEP 2019    // шаг приращения размера массива
#define TEST_REPEAT     10      // каждый тест проводить X раз
#define INIT_RAND       1234    // admin pass для инициализации генератора случайных чисел
#define OUT_SEPARATOR   "; "

// sort_func_t - тип - стандарт заголовка для функции сортировки 
typedef void (*sort_func_t)(int array[], int size);

// формирую в файле первую строку, там будут значения 
// == размеры массива на каждом шаге тестирования
void test_MakeFirstLine(FILE* out_file);


// Тестирует алгоритм на массивах разного размера, результат в CSV файл
void test_algorithm(sort_func_t fun, const char* algorithm, FILE* out_file);

