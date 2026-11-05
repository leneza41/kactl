/**
 * Author: Unknown
 * Date: 2009-08-26
 * License: CC0
 * Source: https://cp-algorithms.com/algebra/divisors.html#multiplicative-functions
 * Description: Sum of divisors
 * Time: ...
 * Status: Tested
 */
#pragma once

long long SumOfDivisors(long long num) {
    long long total = 1;

    for (int i = 2; (long long)i * i <= num; i++) {
        if (num % i == 0) {
            int e = 0;
            do {
                e++;
                num /= i;
            } while (num % i == 0);

            long long sum = 0, pow = 1;
            do {
                sum += pow;
                pow *= i;
            } while (e-- > 0);
            total *= sum;
        }
    }
    if (num > 1) {
        total *= (1 + num);
    }
    return total;
}