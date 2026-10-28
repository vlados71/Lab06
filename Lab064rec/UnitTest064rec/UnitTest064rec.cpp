#include "pch.h"
#include "CppUnitTest.h"

// Підключаємо код програми. main() перейменовуємо, щоб не конфліктував з тестовим проєктом.
#define main Lab064rec_main
#include "../Lab064rec/Lab064rec.cpp"
#undef main

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest064rec
{
    // Чи збігаються перші n елементів двох масивів дійсних чисел (з допуском)
    bool Same(const double* x, const double* y, const int n)
    {
        for (int i = 0; i < n; i++)
            if (fabs(x[i] - y[i]) > 1e-9)
                return false;
        return true;
    }

    TEST_CLASS(UnitTest064rec)
    {
    public:

        // ---------- 1.1 Max (виклик: Max(a, size, 1, a[0])) ----------

        TEST_METHOD(Max_Mixed)
        {
            double a[] = { 1.5, -2.0, 9.25, 4.0 };
            Assert::AreEqual(9.25, Max(a, 4, 1, a[0]), 1e-9);
        }

        // Усі від'ємні: результат не повинен бути нулем
        TEST_METHOD(Max_AllNegative)
        {
            double a[] = { -3.0, -1.5, -7.0 };
            Assert::AreEqual(-1.5, Max(a, 3, 1, a[0]), 1e-9);
        }

        TEST_METHOD(Max_AtFirstPosition)
        {
            double a[] = { 8.0, 1.0, 2.0 };
            Assert::AreEqual(8.0, Max(a, 3, 1, a[0]), 1e-9);
        }

        TEST_METHOD(Max_AtLastPosition)
        {
            double a[] = { 1.0, 2.0, 8.0 };
            Assert::AreEqual(8.0, Max(a, 3, 1, a[0]), 1e-9);
        }

        TEST_METHOD(Max_SingleElement)
        {
            double a[] = { -4.5 };
            Assert::AreEqual(-4.5, Max(a, 1, 1, a[0]), 1e-9);
        }

        // ---------- LastPositiveIndex (виклик: LastPositiveIndex(a, size - 1)) ----------

        TEST_METHOD(LastPositiveIndex_Middle)
        {
            double a[] = { -1.0, 2.0, -3.0, 4.0, -5.0 };
            Assert::AreEqual(3, LastPositiveIndex(a, 4));
        }

        TEST_METHOD(LastPositiveIndex_AtEnd)
        {
            double a[] = { -1.0, 2.0, 3.0 };
            Assert::AreEqual(2, LastPositiveIndex(a, 2));
        }

        TEST_METHOD(LastPositiveIndex_AtStart)
        {
            double a[] = { 1.0, -2.0, -3.0 };
            Assert::AreEqual(0, LastPositiveIndex(a, 2));
        }

        TEST_METHOD(LastPositiveIndex_NoPositive)
        {
            double a[] = { -1.0, -2.0, -3.0 };
            Assert::AreEqual(-1, LastPositiveIndex(a, 2));
        }

        // Нуль не є додатним числом
        TEST_METHOD(LastPositiveIndex_ZeroIsNotPositive)
        {
            double a[] = { 0.0, -1.0, 0.0 };
            Assert::AreEqual(-1, LastPositiveIndex(a, 2));
        }

        // ---------- SumBefore (виклик: SumBefore(a, end, 0)) ----------

        TEST_METHOD(SumBefore_Basic)
        {
            double a[] = { 1.0, 2.0, 3.0, 4.0 };
            Assert::AreEqual(6.0, SumBefore(a, 3, 0), 1e-9);
        }

        TEST_METHOD(SumBefore_EmptyRange)
        {
            double a[] = { 1.0, 2.0, 3.0 };
            Assert::AreEqual(0.0, SumBefore(a, 0, 0), 1e-9);
        }

        // ---------- 1.2 SumBeforeLastPositive ----------

        // Останній додатний має індекс 4: 1.5 - 2.5 + 3 - 4 = -2
        TEST_METHOD(SumBeforeLastPositive_Basic)
        {
            double a[] = { 1.5, -2.5, 3.0, -4.0, 2.0, -1.0 };
            double sum = 0;
            bool found = SumBeforeLastPositive(a, 6, sum);
            Assert::IsTrue(found);
            Assert::AreEqual(-2.0, sum, 1e-9);
        }

        // Останній додатний - перший елемент: сума порожня, тобто 0
        TEST_METHOD(SumBeforeLastPositive_PositiveIsFirst)
        {
            double a[] = { 5.0, -1.0, 0.0 };
            double sum = 99.0;
            bool found = SumBeforeLastPositive(a, 3, sum);
            Assert::IsTrue(found);
            Assert::AreEqual(0.0, sum, 1e-9);
        }

        // Останній додатний - наприкінці масиву: сума всіх елементів, крім останнього
        TEST_METHOD(SumBeforeLastPositive_PositiveIsLast)
        {
            double a[] = { 1.0, 2.0, 3.0, 4.0 };
            double sum = 0;
            bool found = SumBeforeLastPositive(a, 4, sum);
            Assert::IsTrue(found);
            Assert::AreEqual(6.0, sum, 1e-9);
        }

        // Додатних елементів немає: false, sum не змінюється
        TEST_METHOD(SumBeforeLastPositive_NoPositive)
        {
            double a[] = { -1.0, 0.0, -3.0 };
            double sum = 123.0;
            bool found = SumBeforeLastPositive(a, 3, sum);
            Assert::IsFalse(found);
            Assert::AreEqual(123.0, sum, 1e-9);
        }

        // ---------- 2 Compress (виклик: Compress(a, size, lo, hi, 0, 0)) ----------

        // Порядок елементів, що залишилися, зберігається
        TEST_METHOD(Compress_PreservesOrder)
        {
            double a[] = { 1.21, -7.21, -9.87, -4.53, 1.19, 6.90, -6.46, 0.41, -1.41, -6.66, -3.26, -0.79 };
            double e[] = { 1.21, -7.21, -9.87, 1.19, 6.90, -6.46, 0.41, -1.41, -6.66, -0.79 };
            int k = Compress(a, 12, 2.0, 5.0, 0, 0);
            Assert::AreEqual(10, k);
            Assert::IsTrue(Same(a, e, 10));
        }

        // Межі інтервалу включаються: |x| == a та |x| == b теж видаляються
        TEST_METHOD(Compress_BoundsInclusive)
        {
            double a[] = { 2.0, 5.0, 1.0, -5.0, 6.0, -2.0, 3.0 };
            double e[] = { 1.0, 6.0 };
            int k = Compress(a, 7, 2.0, 5.0, 0, 0);
            Assert::AreEqual(2, k);
            Assert::IsTrue(Same(a, e, 2));
        }

        // Видаляється за модулем, тобто і від'ємні значення
        TEST_METHOD(Compress_UsesModulus)
        {
            double a[] = { -3.0, 3.0, 10.0 };
            double e[] = { 10.0 };
            int k = Compress(a, 3, 2.0, 4.0, 0, 0);
            Assert::AreEqual(1, k);
            Assert::IsTrue(Same(a, e, 1));
        }

        // Нічого не видаляється
        TEST_METHOD(Compress_NothingRemoved)
        {
            double a[] = { 1.0, 6.0, -7.0 };
            double e[] = { 1.0, 6.0, -7.0 };
            int k = Compress(a, 3, 2.0, 5.0, 0, 0);
            Assert::AreEqual(3, k);
            Assert::IsTrue(Same(a, e, 3));
        }

        // Видаляється все
        TEST_METHOD(Compress_AllRemoved)
        {
            double a[] = { 2.0, -3.0, 4.0 };
            int k = Compress(a, 3, 2.0, 5.0, 0, 0);
            Assert::AreEqual(0, k);
        }

        // Інтервал [0, 0] видаляє нулі
        TEST_METHOD(Compress_RemovesZeros)
        {
            double a[] = { 0.0, 1.0, 2.0 };
            double e[] = { 1.0, 2.0 };
            int k = Compress(a, 3, 0.0, 0.0, 0, 0);
            Assert::AreEqual(2, k);
            Assert::IsTrue(Same(a, e, 2));
        }

        // ---------- FillZeros (виклик: FillZeros(a, size, from)) ----------

        TEST_METHOD(FillZeros_Tail)
        {
            double a[] = { 1.0, 2.0, 3.0, 4.0 };
            double e[] = { 1.0, 2.0, 0.0, 0.0 };
            FillZeros(a, 4, 2);
            Assert::IsTrue(Same(a, e, 4));
        }

        TEST_METHOD(FillZeros_FromStart)
        {
            double a[] = { 1.0, 2.0, 3.0 };
            double e[] = { 0.0, 0.0, 0.0 };
            FillZeros(a, 3, 0);
            Assert::IsTrue(Same(a, e, 3));
        }

        // from == size: нічого не змінюється
        TEST_METHOD(FillZeros_NothingToFill)
        {
            double a[] = { 1.0, 2.0, 3.0 };
            double e[] = { 1.0, 2.0, 3.0 };
            FillZeros(a, 3, 3);
            Assert::IsTrue(Same(a, e, 3));
        }

        // Compress + FillZeros разом: після видалення вільні місця в кінці заповнені нулями
        TEST_METHOD(Compress_ThenFillZeros)
        {
            double a[] = { 1.0, -3.0, 6.0, 4.0, -7.0 };
            double e[] = { 1.0, 6.0, -7.0, 0.0, 0.0 };
            int k = Compress(a, 5, 3.0, 4.0, 0, 0);
            FillZeros(a, 5, k);
            Assert::AreEqual(3, k);
            Assert::IsTrue(Same(a, e, 5));
        }

        // ---------- Create (динамічний масив) ----------

        // Усі значення в діапазоні [Low; High] і мають не більше двох знаків після коми
        TEST_METHOD(Create_ValuesInRangeTwoDecimals)
        {
            const int n = 200; // глибина рекурсії = n
            double* a = new double[n];
            srand(12345);
            Create(a, n, -10, 10, 0);
            bool ok = true;
            for (int i = 0; i < n; i++)
            {
                if (a[i] < -10 || a[i] > 10)
                    ok = false;
                if (fabs(a[i] * 100 - round(a[i] * 100)) > 1e-6)
                    ok = false;
            }
            delete[] a;
            Assert::IsTrue(ok);
        }
    };
}