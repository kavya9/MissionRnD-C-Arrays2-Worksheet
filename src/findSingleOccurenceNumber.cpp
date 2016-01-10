/*
OVERVIEW: Given an array where every element occurs three times, except one element which occurs only
once. Find the element that occurs once.
E.g.: Input: arr = 12, 1, 12, 3, 12, 1, 1, 2, 3, 3
ouput: 2

INPUTS: Integer array and length of the array.

OUTPUT: Element that occurs only once.

ERROR CASES: Return -1 for invalid inputs.

NOTES:
*/

int findSingleOccurenceNumber(int *A, int len) {
	if (A == '\0' || len <= 0) return -1;
	int i,element,once=0,twice=0,notThrice;
	for (i = 0; i < len; i++)
	{
		element = A[i];
		twice |= once & element;
		once ^= element;
		notThrice = ~(once & twice);
		once &= notThrice;
		twice &= notThrice;
	}
	return once;
}
	