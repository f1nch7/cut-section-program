#include "../include/GastResult.h"

int main() {
    
    string datFolderPath = "input"; // ���DAT�ļ��� �ļ��� ·��

    Point oriP; //  ��ȡ����� ��ʼ��
    oriP.x = 0;
    oriP.y = 0;
    Point markP; // ��ȡ����� �յ�
    markP.x = 50.12;
    markP.y = 50.12;

    // 1- ��ȡ���� result*s.dat �ļ���·��
    GastResult gr;
    gr.setFolderPath(datFolderPath);
    vector<string> datFilePaths = gr.getAllDatPaths();

    // 2- ɸѡ����ǰ·��

    

    return 0;
}
