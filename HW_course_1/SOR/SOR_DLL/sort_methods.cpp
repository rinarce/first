#include "pch.h"
#include <stdlib.h>
#include "sort_methods.h"

// -----------------------------------------------------------
// Стандартная функция Си qsort() как пример
int _cmpInt(const void* a, const void* b)
{ 
  return *(int*)a - *(int*)b;   // функция сравнения целых чисел для qsort()
}

// Стандартная функция Си qsort()
extern void EtalonSort(int array[], int size)
{ // Обёртка для единообразного вызова сортировок
  qsort(array, size, sizeof(int), _cmpInt); 
}

// -----------------------------------------------------------
// Пузырьком вариант 1
extern  void _bubbleSort_1(int array[], int size)
{
  int temp, finish;
  // Сортировка массива пузырьком

  for (int i = 0; i < size - 1; i++) {
    finish = 1;
    for (int j = 0; j < size - i - 1; j++) {
      if (array[j] > array[j + 1]) {
        // меняем элементы местами
        temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
        finish = 0;          //  был обмен
      }
    }
    if (finish)
      break;
  }
}

// -----------------------------------------------------------
// Пузырьком вариант 2 - указатели вместо массивов
extern  void _bubbleSort_2(int array[], int size)
{
  int temp;
  int* start = array, * end = array + size, * i, * j;
  int* j_end = end - 1;
  // Сортировка массива пузырьком
  for (i = start; i < end; i++, j_end--) {
    for (j = start; j < j_end; j++) {
      if (*j > * (j + 1)) {
        // меняем элементы местами
        temp = *j;
        *j = *(j + 1);
        *(j + 1) = temp;
      }

    }
  }
}

// -----------------------------------------------------------
// Выбором
extern  void _selectSort_1(int array[], int size)
{
  for (int i = size - 1; i; i--)
  { // начнём с конца, просто так, до второго элемента
    int max = array[i];               // пока примем его за максимальный
    unsigned max_ind = i;             // это индекс максимального элемента
    for (int j = i - 1; j >= 0; j--)  // проверим все элементы левее
      if (array[j] > max)
      {
        max = array[j];
        max_ind = j;
      }
    if (max_ind != i)
    {
      int temp = array[i];
      array[i] = array[max_ind];
      array[max_ind] = temp;
    }
  }
}

// -----------------------------------------------------------
// Слиянием вариант 1         // http://kvodo.ru/mergesort.html 
// С дополнительной памятью, выделяю память на каждом слиянии

void Merge_1(int array[], int first, int last)
{ //функция, сливающая массивы 
  int middle, start, final, j;
  // выделяю вспомогательный массив (размер неоптимален -
  // (размер - по последнему элементу, чтоб не пересчитывать индексы)
  int* mas = (int*)malloc((last + 1) * sizeof(int));
  middle = (first + last) / 2;         //вычисление среднего элемента
  start = first;                       //начало левой части
  final = middle + 1;                  //начало правой части
  for (j = first; j <= last; j++)      //выполнять от начала до конца
    if ((start <= middle)
      && ((final > last) || (array[start] < array[final])))
    {
      mas[j] = array[start];
      start++;
    }
    else
    {
      mas[j] = array[final];
      final++;
    }
  //возвращение результата в список
  for (j = first; j <= last; j++) array[j] = mas[j];
  free(mas);
};

void MergeSort_1(int array[], int first, int last)
{
  //first, last – номера первого и последнего элементов соответственно
  if (first < last)
  {
    MergeSort_1(array, first, (first + last) / 2);     //сортировка левой части
    MergeSort_1(array, (first + last) / 2 + 1, last);  //сортировка правой части
    Merge_1(array, first, last);                       //слияние двух частей
  }
}

// Обёртка для единообразного вызова сортировок
extern void _mergeSort_1(int array[], int size)
{
  MergeSort_1(array, 0, size - 1);
}


// -----------------------------------------------------------
// Слиянием вариант 2         // http://kvodo.ru/mergesort.html 
// С дополнительной памятью, попробую выделять память только 1 раз
static int* tempo = NULL;
void Merge_2(int array[], int first, int last)
{
  int middle, start, final, j;
  int* mas = tempo;
  middle = (first + last) / 2;         //вычисление среднего элемента
  start = first;                       //начало левой части
  final = middle + 1;                  //начало правой части
  for (j = first; j <= last; j++)      //выполнять от начала до конца
    if ((start <= middle)
      && ((final > last) || (array[start] < array[final])))
    {
      mas[j] = array[start];
      start++;
    }
    else
    {
      mas[j] = array[final];
      final++;
    }
  //возвращение результата в список
  for (j = first; j <= last; j++) array[j] = mas[j];

};

