#include "../include/GastResult.h"

void GastResult::setFolderPath(string _path) {
    this->folderPath = _path;
    this->findDat(this->folderPath);
}

vector<string> GastResult::getAllDatPaths()
{
    return this->allDatPaths;
}

void GastResult::findDat(const string& _path) {
    string imglist_file = "1.txt";//存储文件名称列表
    ofstream ofs(imglist_file);
    ofs.close();
    string temp_imgname;
    string dir_command("dir ");
    dir_command += _path + "/b > " + imglist_file;//m_strImageSet是我之前建立的变量 里面存放的是文件夹路径
    ifstream file(imglist_file.c_str(), ios::in);
    system(dir_command.c_str());
    vector <string> imglist;
    //把图像名称都存入vector中
    while (getline(file, temp_imgname))
    {
        if (temp_imgname.find("result") == 0) {
            // 检查是否以"s.dat"结尾
            size_t len = temp_imgname.length();
            if (temp_imgname.length() >= 4 && temp_imgname.substr(temp_imgname.length() - 5) == "s.dat") {
                this->allDatPaths.push_back(temp_imgname);
            }
        }

    }
    file.close();
    remove(imglist_file.c_str());
}

vector<vector<double>> GastResult::readData(const string &filename)
{
    vector<vector<double>> data;
    ifstream file(filename);
    string line;

    // 跳过文件的第一行（标题）
    getline(file, line);

    // 读取数据
    while (getline(file, line)) {
        stringstream ss(line);
        vector<double> row;
        double value;
        while (ss >> value) {
            row.push_back(value);
        }
        if (row.size() > 0) {
            data.push_back(row);
        }
    }

    return data;
}

void GastResult::computeSectionData(const vector<Point>& sectionPoints, 
                                   const vector<vector<double>>& modelData, 
                                   vector<double>& QSec, 
                                   vector<double>& A, 
                                   vector<double>& Width) {
    // 计算每个断面上的流量、面积、速度等
    // 模拟计算逻辑，具体根据你的需求实现

    for (size_t i = 0; i < sectionPoints.size(); ++i) {
        const Point& p = sectionPoints[i];
        for (const auto& data : modelData) {
            if (fabs(p.x - data[0]) < 0.001 && 
                fabs(p.y - data[1]) < 0.001) {
                // 计算流量、面积、宽度等（示例）
                QSec.push_back(data[4]);  // 示例，流量
                A.push_back(data[4] * 0.1);  // 示例，面积
                Width.push_back(1.0);  // 示例，宽度
            }
        }
    }
}
