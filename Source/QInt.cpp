#include "QInt.h"

QInt::QInt()
{
	for (int i = 0; i < 4; i++)
		arrayBits[i] = 0;
}

QInt::QInt(string input, string base) :QInt()
{
	if (base == "2")
		createFromBin(input);
	else if (base == "10")
		createFromDec(input);
	else if (base == "16")
		createFromHex(input);
}

void QInt::createFromBin(string & input)
{
	for (int i = input.length() - 1; i >= 0; i--)
	{
		if (input[i] == '1')
			setBit(input.length() - 1 - i, 1);
	}
}

void QInt::updateFromBin(string & input, QInt & x)
{
	for (int i = input.length() - 1; i >= 0; i--)
	{
		if (input[i] == '1')
			x.setBit(input.length() - 1 - i, 1);
		if (input[i] == '0')
			x.setBit(input.length() - 1 - i, 0);
	}
}

void QInt::createFromDec(string & input)
{
	string temp = decToBin(input);
	createFromBin(temp);
}

void QInt::createFromHex(string & input)
{
	string temp = hexToBin(input);
	createFromBin(temp);
}

bool QInt::setBit(int index, bool bit)
{
	if (index<0 || index>MAX_SIZE - 1)
		return false;
	else
	{
		int pos = 3;
		while ((index - BIT_PER_INT) >= 0)
		{
			index -= BIT_PER_INT;
			pos--;
		}
		if (bit == 1)
			turnOnBit(arrayBits[pos], index);
		else
			turnOffBit(arrayBits[pos], index);
		return true;
	}
}

bool QInt::getBit(int index)
{
	if (index<0 || index>MAX_SIZE - 1)
		return false;
	else
	{
		int pos = 3;
		while ((index - BIT_PER_INT) >= 0)
		{
			index -= BIT_PER_INT;
			pos--;
		}
		return getBitFromInt(arrayBits[pos], index);
	}
}

QInt QInt::operator+(QInt other)
{
	QInt sum;
	int mark = 0;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		//Cộng từng bit
		int s = getBit(i) + other.getBit(i) + mark;

		if (s == 1)
		{

			mark = 0;
			//Chuyển bit thứ i thành 1
			sum.setBit(i, 1);
		}
		//Nếu tổng là 2
		else if (s == 2)
		{
			//Nhớ 1
			mark = 1;
			//Chuyển bit thứ i thành 0
			sum.setBit(i, 0);
		}
		//Nếu tổng là 3
		else if (s == 3)
		{
			//Nhớ 1
			mark = 1;
			//Chuyển bit thứ i thành 1
			sum.setBit(i, 1);
		}
		//Nếu tổng là 0
		else if (s == 0)
		{
			//Nhớ 0
			mark = 0;
			//Chuyển bit thứ i thành 0
			sum.setBit(i, 0);
		}
	}
	return sum;
}

QInt QInt::operator-(QInt other)
{
	QInt negativeOther = ~other;
	QInt one("1", "10");
	negativeOther = negativeOther + one;
	return (*this) + negativeOther;
}

QInt QInt::operator*(QInt other)
{
	QInt A;
	QInt Q = *this;
	int k = 128;
	int bitQ1 = 0;
	string result;
	string temp1, temp2;
	while (k > 0)
	{
		int bit = Q.getBit(0);
		if (bit == 1 && bitQ1 == 0)
			A = A - other;
		if (bit == 0 && bitQ1 == 1)
			A = A + other;
		//
		if (bit == 1)
			bitQ1 = 1;
		else bitQ1 = 0;
		//
		temp1 = A.toString("2");
		temp2 = Q.toString("2");
		string str;
		str = str.append(temp1);
		str = str.append(temp2);

		for (int i = MAX_SIZE * 2 - 1; i > MAX_SIZE * 2 - 1 - 1; i--)
		{
			str.erase(str.length() - 1, 1);
			str.insert(str.begin(), str[0]);
		}

		for (int i = 0; i < MAX_SIZE; i++)
		{
			temp1[i] = str[i];
		}
		int j = 0;
		for (int i = MAX_SIZE; i < MAX_SIZE * 2; i++)
		{
			temp2[j] = str[i];
			j++;
		}

		//Cập nhật lại A và Q
		QInt A_temp(temp1, "2");
		QInt Q_temp(temp2, "2");
		A = A_temp;
		Q = Q_temp;

		str.clear();
		k--;
	}
	// Kết quả là A nối với Q ;
	return Q; // chỉ cần Q 
}

