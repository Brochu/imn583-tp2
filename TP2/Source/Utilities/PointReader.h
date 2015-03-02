#ifndef POINT_READER_H_
#define POINT_READER_H_

#include <string>
#include <vector>

#include "../Foundation/Vector3.h"

using namespace std;

vector<Vector3> ReadPoints(const string &ao_FileName);

#endif //POINT_READER_H_