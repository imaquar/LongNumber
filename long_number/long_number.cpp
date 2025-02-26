#include "long_number.hpp"
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <string>
#include <chrono>

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
        if (i == '.') {
            bin_numbers.insert(bin_numbers.begin(), -1);
        }
    }
}

long_number::long_number(int after_point, bool is_negative) : after_point(after_point), is_negative(is_negative) {}

long_number::long_number(const std::string & string, int after_point, bool is_negative) : after_point(after_point), is_negative(is_negative) {
    from_str_to_vec(string);
}

long_number::long_number(const long_number & other) : bin_numbers(other.bin_numbers), after_point(other.after_point), is_negative(other.is_negative) {}

long_number::~long_number() {}

long_number & long_number::operator = (const long_number & other) {
    if (this != &other) {
        bin_numbers = other.bin_numbers;
        after_point = other.after_point;
        is_negative = other.is_negative;
    }
    return *this;
}

long_number long_number::operator-() const {
    long_number result = *this;
    result.is_negative = !is_negative;
    return result;
}

long_number long_number::operator + (const long_number & other) const {
    if (is_negative == other.is_negative) {
        long_number res;
        res.is_negative = is_negative;
        int check = 0;
        size_t max_size = maxi(bin_numbers.size(), other.bin_numbers.size());
        res.bin_numbers.resize(max_size, 0);

        int pos1 = -1;
        int pos2 = -1;

        for (size_t i = 0; i != bin_numbers.size(); ++i) {
            if (bin_numbers[i] == -1) {
                pos1 = i;
                break;
            }
        }
        for (size_t i = 0; i != other.bin_numbers.size(); ++i) {
            if (other.bin_numbers[i] == -1) {
                pos2 = i;
                break;
            }
        }

        int decimal_shift = 0;
        if (pos1 != -1 && pos2 != -1) {
            decimal_shift = pos1 - pos2;
        } else if (pos1 != -1) {
            decimal_shift = pos1;
        } else if (pos2 != -1) {
            decimal_shift = -pos2;
        }

        for (size_t i = 0; i != max_size; ++i) {
            int idx1 = i - decimal_shift;
            int idx2 = i;

            if (idx1 >= 0 && static_cast<size_t>(idx1) < bin_numbers.size() && bin_numbers[idx1] == -1) {
                res.bin_numbers[i] = -1;
                continue;
            }
            if (idx2 >= 0 && static_cast<size_t>(idx2) < other.bin_numbers.size() && other.bin_numbers[idx2] == -1) {
                res.bin_numbers[i] = -1;
                continue;
            }

            int sum = check;
            if (idx1 >= 0 && static_cast<size_t>(idx1) < bin_numbers.size() && bin_numbers[idx1] != -1) {
                sum += bin_numbers[idx1];
            }
            if (idx2 >= 0 && static_cast<size_t>(idx2) < other.bin_numbers.size() && other.bin_numbers[idx2] != -1) {
                sum += other.bin_numbers[idx2];
            }
            res.bin_numbers[i] = sum % 2;
            check = sum / 2;
        }
        if (check) {
            res.bin_numbers.push_back(check);
        }
        return res;
    } else {
        if (is_negative) {
            long_number temp = *this;
            temp.is_negative = false;
            return other - temp;
        } else {
            long_number temp = other;
            temp.is_negative = false;
            return *this - temp;
        }
    }
}

