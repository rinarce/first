// SummaSdachi.cpp : 
#include <stdio.h>

void InputIntArray(int array[], int n)
{   // ввод массива целых чисел длиной n
    for (int i = 0; i < n; i++)
        scanf_s("%d", &array[i]);
}

int MakeSum(int array[], int needSum, int useElements)
{   // функция пытается набрать сумму == needSum из элементов массива array
    // использую только первые useElements его элементов
    // если найдет - печатает эти элементы и возвращает 1
    // если не получилось - возвращает 0

    if (useElements == 1 && needSum != array[0])
        return 0;  // можно использовать только 1 элемент и сумма не получилась

    // попробуем использовать все оставшиеся элементы по очереди
    for (int i = 0; i < useElements; i++)
    {   // что если попробовать элемент array[i] ?
        int restSum = needSum - array[i];
        if (restSum == 0)
        {   // подходит идеально, печатаем его и возврат результата == 1
            printf("%d ", array[i]);
            return 1; // дальше не проверяем, уже найдено
        }
        else if (restSum > 0) // есть ещё остаток суммы
        {// пробуем варианты с этим элементом, используя только элементы до него (<-- левее)
            if (i >= 1 && MakeSum(array, restSum, i)) // i > 0, т.к. до array[0] ничего нет
            {   // MakeSum что-то нашёл (вернул 1) и в это случае уже напечатал
                // значит элемент array[i] теже подходит, печатаем его, возврат результата == 1
                printf("%d ", array[i]);
                return 1; // больше не искать
            }
        }
        else 
        {    // тут restSum < 0 значит элемент array[i] в данном случае
             // совершенно не подходит - он просто больше чем требуется
             // и в этом else ничего не далаем, просто пропускаем элемент
        }
    }
    return 0; // всё перепробовали, ничего не подошло
}

int main()
{
    int monety[101] = { 0 };
    int n_monet, summa;
    scanf_s("%d %d", &n_monet, &summa);
    InputIntArray(monety, n_monet);

    // пытаемся набрать сумму, используя все монеты
    if (MakeSum(monety, summa, n_monet) == 0)
        printf("-1"); // не получилось
    
    return 0;
}
