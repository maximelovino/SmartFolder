#include "Parser.h"

int isValidPath(char *path) {
	static regex_t regex;
	static int compiled;
	if (!compiled) {
		if (regcomp(&regex, FILE_PATH_REGEX, 0)) {
			logMessage(2, "Couldn't compile the regexp to check validity of folder");
			return -1;
		} else {
			compiled = 1;
		}
	}
	return regexec(&regex, path, 0, NULL, 0);
}

struct timespec *getTimeSpec(char *date) {
	int step = 0;
	struct timespec *t = malloc(sizeof(struct timespec));
	if (step == 0) {
		char year[5];
		strncpy(year, date, 4);
		int yyyy = atoi(year);
		t->tv_sec = (yyyy - 1970) * SECONDS_IN_YEAR;
		step++;
	} else if (step == 1) {
		char month[3];
		strncpy(month, &(date[6]), 2);
		int mm = atoi(month);
		t->tv_sec += (mm - 1) * SECONDS_IN_MONTH;
		step++;
	} else if (step == 2) {
		char day[3];
		strncpy(day, &(date[10]), 2);
		int dd = atoi(day);
		t->tv_sec += (dd - 1) * SECONDS_IN_DAY;
	}
	return t;
}

searchType getSearchType(char *param, char *arg) {
	if (strcmp(param, "--name") == 0) {
		return NAME;
	} else if (strcmp(param, "--size") == 0) {
		if (arg[0] == '+')
			return SIZE_BIGGER;
		else if (arg[0] == '-')
			return SIZE_SMALLER;
		else
			return SIZE_EQUAL;
	} else if (strcmp(param, "--dateStatus") == 0) {
		if (arg[0] == '+')
			return STATUS_DATE_A;
		else if (arg[0] == '-')
			return STATUS_DATE_B;
		else
			return STATUS_DATE_E;
	} else if (strcmp(param, "--dateModified") == 0) {
		if (arg[0] == '+')
			return MODIF_DATE_A;
		else if (arg[0] == '-')
			return MODIF_DATE_B;
		else
			return MODIF_DATE_E;
	} else if (strcmp(param, "--dateUsed") == 0) {
		if (arg[0] == '+')
			return USAGE_DATE_A;
		else if (arg[0] == '-')
			return USAGE_DATE_B;
		else
			return USAGE_DATE_E;
	} else if (strcmp(param, "--uid") == 0) {
		return OWNER;
	} else if (strcmp(param, "--gid") == 0) {
		return GROUP;
	} else if (strcmp(param, "--perms") == 0) {
		return MODE;
	}
	return -1;
}


int isBooleanOp(char *word) {
	return (strcmp(word, "and") & strcmp(word, "AND") & strcmp(word, "or") & strcmp(word, "OR") & strcmp(word, "not") &
			strcmp(word, "NOT") & strcmp(word, "xor") & strcmp(word, "XOR")) == 0;
}

int isValidSearch(searchType st, char *arg) {
	if (st == NAME) {
		return 1;
	} else if (st == SIZE_SMALLER || st == SIZE_BIGGER || st == SIZE_EQUAL) {
		int starti = (st != SIZE_EQUAL);
		for (int i = starti; arg[i + 1]; i++) {
			if (!isdigit(arg[i])) {
				return 0;
			}
		}
		return 1;
	} else if (st == STATUS_DATE_B || st == STATUS_DATE_A || st == MODIF_DATE_B || st == MODIF_DATE_A ||
			   st == USAGE_DATE_B || st == USAGE_DATE_A || st == STATUS_DATE_E || st == MODIF_DATE_E ||
			   st == USAGE_DATE_E) {
		int starti = !(st == STATUS_DATE_E || st == MODIF_DATE_E || st == USAGE_DATE_E);
		for (int i = starti; arg[i]; i++) {
			if (i == 4 + starti || i == 7 + starti) {
				//skip separator
				continue;
			}
			if (!isdigit(arg[i])) {
				return 0;
			}
		}
	} else if (st == OWNER || st == GROUP) {
		return 1;
	} else if (st == MODE) {
		if (strlen(arg) == 3) {
			for (int i = 0; arg[i]; i++) {
				if (!isdigit(arg[i])) {
					return 0;
				}
			}
		}
		return 1;
	}
	return 0;
}

