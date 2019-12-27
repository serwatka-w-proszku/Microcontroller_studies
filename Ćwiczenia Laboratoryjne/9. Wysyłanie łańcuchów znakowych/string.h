enum Result{ OK, ERROR };
enum CompResult { DIFFERENT, EQUAL };

//void AppendString (char [],char []);
void CopyString(char [], char []);
//void UIntToHexStr(unsigned int, char []);
void AppendUIntToString(unsigned int, char []);
enum Result eHexStringToUInt(char [], unsigned int *);
enum CompResult eCompareString(char [], char *);
void ReplaceCharactersInString(char [], char, char);
