#include "pch.h"          // Visual Studio
#include <stdlib.h>
#include "sort_methods.h"

// -----------------------------------------------------------
// Стандартная функция Си qsort() как пример
int _cmpInt(const void* a, const void* b)
{ 
  return *(int*)a - *(int*)b;   // функция сравнения целых чисел для qsort()
}

// Стандартная функция Си qsort()
extern void ProperSort(int array[], int size)
{ // Обёртка для единообразного вызова сортировок
  qsort(array, size, sizeof(int), _cmpInt); 
}

// -----------------------------------------------------------
// сортировка Пузырьком - вариант 1
extern  void BubbleSort1(int array[], int size)
{
  int temp, finish;

  for (int i = 0; i < size - 1; i++) {
    finish = 1;
    for (int j = 0; j < size - i - 1; j++) {
      if (array[j] > array[j + 1]) 
      {
        temp = array[j];      // меняем элементы местами
        array[j] = array[j + 1];
        array[j + 1] = temp;
        finish = 0;           //  был обмен, работаем ещё
      }
    }
    if (finish)               // за проход не было обменов - всё
      break;                  // массив отсортирован
  }
}

// -----------------------------------------------------------
//  сортировка Пузырьком вариант 2 - указатели вместо массивов
extern  void BubbleSort2(int array[], int size)
{
  int temp, finish;
  int* start = array, * end = array + size, * i, * j;
  int* j_end = end - 1;

  for (i = start; i < end; i++, j_end--) {
    finish = 1;
    for (j = start; j < j_end; j++) {
      if (*j > * (j + 1)) 
      {
        temp = *j;          // меняем элементы местами
        *j = *(j + 1);
        *(j + 1) = temp;
        finish = 0;
      }
    }
    if (finish)             // за проход не было обменов - всё
      break;                // массив отсортирован
  }
}

// -----------------------------------------------------------
// Выбором
extern  void SelectSort1(int array[], int size)
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
// Вставками http://rosettacode.org/wiki/Sorting_algorithms/Insertion_sort
extern void InsertionSort(int array[], int size) 
{
  for (int i = 1; i < size; ++i) 
  {
    int tmp = array[i];
    int j = i;
    // tmp - очередной элемент проверим со всеми левее
    while (j > 0 && tmp < array[j - 1]) 
    { // перемещаем если tmp должен быть ещё левее
      array[j] = array[j - 1];  
      --j;
    }
    array[j] = tmp;  // tmp попал на своё место
  }
}

// -----------------------------------------------------------
// Слиянием вариант 1         // http://kvodo.ru/mergesort.html 
// С дополнительной памятью, выделяю память на каждом слиянии

