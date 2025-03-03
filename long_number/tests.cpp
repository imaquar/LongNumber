#include "long_number.hpp"
#include <cmath>
#include <iostream>

void tests() {
    int prec1 = 10;
    int prec2 = 5;
    int prec = maxi(prec1, prec2);

    long_number a1 = 7.0_longnum;
    long_number a2 = 8.0_longnum;
    a1.set_after_point(prec);
    a2.set_after_point(prec);

    long_number sum = a1 + a2;
    if (sum.to_str() == "1111.0000000000") {
        std::cout << "Test 1: " << "OK\n";
    } else {
        std::cout << "Test 1: " << "FAIL\n";
    }

    long_number a3 = -1.0_longnum;
    long_number a4 = -2.0_longnum;
    a3.set_after_point(prec);
    a4.set_after_point(prec);

    long_number sum2 = a3 + a4;
    if (sum2.to_str() == "-11.0000000000") {
        std::cout << "Test 2: " << "OK\n";
    } else {
        std::cout << "Test 2: " << "FAIL\n";
    }

    long_number b1 = 8.0_longnum;
    long_number b2 = 4.0_longnum;
    b1.set_after_point(prec);
    b2.set_after_point(prec);

    long_number diff = b1 - b2;
    if (diff.to_str() == "100.0000000000") {
        std::cout << "Test 3: " << "OK\n";
    } else {
        std::cout << "Test 3: " << "FAIL\n";
    }

    long_number b3 = 10.0_longnum;
    long_number b4 = 20.0_longnum;
    b3.set_after_point(prec);
    b4.set_after_point(prec);

    long_number diff2 = b3 - b4;
    if (diff2.to_str() == "-1010.0000000000") {
        std::cout << "Test 4: " << "OK\n";
    } else {
        std::cout << "Test 4: " << "FAIL\n";
    }

    long_number c1 = 10.0_longnum;
    long_number c2 = 5.0_longnum;
    c1.set_after_point(prec);
    c2.set_after_point(prec);

    long_number prod = c1 * c2;
    if (prod.to_str() == "110010.0000000000") {
        std::cout << "Test 5: " << "OK\n";
    } else {
        std::cout << "Test 5: " << "FAIL\n";
    }

    long_number c3 = -2.0_longnum;
    long_number c4 = 5.0_longnum;
    c3.set_after_point(prec);
    c4.set_after_point(prec);

    long_number prod2 = c3 * c4;
    if (prod2.to_str() == "-1010.0000000000") {
        std::cout << "Test 6: " << "OK\n";
    } else {
        std::cout << "Test 6: " << "FAIL\n";
    }

    long_number d1 = 2.0_longnum;
    long_number d2 = 4.0_longnum;
    d1.set_after_point(prec);
    d2.set_after_point(prec);

    long_number div = d1 / d2;
    if (div.to_str() == "0.1000000000") {
        std::cout << "Test 7: " << "OK\n";
    } else {
        std::cout << "Test 7: " << "FAIL\n";
    }

    long_number d3 = 10.0_longnum;
    long_number d4 = 5.0_longnum;
    d3.set_after_point(prec);
    d4.set_after_point(prec);

    long_number div2 = d3 / d4;
    if (div2.to_str() == "10.0000000000") {
        std::cout << "Test 8: " << "OK\n";
    } else {
        std::cout << "Test 8: " << "FAIL\n";
    }

    long_number e1 = 10.0_longnum;
    long_number e2 = -10.0_longnum;
    e1.set_after_point(prec);
    e2.set_after_point(prec);

    if (e1 > e2) {
        std::cout << "Test 9: " << "OK\n";
    } else {
        std::cout << "Test 9: " << "FAIL\n";
    }

    long_number e3 = 100.0_longnum;
    long_number e4 = 10.0_longnum;
    e3.set_after_point(prec);
    e4.set_after_point(prec);

    if (e3 > e4) {
        std::cout << "Test 10: " << "OK\n";
    } else {
        std::cout << "Test 10: " << "FAIL\n";
    }

    long_number f1 = 20.0_longnum;
    long_number f2 = 20.5_longnum;
    f1.set_after_point(prec);
    f2.set_after_point(prec);

    if (f1 < f2) {
        std::cout << "Test 11: " << "OK\n";
    } else {
        std::cout << "Test 11: " << "FAIL\n";
    }

    long_number f3 = 100.0_longnum;
    long_number f4 = 101.0_longnum;
    f3.set_after_point(prec);
    f4.set_after_point(prec);

    if (f3 < f4) {
        std::cout << "Test 12: " << "OK\n";
    } else {
        std::cout << "Test 12: " << "FAIL\n";
    }

    long_number g1 = 100.0_longnum;
    long_number g2 = 100.0_longnum;
    g1.set_after_point(prec);
    g2.set_after_point(prec);

    if (g1 == g2) {
        std::cout << "Test 13: " << "OK\n";
    } else {
        std::cout << "Test 13: " << "FAIL\n";
    }

    long_number g3 = -50.0_longnum;
    long_number g4 = -50.0_longnum;
    g3.set_after_point(prec);
    g4.set_after_point(prec);

    if (g3 == g4) {
        std::cout << "Test 14: " << "OK\n";
    } else {
        std::cout << "Test 14: " << "FAIL\n";
    }

    long_number h1 = 100.0_longnum;
    long_number h2 = 200.0_longnum;
    h1.set_after_point(prec);
    h2.set_after_point(prec);

    if (h1 != h2) {
        std::cout << "Test 15: " << "OK\n";
    } else {
        std::cout << "Test 15: " << "FAIL\n";
    }

    long_number h3 = -50.0_longnum;
    long_number h4 = -100.0_longnum;
    h3.set_after_point(prec);
    h4.set_after_point(prec);

    if (h3 != h4) {
        std::cout << "Test 16: " << "OK\n";
    } else {
        std::cout << "Test 16: " << "FAIL\n";
    }
}

int main() {
    
    tests();

    return 0;
}