#include "PointReader.h"

#include <cstdio>

vector<Vector3> ReadPoints(const string &ao_FileName)
{
	vector<Vector3> to_PointsList;
	FILE* po_File = fopen(ao_FileName.c_str(),"r");

	int u32_PtCount = 0;

	fscanf(po_File,"%d",&u32_PtCount);

	for(int i = 0; i < u32_PtCount; ++i)
	{
		Vector3 v3_TmpVec;

		fscanf(po_File,"%f",&v3_TmpVec.X());
		fscanf(po_File,"%f",&v3_TmpVec.Y());
		fscanf(po_File,"%f",&v3_TmpVec.Z());

		to_PointsList.push_back(v3_TmpVec);
	}

	fclose(po_File);
	
	return to_PointsList;
}