//функция, сливающая массивы 
// С дополнительной памятью, выделяю память на каждом слиянии
void _merge1(int array[], int first, int last)
{ 
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

void _mergeSort1(int array[], int first, int last)
{
  //first, last – номера первого и последнего элементов соответственно
  if (first < last)
  {
    _mergeSort1(array, first, (first + last) / 2);     //сортировка левой части
    _mergeSort1(array, (first + last) / 2 + 1, last);  //сортировка правой части
    _merge1(array, first, last);                       //слияние двух частей
  }
}

// Обёртка для единообразного вызова сортировок
extern void MergeSort1(int array[], int size)
{
  _mergeSort1(array, 0, size - 1);
}


// -----------------------------------------------------------
// Слиянием вариант 2         // http://kvodo.ru/mergesort.html 
// С дополнительной памятью, выделяю память только 1 раз
static int* s_tempo = NULL;
void _merge2(int array[], int first, int last)
{
  int middle, start, final, j;
  int* mas = s_tempo;
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

void _mergeSort2(int array[], int first, int last)
{
  //first, last – номера первого и последнего элементов соответственно
  if (first < last)
  {
    _mergeSort2(array, first, (first + last) / 2);     //сортировка левой части
    _mergeSort2(array, (first + last) / 2 + 1, last);  //сортировка правой части
    _merge2(array, first, last);                       //слияние двух частей
  }
}

// Обёртка для единообразного вызова сортировок, // и тут выделю память
extern void merge_sort_2(int array[], int size)
{ // без выделения каждый раз, выделяю 1 раз, 
  // передаю через глобальную переменную s_tempo
  s_tempo = (int*)malloc(size * sizeof(int));;
  _mergeSort2(array, 0, size - 1);
  free(s_tempo);
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
int* _mergeSortWiki(int* up, int* down, unsigned int left, unsigned int right)
{
  if (left == right)
  {
    down[left] = up[left];
    return down;
  }

  unsigned int middle = (left + right) / 2;

  // разделяй и сортируй
  int* l_buff = _mergeSortWiki(up, down, left, middle);
  int* r_buff = _mergeSortWiki(up, down, middle + 1, right);

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
// только без выделения массива каждый раз, выделяю 1 раз, */
extern void MergeSortWiki(int array[], int size)
{ 
  if (size <= 0) return; // с нулевым размером не дружит

  int* temp = (int*)malloc(size * sizeof(int));
  int* result = _mergeSortWiki(array, temp, 0, size - 1);

  // особенности данной реализации - результат может быть в любом массиве из 2х
  if (result == temp) // тут результат не там где надо
    for (int i = 0; i < size; i++)
      array[i] = result[i];
  free(temp);
}


// -----------------------------------------------------------
// Быстрая сортировка  («qsort») Чарльз Хоар (Charles Antony Richard Hoare)
// вариант // http://kvodo.ru/quicksort.html
void _qiuckSortHoare(int* array, int first, int last)
{
  int mid, count;
  int f = first, l = last;
  mid = array[(f + l) / 2]; //вычисление опорного элемента
  do
  {
    while (array[f] < mid) f++;
    while (array[l] > mid) l--;
    if (f <= l) //перестановка элементов
    {
      count = array[f];
      array[f] = array[l];
      array[l] = count;
      f++;
      l--;
    }
  } while (f < l);
  if (first < l) _qiuckSortHoare(array, first, l);
  if (f < last) _qiuckSortHoare(array, f, last);
}

// Быстрая сортировка  («qsort») Чарльз Хоар (Charles Antony Richard Hoare)
// вариант // http://kvodo.ru/quicksort.html
// вариант - для малых размеров переходить на другую сортировку
void _qiuckSortHoare2(int* mas, int first, int last)
{
  int size = last - first + 1;
  if (size < 66)  // меньше этого размера не сортировать (размер с потолка)
  {
    return; // так лучше, ничего не делать, а потом отсортировать весь
    InsertionSort(mas + first, size); // вар 2
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
  if (first < l) _qiuckSortHoare2(mas, first, l);
  if (f < last) _qiuckSortHoare2(mas, f, last);
}


// Обёртка для единообразного вызова сортировок,
// Быстрая сортировка  («qsort») Чарльз Хоар
// вариант // http://kvodo.ru/quicksort.html
extern void QiuckSortHoare(int array[], int size)
{
  _qiuckSortHoare(array, 0, size - 1);
}

// Обёртка для единообразного вызова сортировок,
// Быстрая сортировка  («qsort») Чарльз Хоар
// вариант // http://kvodo.ru/quicksort.html
// вариант - для малых размеров переходить на другую сортировку
extern void QiuckSortHoare2(int array[], int size)
{
  _qiuckSortHoare2(array, 0, size - 1);
  // остались неотсортированные кусочки в массиве - отсортируем ВСТАВКАМИ
  InsertionSort(array, size);   
}


// -----------------------------------------------------------
// Гномья сортировка Hamid Sarbazi-Azad (вставками)
  extern void GnomeSort(int array[], int size)
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
        int temp = array[j];      // _swapUnsigned
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
extern void ShellSort2(int array[], int size)
{ 
  register int i, j, gap, k, x;
  // int a[5] = { 9, 5, 3, 2, 1 }; /* Пример из книги Герберта Шилдта */
  // другой вариант https://habr.com/ru/post/204968/
  // или http://rosettacode.org/wiki/Sorting_algorithms/Shell_sort#C.2B.2B
  int a[9] = { 1750, 701, 301, 132, 57, 23, 10, 4, 1 };
  

  for (k = 0; k < 9; k++) {
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
// переделан из варианта C++
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

extern void ShellSort3(int array[], int size) {
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
extern void CombSort(int array[], int size)
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
extern void CombSort2(int array[], int size)
{
  register int i, j, gap, temp, swapped = 1;

  gap = size;
  while (gap > 1 || swapped == 1)
  {
    gap = gap * 10 / 13;
    if (gap == 9 || gap == 10) gap = 11;
    if (gap < 1) gap = 1;
    swapped = 0;
    for (i = 0, j = gap; j < size; i++, j++)
    {
      if (array[i] > array[j])
      {
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        swapped = 1;
      }
    }
  }
}



// -----------------------------------------------------------
// Radix sort
// http://rosettacode.org/wiki/Sorting_algorithms/Radix_sort#C

static void _swapUnsigned(unsigned* a, unsigned* b) {
  unsigned tmp = *a;
  *a = *b;
  *b = tmp;
}

/* sort unsigned ints */

static void _radixSortUnsigned(unsigned* from, unsigned* to, unsigned bit)
{
  if (!bit || to < from + 1) return;
  
  unsigned* ll = from, * rr = to - 1;
  for (;;) {
    /* find left most with bit, and right most without bit, _swapUnsigned */
    while (ll < rr && !(*ll & bit)) ll++;
    while (ll < rr && (*rr & bit)) rr--;
    if (ll >= rr) break;
    // _swapUnsigned(ll, rr);
    unsigned temp = *ll;
    *ll = *rr;
    *rr = temp;
  }

  if (!(bit & *ll) && ll < to) ll++;
  bit >>= 1;

  _radixSortUnsigned(from, ll, bit);
  _radixSortUnsigned(ll, to, bit);
}

/* sort signed ints: flip highest bit, sort as unsigned, flip back */
static void _radixSortSigned(int* array, const size_t size)
{
  size_t i;
  unsigned* unsigned_array = (unsigned*)array;

  for (i = 0; i < size; i++)          // избавляемся от знака
    unsigned_array[i] ^= INT_MIN;

  _radixSortUnsigned(unsigned_array, unsigned_array + size, INT_MIN);

  for (i = 0; i < size; i++)          // восстанавливаем знак обратно
    unsigned_array[i] ^= INT_MIN;
}

// обёртка
extern void RadixSort(int array[], int size)
{
  _radixSortSigned(array, size); // для целых со знаком
}


// -----------------------------------------------------------
// Пирамидальная https://www.codelab.ru/task/pyramid_sort/

/* Функция "балансировки" пирамиды.   (просеивания, добавления элементов) */
void _screening(int array[], int k, int n) 
{
  /* Это чтобы при k=0 и n=0 не делалось лишней  перестановки*/
  if (0 == n) return;

  int tmp, childPos;
  tmp = array[k];

  while (k <= n / 2) 
  {
    childPos = 2 * k;  // Левый ребенок элемента k

    // выбираем большего ребенка элемента k из 2-х: либо левый, либо правый
    if (childPos < n && array[childPos] < array[childPos + 1]) 
    {
      childPos++;
    }
    
    /* Если родитель x[k] больше всех своих детей,
       то ничего не делаем, он стоит на правильном месте */
    if (tmp >= array[childPos]) break;

    // иначе - меняем x[k] с наибольшим ребенком
    array[k] = array[childPos];
    k = childPos;
  }
  array[k] = tmp;
}


extern void PyramidSort(int array[], int size) 
{
  register int i, tmp;

  // Построение пирамиды 
  for (i = size / 2; i >= 0; i--) 
  {
    _screening(array, i, size - 1);
  }

  /* Формирование конечной отсортированной
     последовательности + "балансирование" пирамиды */
  for (i = size - 1; i > 0; i--) 
  {
    // меняем первый с последним 
    tmp = array[0];
    array[0] = array[i];
    array[i] = tmp;

    /* Восстановление баланса  для пирамиды x[0..i-2] */
    _screening(array, 0, i - 1);
  }
}



// -----------------------------------------------------------
// Heap sort 
// http://rosettacode.org/wiki/Sorting_algorithms/Heapsort
int _maxHS(int array[], int size, int i, int j, int k)
{
  int mx = i;
  
  if (j < size && array[j] > array[mx])
      mx = j;
  
  if (k < size && array[k] > array[mx])
      mx = k;
  
  return mx;
}

void _downHeap(int array[], int n, int i) 
{
  while (1) 
  {
    int j = _maxHS(array, n, i, 2 * i + 1, 2 * i + 2);
    
    if (j == i)   break;
    
    int t = array[i];
    array[i] = array[j];
    array[j] = t;
    i = j;
  }
}

extern void HeapSort(int array[], int size) 
{
  int i;
  for (i = (size - 2) / 2; i >= 0; i--) 
  {
    _downHeap(array, size, i);
  }
  for (i = 0; i < size; i++) 
  {
    int t = array[size - i - 1];
    array[size - i - 1] = array[0];
    array[0] = t;

    _downHeap(array, size - i - 1, 0);
  }
}