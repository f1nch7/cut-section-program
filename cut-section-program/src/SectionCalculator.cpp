 //#include "./include/SectionCalculator.h"
 //#include <iostream>
 //#include <fstream>

 //SectionCalculator::SectionCalculator() {}

 //void SectionCalculator::calculateSections(const std::string& inputDir, const std::vector<std::string>& fileNames) {
 //    std::vector<std::vector<double>> modelData = GastResult::readData(inputDir + "/" + fileNames[0]);

 //    for (const auto& file : fileNames) {
 //        Section section;

 //        // 这里加载断面数据并计算
 //        // 例如：从文件或其他地方获取断面点数据
 //        section.addPoint(Point(9.96, 0.06, 100.0));  // 添加示例数据
 //        section.addPoint(Point(9.96, 0.96, 110.0));  // 添加示例数据

 //        calculateSectionFlowAndArea(section, modelData);
 //    }

 //    writeResultsToFile("SectionResults.txt");
 //}

 //void SectionCalculator::calculateSectionFlowAndArea(const Section& section, const std::vector<std::vector<double>>& modelData) {
 //    std::vector<double> QSec, A, Width;
 //    GastResult::computeSectionData(section.getPoints(), modelData, QSec, A, Width);

 //    // 将计算结果存储到 sectionOutput 中
 //    sectionOutput.push_back(QSec);  // 存储流量等
 //}

 //void SectionCalculator::writeResultsToFile(const std::string& filename) {
 //    std::ofstream file(filename);
 //    for (const auto& row : sectionOutput) {
 //        for (size_t i = 0; i < row.size(); ++i) {
 //            file << row[i];
 //            if (i < row.size() - 1) {
 //                file << " ";
 //            }
 //        }
 //        file << "\n";
 //    }
 //}

 //const std::vector<std::vector<double>>& SectionCalculator::getSectionOutput() const {
 //    return sectionOutput;
 //}