QInt QInt::operator/(QInt other)
{
	int k = 128;
	QInt A;
	QInt Q = *this;
	int q1 = 0;
	string temp1, temp2;
	string str;
	string temp3;
	int count = 0;
	if (Q.getBit(127) == 1)
	{
		QInt one("1", "10");
		Q = ~Q;
		Q = Q + one;
		count++;
	}
	if (other.getBit(127) == 1)
	{
		QInt one("1", "10");
		other = ~other;
		other = other + one;
		count++;
	}
	while (k > 0)
	{
		// dịch trái 1 bit [A , Q]

		temp1 = A.toString("2");
		temp2 = Q.toString("2");
		str = str.append(temp1);
		str = str.append(temp2);
		for (int i = 0; i < 1; i++)
		{
			str.insert(str.end(), 1, '0');
			str.erase(str.begin());
		}
		//
		for (int i = 0; i < MAX_SIZE; i++)
		{
			temp1[i] = str[i];
		}
		int j = 0;
		for (int i = MAX_SIZE; i < MAX_SIZE * 2; i++)
		{
			temp2[j] = str[i];
			j++;
		}

		//Cập nhật lại A và Q
		QInt A_temp(temp1, "2");
		QInt Q_temp(temp2, "2");
		A = A_temp;
		Q = Q_temp;

		str.clear();
		//
		A = A - other;
		// Nếu A<0 : A=A+M and q1=0
		if (A.getBit(127) == 1)
		{
			q1 = 0;
			Q.setBit(0, q1);
			A = A + other;
		}
		else // 
		{
			q1 = 1;
			Q.setBit(0, q1);
		}
		k--;
	}
	// Kết quả : This là thương , A là số dư
	if (count == 1)
	{
		QInt one("1", "10");
		Q = ~Q;
		Q = Q + one;
		return Q;
	}
	else
		return Q;
}

QInt QInt::operator&(QInt other)
{
	for (int i = 0; i < 4; i++)
		this->arrayBits[i] &= other.arrayBits[i];
	return (*this);
}

QInt QInt::operator|(QInt other)
{
	for (int i = 0; i < 4; i++)
		this->arrayBits[i] |= other.arrayBits[i];
	return (*this);
}

QInt QInt::operator^(QInt other)
{
	for (int i = 0; i < 4; i++)
		this->arrayBits[i] ^= other.arrayBits[i];
	return (*this);
}

QInt QInt::operator~()
{
	for (int i = 0; i < 4; i++)
		this->arrayBits[i] = ~this->arrayBits[i];
	return (*this);
}

QInt QInt::operator<<(int dis)
{
	QInt result;
	if (dis <= 0 || dis >= 128)
		return(*this);
	string temp = this->toString("2");
	for (int i = 0; i < dis; i++)
	{
		temp.insert(temp.end(), 1, '0');
		temp.erase(temp.begin());
	}

	result.createFromBin(temp);
	return result;
}

QInt QInt::operator>>(int dis)
{
	QInt result;
	if (dis <= 0 || dis >= 128)
		return(*this);
	string temp = this->toString("2");
	for (int i = MAX_SIZE - 1; i > MAX_SIZE - 1 - dis; i--)
	{
		temp.erase(temp.length() - 1, 1);
		temp.insert(temp.begin(), temp[0]);
	}

	result.createFromBin(temp);
	return result;
}

QInt QInt::rol()
{
	QInt result;
	string temp = this->toString("2");
	char mark = temp[0];
	temp.erase(temp.begin());
	temp.insert(temp.length(), 1, mark);

	result.createFromBin(temp);
	return result;
}

QInt QInt::ror()
{
	QInt result;
	string temp = this->toString("2");

	char mark = temp[temp.length() - 1];
	temp.erase(temp.length() - 1, 1);
	temp.insert(temp.begin(), mark);

	result.createFromBin(temp);
	return result;
}

string QInt::toString(string base)
{
	string temp;
	temp.resize(MAX_SIZE);
	for (int i = 0; i < MAX_SIZE; i++)
		temp[i] = getBit(MAX_SIZE - 1 - i) + '0';

	string result;
	if (base == "2")
		result = temp;
	if (base == "10")
		result = binToDec(temp);
	if (base == "16")
		result = binToHex(temp);

	return result;
}