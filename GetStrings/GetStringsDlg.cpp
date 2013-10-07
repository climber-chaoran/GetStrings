
// GetStringsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GetStrings.h"
#include "GetStringsDlg.h"
#include "crc/crc.h"
#include <assert.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CGetStringsDlg 对话框




CGetStringsDlg::CGetStringsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetStringsDlg::IDD, pParent), m_jump_table(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CGetStringsDlg::~CGetStringsDlg()
{
    free(m_jump_table);
    m_jump_table = NULL;
}

void CGetStringsDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_CtrlList);
}

BEGIN_MESSAGE_MAP(CGetStringsDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON1, &CGetStringsDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CGetStringsDlg 消息处理程序
unsigned _stdcall ThreadFun(void *p)
{
    CGetStringsDlg *pDlg = (CGetStringsDlg*)p;
    int i = 0;
    pDlg->m_CtrlList.SetRedraw(FALSE);
    while (TRUE)
    {
        Sleep(300);
        pDlg->m_CtrlList.InsertItem(0, "abcd");
        i++;
        if (i == 10)
        {
            pDlg->m_CtrlList.SetRedraw(TRUE);
            pDlg->m_CtrlList.SetRedraw(FALSE);
            i = 0;
        }
    }
    return 1;
}

BOOL CGetStringsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    m_CtrlList.InsertColumn(0, "字符串", LVCFMT_LEFT, 500);
    m_CtrlList.InsertColumn(1, "序号", LVCFMT_LEFT, 50);
    m_CtrlList.InsertColumn(2, "地址", LVCFMT_LEFT, 100);
    m_CtrlList.SetExtendedStyle((m_CtrlList.GetExStyle() | LVS_EX_FULLROWSELECT) & ~(LVS_EX_CHECKBOXES));

    PrepareKeyWords();

    //_beginthreadex(NULL, 0, ThreadFun, this, 0, NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGetStringsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGetStringsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGetStringsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//void CGetStringsDlg::OnBnClickedButton1()
//{
//    // TODO: Add your control notification handler code here
//    //WCHAR ch[] = {0x6309, 0x94ae, 0x0031, 0x4e00, 0x0033, 0x0000};
//    WCHAR ch[] = L"一不可以是测试程序吗sunnia一nzhong";
//
//    char mulCh[256] = {0};
//    //WideCharToMultiByte(CP_ACP, 0x400, ch, _countof(ch), mulCh, _countof(mulCh), NULL, NULL);
//    WideCharToMultiByte(0x3a8, 0x400, ch, _countof(ch), mulCh, _countof(mulCh), NULL, NULL);
//
//}

void CGetStringsDlg:: OnBnClickedButton1()
{
    // TODO: Add your control notification handler code here
    GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
    GetStrings();
    GetDlgItem(IDC_BUTTON1)->EnableWindow();
}

void CGetStringsDlg:: GetStrings()
{
    WCHAR ch[] = L"一不可以是测试程序吗sunnia一nzhong";
    //E:/360/analyze_tool/ViewClound/bin/ViewClound_d.exe
    //D:\work\testMFC\Release\testMFC.exe
    //CHAR chFile[] = "C:\\Users\\sunnianzhong\\Desktop\\noname";
    //CHAR chFile[] = "D:\\download\\vax10.7.1908\\VA_X_Setup1908.exe";
    CHAR chFile[] = "E:\\360\\GetStrings\\Debug\\GetStrings.exe";
    //CHAR chFile[] = "E:/360/analyze_tool/ViewClound/bin/CloundPlug_d.dll";
    //CHAR chFile[] = "D:\\work\\testMFC\\Release\\testMFC.exe";
    HANDLE hFile = CreateFile(chFile, GENERIC_READ, FILE_SHARE_READ , NULL, 
                    OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL , NULL);
    if (INVALID_HANDLE_VALUE == hFile)
    {
        return;
    }

    int nLen = GetFileSize( hFile, NULL );

    if (0 == nLen )
    {
        return;
    }

    HANDLE hMap = CreateFileMapping( hFile, NULL , PAGE_READONLY, 0, nLen, NULL);

    UCHAR *pMap = (UCHAR*) MapViewOfFile(hMap , FILE_MAP_READ, 0, 0, nLen);
    if (NULL == pMap)
    {
        int n = GetLastError();
        return;
    }

    GetStringsFromMemory (pMap, nLen);


    if (pMap )
    {
        UnmapViewOfFile(pMap );
    }
    if (hMap )
    {
        CloseHandle(hMap );
    }
    CloseHandle(hFile );
}

void CGetStringsDlg::SaveList()
{
    FILE *pFile = fopen("strings.txt", "wb");
    if (NULL == pFile)
    {
        return;
    }
    for (int i = 0; i < m_CtrlList.GetItemCount(); i++)
    {
        CString cs = m_CtrlList.GetItemText(i, 0);
        fwrite(cs, cs.GetLength(), 1, pFile);
        fwrite("\r\n", 2, 1, pFile);
    }
    fclose(pFile);
}

void CGetStringsDlg:: GetStringsFromMemory (UCHAR * pMap, int nLen)
{
    m_CtrlList.DeleteAllItems();
    m_CtrlList.SetRedraw(FALSE);
    GetAsciiStrings2(pMap , nLen);
    GetUnicodeStrings2(pMap, pMap , nLen);
    GetUnicodeStrings2(pMap, pMap+1 , nLen-1);
    //GetAsciiStrings(pMap , nLen);
    //GetUnicodeStrings(pMap, pMap , nLen);
    //GetUnicodeStrings(pMap, pMap+1 , nLen-1);
    SaveList();
    m_CtrlList.SetRedraw(TRUE);
}

void CGetStringsDlg:: GetAsciiStrings2(UCHAR *pMap, int nLen)
{
    UCHAR *pStart = NULL;
    int nStringsLen = 0;
    int nContiuneMultiByte = 0;
    int nMaxMultiByteCount = 0;
    int nContiuneAsciiByte = 0;
    int nMaxAsciiByteCount = 0;

    for (int i = 0; i < nLen; i++)
    {
        if (pMap[i] >= 0x20 && pMap[i] <= 0x7e)
        {
            if (nMaxMultiByteCount < nContiuneMultiByte)
            {
                nMaxMultiByteCount = nContiuneMultiByte;
            }
            nContiuneMultiByte = 0;
            if (0 == nStringsLen)
            {
                pStart = &pMap[i];
            }
            nContiuneAsciiByte++;
            nStringsLen++;
        }
        else if (i+1 < nLen && pMap[i] >= 0xb0 &&  pMap[i] <= 0xf7 && 
                               pMap[i+1] >= 0xa0)//0xb0a0 - 0xf7ff
        {
            if (nMaxAsciiByteCount < nContiuneAsciiByte)
            {
                nMaxAsciiByteCount = nContiuneAsciiByte;
            }
            nContiuneAsciiByte = 0;
            if (0 == nStringsLen)
            {
                pStart = &pMap[i];
            }
            nContiuneMultiByte++;
            nStringsLen += 2;
            i++;
        }
        else
        {
            if (nStringsLen >= 5 && 
                (nContiuneAsciiByte >= 5 || nMaxAsciiByteCount >= 5 ||
                 nContiuneMultiByte >= 3 || nMaxMultiByteCount >= 3))
            {
                FindOneAsciiString(pMap, pStart, &pStart[nStringsLen-1]);
            }
            nContiuneMultiByte = 0;
            nMaxMultiByteCount = 0;
            nContiuneAsciiByte = 0;
            nMaxAsciiByteCount = 0;
            nStringsLen = 0;
        }
    }
}

void CGetStringsDlg:: GetAsciiStrings(UCHAR *pMap, int nLen)
{
    UCHAR *pStart = pMap;
    UCHAR *pLast = pMap+ nLen-1;
    
    while (TRUE)
    {
        while('\0' == *pStart && pStart <= pLast )
            pStart++;
        if (pStart >= pLast)
            return;

        UCHAR *pEnd = pStart;
        while('\0' != *pEnd && '\r' != *pEnd && pEnd <= pLast)
        {
            pEnd++;
        }
        if (pEnd > pLast)
        {
            pEnd = pLast;
        }

        UCHAR *pBegin = ('\0' == *pEnd || '\r' == *pEnd) ? pEnd-1 : pEnd ;
        UCHAR *pTail = pBegin;
        int nNumber = 3;
        while (TRUE)
        {
            while (pBegin >= pStart)
            {
                if (*pBegin >= 0x1f && *pBegin <= 0x7f)
                {
                    pBegin--;
                }
                else if (pBegin > pStart && *pBegin >= 0xa0 && *(pBegin-1) >= 0xa0)
                {
                    pBegin -= 2;
                }
                else
                {
                    break;
                }
            }
            pBegin++;

            if (pTail - pBegin >= nNumber)// is a string
            {
                FindOneAsciiString(pMap, pBegin, pTail);
            }
            pBegin = pTail = pBegin-2;
            nNumber = 5;
            if (pBegin <= pStart)
            {
                break;
            }
        }
        pStart = pEnd+1;
    }
}

void CGetStringsDlg:: GetUnicodeStrings2(UCHAR * pBase, UCHAR *pMap, int nLen )
{
    WCHAR *pBegin = (WCHAR*)pMap;
    WCHAR *pStart = NULL;
    int nWcharCount = nLen/2;
    int nStringLen = 0;

    for (int i = 0; i < nWcharCount; i++)
    {
        if ((pBegin[i] >= 0x20 && pBegin[i] <= 0x7e) || 
            (pBegin[i] >= 0x4e00 && pBegin[i] <= 0x9fbf))
        {
            if (0 == nStringLen)
            {
                pStart = &pBegin[i];
            }
            nStringLen++;
        }
        else
        {
            if (nStringLen >= 5)
            {
                FindOneUnicodeString(pBase, pStart, &pStart[nStringLen-1]);
            }
            nStringLen = 0;
        }
    }
}

void CGetStringsDlg:: GetUnicodeStrings(UCHAR * pBase, UCHAR *pMap, int nLen )
{
    WCHAR *pStart = (WCHAR*)pMap;
    WCHAR *pLast = (WCHAR*)(pMap+nLen-2);

    while (TRUE)
    {
        while (L'\0' == pStart && pStart <= pLast)
            pStart++;
        if (pStart >= pLast)
            return;

        WCHAR *pEnd = pStart;

        while (L'\0' != *pEnd && L'\r' != *pEnd && pEnd <= pLast)
        {
            //pEnd = (WCHAR*)(((char*)pEnd)+1);
            pEnd++;
        }
        if (pEnd > pLast)
        {
            pEnd = pLast;
        }

        WCHAR *pBegin = (L'\0' == *pEnd || L'\r' == *pEnd) ? pEnd-1 : pEnd ;
        //WCHAR *pBegin = (WCHAR*)(((DWORD)pEnd)-1);
        WCHAR *pTail = pBegin;

        while (pBegin >= pStart)
        {
            if (*pBegin >= 0x1f && *pBegin <= 0x7f)
            {
                pBegin--;
            }
            else if (*pBegin >= 0x4e00 && *pBegin <= 0x9fbf)
            {
                pBegin--;
            }
            else
            {
                break;
            }
        }
        pBegin++;

        if (pTail - pBegin >= 3)// is a string
        {
            FindOneUnicodeString(pBase, pBegin, pTail);
        }
        pStart = pEnd+1;
    }
}

void CGetStringsDlg::FindOneAsciiString(UCHAR *pBase, UCHAR *pStart, UCHAR *pEnd)
{
    CHAR chOrg[256] = {0};
    CHAR chLow[256] = {0};
    int nLen = (pEnd-pStart+1) > _countof(chOrg)-1 ? _countof(chOrg)-1 : pEnd-pStart+1;
    memcpy(chOrg, pStart, nLen);
    memcpy(chLow, pStart, nLen);
    _strlwr_s(chLow, sizeof(chOrg));

    //DWORD dwNum = 0;
    //DWORD dwCrc32 = GetCrc32(dwNum, (UCHAR*)ch, nLen);
    //if (m_Crc32SetAscii.end() != m_Crc32SetAscii.find(dwCrc32))
    //{
    //    return;
    //}
    //m_Crc32SetAscii.insert(dwCrc32);

    InsertList(chOrg, chLow, nLen, (void*)(pStart-pBase));
}

void CGetStringsDlg::FindOneUnicodeString(UCHAR *pBase, WCHAR *pStart, WCHAR *pEnd)
{
    WCHAR wch[256] = {0};
    CHAR chOrg[256*2] = {0};
    CHAR chLow[256*2] = {0};
    int nLen = (pEnd-pStart+1) > _countof(wch)-1 ? _countof(wch)-1 : pEnd-pStart+1;
    memcpy(wch, pStart, nLen*sizeof(WCHAR));
    WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, wch, nLen, chOrg, _countof(chOrg), NULL, NULL);
    nLen = strlen(chOrg);
    strcpy_s(chLow, _countof(chLow), chOrg);
    _strlwr_s(chLow, sizeof(chLow));

    //DWORD dwNum = 0;
    //DWORD dwCrc32 = GetCrc32(dwNum, (UCHAR*)ch, nLen);
    //if (m_Crc32SetUnicode.end() != m_Crc32SetUnicode.find(dwCrc32))
    //{
    //    return;
    //}
    //m_Crc32SetUnicode.insert(dwCrc32);

    InsertList(chOrg, chLow, nLen, (void*)((UCHAR*)pStart-pBase));
}

