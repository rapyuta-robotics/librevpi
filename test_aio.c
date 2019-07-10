#include "revpi_do.h"
#include "revpi_di.h"
#include <string.h>
#include <stdio.h>

int main()
{
int voltage;
char pin_number[10];
for (int i=1; i<=4; i++)
{
        char input_variable[] = "InputValue_";
        sprintf(pin_number,"%d",i);
        strcat(input_variable,pin_number);
        readVariableValue(input_variable,&voltage);
        printf("\n voltage of %s : %d \n", input_variable, voltage );
}
}










