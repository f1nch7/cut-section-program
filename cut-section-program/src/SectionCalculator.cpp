 //#include "./include/SectionCalculator.h"
 //#include <iostream>
 //#include <fstream>

 //SectionCalculator::SectionCalculator() {}

 //void SectionCalculator::calculateSections(const std::string& inputDir, const std::vector<std::string>& fileNames) {
 //    std::vector<std::vector<double>> modelData = GastResult::readData(inputDir + "/" + fileNames[0]);

 //    for (const auto& file : fileNames) {
 //        Section section;

 //        // ������ض������ݲ�����
 //        // ���磺���ļ��������ط���ȡ���������
 //        section.addPoint(Point(9.96, 0.06, 100.0));  // ���ʾ������
 //        section.addPoint(Point(9.96, 0.96, 110.0));  // ���ʾ������

 //        calculateSectionFlowAndArea(section, modelData);
 //    }

 //    writeResultsToFile("SectionResults.txt");
 //}

 //void SectionCalculator::calculateSectionFlowAndArea(const Section& section, const std::vector<std::vector<double>>& modelData) {
 //    std::vector<double> QSec, A, Width;
 //    GastResult::computeSectionData(section.getPoints(), modelData, QSec, A, Width);

 //    // ���������洢�� sectionOutput ��
 //    sectionOutput.push_back(QSec);  // �洢������
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
