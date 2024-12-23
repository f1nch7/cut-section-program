#pragma once
#include "../include/GastResult.h"
/*
	1- 读取bathy，提取头部数据
	2- 提取result路径
	3- 根据输入的断面点，判断断面网格的行列号（x,y)
	4- 根据行列号，得到对应的坐标
	5- 开始遍历result，判断提取出来的断面坐标对应的数据并存储
*/

class SectionData
{
public:
	SectionData();
	~SectionData();
public:
	void initValues(const string& _resultFolderPath, const string& _bathyFolderPath, const string& _bathyName = "bathy.asc");
private:
	GastResult gr;
};
