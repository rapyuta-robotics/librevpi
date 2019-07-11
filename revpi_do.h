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

void revpi_set_do(int pin_number, uint32_t i32uValue)
{
		char pszVariableName[10];
		snprintf(pszVariableName, 10, "O_%d", pin_number); 	
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
		} else if (sPiVariable.i16uLength == 8) {
				i8uValue = i32uValue;
				rc = piControlWrite(sPiVariable.i16uAddress, 1, (uint8_t *) & i8uValue);

		} else if (sPiVariable.i16uLength == 16) {
				i16uValue = i32uValue;
				rc = piControlWrite(sPiVariable.i16uAddress, 2, (uint8_t *) & i16uValue);

		} else if (sPiVariable.i16uLength == 32) {
				rc = piControlWrite(sPiVariable.i16uAddress, 4, (uint8_t *) & i32uValue);
		}
}
