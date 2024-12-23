#include "../include/GastResult.h"

int main() {
    
    string datFolderPath = "input"; // 存放DAT文件的 文件夹 路径

    Point oriP; //  截取断面的 起始点
    oriP.x = 0;
    oriP.y = 0;
    Point markP; // 截取断面的 终点
    markP.x = 50.12;
    markP.y = 50.12;

    // 1- 获取所有 result*s.dat 文件的路径
    GastResult gr;
    gr.setFolderPath(datFolderPath);
    vector<string> datFilePaths = gr.getAllDatPaths();

    // 2- 筛选出当前路径

    

    return 0;
}
