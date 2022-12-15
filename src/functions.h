#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct
{
    double real;
    double imaginary;
}complex_number;

complex_number addition(complex_number num1, complex_number num2);
complex_number subtraction(complex_number num1, complex_number num2);
complex_number multiply(complex_number num1, complex_number num2);
complex_number division(complex_number num1, complex_number num2);

complex_number convert_str_to_complex_number(char* num);

double calculate_phi(complex_number num);
double calculate_r(complex_number num);

#endif