#include "calc.h"

// Reverse Polish calculator
int main()
{
    int type;
    double op1[2];
    double op2[2];
    char s[MAXOP];

    while ((type = getop(s)) != EOF)
    {
        switch(type)
        {
            case (int)RAW:
                op1[0] = atof(s);
                op1[1] = RAW;
                push(op1);
                break;
            case (int)VAR:
                op1[0] = s[0];
                op1[1] = VAR;
                push(op1);
                break;                
            case '+':
                pop(op2);
                pop(op1);
                add(op1, op2);
                break;
            case '*':
                pop(op2);
                pop(op1);
                multiply(op1, op2);
                break;
            case '-':
                pop(op2);
                pop(op1);
                subtract(op1, op2);
                break;
            case '/':
                pop(op2);
                pop(op1);
                divide(op1, op2);
               break;
            case '%':
                pop(op2);
                pop(op1);
                modulus(op1, op2);
                break;
            case '=':
                pop(op2);
                pop(op1);
                assign(op1, op2);
                break;            
            case '\n':
                pop(op1);
                printf("\t%.8f\n", op1[0]);
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}
