#include "pch.h"
#include <stdlib.h>
#include "sort_methods.h"

// -----------------------------------------------------------
// ����������� ������� �� qsort() ��� ������
int _cmpInt(const void* a, const void* b)
{ 
  return *(int*)a - *(int*)b;   // ������� ��������� ����� ����� ��� qsort()
}

// ����������� ������� �� qsort()
extern void EtalonSort(int array[], int size)
{ // ������ ��� �������������� ������ ����������
  qsort(array, size, sizeof(int), _cmpInt); 
}

// -----------------------------------------------------------
// ��������� ������� 1
extern  void _bubbleSort_1(int array[], int size)
{
  int temp;
  // ���������� ������� ���������
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (array[j] > array[j + 1]) {
        // ������ �������� �������
        temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }
}

// -----------------------------------------------------------
// ��������� ������� 2 - ��������� ������ ��������
extern  void _bubbleSort_2(int array[], int size)
{
  int temp;
  int* start = array, * end = array + size, * i, * j;
  int* j_end = end - 1;
  // ���������� ������� ���������
  for (i = start; i < end; i++, j_end--) {
    for (j = start; j < j_end; j++) {
      if (*j > * (j + 1)) {
        // ������ �������� �������
        temp = *j;
        *j = *(j + 1);
        *(j + 1) = temp;
      }

    }
  }
}

// -----------------------------------------------------------
// �������
extern  void _selectSort_1(int array[], int size)
{
  for (int i = size - 1; i; i--)
  { // ����� � �����, ������ ���, �� ������� ��������
    int max = array[i];               // ���� ������ ��� �� ������������
    unsigned max_ind = i;             // ��� ������ ������������� ��������
    for (int j = i - 1; j >= 0; j--)  // �������� ��� �������� �����
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
// �������� ������� 1         // http://kvodo.ru/mergesort.html 
// � �������������� �������, ������� ������ �� ������ �������

void Merge_1(int array[], int first, int last)
{ //�������, ��������� ������� 
  int middle, start, final, j;
  // ������� ��������������� ������ (������ ����������� -
  // (������ - �� ���������� ��������, ���� �� ������������� �������)
  int* mas = (int*)malloc((last + 1) * sizeof(int));
  middle = (first + last) / 2;         //���������� �������� ��������
  start = first;                       //������ ����� �����
  final = middle + 1;                  //������ ������ �����
  for (j = first; j <= last; j++)      //��������� �� ������ �� �����
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
  //����������� ���������� � ������
  for (j = first; j <= last; j++) array[j] = mas[j];
  free(mas);
};

void MergeSort_1(int array[], int first, int last)
{
  //first, last � ������ ������� � ���������� ��������� ��������������
  if (first < last)
  {
    MergeSort_1(array, first, (first + last) / 2);     //���������� ����� �����
    MergeSort_1(array, (first + last) / 2 + 1, last);  //���������� ������ �����
    Merge_1(array, first, last);                       //������� ���� ������
  }
}

// ������ ��� �������������� ������ ����������
extern void _mergeSort_1(int array[], int size)
{
  MergeSort_1(array, 0, size - 1);
}


// -----------------------------------------------------------
// �������� ������� 2         // http://kvodo.ru/mergesort.html 
// � �������������� �������, �������� �������� ������ ������ 1 ���
static int* tempo = NULL;
void Merge_2(int array[], int first, int last)
{
  int middle, start, final, j;
  int* mas = tempo;
  middle = (first + last) / 2;         //���������� �������� ��������
  start = first;                       //������ ����� �����
  final = middle + 1;                  //������ ������ �����
  for (j = first; j <= last; j++)      //��������� �� ������ �� �����
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
  //����������� ���������� � ������
  for (j = first; j <= last; j++) array[j] = mas[j];

};

void MergeSort_2(int array[], int first, int last)
{
  //first, last � ������ ������� � ���������� ��������� ��������������
  if (first < last)
  {
    MergeSort_2(array, first, (first + last) / 2);     //���������� ����� �����
    MergeSort_2(array, (first + last) / 2 + 1, last);  //���������� ������ �����
    Merge_2(array, first, last);                       //������� ���� ������
  }
}

// ������ ��� �������������� ������ ����������, // � ��� ������ ������
extern void _mergeSort_2(int array[], int size)
{ // ��� ��������� ������ ���, ������� 1 ���, 
  // ������� ����� ���������� ���������� tempo
  tempo = (int*)malloc(size * sizeof(int));;
  MergeSort_2(array, 0, size - 1);
  free(tempo);
}


// -----------------------------------------------------------
/** https://ru.wikipedia.org/wiki/����������_��������
  * ��������� ������, ��������� ����������� ���������� ��������
  * up - ��������� �� ������, ������� ����� �����������
  * down - ��������� �� ������ �, ��� �������, ����� �� �������� ��� � 'up', ������������ ��� �����
  * left - ����� ������� �������, ��������� 0, ����� ����������� ������ � ������
  * right - ������ ������� �������, ��������� ����� ������� - 1, ����� ����������� ������ �� ���������� ��������
  * ����������: ��������� �� ��������������� ������. ��-�� ������������ ������ ������ ����������
  * ��������������� ������ ������� ����� ��������� ���� � 'up', ���� � 'down'
  **/
int* merge_sort_wiki(int* up, int* down, unsigned int left, unsigned int right)
{
  if (left == right)
  {
    down[left] = up[left];
    return down;
  }

  unsigned int middle = (left + right) / 2;

  // �������� � ��������
  int* l_buff = merge_sort_wiki(up, down, left, middle);
  int* r_buff = merge_sort_wiki(up, down, middle + 1, right);

  // ������� ���� ��������������� �������
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

// �������� ������ // https://ru.wikipedia.org/wiki/����������_��������
// ��� ��������� ������� ������ ���, ������� 1 ���, */
extern void _mergeSort_wiki(int array[], int size)
{ 
  int* temp = (int*)malloc(size * sizeof(int));
  int* result = merge_sort_wiki(array, temp, 0, size - 1);

  // ����������� ������ ���������� - ��������� ����� ���� � ����� ������� �� 2�
  if (result == temp) // ��� ��������� �� ��� ��� ����
    for (int i = 0; i < size; i++)
      array[i] = result[i];
  free(temp);
}

