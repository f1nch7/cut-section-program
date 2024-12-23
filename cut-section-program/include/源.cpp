#if 0
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <chrono>
#include <vector>

using namespace std;

// 定义一个结构体用于存储数据
struct DataRow {
    double z, zb, u, v;
};

// 用于比较 x 和 y 的点
struct Point {
    double x, y;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// 哈希函数，使得 Point 可以作为 unordered_map 的键
namespace std {
    template <>
    struct hash<Point> {
        size_t operator()(const Point& p) const {
            return hash<double>()(p.x) ^ hash<double>()(p.y);
        }
    };
};

// 逐行读取文件并进行线性查找
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

        // 遍历所有目标点并进行查找
        for (const auto& targetPoint : targetPoints) {
            if (point == targetPoint) {
                resultMap[point] = row;
            }
        }
    }

    // 输出查找结果
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

// 使用哈希表存储数据并查找
void hashTableReadAndSearch(const string& filename, const vector<Point>& targetPoints) {
    ifstream file(filename);
    string line;
    unordered_map<Point, DataRow> dataMap;
    double x, y, z, zb, u, v;

    // 读取文件并将数据存入哈希表
    while (getline(file, line)) {
        istringstream ss(line);
        ss >> x >> y >> z >> zb >> u >> v;
        Point point = { x, y };
        DataRow row = { z, zb, u, v };
        dataMap[point] = row;
    }

    // 查找目标坐标对应的数据
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
    string filename = "data.dat"; // 假设文件名是 data.txt

    // 设置要查找的 10 个目标坐标点
    vector<Point> targetPoints = {
        {25.0, 25.0}, {75.0, 25.0}, {125.0, 25.0}, {175.0, 25.0}, {225.0, 25.0},
        {275.0, 25.0}, {325.0, 25.0}, {375.0, 25.0}, {425.0, 25.0}, {475.0, 25.0}
    };

    // 使用逐行读取方法
    auto start = chrono::high_resolution_clock::now();
    cout << "Using linear read and search:" << endl;
    linearReadAndSearch(filename, targetPoints);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> linear_duration = end - start;
    cout << "Time taken for linear read and search: " << linear_duration.count() << " seconds." << endl;

    cout << endl;

    // 使用哈希表读取和查找方法
    start = chrono::high_resolution_clock::now();
    cout << "Using hash table read and search:" << endl;
    hashTableReadAndSearch(filename, targetPoints);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> hash_duration = end - start;
    cout << "Time taken for hash table read and search: " << hash_duration.count() << " seconds." << endl;

    return 0;
}
#endif