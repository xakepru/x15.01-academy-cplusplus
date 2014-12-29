// Владимир Керимов специально для журнала "Хакер"

#include "decimal.hpp"
#include <iostream>
#include <conio.h>

int main()
{
    decimal a;
    std::cout << "\n decimal a; a: " << a;
    decimal b = -123.456789;
    std::cout << "\n decimal b = 123.456789; b: " << b;
    decimal c(11, 2);
    std::cout << "\n decimal c(11, 2); c: " << c;
    a = -1, b = 3, c = a / b;
    std::cout << "\n a = -1, b = 3, c = a / b; c: " << c;
    a = c * b;
    std::cout << "\n a = c * b; a: " << a;

    std::cout << "\n\n Press any key... ";
    _getch();
    return 0;
}
