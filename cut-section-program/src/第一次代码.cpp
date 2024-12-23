// #include <iostream>
// #include <fstream>
// #include <vector>
// #include <cmath>
// #include <string>
// #include <sstream>
// #include <algorithm>

// // 定义一个结构体来存储点的坐标和高程
// struct Point {
//     double x, y, elevation;
// };

// // 函数：读取文件数据并返回二维数组
// std::vector<std::vector<double>> readData(const std::string& filename) {
//     std::vector<std::vector<double>> data;
//     std::ifstream file(filename);
//     std::string line;

//     // 跳过文件的第一行（标题）
//     std::getline(file, line);

//     // 读取数据
//     while (std::getline(file, line)) {
//         std::stringstream ss(line);
//         std::vector<double> row;
//         double value;
//         while (ss >> value) {
//             row.push_back(value);
//         }
//         if (row.size() > 0) {
//             data.push_back(row);
//         }
//     }

//     return data;
// }

// // 函数：将结果写入文件
// void writeData(const std::string& filename, const std::vector<std::vector<double>>& data) {
//     std::ofstream file(filename);
//     for (const auto& row : data) {
//         for (size_t i = 0; i < row.size(); ++i) {
//             file << row[i];
//             if (i < row.size() - 1) {
//                 file << " ";
//             }
//         }
//         file << "\n";
//     }
// }

// int main() {
//     double x_ori = 0.0;  // x轴起点
//     double y_ori = 0.0;  // y轴起点
//     double dxSec = 0.1;  // 网格单元大小

//     // 定义断面起始和结束点的坐标
//     std::vector<double> Secx0 = {9.96};
//     std::vector<double> Secy0 = {0.06};
//     std::vector<double> Secx1 = {9.96};
//     std::vector<double> Secy1 = {0.96};

//     // 输入目录，GAST模型数据的存储位置
//     std::string InputDir = "D:/Work/2024Work/10_Oct/Mingmodel/PollModelrun1016/Out";
    
//     // 计算断面坐标
//     int NSec = Secx0.size();
//     for (int i = 0; i < NSec; ++i) {
//         Secx0[i] -= x_ori;
//         Secy0[i] -= y_ori;
//         Secx1[i] -= x_ori;
//         Secy1[i] -= y_ori;
//     }

//     std::vector<double> Secx;
//     std::vector<double> Secy;
//     std::vector<int> NoSec;
//     int NSecCell = 1; // 断面单元数量
//     double a, b;
    
//     for (int i = 0; i < NSec; ++i) {
//         if (std::abs(Secx1[i] - Secx0[i]) > std::abs(Secy1[i] - Secy0[i])) {
//             a = (Secy1[i] - Secy0[i]) / (Secx1[i] - Secx0[i]);
//             b = Secy0[i] - a * Secx0[i];
//             int NumSecCell = std::round((Secx1[i] - Secx0[i]) / dxSec);
//             for (int j = 0; j <= NumSecCell; ++j) {
//                 Secx.push_back(Secx0[i] + j * dxSec);
//                 Secy.push_back(a * Secx.back() + b);
//                 NoSec.push_back(i);
//                 NSecCell++;
//             }
//         } else {
//             a = (Secx1[i] - Secx0[i]) / (Secy1[i] - Secy0[i]);
//             b = Secx0[i] - a * Secy0[i];
//             int NumSecCell = std::round((Secy1[i] - Secy0[i]) / dxSec);
//             for (int j = 0; j <= NumSecCell; ++j) {
//                 Secy.push_back(Secy0[i] + j * dxSec);
//                 Secx.push_back(a * Secy.back() + b);
//                 NoSec.push_back(i);
//                 NSecCell++;
//             }
//         }
//     }

//     // 读取GAST模型数据
//     std::vector<std::string> fileNames = {"FirstDat.dat"}; // 这里应该填入真实的文件名

//     std::vector<std::vector<double>> FirstDat = readData(fileNames[0]);
//     std::vector<Point> SectionData;
//     double distmin = 2 * dxSec;

//     for (size_t ii = 0; ii < Secx.size(); ++ii) {
//         double SecX = Secx[ii];
//         double SecY = Secy[ii];
//         int SecNo = NoSec[ii];

//         // 根据坐标筛选数据
//         std::vector<std::vector<double>> SecondDat;
//         for (const auto& row : FirstDat) {
//             if (row[0] < (std::max(Secx0[SecNo], Secx1[SecNo]) + 2 * dxSec) &&
//                 row[0] > (std::min(Secx0[SecNo], Secx1[SecNo]) - 2 * dxSec) &&
//                 row[1] < (std::max(Secy0[SecNo], Secy1[SecNo]) + 2 * dxSec) &&
//                 row[1] > (std::min(Secy0[SecNo], Secy1[SecNo]) - 2 * dxSec)) {
//                 SecondDat.push_back(row);
//             }
//         }

//         // 找到距离断面点最近的有效数据
//         for (const auto& row : SecondDat) {
//             double DistCell = std::sqrt(std::pow(row[0] - SecX, 2) + std::pow(row[1] - SecY, 2));
//             if (DistCell < distmin) {
//                 distmin = DistCell;
//                 Point point = {row[0], row[1], row[2]}; // x, y, 高程
//                 SectionData.push_back(point);
//             }
//         }
//         distmin = 2 * dxSec;
//     }

//     // 将断面数据写入文件
//     std::vector<std::vector<double>> SecOutput;
//     for (size_t i = 0; i < SectionData.size(); ++i) {
//         std::vector<double> row = {SectionData[i].x, SectionData[i].y, SectionData[i].elevation};
//         SecOutput.push_back(row);
//     }

//     writeData("SectionData.R.txt", SecOutput);

//     // -------------------------------------------------
//     // 计算流量、面积、速度等
//     // -------------------------------------------------
//     std::vector<double> QSec(NSec, 0.0);
//     std::vector<double> A(NSec, 0.0);
//     std::vector<double> Width(NSec, 0.0);
//     std::vector<double> h_wet(NSec, 0.0);
//     std::vector<double> VSec;
    
//     // 读取更多文件并进行计算
//     for (const auto& file : fileNames) {
//         std::vector<std::vector<double>> FirstDat = readData(file);
//         for (size_t pp = 0; pp < Secx.size(); ++pp) {
//             for (size_t nn = 0; nn < FirstDat.size(); ++nn) {
//                 if (Secx[pp] == FirstDat[nn][0] && Secy[pp] == FirstDat[nn][1]) {
//                     for (int ss = 0; ss < NSec; ++ss) {
//                         if (NoSec[pp] == ss) {
//                             QSec[ss] += FirstDat[nn][4] * std::sqrt(std::pow(FirstDat[nn][2], 2) + std::pow(FirstDat[nn][3], 2)) * dxSec;
//                             A[ss] += FirstDat[nn][4] * dxSec;
//                             if (FirstDat[nn][4] > 0.01) {
//                                 Width[ss] += dxSec;
//                             }
//                         }
//                     }
//                 }
//             }
//         }
        
//         // 重置流量、面积和宽度
//         std::fill(QSec.begin(), QSec.end(), 0.0);
//         std::fill(A.begin(), A.end(), 0.0);
//         std::fill(Width.begin(), Width.end(), 0.0);
//     }

//     // 计算速度和水深
//     for (int ss = 0; ss < NSec; ++ss) {
//         VSec.push_back(QSec[ss] / A[ss]);
//         double h_mean = A[ss] / Width[ss];
//     }

//     // 输出最终结果
//     writeData("SectionOutput.txt", SecOutput);

//     std::cout << "完成!" << std::endl;

//     return 0;
// }
