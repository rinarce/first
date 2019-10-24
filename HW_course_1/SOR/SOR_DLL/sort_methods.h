#pragma once

// ����������� ������� �� qsort() ��� ������
extern void EtalonSort(int array[], int size);


// ��������� ������� 1
extern void _bubbleSort_1(int array[], int size);
// ��������� ������� 2 - ��������� ������ ��������
extern void _bubbleSort_2(int array[], int size);


// �������
extern void _selectSort_1(int array[], int size);


// �������� ������� 1         // http://kvodo.ru/mergesort.html 
// � �������������� �������, ������� ������ �� ������ �������
extern void _mergeSort_1(int array[], int size);

// �������� ������� 2         // http://kvodo.ru/mergesort.html 
// � �������������� �������, �������� �������� ������ ������ 1 ���
extern void _mergeSort_2(int array[], int size);

// �������� ������� 3 
// �������� ������ // https://ru.wikipedia.org/wiki/����������_��������
// � ��� �������, ������ ������� 1 ��� ������� 
extern void _mergeSort_wiki(int array[], int size);

// ������� ����������  (�qsort�) ������ ����
// ������� // http://kvodo.ru/quicksort.html
extern void _qiuckSort_Hoare(int array[], int size);
