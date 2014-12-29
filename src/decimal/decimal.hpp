// Класс десятичной дроби с фиксированной точкой
// Владимир Керимов (c) 2012
// редакция файла для журнала "Хакер"

#pragma once

#include <cstdint>
#include <string>
#include <iosfwd>

class decimal
{
public:
    static const int32_t precision_max  = 18;
    static const int32_t precision_auto = -1;

    decimal(int32_t precision = precision_auto);

    decimal(int64_t integral, uint64_t fractional, int32_t precision);

    decimal(double value, int32_t precision = precision_auto);
    decimal(float  value, int32_t precision = precision_auto);

    decimal(int64_t value, int32_t precision = precision_auto);
    decimal(int32_t value, int32_t precision = precision_auto);
    decimal(int16_t value, int32_t precision = precision_auto);
    decimal(int8_t  value, int32_t precision = precision_auto);

    decimal(uint64_t value, int32_t precision = precision_auto);
    decimal(uint32_t value, int32_t precision = precision_auto);
    decimal(uint16_t value, int32_t precision = precision_auto);
    decimal(uint8_t  value, int32_t precision = precision_auto);

    decimal(bool value, int32_t precision = precision_auto);

    decimal& operator = (double   value);
    decimal& operator = (float    value);
    decimal& operator = (int64_t  value);
    decimal& operator = (int32_t  value);
    decimal& operator = (int16_t  value);
    decimal& operator = (int8_t   value);
    decimal& operator = (uint64_t value);
    decimal& operator = (uint32_t value);
    decimal& operator = (uint16_t value);
    decimal& operator = (uint8_t  value);
    decimal& operator = (bool     value);

    int64_t  get_integral()   const;
    uint64_t get_fractional() const;
    int32_t  get_precision()  const;

    void set_precision(int32_t precision);

    double   to_double() const;
    float    to_float()  const;
    int64_t  to_int64()  const;
    int32_t  to_int32()  const;
    int16_t  to_int16()  const;
    int8_t   to_int8()   const;
    uint64_t to_uint64() const;
    uint32_t to_uint32() const;
    uint16_t to_uint16() const;
    uint8_t  to_uint8()  const;
    bool     to_bool()   const;

    operator double()   const;
    operator float()    const;
    operator int64_t()  const;
    operator int32_t()  const;
    operator int16_t()  const;
    operator int8_t()   const;
    operator uint64_t() const;
    operator uint32_t() const;
    operator uint16_t() const;
    operator uint8_t()  const;
    operator bool()     const;

    std::string to_string() const;
    void from_string(std::string const& source);

    int64_t get_floor() const;
    int64_t get_ceil()  const;
    int64_t get_rounded() const;
    double  get_fractional_as_double() const;
    float   get_fractional_as_float() const;

    decimal get_rounded_to(int32_t precision) const;
    decimal get_absolute() const;

    decimal reverse() const;

    decimal& operator += (decimal const& another);
    decimal& operator -= (decimal const& another);
    decimal& operator *= (decimal const& another);
    decimal& operator /= (decimal const& another);

    decimal operator + (decimal const& another) const;
    decimal operator - (decimal const& another) const;
    decimal operator * (decimal const& another) const;
    decimal operator / (decimal const& another) const;

    decimal operator + () const;
    decimal operator - () const;

    bool operator ! () const;

    bool operator == (decimal const& another) const;
    bool operator != (decimal const& another) const;
    bool operator <= (decimal const& another) const;
    bool operator <  (decimal const& another) const;
    bool operator >= (decimal const& another) const;
    bool operator >  (decimal const& another) const;

private:
    int64_t  m_integral;
    uint64_t m_fractional;
    int32_t  m_precision;

    static const uint64_t divider      = static_cast<uint64_t>(1.0e+18);
    static const uint64_t divider_sqrt = static_cast<uint64_t>(1.0e+9);

    static const double multiplier_double;
    static const float  multiplier_float;

    static const uint64_t epsilon_double = static_cast<uint64_t>(1.0e+4);
    static const uint64_t epsilon_float  = static_cast<uint64_t>(1.0e+12);

    void normalize();
    void normfloat();
};

std::ostream& operator << (std::ostream& output, decimal const& value);
std::istream& operator >> (std::istream& input, decimal& result);
