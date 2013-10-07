#pragma once

#include <vector>
using namespace std;

#define ALL_BYTES       256 
#define END_FLAG32      0x80000000

typedef int (*JMPTABLE_FIX)[ALL_BYTES];

JMPTABLE_FIX CreateJumpTableFix(vector<CString> patternTable);

char* MultiSearchFix(char *p, int nLen, JMPTABLE_FIX pJmpTable, int &nIdx);
