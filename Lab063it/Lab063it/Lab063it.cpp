// Лабораторна робота № 6.3
// Варіант 5. Ітераційний спосіб.
// Впорядкування елементів масиву за незростанням (метод вибору):
// 1) звичайна функція (для int); 2) шаблон функції (для довільного типу).

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Впорядкування за незростанням: звичайна функція для масиву цілих чисел
void Sort(int* a, const int size)
{
    for (int i = 0; i < size - 1; i++) // індекс початку невпорядкованої частини
    {
        int max = a[i];                // пошук максимального елемента
        int imax = i;                  // невпорядкованої частини
        for (int j = i + 1; j < size; j++)
            if (max < a[j])
            {
                max = a[j];
                imax = j;
            }
        a[imax] = a[i];                // обмін місцями максимального та першого
        a[i] = max;                    // елементів невпорядкованої частини
    }
}

// Впорядкування за незростанням: шаблон функції
template <typename T>
void Sort(T* a, const int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        T max = a[i];
        int imax = i;
        for (int j = i + 1; j < size; j++)
            if (max < a[j])
            {
                max = a[j];
                imax = j;
            }
        a[imax] = a[i];
        a[i] = max;
    }
}

// Виведення масиву в рядок (шаблон, працює для будь-якого типу, що виводиться через <<)
template <typename T>
void Print(T* a, const int size)
{
    for (int i = 0; i < size; i++)
        cout << setw(8) << a[i];
    cout << endl;
}

int main()
{
    const int n = 8;

    // 1) звичайна функція
    int a[n] = { 4, -2, 9, 4, 0, 7, -5, 9 };
    cout << "Ordinary function, int:" << endl;
    Print(a, n);
    Sort(a, n);
    Print(a, n);
    cout << endl;

    // 2) шаблон функції, int
    int b[n] = { 4, -2, 9, 4, 0, 7, -5, 9 };
    cout << "Template Sort<int>:" << endl;
    Print(b, n);
    Sort<int>(b, n);
    Print(b, n);
    cout << endl;

    // 2) шаблон функції, double
    double c[n] = { 1.5, -2.25, 9.0, 4.75, 0.0, 7.1, -5.5, 9.0 };
    cout << "Template Sort<double>:" << endl;
    Print(c, n);
    Sort<double>(c, n);
    Print(c, n);
    cout << endl;

    // 2) шаблон функції, string
    string d[n] = { "pear", "apple", "kiwi", "plum", "fig", "lemon", "date", "mango" };
    cout << "Template Sort<string>:" << endl;
    Print(d, n);
    Sort<string>(d, n);
    Print(d, n);

    return 0;
}