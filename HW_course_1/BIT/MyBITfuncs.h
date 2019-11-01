#ifndef MYBITFUNCS_H_INCLUDED__
#define MYBITFUNCS_H_INCLUDED__
#pragma once

#pragma warning(disable:4996)   // for use scanf in VisualStudio
#define BIT_ZERO_SYM '.'        // для вывода на экран
#define BIT_ONE_SYM '#'

// вариации целочисленых беззнаковых типов ------------------------------------------------
// typedef unsigned char integer_t;       // разкомментить только один из них
// typedef unsigned short integer_t;
// typedef unsigned int integer_t;
 typedef unsigned long integer_t; 
// typedef unsigned long long integer_t;

// тип для ввода / вывода
typedef unsigned long long MaxInt;

// ОСНОВА --------------------------------------------------------------
// вводит положительное число, преобразует его к типу integer_t
integer_t BitInputTestNumber();
  
// определяет, сколько цифр понадобится для 10го представления Х
unsigned int BitCountDecimalDigits(integer_t x);
  
// находит максимальное значение 2 целых
unsigned int Max2Uns(unsigned int x1, unsigned int x2);
  
// печатает Х в разных представлениях по условию задачи
void BitPrint(const char text[], integer_t x, unsigned int decimalWidtn);
  

// ЗАДАНИЯ --------------------------------------------------------------

// производит обмен битовых блоков размера blockSize в числе Х, 
// 1 - реверс битов, 2 - попарно b1b0 <-> b(n)b(n-1) ..., 4 - b3..b0 <-> 4 старших бита ...
// 8 - побайтно (младший байт со старшим и т.д.), любое другое число - не меняет Х
integer_t BitReverseBitsBlocks(integer_t x, unsigned int blockSize);

// производит обмен битов внутри битовых блоков размера blockSize в числе Х, 
// 1 - ничего, 2 - чётные биты меняются с нечётными, 4 - реверс в каждй 4ке битов
// 8 - реверс битов в каждом байте, любое другое число - не меняет Х
integer_t BitReverseInBlocks(integer_t x, unsigned int blockSize);

// циклический сдвиг <---  влево <--- 
integer_t BitCycleLeft(integer_t x, unsigned int shift);
  
// циклический сдвиг ---> вправо --->
integer_t BitCycleRight(integer_t x, unsigned  int shift);
  
// циклический сдвиг <---  влево <--- (в каждом байте отдельно)
integer_t BitCycleInBytesLeft(integer_t x, unsigned  int shift);
  
// циклический сдвиг ---> вправо ---> (в каждом байте отдельно)
integer_t BitCycleInBytesRight(integer_t x, unsigned int shift);

#endif MYBITFUNCS_H_INCLUDED__