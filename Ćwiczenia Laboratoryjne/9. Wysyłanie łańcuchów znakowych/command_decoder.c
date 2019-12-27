#include "string.h"
#include "command_decoder.h"

#define MAX_KEYWORD_NR 4
#define NULL 0
#define SEPARATOR ' '


//	variables

struct Keyword asKeywordList[MAX_KEYWORD_NR] = {
	{ CALCULATE, "calc" },
	{ ID,        "id"   },
	{ CALIBRATION, "callib" },
	{ GOTO, "goto" },
};

struct Token asToken[MAX_TOKEN_NR];

unsigned char ucTokenNr;


// Functions

unsigned char ucFindTokensInString(char *pcString){
	
	unsigned char ucCharCounter, ucCurrentChar, ucTokenNr = 0;
	enum DecodeState eDecodeState = DELIMITER;
	
	for (ucCharCounter = 0;;ucCharCounter++){
		ucCurrentChar = pcString[ucCharCounter];

		switch (eDecodeState){
			case TOKEN:
				if (NULL == ucCurrentChar){
					return ucTokenNr;
				}
				else if (SEPARATOR == ucCurrentChar){
					eDecodeState = DELIMITER;
				}
				break;
			case DELIMITER :
				if (NULL == ucCurrentChar){
					return ucTokenNr;
				}
				else if (SEPARATOR != ucCurrentChar){
					asToken[ucTokenNr].uValue.pcString = &pcString[ucCharCounter];
					eDecodeState = TOKEN;
					ucTokenNr++;
				}
				break;
		}
	}
}

enum Result eStringToKeyword(char pcStr[],enum KeywordCode *peKeywordCode){
	
	unsigned char ucKeywordCounter;
	enum CompResult eCompResult;

	for (ucKeywordCounter = 0; ucKeywordCounter < MAX_KEYWORD_NR; ucKeywordCounter++){
		eCompResult = eCompareString(asKeywordList[ucKeywordCounter].cString, pcStr);
		if (eCompResult == EQUAL) {
			*peKeywordCode = asKeywordList[ucKeywordCounter].eCode;
			return OK;
		}
	}
	return ERROR;
}

void DecodeTokens(void){
	
	char cTokenCounter, *pcString;
	struct Token *sCurrentToken;

	for (cTokenCounter = 0; cTokenCounter < ucTokenNr; cTokenCounter++){
		sCurrentToken = &asToken[cTokenCounter];
		pcString = asToken[cTokenCounter].uValue.pcString;
		if (OK == eStringToKeyword(pcString, &(*sCurrentToken).uValue.eKeyword)){
			sCurrentToken->eType = KEYWORD;
		}
		else if (OK == eHexStringToUInt(pcString, &(*sCurrentToken).uValue.uiNumber)){
			sCurrentToken->eType = NUMBER;
		}
		else{
			sCurrentToken->eType = STRING;
		}
	}
}

void DecodeMsg(char *pcString){
	
	ucTokenNr = ucFindTokensInString(pcString);
	ReplaceCharactersInString(pcString, SEPARATOR, NULL);
	DecodeTokens();
}
