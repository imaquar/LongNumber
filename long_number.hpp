#include <iostream>
#include <string>
#include <vector>
#include <bitset>

class long_number {
private:
    std::vector<int> bin_numbers;
    int after_point;
    bool is_negative;
    
    void from_str_to_vec(const std::string & string);
public:
    long_number(int after_point = 6, bool is_negative = false);
    long_number(const std::string & string, int after_point = 6, bool is_negative = false);
    long_number(const long_number & other);
    ~long_number();

    long_number & operator = (const long_number & other);

    long_number operator-() const;

    long_number operator + (const long_number & other) const;
    long_number operator - (const long_number & other) const;
    long_number operator * (const long_number & other) const;
    long_number operator / (const long_number & other) const;

    bool operator == (const long_number & other) const;
    bool operator != (const long_number & other) const;
    bool operator < (const long_number & other) const;
    bool operator > (const long_number & other) const;
    bool operator >= (const long_number & other) const;

    void set_after_point(int after_point);
    int get_after_point() const;
    void adjust_after_point();

    std::string to_str() const;

    bool get_is_negative() const;
    void set_is_negative(bool is_negative);

    friend long_number operator ""_longnum(long double number);

    void print_bin_number() const;

    size_t size() const {
        return bin_numbers.size();
    }

    void insert_zeros_after_decimal_point();

    const std::vector<int>& get_bin_numbers() const;

};

long_number operator ""_longnum(long double number);

size_t maxi(size_t a, size_t b);