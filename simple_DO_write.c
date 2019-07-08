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

void writeVariableValue(char *pszVariableName, uint32_t i32uValue)
{
        int rc;
        SPIVariable sPiVariable;
        SPIValue sPIValue;
        uint8_t i8uValue;
        uint16_t i16uValue;

        strncpy(sPiVariable.strVarName, pszVariableName, sizeof(sPiVariable.strVarName));
        rc = piControlGetVariableInfo(&sPiVariable);
        if (sPiVariable.i16uLength == 1) {
                sPIValue.i16uAddress = sPiVariable.i16uAddress;
                sPIValue.i8uBit = sPiVariable.i8uBit;
                sPIValue.i8uValue = i32uValue;
                rc = piControlSetBitValue(&sPIValue);
}
}

int main(int argc, char *argv[])
{
                int value = 0;
                writeVariableValue("O_1",value);

}
