#ifndef _CONTROLRECT_H
#define _CONTROLRECT_H

class CTracker;

struct setups{

	int Function;
	int Type;
	int Group;
	bool Delete;
	CString Text;
	CString GText;
	CString BitmapPath;
	bool    DrawButton;
	int Horiz;
	int Vert;
	CString Label;
	int WhichLed;
	int Color;
	BOOL Flash;
	BOOL RedGreen;
	int OEMCode;
	int HotKey;
	CString Format;
	int  TabGroup;
};


class CControlRect :   public CWnd
{
 

public:
	 setups   Controls;
	 void    *Object;
	 CRect   m_rect;
	 CRect   OrigRect;
 
// Controls enumerated in WindowType
	enum WindowType
	{
		enmScrollBar,
		enmStatic,
		enmButton,
		enmEdit,
		enmListBox,
		enmComboBox,
		enmStaticCounter,
		enmBitButton,
		enmJoystick,
		enmLabel,
		enmLed,
		enmMDI,
		enmGCode,
		enmTool
	};

// Can use enumerated type to create control
	BOOL Create( WindowType wndType, 
				 LPCTSTR lpszWindowName , 
				 CWnd* pParentWnd, 
				 DWORD dwStyle = WS_DISABLED, 
				 const CRect& Rect = CRect(0,0,0,0), 
				 UINT nID = 0 );	
 
// Tracks movement rectangle for control
	void Track( CWnd* pWnd, CPoint point, BOOL bAllowInvert = FALSE, CWnd* pWndClipTo = NULL );

// Sets bounding rectangle for control
	void SetRect( int x1, int y1, int x2, int y2 );
	void SetRect( const CRect & rect );

private:
// TRUE if selected
	BOOL m_bSelected;
	BOOL m_bLastSelected;
 
public:	
	bool IsSelected();
	bool Enter( int key );
	void Select();
	void DeSelect();
	bool IsVisable();
	bool DoHotKey( int key);
	void Update();
	void CloseControl();
 
	CControlRect();
	~CControlRect();

};

#endif 
