#include "MyBITfuncs.h"
#include <stdio.h>
#pragma warning(disable:4996)   // for use scanf in VisualStudio


// битовые маски на все случаи ------------------------------------------------------------
// для реверса блоками --------------------------------------------------------------------
const integer_t bit_mask_LOW = ((integer_t)0b00000001);
const integer_t bit_mask_HIGH = ((integer_t)0b10000000) << ((sizeof(integer_t) - 1) * 8);

const integer_t bit_mask_REV2_L = ((integer_t)0b00000011);
const integer_t bit_mask_REV2_H = ((integer_t)0b11000000) << ((sizeof(integer_t) - 1) * 8);

const integer_t bit_mask_REV4_L = ((integer_t)0b00001111);
const integer_t bit_mask_REV4_H = ((integer_t)0b11110000) << ((sizeof(integer_t) - 1) * 8);

const integer_t bit_mask_REV8_L = ((integer_t)0b11111111);
const integer_t bit_mask_REV8_H = ((integer_t)0b11111111) << ((sizeof(integer_t) - 1) * 8);

// для реверса внутри блоков --------------------------------------------------------------
const integer_t bit_mask_20 = (integer_t)0b0101010101010101010101010101010101010101010101010101010101010101;
const integer_t bit_mask_21 = (integer_t)0b1010101010101010101010101010101010101010101010101010101010101010;

const integer_t bit_mask_40 = (integer_t)0b0001000100010001000100010001000100010001000100010001000100010001;
const integer_t bit_mask_41 = (integer_t)0b0010001000100010001000100010001000100010001000100010001000100010;
const integer_t bit_mask_42 = (integer_t)0b0100010001000100010001000100010001000100010001000100010001000100;
const integer_t bit_mask_43 = (integer_t)0b1000100010001000100010001000100010001000100010001000100010001000;

const integer_t bit_mask_80 = (integer_t)0b0000000100000001000000010000000100000001000000010000000100000001;
const integer_t bit_mask_81 = (integer_t)0b0000001000000010000000100000001000000010000000100000001000000010;
const integer_t bit_mask_82 = (integer_t)0b0000010000000100000001000000010000000100000001000000010000000100;
const integer_t bit_mask_83 = (integer_t)0b0000100000001000000010000000100000001000000010000000100000001000;
const integer_t bit_mask_84 = (integer_t)0b0001000000010000000100000001000000010000000100000001000000010000;
const integer_t bit_mask_85 = (integer_t)0b0010000000100000001000000010000000100000001000000010000000100000;
const integer_t bit_mask_86 = (integer_t)0b0100000001000000010000000100000001000000010000000100000001000000;
const integer_t bit_mask_87 = (integer_t)0b1000000010000000100000001000000010000000100000001000000010000000;

// битовые маски ---- в форме структуры ----------------------------------------
struct {  
  // для реверса блоками --------------------------------------------------------------------
  const integer_t b_LOW = ((integer_t)0b00000001);
  const integer_t b_HIGH = ((integer_t)0b10000000) << ((sizeof(integer_t) - 1) * 8);

  const integer_t REV2_L = ((integer_t)0b00000011);
  const integer_t REV2_H = ((integer_t)0b11000000) << ((sizeof(integer_t) - 1) * 8);

  const integer_t REV4_L = ((integer_t)0b00001111);
  const integer_t REV4_H = ((integer_t)0b11110000) << ((sizeof(integer_t) - 1) * 8);

  const integer_t REV8_L = ((integer_t)0b11111111);
  const integer_t REV8_H = ((integer_t)0b11111111) << ((sizeof(integer_t) - 1) * 8);

  // для реверса внутри блоков --------------------------------------------------------------
  const integer_t block_bit_20 = (integer_t)0b0101010101010101010101010101010101010101010101010101010101010101;
  const integer_t block_bit_21 = (integer_t)0b1010101010101010101010101010101010101010101010101010101010101010;

  const integer_t block_bit_40 = (integer_t)0b0001000100010001000100010001000100010001000100010001000100010001;
  const integer_t block_bit_41 = (integer_t)0b0010001000100010001000100010001000100010001000100010001000100010;
  const integer_t block_bit_42 = (integer_t)0b0100010001000100010001000100010001000100010001000100010001000100;
  const integer_t block_bit_43 = (integer_t)0b1000100010001000100010001000100010001000100010001000100010001000;

  const integer_t block_bit_80 = (integer_t)0b0000000100000001000000010000000100000001000000010000000100000001;
  const integer_t block_bit_81 = (integer_t)0b0000001000000010000000100000001000000010000000100000001000000010;
  const integer_t block_bit_82 = (integer_t)0b0000010000000100000001000000010000000100000001000000010000000100;
  const integer_t block_bit_83 = (integer_t)0b0000100000001000000010000000100000001000000010000000100000001000;
  const integer_t block_bit_84 = (integer_t)0b0001000000010000000100000001000000010000000100000001000000010000;
  const integer_t block_bit_85 = (integer_t)0b0010000000100000001000000010000000100000001000000010000000100000;
  const integer_t block_bit_86 = (integer_t)0b0100000001000000010000000100000001000000010000000100000001000000;
  const integer_t block_bit_87 = (integer_t)0b1000000010000000100000001000000010000000100000001000000010000000;
} bit_mask;

