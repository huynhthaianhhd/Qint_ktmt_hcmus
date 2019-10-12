#include "FileFunction.h"

vector<string> readString(ifstream & fileIn)
{
	vector<string>result;
	string temp;
	while (!fileIn.eof())
	{
		getline(fileIn, temp);
		result.push_back(temp);
	}
	return result;
}

void writeString(ofstream & fileOut, vector<string>& output)
{
	for (int i = 0; i < output.size(); i++)
		fileOut << output[i] << endl;
}

vector<string> splitString(string input)
{
	vector<string>result;
	//Chuyển sang kiểu char* để làm việc với strtok
	char *clone = _strdup(input.c_str());
	char *temp = strtok(clone, " ");
	if (temp)
		result.push_back(string(temp));
	//Trong khi còn cắt được thì cắt ở vị trí bắt đầu là vị trí trước đó đã dừng lại
	while (temp = strtok(NULL, " "))
		result.push_back(string(temp));

	delete[]clone;
	delete[]temp;

	return result;
}

string analysisData(vector<string> input)
{
	if (input.size() == 4)
	{
		if ((input[2] != ">>") && (input[2] != "<<"))
		{
			QInt num1(input[1], input[0]);
			QInt num2(input[3], input[0]);

			if (input[2] == "+")
			{
				QInt result = num1 + num2;
				return result.toString(input[0]);
			}

			if (input[2] == "-")
			{
				QInt result = num1 - num2;
				return result.toString(input[0]);
			}

			if (input[2] == "*")
			{
				QInt result = num1 * num2;
				return result.toString(input[0]);
			}

			if (input[2] == "/")
			{
				QInt result = num1 / num2;
				return result.toString(input[0]);
			}

			if (input[2] == "&")
			{
				QInt result = num1 & num2;
				return result.toString(input[0]);
			}

			if (input[2] == "|")
			{
				QInt result = num1 | num2;
				return result.toString(input[0]);
			}

			if (input[2] == "^")
			{
				QInt result = num1 ^ num2;
				return result.toString(input[0]);
			}
		}

		else
		{
			QInt num(input[1], input[0]);
			int dis = atoi(input[3].c_str());
			if (input[2] == ">>")
			{
				QInt result = num >> dis;
				return result.toString(input[0]);
			}

			if (input[2] == "<<")
			{
				QInt result = num << dis;
				return result.toString(input[0]);
			}
		}
	}

	if (input.size() == 3)
	{
		QInt num(input[2], input[0]);
		if (input[1] == "rol")
			return num.rol().toString(input[0]);

		if (input[1] == "ror")
			return num.ror().toString(input[0]);

		if (input[1] == "~")
			return (~num).toString(input[0]);

		//Trường hợp còn lại là chuyển cơ số
		return num.toString(input[1]);
	}

	return "";
}

void writeFile(string fileInPath, string fileOutPath)
{
	ifstream fileIn(fileInPath, ios::in);
	if (!fileIn)
	{
		cout << "Can not open file !" << endl;
		system("pause");
		exit(0);
	}

	else
	{
		vector<string>input = readString(fileIn);
		fileIn.close();

		vector<string>output;
		for (int i = 0; i < input.size(); i++)
		{

			string temp = analysisData(splitString(input[i]));

			formatString(temp);

			output.push_back(temp);
		}

		ofstream fileOut(fileOutPath, ios::out);
		writeString(fileOut, output);
		fileOut.close();

		cout << "Process completed !" << endl;
	}
}