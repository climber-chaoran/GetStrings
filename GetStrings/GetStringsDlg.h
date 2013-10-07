
// GetStringsDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "MultiMatch.h"

#include <set>
#include <vector>
using namespace std;


// CGetStringsDlg 对话框
class CGetStringsDlg : public CDialog
{
// 构造
public:
    CGetStringsDlg(CWnd* pParent = NULL);	// 标准构造函数
    ~CGetStringsDlg();

// 对话框数据
	enum { IDD = IDD_GETSTRINGS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButton1();
    void GetStrings();
    void GetStringsFromMemory (UCHAR * pMap, int nLen);
    void GetAsciiStrings(UCHAR *pMap, int nLen );
    void GetAsciiStrings2(UCHAR *pMap, int nLen );

    void GetUnicodeStrings(UCHAR * pBase, UCHAR *pMap, int nLen );
    void GetUnicodeStrings2(UCHAR * pBase, UCHAR *pMap, int nLen );

    void FindOneAsciiString(UCHAR *pBase, UCHAR *pStart, UCHAR *pEnd);
    void FindOneUnicodeString(UCHAR *pBase, WCHAR *pStart, WCHAR *pEnd);
    void SaveList();
    void PrepareKeyWords();
    void InsertList(char *chOrg, char *chLow, int nLen, void* pStart);

    set<DWORD> m_Crc32SetAscii;
    set<DWORD> m_Crc32SetUnicode;
    vector<CString> m_vecKeyWord;
    JMPTABLE_FIX m_jump_table;

    CListCtrl m_CtrlList;
};
