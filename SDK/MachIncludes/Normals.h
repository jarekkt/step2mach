#pragma once

#include "TitleTip.h"


// Normals

class Normals : public CWnd
{
	DECLARE_DYNAMIC(Normals)

public:
	Normals();
	virtual ~Normals();

	double Conditions[50];
	double Check[50];
    bool   Normal[50];

	void LoadNormals();
	bool IsNormal(int x);
	bool IsAllNormal();
	void SaveNormals();
	bool DisplayStatus( );
	CString  Abnormal;




protected:
	DECLARE_MESSAGE_MAP()
};


