#include "../include/SectionData.h"


SectionData::SectionData() {

}

SectionData::~SectionData() {

}

void SectionData::initValues(const string& _resultFolderPath, const string& _bathyFolderPath, const string& _bathyName) {
	this->gr.initValues(_resultFolderPath, _bathyFolderPath, _bathyName);
}

void SectionData::initSectionData(const vector<Point>& _vPoints) {
	// 根据传入的两个点的坐标，计算出所在直线的公示
	// y = kx + b
	// k = (y2 - y1) / (x2 - x1)
	// b = y1 - k * x1
	
	for (size_t i = 0; i < (_vPoints.size() / 2); i++) {
		double k = (_vPoints[i * 2 + 1].y - _vPoints[i * 2].y) / (_vPoints[i * 2 + 1].x - _vPoints[i * 2].x);
		double b = _vPoints[i * 2].y - k * _vPoints[i * 2].x;
		//cout << "k = " << k << " b = " << b << endl;
		this->calSectionData(k, b);
	}
	for (size_t i = 0; i < this->allSections.size(); i++) {
		for (size_t j = 0; j < this->allSections[i].size(); j++) {
			cout << this->allSections[i][j].x << " " << this->allSections[i][j].y << endl;
		}
		cout << endl;
	}
}

void SectionData::calSectionData(double _k, double _b) {
	/*
		传入的k和b是断面的直线方程的k和b
		然后根据bathy文件的头部信息，获取到原点坐标xorign,yorigin
		将xorign + cellsize * x作为横坐标代入直线方程，得到y值
		判断得到的y是几倍的cellsize，即为行号，1.1倍的cellsize即为第二行
		
	*/
	// y1 = k * x1 + b
	vector<Point> vSections;
	for (size_t i = 0; i < this->gr.ncols; i++) {
		cout << "i = " << i << endl;
		double y = _k * (this->gr.xllcorner + this->gr.cellSize * i) + _b;
		double yushu = (y - this->gr.yllcorner) / this->gr.cellSize;
		cout << "yushu = " << yushu << endl;
		int nrow = int (yushu);
		// 由于坐标表示的是网格的中心点，所以判断的时候，要加上0.5
		if (y - this->gr.yllcorner - nrow * this->gr.cellSize > this->gr.cellSize / 2) {
			nrow++;
		}
		// 根据行列号，计算出对应的坐标
		Point p = this->gr.getPointCoor(i, nrow);
		//cout << "nrow = " << nrow << " i = " << i << endl;
		vSections.push_back(p);
		if (this->isSectionData(nrow + 1, i, _k, _b)) {
			Point p1 = this->gr.getPointCoor(nrow + 1, i);
			//cout << "nrow + 1 = " << nrow + 1 << " i = " << i << endl;
			vSections.push_back(p1);
		}
		if (this->isSectionData(nrow - 1, i, _k, _b)) {
			Point p2 = this->gr.getPointCoor(nrow - 1, i);
			//cout << "nrow - 1 = " << nrow - 1 << " i = " << i << endl;
			vSections.push_back(p2);
		}
		//system("pause");
	}
	this->allSections.push_back(vSections);
}

bool SectionData::isSectionData(double _nrow, double _ncol, double _k, double _b)
{
	// 根据传入的行列号,先得到对应的坐标
	Point p = this->gr.getPointCoor(_nrow, _ncol);
	cout << "p.x = " << p.x << " p.y = " << p.y << endl;
	// 坐标如果有小于原点的横坐标或者纵坐标，直接返回false
	if (p.x < this->gr.xllcorner || p.y < this->gr.yllcorner) {
		return false;
	}

	// 然后根据直线方程，判断这个点到直线的距离是否小于根号二的cellsize/2，是则返回true，否则返回false
	// 直线方程是y = kx + b
	// 到直线的距离是 abs(kx - y + b) / sqrt(k^2 + 1)
	double dis = abs(_k * p.x - p.y + _b) / sqrt(_k * _k + 1);
	cout << "_ncol = " << _ncol << " _nrow = " << _nrow << endl;
	cout << "_k = " << _k << " _b = " << _b << endl;
	cout << "p.x = " << p.x << " p.y = " << p.y << endl;
	cout << "d2s = " << sqrt(2) * this->gr.cellSize / 2 << endl;
	cout << "dis = " << dis << endl;
	system("pause");
	//if (dis < 1.414214 * this->gr.cellSize / 2) {
	if (dis < sqrt(2) * this->gr.cellSize / 2) {		
		return true;
	}
	return false;
}
