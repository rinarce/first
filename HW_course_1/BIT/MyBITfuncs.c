#include "MyBITfuncs.h"
#include <stdio.h>
#pragma warning(disable:4996)   // for use scanf in VisualStudio


// битовые маски на все случаи ------------------------------------------------------------
// для реверса блоками, выделяют нужный блок  ---------------------------------------------
const integer_t s_bitMaskLow = ((integer_t)0b00000001);
const integer_t s_bitMaskHigh = ((integer_t)0b10000000) << ((sizeof(integer_t) - 1) * 8);

const integer_t s_bitMaskRev2Low = ((integer_t)0b00000011);
const integer_t s_bitMaskRev2Hight = ((integer_t)0b11000000) << ((sizeof(integer_t) - 1) * 8);

const integer_t s_bitMaskRev4Low = ((integer_t)0b00001111);
const integer_t s_bitMaskRev4Hight = ((integer_t)0b11110000) << ((sizeof(integer_t) - 1) * 8);

const integer_t s_bitMaskRev8Low = ((integer_t)0b11111111);
const integer_t s_bitMaskRev8Hight = ((integer_t)0b11111111) << ((sizeof(integer_t) - 1) * 8);

// для реверса внутри блоков --- выделяют нужные биты в каждом блоке ---------------------------------------
const integer_t s_bitMask20 = (integer_t)0b0101010101010101010101010101010101010101010101010101010101010101;
const integer_t s_bitMask21 = (integer_t)0b1010101010101010101010101010101010101010101010101010101010101010;

const integer_t s_bitMask40 = (integer_t)0b0001000100010001000100010001000100010001000100010001000100010001;
const integer_t s_bitMask41 = (integer_t)0b0010001000100010001000100010001000100010001000100010001000100010;
const integer_t s_bitMask42 = (integer_t)0b0100010001000100010001000100010001000100010001000100010001000100;
const integer_t s_bitMask43 = (integer_t)0b1000100010001000100010001000100010001000100010001000100010001000;

const integer_t s_bitMask80 = (integer_t)0b0000000100000001000000010000000100000001000000010000000100000001;
const integer_t s_bitMask81 = (integer_t)0b0000001000000010000000100000001000000010000000100000001000000010;
const integer_t s_bitMask82 = (integer_t)0b0000010000000100000001000000010000000100000001000000010000000100;
const integer_t s_bitMask83 = (integer_t)0b0000100000001000000010000000100000001000000010000000100000001000;
const integer_t s_bitMask84 = (integer_t)0b0001000000010000000100000001000000010000000100000001000000010000;
const integer_t s_bitMask85 = (integer_t)0b0010000000100000001000000010000000100000001000000010000000100000;
const integer_t s_bitMask86 = (integer_t)0b0100000001000000010000000100000001000000010000000100000001000000;
const integer_t s_bitMask87 = (integer_t)0b1000000010000000100000001000000010000000100000001000000010000000;

// вводит положительное число, преобразует его к типу integer_t
integer_t BitInputTestNumber()
{ MaxInt input_data;
  printf("   Введите число : ");
  scanf("%llu", &input_data);

  MaxInt alowed_num = (integer_t)(-1);
  if (alowed_num < input_data)
      printf("! Обрезано, макс : %llu\n", alowed_num);
  return (integer_t)input_data;
}

// ? сколько цифр понадобится для 10го представления Х
unsigned int BitCountDecimalDigits(integer_t x)
{ 
  unsigned int dec_width = 1;  // 1 в любом случае
  while (x /= 10)              // пока от деления на 10 получаем не 0
    dec_width++;               // значит нужны ещё позиции для 10 записи числа
  return dec_width;
}

unsigned int Max2Uns(unsigned int x1, unsigned int x2)    // находит максимальное значение 
{   return (x1 > x2) ? x1 : x2;   }

// печатает Х в разных представлениях по условию задачи
// text - пояснительный текст до числа
  // decimalWidth - получает извне, остальные рассчитывает
void BitPrint(const char text[], integer_t x, unsigned int decimalWidth) { 
  // пример 163 = 0xA3 = 10100011         ДЕС = НЕХ = БИН
  const int sizeBytes = sizeof(integer_t);
  const int sizeHexes = sizeof(integer_t) * 2;
  const int sizeBites = sizeof(integer_t) * 8;
  MaxInt xOutput = (MaxInt) x;
  char bits[sizeof(integer_t) * 8 + 1] = { 0 };  // +1 для конца строки

  printf("%s %*llu = 0x%0*llX = ", 
        text, decimalWidth, xOutput, sizeHexes, xOutput);

  for (int bit = sizeBites - 1; bit >= 0; --bit) {      // расчёт битов
    bits[bit] = (s_bitMaskLow & x) ? BIT_ONE_SYM : BIT_ZERO_SYM;
    x >>= 1;
  }
  // печать битов, для очень длинных (>32 бит) - с новой строки
  printf("%s%s\n", 
        ((sizeof(integer_t)>4) ? "\n               " : ""), bits);
}

