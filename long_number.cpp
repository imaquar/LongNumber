#include "long_number.hpp"
#include <cmath>

size_t maxi(size_t a, size_t b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

void long_number::from_str_to_vec(const std::string & string) {
    bin_numbers.clear();
    for (char i : string) {
        if (i == '0' || i == '1') {
            bin_numbers.insert(bin_numbers.begin(), i - '0');
        }
    }
}

long_number::long_number() {}

long_number::long_number(const std::string & string) {
    from_str_to_vec(string);
}

long_number::long_number(const long_number & other) {
    bin_numbers = other.bin_numbers;
}

long_number::~long_number() {}

long_number & long_number::operator = (const long_number & other) {
    bin_numbers = other.bin_numbers;
    return *this;
}

long_number long_number::operator + (const long_number & other) const {
    long_number res;
    int check = 0;
    size_t max_size = maxi(bin_numbers.size(), other.bin_numbers.size());
    res.bin_numbers.resize(max_size, 0);
    for (size_t i = 0; i != max_size; ++i) {
        int sum = check;
        if (i < bin_numbers.size()) {
            sum += bin_numbers[i];
        }
        if (i < other.bin_numbers.size()) {
            sum += other.bin_numbers[i];
        }
        res.bin_numbers[i] = sum % 2;
        check = sum / 2;
    }
    if (check) {
        res.bin_numbers.push_back(check);
    }
    return res;
}

long_number long_number::operator - (const long_number & other) const {
    long_number res;
    int check = 0;
    size_t max_size = maxi(bin_numbers.size(), other.bin_numbers.size());
    res.bin_numbers.resize(max_size, 0);
    for (size_t i = 0; i != max_size; ++i) {
        int num = 0;
        if (i < other.bin_numbers.size()) {
            num = other.bin_numbers[i];
        }
        int diff = bin_numbers[i] - num - check;
        if (diff < 0) {
            diff += 2;
            check = 1;
        } else {
            check = 0;
        }
        res.bin_numbers[i] = diff;
    }
    return res;
}

long_number long_number::operator * (const long_number & other) const {
    long_number res;
    size_t new_size = bin_numbers.size() + other.bin_numbers.size();
    res.bin_numbers.resize(new_size, 0);
    for (size_t i = 0; i != bin_numbers.size(); ++i) {
        int check = 0;
        for (size_t j = 0; j != other.bin_numbers.size(); ++j) {
            int prod = bin_numbers[i] * other.bin_numbers[j] + res.bin_numbers[i + j] + check;
            res.bin_numbers[i + j] = prod % 2;
            check = prod / 2;
        }
        res.bin_numbers[i + other.bin_numbers.size()] += check;
    }
    return res;
}

long_number long_number::operator / (const long_number & other) const {
    long_number result;
    long_number rem = *this;

    for (int i = bin_numbers.size() - other.bin_numbers.size(); i >= 0; --i) {
        long_number split = other;
        split.bin_numbers.insert(split.bin_numbers.begin(), i, 0);

        if (rem > split || rem == split) {
            rem = rem - split;
            result.bin_numbers.insert(result.bin_numbers.begin(), 1);
        } else {
            result.bin_numbers.insert(result.bin_numbers.begin(), 0);
        }
    }

    return result;
}

bool long_number::operator == (const long_number & other) const {
    return bin_numbers == other.bin_numbers;
}

bool long_number::operator != (const long_number & other) const {
    return !(bin_numbers == other.bin_numbers);
}

bool long_number::operator < (const long_number & other) const {
    if (bin_numbers.size() != other.bin_numbers.size()) {
        if (bin_numbers.size() < other.bin_numbers.size()) {
            return true;
        } else {
            return false;
        }
    }
    for (size_t i = bin_numbers.size(); i != 0; --i) {
        if (bin_numbers[i - 1] != other.bin_numbers[i - 1]) {
            if (bin_numbers[i - 1] < other.bin_numbers[i - 1]) {
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

bool long_number::operator > (const long_number & other) const {
    if (bin_numbers.size() != other.bin_numbers.size()) {
        if (bin_numbers.size() > other.bin_numbers.size()) {
            return true;
        } else {
            return false;
        }
    }
    for (size_t i = bin_numbers.size(); i != 0; --i) {
        if (bin_numbers[i - 1] != other.bin_numbers[i - 1]) {
            if (bin_numbers[i - 1] > other.bin_numbers[i - 1]) {
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

int long_number::after_point = 6;

void long_number::set_after_point(int new_after_point) {
    after_point = new_after_point;
}

long_number operator ""_longnum(long double number) {
    std::string string;
    long long integer = static_cast<long long>(std::floor(number));
    long double fraction = number - integer;
    
    if (integer == 0) {
        string = "0";
    } else {
        while (integer > 0) {
            string.insert(string.begin(), (integer % 2) + '0');
            integer /= 2;
        }
    }
    string += '.';

    for (int i = 0; i != long_number::after_point; ++i) {
        fraction *= 2;
        if (fraction >= 1.0) {
            string += '1';
            fraction -= 1.0;
        } else {
            string += '0';
        }
    }

    return long_number(string);
}

std::string long_number::to_str() const {
    std::string string;
    for (size_t i = bin_numbers.size(); i != 0; --i) {
        string += std::to_string(bin_numbers[i - 1]);
    }
    return string;
}

/*
int main() {

    long_number::set_after_point(10);

    long_number ch1 = 10.0_longnum;
    long_number ch2 = 5.0_longnum;

    long_number sum = ch1 + ch2;
    long_number diff = ch1 - ch2;
    long_number prod = ch1 * ch2;
    long_number div = ch1 / ch2;

    std::cout << "Sum: " << sum.to_str() << '\n';
    std::cout << "Diff: " << diff.to_str() << '\n';
    std::cout << "Prod: " << prod.to_str() << '\n';
    std::cout << "Div: " << div.to_str() << '\n';

    return 0;
}
*/



