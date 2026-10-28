// Лабораторна робота № 6.3
// Варіант 5. Рекурсивний спосіб.
// Впорядкування елементів масиву за незростанням (метод вибору):
// 1) звичайні функції (для int); 2) шаблони функцій (для довільного типу).

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Пошук максимального елемента, починаючи з позиції j:
// max, imax - вхідні/вихідні параметри (початкові значення задає виклик)
void FindMax(int* a, const int size, int j, int& max, int& imax)
{
    if (j < size)
    {
        if (a[j] > max)
        {
            max = a[j];
            imax = j;
        }
        FindMax(a, size, j + 1, max, imax);
    }
}

// Впорядкування за незростанням: звичайна функція, i - початок невпорядкованої частини
void Sort(int* a, const int size, int i)
{
    if (i < size - 1)
    {
        int max = a[i];
        int imax = i;
        FindMax(a, size, i + 1, max, imax);
        a[imax] = a[i];                // обмін місцями максимального та першого
        a[i] = max;                    // елементів невпорядкованої частини
        Sort(a, size, i + 1);
    }
}

// Шаблон: пошук максимального елемента
template <typename T>
void FindMax(T* a, const int size, int j, T& max, int& imax)
{
    if (j < size)
    {
        if (a[j] > max)
        {
            max = a[j];
            imax = j;
        }
        FindMax(a, size, j + 1, max, imax);
    }
}

// Шаблон: впорядкування за незростанням
template <typename T>
void Sort(T* a, const int size, int i)
{
    if (i < size - 1)
    {
        T max = a[i];
        int imax = i;
        FindMax(a, size, i + 1, max, imax);
        a[imax] = a[i];
        a[i] = max;
        Sort(a, size, i + 1);
    }
}

// Виведення масиву в рядок (шаблон)
template <typename T>
void Print(T* a, const int size, int i)
{
    if (i < size)
    {
        cout << setw(8) << a[i];
        Print(a, size, i + 1);
    }
    else
        cout << endl;
}

int main()
{
    const int n = 8;

    // 1) звичайні функції
    int a[n] = { 4, -2, 9, 4, 0, 7, -5, 9 };
    cout << "Ordinary function, int:" << endl;
    Print(a, n, 0);
    Sort(a, n, 0);
    Print(a, n, 0);
    cout << endl;

    // 2) шаблон функції, int
    int b[n] = { 4, -2, 9, 4, 0, 7, -5, 9 };
    cout << "Template Sort<int>:" << endl;
    Print(b, n, 0);
    Sort<int>(b, n, 0);
    Print(b, n, 0);
    cout << endl;

    // 2) шаблон функції, double
    double c[n] = { 1.5, -2.25, 9.0, 4.75, 0.0, 7.1, -5.5, 9.0 };
    cout << "Template Sort<double>:" << endl;
    Print(c, n, 0);
    Sort<double>(c, n, 0);
    Print(c, n, 0);
    cout << endl;

    // 2) шаблон функції, string
    string d[n] = { "pear", "apple", "kiwi", "plum", "fig", "lemon", "date", "mango" };
    cout << "Template Sort<string>:" << endl;
    Print(d, n, 0);
    Sort<string>(d, n, 0);
    Print(d, n, 0);

    return 0;
}