// обращает порядок битов в Х
integer_t _bit1Reverse(integer_t x) { 
  integer_t maskHigh = s_bitMaskHigh;   // выделяет левый бит  (старший)
  integer_t maskLow = s_bitMaskLow;     // выделяет правый бит (младший)
  integer_t result = 0;                  // для накопления результата
  while (maskHigh > maskLow) {         // пока маски не пересекли друг друга

    integer_t newBitsLow = (x & maskHigh) ? maskLow : 0;  // выделяем 2 бита
    integer_t newBitsHight = (x & maskLow) ? maskHigh : 0;
                                               
    result = result | newBitsHight | newBitsLow;    // формируем результат
                                         // сдвигаем маски навстречу, к середине числа
    maskHigh >>= 1;                     // левую - вправо
    maskLow <<= 1;                      // правую - влево
  }
  return result;
}

// обращает порядок пар битов в Х
integer_t _bit2Reverse(integer_t x) { 
  integer_t maskLow  = s_bitMaskRev2Low;    // выделяет 2 левых бит  (старших)
  integer_t maskHigh = s_bitMaskRev2Hight;  // выделяет 2 правых бит (младших)
  integer_t result = 0;
  int delta = sizeof(integer_t) * 8 - 2;    // на сколько сдвигать первоначально
  while (delta > 0) {                       // биты выделяются и сразу сдвигаю на нужное расстояние
    integer_t newBitsLow = (x & maskHigh) >> delta;
    integer_t newBitsHight = (x & maskLow) << delta;

    // добавить к результату очередную порцию 
    result =  result | newBitsHight | newBitsLow;

    maskHigh >>= 2;
    maskLow <<= 2;
    delta -= 4;         // маски сходятся => сдвигать меньше
  }
  return result;
}

// обращает порядок четвёрок битов в Х
integer_t _bit4Reverse(integer_t x) { 
  integer_t maskLow = s_bitMaskRev4Low;     // выделяет 4 левых бит  (старших)
  integer_t maskHigh = s_bitMaskRev4Hight;  // выделяет 4 правых бит (младших)
  integer_t result = 0;
  int delta = sizeof(integer_t) * 8 - 4;    // на сколько сдвигать первоначально
  while (delta > 0) {                       // биты выделяются и сразу сдвигаю на нужное расстояние
    integer_t newBitsLow   = (x & maskHigh) >> delta;
    integer_t newBitsHight = (x & maskLow) << delta;

    // добавить к результату очередную порцию 
    result = result | newBitsHight | newBitsLow;

    maskHigh >>= 4;
    maskLow <<= 4;
    delta -= 8;         // маски сходятся => сдвигать меньше
  }
  return result;
}

// обращает порядок байтов в Х
integer_t _bit8Reverse(integer_t x) { 
  if (sizeof(integer_t) == 1) 
    return x; // для однобайтового числа перестановка байт не нужна
  integer_t maskLow  = s_bitMaskRev8Low;     // выделяет 8 левых бит  (старших)
  integer_t maskHigh = s_bitMaskRev8Hight;   // выделяет 8 правых бит (младших)
  integer_t result = 0;
  int delta = sizeof(integer_t) * 8 - 8;     // на сколько сдвигать первоначально
  while (delta > 0) {                        // биты выделяются и сразу сдвигаю на нужное расстояние
    integer_t newBitsLow = (x & maskHigh) >> delta;
    integer_t newBitsHight = (x & maskLow) << delta;

    // добавить к результату очередную порцию 
    result = result | newBitsHight | newBitsLow;

    maskHigh >>= 8;
    maskLow <<= 8;
    delta -= 16;         // маски сходятся => сдвигать меньше
  }

  return result;
}

// меняет биты попарно bit0<->bit1, bit2<->bit3 ...
integer_t _bitSwap2(integer_t x) { 
  integer_t bits0 = x & s_bitMask20;       // тут  чётные биты Х
  integer_t bits1 = x & s_bitMask21;       // тут нечётные биты Х
  
  integer_t new_bits1 = bits0 << 1;        // чётные биты стали нечётными
  integer_t new_bits0 = bits1 >> 1;        // и наоборот, нечет -> чет
  
  integer_t newX = new_bits1 | new_bits0; // сливаем их вместе

  return newX;
}

// меняет биты в каждой 4ке реверс bit0 < ->bit3, bit1 < ->bit2 ...
integer_t _bitSwap4(integer_t x)
{ 
  integer_t bits0 = x & s_bitMask40;    // в каждой четвёрке выделю биты 3 2 1 0
  integer_t bits1 = x & s_bitMask41;
  integer_t bits2 = x & s_bitMask42;
  integer_t bits3 = x & s_bitMask43;

  integer_t new_bits0 = bits3 >> 3;     // меняем местами (пока только сдвигаю)
  integer_t new_bits1 = bits2 >> 1;     // 3 <-> 0    2<->1
  integer_t new_bits2 = bits1 << 1;
  integer_t new_bits3 = bits0 << 3;

  // биты на своём месте, можно их соединить в новое число
  integer_t newX = new_bits3 | new_bits2 | new_bits1 | new_bits0;

  return newX;
}

