/*
OVERVIEW: You are given 2 bank statements that are ordered by date. Write a function that returns dates common to both statements
(ie both statements have transactions in these dates).
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
B[3] = { { 10, "09-10-2003", "First" }, { 220, "18-01-2010", "Sixth" }, { 320, "27-08-2015", "Seventh" } };
Output: { { 10, "09-10-2003", "First" } }

INPUTS: Two bank statements (array of transactions).

OUTPUT: Transactions having same dates.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

#include <iostream>

struct transaction {
	int amount;
	char date[11];
	char description[20];
};

int leap(int y)
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
int formatValidate(char *date)
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
int validate(int day, int mon, int year)
{
	int flag = 0;
	if (mon<1 || mon>12)flag++;
	if ((mon == 1 || mon == 3 || mon == 5 || mon == 7 || mon == 8 || mon == 10 || mon == 12) && day>31)flag++;
	else if (mon == 2 && !(leap(year)) && day>28)flag++;
	else if (mon == 2 && leap(year) && day>29)flag++;
	else if ((mon == 4 || mon == 6 || mon == 9 || mon == 11) && day>30)flag++;
	if (flag)return 0;
	else return 1;

}
int compare(int num1, int num2)
{
	if (num1<num2)return 1;
	else if (num2 < num1)return 2;
	else return -1;
}

int isOlder(char *date1, char *date2) {
	int year[2], mon[2], day[2], i, ans;
	if (formatValidate(date1) == -1 || formatValidate(date2) == -1)return -1;
	day[0] = (date1[0] - 48) * 10 + (date1[1] - 48);
	mon[0] = (date1[3] - 48) * 10 + (date1[4] - 48);
	year[0] = (date1[6] - 48) * 1000 + (date1[7] - 48) * 100 + (date1[8] - 48) * 10 + (date1[9] - 48);

	day[1] = (date2[0] - 48) * 10 + (date2[1] - 48);
	mon[1] = (date2[3] - 48) * 10 + (date2[4] - 48);
	year[1] = (date2[6] - 48) * 1000 + (date2[7] - 48) * 100 + (date2[8] - 48) * 10 + (date2[9] - 48);
	if (!validate(day[0], mon[0], year[0]))return -1;
	if (!validate(day[1], mon[1], year[1]))return -1;
	ans = compare(year[0], year[1]);
	if (ans != -1)return ans;
	else
	{
		ans = compare(mon[0], mon[1]);
		if (ans != -1)return ans;
		else
		{
			ans = compare(day[0], day[1]);
			if (ans != -1)return ans;
			return 0;
		}
	}
}
struct transaction * sortedArraysCommonElements(struct transaction *A, int ALen, struct transaction *B, int BLen)
{
	if(A==NULL || B==NULL || ALen <=0 ||BLen<=0 ) return NULL;
	int *dateNumA, *dateNumB, day[2] = { 0, 0 }, month[2] = { 0, 0 }, year[2] = { 0, 0 }, size;
	struct transaction *common;
	if (ALen < BLen) size = BLen;
	else size = ALen;
	common = (struct transaction *)malloc((size + 10)* sizeof(struct transaction));
	int i = 0, j = 0, k = 0, cmp;
	while (i < ALen && j < BLen)
	{
		cmp = isOlder(A[i].date, B[j].date);
		if (cmp == -1) return NULL;
		if (cmp == 1)i++;
		else if (cmp == 2)j++;
		else
		{
			common[k] = A[i];
			i++;
			j++;
			k++;
		}
	}
	if (k == 0) return NULL;
	return common;
}