#include <iostream>
#include <string>
#include <vector>
#include <bitset>

class long_number {
private:
    std::vector<int> bin_numbers;
    static int after_point;
    
    void from_str_to_vec(const std::string & string);
public:
    long_number();
    long_number(const std::string & string);
    long_number(const long_number & other);
    ~long_number();

    long_number & operator = (const long_number & other);

    long_number operator + (const long_number & other) const;
    long_number operator - (const long_number & other) const;
    long_number operator * (const long_number & other) const;
    long_number operator / (const long_number & other) const;

    bool operator == (const long_number & other) const;
    bool operator != (const long_number & other) const;
    bool operator < (const long_number & other) const;
    bool operator > (const long_number & other) const;

    static void set_after_point(int after_point);

    friend long_number operator ""_longnum (long double number);

    std::string to_str() const;
    
};