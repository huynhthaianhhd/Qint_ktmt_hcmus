//===============================================================
//Nội dung: Xử lý số dạng chuỗi
//===============================================================

#pragma once
#include "Helper.h"

#pragma region Chuyển cơ số

//Chuyển chuỗi từ hệ 10 sang hệ 2
string decToBin(string input);

//Chuyển chuỗi từ hệ 2 sang hệ 10
string binToDec(string input);

//Chuyển chuỗi từ hệ 16 sang hệ 2
string hexToBin(string input);

//Chuyển chuỗi từ hệ 2 sang hệ 16
string binToHex(string input);

//Chuyển nhị phân sang dạng bù 2
string toTwosComplement(string input);

//Chuyển nhị phân dạng bù 2 về dạng dấu lượng
string toBasisBin(string input);

#pragma endregion

#pragma region Tính toán trên chuỗi

//Chia 2 lấy dư
char getRemainder(string input);

//Chia 2 lấy thương
string getQuotient(string input);

//Cộng 2 số dạng chuỗi
string sumFromString(string num1, string num2);

//Lũy thừa số dạng chuỗi
string expFromString(string num, int pow);

//Tích 2 số dạng chuỗi
string mulFromString(string num1, string num2);

//Tích 1 ký tự với 1 chuỗi (Để bổ trợ cho hàm tích 2 số dạng chuỗi)
string mulFromString(char num1, string num2);

#pragma endregion

//Xóa số 0 ở đầu không cần
void formatString(string &input);