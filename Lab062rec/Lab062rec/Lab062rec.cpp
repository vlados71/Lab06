// Лабораторна робота № 6.2
// Варіант 5. Рекурсивний спосіб.
// Середнє арифметичне непарних елементів одновимірного масиву.

#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

// Формування масиву випадковими числами з діапазону [Low; High]
void Create(int* a, const int size, const int Low, const int High, int i)
{
    a[i] = Low + rand() % (High - Low + 1);
    if (i < size - 1)
        Create(a, size, Low, High, i + 1);
}

// Виведення масиву в рядок
void Print(int* a, const int size, int i)
{
    cout << setw(4) << a[i];
    if (i < size - 1)
        Print(a, size, i + 1);
    else
        cout << endl;
}

// Сума непарних елементів
int SumOdd(int* a, const int size, int i)
{
    if (i < size)
    {
        if (a[i] % 2 != 0) // != 0, а не == 1, щоб коректно працювати з від'ємними
            return a[i] + SumOdd(a, size, i + 1);
        else
            return SumOdd(a, size, i + 1);
    }
    else
        return 0;
}

// Кількість непарних елементів
int CountOdd(int* a, const int size, int i)
{
    if (i < size)
    {
        if (a[i] % 2 != 0)
            return 1 + CountOdd(a, size, i + 1);
        else
            return CountOdd(a, size, i + 1);
    }
    else
        return 0;
}

// Середнє арифметичне непарних елементів.
// Результат повертається через параметр avg.
// Функція повертає false, якщо непарних елементів немає.
bool AverageOdd(int* a, const int size, double& avg)
{
    int k = CountOdd(a, size, 0);
    if (k == 0)
        return false;
    avg = (double)SumOdd(a, size, 0) / k;
    return true;
}

int main()
{
    srand((unsigned)time(NULL)); // ініціалізація генератора випадкових чисел

    const int n = 10;
    int a[n];
    int Low = -10;
    int High = 10;

    Create(a, n, Low, High, 0);
    Print(a, n, 0);

    double avg;
    if (AverageOdd(a, n, avg))
        cout << "Average of odd elements = " << fixed << setprecision(2) << avg << endl;
    else
        cout << "There are no odd elements" << endl;

    return 0;
}