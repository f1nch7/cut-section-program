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
		判断得到的y是几倍的cellsize，即为行号，1.1倍的cellsize即为第1行
		
	*/
	// y1 = k * x1 + b
	vector<Point> vSections;
	for (size_t i = 0; i < this->gr.ncols; i++) {
		//cout << "当前X是 i = " << i << endl;
		//cout << "断面直线 y = " << _k << "x + " << _b << endl;
		double newY = _k * (this->gr.xllcorner + this->gr.cellSize * i) + _b; // 计算出当前X对应的Y
		//cout << "网格的x代入直线得到newY = " << newY << endl;
		int nrow = (newY - this->gr.yllcorner) / this->gr.cellSize; // 计算上几倍的网格精度
		// 根据行列号，计算出对应的坐标
		if (this->isSectionData(nrow, i, _k, _b)) {
			Point p = this->gr.getPointCoor(nrow, i);
			vSections.push_back(p);
		}
		
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
	//// 根据传入的行列号,先得到对应的坐标
	//Point current_point = this->gr.getPointCoor(_nrow, _ncol);
	//cout << "相邻网格 p.x = " << current_point.x << " p.y = " << current_point.y << endl;
	//// 坐标如果有小于原点的横坐标或者纵坐标，直接返回false
	//if (current_point.x < this->gr.xllcorner || current_point.y < this->gr.yllcorner) {
	//	cout << "coor error" << endl << endl;
	//	return false;
	//}

	//// 然后根据直线方程，判断这个点到直线的距离是否小于根号二的cellsize/2，是则返回true，否则返回false
	//// 直线方程是y = kx + b
	//// 到直线的距离是 abs(kx - y + b) / sqrt(k^2 + 1)
	//double dis = abs(_k * current_point.x - current_point.y + _b) / sqrt(_k * _k + 1);
	//cout << "_ncol = " << _ncol << " _nrow = " << _nrow << endl;
	//cout << "_k = " << _k << " _b = " << _b << endl;
	//cout << "isS p.x = " << current_point.x << " isS p.y = " << current_point.y << endl;
	//cout << "d2s = " << sqrt(2) * this->gr.cellSize / 2 << endl;
	//cout << "dis = " << dis << endl << endl;
	////if (dis < 1.414214 * this->gr.cellSize / 2) {
	//if (dis < sqrt(2) * this->gr.cellSize / 2) {
	//	cout << "zhengque!" << endl << endl;
	//	return true;
	//}
	//cout << "chaochaochaole!" << endl << endl;
	//return false;
	double left = this->gr.cellSize * _ncol;
	double right = this->gr.cellSize * _ncol + this->gr.cellSize;
	double bottom = this->gr.cellSize * _nrow;
	double top = this->gr.cellSize * _nrow + this->gr.cellSize;

	// 检查直线是否与网格的左边界相交
	double yLeft = _k * left + _b;
	if (yLeft >= bottom && yLeft <= top) {
		return true;
	}

	// 检查直线是否与网格的右边界相交
	double yRight = _k * right + _b;
	if (yRight >= bottom && yRight <= top) {
		return true;
	}

	// 检查直线是否与网格的下边界相交
	double xBottom = (bottom - _b) / _k;
	if (xBottom >= left && xBottom <= right) {
		return true;
	}

	// 检查直线是否与网格的上边界相交
	double xTop = (top - _b) / _k;
	if (xTop >= left && xTop <= right) {
		return true;
	}

	// 如果直线与网格的任何一边都没有交点，则不穿过网格
	return false;
}
