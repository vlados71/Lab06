#include "pch.h"
#include "CppUnitTest.h"

// Підключаємо код програми. main() перейменовуємо, щоб не конфліктував з тестовим проєктом.
#define main Lab063it_main
#include "../Lab063it/Lab063it.cpp"
#undef main

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest063it
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

    TEST_CLASS(UnitTest063it)
    {
    public:

        // ---------- звичайна функція (int) ----------

        // Випадковий порядок, є дублікати
        TEST_METHOD(Sort_Int_Mixed)
        {
            int a[] = { 4, -2, 9, 4, 0, 7, -5, 9 };
            int e[] = { 9, 9, 7, 4, 4, 0, -2, -5 };
            Sort(a, 8);
            Assert::IsTrue(Same(a, e, 8));
        }

        // Масив уже впорядкований за незростанням: не змінюється
        TEST_METHOD(Sort_Int_AlreadySorted)
        {
            int a[] = { 5, 4, 3, 2, 1 };
            int e[] = { 5, 4, 3, 2, 1 };
            Sort(a, 5);
            Assert::IsTrue(Same(a, e, 5));
        }

        // Масив впорядкований за зростанням: стає зворотним
        TEST_METHOD(Sort_Int_Ascending)
        {
            int a[] = { 1, 2, 3, 4, 5 };
            int e[] = { 5, 4, 3, 2, 1 };
            Sort(a, 5);
            Assert::IsTrue(Same(a, e, 5));
        }

        // Усі елементи однакові
        TEST_METHOD(Sort_Int_AllEqual)
        {
            int a[] = { 3, 3, 3, 3 };
            int e[] = { 3, 3, 3, 3 };
            Sort(a, 4);
            Assert::IsTrue(Same(a, e, 4));
        }

        // Лише від'ємні числа
        TEST_METHOD(Sort_Int_Negatives)
        {
            int a[] = { -3, -10, -1, -7 };
            int e[] = { -1, -3, -7, -10 };
            Sort(a, 4);
            Assert::IsTrue(Same(a, e, 4));
        }

        // Два елементи
        TEST_METHOD(Sort_Int_TwoElements)
        {
            int a[] = { 1, 2 };
            int e[] = { 2, 1 };
            Sort(a, 2);
            Assert::IsTrue(Same(a, e, 2));
        }

        // Один елемент
        TEST_METHOD(Sort_Int_SingleElement)
        {
            int a[] = { 42 };
            int e[] = { 42 };
            Sort(a, 1);
            Assert::IsTrue(Same(a, e, 1));
        }

        // Порожній масив: нічого не відбувається і немає помилки
        TEST_METHOD(Sort_Int_Empty)
        {
            int a[] = { 7 };
            Sort(a, 0);
            Assert::AreEqual(7, a[0]);
        }

        // ---------- шаблон функції ----------

        TEST_METHOD(Sort_Template_Int)
        {
            int a[] = { 4, -2, 9, 4, 0, 7, -5, 9 };
            int e[] = { 9, 9, 7, 4, 4, 0, -2, -5 };
            Sort<int>(a, 8);
            Assert::IsTrue(Same(a, e, 8));
        }

        TEST_METHOD(Sort_Template_Double)
        {
            double a[] = { 1.5, -2.25, 9.0, 4.75, 0.0, 7.1, -5.5, 9.0 };
            double e[] = { 9.0, 9.0, 7.1, 4.75, 1.5, 0.0, -2.25, -5.5 };
            Sort<double>(a, 8);
            Assert::IsTrue(Same(a, e, 8));
        }

        TEST_METHOD(Sort_Template_String)
        {
            string a[] = { "pear", "apple", "kiwi", "plum", "fig", "lemon", "date", "mango" };
            string e[] = { "plum", "pear", "mango", "lemon", "kiwi", "fig", "date", "apple" };
            Sort<string>(a, 8);
            Assert::IsTrue(Same(a, e, 8));
        }

        TEST_METHOD(Sort_Template_SingleElement)
        {
            double a[] = { 2.5 };
            double e[] = { 2.5 };
            Sort<double>(a, 1);
            Assert::IsTrue(Same(a, e, 1));
        }

        // Звичайна функція і шаблон дають однаковий результат
        TEST_METHOD(Sort_Ordinary_And_Template_Agree)
        {
            int a[] = { 8, 1, 6, 3, 6, -4, 0 };
            int b[] = { 8, 1, 6, 3, 6, -4, 0 };
            Sort(a, 7);
            Sort<int>(b, 7);
            Assert::IsTrue(Same(a, b, 7));
        }
    };
}