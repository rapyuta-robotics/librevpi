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

int revpi_get_di(int pin_number)
{
		char pszVariableName[10];
		snprintf(pszVariableName, 10, "I_%d", pin_number); 
		bool cyclic = true;
		bool quiet = false;
		int rc;
		SPIVariable sPiVariable;
		SPIValue sPIValue;
		uint8_t i8uValue;
		uint16_t i16uValue;
		uint32_t i32uValue;

		strncpy(sPiVariable.strVarName, pszVariableName, sizeof(sPiVariable.strVarName));
		rc = piControlGetVariableInfo(&sPiVariable);
		if (rc < 0) {
				printf("Cannot find variable '%s'\n", pszVariableName);
		}
		if (sPiVariable.i16uLength == 1) {
				sPIValue.i16uAddress = sPiVariable.i16uAddress;
				sPIValue.i8uBit = sPiVariable.i8uBit;
				rc = piControlGetBitValue(&sPIValue);
				if (rc < 0)
						printf("Get bit error\n");
				else 
						return(sPIValue.i8uValue);
		} 

		else if (sPiVariable.i16uLength == 8) {
				rc = piControlRead(sPiVariable.i16uAddress, 1, (uint8_t *) & i8uValue);
				if (rc < 0)
						printf("Read error\n");
				else 
						return(i8uValue);
		}

		else if (sPiVariable.i16uLength == 16) {
				rc = piControlRead(sPiVariable.i16uAddress, 2, (uint8_t *) & i16uValue);
				if (rc < 0)
						printf("Read error\n");
				else 
						return(i16uValue);
		} 

		else if (sPiVariable.i16uLength == 32) {
				rc = piControlRead(sPiVariable.i16uAddress, 4, (uint8_t *) & i32uValue);
				if (rc < 0)
						printf("Read error\n");
				else       
						return(i32uValue);
		}
		else
				printf("Could not read variable %s. Internal Error\n", pszVariableName);
}






