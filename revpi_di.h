#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <termios.h>
#include <getopt.h>
#include <time.h>
#include <sys/types.h>
#include <stdbool.h>
#include "piControlIf.h"
#include "piControl.h"
void readVariableValue(char *pszVariableName,int *pin_state )
{
        int rc;
        SPIVariable sPiVariable;
        SPIValue sPIValue;
        uint8_t i8uValue;
        strncpy(sPiVariable.strVarName, pszVariableName, sizeof(sPiVariable.strVarName));
        rc = piControlGetVariableInfo(&sPiVariable);
        sPIValue.i16uAddress = sPiVariable.i16uAddress;
        sPIValue.i8uBit = sPiVariable.i8uBit;
        rc = piControlGetBitValue(&sPIValue);
        *pin_state  = sPIValue.i8uValue;
}

