// Класс десятичной дроби с фиксированной точкой
// Владимир Керимов (c) 2012
// редакция файла для журнала "Хакер"

#include "decimal.hpp"
#include <algorithm>
#include <typeinfo>
#include <limits>
#include <cstdio>
#include <cmath>

namespace
{
    static const uint64_t POW10[] = {
        1uLL,                   // 10^0
        10uLL,                  // 10^1
        100uLL,                 // 10^2
        1000uLL,                // 10^3
        10000uLL,               // 10^4
        100000uLL,              // 10^5
        1000000uLL,             // 10^6
        10000000uLL,            // 10^7
        100000000uLL,           // 10^8
        1000000000uLL,          // 10^9
        10000000000uLL,         // 10^10
        100000000000uLL,        // 10^11
        1000000000000uLL,       // 10^12
        10000000000000uLL,      // 10^13
        100000000000000uLL,     // 10^14
        1000000000000000uLL,    // 10^15
        10000000000000000uLL,   // 10^16
        100000000000000000uLL,  // 10^17
        1000000000000000000uLL, // 10^18
    };

    static const uint64_t HALF_POW10[] = {
        0,                      // 10^0  / 2
        5uLL,                   // 10^1  / 2
        50uLL,                  // 10^2  / 2
        500uLL,                 // 10^3  / 2
        5000uLL,                // 10^4  / 2
        50000uLL,               // 10^5  / 2
        500000uLL,              // 10^6  / 2
        5000000uLL,             // 10^7  / 2
        50000000uLL,            // 10^8  / 2
        500000000uLL,           // 10^9  / 2
        5000000000uLL,          // 10^10 / 2
        50000000000uLL,         // 10^11 / 2
        500000000000uLL,        // 10^12 / 2
        5000000000000uLL,       // 10^13 / 2
        50000000000000uLL,      // 10^14 / 2
        500000000000000uLL,     // 10^15 / 2
        5000000000000000uLL,    // 10^16 / 2
        50000000000000000uLL,   // 10^17 / 2
        500000000000000000uLL,  // 10^18 / 2
    };


}

const double decimal::multiplier_double = 1.0  / decimal::divider;
const float  decimal::multiplier_float  = 1.0f / decimal::divider;

decimal::decimal(int32_t precision)
    : m_integral(0),
      m_fractional(0),
      m_precision(precision)
{
}

decimal::decimal(int64_t integral, uint64_t fractional, int32_t precision)
    : m_integral(integral),
      m_fractional(fractional),
      m_precision(precision)
{
}

decimal::decimal(double value, int32_t precision)
    : m_integral(static_cast<int64_t>(std::floor(value))),
      m_fractional(static_cast<uint64_t>((value - m_integral) * divider + 0.5)),
      m_precision(precision)
{
    normalize();
}

void decimal::normalize()
{
    static const uint64_t delta = epsilon_double / 2;
    uint64_t rem = m_fractional % epsilon_double;
    if (rem)
    {
        if (rem > delta)
            m_fractional += epsilon_double - rem;
        else
            m_fractional -= rem;
    }
}

decimal::decimal(float value, int32_t precision)
    : m_integral(static_cast<int64_t>(std::floor(value))),
      m_fractional(static_cast<uint64_t>((value - m_integral) * divider + 0.5)),
      m_precision(precision)
{
    normfloat();
}

void decimal::normfloat()
{
    static const uint64_t delta = epsilon_float / 2;
    uint64_t rem = m_fractional % epsilon_float;
    if (rem)
    {
        if (rem > delta)
            m_fractional += epsilon_float - rem;
        else
            m_fractional -= rem;
    }
}

void decimal::set_precision(int32_t precision)
{
    if (precision > precision_max)
        m_precision = precision_max;
    else if (precision < precision_auto)
        m_precision = precision_auto;
    else
        m_precision = precision;
}

decimal::decimal(int64_t value, int32_t precision)
    : m_integral(value),
      m_fractional(0),
      m_precision(precision)
{
}

decimal::decimal(uint64_t value, int32_t precision)
    : m_integral(static_cast<int64_t>(value)),
      m_fractional(0),
      m_precision(precision)
{
}

