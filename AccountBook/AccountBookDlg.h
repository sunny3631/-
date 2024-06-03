
// AccountBookDlg.h: 헤더 파일
//

#pragma once
#include<afxwin.h>
typedef signed long int Long;

// CAccountBookDlg 대화 상자
class CAccountBookDlg : public CDialogEx
{
// 생성입니다.
public:
	CAccountBookDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ACCOUNTBOOK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


	/*afx_msg void OnEnChangeEdit3();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	CButton m_BUTTONENTER;
	CButton n_BUTTTONCORRECT;
	CButton m_BUTTONCANCEL;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnEnChangeEdit2();
	CString GetCode(Long index);
public:
	CString Getcode(Long index);
	void Insert(Long index);
	void Load();
	void Save();
	void Modify(Long index);*/
public:
	
	CListCtrl m_IcSpend;
	CComboBox m_cbSpendIncome;
	CEdit m_edMoney;
	CComboBox m_cbMainCategory;
	CComboBox m_cbSubCategory;
	CEdit m_edMemo;
	CDateTimeCtrl m_dtpDate;
	CStatic m_stDisp;

	int m_iSelect;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonMake();
	afx_msg void OnBnClickedButtonModify();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnNMClickListSpend(NMHDR* pNMHDR, LRESULT* pResult);

	void DisplaySum();
	
	afx_msg void OnStnClickedStaticDisp();
};
