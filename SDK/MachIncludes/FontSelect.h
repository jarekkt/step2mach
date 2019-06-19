#pragma once
#include "afxwin.h"
#include "OXRoundedButton.h"
#include "OXFontPickerButton.h"



// FontSelect dialog

class FontSelect : public CDialog
{
	DECLARE_DYNAMIC(FontSelect)

public:
	FontSelect(CWnd* pParent = NULL);   // standard constructor
	virtual ~FontSelect();

CFont m_font;
COLORREF m_clrText;
CFont m_font1;
COLORREF m_clrText1;
CFont m_font2;
COLORREF m_clrText2;

// Dialog Data
	enum { IDD = IDD_FONTS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	COXFontPickerButton m_DRO;
	COXFontPickerButton m_Label;
	COXFontPickerButton m_Code;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedDrofont();
	afx_msg void OnBnClickedDrolabel();
};
