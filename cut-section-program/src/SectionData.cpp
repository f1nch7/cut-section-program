#include "../include/SectionData.h"


SectionData::SectionData()
{
}

SectionData::~SectionData()
{
}

void SectionData::initValues(const string& _resultFolderPath, const string& _bathyFolderPath, const string& _bathyName) {
	this->gr.initValues(_resultFolderPath, _bathyFolderPath, _bathyName);
}
