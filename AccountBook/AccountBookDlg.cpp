
// AccountBookDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "AccountBook.h"
#include "AccountBookDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
//public:
//	afx_msg void OnNMClickListSpend(NMHDR* pNMHDR, LRESULT* pResult);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	//ON_NOTIFY(NM_CLICK, IDC_LIST_SPEND, &CAboutDlg::OnNMClickListSpend)
END_MESSAGE_MAP()


// CAccountBookDlg 대화 상자



CAccountBookDlg::CAccountBookDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ACCOUNTBOOK_DIALOG, pParent)
	, m_iSelect(-1)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAccountBookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_SPEND, m_IcSpend);
	DDX_Control(pDX, IDC_COMBO_SPEND_INCOME, m_cbSpendIncome);
	DDX_Control(pDX, IDC_EDIT_MONEY, m_edMoney);
	DDX_Control(pDX, IDC_COMBO_MAIN_CATEGORY, m_cbMainCategory);
	DDX_Control(pDX, IDC_COMBO_SUB_CATEGORY, m_cbSubCategory);
	DDX_Control(pDX, IDC_EDIT_MEMO, m_edMemo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_DATE, m_dtpDate);
	DDX_Control(pDX, IDC_STATIC_DISP, m_stDisp);
}

BEGIN_MESSAGE_MAP(CAccountBookDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CAccountBookDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CAccountBookDlg::OnBnClickedCancel) 
	ON_BN_CLICKED(IDC_BUTTON_MAKE, &CAccountBookDlg::OnBnClickedButtonMake)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CAccountBookDlg::OnBnClickedButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CAccountBookDlg::OnBnClickedButtonDelete)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SPEND, &CAccountBookDlg::OnNMClickListSpend)
END_MESSAGE_MAP()


// CAccountBookDlg 메시지 처리기

BOOL CAccountBookDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_IcSpend.InsertColumn(0, _T("순서"), LVCFMT_CENTER, 50);
	m_IcSpend.InsertColumn(1, _T("날짜"), LVCFMT_CENTER, 100);
	m_IcSpend.InsertColumn(2, _T("지출/수입"), LVCFMT_CENTER, 100);
	m_IcSpend.InsertColumn(3, _T("금액"), LVCFMT_CENTER, 100);
	m_IcSpend.InsertColumn(4, _T("대분류"), LVCFMT_CENTER, 100);
	m_IcSpend.InsertColumn(5, _T("소분류"), LVCFMT_CENTER, 100);
	m_IcSpend.InsertColumn(6, _T("메모"), LVCFMT_CENTER, 400);
	m_IcSpend.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 지출/수입 콤보박스 초기화
	m_cbSpendIncome.InsertString(0, _T("지출"));
	m_cbSpendIncome.InsertString(1, _T("수입"));
	m_cbSpendIncome.SetCurSel(0);

	// 대분류 콤보박스 초기화
	m_cbMainCategory.InsertString(0, _T("월급"));
	m_cbMainCategory.InsertString(1, _T("용돈"));
	m_cbMainCategory.InsertString(2, _T("저축"));
	m_cbMainCategory.InsertString(3, _T("식비"));
	m_cbMainCategory.InsertString(4, _T("통신비"));
	m_cbMainCategory.InsertString(5, _T("교통비"));
	m_cbMainCategory.InsertString(6, _T("교육비"));
	m_cbMainCategory.SetCurSel(0);

	// 소분류 콤보박스 초기화
	m_cbSubCategory.InsertString(0, _T("알바 월급"));
	m_cbSubCategory.InsertString(1, _T("과외 월급"));
	m_cbSubCategory.InsertString(2, _T("택시비"));
	m_cbSubCategory.InsertString(3, _T("버스비"));
	m_cbSubCategory.InsertString(4, _T("배달음식"));
	m_cbSubCategory.InsertString(5, _T("약속"));
	m_cbSubCategory.SetCurSel(0);
	
	DisplaySum();
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CAccountBookDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CAccountBookDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CAccountBookDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CAccountBookDlg::OnBnClickedOk()
{
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}

void CAccountBookDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void CAccountBookDlg::OnBnClickedButtonMake()
{
	CString sSpendIncome;
	CString sMoney;
	CString sMainCategory;
	CString sSubCategory;
	CString sMemo;
	CString sDate;

	m_cbSpendIncome.GetWindowText(sSpendIncome);
	m_edMoney.GetWindowText(sMoney);
	m_cbMainCategory.GetWindowText(sMainCategory);
	m_cbSubCategory.GetWindowText(sSubCategory);
	m_edMemo.GetWindowText(sMemo);
	m_dtpDate.GetWindowText(sDate);

	CString sNo;
	int iCount = m_IcSpend.GetItemCount();
	sNo.Format(_T("%d"), iCount);
	m_IcSpend.InsertItem(iCount, sNo);
	m_IcSpend.SetItemText(iCount, 1, sDate);
	m_IcSpend.SetItemText(iCount, 2, sSpendIncome);
	m_IcSpend.SetItemText(iCount, 3, sMoney);
	m_IcSpend.SetItemText(iCount, 4, sMainCategory);
	m_IcSpend.SetItemText(iCount, 5, sSubCategory);
	m_IcSpend.SetItemText(iCount, 6, sMemo);

	DisplaySum();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CAccountBookDlg::OnBnClickedButtonModify()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iCount = m_IcSpend.GetItemCount();
	if ((-1 < m_iSelect) && (m_iSelect < iCount))
	{
		CString sSpendIncome;
		CString sMoney;
		CString sMainCategory;
		CString sSubCategory;
		CString sMemo;
		CString sDate;

		m_cbSpendIncome.GetWindowText(sSpendIncome);
		m_edMoney.GetWindowText(sMoney);
		m_cbMainCategory.GetWindowText(sMainCategory);
		m_cbSubCategory.GetWindowText(sSubCategory);
		m_edMemo.GetWindowText(sMemo);
		m_dtpDate.GetWindowText(sDate);

		m_IcSpend.SetItemText(m_iSelect, 1, sDate);
		m_IcSpend.SetItemText(m_iSelect, 2, sSpendIncome);
		m_IcSpend.SetItemText(m_iSelect, 3, sMoney);
		m_IcSpend.SetItemText(m_iSelect, 4, sMainCategory);
		m_IcSpend.SetItemText(m_iSelect, 5, sSubCategory);
		m_IcSpend.SetItemText(m_iSelect, 6, sMemo);
	}
	DisplaySum();
}


void CAccountBookDlg::OnBnClickedButtonDelete()
{
	int iCount = m_IcSpend.GetItemCount();
	if ((-1 < m_iSelect) && (m_iSelect < iCount))
	{
		m_IcSpend.DeleteItem(m_iSelect);

		
	}
	DisplaySum();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CAccountBookDlg::OnNMClickListSpend(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (IDC_LIST_SPEND == pNMItemActivate->hdr.idFrom)
	{
		int iItemCnt = m_IcSpend.GetItemCount();
		int iSelItem = pNMItemActivate->iItem;

		if ((0 <= iSelItem) && (iSelItem < iItemCnt))
		{
			m_iSelect = iSelItem;
		}
	}
	*pResult = 0;
}

void CAccountBookDlg::DisplaySum()
{
	CString sSum;
	int iSum = 0;
	int iCount = m_IcSpend.GetItemCount();

	for (int i = 0; i < iCount; i++)
	{
		CString sSpendIncome;
		sSpendIncome = m_IcSpend.GetItemText(i, 2);
		if (_T("") != sSpendIncome)
		{
			CString sMoney;
			sMoney = m_IcSpend.GetItemText(i, 3);

			if (_T("지출") == sSpendIncome) 
				iSum -= _ttoi(sMoney);
						
			else if (_T("수입") == sSpendIncome)
				iSum += _ttoi(sMoney);
		}
	}

	sSum.Format(_T("총합 %d원"), iSum);
	m_stDisp.SetWindowText(sSum);
	
	if (iSum < -200000) 
		MessageBox(_T("소비 한도를 넘어섰습니다"), _T("경고 메세지"), MB_ICONWARNING);
}