// вводит положительное число, преобразует его к типу integer_t
integer_t BIT_Input()
{ MaxInt input_data;
  printf("   Введите число : ");
  scanf("%llu", &input_data);

  MaxInt alowed_num = (integer_t)(-1);
  if (alowed_num < input_data)
      printf("! Обрезано, макс : %llu\n", alowed_num);
  return (integer_t)input_data;
}

// ? сколько цифр понадобится для 10го представления Х
unsigned int BIT_count_dec_width(integer_t x)
{ 
  unsigned int dec_width = 1;  // 1 в любом случае
  while (x /= 10) dec_width++;
  return dec_width;
}

unsigned int max_2u(unsigned int x1, unsigned int x2)    // находит максимальное значение 
{   return (x1 > x2) ? x1 : x2;   }

// печатает Х в разных представлениях по условию задачи
void BIT_Print(const char text[], integer_t x, unsigned int size_in_dec)
{ // size_in_dec - получает извне, остальные рассчитывает
  // пример 163 = 0xA3 = 10100011         ДЕС = НЕХ = БИН
  const int size_in_bytes = sizeof(integer_t);
  const int size_in_hexes = sizeof(integer_t) * 2;
  const int size_in_bites = sizeof(integer_t) * 8;
  MaxInt x_output = (MaxInt) x;
  char bits[sizeof(integer_t) * 8 + 1] = { 0 };  // +1 для конца строки

  printf("%s %*llu = 0x%0*llX = ", 
        text, size_in_dec, x_output, size_in_hexes, x_output);

  for (int i = size_in_bites - 1; i >= 0; i--)       // расчёт битов
  { bits[i] = (bit_mask_LOW & x) ? BIT_ONE_SYM : BIT_ZERO_SYM;
    x >>= 1;
  }
  // печать битов, для очень длинных - с новой строки
  printf("%s%s\n", 
        ((sizeof(integer_t)>4) ? "\n               " : ""), bits);
}

integer_t BIT_1Reverse(integer_t x)
{ // обращает порядок битов в Х
  integer_t mask_high = bit_mask_HIGH;
  integer_t mask_low = bit_mask_LOW;
  integer_t result = 0;
  while (mask_high > mask_low)
  {   
    integer_t new_bits_L = (x & mask_high) ? mask_low : 0;
    integer_t new_bits_H = (x & mask_low) ? mask_high : 0;

    result = result | new_bits_H | new_bits_L;

    mask_high >>= 1;
    mask_low <<= 1;
  }
  return result;
}

integer_t BIT_2Reverse(integer_t x)
{ // обращает порядок пар битов в Х
  integer_t mask_low  = bit_mask_REV2_L;
  integer_t mask_high = bit_mask_REV2_H;
  integer_t result = 0;
  int delta = sizeof(integer_t) * 8 - 2; // на сколько сдвигать первоначально
  while (delta > 0)
  {
    integer_t new_bits_L = (x & mask_high) >> delta;
    integer_t new_bits_H = (x & mask_low) << delta;

    result =  result | new_bits_H | new_bits_L;

    mask_high >>= 2;
    mask_low <<= 2;
    delta -= 4;
  }
  return result;
}

integer_t BIT_4Reverse(integer_t x)
{ // обращает порядок четвёрок битов в Х
  integer_t result = 0;

// XXXXXXXXXXXXXXXXXX --- ещё не реализовано --- XXXXXXXXXXXXXXX

  return result;
}

integer_t BIT_8Reverse(integer_t x)
{ // обращает порядок байтов в Х
  if (sizeof(integer_t) == 1) 
    return x; // для однобайтового числа перестановка байт не нужна
  integer_t result = 0;

// XXXXXXXXXXXXXXXXXX --- ещё не реализовано --- XXXXXXXXXXXXXXX

  return result;
}

integer_t BIT_Swap2(integer_t x)
{ // меняет биты попарно bit0<->bit1, bit2<->bit3 ...
  integer_t bits0 = x & bit_mask_20;
  integer_t bits1 = x & bit_mask_21;
  
  integer_t new_bits1 = bits0 << 1;
  integer_t new_bits0 = bits1 >> 1;
  
  integer_t new_x = new_bits1 | new_bits0;

  return new_x;
}