decimal::decimal(int32_t value, int32_t precision)
    : m_integral(value),
      m_fractional(0),
      m_precision(precision)
{
}

decimal::decimal(uint32_t value, int32_t precision)
    : m_integral(value),
      m_fractional(0),
      m_precision(precision)
{
}

decimal::decimal(int16_t value, int32_t precision)
    : m_integral(value),
      m_fractional(0),
      m_precision(precision)
{
}

decimal::decimal(uint16_t value, int32_t precision)
    : m_integral(value),
      m_fractional(0),
      m_precision(precision)
{
}

decimal::decimal(int8_t value, int32_t precision)
    : m_integral(value),
      m_fractional(0),
      m_precision(precision)
{
}

decimal::decimal(uint8_t value, int32_t precision)
    : m_integral(value),
      m_fractional(0),
      m_precision(precision)
{
}

decimal::decimal(bool value, int32_t precision)
    : m_integral(value),
      m_fractional(0),
      m_precision(precision)
{
}

decimal& decimal::operator = (double value)
{
    return *this = decimal(value, m_precision);
}

decimal& decimal::operator = (float value)
{
    return *this = decimal(value, m_precision);
}

decimal& decimal::operator = (int64_t value)
{
    return *this = decimal(value, m_precision);
}

decimal& decimal::operator = (int32_t value)
{
    return *this = decimal(value, m_precision);
}

decimal& decimal::operator = (int16_t value)
{
    return *this = decimal(value, m_precision);
}

decimal& decimal::operator = (int8_t value)
{
    return *this = decimal(value, m_precision);
}

decimal& decimal::operator = (uint64_t value)
{
    return *this = decimal(value, m_precision);
}

decimal& decimal::operator = (uint32_t value)
{
    return *this = decimal(value, m_precision);
}

decimal& decimal::operator = (uint16_t value)
{
    return *this = decimal(value, m_precision);
}

decimal& decimal::operator = (uint8_t value)
{
    return *this = decimal(value, m_precision);
}

decimal& decimal::operator = (bool value)
{
    return *this = decimal(value, m_precision);
}

double decimal::to_double() const
{
    return m_integral + get_fractional_as_double();
}

float decimal::to_float() const
{
    return m_integral + get_fractional_as_float();
}

int64_t decimal::to_int64() const
{
    return m_fractional < divider / 2 ? m_integral : m_integral + 1;
}

template <typename result_type, typename value_type>
result_type check_range_cast(value_type value)
{
    if (value > std::numeric_limits<result_type>::max() ||
        value < std::numeric_limits<result_type>::min())
    {
        throw std::out_of_range("Decimal value is out of range of type " + std::string(typeid(result_type).name()));
    }
    return static_cast<result_type>(value);
}

int32_t decimal::to_int32() const
{
    return check_range_cast<int32_t>(to_int64());
}

int16_t decimal::to_int16() const
{
    return check_range_cast<int16_t>(to_int64());
}

int8_t decimal::to_int8() const
{
    return check_range_cast<int8_t>(to_int64());
}

uint64_t decimal::to_uint64() const
{
    int64_t result = to_int64();
    if (result < 0)
    {
        throw std::out_of_range("Decimal value is negative and cannot be unsigned type");
    }
    return static_cast<uint64_t>(result);
}

uint32_t decimal::to_uint32() const
{
    return check_range_cast<uint32_t>(to_uint64());
}

uint16_t decimal::to_uint16() const
{
    return check_range_cast<uint16_t>(to_uint64());
}

uint8_t decimal::to_uint8() const
{
    return check_range_cast<uint8_t>(to_uint64());
}

bool decimal::to_bool() const
{
    return m_integral && m_fractional;
}

decimal::operator int64_t() const
{
    return to_int64();
}

decimal::operator int32_t() const
{
    return to_int32();
}

decimal::operator int16_t() const
{
    return to_int16();
}

decimal::operator int8_t() const
{
    return to_int8();
}

decimal::operator uint64_t() const
{
    return to_uint64();
}

decimal::operator uint32_t() const
{
    return to_uint32();
}

decimal::operator uint16_t() const
{
    return to_uint16();
}

decimal::operator uint8_t() const
{
    return to_uint8();
}

