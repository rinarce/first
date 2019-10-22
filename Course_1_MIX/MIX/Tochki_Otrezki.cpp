// Tochki_Otrezki.cpp
#include <stdio.h>
#include <stdlib.h>

void InputIntArray(int array[], int n)
{   // ввод массива целых чисел длиной n
    for (int i = 0; i < n; i++)
        scanf_s("%d", &array[i]);
}

int cmpInt(const void* a, const void* b) 
{ // функция сравнения целых чисел для qsort()
    return *(int*)a - *(int*)b;
}


void SortIntArray(int array[], int len)
{   // сортирует массив целых чисел длиной len по возрастанию
    
    // пока воспользуюсь qsort() из <stdlib.h>
    // https://ru.wikibooks.org/wiki/Язык_Си_в_примерах/Сортировка 
    // https://stackoverflow.com/questions/1787996/c-library-function-to-do-sort

    // https://github.com/swenson/sort -- другой вариант самых разных сортировок
    // https://habr.com/ru/post/335920/

    qsort(array, len, sizeof(int), cmpInt);
}

int ArraySearchGE(int array[], int len, int x)
{   // в сортированном массиве array длиной len находит индекс элемента,
    // который больше либо равен Х =>     array[result] >= x
    // если таких нет - возвращает len (т.е. за последним)

    /*
    // пока тупой линейный поиск
    for (int i = 0; i < len; i++)
        if (array[i] >= x)
            return i;
    return len;
    */
    
    // бинарный поиск
    int l = 0, r = len - 1;
    while (l < r)
    {
      int m = l + (r - l) / 2;
      if (array[m] >= x)
        r = m;
      else
        l = m + 1;
    }
    return l;
}

  
int ArraySearchGT(int array[], int len, int x)
{   // в сортированном массиве array длиной len находит индекс элемента,
    // который больше Х =>     array[result] > x   
    // если таких нет - возвращает len (т.е. за последним)
    /*
    // пока тупой линейный поиск
    for (int i = 0; i < len; i++)
        if (array[i] > x)
            return i;
    return len;
    */

    // бинарный поиск
    int l = 0, r = len - 1;
    while (l < r)
    {
      int m = r - (r - l) / 2;
      if (array[m] <= x)
        l = m;
      else
        r = m - 1;
    }
    return l + 1;

}


int main()
{
    int n_tockek, m_otrezkov;
    int tochki[100000] = { 0 };
    scanf_s("%d %d", &n_tockek, &m_otrezkov);

    InputIntArray(tochki, n_tockek);
    SortIntArray(tochki, n_tockek);

    for (int i = 0; i < m_otrezkov; i++)
    {
        int left, right;            // границы отрезка
        scanf_s("%d %d", &left, &right);
        
        // находим индекс первой точки >= левой границы отрезка 
        int leftIndex = ArraySearchGE(tochki, n_tockek, left);

        // находим индекс первой точки > правой границы отрезка
        int rightIndex = ArraySearchGT(tochki, n_tockek, right);

        printf("%d\n", rightIndex - leftIndex);
    }
    
    return 0;
}
