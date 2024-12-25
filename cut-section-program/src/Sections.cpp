//#include "../include/Sections.h"
//
//
//Sections::Sections()
//{
//
//}
//
//Sections::~Sections()
//{
//}
//
//void Sections::initValues(const Point& _oriP, const Point& _markP)
//{
//	this->oriP.x = _oriP.x;
//	this->oriP.y = _oriP.y;
//	this->markP.x = _markP.x;
//	this->markP.y = _markP.y;
//    this->readBathy("E:\\vs2022Project\\cut-section-program\\cut-section-program\\cut-section-program\\input\\bathy.asc");
//}
//
//void Sections::readBathy(const string& _path) {
//
//	/*ifstream ifs(_path);
//	string line;
//	getline(ifs, line);
//    this->ncols = atoi(this->splitString(line).c_str());
//    getline(ifs, line);
//    this->nrows = atoi(this->splitString(line).c_str());
//    getline(ifs, line);
//    this->xllcorner = atof(this->splitString(line).c_str());
//    getline(ifs, line);
//    this->yllcorner = atof(this->splitString(line).c_str());
//    getline(ifs, line);
//    this->cellSize = atof(this->splitString(line).c_str());
//    cout << "cellsize = " << this->cellSize << endl;*/
//}
//
//string Sections::splitString(const string& _line)
//{
//    istringstream tokenStream(_line);
//    string token;
//    vector<string> v1;
//    while (getline(tokenStream, token, ' ')) {
//        if (!token.empty()) {
//            v1.push_back(token);
//        }
//    }
//
//    if (v1.empty()) {
//        cerr << "Error: void Sections::splitString():" << _line << endl;
//        return "";
//    }
//    return v1.back();
//}