template <typename value_type>
std::string cast_to_string(value_type value, char const* format, size_t max_size = 20)
{
    std::string result(max_size, '\0');
    int bytes_written = _snprintf(&result.at(0), result.size(), format, value);
    result.resize(bytes_written);
    return result;
}

std::string decimal::to_string() const
{
    int64_t  lex_int;
    uint64_t lex_frac;
    if (m_integral >= 0 || !m_fractional)
        lex_int = m_integral, lex_frac = m_fractional;
    else
        lex_int = m_integral + 1, lex_frac = divider - m_fractional;
    if (m_precision == precision_auto)
    {
        if (!m_fractional)
            return cast_to_string(lex_int, "%lld");
        else
        {
            std::string dec = cast_to_string(lex_frac, "%018llu");
            size_t last = dec.find_last_not_of('0');
            dec.resize(last + 1);
            return cast_to_string(lex_int, "%lld") + '.' + dec;
        }
    }
    else if (!m_precision)
    {
        return cast_to_string(lex_int, "%lld");
    }
    else
    {
        if (m_precision < 0 || m_precision > precision_max)
            std::runtime_error("Unexpected precision of decimal value");
        int p = precision_max - m_precision;
        return cast_to_string(lex_int, "%lld") + '.' 
             + cast_to_string((lex_frac + HALF_POW10[p]) / POW10[p], "%018llu").substr(0, m_precision);
    }
}

void decimal::from_string(std::string const& source)
{
    double value = 0;
    int read_count = _snscanf(source.c_str(), source.size(), "%LG", &value);
    if (read_count != 1)
        throw std::runtime_error("Unable to read value from string: " + (source.size() < 0x100 ? source : source.substr(0, 0x100) + "..."));
    *this = decimal(value);
}

int64_t decimal::get_floor() const
{
    return m_integral;
}

int64_t decimal::get_ceil() const
{
    return m_fractional ? m_integral + 1 : m_integral;
}

int64_t decimal::get_rounded() const
{
    return m_fractional >= divider / 2 ? m_integral + 1 : m_integral;
}

double decimal::get_fractional_as_double() const
{
    return m_fractional * multiplier_double;
}

float decimal::get_fractional_as_float() const
{
    return m_fractional * multiplier_float;
}

decimal decimal::get_rounded_to(int32_t precision) const
{
    decimal result = *this;
    if (precision >= 0 || precision <= precision_max)
    {
        result.m_fractional -= m_fractional % POW10[precision];
        result.m_precision = std::min(m_precision, precision);
    }
    return result;
}

decimal decimal::get_absolute() const
{
    if (m_integral < 0)
    {
        if (m_fractional)
            return decimal(-m_integral - 1, divider - m_fractional, m_precision);
        else
            return decimal(-m_integral, m_precision);
    }
    else
        return *this;
}

decimal& decimal::operator += (const decimal& arg)
{
    m_integral += arg.m_integral;
    m_fractional += arg.m_fractional;
    if (m_fractional >= divider)
        ++m_integral, m_fractional -= divider;
    m_precision = std::max(m_precision, arg.m_precision);
    return *this;
}

decimal& decimal::operator -= (const decimal& arg)
{
    m_integral -= arg.m_integral;
    if (m_fractional >= arg.m_fractional)
        m_fractional -= arg.m_fractional;
    else
        --m_integral, m_fractional = divider - (arg.m_fractional - m_fractional);
    m_precision = std::max(m_precision, arg.m_precision);
    return *this;
}

decimal& decimal::operator *= (const decimal& arg)
{
    return (*this = *this * arg);
}

decimal& decimal::operator /= (const decimal& arg)
{
    return (*this = *this / arg);
}

decimal decimal::operator + (const decimal& arg) const
{
    decimal res = *this;
    return res += arg;
}

decimal decimal::operator - (const decimal& arg) const
{
    decimal res = *this;
    return res -= arg;
}

decimal decimal::operator - () const
{
    decimal res(-m_integral, m_precision);
    if (m_fractional)
    {
        --res.m_integral;
        res.m_fractional = divider - m_fractional;
    }
    return res;
}

