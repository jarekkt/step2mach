#ifndef _cmd_h
#define _cmd_h

#include <string>

class cmd_cCmd {
public:
	cmd_cCmd(char *[],  char * = "");

	char * Arg()    { return m_pArg; }
	char   Option() { return m_Option; }
	void   Reset()  { m_ppCurrentArg = m_ppArgV; }
	char   Next();

private:
	char    m_Option;
	char *  m_pArg;
	char ** m_ppCurrentArg;
	char  * m_pOptionList;
	char ** m_ppArgV;
};

#endif
