#include "revpi_do.h"
#include "revpi_di.h"
#include <string.h>

int main()
{
int pin_state;
char pin_number[5];

for (int i=10; i<=16; i++)
{
        printf("------------------------------------------------------");
        printf("\n pin number %d",i);
        pin_number[0] = '\0';
        char output_variable[] = "O_";
        char input_variable[] = "I_";

        sprintf(pin_number,"%d",i);
        strcat(output_variable,pin_number);
        strcat(input_variable,pin_number);

        pin_state = 0;
        writeVariableValue(output_variable,pin_state);
        sleep(1);
        printf("\n Set value %d on pin O_%d \n", pin_state,i);
        readVariableValue(input_variable,&pin_state);
        sleep(1);
        printf(" Read value %d from pin I_%d \n", pin_state,i);
        (pin_state ==0) ? printf(" \n success \n") : printf(" \n failure \n");
 
        pin_state = 1;
        writeVariableValue(output_variable,pin_state);
        sleep(1);
        printf(" Set value %d on pin O_%d \n", pin_state,i);
        readVariableValue(input_variable,&pin_state);
        sleep(1);
        printf(" Read value %d from pin I_%d \n", pin_state,i);
        (pin_state ==1) ? printf(" \n success \n") : printf(" \n failure \n");
}
}