// Лабораторна робота № 6.4
// Варіант 5. Ітераційний спосіб.
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
void Create(double* a, const int size, const double Low, const double High)
{
    for (int i = 0; i < size; i++)
    {
        double x = Low + (High - Low) * rand() / RAND_MAX;
        a[i] = round(x * 100) / 100;
    }
}

// Виведення масиву в рядок
void Print(double* a, const int size)
{
    for (int i = 0; i < size; i++)
        cout << setw(8) << fixed << setprecision(2) << a[i];
    cout << endl;
}

// 1.1. Максимальний елемент (початкове значення береться з масиву)
double Max(double* a, const int size)
{
    double max = a[0];
    for (int i = 1; i < size; i++)
        if (a[i] > max)
            max = a[i];
    return max;
}

// Індекс останнього додатного елемента (-1, якщо додатних елементів немає)
int LastPositiveIndex(double* a, const int size)
{
    for (int i = size - 1; i >= 0; i--)
        if (a[i] > 0)
            return i;
    return -1;
}

// Сума елементів з індексами від 0 до end-1 (тобто розташованих до елемента з індексом end)
double SumBefore(double* a, const int end)
{
    double s = 0;
    for (int i = 0; i < end; i++)
        s += a[i];
    return s;
}

// 1.2. Сума елементів до останнього додатного елемента.
// Результат повертається через параметр sum.
// Функція повертає false, якщо додатних елементів немає.
bool SumBeforeLastPositive(double* a, const int size, double& sum)
{
    int k = LastPositiveIndex(a, size);
    if (k == -1)
        return false;
    sum = SumBefore(a, k);
    return true;
}

// 2. Стиснення: залишає елементи, модуль яких НЕ лежить в [lo, hi], зсуваючи їх на початок.
// Повертає кількість елементів, що залишилися.
int Compress(double* a, const int size, const double lo, const double hi)
{
    int k = 0; // позиція для запису наступного елемента, що залишається
    for (int i = 0; i < size; i++)
        if (fabs(a[i]) < lo || fabs(a[i]) > hi)
            a[k++] = a[i];
    return k;
}

// Заповнення нулями елементів з індексами від from до size-1
void FillZeros(double* a, const int size, const int from)
{
    for (int i = from; i < size; i++)
        a[i] = 0;
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
    Create(a, n, -10, 10);
    Print(a, n);

    cout << "max = " << fixed << setprecision(2) << Max(a, n) << endl;

    double sum;
    if (SumBeforeLastPositive(a, n, sum))
        cout << "sum before last positive = " << fixed << setprecision(2) << sum << endl;
    else
        cout << "There are no positive elements" << endl;

    int k = Compress(a, n, lo, hi);
    FillZeros(a, n, k);
    Print(a, n);

    delete[] a; // знищили динамічний масив
    return 0;
}