struct Watch {
	unsigned char ucMinutes, ucSeconds;
	unsigned char fSecondsValueChanged, fMinutesValueChanged;
};

extern struct Watch sWatch;

void WatchUpdate(void);
