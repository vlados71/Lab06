#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab061rec/Lab061rec.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestRecursive
{
    TEST_CLASS(UnitTestRecursive)
    {
    public:
        TEST_METHOD(TestSumRec)
        {
            const int n = 7;
            int a[n] = { -4, 2, 0, 7, 6, -10, 8 };

            int expectedSum = 16;
            // Виклик рекурсивної функції з передачею початкового індексу 0
            int actualSum = Sum(a, n, 0);

            Assert::AreEqual(expectedSum, actualSum);
        }

        TEST_METHOD(TestCountRec)
        {
            const int n = 7;
            int a[n] = { -4, 2, 0, 7, 6, -10, 8 };

            int expectedCount = 3;
            // Виклик рекурсивної функції з передачею початкового індексу 0
            int actualCount = Count(a, n, 0);

            Assert::AreEqual(expectedCount, actualCount);
        }
    };
}