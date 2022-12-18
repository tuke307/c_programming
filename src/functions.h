#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct
{
    double real;
    double imaginary;
}complex_number;

typedef struct
{
    double phi;
    double phi_cos;
    double phi_sin;
    double r;
}output_vars;

complex_number addition(complex_number num1, complex_number num2);
complex_number subtraction(complex_number num1, complex_number num2);
complex_number multiply(complex_number num1, complex_number num2);
complex_number division(complex_number num1, complex_number num2);

complex_number convert_str_to_complex_number(char* num);

output_vars calculate_output_vars(complex_number num);

#endif