void MergeSort_2(int array[], int first, int last)
{
  //first, last – номера первого и последнего элементов соответственно
  if (first < last)
  {
    MergeSort_2(array, first, (first + last) / 2);     //сортировка левой части
    MergeSort_2(array, (first + last) / 2 + 1, last);  //сортировка правой части
    Merge_2(array, first, last);                       //слияние двух частей
  }
}

// Обёртка для единообразного вызова сортировок, // и тут выделю память
extern void _mergeSort_2(int array[], int size)
{ // без выделения каждый раз, выделяю 1 раз, 
  // передаю через глобальную переменную tempo
  tempo = (int*)malloc(size * sizeof(int));;
  MergeSort_2(array, 0, size - 1);
  free(tempo);
}


// -----------------------------------------------------------
/** https://ru.wikipedia.org/wiki/Сортировка_слиянием
  * Сортирует массив, используя рекурсивную сортировку слиянием
  * up - указатель на массив, который нужно сортировать
  * down - указатель на массив с, как минимум, таким же размером как у 'up', используется как буфер
  * left - левая граница массива, передайте 0, чтобы сортировать массив с начала
  * right - правая граница массива, передайте длину массива - 1, чтобы сортировать массив до последнего элемента
  * возвращает: указатель на отсортированный массив. Из-за особенностей работы данной реализации
  * отсортированная версия массива может оказаться либо в 'up', либо в 'down'
  **/
int* merge_sort_wiki(int* up, int* down, unsigned int left, unsigned int right)
{
  if (left == right)
  {
    down[left] = up[left];
    return down;
  }

  unsigned int middle = (left + right) / 2;

  // разделяй и сортируй
  int* l_buff = merge_sort_wiki(up, down, left, middle);
  int* r_buff = merge_sort_wiki(up, down, middle + 1, right);

  // слияние двух отсортированных половин
  int* target = l_buff == up ? down : up;

  unsigned int l_cur = left, r_cur = middle + 1;
  for (unsigned int i = left; i <= right; i++)
  {
    if (l_cur <= middle && r_cur <= right)
    {
      if (l_buff[l_cur] < r_buff[r_cur])
      {
        target[i] = l_buff[l_cur];
        l_cur++;
      }
      else
      {
        target[i] = r_buff[r_cur];
        r_cur++;
      }
    }
    else if (l_cur <= middle)
    {
      target[i] = l_buff[l_cur];
      l_cur++;
    }
    else
    {
      target[i] = r_buff[r_cur];
      r_cur++;
    }
  }
  return target;
}

// алгоритм отсюда // https://ru.wikipedia.org/wiki/Сортировка_слиянием
// без выделения массива каждый раз, выделяю 1 раз, */
extern void _mergeSort_wiki(int array[], int size)
{ 
  int* temp = (int*)malloc(size * sizeof(int));
  int* result = merge_sort_wiki(array, temp, 0, size - 1);

  // особенности данной реализации - результат может быть в любом массиве из 2х
  if (result == temp) // тут результат не там где надо
    for (int i = 0; i < size; i++)
      array[i] = result[i];
  free(temp);
}


// -----------------------------------------------------------
// Быстрая сортировка  («qsort») Чарльз Хоар (Charles Antony Richard Hoare)
// вариант // http://kvodo.ru/quicksort.html
void qiuckSort_Hoare(int* mas, int first, int last)
{
  int mid, count;
  int f = first, l = last;
  mid = mas[(f + l) / 2]; //вычисление опорного элемента
  do
  {
    while (mas[f] < mid) f++;
    while (mas[l] > mid) l--;
    if (f <= l) //перестановка элементов
    {
      count = mas[f];
      mas[f] = mas[l];
      mas[l] = count;
      f++;
      l--;
    }
  } while (f < l);
  if (first < l) qiuckSort_Hoare(mas, first, l);
  if (f < last) qiuckSort_Hoare(mas, f, last);
}

