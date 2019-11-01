#include <stdio.h>

void PrintPower(unsigned long long int divisor, int power) {
  static int wasFirst = 0;	  // == 0 пока не напечатана первая группа
  if (wasFirst++)             // больше уже не будет == 0
    printf(" * %lld^%d", divisor, power); // не первый раз
  else
    printf("%lld^%d", divisor, power);    // первый раз
}

int main() {
  unsigned long long int n, divisor = 2;
  scanf_s("%llu", &n);
  if (n == 1) { // особый случай
    PrintPower(n, 1);
    return 0;
  }
  while (divisor * divisor <= n) {  // делитель не может быть больше sqrt(n)
    if ((n % divisor) == 0) {     // делится нацело
      int power = 0;
      while ((n % divisor) == 0) { // делим пока делится
        power++;
        n /= divisor;
      }
      PrintPower(divisor, power);
    }
    divisor++; // перебор делителей подряд, но можно улучшить
  }
  if (n != 1)    // последнее оставшееся число не выводить * 1^1
    PrintPower(n, 1);
  return 0;
}
