

  
#pragma once


// Monitoring

class Monitoring : public CWnd
{
	DECLARE_DYNAMIC(Monitoring)

public:
	Monitoring();

	void     SetWords();
	virtual ~Monitoring();

	G100Message MonitorMess;

protected:
	DECLARE_MESSAGE_MAP()
public:
	void Update(void);
	void UpdateMasks(void);
	void OnMonitor(short curr, DWORD hBits);
	void OnMonitorMessage( WTMonitor *mon );
	void LimitHomeActivated(int x);
	void DoEmerg();
	void ProbeHit();
	void CompleteSequences();
	void StartHome( int axis );
	void EndHome( int axis );
	void DoOffset( int mask );
};


