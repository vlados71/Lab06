// ІТЕраційний варіант 

#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

// 1. Формування масиву
void Create(int* a, const int size, const int Low, const int High)
{
    for (int i = 0; i < size; i++)
        a[i] = Low + rand() % (High - Low + 1);
}

// 2. Виведення масиву в рядок
void Print(int* a, const int size)
{
    for (int i = 0; i < size; i++)
        cout << setw(4) << a[i];
    cout << endl;
}

// 3. Обчислення кількості додатних парних елементів
int Count(int* a, const int size)
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (a[i] > 0 && a[i] % 2 == 0)
            count++;
    }
    return count;
}

// 4. Обчислення суми додатних парних елементів
int Sum(int* a, const int size)
{
    int S = 0;
    for (int i = 0; i < size; i++)
    {
        if (a[i] > 0 && a[i] % 2 == 0)
            S += a[i];
    }
    return S;
}

// 5. Заміна додатних парних елементів нулями
void Zero(int* a, const int size)
{
    for (int i = 0; i < size; i++)
    {
        if (a[i] > 0 && a[i] % 2 == 0)
            a[i] = 0;
    }
}

int main()
{
    srand((unsigned)time(NULL)); // ініціалізація генератора випадкових чисел

    const int n = 25;
    int a[n];
    int Low = -20;
    int High = 30;

    // Формуємо та виводимо початковий масив
    Create(a, n, Low, High);
    cout << "Original array:" << endl;
    Print(a, n);

    // Обчислюємо кількість та суму (до модифікації масиву!)
    int k = Count(a, n);
    int s = Sum(a, n);

    // Замінюємо елементи нулями
    Zero(a, n);

    // Виводимо модифікований масив та результати
    cout << "Modified array:" << endl;
    Print(a, n);

    cout << "Count = " << k << endl;
    cout << "Sum   = " << s << endl;

    return 0;
}