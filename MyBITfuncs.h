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
integer_t BIT_Input();
  // вводит положительное число, преобразует его к типу integer_t
unsigned int BIT_count_dec_width(integer_t x);
  // определяет, сколько цифр понадобится для 10го представления Х
unsigned int max_2u(unsigned int x1, unsigned int x2);
  // находит максимальное значение 2 целых
void BIT_Print(const char text[], integer_t x, unsigned int size_in_dec);
  // печатает Х в разных представлениях по условию задачи

// ЗАДАНИЯ --------------------------------------------------------------
integer_t BIT_reverse_bit_blocks(integer_t x, unsigned int block_size);
  // производит обмен битовых блоков размера block_size в числе Х, 
  // 1 - реверс битов, 2 - попарно b1b0 <-> b(n)b(n-1) ..., 4 - b3..b0 <-> 4 старших бита ...
  // 8 - побайтно (младший байт со старшим и т.д.), любое другое число - не меняет Х
integer_t BIT_reverse_IN_blocks(integer_t x, unsigned int block_size);
   // производит обмен битов внутри битовых блоков размера block_size в числе Х, 
   // 1 - ничего, 2 - чётные биты меняются с нечётными, 4 - реверс в каждй 4ке битов
   // 8 - реверс битов в каждом байте, любое другое число - не меняет Х
integer_t BIT_CycleLeft(integer_t x, unsigned int shift);
  // циклический сдвиг <---  влево <--- 
integer_t BIT_CycleRight(integer_t x, unsigned  int shift);
  // циклический сдвиг ---> вправо --->
integer_t BIT_CycleLeft_inBytes(integer_t x, unsigned  int shift);
  // циклический сдвиг <---  влево <--- (в каждом байте отдельно)
integer_t BIT_CycleRight_inBytes(integer_t x, unsigned int shift);
  // циклический сдвиг ---> вправо ---> (в каждом байте отдельно)
