#include "test_runner.h"
#include "Bigint.h"

void TestWithBasicNumber() {
for (int count = 0; count < 100000; count++) {
    long long a = rand() % (int)(2 * 1e4) - (int)(1e4);
    long long b = rand() % (int)(2 * 1e4) - (int)(1e4);
    Bigint A(a);
    Bigint B(b);
    Bigint sum(a + b);
    Bigint dif(a - b);
    Bigint prod(a * b);
    ASSERT_EQUAL(A + B, sum);
    ASSERT_EQUAL(A - B, dif);
    ASSERT_EQUAL(A * B, prod);
    ASSERT_EQUAL(A > B, a > b);
    ASSERT_EQUAL(A < B, a < b);
    ASSERT_EQUAL(A >= B, a >= b);
    ASSERT_EQUAL(A <= B, a <= b);
    ASSERT_EQUAL(A == B, a == b);
    ASSERT_EQUAL(A != B, a != b);
}
}

void TestWithPowerOfTwo() {
    Bigint sum = 0;
    Bigint a = 1;
    for (int i = 0; i < 10; ++i) {
        sum = sum + a;
        a = a * 2;
    }
    ASSERT_EQUAL(sum, a-1); //sum(2^i) = 2^n - 1, where i=1..n-1
    ASSERT_EQUAL(a, Bigint(2)^10);
}

//Works only with number system 10^4 or lower. With higher number rounding erros give not accurate result.  
void TestFfp() {
    for(int i = 0; i < 10; ++i) {
        long long a = rand() % (int)(2 * 1e8) - (int)(1e8);
        long long b = rand() % (int)(2 * 1e8) - (int)(1e8);
        Bigint A = (Bigint(a)^10) * (Bigint(b)^15);
        Bigint B = (Bigint(a)^15) * (Bigint(b)^10);
        ASSERT_EQUAL(A * B, ffp(A, B));
    }

    
}