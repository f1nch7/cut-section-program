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

private:
	GastResult gr; // 读取bathy文件头部信息
	vector<vector<Point>> allSections; // 存储所有断面的坐标

public:
	// 初始化路径信息，读取bathy文件头部信息
	void initValues(const string& _resultFolderPath, const string& _bathyFolderPath, const string& _bathyName = "bathy.asc");
	// 接收断面点信息
	void initSectionData(const vector<Point>& _vPoints);
	// 计算断面截取的网格行列号
	void calSectionData(double _k, double _b);
	bool isSectionData(double _nrow, double _ncol, double _k, double _b);

};