// Быстрая сортировка  («qsort») Чарльз Хоар (Charles Antony Richard Hoare)
// вариант // http://kvodo.ru/quicksort.html
// вариант - для малых размеров переходить на другую сортировку
// чё-то не улучшает
void qiuckSort_Hoare_2(int* mas, int first, int last)
{
  int size = last - first + 1;
  if (size < 666)
  { 
    ShellSort(mas + first, size);
    
  }
  
  int mid, count;
  int f = first, l = last;
  mid = mas[(f + l) / 2]; //вычисление опорного элемента
  do
  {
    while (mas[f] < mid) f++;
    while (mas[l] > mid) l--;
    if (f <= l) //перестановка элементов
    {
      count = mas[f];
      mas[f] = mas[l];
      mas[l] = count;
      f++;
      l--;
    }
  } while (f < l);
  if (first < l) qiuckSort_Hoare_2(mas, first, l);
  if (f < last) qiuckSort_Hoare_2(mas, f, last);
}


// Обёртка для единообразного вызова сортировок,
// Быстрая сортировка  («qsort») Чарльз Хоар
// вариант // http://kvodo.ru/quicksort.html
extern void _qiuckSort_Hoare(int array[], int size)
{
  qiuckSort_Hoare(array, 0, size - 1);
}

// Обёртка для единообразного вызова сортировок,
// Быстрая сортировка  («qsort») Чарльз Хоар
// вариант // http://kvodo.ru/quicksort.html
// вариант - для малых размеров переходить на другую сортировку
extern void _qiuckSort_Hoare_2(int array[], int size)
{
  qiuckSort_Hoare_2(array, 0, size - 1);
}


// -----------------------------------------------------------
// Гномья сортировка Hamid Sarbazi-Azad (вставками)
  extern void gnomeSort(int array[], int size)
{
  int i = 1, j = 2;               // j граница, до которой дошёл гном
  while (i < size)
  {
    if (array[i - 1] <= array[i]) // пока  соблюдается порядок
    {
      i = j;                      // гном прыгает вправо
      j++;
    }
    else
    { // нарушен порядок => поменять местами, и проверить чуть левее 
      // гном несёт число к началу, пока не найдёт ему место
      int t = array[i]; array[i] = array[i - 1]; array[i - 1] = t;
      i--;        // проверяем ближе к началу, возможно придётся сдвигать ещё
      if (i == 0) // если гном дошёл до 0 => прыгнуть на j
      { i = j;
        j++;      // в следующий раз прыгать дальше
      }
    }
  }
}


// -----------------------------------------------------------
//сортировка Шелла
extern void ShellSort(int array[], int size)
{
  int d = size / 2;
  while (d > 0)
  {
    for (int i = 0; i < size - d; i++)
    {
      int j = i;
      while (j >= 0 && array[j] > array[j + d])
      {
        int temp = array[j];      // swap
        array[j] = array[j + d]; 
        array[j + d] = temp;
        j--;
      }
    }
    d = d / 2;
  }
}

// -----------------------------------------------------------
//сортировка Шелла  /* Пример из книги Герберта Шилдта */
// https://ru.wikibooks.org/wiki/Реализации_алгоритмов/Сортировка/Шелла
// фиксированные значения расстояния между сравнениями
extern void ShellSort_2(int array[], int size)
{ 
  register int i, j, gap, k, x;
  // int a[5] = { 9, 5, 3, 2, 1 }; /* Пример из книги Герберта Шилдта */
  // другой вариант https://habr.com/ru/post/204968/
  int a[8] = { 701, 301, 132, 57, 23, 10, 4, 1 };

  for (k = 0; k < 8; k++) {
    gap = a[k];
    for (i = gap; i < size; ++i) {
      x = array[i];
      for (j = i - gap; (x < array[j]) && (j >= 0); j = j - gap)
        array[j + gap] = array[j];
      array[j + gap] = x;
    }
  }
}

