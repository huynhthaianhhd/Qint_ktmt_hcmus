#include "StringFunction.h"

string decToBin(string input)
{
	string temp = input;
	string result;
	result.resize(MAX_SIZE);
	for (int i = 0; i < result.size(); i++)
		result[i] = '0';

	int index = result.size();

	//Nếu là số âm
	if (input[0] == '-')
	{
		//Xóa dấu trừ rồi thao tác như số dương
		temp = input.erase(0, 1);

		//Làm tới khi temp = 0 thì dừng
		while (temp != "0")
		{
			char remainder = getRemainder(temp);
			result[--index] = remainder;
			temp = getQuotient(temp);
		}

		//Đưa về dạng bù 2
		result = toTwosComplement(result);
	}

	else
	{
		//Làm tới khi temp = 0 thì dừng
		while (temp != "0")
		{
			char remainder = getRemainder(temp);
			result[--index] = remainder;
			temp = getQuotient(temp);
		}
	}
	return result;
}

string binToDec(string input)
{
	string sum = "0";
	//Số dương
	if (input[0] == '0')
	{
		for (int i = 0; i < input.size(); i++)
		{
			if (input[i] == '1')
				sum = sumFromString(sum, expFromString("2", MAX_SIZE - 1 - i));
		}
		return sum;
	}
	else
	{
		//Số âm thì chuyển về dấu lượng
		input = toBasisBin(input);
		for (int i = 0; i < input.size(); i++)
		{
			if (input[i] == '1')
				sum = sumFromString(sum, expFromString("2", MAX_SIZE - 1 - i));
		}

		//Thêm dấu -
		sum.insert(sum.begin(), 1, '-');
	}
	return sum;
}

string hexToBin(string input)
{
	string result = "";
	string convert = "";
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == '0') convert = "0000";
		if (input[i] == '1') convert = "0001";
		if (input[i] == '2') convert = "0010";
		if (input[i] == '3') convert = "0011";
		if (input[i] == '4') convert = "0100";
		if (input[i] == '5') convert = "0101";
		if (input[i] == '6') convert = "0110";
		if (input[i] == '7') convert = "0111";
		if (input[i] == '8') convert = "1000";
		if (input[i] == '9') convert = "1001";
		if (input[i] == 'A') convert = "1010";
		if (input[i] == 'B') convert = "1011";
		if (input[i] == 'C') convert = "1100";
		if (input[i] == 'D') convert = "1101";
		if (input[i] == 'E') convert = "1110";
		if (input[i] == 'F') convert = "1111";

		result += convert;
	}

	//Thêm 0 vào đầu cho đủ 128 bits
	while (result.size() < MAX_SIZE)
		result.insert(0, 1, '0');

	return result;
}

string binToHex(string input)
{
	string result;
	char convert = '\0';
	for (int i = 0; i < input.size(); i += 4)
	{
		string temp = input.substr(i, 4);
		if (temp == "0000") convert = '0';
		if (temp == "0001") convert = '1';
		if (temp == "0010") convert = '2';
		if (temp == "0011") convert = '3';
		if (temp == "0100") convert = '4';
		if (temp == "0101") convert = '5';
		if (temp == "0110") convert = '6';
		if (temp == "0111") convert = '7';
		if (temp == "1000") convert = '8';
		if (temp == "1001") convert = '9';
		if (temp == "1010") convert = 'A';
		if (temp == "1011") convert = 'B';
		if (temp == "1100") convert = 'C';
		if (temp == "1101") convert = 'D';
		if (temp == "1110") convert = 'E';
		if (temp == "1111") convert = 'F';

		result += convert;
	}

	return result;
}

string toTwosComplement(string input)
{
	//Chuyển 1 -> 0 và 0 -> 1
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '1')
			input[i] = '0';
		else
			input[i] = '1';
	}

	//Cộng 1
	int check = 1;
	int pos = input.size() - 1;
	while (check != 0)
	{
		//Nếu phần tử cuối = 0
		if (input[pos] == '0')
		{
			input[pos] = '1';
			check = 0;
		}
		else
			input[pos] = '0';
		pos--;
	}

	return input;
}

string toBasisBin(string input)
{
	//Trừ 1
	int check = 1;
	int index = input.size() - 1;

	while (check != 0)
	{
		if (input[index] == '1')
		{
			input[index] = '0';
			check = 0;
		}
		else
		{
			input[index] = '1';
		}
		index--;
	}

	//~(input)
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '0')
			input[i] = '1';
		else
			input[i] = '0';
	}

	return input;
}

char getRemainder(string input)
{
	char result;
	//Lấy ra chữ số cuối và chuyển về int
	int last = input[input.length() - 1] - '0';
	//Lấy số dư
	result = (last % 2) + '0';
	return result;
}

string getQuotient(string input)
{
	if (input == "1")
		return "0";

	string result = "";
	int pos = 0;
	int temp = input[pos] - '0';

	while (temp < 2)
		temp = temp * 10 + (input[++pos] - '0');

	while (pos < input.size())
	{
		result += (temp / 2) + '0';
		temp = (temp % 2) * 10 + (input[++pos] - '0');
	}

	return result;
}

string sumFromString(string num1, string num2)
{
	string result = "";
	int len1 = num1.length();
	int len2 = num2.length();

	//Chuẩn hóa chuỗi cho 2 độ dài chuỗi bằng nhau bằng cách thêm 0 vào đầu
	if (len1 >= len2)
		num2.insert(0, len1 - len2, '0');
	else
		num1.insert(0, len2 - len1, '0');

	//Biến nhớ (VD: Cộng ra 21 thì nhớ 2)
	int mark = 0;
	for (int i = num1.length() - 1; i >= 0; i--)
	{
		//Tính tổng từng đôi một
		mark = (num1[i] - '0') + (num2[i] - '0') + mark;
		//Gán phần đơn vị vào kết quả
		result.insert(0, 1, (mark % 10) + '0');
		//Lấy lại phần hàng chục
		mark /= 10;
	}
	//Sau khi cộng đôi một xong mà biến nhớ còn thì thêm vào đầu kết quả
	if (mark > 0)
		result.insert(0, 1, mark + '0');

	return result;
}

string expFromString(string num, int pow)
{
	string result = "1";
	for (int i = 0; i < pow; i++)
		result = mulFromString(result, num);
	return result;
}

string mulFromString(string num1, string num2)
{
	string result = "";
	int len = num1.length();
	string temp;

	for (int i = len - 1; i >= 0; i--)
	{
		//Nhân từng số của num1 với num2
		temp = mulFromString(num1[i], num2);
		temp.insert(temp.length(), len - i - 1, '0');
		result = sumFromString(result, temp);
	}

	return result;
}

string mulFromString(char num1, string num2)
{
	string result = "";
	//Biến nhớ (VD: Cộng ra 21 thì nhớ 2)
	int mark = 0;
	for (int i = num2.length() - 1; i >= 0; i--)
	{
		//Nhân num1 với từng số của num2
		mark = (num1 - '0')*(num2[i] - '0') + mark;
		//Gán phần đơn vị vào kết quả
		result.insert(0, 1, (mark % 10) + '0');
		//Lấy lại phần hàng chục
		mark /= 10;
	}
	//Sau khi nhân xong mà biến nhớ còn thì thêm vào đầu kết quả
	if (mark > 0)
		result.insert(0, 1, mark + '0');

	return result;
}

void formatString(string & input)
{
	//Loại trừ kết quả là 0
	if ((input[0] == '0' && input.length() == 1) || input[0] != '0')
		return;
	else
	{
		input.erase(0, 1);
		formatString(input);
	}
}