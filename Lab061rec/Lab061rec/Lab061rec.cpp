#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

// 1. Рекурсивне формування масиву
void Create(int* a, const int size, const int Low, const int High, int i)
{
    a[i] = Low + rand() % (High - Low + 1);
    if (i < size - 1)
        Create(a, size, Low, High, i + 1);
}

// 2. Рекурсивне виведення масиву в рядок
void Print(int* a, const int size, int i)
{
    cout << setw(4) << a[i];
    if (i < size - 1)
        Print(a, size, i + 1);
    else
        cout << endl;
}

// 3. Рекурсивне обчислення кількості додатних парних елементів
int Count(int* a, const int size, int i)
{
    if (i < size)
    {
        if (a[i] > 0 && a[i] % 2 == 0)
            return 1 + Count(a, size, i + 1);
        else
            return Count(a, size, i + 1);
    }
    else
        return 0;
}

// 4. Рекурсивне обчислення суми додатних парних елементів
int Sum(int* a, const int size, int i)
{
    if (i < size)
    {
        if (a[i] > 0 && a[i] % 2 == 0)
            return a[i] + Sum(a, size, i + 1);
        else
            return Sum(a, size, i + 1);
    }
    else
        return 0;
}

// 5. Рекурсивна заміна додатних парних елементів нулями
void Zero(int* a, const int size, int i)
{
    if (a[i] > 0 && a[i] % 2 == 0)
        a[i] = 0;
    if (i < size - 1)
        Zero(a, size, i + 1);
}

int main()
{
    srand((unsigned)time(NULL));

    const int n = 25;
    int a[n];
    int Low = -20;
    int High = 30;

    // Перший виклик усіх рекурсивних функцій починається з індексу i = 0
    Create(a, n, Low, High, 0);
    cout << "Original array:" << endl;
    Print(a, n, 0);

    int k = Count(a, n, 0);
    int s = Sum(a, n, 0);

    Zero(a, n, 0);

    cout << "Modified array:" << endl;
    Print(a, n, 0);

    cout << "Count = " << k << endl;
    cout << "Sum   = " << s << endl;

    return 0;
}