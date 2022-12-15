#include<stdio.h>
#include<string.h>
#include<math.h>
#include "functions.h"

 // gcc calculator.c functions.c -Wall -o main.exe
 // ./main.exe
int main()
{
    char str_num1[256], str_num2[256];
    complex_number cn_num1, cn_num2, result;
    char math_operation, res_format;
    double r, phi, phi_cos, phi_sin;

    printf("-----------------------------------------------------------------------\n");
    printf("This programm handles mathematical operations with two complex numbers.\n");
    printf("-----------------------------------------------------------------------\n\n");

    printf("Enter the first complex number (a+bi):\n");
    printf("answer: ");
    scanf("%s", &str_num1);

    //cn_num1 = convert_str_to_complex_number(str_num1);
    sscanf(str_num1, "%lf + %lfi", &cn_num1.real, &cn_num1.imaginary);
    
    printf("\nEnter the second complex number (a+bi):\n");
    printf("answer: ");
    scanf("%s", &str_num2);

    //cn_num2 = convert_str_to_complex_number(str_num2);
    sscanf(str_num2, "%lf+%lfi", &cn_num2.real, &cn_num2.imaginary);

    printf("\nWhich operation you would like to do?\n");
    printf("+: addition\n");
    printf("-: subtraction\n");
    printf("*: multiply\n");
    printf("/: division\n");

    printf("answer: ");
    scanf("%s", &math_operation);

    switch (math_operation)
    {
    case '+':
        result = addition(cn_num1, cn_num2);
        break;
    case '-':
        result = subtraction(cn_num1, cn_num2);
        break;
    case '/':
        result = division(cn_num1, cn_num2);
        break;
    case '*':
        result = multiply(cn_num1, cn_num2);
        break;
    
    default:
        printf("ERROR: unsupported operation.\n");
        return -1;
        break;
    }

    printf("\nWhich result format do you like?\n");
    printf("a: cartesian: z = a + bi\n");
    printf("b: polar 1: z = r * e(i * phi)\n");
    printf("c: Polar 2: z = r * (cos(phi) + i * sin(phi))\n");

    printf("answer: ");
    scanf("%s", &res_format);
    printf("\n");

    phi = calculate_phi(result);
    phi_cos = cos(phi);
    phi_sin = sin(phi);
    r = calculate_r(result);

    switch (res_format)
    {
    case 'a':
        printf("result: %f + %fi\n", result.real, result.imaginary);
        break;
    case 'b':
        printf("result: %f + e^(i * %f)\n", r, phi);
        break;
    case 'c':
        printf("result: %f + (%f + i * %f)\n", r, phi_sin, phi_cos);
        break;
    
    default:
        printf("ERROR: unsupported format.\n");
        return -1;
        break;
    }

    return 1;
}
