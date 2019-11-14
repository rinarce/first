#ifndef TESTING_SYSTEM_H_INCLUDED__
#define TESTING_SYSTEM_H_INCLUDED__
#pragma once
#include <time.h>
#include "SOR.h"

// !! закомментить после проверки корректности всех алгоритмов
//#define CHECK_SORTED   // провер€ть массив после работы алгоритма?

#define ARRAY_MIN_SIZE  100     // минимальный размер массива
#define ARRAY_MAX_SIZE  77777   // максимальный
#define ARRAY_SIZE_STEP 2019    // шаг приращени€ размера массива
#define TEST_REPEAT     10      // каждый тест проводить X раз
#define INIT_RAND       1234    // admin pass дл€ инициализации генератора случайных чисел
#define OUT_SEPARATOR   "; "

// sort_func_t - тип - стандарт заголовка дл€ функции сортировки 
typedef void (*sort_func_t)(int array[], int size);

// формирую в файле первую строку, там будут значени€ 
// == размеры массива на каждом шаге тестировани€
void TestMakeFirstLine(FILE* out_file);


// “естирует алгоритм на массивах разного размера, результат в CSV файл
void TestAlgorithm(sort_func_t fun, const char* algorithm, FILE* out_file);

#endif TESTING_SYSTEM_H_INCLUDED__
