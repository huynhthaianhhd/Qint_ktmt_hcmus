//===============================================================
//Nội dung: Đọc + ghi file
//===============================================================

#pragma once
#include "QInt.h"

//Đọc từng file (Chưa xử lý dữ liệu)
vector<string>readString(ifstream& fileIn);

//Ghi kết quả
void writeString(ofstream& fileOut, vector<string>& output);

//Tách dữ liệu thành các toán hạng và toán tử
vector<string> splitString(string input);

//Xử lý dữ liệu
string analysisData(vector<string>input);

//Hàm chính: Đọc file và ghi kết quả ra file
void writeFile(string fileIn, string fileOut);