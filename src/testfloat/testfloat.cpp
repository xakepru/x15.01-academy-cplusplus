#include <iostream>
#include <conio.h>
#include <cstdint>
#include <typeinfo>
#include <string>

template <typename value_type>
std::string binary_output(value_type value)
{
    std::string result;
    result.reserve(sizeof(value));
    value_type bit = 1;
    for (bit <<= 8 * sizeof(value) - 1; bit; bit >>= 1)
    {
        result.push_back( (value & bit) == 0 ? '0' : '1' );
    }
    return result;
}

template <typename value_type>
struct binary_float;

template <>
struct binary_float<float>
{
    typedef uint32_t int_type;
    static const int_type sgn_mask = 0x80000000uL;
    static const int_type exp_mask = 0x7F800000uL;
    static const int_type man_mask = 0x00700000uL;
    static const int_type exp_bias = 127;
    static const int sgn_shift = 31;
    static const int exp_shift = 23;
    static const int exp_size = 8;
    static const int man_size = 23;
    static const int man_offset = 9;
};

template <>
struct binary_float<double>
{
    typedef uint64_t int_type;
    static const int_type sgn_mask = 0x8000000000000000uLL;
    static const int_type exp_mask = 0x7FF0000000000000uLL;
    static const int_type man_mask = 0x000FFFFFFFFFFFFFuLL;
    static const int_type exp_bias = 1023;
    static const int sgn_shift = 63;
    static const int exp_shift = 52;
    static const int exp_size = 11;
    static const int man_size = 52;
    static const int man_offset = 12;
};

template <typename value_type>
void show_details(value_type value)
{
    union floating_representation
    {
        value_type value;
        typename binary_float<value_type>::int_type binary;
    } representation;
    representation.value = value;
    auto binary_value = representation.binary;
    std::string bit_string = binary_output(binary_value);
    std::cout << "\n floating-point value: " << value << " of " << typeid(value).name()
              << "\n bits: " << bit_string
              << "\n sign: " << bit_string[0]
              << "\n exponent: " << bit_string.substr(1, binary_float<value_type>::exp_size) << " ~ " 
                                 << ((binary_value & binary_float<value_type>::exp_mask) >> binary_float<value_type>::exp_shift) - binary_float<value_type>::exp_bias
              << "\n mantissa: " << bit_string.substr(binary_float<value_type>::man_offset, binary_float<value_type>::man_size)
              << std::endl;
}

int main()
{
    double double_precision = 640.0;
    float  single_precision = 640.0f;
    show_details(double_precision);
    show_details(single_precision);
    std::cout << "\n Press any key... ";
    _getch();
    return 0;
}
