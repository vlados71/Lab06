#include "pch.h"
#include "CppUnitTest.h"

// Підключаємо код програми. main() перейменовуємо, щоб не конфліктував з тестовим проєктом.
#define main Lab063rec_main
#include "../Lab063rec/Lab063rec.cpp"
#undef main

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest063rec
{
    // Чи збігаються перші n елементів двох масивів
    template <typename T>
    bool Same(const T* x, const T* y, const int n)
    {
        for (int i = 0; i < n; i++)
            if (!(x[i] == y[i]))
                return false;
        return true;
    }

    TEST_CLASS(UnitTest063rec)
    {
    public:

        // ---------- допоміжна функція FindMax ----------

        // Максимальний елемент та його індекс; при рівних значеннях залишається перший
        TEST_METHOD(FindMax_Int_FirstOfEqualMaxima)
        {
            int a[] = { 3, 7, 7, 1 };
            int max = a[0];
            int imax = 0;
            FindMax(a, 4, 1, max, imax);
            Assert::AreEqual(7, max);
            Assert::AreEqual(1, imax);
        }

        // Пошук починається з позиції j: елементи до неї не враховуються
        TEST_METHOD(FindMax_Int_StartsFromJ)
        {
            int a[] = { 100, 1, 5, 2 };
            int max = a[2];
            int imax = 2;
            FindMax(a, 4, 3, max, imax);
            Assert::AreEqual(5, max);
            Assert::AreEqual(2, imax);
        }

        TEST_METHOD(FindMax_Template_Double)
        {
            double a[] = { 1.5, -2.0, 9.25, 4.0 };
            double max = a[0];
            int imax = 0;
            FindMax<double>(a, 4, 1, max, imax);
            Assert::AreEqual(9.25, max, 1e-9);
            Assert::AreEqual(2, imax);
        }

        // ---------- звичайна функція (int) ----------

        // Випадковий порядок, є дублікати
        TEST_METHOD(Sort_Int_Mixed)
        {
            int a[] = { 4, -2, 9, 4, 0, 7, -5, 9 };
            int e[] = { 9, 9, 7, 4, 4, 0, -2, -5 };
            Sort(a, 8, 0);
            Assert::IsTrue(Same(a, e, 8));
        }

        // Масив уже впорядкований за незростанням: не змінюється
        TEST_METHOD(Sort_Int_AlreadySorted)
        {
            int a[] = { 5, 4, 3, 2, 1 };
            int e[] = { 5, 4, 3, 2, 1 };
            Sort(a, 5, 0);
            Assert::IsTrue(Same(a, e, 5));
        }

        // Масив впорядкований за зростанням: стає зворотним
        TEST_METHOD(Sort_Int_Ascending)
        {
            int a[] = { 1, 2, 3, 4, 5 };
            int e[] = { 5, 4, 3, 2, 1 };
            Sort(a, 5, 0);
            Assert::IsTrue(Same(a, e, 5));
        }

        // Усі елементи однакові
        TEST_METHOD(Sort_Int_AllEqual)
        {
            int a[] = { 3, 3, 3, 3 };
            int e[] = { 3, 3, 3, 3 };
            Sort(a, 4, 0);
            Assert::IsTrue(Same(a, e, 4));
        }

        // Лише від'ємні числа
        TEST_METHOD(Sort_Int_Negatives)
        {
            int a[] = { -3, -10, -1, -7 };
            int e[] = { -1, -3, -7, -10 };
            Sort(a, 4, 0);
            Assert::IsTrue(Same(a, e, 4));
        }

        // Два елементи
        TEST_METHOD(Sort_Int_TwoElements)
        {
            int a[] = { 1, 2 };
            int e[] = { 2, 1 };
            Sort(a, 2, 0);
            Assert::IsTrue(Same(a, e, 2));
        }

        // Один елемент: немає звернення за межі масиву
        TEST_METHOD(Sort_Int_SingleElement)
        {
            int a[] = { 42 };
            int e[] = { 42 };
            Sort(a, 1, 0);
            Assert::IsTrue(Same(a, e, 1));
        }

        // Порожній масив: нічого не відбувається і немає помилки
        TEST_METHOD(Sort_Int_Empty)
        {
            int a[] = { 7 };
            Sort(a, 0, 0);
            Assert::AreEqual(7, a[0]);
        }

        // ---------- шаблон функції ----------

        TEST_METHOD(Sort_Template_Int)
        {
            int a[] = { 4, -2, 9, 4, 0, 7, -5, 9 };
            int e[] = { 9, 9, 7, 4, 4, 0, -2, -5 };
            Sort<int>(a, 8, 0);
            Assert::IsTrue(Same(a, e, 8));
        }

        TEST_METHOD(Sort_Template_Double)
        {
            double a[] = { 1.5, -2.25, 9.0, 4.75, 0.0, 7.1, -5.5, 9.0 };
            double e[] = { 9.0, 9.0, 7.1, 4.75, 1.5, 0.0, -2.25, -5.5 };
            Sort<double>(a, 8, 0);
            Assert::IsTrue(Same(a, e, 8));
        }

        TEST_METHOD(Sort_Template_String)
        {
            string a[] = { "pear", "apple", "kiwi", "plum", "fig", "lemon", "date", "mango" };
            string e[] = { "plum", "pear", "mango", "lemon", "kiwi", "fig", "date", "apple" };
            Sort<string>(a, 8, 0);
            Assert::IsTrue(Same(a, e, 8));
        }

        TEST_METHOD(Sort_Template_SingleElement)
        {
            double a[] = { 2.5 };
            double e[] = { 2.5 };
            Sort<double>(a, 1, 0);
            Assert::IsTrue(Same(a, e, 1));
        }

        // Звичайна функція і шаблон дають однаковий результат
        TEST_METHOD(Sort_Ordinary_And_Template_Agree)
        {
            int a[] = { 8, 1, 6, 3, 6, -4, 0 };
            int b[] = { 8, 1, 6, 3, 6, -4, 0 };
            Sort(a, 7, 0);
            Sort<int>(b, 7, 0);
            Assert::IsTrue(Same(a, b, 7));
        }
    };
}