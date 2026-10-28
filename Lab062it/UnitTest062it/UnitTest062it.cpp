#include "pch.h"
#include "CppUnitTest.h"

// Підключаємо код програми. main() перейменовуємо, щоб не конфліктував з тестовим проєктом.
#define main Lab062it_main
#include "../Lab062it/Lab062it.cpp"
#undef main

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest062it
{
    TEST_CLASS(UnitTest062it)
    {
    public:

        // Суміш парних і непарних додатних: непарні 1, 3, 5 -> (1+3+5)/3 = 3
        TEST_METHOD(AverageOdd_PositiveMixed)
        {
            int a[] = { 1, 2, 3, 4, 5 };
            double avg = 0;
            bool found = AverageOdd(a, 5, avg);
            Assert::IsTrue(found);
            Assert::AreEqual(3.0, avg, 1e-9);
        }

        // Від'ємні непарні мають враховуватися (-3 % 2 == -1, а не 1)
        TEST_METHOD(AverageOdd_NegativeOdd)
        {
            int a[] = { 6, -8, 8, -3, -9, 0, 4, -7, 0, -5 };
            double avg = 0;
            bool found = AverageOdd(a, 10, avg);
            Assert::IsTrue(found);
            Assert::AreEqual(-6.0, avg, 1e-9);
        }

        // Додатні і від'ємні непарні разом: (-3 + 5) / 2 = 1
        TEST_METHOD(AverageOdd_MixedSigns)
        {
            int a[] = { -3, 2, 5, 8 };
            double avg = 0;
            bool found = AverageOdd(a, 4, avg);
            Assert::IsTrue(found);
            Assert::AreEqual(1.0, avg, 1e-9);
        }

        // Результат дробовий: непарні 1, 3, 7 -> 11 / 3 = 3.666...
        TEST_METHOD(AverageOdd_FractionalResult)
        {
            int a[] = { 1, 3, 4, 7 };
            double avg = 0;
            bool found = AverageOdd(a, 4, avg);
            Assert::IsTrue(found);
            Assert::AreEqual(11.0 / 3.0, avg, 1e-9);
        }

        // Усі елементи непарні
        TEST_METHOD(AverageOdd_AllOdd)
        {
            int a[] = { 1, 3, 5, 7 };
            double avg = 0;
            bool found = AverageOdd(a, 4, avg);
            Assert::IsTrue(found);
            Assert::AreEqual(4.0, avg, 1e-9);
        }

        // Єдиний елемент, і він непарний
        TEST_METHOD(AverageOdd_SingleOddElement)
        {
            int a[] = { 7 };
            double avg = 0;
            bool found = AverageOdd(a, 1, avg);
            Assert::IsTrue(found);
            Assert::AreEqual(7.0, avg, 1e-9);
        }

        // Непарних елементів немає (нуль - парне число): функція повертає false
        TEST_METHOD(AverageOdd_NoOdd)
        {
            int a[] = { 2, 4, 0, -6, 8 };
            double avg = 123.0;
            bool found = AverageOdd(a, 5, avg);
            Assert::IsFalse(found);
            Assert::AreEqual(123.0, avg, 1e-9); // avg не змінюється
        }

        TEST_METHOD(SumOdd_Basic)
        {
            int a[] = { 1, 2, 3, -5, 8 };
            Assert::AreEqual(-1, SumOdd(a, 5));
        }

        TEST_METHOD(SumOdd_NoOdd)
        {
            int a[] = { 2, 4, 6 };
            Assert::AreEqual(0, SumOdd(a, 3));
        }

        TEST_METHOD(CountOdd_Basic)
        {
            int a[] = { 1, 2, 3, -5, 8, 0 };
            Assert::AreEqual(3, CountOdd(a, 6));
        }

        TEST_METHOD(CountOdd_NoOdd)
        {
            int a[] = { 2, 4, 6 };
            Assert::AreEqual(0, CountOdd(a, 3));
        }

        // Усі згенеровані значення мають лежати в діапазоні [Low; High]
        TEST_METHOD(Create_ValuesInRange)
        {
            const int n = 1000;
            int a[n];
            const int Low = -10, High = 10;
            srand(12345);
            Create(a, n, Low, High);
            bool ok = true;
            for (int i = 0; i < n; i++)
                if (a[i] < Low || a[i] > High)
                    ok = false;
            Assert::IsTrue(ok);
        }
    };
}