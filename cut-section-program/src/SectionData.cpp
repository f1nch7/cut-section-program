#include "../include/SectionData.h"


SectionData::SectionData() {

}

SectionData::~SectionData() {

}

void SectionData::initValues(const string& _resultFolderPath, const string& _bathyFolderPath, const string& _bathyName) {
	this->gr.initValues(_resultFolderPath, _bathyFolderPath, _bathyName);
}

void SectionData::initSectionData(const vector<Point>& _vPoints) {
	// ���ݴ��������������꣬���������ֱ�ߵĹ�ʾ
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
		�����k��b�Ƕ����ֱ�߷��̵�k��b
		Ȼ�����bathy�ļ���ͷ����Ϣ����ȡ��ԭ������xorign,yorigin
		��xorign + cellsize * x��Ϊ���������ֱ�߷��̣��õ�yֵ
		�жϵõ���y�Ǽ�����cellsize����Ϊ�кţ�1.1����cellsize��Ϊ�ڶ���
		
	*/
	// y1 = k * x1 + b
	vector<Point> vSections;
	for (size_t i = 0; i < this->gr.ncols; i++) {
		cout << "i = " << i << endl;
		double y = _k * (this->gr.xllcorner + this->gr.cellSize * i) + _b;
		double yushu = (y - this->gr.yllcorner) / this->gr.cellSize;
		cout << "yushu = " << yushu << endl;
		int nrow = int (yushu);
		// ���������ʾ������������ĵ㣬�����жϵ�ʱ��Ҫ����0.5
		if (y - this->gr.yllcorner - nrow * this->gr.cellSize > this->gr.cellSize / 2) {
			nrow++;
		}
		// �������кţ��������Ӧ������
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
	// ���ݴ�������к�,�ȵõ���Ӧ������
	Point p = this->gr.getPointCoor(_nrow, _ncol);
	cout << "p.x = " << p.x << " p.y = " << p.y << endl;
	// ���������С��ԭ��ĺ�������������ֱ꣬�ӷ���false
	if (p.x < this->gr.xllcorner || p.y < this->gr.yllcorner) {
		return false;
	}

	// Ȼ�����ֱ�߷��̣��ж�����㵽ֱ�ߵľ����Ƿ�С�ڸ��Ŷ���cellsize/2�����򷵻�true�����򷵻�false
	// ֱ�߷�����y = kx + b
	// ��ֱ�ߵľ����� abs(kx - y + b) / sqrt(k^2 + 1)
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
