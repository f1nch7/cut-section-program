#pragma once
#include "../include/GastResult.h"
/*
	1- ��ȡbathy����ȡͷ������
	2- ��ȡresult·��
	3- ��������Ķ���㣬�ж϶�����������кţ�x,y)
	4- �������кţ��õ���Ӧ������
	5- ��ʼ����result���ж���ȡ�����Ķ��������Ӧ�����ݲ��洢
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
