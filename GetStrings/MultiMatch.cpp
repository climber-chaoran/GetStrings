#include "stdafx.h"
#include "MultiMatch.h"
#include <assert.h>

void FillTableFix(int *p, int n)
{
    for (int i = 0; i < ALL_BYTES; i++)
    {
        assert(p[i] == 0);
        p[i] = n;
    }
}

JMPTABLE_FIX CreateJumpTableFix(vector<CString> patternTable)
{
    int             nTotalLen   = 0;
    int             nNextRow    = 0;
    int             nCount      = patternTable.size();
    JMPTABLE_FIX    pJmpTab     = NULL;

    for (int i = 0; i < nCount; i++)
    {
        nTotalLen += patternTable[i].GetLength();
    }
    nTotalLen -= nCount-1;//for reason 1

    pJmpTab = (JMPTABLE_FIX)malloc(nTotalLen*ALL_BYTES*sizeof(int));
    if (!pJmpTab)
    {
        return pJmpTab;
    }
    memset(pJmpTab, 0, nTotalLen*ALL_BYTES*sizeof(int));

    for (int i = 0; i < nCount; i++)
    {
        int nCurRow = 0;
        for (int j = 0; j < patternTable[i].GetLength(); j++)
        {
            byte cSign   = patternTable[i].GetAt(j);
            int cNext   = pJmpTab[nCurRow][cSign];
            if (cNext == 0)
            {
                if (j == patternTable[i].GetLength()-1)//the last character of the pattern, and the inner loop will over
                {
                    pJmpTab[nCurRow][cSign] = i | END_FLAG32;// 'i' indicate the pattern's number
                }
                else
                {
                    nNextRow++;//need add
                    pJmpTab[nCurRow][cSign] = nNextRow;
                }
                nCurRow = nNextRow;
            } 
            else
            {
                //assert(0 == (cNext & END_FLAG32));//if reach a end position, the prefix of current pattern is another pattern
                if (j == patternTable[i].GetLength()-1)
                {
                    pJmpTab[nCurRow][cSign] = i | END_FLAG32;// 'i' indicate the pattern's number
                }
                if (0 != (cNext & END_FLAG32) || j == patternTable[i].GetLength()-1)
                {
                    AfxMessageBox("发现重复数据！");
                    AfxMessageBox(patternTable[i]);
                    break;
                }
                nCurRow = cNext;
            }
        }
    }
    return pJmpTab;
}

char* MultiSearchFix(char *p, int nLen, JMPTABLE_FIX pJmpTable, int &nIdx)
{
    for (int nStart = 0; nStart < nLen; nStart++)
    {
        for (int i = nStart, nRow = 0; i < nLen; i++)
        {
            int nNext = pJmpTable[nRow][(UCHAR)p[i]];
            if (0 == nNext)
            {
                break;
            }
            //check whether is end of pattern or not
            if (nNext & END_FLAG32)
            {
                nIdx = nNext & (~END_FLAG32);
                return &p[i];
            }
            nRow = nNext;
        }
    }
    return NULL;
}