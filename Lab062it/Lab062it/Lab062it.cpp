// Лабораторна робота № 6.2
// Варіант 5. Ітераційний спосіб.
// Середнє арифметичне непарних елементів одновимірного масиву.

#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

// Формування масиву випадковими числами з діапазону [Low; High]
void Create(int* a, const int size, const int Low, const int High)
{
    for (int i = 0; i < size; i++)
        a[i] = Low + rand() % (High - Low + 1);
}

// Виведення масиву в рядок
void Print(int* a, const int size)
{
    for (int i = 0; i < size; i++)
        cout << setw(4) << a[i];
    cout << endl;
}

// Сума непарних елементів
int SumOdd(int* a, const int size)
{
    int s = 0;
    for (int i = 0; i < size; i++)
        if (a[i] % 2 != 0) // != 0, а не == 1, щоб коректно працювати з від'ємними
            s += a[i];
    return s;
}

// Кількість непарних елементів
int CountOdd(int* a, const int size)
{
    int k = 0;
    for (int i = 0; i < size; i++)
        if (a[i] % 2 != 0)
            k++;
    return k;
}

// Середнє арифметичне непарних елементів.
// Результат повертається через параметр avg.
// Функція повертає false, якщо непарних елементів немає.
bool AverageOdd(int* a, const int size, double& avg)
{
    int k = CountOdd(a, size);
    if (k == 0)
        return false;
    avg = (double)SumOdd(a, size) / k;
    return true;
}

int main()
{
    srand((unsigned)time(NULL)); // ініціалізація генератора випадкових чисел

    const int n = 10;
    int a[n];
    int Low = -10;
    int High = 10;

    Create(a, n, Low, High);
    Print(a, n);

    double avg;
    if (AverageOdd(a, n, avg))
        cout << "Average of odd elements = " << fixed << setprecision(2) << avg << endl;
    else
        cout << "There are no odd elements" << endl;

    return 0;
}