long_number long_number::operator - (const long_number & other) const {
    if (*this == other) {
        return long_number("0", after_point, false);
    }

    if (is_negative == other.is_negative) {
        if (*this < other) {
            long_number res = other - *this;
            res.is_negative = !is_negative;
            return res;
        }
        long_number res;
        res.is_negative = is_negative;
        int check = 0;
        size_t max_size = maxi(bin_numbers.size(), other.bin_numbers.size());
        res.bin_numbers.resize(max_size, 0);
        for (size_t i = 0; i != max_size; ++i) {
            if (bin_numbers[i] == -1 || other.bin_numbers[i] == -1) {
                res.bin_numbers[i] = -1;
                continue;
            }
            int num = 0;
            if (i < other.bin_numbers.size() && other.bin_numbers[i] != -1) {
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

        while (res.bin_numbers.size() > 1 && res.bin_numbers.back() == 0) {
            res.bin_numbers.pop_back();
        }

        if (res.bin_numbers.back() == -1) {
            res.bin_numbers.push_back(0);
        }

        bool is_zero = true;
        for (int digit : res.bin_numbers) {
            if (digit != 0 && digit != -1) {
                is_zero = false;
                break;
            }
        }
        if (is_zero) {
            return long_number("0", after_point, false);
        }

        return res;
    } else {
        if (is_negative) {
            long_number temp = *this;
            temp.is_negative = false;
            return -(temp + other);
        } else {
            long_number temp = other;
            temp.is_negative = false;
            return *this + temp;
        }
    }
}

long_number long_number::operator * (const long_number & other) const {
    long_number res;
    res.is_negative = is_negative != other.is_negative;

    int pos1 = -1;
    int pos2 = -1;

    for (size_t i = 0; i != bin_numbers.size(); ++i) {
        if (bin_numbers[i] == -1) {
            pos1 = i;
            break;
        }
    }
    for (size_t i = 0; i != other.bin_numbers.size(); ++i) {
        if (other.bin_numbers[i] == -1) {
            pos2 = i;
            break;
        }
    }

    std::vector<int> num1 = bin_numbers;
    std::vector<int> num2 = other.bin_numbers;

    if (pos1 != -1) {
        num1.erase(num1.begin() + pos1);
    }
    if (pos2 != -1) {
        num2.erase(num2.begin() + pos2);
    }

    size_t new_size = num1.size() + num2.size();
    res.bin_numbers.resize(new_size, 0);

    for (size_t i = 0; i != num1.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j != num2.size(); ++j) {
            int prod = num1[i] * num2[j] + res.bin_numbers[i + j] + carry;
            res.bin_numbers[i + j] = prod % 2;
            carry = prod / 2;
        }
        if (carry != 0) {
            res.bin_numbers[i + num2.size()] += carry;
        }
    }

    int total_decimal_places = (pos1 != -1 ? bin_numbers.size() - pos1 - 1 : 0) +
                               (pos2 != -1 ? other.bin_numbers.size() - pos2 - 1 : 0);

    if (total_decimal_places > 0) {
        res.bin_numbers.insert(res.bin_numbers.begin() + (res.bin_numbers.size() - total_decimal_places), -1);
    }

    while (res.bin_numbers.size() > 1 && res.bin_numbers.back() == 0 && res.bin_numbers[res.bin_numbers.size() - 2] != -1) {
        res.bin_numbers.pop_back();
    }

    res.after_point = maxi(after_point, other.after_point);
    res.adjust_after_point();

    return res;
}

long_number long_number::operator / (const long_number & other) const {
    if (other == long_number("0", other.after_point, false)) {
        throw std::invalid_argument("Division by zero");
    }

    long_number res;
    res.is_negative = is_negative != other.is_negative;
    long_number rem = *this;
    long_number other_copy = other;

    int pos1 = -1;
    int pos2 = -1;

    for (size_t i = 0; i != bin_numbers.size(); ++i) {
        if (bin_numbers[i] == -1) {
            pos1 = i;
            break;
        }
    }
    for (size_t i = 0; i != other_copy.bin_numbers.size(); ++i) {
        if (other_copy.bin_numbers[i] == -1) {
            pos2 = i;
            break;
        }
    }

    if (pos1 != -1) {
        rem.bin_numbers.erase(rem.bin_numbers.begin() + pos1);
    }
    if (pos2 != -1) {
        other_copy.bin_numbers.erase(other_copy.bin_numbers.begin() + pos2);
    }

    size_t size_diff = (rem.bin_numbers.size() > other_copy.bin_numbers.size()) ? rem.bin_numbers.size() - other_copy.bin_numbers.size() : other_copy.bin_numbers.size() - rem.bin_numbers.size();
    
    for (int i = after_point; i >= 0; --i) {
        long_number split = other_copy;
        split.bin_numbers.insert(split.bin_numbers.begin(), size_diff, 0);
        size_diff = std::max(static_cast<int>(size_diff) - 1, 0);
    
        if (rem >= split) {
            rem = rem - split;
            res.bin_numbers.insert(res.bin_numbers.begin(), 1);
            rem.bin_numbers.insert(rem.bin_numbers.begin(), 0);
        } else {
            res.bin_numbers.insert(res.bin_numbers.begin(), 0);
            rem.bin_numbers.insert(rem.bin_numbers.begin(), 0);
        }
    }

    int count = 0;
    if (pos1 != -1) {
        count += bin_numbers.size() - pos1 - 1;
    }
    if (pos2 != -1) {
        count -= other_copy.bin_numbers.size() - pos2 - 1;
    }

    if (count > 0) {
        res.bin_numbers.insert(res.bin_numbers.end() - count, -1);
    } else {
        res.bin_numbers.insert(res.bin_numbers.end() - 1, -1);
    }

    res.after_point = maxi(after_point, other.after_point);
    res.adjust_after_point();

    return res;
}

bool long_number::operator == (const long_number & other) const {
    return bin_numbers == other.bin_numbers && after_point == other.after_point && is_negative == other.is_negative;
}

bool long_number::operator != (const long_number & other) const {
    return !(*this == other);
}

bool long_number::operator < (const long_number & other) const {
    if (is_negative != other.is_negative) {
        return is_negative;
    }
    if (bin_numbers.size() != other.bin_numbers.size()) {
        return bin_numbers.size() < other.bin_numbers.size();
    }
    for (size_t i = bin_numbers.size(); i != 0; --i) {
        if (bin_numbers[i - 1] != other.bin_numbers[i - 1]) {
            return bin_numbers[i - 1] < other.bin_numbers[i - 1];
        }
    }
    return false;
}

bool long_number::operator > (const long_number & other) const {
    if (is_negative != other.is_negative) {
        return other.is_negative;
    }
    if (bin_numbers.size() != other.bin_numbers.size()) {
        return bin_numbers.size() > other.bin_numbers.size();
    }
    for (size_t i = bin_numbers.size(); i != 0; --i) {
        if (bin_numbers[i - 1] != other.bin_numbers[i - 1]) {
            return bin_numbers[i - 1] > other.bin_numbers[i - 1];
        }
    }
    return false;
}

bool long_number::operator >= (const long_number & other) const {
    return !(*this < other);
}

void long_number::adjust_after_point() {
    int current_size = bin_numbers.size();
    int count = 0;
    for (int i = 0; i != current_size; ++i) {
        if (bin_numbers[i] == -1) {
            break;
        }
        count += 1;
    }
    if (after_point > count) {
        for (int i = 0; i != after_point - count; ++i) {
            bin_numbers.insert(bin_numbers.begin(), 0);
        }
    } else if (after_point < current_size) {
        bin_numbers.erase(bin_numbers.begin(), bin_numbers.begin() + (count - after_point));
    }
}

void long_number::set_after_point(int new_after_point) {
    after_point = new_after_point;
    adjust_after_point();
}

int long_number::get_after_point() const {
    return after_point;
}

bool long_number::get_is_negative() const {
    return is_negative;
}

void long_number::set_is_negative(bool is_negative) {
    this->is_negative = is_negative;
}

std::string long_number::to_str() const {
    std::string string;
    if (is_negative) {
        string += '-';
    }
    int count = 0;
    bool has_non_zero = false;
    for (size_t i = bin_numbers.size(); i != 0; --i) {
        if (i == bin_numbers.size() && bin_numbers[i - 2] == -1) {
            count = 1;
        }
        if (bin_numbers[i - 1] == 1) {
            count = 1;
            has_non_zero = true;
        }
        if (count == 1) {
            if (bin_numbers[i - 1] == -1) {
                string += '.';
            } else {
                string += std::to_string(bin_numbers[i - 1]);
            }
        }
    }
    if (!has_non_zero) {
        string = "0";
    }
    return string;
}

long_number operator ""_longnum(long double number) {
    std::string string;
    bool is_negative = number < 0;
    if (is_negative) {
        number = -number;
    }
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

    while (fraction > 0.0) {
        fraction *= 2;
        if (fraction >= 1.0) {
            string += '1';
            fraction -= 1.0;
        } else {
            string += '0';
        }

        if (string.size() > 1000) {
            break;
        }
    }

    return long_number(string, 1024, is_negative);
}

void long_number::print_bin_number() const {
    bool decimal_point_passed = false;
    for (auto it = bin_numbers.rbegin(); it != bin_numbers.rend(); ++it) {
        if (*it == -1) {
            std::cout << '.';
            decimal_point_passed = true;
        } else {
            std::cout << *it;
        }
    }
    if (!decimal_point_passed) {
        std::cout << ".0";
    }
    std::cout << std::endl;
}

void long_number::insert_zeros_after_decimal_point() {

    auto it = std::find(bin_numbers.begin(), bin_numbers.end(), -1);

    if (it != bin_numbers.end()) {
        bin_numbers.insert(it, 4, 0);
    }
}

const std::vector<int>& long_number::get_bin_numbers() const {
    return bin_numbers;
}