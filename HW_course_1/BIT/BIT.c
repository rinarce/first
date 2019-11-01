// BIT.cpp 
#include <stdio.h>
#include <locale.h>
#include "MyBITfuncs.h"

int main() {
  integer_t testNumber;
  setlocale(LC_ALL, "Russian");
  do {
    // Ввод
    testNumber = BitInputTestNumber();
    unsigned decWidth = BitCountDecimalDigits(testNumber);  // ширина в десятичном виде
    unsigned operand2;
    printf(" Введите операнд : ");
    scanf("%d", &operand2);

    // Расчёты
    integer_t xx1reverse = BitReverseBitsBlocks(testNumber, 1);
    decWidth = Max2Uns(decWidth, BitCountDecimalDigits(xx1reverse));
    integer_t xx2reverse = BitReverseBitsBlocks(testNumber, 2);
    decWidth = Max2Uns(decWidth, BitCountDecimalDigits(xx2reverse));
    integer_t xx4reverse = BitReverseBitsBlocks(testNumber, 4);
    decWidth = Max2Uns(decWidth, BitCountDecimalDigits(xx4reverse));
    integer_t xx8reverse = BitReverseBitsBlocks(testNumber, 8);
    decWidth = Max2Uns(decWidth, BitCountDecimalDigits(xx8reverse));
    integer_t xxswap2 = BitReverseInBlocks(testNumber, 2);
    decWidth = Max2Uns(decWidth, BitCountDecimalDigits(xxswap2));
    integer_t xxswap4 = BitReverseInBlocks(testNumber, 4);
    decWidth = Max2Uns(decWidth, BitCountDecimalDigits(xxswap4));
    integer_t xxswap8 = BitReverseInBlocks(testNumber, 8);
    decWidth = Max2Uns(decWidth, BitCountDecimalDigits(xxswap8));
    integer_t xxcycleL = BitCycleLeft(testNumber, operand2);
    decWidth = Max2Uns(decWidth, BitCountDecimalDigits(xxcycleL));
    integer_t xxcycleR = BitCycleRight(testNumber, operand2);
    decWidth = Max2Uns(decWidth, BitCountDecimalDigits(xxcycleR));
    integer_t xxcycleL_b = BitCycleInBytesLeft(testNumber, operand2);
    decWidth = Max2Uns(decWidth, BitCountDecimalDigits(xxcycleL_b));
    integer_t xxcycleR_b = BitCycleInBytesRight(testNumber, operand2);
    decWidth = Max2Uns(decWidth, BitCountDecimalDigits(xxcycleR_b));

    // Распечатка
    BitPrint("        Вы ввели :", testNumber, decWidth);
    BitPrint(" Реверс по битам :", xx1reverse, decWidth);
    BitPrint(" Реверс по 2 бит :", xx2reverse, decWidth);
    BitPrint(" Реверс по 4 бит :", xx4reverse, decWidth);
    BitPrint(" Реверс побайтно :", xx8reverse, decWidth);
    BitPrint(" Обмен бит в 2ке :", xxswap2, decWidth);
    BitPrint(" Обмен бит в 4ке :", xxswap4, decWidth);
    BitPrint(" Обмен бит в 8ке :", xxswap8, decWidth);
    BitPrint("   Цикл << числа :", xxcycleL, decWidth);
    BitPrint("   Цикл >> числа :", xxcycleR, decWidth);
    BitPrint("Цикл << в байтах :", xxcycleL_b, decWidth);
    BitPrint("Цикл >> в байтах :", xxcycleR_b, decWidth);

    printf("\n");

  } while (testNumber); // условие выхода из цикла -> число == 0

  return 0;
}
