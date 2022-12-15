#include<stdio.h>
#include<string.h>
#include "functions.h"

complex_number addition(complex_number num1, complex_number num2)
{
    complex_number res;

    res.real = num1.real + num1.imaginary;
    res.imaginary = num2.real + num2.imaginary;

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
    const char seperator = '+';
    char* e, num1, num2;
    int seperator_index;

    if(num[0] == seperator)
    {
        printf("ERROR: Please ignore the mathematical operator (+) for your number.\n");
        return;
    }

    e = strchr(num, seperator);
    printf("%i\n", e);

    if(e == NULL)
    {
        printf("ERROR: Please provide the complex number in the right format.\n");
        return;
    }

    seperator_index = (int)(e - num);
    printf("%f\n", seperator_index);

    //num1[seperator_index + 1];
    strncpy(num1, num, seperator_index);
    
    //num2[strlen(num) - seperator_index];
    strcpy(num2, num + seperator_index + 1);

    ret.real = strtod(num1, NULL);
    ret.imaginary = strtod(num2, NULL);

    printf("%i\n", strtod(num1, NULL));
    printf("%i\n", strtod(num2, NULL));

    return ret;
}

double calculate_phi(complex_number num)
{
    return atan(num.imaginary / num.real);
}

double calculate_r(complex_number num)
{
    return sqrt(pow(num.real, 2) + pow(num.imaginary, 2));
}