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


int main(int argc, char *argv[])
{
	int c;
	char szVariableName[256];
	unsigned long value;
	char *pszTok;
	while ((c = getopt(argc, argv, "dv:1qr:w:s:R:g:xlfS")) != -1) {
		switch (c) {
			case 'w':
							pszTok = strtok(optarg, ",");
							if (pszTok != NULL) {
								strncpy(szVariableName, pszTok, sizeof(szVariableName));
								pszTok = strtok(NULL, ",");
								if (pszTok != NULL) {
									value = strtol(pszTok, NULL, 10);
									printf("hello %d , %s",value,szVariableName);
									writeVariableValue(szVariableName, value);
									return 0;
								}
							}
					break;
					}
	}
}
