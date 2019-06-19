//
// FormulaParser.h: interface for the CFormulaParser class.
// Copyright: 2004, Ralf Wirtz GNU lesser license. No Licence requirements.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FORMELPARSER_H__F802A742_8772_11D1_BD24_0000C02FB5AC__INCLUDED_)
#define AFX_FORMELPARSER_H__F802A742_8772_11D1_BD24_0000C02FB5AC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define ANZFUNKTKONST 10

#include "PhysConst.h"

class CFormulaParser  
{
private:

	CPhysConst m_PhysConst; 

	//Implementation
	CString m_strFormula;
	CString m_strFunction;
	CString m_strErrortext;

	static CString g_strF;

	double m_dFunctionConstant[ANZFUNKTKONST];
	CStringArray m_strStandardFunction;

	double SignFactor(int& nPosition, CString& strCharacter);
	double Expression(int& nPosition, CString& strCharacter);
	double SimpleExpression(int& nPosition, CString& strCharacter);
	double Term(int& nPosition, CString& strCharacter);
	double Factor(int& nPosition, CString& strCharacter);
	double Char_n(int& nPosition, CString& strCharacter);
	CString strChar_(BYTE DecimalZahl);

	CString GetNextToken(CString& strSrc, const CString strDelim);
	double SINQ(double Winkel_grad);
	double COSQ(double Winkel_grad);
	double DEG(double x /* rad */) ;
	double RAD(double x /* grad */);
	double cot(double x);
	long double signl(long double x);
	double ArSinh(double x);
	double ArCosh(double x);
	double ArTanh(double x);
	double ArCoth(double x);
	double sqr(double x);

public:
	void StripFormula(CString& strFormula);
	CString GetFormula();
	void SetFormula(CString Formula);
	void SetFunctConst(int index, double val);
	
	CFormulaParser();
	virtual ~CFormulaParser();

	//Interface
	double Calculation(CString strFormula, int& ErrorPosition, CString& Errortext, BOOL strip = true);
};

#endif // !defined(AFX_FORMELPARSER_H__F802A742_8772_11D1_BD24_0000C02FB5AC__INCLUDED_)
