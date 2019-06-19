#pragma once


// probeconfig dialog

class probeconfig : public CDialog
{
	DECLARE_DYNAMIC(probeconfig)

public:
	probeconfig(CWnd* pParent = NULL);   // standard constructor
	virtual ~probeconfig();

// Dialog Data
	enum { IDD = IDD_PROBECONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	double m_length;
	double m_width;
	double m_Xstepover;
	double m_Ystepover;
	double m_probedist;
	double m_clearance;
	double m_feedrate;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeFeedrate();
	afx_msg void OnEnChangeYstepover();
	afx_msg void OnEnChangeProbedist();
	double m_ProbeRad;
	int m_Type;
	double m_ProbeStuck;
};
