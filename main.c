//
//  main.c
//  Ordinary_Least_Squares
//
//  Created by barry on 23.03.2018.
//  Copyright © 2018 barry. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#define N 9
#define M N+1
void method_Gauss(double [N][M]);

int main(int argc, const char * argv[]) {
    FILE *file = fopen("input_data.txt", "r");
    double x[N], y[N];
    for (int i =0; i < N; i++) {
        fscanf(file, "%lf", &x[i]);    }
    for (int i =0; i < N; i++) {
        fscanf(file, "%lf", &y[i]);
    }
    fclose(file);
    double a[N][N+1];
    int p;
    for (int i = N-1; i >= 0; i--) {
        for (int j = 0; j < N; j++) {
            a[i][9] += y[j]*x[i];
            p = i+j;
            for (int k = 0; k < N; k++) {
                a[i][j] += pow(x[k], p);
            }
        }
    }
    a[0][0] = N;
    method_Gauss(a);
    
    return 0;
}
void method_Gauss(double a[N][M]){
    double temp;
    int buff, i, j;
    int k = 0; // текущая операция
    
    while (k < N - 1){ // ищем строку с максимальным коэф. при x1
        buff = k;
        for (i = k; i < N; i++) {
            if (a[buff][k] < a[i][k]){
                buff = i;
            }
        }
        for (j = k; j < M; j++) { // меняем местами строку с элементом max со строкой "k"
            temp = a[buff][j];
            a[buff][j] = a[k][j];
            a[k][j] = temp;
        }
        for (i = k; i < N; i++) { // нормируем уравн относительно k-того эл-та
            temp = a[i][k];
            for (j = k; j < M; j++) {
                if (!a[i][j]) continue;
                a[i][j] /= temp;
            }
        }
        for (i = k + 1; i < N; i++) { // вычитаем k-тую строку из ставшихся строк
            for (j = k; j < M; j++) {
                a[i][j] -= a[k][j];
            }
        }
        k++;
    }
    temp = a[N-1][M-2];
    a[N-1][M-2] /= temp; //последние нормирование
    a[N-1][M-1] /= temp;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
        }
    }
    double ot[N] = {0}, x[N] = {0};
    x[N-1] = a[N-1][M-1];
    for (i = N - 1; i >= 0; i--) { // обратная подстановка
        ot[i] = a[i][M-1];
        for (j = M - 2; j>=0; j--) {
            if (j == i) continue;
            ot[i] -= a[i][j] * x[j];
        }
        x[i] = ot[i];
    }
    FILE *file = fopen("answear_data.txt", "w");
    char c = 'a';
    for (i = 0 ; i < N; i++) { // Формат вывода должен быть:«a = ... b = ... c = ... d = ... e = ...»
        fprintf(file, " %c = %lf", c+i, x[i]);
    }
    fclose(file);
}
