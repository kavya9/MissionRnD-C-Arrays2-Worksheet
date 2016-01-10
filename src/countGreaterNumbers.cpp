/*
OVERVIEW: You are given a bank statement where transactions are ordered by date. Write a function that finds the number of transactions in that statement after a given date.
-- find the count of numbers greater than a given number in a sorted array.
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
date = "19-10-2004"
Output: 1 (as there is only one transaction { 30, "03-03-2005", "Third" })

INPUTS: One bank statement (array of transactions) and date.

OUTPUT: Return the number of transactions in that statement after a given date.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

struct transaction {
	int amount;
	char date[11];
	char description[20];
};
int leap1(int y)
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
int * validate(char *date)
{
	int i,dateNum[11];
	for (i = 0; i < 10; i++)
	{
		if (i == 2 || i == 5)
		{
			if (date[i] != '-')return '\0';
		}
		else
		{
			if ((date[i]<'0' || date[i]>'9') || (date[i]<'0' || date[i]>'9'))return '\0';
		}
		dateNum[i] = date[i] - 48;
	}
	return dateNum;
}

int dateValidate(int day, int mon, int year)
{
int flag = 0;
if (mon<1 || mon>12)flag++;
if ((mon == 1 || mon == 3 || mon == 5 || mon == 7 || mon == 8 || mon == 10 || mon == 12) && day>31)flag++;
else if (mon == 2 && !(leap1(year)) && day>28)flag++;
else if (mon == 2 && leap1(year) && day>29)flag++;
else if ((mon == 4 || mon == 6 || mon == 9 || mon == 11) && day>30)flag++;
if (flag)return 0;
else return 1;

}
int countGreaterNumbers(struct transaction *Arr, int len, char *date) {
	if (Arr=='\0' || len<=0 || date=='\0' )return '\0';
	int i, j, day[2] = { 0, 0 }, month[2] = { 0, 0 }, year[2] = { 0, 0 }, transactions = 0 ,ans,*dateNum;
	struct transaction trans;
	dateNum = validate(date);
	if (dateNum != '\0')
	{
		day[0] = dateNum[0] * 10 + dateNum[1];
		month[0] = dateNum[3] * 10 + dateNum[4];
		year[0] = dateNum[6] * 1000 + dateNum[7] * 100 + dateNum[8] * 10 + dateNum[9];
		if (!dateValidate(day[0], month[0], year[0])) return '\0';
		for (i = 0; i < len; i++)
		{
			day[1] = 0, month[1] = 0, year[1] = 0;
			dateNum = validate(Arr[i].date);
			if (dateNum != '\0')
			{
				day[1] = dateNum[0] * 10 + dateNum[1];
				month[1] = dateNum[3] * 10 + dateNum[4];
				year[1] = dateNum[6] * 1000 + dateNum[7] * 100 + dateNum[8] * 10 + dateNum[9];
				if (!dateValidate(day[1], month[1], year[1])) return '\0';
				if (year[0] < year[1]) transactions++;
				else if (year[0] == year[1])
				{
					if (month[0] < month[1]) transactions++;
					else if (month[0] == month[1])
					{
						if (day[0] < day[1]) transactions++;
					}
				}
			}
		}

		return transactions;
	}
	return '\0';
}


