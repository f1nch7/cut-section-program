#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>
using namespace std;

struct Point {
    Point(double _x, double _y) : x(_x), y(_y) {};
    double x = 0.0;
    double y = 0.0;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

class GastResult {

private:
    int ncols = 0;
    int nrows = 0;
    double xllcorner = 0;
    double yllcorner = 0;
    double cellSize = 0.0;
    vector<string> allDatPaths;
    string resultFolderPath;
    string bathyFolderPath;
    string bathyName;

public:
    void initValues(const string& _resultFolderPath, const string& _bathyFolderPath, const string& _bathyName = "bathy.asc");
    vector<string> getAllDatPaths();
    void readBathy(const string& _path);

private:
    void findDat(const string& _path);
    string splitString(const string& _line);

};

