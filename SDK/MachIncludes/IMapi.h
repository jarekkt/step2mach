/*
 *	$Header: /common/IMapi.h 1     28/03/01 8:42p Admin $
 *
 *	$History: IMapi.h $
 * 
 * *****************  Version 1  *****************
 * User: Admin        Date: 28/03/01   Time: 8:42p
 * Created in $/common
 */
#include "mapi.h"

class CIMapi
{
public:
					CIMapi();
					~CIMapi();

	enum errorCodes
	{
		IMAPI_SUCCESS = 0,
		IMAPI_LOADFAILED,
		IMAPI_INVALIDDLL,
		IMAPI_FAILTO,
		IMAPI_FAILCC,
		IMAPI_FAILATTACH
	};

//	Attributes
	void			Subject(LPCTSTR subject);
	void			Text(LPCTSTR text)			{ m_text = text; }

	UINT			Error();
	void			From(LPCTSTR from)			{ m_from.lpszName = (LPTSTR) from; }

	static BOOL		HasEmail();

//	Operations
	BOOL			To(LPCTSTR recip);
	BOOL			Attach(LPCTSTR path, LPCTSTR name = NULL);
	
	BOOL			Send(ULONG flags = 0);

private:
	BOOL			AllocNewTo();

	MapiMessage		m_message;
	MapiRecipDesc	m_from;
	UINT			m_error;
	CString			m_text;
	LHANDLE			m_sessionHandle;

	ULONG (PASCAL *m_lpfnSendMail)(ULONG, ULONG, MapiMessage*, FLAGS, ULONG);
	ULONG (PASCAL *m_lpfnMAPILogon)(ULONG, LPTSTR, LPTSTR, FLAGS, ULONG, LPLHANDLE);
	
	static HINSTANCE m_hInstMail;
	static BOOL		m_isMailAvail;
};
