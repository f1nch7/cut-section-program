#if 0
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <chrono>
#include <vector>

using namespace std;

// ����һ���ṹ�����ڴ洢����
struct DataRow {
    double z, zb, u, v;
};

// ���ڱȽ� x �� y �ĵ�
struct Point {
    double x, y;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// ��ϣ������ʹ�� Point ������Ϊ unordered_map �ļ�
namespace std {
    template <>
    struct hash<Point> {
        size_t operator()(const Point& p) const {
            return hash<double>()(p.x) ^ hash<double>()(p.y);
        }
    };
};

// ���ж�ȡ�ļ����������Բ���
void linearReadAndSearch(const string& filename, const vector<Point>& targetPoints) {
    ifstream file(filename);
    string line;
    double x, y, z, zb, u, v;
    unordered_map<Point, DataRow> resultMap;

    while (getline(file, line)) {
        istringstream ss(line);
        ss >> x >> y >> z >> zb >> u >> v;
        Point point = { x, y };
        DataRow row = { z, zb, u, v };

        // ��������Ŀ��㲢���в���
        for (const auto& targetPoint : targetPoints) {
            if (point == targetPoint) {
                resultMap[point] = row;
            }
        }
    }

    // ������ҽ��
    for (const auto& targetPoint : targetPoints) {
        if (resultMap.find(targetPoint) != resultMap.end()) {
            const DataRow& row = resultMap[targetPoint];
            cout << "Found data for (" << targetPoint.x << ", " << targetPoint.y << "): "
                << "z = " << row.z << ", zb = " << row.zb << ", u = " << row.u << ", v = " << row.v << endl;
        }
        else {
            cout << "Data not found for (" << targetPoint.x << ", " << targetPoint.y << ")." << endl;
        }
    }
}

// ʹ�ù�ϣ��洢���ݲ�����
void hashTableReadAndSearch(const string& filename, const vector<Point>& targetPoints) {
    ifstream file(filename);
    string line;
    unordered_map<Point, DataRow> dataMap;
    double x, y, z, zb, u, v;

    // ��ȡ�ļ��������ݴ����ϣ��
    while (getline(file, line)) {
        istringstream ss(line);
        ss >> x >> y >> z >> zb >> u >> v;
        Point point = { x, y };
        DataRow row = { z, zb, u, v };
        dataMap[point] = row;
    }

    // ����Ŀ�������Ӧ������
    for (const auto& targetPoint : targetPoints) {
        if (dataMap.find(targetPoint) != dataMap.end()) {
            const DataRow& row = dataMap[targetPoint];
            cout << "Found data for (" << targetPoint.x << ", " << targetPoint.y << "): "
                << "z = " << row.z << ", zb = " << row.zb << ", u = " << row.u << ", v = " << row.v << endl;
        }
        else {
            cout << "Data not found for (" << targetPoint.x << ", " << targetPoint.y << ")." << endl;
        }
    }
}

int main() {
    string filename = "data.dat"; // �����ļ����� data.txt

    // ����Ҫ���ҵ� 10 ��Ŀ�������
    vector<Point> targetPoints = {
        {25.0, 25.0}, {75.0, 25.0}, {125.0, 25.0}, {175.0, 25.0}, {225.0, 25.0},
        {275.0, 25.0}, {325.0, 25.0}, {375.0, 25.0}, {425.0, 25.0}, {475.0, 25.0}
    };

    // ʹ�����ж�ȡ����
    auto start = chrono::high_resolution_clock::now();
    cout << "Using linear read and search:" << endl;
    linearReadAndSearch(filename, targetPoints);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> linear_duration = end - start;
    cout << "Time taken for linear read and search: " << linear_duration.count() << " seconds." << endl;

    cout << endl;

    // ʹ�ù�ϣ���ȡ�Ͳ��ҷ���
    start = chrono::high_resolution_clock::now();
    cout << "Using hash table read and search:" << endl;
    hashTableReadAndSearch(filename, targetPoints);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> hash_duration = end - start;
    cout << "Time taken for hash table read and search: " << hash_duration.count() << " seconds." << endl;

    return 0;
}
#endif