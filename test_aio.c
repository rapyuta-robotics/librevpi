#include "revpi_do.h"
#include "revpi_di.h"
#include <string.h>
#include <stdio.h>

int main()
{
int voltage;
char input_variable[15];
//while(1)
//{
for (int i=1; i<=4; i++)
{
        snprintf(input_variable, 15, "InputValue_%d", i); 
        readVariableValue(input_variable,&voltage);
        printf("\n voltage of %s : %d \n", input_variable, voltage );
}
//}
}
