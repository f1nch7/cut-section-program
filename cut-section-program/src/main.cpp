#include "../include/SectionData.h"

int main() {
    
    string datFolderPath = "input"; // 存放DAT文件的 文件夹 路径
    string bathyFolderPath = "input"; // 存放DAT文件的 文件夹 路径
    /*
        vector<Point> vp = { {0,0}, {50.12,50.12} }; 是一个断面的写法，当同时有若个断面，参考如下写法：
        vector<Point> vp = { {0,0}, {50.12,50.12},   // 第一个断面的两个点，注意这里要有逗号
                             {0,0}, {50.12,50.12} }; // 第二个断面的两个点···· 以此类推

    */
    vector<Point> vp = {    {0,0}, {50.12,50.12}};
    SectionData sd;
    /*
        默认bathy的文件名是  bathy.asc，如果要更改，则在第三个参数输入bathy的文件名：
        string bathyName = "bathy1025.asc";
        sd.initValues(datFolderPath, bathyFolderPath, bathyName);
    */
    sd.initValues(datFolderPath, bathyFolderPath);
    

    return 0;
}
