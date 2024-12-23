#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>
using namespace std;

class Point {
public:
    double x = 0.0;
    double y = 0.0;

};

class GastResult {

private:
    vector<string> allDatPaths;
    string folderPath;

public:
    void setFolderPath(string _path);
    vector<string> getAllDatPaths();

private:
    void findDat(const string& _path);
    // ��ȡ�����ļ�
    static vector<vector<double>> readData(const string& filename);

    // ����������������ٶȵ�
    static void computeSectionData(const vector<Point>& sectionPoints, 
                                   const vector<vector<double>>& modelData, 
                                   vector<double>& QSec, 
                                   vector<double>& A, 
                                   vector<double>& Width);
};

