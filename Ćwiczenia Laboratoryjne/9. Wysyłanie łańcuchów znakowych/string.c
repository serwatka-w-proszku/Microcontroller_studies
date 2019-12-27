#include "string.h"

#define NULL 0




void CopyString(char pcSource[], char pcDestination[]){
	unsigned char ucCharacterCounter;
	
	for (ucCharacterCounter = 0; NULL != pcSource[ucCharacterCounter]; ucCharacterCounter++){
		pcDestination[ucCharacterCounter] = pcSource[ucCharacterCounter];
	}
	pcDestination[ucCharacterCounter] = NULL;
}

void AppendString (char pcSourceStr[], char pcDestinationStr[]){
	unsigned char ucCharacterCounter;

	for(ucCharacterCounter=0; pcDestinationStr[ucCharacterCounter]!= NULL; ucCharacterCounter ++){}
	CopyString(pcSourceStr, &pcDestinationStr[ucCharacterCounter]);
}

//moze trzeba to wymienic na wersje podstawowa z 2 tablicami
enum CompResult eCompareString(char pcStr1[], char * pcStr2){
	unsigned char ucCharacterCounter;

	for (ucCharacterCounter = 0; pcStr1[ucCharacterCounter] == pcStr2[ucCharacterCounter]; ucCharacterCounter++){
		if (pcStr1[ucCharacterCounter] == NULL){
			return EQUAL;
		}
	}
	return DIFFERENT;
}

/*
|--------------------------------------------------------------------------
|	Function - Replace chars 
|--------------------------------------------------------------------------
*/

void ReplaceCharactersInString(char pcString[], char cOldChar, char cNewChar){
	unsigned char ucCharacterCounter;
	
	for (ucCharacterCounter = 0; NULL != pcString[ucCharacterCounter]; ucCharacterCounter++){
		if (pcString[ucCharacterCounter] == cOldChar){
			pcString[ucCharacterCounter] = cNewChar;
		}
	}
}

/*
|--------------------------------------------------------------------------
|	Function - Convert int to hex
|--------------------------------------------------------------------------
*/

void UIntToHexStr(unsigned int uiValue, char pcStr[]){
	unsigned char ucNibbleCounter, ucCurrentNibble;

	pcStr[0] = '0';
	pcStr[1] = 'x';
	pcStr[6] = NULL;
	for (ucNibbleCounter = 0; ucNibbleCounter < 4; ucNibbleCounter++){
		ucCurrentNibble = ((uiValue >> (4 * ucNibbleCounter)) & 0x000F);
		if (ucCurrentNibble > 9){
			pcStr[5 - ucNibbleCounter] = ucCurrentNibble + 'A' - 10;
		}
		else{
			pcStr[5 - ucNibbleCounter] = ucCurrentNibble + '0';
		}
	}
}

void AppendUIntToString(unsigned int uiValue, char pcDestinationStr[]){
	unsigned char ucCharacterCounter;

	for (ucCharacterCounter = 0; NULL != pcDestinationStr[ucCharacterCounter]; ucCharacterCounter++){}
	UIntToHexStr(uiValue, &pcDestinationStr[ucCharacterCounter]);
}
/*
|--------------------------------------------------------------------------
|	Function - Convert hex to int
|--------------------------------------------------------------------------
*/

enum Result eHexStringToUInt(char pcStr[], unsigned int *puiValue){
	unsigned char ucCharCounter, ucCurrentChar;

	if (('0' != pcStr[0]) || ('x' != pcStr[1]) || (NULL == pcStr[2])){
		return ERROR;
	}
	*puiValue = 0;
	for (ucCharCounter = 2; pcStr[ucCharCounter] != NULL; ucCharCounter++){
		if (6 == ucCharCounter){
			return ERROR;
		}
		ucCurrentChar = pcStr[ucCharCounter];
		*puiValue = (*puiValue << 4) + ucCurrentChar;
		if (ucCurrentChar < 'A'){
			*puiValue = *puiValue - '0';
		}
		else{
			*puiValue = *puiValue - 'A' + 10;
		}
	}
	return OK;
}
