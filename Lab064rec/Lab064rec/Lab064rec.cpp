// Лабораторна робота № 6.4
// Варіант 5. Рекурсивний спосіб.
// Одновимірний динамічний масив з n дійсних елементів:
// 1.1. максимальний елемент;
// 1.2. сума елементів, розташованих до останнього додатного елемента;
// 2.   стиснення масиву: видалити елементи, модуль яких лежить в інтервалі [a, b],
//      вільні елементи в кінці заповнити нулями (відносний порядок зберігається).
// Параметри n, a, b вводяться з клавіатури.

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <time.h>
using namespace std;

// Формування масиву випадковими дійсними числами з діапазону [Low; High] (2 знаки після коми)
void Create(double* a, const int size, const double Low, const double High, int i)
{
    double x = Low + (High - Low) * rand() / RAND_MAX;
    a[i] = round(x * 100) / 100;
    if (i < size - 1)
        Create(a, size, Low, High, i + 1);
}

// Виведення масиву в рядок
void Print(double* a, const int size, int i)
{
    cout << setw(8) << fixed << setprecision(2) << a[i];
    if (i < size - 1)
        Print(a, size, i + 1);
    else
        cout << endl;
}

// 1.1. Максимальний елемент: викликається як Max(a, size, 1, a[0])
double Max(double* a, const int size, int i, double max)
{
    if (i < size)
    {
        if (a[i] > max)
            max = a[i];
        return Max(a, size, i + 1, max);
    }
    else
        return max;
}

// Індекс останнього додатного елемента (-1, якщо додатних елементів немає).
// Перегляд іде з кінця: викликається як LastPositiveIndex(a, size - 1)
int LastPositiveIndex(double* a, int i)
{
    if (i < 0)
        return -1;
    if (a[i] > 0)
        return i;
    return LastPositiveIndex(a, i - 1);
}

// Сума елементів з індексами від i до end-1: викликається як SumBefore(a, end, 0)
double SumBefore(double* a, const int end, int i)
{
    if (i < end)
        return a[i] + SumBefore(a, end, i + 1);
    else
        return 0;
}

// 1.2. Сума елементів до останнього додатного елемента.
// Результат повертається через параметр sum.
// Функція повертає false, якщо додатних елементів немає.
bool SumBeforeLastPositive(double* a, const int size, double& sum)
{
    int k = LastPositiveIndex(a, size - 1);
    if (k == -1)
        return false;
    sum = SumBefore(a, k, 0);
    return true;
}

// 2. Стиснення: залишає елементи, модуль яких НЕ лежить в [lo, hi], зсуваючи їх на початок.
// i - індекс елемента, що переглядається; k - позиція для запису. Викликається як Compress(a, size, lo, hi, 0, 0).
// Повертає кількість елементів, що залишилися.
int Compress(double* a, const int size, const double lo, const double hi, int i, int k)
{
    if (i < size)
    {
        if (fabs(a[i]) < lo || fabs(a[i]) > hi)
        {
            a[k] = a[i];
            return Compress(a, size, lo, hi, i + 1, k + 1);
        }
        else
            return Compress(a, size, lo, hi, i + 1, k);
    }
    else
        return k;
}

// Заповнення нулями елементів з індексами від i до size-1
void FillZeros(double* a, const int size, int i)
{
    if (i < size)
    {
        a[i] = 0;
        FillZeros(a, size, i + 1);
    }
}

int main()
{
    srand((unsigned)time(NULL)); // ініціалізація генератора випадкових чисел

    int n;
    do
    {
        cout << "n = "; cin >> n;
    } while (n <= 0);

    double lo, hi;
    cout << "a = "; cin >> lo;
    cout << "b = "; cin >> hi;
    if (lo > hi)
        swap(lo, hi);

    double* a = new double[n]; // динамічний масив
    Create(a, n, -10, 10, 0);
    Print(a, n, 0);

    cout << "max = " << fixed << setprecision(2) << Max(a, n, 1, a[0]) << endl;

    double sum;
    if (SumBeforeLastPositive(a, n, sum))
        cout << "sum before last positive = " << fixed << setprecision(2) << sum << endl;
    else
        cout << "There are no positive elements" << endl;

    int k = Compress(a, n, lo, hi, 0, 0);
    FillZeros(a, n, k);
    Print(a, n, 0);

    delete[] a; // знищили динамічний масив
    return 0;
}