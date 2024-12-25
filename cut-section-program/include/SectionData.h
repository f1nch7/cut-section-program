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

private:
	GastResult gr; // ��ȡbathy�ļ�ͷ����Ϣ
	vector<vector<Point>> allSections; // �洢���ж��������

public:
	// ��ʼ��·����Ϣ����ȡbathy�ļ�ͷ����Ϣ
	void initValues(const string& _resultFolderPath, const string& _bathyFolderPath, const string& _bathyName = "bathy.asc");
	// ���ն������Ϣ
	void initSectionData(const vector<Point>& _vPoints);
	// ��������ȡ���������к�
	void calSectionData(double _k, double _b);
	bool isSectionData(double _nrow, double _ncol, double _k, double _b);

};
