#include "long_number.hpp"
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <string>
#include <chrono>

long_number calc_pi(int after_point) {

    long_number pi = 0.0_longnum;
    pi.set_after_point(after_point);

    long_number n0 = 1.0_longnum;
    n0.set_after_point(after_point);

    long_number n = 16.0_longnum;
    n.set_after_point(after_point);

    long_number a0 = 4.0_longnum;
    a0.set_after_point(after_point);

    long_number b0 = 2.0_longnum;
    b0.set_after_point(after_point);

    long_number c0 = 1.0_longnum;
    c0.set_after_point(after_point);

    long_number d0 = 1.0_longnum;
    d0.set_after_point(after_point);

    long_number a = 1.0_longnum;
    a.set_after_point(after_point);

    long_number b = 4.0_longnum;
    b.set_after_point(after_point);

    long_number c = 5.0_longnum;
    c.set_after_point(after_point);

    long_number d = 6.0_longnum;
    d.set_after_point(after_point);

    long_number ch = 8.0_longnum;
    ch.set_after_point(after_point);

    if (after_point == 0) {
        long_number result = 3.0_longnum;
        result.set_after_point(after_point);
        return result;
    }

    for (int k = 0; k < after_point; ++k) {

        long_number term1 = a0 / a;
        
        long_number term2 = b0 / b;
        
        long_number term3 = c0 / c;
        
        long_number term4 = d0 / d;

        long_number term = term1 - term2 - term3 - term4;

        term = n0 * term;
        term.set_after_point(after_point);

        pi = pi + term;

        if (k == 0) {
            n0 = n0 / n;
        } else {
            n0.insert_zeros_after_decimal_point();
        }
        
        a = a + ch;

        b = b + ch;

        c = c + ch;

        d = d + ch;

    }

    return pi;
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <precision>" << std::endl;
        return 1;
    }

    int after_point = 4 * std::stoi(argv[1]);

    auto start = std::chrono::high_resolution_clock::now();
    
    long_number pi = calc_pi(after_point);

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;

    std::cout << "PI = " << pi.to_str() << '\n';

    std::cout << "Time: " << duration.count() << " seconds" << std::endl;

    return 0;
}
