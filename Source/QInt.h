//===============================================================
//Nội dung:
//	Chuyển cơ số
//	Các phép toán + - * / AND OR XOR NOT << >> rol ror
//===============================================================

#pragma once
#include "StringFunction.h"

class QInt
{
private:
	//Mảng 4 phần tử kiểu int tương đương 128 bits
	int arrayBits[4];

public:
#pragma region Khởi tạo

	//Khởi tạo mặc định là 0
	QInt();

	//Khởi tạo từ chuỗi có hệ base
	QInt(string input, string base);

	//Khởi tạo từ chuỗi có hệ 2
	void createFromBin(string &input);

	//Cập nhật x từ chuỗi input
	void updateFromBin(string & input, QInt &x);

	//Khởi tạo từ chuỗi có hệ 10
	void createFromDec(string &input);

	//Khởi tạo từ chuỗi có hệ 16
	void createFromHex(string &input);

#pragma endregion

#pragma region Thao tác trên bit

	//Đặt bit ở vị trí index trong mảng arrayBits
	bool setBit(int index, bool bit);

	//Lấy ra bit ở vị trí index trong mảng arrayBits
	bool getBit(int index);

#pragma endregion

#pragma region Phép toán

	//Operator cộng
	QInt operator+(QInt other);

	//Operator trừ
	QInt operator-(QInt other);

	//Operator nhân
	QInt operator*(QInt other);

	//Operator chia
	QInt operator/(QInt other);

	//Operator AND
	QInt operator&(QInt other);

	//Operator OR
	QInt operator|(QInt other);

	//Operator XOR
	QInt operator^(QInt other);

	//Operator NOT
	QInt operator~();

	//Dịch trái
	QInt operator<<(int dis);

	//Dịch phải
	QInt operator>>(int dis);

	//Xoay trái
	QInt rol();

	//Xoay phải
	QInt ror();

#pragma endregion

	//Trả về chuỗi có hệ base
	string toString(string base);
};