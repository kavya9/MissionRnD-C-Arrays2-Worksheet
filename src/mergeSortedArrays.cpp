/*
OVERVIEW: You are given 2 bank statements that are ordered by date - Write a function that produces a single merged statement ordered by dates.
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
B[2] = { { 10, "09-10-2003", "First" }, { 220, "18-01-2010", "Sixth" } };
Output: { { 10, "09-10-2003", "First" }, { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" },  30, "03-03-2005", "Third" }, { 220, "18-01-2010", "Sixth" } }

INPUTS: Two bank statements (array of transactions).

OUTPUT: Combined statement ordered by transaction date.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

#include <iostream>

struct transaction {
	int amount;
	char date[11];
	char description[20];
};

int leap2(int y)
{
	if (y % 4 == 0)
	{
		if (y % 100 != 0)return 1;
		else if (y % 100 == 0)
		{
			if (y % 400 == 0)return 1;
			else return 0;
		}
	}
	else return 0;
}
int formatValidate2(char *date)
{
	int i;
	for (i = 0; i < 10; i++)
	{
		if (i == 2 || i == 5)
		{
			if (date[i] != '-')return -1;
		}
		else
		{
			if (date[i]<'0' || date[i]>'9')return -1;
		}
	}
	return 1;
}
int validate2(int day, int mon, int year)
{
	int flag = 0;
	if (mon<1 || mon>12)flag++;
	if ((mon == 1 || mon == 3 || mon == 5 || mon == 7 || mon == 8 || mon == 10 || mon == 12) && day>31)flag++;
	else if (mon == 2 && !(leap2(year)) && day>28)flag++;
	else if (mon == 2 && leap2(year) && day>29)flag++;
	else if ((mon == 4 || mon == 6 || mon == 9 || mon == 11) && day>30)flag++;
	if (flag)return 0;
	else return 1;

}
int compare2(int num1, int num2)
{
	if (num1<num2)return 1;
	else if (num2 < num1)return 2;
	else return -1;
}

int isOlder2(char *date1, char *date2) {
	int year[2], mon[2], day[2], i, ans;
	if (formatValidate2(date1) == -1 || formatValidate2(date2) == -1)return -1;
	day[0] = (date1[0] - 48) * 10 + (date1[1] - 48);
	mon[0] = (date1[3] - 48) * 10 + (date1[4] - 48);
	year[0] = (date1[6] - 48) * 1000 + (date1[7] - 48) * 100 + (date1[8] - 48) * 10 + (date1[9] - 48);

	day[1] = (date2[0] - 48) * 10 + (date2[1] - 48);
	mon[1] = (date2[3] - 48) * 10 + (date2[4] - 48);
	year[1] = (date2[6] - 48) * 1000 + (date2[7] - 48) * 100 + (date2[8] - 48) * 10 + (date2[9] - 48);
	if (!validate2(day[0], mon[0], year[0]))return -1;
	if (!validate2(day[1], mon[1], year[1]))return -1;
	ans = compare2(year[0], year[1]);
	if (ans != -1)return ans;
	else
	{
		ans = compare2(mon[0], mon[1]);
		if (ans != -1)return ans;
		else
		{
			ans = compare2(day[0], day[1]);
			if (ans != -1)return ans;
			return 0;
		}
	}
}

struct transaction * mergeSortedArrays(struct transaction *A, int ALen, struct transaction *B, int BLen) {
	if (A == NULL || B == NULL || ALen <= 0 || BLen <= 0) return NULL;
	struct transaction *merged = (struct transaction *)malloc((ALen + BLen)*sizeof(struct transaction));
	int i = 0, j = 0, k = 0,cmp;
	while (i < ALen && j < BLen)
	{
		cmp = isOlder2(A[i].date, B[j].date);
		if (cmp == -1)return NULL;
		else if (cmp == 1)
		{
			merged[k] = A[i]; i++; 
		}
		else if (cmp == 2)
		{
			merged[k] = B[j]; j++; 
		}
		else
		{
			merged[k] = A[i];
			k++;
			merged[k] = A[i];
			i++;
			j++;
		}
		k++;
	}
	while (i < ALen)
	{
		merged[k] = A[i];
		k++;
		i++;
	}
	while (j < BLen)
	{
		merged[k] = B[j];
		k++;
		j++;
	}
	return merged;
}