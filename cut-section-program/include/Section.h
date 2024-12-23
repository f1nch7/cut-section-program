#pragma once
#include <iostream>
using namespace std;
#include <vector>

class Section {
public:
    std::vector<Point> points;
    
    // ��ӵ㵽����
    void addPoint(const Point& point) {
        points.push_back(point);
    }

    // ��ȡ�����ϵ����е�
    const std::vector<Point>& getPoints() const {
        return points;
    }
};
