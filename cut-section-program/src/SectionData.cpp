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
		�жϵõ���y�Ǽ�����cellsize����Ϊ�кţ�1.1����cellsize��Ϊ��1��
		
	*/
	// y1 = k * x1 + b
	vector<Point> vSections;
	for (size_t i = 0; i < this->gr.ncols; i++) {
		//cout << "��ǰX�� i = " << i << endl;
		//cout << "����ֱ�� y = " << _k << "x + " << _b << endl;
		double newY = _k * (this->gr.xllcorner + this->gr.cellSize * i) + _b; // �������ǰX��Ӧ��Y
		//cout << "�����x����ֱ�ߵõ�newY = " << newY << endl;
		int nrow = (newY - this->gr.yllcorner) / this->gr.cellSize; // �����ϼ��������񾫶�
		// �������кţ��������Ӧ������
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
	//// ���ݴ�������к�,�ȵõ���Ӧ������
	//Point current_point = this->gr.getPointCoor(_nrow, _ncol);
	//cout << "�������� p.x = " << current_point.x << " p.y = " << current_point.y << endl;
	//// ���������С��ԭ��ĺ�������������ֱ꣬�ӷ���false
	//if (current_point.x < this->gr.xllcorner || current_point.y < this->gr.yllcorner) {
	//	cout << "coor error" << endl << endl;
	//	return false;
	//}

	//// Ȼ�����ֱ�߷��̣��ж�����㵽ֱ�ߵľ����Ƿ�С�ڸ��Ŷ���cellsize/2�����򷵻�true�����򷵻�false
	//// ֱ�߷�����y = kx + b
	//// ��ֱ�ߵľ����� abs(kx - y + b) / sqrt(k^2 + 1)
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

	// ���ֱ���Ƿ����������߽��ཻ
	double yLeft = _k * left + _b;
	if (yLeft >= bottom && yLeft <= top) {
		return true;
	}

	// ���ֱ���Ƿ���������ұ߽��ཻ
	double yRight = _k * right + _b;
	if (yRight >= bottom && yRight <= top) {
		return true;
	}

	// ���ֱ���Ƿ���������±߽��ཻ
	double xBottom = (bottom - _b) / _k;
	if (xBottom >= left && xBottom <= right) {
		return true;
	}

	// ���ֱ���Ƿ���������ϱ߽��ཻ
	double xTop = (top - _b) / _k;
	if (xTop >= left && xTop <= right) {
		return true;
	}

	// ���ֱ����������κ�һ�߶�û�н��㣬�򲻴�������
	return false;
}
