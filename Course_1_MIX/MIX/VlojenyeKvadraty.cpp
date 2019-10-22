// VlojenyeKvadraty.cpp - печатает квадратную матрицу размером 2n+1
// по краям матрицы == 0, увеличивается к центру до числа == n

#include <stdio.h>

int DistanceToBorders(int border, int x) {
    // х лежит в интервале [0...border] <- есть 2 границы - 0 и border
    // эта функция возвращает расстояние до ближайшей границы интервала
    if (border - x < x)
        return (border - x);
    else
        return x;
}

int main() {
    unsigned int n;
    scanf_s("%u", &n);
    
    int matrixBorder = n * 2;
    for (int i = 0; i <= matrixBorder; i++) {
        // на i строке не может быть чисел, больших maxNumberInLine
        // строка 0 -> 0, 1 -> 1  ..........предпоследняя -> 1, последняя -> 0
        // т.е. расстоянию строки от нулевой или последней строки (ближайшее)
        int maxNumberInLine = DistanceToBorders(matrixBorder, i);
        
        // напечатаем строку i
        for (int j = 0; j <= matrixBorder; j++) {
            // для столбцов аналогично, число в столбце == расстоянию до
            // ближайшей вертикальной границы (==0 на границах матрицы)
            // при этом, не больше разрешённого числа строки maxNumberInLine
            int x = DistanceToBorders(matrixBorder, j);
            if (x > maxNumberInLine)
                x = maxNumberInLine;
            printf("%d ", x);
        }
        printf("\n"); // конец строки матрицы
    }
    return 0;
}