// меняет биты в каждой 8ке реверс bit0 < ->bit7, bit1 < ->bit6 ...
integer_t _bitSwap8(integer_t x)
{ 
  return (integer_t) (x & s_bitMask80) << 7  // нулевые биты станут 7ми
                   | (x & s_bitMask81) << 5  // 1е -> 6ми
                   | (x & s_bitMask82) << 3  // 2е -> 5ми и т.д.
                   | (x & s_bitMask83) << 1 
                   | (x & s_bitMask84) >> 1
                   | (x & s_bitMask85) >> 3
                   | (x & s_bitMask86) >> 5
                   | (x & s_bitMask87) >> 7;
}

integer_t BitReverseBitsBlocks(integer_t x, unsigned int blockSize)
{ // производит обмен битовых блоков размера blockSize в числе Х, 
  // 1 - реверс битов, 2 - попарно b1b0 <-> b(n)b(n-1) ..., 4 - b3..b0 <-> 4 старших бита ...
  // 8 - побайтно (младший байт со старшим и т.д.), любое другое число - не меняет Х
  switch (blockSize)
  {   case 1:   return _bit1Reverse(x);
      case 2:   return _bit2Reverse(x);
      case 4:   return _bit4Reverse(x);
      case 8:   return _bit8Reverse(x);
      default:  return x;
  }
}

// производит обмен битов внутри битовых блоков размера blockSize в числе Х, 
   // 1 - ничего, 2 - чётные биты меняются с нечётными, 4 - реверс в каждй 4ке битов
   // 8 - реверс битов в каждом байте, любое другое число - не меняет Х
integer_t BitReverseInBlocks(integer_t x, unsigned int blockSize) {  
  switch (blockSize)  {   
    case 1:   return x;
    case 2:   return _bitSwap2(x);
    case 4:   return _bitSwap4(x);
    case 8:   return _bitSwap8(x);
    default:  return x;
  }
}

// циклический сдвиг <--- влево <---
integer_t BitCycleLeft(integer_t x, unsigned int shift) { 
  // shift по модулю количества битов, иначе тормозит на больших shift
  shift %= (sizeof(integer_t) * 8);
  for (; shift > 0; shift--) {      
    // запомним удаляемый старший бит
    integer_t bit = (x & s_bitMaskHigh) ? s_bitMaskLow : 0;
    x = (x << 1) | bit;   // сдвиг Х на 1 и добавка запомненого в бит0
  }
  return x;
}

// циклический сдвиг ---> вправо --->
integer_t BitCycleRight(integer_t x, unsigned int shift) { 
  // shift по модулю количества битов, иначе тормозит на больших shift
  shift %= (sizeof(integer_t) * 8);
  for (; shift > 0; shift--)  {                       
    // запомним удаляемый младший бит0
    integer_t bit = (x & s_bitMaskLow) ? s_bitMaskHigh : 0;
    x = (x >> 1) | bit;   // сдвиг на 1 и добавка запомненого в старший бит
  }
  return x;
}

// циклический сдвиг <---  влево <--- (в каждом байте отдельно)
integer_t BitCycleInBytesLeft(integer_t x, unsigned int shift) { 
  // shift по модулю 8, иначе тормозит на больших shift
  shift %= 8; // циклический сдвиг байта на 8 не изменяет число
  
  // маска для обнуления выделенных ранее битов в числе Х
  // иначе, они, сдвинувшись, займут чужое место в соседнем байте
  integer_t clearMask = ~s_bitMask87;
  while (shift) {
    // выделяем нужные биты и срузу их сдвигаем на новую позицию
    integer_t bits7to0 = (x & s_bitMask87) >> 7;
    x &= clearMask;  // обнуляем эти биты, теперь там нули, можно записывать сохранённые ранее
    x <<= 1;          // сдвигаем Х
    x |= bits7to0; // выделеные ранее биты (они уже в новой позиции) сливаем (суммируем) с Х
    shift--;
  }
  return x;
}

// циклический сдвиг ---> вправо ---> (в каждом байте отдельно)
integer_t BitCycleInBytesRight(integer_t x, unsigned int shift) { 
  // shift по модулю 8, иначе тормозит на больших shift
  shift %= 8; // циклический сдвиг байта на 8 не изменяет число

  // маска для обнуления выделенных ранее битов в числе Х
  // иначе, они, сдвинувшись, займут чужое место в соседнем байте
  integer_t clearMask = ~s_bitMask80;
  
  while (shift) {
    // выделяем нужные биты и срузу их сдвигаем на новую позицию
    integer_t bits0to7 = (x & s_bitMask80) << 7;
    x &= clearMask;       // обнуляем эти биты, теперь там нули, можно записывать сохранённые ранее
    x >>= 1;              // сдвигаем Х туда ->
    x |= bits0to7;     // выделеные ранее биты (они уже в новой позиции) сливаем (суммируем) с Х
    shift--;
  }
  return x;
}
