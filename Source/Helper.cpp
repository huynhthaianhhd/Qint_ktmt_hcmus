#include "Helper.h"

bool turnOnBit(int & a, int index)
{
	if (index<0 || index>BIT_PER_INT - 1)
		return false;
	else
	{
		a |= (1 << index);
		return true;
	}
}

bool turnOffBit(int & a, int index)
{
	if (index<0 || index>BIT_PER_INT - 1)
		return false;
	else
	{
		a &= ~(1 << index);
		return true;
	}
}

bool getBitFromInt(int & a, int index)
{
	if (index<0 || index>BIT_PER_INT - 1)
		return false;
	else
		return (a >> index) & 1;
}