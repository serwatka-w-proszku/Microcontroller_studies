#include "watchdog.h"

struct Watch sWatch;

void WatchUpdate(void){
	sWatch.ucSeconds ++;
	if(sWatch.ucSeconds == 60){
		sWatch.ucMinutes ++;
		sWatch.fMinutesValueChanged = 1;
		sWatch.ucSeconds = 0;
	}
	sWatch.fSecondsValueChanged = 1;
}
