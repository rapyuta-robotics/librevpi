#include "revpi_do.h"
#include "revpi_di.h"
#include <string.h>

int main()
{
int pin_state;
char output_variable[10];
char input_variable[10];

for (int i=1; i<=16; i++)
{
        printf("------------------------------------------------------");
        printf("\n pin number %d",i);

        snprintf(output_variable, 10, "O_%d", i); 
        snprintf(input_variable, 10, "I_%d", i); 

        pin_state = 0;
        writeVariableValue(output_variable,pin_state);
        sleep(1);
        printf("\n Set value %d on pin %s \n", pin_state,output_variable);
        readVariableValue(input_variable,&pin_state);
        sleep(1);
        printf(" Read value %d from pin %s \n", pin_state,input_variable);
        (pin_state ==0) ? printf(" \n success \n") : printf(" \n failure \n");

        pin_state = 1;
        writeVariableValue(output_variable,pin_state);
        sleep(1);
        printf(" Set value %d on pin %s \n", pin_state,output_variable);
        readVariableValue(input_variable,&pin_state);
        sleep(1);
        printf(" Read value %d from pin %s \n", pin_state,input_variable);
        (pin_state ==1) ? printf(" \n success \n") : printf(" \n failure \n");

}
}