integer_t BIT_Swap4(integer_t x)
{ // меняет биты в каждой 4ке реверс bit0 < ->bit3, bit1 < ->bit2 ...
  integer_t bits0 = x & bit_mask_40;
  integer_t bits1 = x & bit_mask_41;
  integer_t bits2 = x & bit_mask_42;
  integer_t bits3 = x & bit_mask_43;

  integer_t new_bits0 = bits3 >> 3;
  integer_t new_bits1 = bits2 >> 1;
  integer_t new_bits2 = bits1 << 1;
  integer_t new_bits3 = bits0 << 3;

  integer_t new_x = new_bits3 | new_bits2 | new_bits1 | new_bits0;

  return new_x;
}

integer_t BIT_Swap8(integer_t x)
{ // меняет биты в каждой 8ке реверс bit0 < ->bit7, bit1 < ->bit6 ...
  return (integer_t) (x & bit_mask_80) << 7
                   | (x & bit_mask_81) << 5
                   | (x & bit_mask_82) << 3
                   | (x & bit_mask_83) << 1
                   | (x & bit_mask_84) >> 1
                   | (x & bit_mask_85) >> 3
                   | (x & bit_mask_86) >> 5
                   | (x & bit_mask_87) >> 7;
}

integer_t BIT_reverse_bit_blocks(integer_t x, unsigned int block_size)
{ // производит обмен битовых блоков размера block_size в числе Х, 
  // 1 - реверс битов, 2 - попарно b1b0 <-> b(n)b(n-1) ..., 4 - b3..b0 <-> 4 старших бита ...
  // 8 - побайтно (младший байт со старшим и т.д.), любое другое число - не меняет Х
  switch (block_size)
  {   case 1:   return BIT_1Reverse(x);
      case 2:   return BIT_2Reverse(x);
      case 4:   return BIT_4Reverse(x);
      case 8:   return BIT_8Reverse(x);
      default:  return x;
  }
}

integer_t BIT_reverse_IN_blocks(integer_t x, unsigned int block_size)
{  // производит обмен битов внутри битовых блоков размера block_size в числе Х, 
   // 1 - ничего, 2 - чётные биты меняются с нечётными, 4 - реверс в каждй 4ке битов
   // 8 - реверс битов в каждом байте, любое другое число - не меняет Х
  switch (block_size)
  {   case 1:   return x;
      case 2:   return BIT_Swap2(x);
      case 4:   return BIT_Swap4(x);
      case 8:   return BIT_Swap8(x);
      default:  return x;
  }
}

integer_t BIT_CycleLeft(integer_t x, unsigned int shift)
{ // циклический сдвиг <--- влево <---
  // shift по модулю количества битов, иначе тормозит на больших shift
  shift %= (sizeof(integer_t) * 8);
  for (; shift > 0; shift--)
  {                       // запомним удаляемый старший бит
    integer_t bit = (x & bit_mask_HIGH) ? bit_mask_LOW : 0;
    x = (x << 1) | bit;   // сдвиг на 1 и добавка запомненого в бит0
  }
  return x;
}

integer_t BIT_CycleRight(integer_t x, unsigned int shift)
{ // циклический сдвиг ---> вправо --->
  // shift по модулю количества битов, иначе тормозит на больших shift
  shift %= (sizeof(integer_t) * 8);
  for (; shift > 0; shift--)
  {                       // запомним удаляемый младший бит0
    integer_t bit = (x & bit_mask_LOW) ? bit_mask_HIGH : 0;
    x = (x >> 1) | bit;   // сдвиг на 1 и добавка запомненого в старший бит
  }
  return x;
}

integer_t BIT_CycleLeft_inBytes(integer_t x, unsigned int shift)
{ // циклический сдвиг <---  влево <--- (в каждом байте отдельно)
  // shift по модулю 8, иначе тормозит на больших shift
  shift %= 8; // циклический сдвиг байта на 8 не изменяет число
  while (shift)
  {
    // выделяем нужные биты и срузу их сдвигаем на новую позицию
    integer_t bits_7_to_0 = (x & bit_mask_87) >> 7;
    // маска для обнуления выделенных ранее битов в числе Х
    // иначе, они, сдвинувшись, займут чужое место в соседнем байте
    integer_t clear_mask = ~ bit_mask_87;
    // обнуляем эти биты, теперь там нули, можно записывать сохранённые ранее
    x &= clear_mask;
    // сдвигаем Х
    x <<= 1;
    // выделеные ранее биты (они уже в новой позиции) сливаем (суммируем) с Х
    x |= bits_7_to_0;
    shift--;
  }
  return x;
}

integer_t BIT_CycleRight_inBytes(integer_t x, unsigned int shift)
{ // циклический сдвиг ---> вправо ---> (в каждом байте отдельно)
  // shift по модулю 8, иначе тормозит на больших shift
  shift %= 8; // циклический сдвиг байта на 8 не изменяет число
  
  while (shift)
  {
    integer_t bits_0_to_7;
      
 // XXXXXXXXXXXXXXXXXX --- ещё не реализовано --- XXXXXXXXXXXXXXX

    shift--;
  }
  return x;
}