int evaluateAndSearch(char **expression, int exprLen, char *folder, List **result) {
	Stack *s = initStack();
	for (int i = 0; i < exprLen; i += 2) {
		char *p1 = expression[i];
		if (!isBooleanOp(p1)) {
			searchType st = getSearchType(p1, expression[i + 1]);
			if (isValidSearch(st, expression[i + 1])) {
				void *op1 = prepareArgument(st, expression[i + 1]);
				logMessage(0, "In evaluate ans search %s", folder);
				List *l1 = searchDirectory(folder, st, op1);
				push(s, l1);
			} else {
				return -1;
			}

		} else {
			List *l1 = pop(s);
			List *l2 = NULL;
			List *l3 = NULL;
			if (strcmp(p1, "and") == 0 || strcmp(p1, "AND") == 0) {
				l2 = pop(s);
				l3 = listIntersect(l1, l2);
			} else if (strcmp(p1, "or") == 0 || strcmp(p1, "OR") == 0) {
				l2 = pop(s);
				l3 = listUnion(l1, l2);
			} else if (strcmp(p1, "xor") == 0 || strcmp(p1, "XOR") == 0) {
				l2 = pop(s);
				l3 = listXOR(l1, l2);
			} else if (strcmp(p1, "not") == 0 || strcmp(p1, "NOT") == 0) {
				l2 = searchDirectory(folder, -1, NULL);
				l3 = listComplement(l2, l1);
			}
			deleteList(l1);
			deleteList(l2);
			push(s, l3);
			i--;
		}
	}
	*(result) = pop(s);
	deleteStack(s);
	return 0;
}

void *prepareArgument(searchType st, char *arg) {
	arg = trimArgument(st, arg);
	logMessage(0, arg);
	int *size = malloc(sizeof(int));

	switch (st) {
		case STATUS_DATE_A:
		case STATUS_DATE_B:
		case STATUS_DATE_E:
		case MODIF_DATE_A:
		case MODIF_DATE_B:
		case MODIF_DATE_E:
		case USAGE_DATE_A:
		case USAGE_DATE_B:
		case USAGE_DATE_E:
			return getTimeSpec(arg);
		case OWNER:
			return sgetpwuid(arg);
		case GROUP:
			return sgetgrgid(arg);
		case SIZE_BIGGER:
		case SIZE_EQUAL:
		case SIZE_SMALLER:
			*size = getSize(arg);
			logMessage(0, "size is %i", *size);
			return size;
		case MODE:
			//TODO
			return NULL;
		case NAME:
			return arg;
	}
}


int getSize(char *sizeAsString) {
	logMessage(0, "Hello %s", sizeAsString);
	char unit = sizeAsString[strlen(sizeAsString) - 1];
	if (unit >= '0' && unit <= '9') {
		return atoi(sizeAsString);
	}
	char subSize[1024];
	strncpy(subSize, sizeAsString, strlen(sizeAsString) - 1);
	subSize[strlen(sizeAsString) - 1] = 0;
	logMessage(0, "Size before unit %s, unit is %c", subSize, unit);
	int size = atoi(subSize);
	//TODO take string without last and atoi
	switch (unit) {
		case 'K':
			return size * 1024;
		case 'M':
			return size * 1024 * 1024;
		case 'G':
			return size * 1024 * 1024 * 1024;
		case 'T':
			return size * 1024 * 1024 * 1024 * 1024;
		default:
			logMessage(2, "Can't recognise unit of size");
			_exit(1);
	}
}

char *trimArgument(searchType st, char *arg) {
	if (st == SIZE_BIGGER || st == SIZE_SMALLER || st == STATUS_DATE_B || st == STATUS_DATE_A || st == MODIF_DATE_B ||
		st == MODIF_DATE_A || st == USAGE_DATE_B || st == USAGE_DATE_A) {
		int s = strlen(arg);
		char *narg = malloc(s);
		strcpy(narg, &arg[1]);
		return narg;
	}
	return arg;
}
