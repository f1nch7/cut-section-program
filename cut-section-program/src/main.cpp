#include "../include/SectionData.h"

int main() {
    
    string datFolderPath = "input"; // ���DAT�ļ��� �ļ��� ·��
    string bathyFolderPath = "input"; // ���DAT�ļ��� �ļ��� ·��
    /*
        vector<Point> vp = { {0,0}, {50.12,50.12} }; ��һ�������д������ͬʱ���������棬�ο�����д����
        vector<Point> vp = { {0,0}, {50.12,50.12},   // ��һ������������㣬ע������Ҫ�ж���
                             {0,0}, {50.12,50.12} }; // �ڶ�������������㡤������ �Դ�����

    */
    vector<Point> vp = {    {0,0}, {50.12,50.12}};
    SectionData sd;
    /*
        Ĭ��bathy���ļ�����  bathy.asc�����Ҫ���ģ����ڵ�������������bathy���ļ�����
        string bathyName = "bathy1025.asc";
        sd.initValues(datFolderPath, bathyFolderPath, bathyName);
    */
    sd.initValues(datFolderPath, bathyFolderPath);
    

    return 0;
}
