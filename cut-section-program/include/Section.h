#pragma once
#include <iostream>
using namespace std;
#include <vector>

class Section {
public:
    std::vector<Point> points;
    
    // 添加点到断面
    void addPoint(const Point& point) {
        points.push_back(point);
    }

    // 获取断面上的所有点
    const std::vector<Point>& getPoints() const {
        return points;
    }
};
