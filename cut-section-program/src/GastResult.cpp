#include "../include/GastResult.h"

void GastResult::initValues(const string& _resultFolderPath, const string& _bathyFolderPath, const string& _bathyName)
{
    this->resultFolderPath = _resultFolderPath;
    this->bathyFolderPath = _bathyFolderPath;
    this->bathyName = _bathyName;
    // 1- 查找result文件夹下所有的dat文件
    this->findDat(_resultFolderPath);
    // 2- 读取bathy，提取头部信息
    this->readBathy(_bathyFolderPath + "\\" + _bathyName);

}

vector<string> GastResult::getAllDatPaths()
{
    return this->allDatPaths;
}

void GastResult::readBathy(const string& _path) {
    ifstream ifs(_path);
    string line;
    getline(ifs, line);
    this->ncols = atoi(this->splitString(line).c_str());
    getline(ifs, line);
    this->nrows = atoi(this->splitString(line).c_str());
    getline(ifs, line);
    this->xllcorner = atof(this->splitString(line).c_str());
    getline(ifs, line);
    this->yllcorner = atof(this->splitString(line).c_str());
    getline(ifs, line);
    this->cellSize = atof(this->splitString(line).c_str());
}

Point GastResult::getPointCoor(int _nrow, int _ncol)
{
	// 通过行列号获取坐标
	// x = xllcorner + cellsize * ncol
	// y = yllcorner + cellsize * nrow
	double x = this->xllcorner + this->cellSize * _ncol;
	double y = this->yllcorner + this->cellSize * _nrow;
	Point p(x, y);
	return p;
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
    while (getline(file, temp_imgname)) {
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

string GastResult::splitString(const string& _line)
{
    istringstream tokenStream(_line);
    string token;
    vector<string> v1;
    while (getline(tokenStream, token, ' ')) {
        if (!token.empty()) {
            v1.push_back(token);
        }
    }

    if (v1.empty()) {
        cerr << "Error: void Sections::splitString():" << _line << endl;
        return "";
    }
    return v1.back();
}

void GastResult::initCoorArr()
{
	this->coorArr = new double* [this->nrows];
	for (int i = 0; i < this->nrows; i++) {
		this->coorArr[i] = new double[this->ncols];
	}
	for (int i = 0; i < this->nrows; i++) {
		for (int j = 0; j < this->ncols; j++) {
			
		}
	}
}

//vector<vector<double>> GastResult::readData(const string &filename)
//{
//    vector<vector<double>> data;
//    ifstream file(filename);
//    string line;
//
//    // 跳过文件的第一行（标题）
//    getline(file, line);
//
//    // 读取数据
//    while (getline(file, line)) {
//        stringstream ss(line);
//        vector<double> row;
//        double value;
//        while (ss >> value) {
//            row.push_back(value);
//        }
//        if (row.size() > 0) {
//            data.push_back(row);
//        }
//    }
//
//    return data;
//}
//
//void GastResult::computeSectionData(const vector<Point>& sectionPoints, 
//                                   const vector<vector<double>>& modelData, 
//                                   vector<double>& QSec, 
//                                   vector<double>& A, 
//                                   vector<double>& Width) {
//    // 计算每个断面上的流量、面积、速度等
//    // 模拟计算逻辑，具体根据你的需求实现
//
//    for (size_t i = 0; i < sectionPoints.size(); ++i) {
//        const Point& p = sectionPoints[i];
//        for (const auto& data : modelData) {
//            if (fabs(p.x - data[0]) < 0.001 && 
//                fabs(p.y - data[1]) < 0.001) {
//                // 计算流量、面积、宽度等（示例）
//                QSec.push_back(data[4]);  // 示例，流量
//                A.push_back(data[4] * 0.1);  // 示例，面积
//                Width.push_back(1.0);  // 示例，宽度
//            }
//        }
//    }
//}
