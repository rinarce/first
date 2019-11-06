// Primes01.c
#include <stdio.h>
#include <math.h>

// https://acmp.ru/index.asp?main=task&id_task=64

/*    подряд идущие по возрастанию простые числа (начиная с 2) записываются друг за другом. 
    Начало данного ряда выглядит так: 23571113171923… Необходимо найти цифру, стоящую в простом 
    ряду на указанном месте. Нумерация позиций начинается с единицы
*/

#define INPUT_FILE   "INPUT.TXT"
#define OUTPUT_FILE "OUTPUT.TXT"

#pragma warning(disable:4996)   // for use scanf in VisualStudio

#define MAX_DIGIT_NUM 10001

/*
def primesGen1() :
  '''  все простые == 12k+1, 12k+5, 12k+7 или 12k+11
  '''
  # при k == 0 обрабатываем отдельно, т.к. 1 - не простое, а 2 и 3 наоборот - простые
  for n in[2, 3, 5, 7, 11]: yield n
    n = 13              # k == 1   -> 12k + 1 == 13
    while True:
if not any(i for i in range(3, int(n * *0.5) + 1, 2) if not n % i) : yield n
n += 4          # 12k + 5
if not any(i for i in range(3, int(n * *0.5) + 1, 2) if not n % i) : yield n
n += 2          # 12k + 7
if not any(i for i in range(3, int(n * *0.5) + 1, 2) if not n % i) : yield n
n += 4          # 12k + 11
if not any(i for i in range(3, int(n * *0.5) + 1, 2) if not n % i) : yield n
n += 2          # 12(k + 1) + 1
*/

int test_prime(int n) {
  int limit = (int)(sqrt((double)n) + 1);
  for (int i = 3; i <= limit; i += 2) 
    if (n % i == 0) return 0;
  return 1;
}

void add_to_array(char array[], int* position, int num) {
  char* ptr = array + *position;
  *position += sprintf(ptr, "%d", num);
}

void fill_prime_digits(char * array, int num_digits) {
  int digit_index = 7;
  int test_num = 13;
  array[1] = '2';
  array[2] = '3';
  array[3] = '5';
  array[4] = '7';
  array[5] = '1';
  array[6] = '1';



  while (digit_index <= num_digits) {
    if (test_prime(test_num)) add_to_array(array, &digit_index, test_num);
    test_num += 4;
    
    if (test_prime(test_num)) add_to_array(array, &digit_index, test_num);
    test_num += 2;
    
    if (test_prime(test_num)) add_to_array(array, &digit_index, test_num);
    test_num += 4;
    
    if (test_prime(test_num)) add_to_array(array, &digit_index, test_num);
    test_num += 2;
  }
}


int main() {
  FILE* inp_file;
  FILE* out_file;
  // int error;
  int numTest, digit_index;
  static char prime_digits[MAX_DIGIT_NUM + 100] = { 0 };

  if (fopen_s(&inp_file, INPUT_FILE, "r"))    return 1;
  if (fopen_s(&out_file, OUTPUT_FILE, "w"))   return 2;
  
  fill_prime_digits(prime_digits, MAX_DIGIT_NUM);

  fscanf_s(inp_file, "%d", &numTest);
  while (numTest--) {
    fscanf_s(inp_file, "%d", &digit_index);
    fprintf(out_file, "%c", prime_digits[digit_index]);
  }
  fclose(inp_file);
  fclose(out_file);
   
  return 0;
}