void CGetStringsDlg::InsertList(char *chOrg, char *chLow, int nLen, void* pStart)
{    
    CHAR chTemp[256] = {0};
    int nIdx = -1;
    char *pFind = MultiSearchFix(chLow, nLen, m_jump_table, nIdx);

    int nCount = m_CtrlList.GetItemCount();
    if (pFind && nIdx != -1)
    {
        nCount = 0;
    }
    m_CtrlList.InsertItem(nCount, chOrg);
    sprintf_s(chTemp, _countof(chTemp), "%d", nCount+1);
    m_CtrlList.SetItemText(nCount, 1, chTemp);
    sprintf_s(chTemp, _countof(chTemp), "%04d", pStart);
    m_CtrlList.SetItemText(nCount, 2, chTemp);

}

void CGetStringsDlg::PrepareKeyWords()
{
    char g_strIniPath[] = "E:/360/analyze_tool/ViewClound/bin/config.ini";
    char szIniData[MAX_PATH] = {0};
    CString strTemp;
    char szKeyValue[16] = "f1";
    int index = 1;
    while(0 != GetPrivateProfileString("feature", szKeyValue, NULL, szIniData, MAX_PATH, g_strIniPath))
    {
        _strlwr_s(szIniData, sizeof(szIniData));
        strTemp.Format("%s", szIniData);
        if (!strTemp.IsEmpty())
        {
            m_vecKeyWord.push_back(strTemp);
        }
        index++;
        sprintf_s(szKeyValue, sizeof(szKeyValue), "%s%d", "f", index);
    }

    //建立查询表格
    if (m_jump_table)
    {
        free(m_jump_table);
    }
    m_jump_table = CreateJumpTableFix(m_vecKeyWord);
    if (NULL == m_jump_table)
    {
        return;
    }

    //for test
    for (int i = 0; i < (int)m_vecKeyWord.size(); i++)
    {
        int nIdx = -1;
        char *pFind = MultiSearchFix(m_vecKeyWord[i].GetBuffer(), m_vecKeyWord[i].GetLength(), m_jump_table, nIdx);
        assert(pFind);
        assert(nIdx != -1);
    }
    //test end

}
