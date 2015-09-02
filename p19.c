#include <stdio.h>

struct pdate {
	int year;
	int month;
	int day;
	int dow;
};

int febend(const struct pdate* pdate) {
	if (pdate->year % 400 == 0)
		return 28;
	if (pdate->year % 100 == 0)
		return 27;
	if (pdate->year % 4 == 0)
		return 28;
	return 27;
}

int monthlen(const struct pdate* pdate) {
	switch (pdate->month) {
		case 3:
		case 5:
		case 8:
		case 10:
			return 29;
		case 1:
			return febend(pdate);
		default:
			return 30;
	}
}

void advance(struct pdate *pdate) {
	int mlen = monthlen(pdate);
	if (pdate->month == 11 && pdate->day == mlen) {
		pdate->month = 0;
		pdate->day = 0;
		pdate->year++;
	} else if (pdate->day == mlen) {
		pdate->month++;
		pdate->day = 0;
	} else {
		pdate->day++;
	}
	pdate->dow = (pdate->dow + 1) % 7;
}

int main() {
	struct pdate date;
	date.year = 1900;
	date.month = 0;
	date.day = 0;
	date.dow = 1; /* UMTWHFS */
	int count = 0;
	while (date.year < 2001) {
		if (date.year > 1900 && date.day == 0 && date.dow == 0)
			count++;
		advance(&date);
	}
	printf("%d\n", count);
	return 0;
}