decimal decimal::operator * (const decimal& another) const
{
    static const int64_t SIGNBIT = 1LL << 63;
    static const uint64_t LIM63 = (1uLL << 63) - 1;
    static const uint64_t LIM18 = LIM63 / divider;
    static const uint64_t LIM09 = LIM63 / divider_sqrt;
    static const char* ERRMSG = "Multiplication overflow for too big decimal point values.";

    decimal left = get_absolute();
    decimal right = another.get_absolute();
    uint64_t a = static_cast<uint64_t>(left.m_integral);
    uint64_t b = left.m_fractional;
    uint64_t c = static_cast<uint64_t>(right.m_integral);
    uint64_t d = right.m_fractional;
    uint64_t A[4][4], B[4], C[4];
    B[0] = a / divider_sqrt, B[1] = a % divider_sqrt, B[2] = b / divider_sqrt, B[3] = b % divider_sqrt;
    C[0] = c / divider_sqrt, C[1] = c % divider_sqrt, C[2] = d / divider_sqrt, C[3] = d % divider_sqrt;

    if (C[0] && B[0] > LIM63 / C[0])
        throw std::runtime_error(ERRMSG);

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            A[i][j] = B[i] * C[j];
            if (A[i][j] > LIM63)
                throw std::runtime_error(ERRMSG);
        }
    }

    if (A[0][0] > LIM18)
        throw std::runtime_error(ERRMSG);

    if (A[0][1] > LIM09 || A[1][0] > LIM09)
        throw std::runtime_error(ERRMSG);

    uint64_t E = A[0][0] * divider;
    if (E > LIM63)
        throw std::runtime_error(ERRMSG);

    E += (A[0][1] + A[1][0]) * divider_sqrt;
    if (E > LIM63)
        throw std::runtime_error(ERRMSG);

    E += A[0][2] + A[1][1] + A[2][0];
    if (E > LIM63)
        throw std::runtime_error(ERRMSG);

    uint64_t D = A[0][3] + A[1][2] + A[2][1] + A[3][0];
    if (D > LIM63)
        throw std::runtime_error(ERRMSG);

    E += D / divider_sqrt;
    if (E > LIM63)
        throw std::runtime_error(ERRMSG);

    uint64_t F = (D % divider_sqrt) * divider_sqrt + A[1][3] + A[2][2] + A[3][1] + (A[2][3] + A[3][2]) / divider_sqrt;
    if (F % 10 == 9) ++F; // correction of 999... at end
    if (F >= divider)
    {
        E += F / divider;
        F = F % divider;
    }

    decimal res(static_cast<int64_t>(E), std::max(m_precision, another.m_precision));
    res.m_fractional = F;

    int64_t negative = (m_integral & SIGNBIT) ^ (another.m_integral & SIGNBIT);

    return negative ? -res : res;
}

decimal decimal::operator / (const decimal& arg) const
{
    return *this * arg.reverse();
}

decimal decimal::reverse() const
{
    decimal res(0LL, m_precision);
    decimal arg = get_absolute();
    uint64_t a = static_cast<uint64_t>(arg.m_integral);
    uint64_t b = arg.m_fractional;
    if (!a)
    {
        if (!m_fractional)
            throw std::runtime_error("Division by zero value with decimal point.");
        res.m_integral = static_cast<int64_t>(divider / b);
        res.m_fractional = (divider % b) * divider;
    }
    else
    {
        int n = 1;
        for (; n <= 18 && a >= POW10[n]; ++n);
        if (n > 18) res.m_fractional = 0;
        else
        {
            uint64_t u = divider;
            uint64_t v = a * POW10[18 - n] + b / POW10[n];
            res.m_fractional = u / v * POW10[18 - n];
            for (++n; n <= 18; ++n)
            {
                u = u % v * 10;
                if (!u) break;
                res.m_fractional += u / v * POW10[18 - n];
            }
        }
    }
    return m_integral < 0 ? -res : res;
}

std::ostream& operator << (std::ostream& output, const decimal& value)
{
    return output << value.to_string();
}

std::istream& operator >> (std::istream& input, decimal& result)
{
    std::string temporary;
    input >> temporary;
    result.from_string(temporary);
    return input;
}
