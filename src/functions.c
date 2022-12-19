#include<stdio.h>
#include<string.h>
#include<math.h>
#include "functions.h"

complex_number addition(complex_number num1, complex_number num2)
{
    complex_number res;

    res.real = num1.real + num2.real;
    res.imaginary = num1.imaginary + num2.imaginary;

    return res;
}

complex_number subtraction(complex_number num1, complex_number num2)
{
    complex_number res;

    res.real = num1.real - num2.real;
    res.imaginary = num1.imaginary - num2.imaginary;

    return res;
}

complex_number multiply(complex_number num1, complex_number num2)
{
    complex_number res;

    res.real = num1.real * num2.real - num1.imaginary * num2.imaginary;
    res.imaginary = num1.real * num2.imaginary + num1.imaginary * num2.real;

    return res;
}

complex_number division(complex_number num1, complex_number num2)
{
    double divider;
    complex_number res;

    divider = num2.real * num2.real + num2.imaginary * num2.imaginary;
    res.real = (num1.real * num2.real + num1.imaginary * num2.imaginary) / divider;
    res.imaginary = (num1.imaginary * num2.real - num1.real * num2.imaginary) / divider;

    return res;
}

complex_number convert_str_to_complex_number(char* num)
{
    complex_number ret;
    char num1[256], num2[256];
    char const seperator = '+';
    char const c_imaginary = 'i';
    int seperator_index;

    if(num[0] == seperator)
    {
        printf("ERROR: Please ignore the mathematical operator (+) for positive numbers.\n");
        ret.isAssigned = 0;
        return ret;
    }

    if(num[strlen(num)-1] != c_imaginary)
    {
        printf("ERROR: Please use the correct format for complex numbers.\n");
        ret.isAssigned = 0;
        return ret;
    }

    seperator_index = get_index(num, seperator);

    if(seperator_index <= 0)
    {
        printf("ERROR: Please provide the complex number in the right format.\n");
        ret.isAssigned = 0;
        return ret;
    }

    strncpy(num1, num, seperator_index);
    strcpy(num2, num + seperator_index + 1);

    ret.real = atof(num);
    ret.imaginary = atof(num2);
    ret.isAssigned = 1;

    return ret;
}

output_vars calculate_output_vars(complex_number num)
{
    output_vars o_vars;

    o_vars.phi =  atan(num.imaginary / num.real);
    o_vars.phi_cos = cos(o_vars.phi);
    o_vars.phi_sin = sin(o_vars.phi);
    o_vars.r =  sqrt(pow(num.real, 2) + pow(num.imaginary, 2));

    return o_vars;
}

int get_index(char* string, char c) {
    char *e = strchr(string, c);

    return (e == NULL ? -1 : e - string);
}