//сортировка Шелла // расстояния между сравнениями по формуле Роберта Седжвика
// https://ru.wikibooks.org/wiki/Реализации_алгоритмов/Сортировка/Шелла
// переделан из непонятного варианта C++
// http://algolist.manual.ru/sort/shell_sort.php 
int increment(int inc[], int size) { // Robert Sedgewick
  // inc[] массив, в который заносятся инкременты 
  // size размерность этого массива
  int p1, p2, p3, s;

  p1 = p2 = p3 = 1;
  s = -1;
  do {// заполняем массив элементов по формуле Роберта Седжвика
    if (++s % 2) {
      inc[s] = 8 * p1 - 6 * p2 + 1;
    }
    else {
      inc[s] = 9 * p1 - 9 * p3 + 1;
      p2 *= 2;
      p3 *= 2;
    }
    p1 *= 2;
    // заполняем массив, пока текущая инкремента хотя бы в 3 раза меньше количества элементов в массиве
  } while (3 * inc[s] < size);

  return s > 0 ? --s : 0;// возвращаем количество элементов в массиве
}

extern void ShellSort_3(int array[], int size) {
  // inc инкремент, расстояние между элементами сравнения
  // seq[40] массив, в котором хранятся инкременты
  int inc, i, j, seq[40];
  int s;//количество элементов в массиве seq[40]

  // вычисление последовательности приращений
  s = increment(seq, size);
  while (s >= 0) {
    //извлекаем из массива очередную инкременту
    inc = seq[s--];
    // сортировка вставками с инкрементами inc
    for (i = inc; i < size; i++) {
      int temp = array[i];
      // сдвигаем элементы до тех пор, пока не дойдем до конца или не упорядочим в нужном порядке
      for (j = i - inc; (j >= 0) && (array[j] > temp); j -= inc)
        array[j + inc] = array[j];
      // после всех сдвигов ставим на место j+inc элемент, который находился на i месте
      array[j + inc] = temp;
    }
  }
}






// -----------------------------------------------------------
//сортировка расчёска // https://ru.wikipedia.org/wiki/Сортировка_расчёской
extern void combSort(int array[], int size)
{
  double fakt = 1.2473309; // фактор уменьшения
  register int i, j, temp, finish, step = size - 1;

  while (step >= 1)
  {
    for (i = 0; i + step < size; ++i)
    {
      if (array[i] > array[i + step])
      {
        temp = array[i];
        array[i] = array[i + step];
        array[i + step] = temp;
      }
    }
    step = (int) (step / fakt);
  }
  // сортировка пузырьком
  for (i = 0; i < size - 1; i++)
  {
    finish = 1;
    for (j = 0; j < size - i - 1; j++)
    {
      if (array[j] > array[j + 1])
      {
        temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
        finish = 0;
      }
    }
    if (finish)
      break;
  }
}

// http://rosettacode.org/wiki/Sorting_algorithms/Comb_sort#C
extern void CombSort_2(int a[], int nElements)
{
  register int i, j, gap, temp, swapped = 1;

  gap = nElements;
  while (gap > 1 || swapped == 1)
  {
    gap = gap * 10 / 13;
    if (gap == 9 || gap == 10) gap = 11;
    if (gap < 1) gap = 1;
    swapped = 0;
    for (i = 0, j = gap; j < nElements; i++, j++)
    {
      if (a[i] > a[j])
      {
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
        swapped = 1;
      }
    }
  }
}



// -----------------------------------------------------------
// Radix sort
// http://rosettacode.org/wiki/Sorting_algorithms/Radix_sort#C

static void swap(unsigned* a, unsigned* b) {
  unsigned tmp = *a;
  *a = *b;
  *b = tmp;
}

/* sort unsigned ints */
static void rad_sort_u(unsigned* from, unsigned* to, unsigned bit)
{
  if (!bit || to < from + 1) return;

  unsigned* ll = from, * rr = to - 1;
  for (;;) {
    /* find left most with bit, and right most without bit, swap */
    while (ll < rr && !(*ll & bit)) ll++;
    while (ll < rr && (*rr & bit)) rr--;
    if (ll >= rr) break;
    swap(ll, rr);
  }

  if (!(bit & *ll) && ll < to) ll++;
  bit >>= 1;

  rad_sort_u(from, ll, bit);
  rad_sort_u(ll, to, bit);
}

/* sort signed ints: flip highest bit, sort as unsigned, flip back */
static void radix_sort(int* a, const size_t len)
{
  size_t i;
  unsigned* x = (unsigned*)a;

  for (i = 0; i < len; i++)
    x[i] ^= INT_MIN;

  rad_sort_u(x, x + len, INT_MIN);

  for (i = 0; i < len; i++)
    x[i] ^= INT_MIN;
}
// обёртка
extern void Radix_Sort(int array[], int size)
{
  radix_sort(array, size);
}