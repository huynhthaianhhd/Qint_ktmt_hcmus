//===============================================================
//Nội dung:
//	Khai báo các thư viện, định nghĩa các hằng số
//	Một số hàm con bổ trợ cho get/set bit
//===============================================================

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

#define BIT_PER_INT 32
#define MAX_SIZE 128

//Bật bit lên 1 ở vị trí index trong phần tử kiểu int
bool turnOnBit(int &a, int index);

//Tắt bit xuống 0 ở vị trí index trong phần tử kiểu int
bool turnOffBit(int &a, int index);

//Lấy ra bit ở vị trí index trong phần tử kiểu int
bool getBitFromInt(int &a, int index);