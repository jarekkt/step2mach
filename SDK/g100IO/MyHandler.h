#pragma once
 
 
class MyHandler : public G100Handler {
public:

	virtual int onHalt(
		unsigned qid, 
		void * qdata, 
		G100Part * gp, 
		unsigned halt_bit,
		unsigned halt_value
		);


	virtual void onAck(
		unsigned qid, 
		void * qdata, 
		G100Part * gp
		);


	virtual void onComplete(
		unsigned qid, 
		void * qdata, 
		G100Part * gp
		);


	virtual void onEndOfQueue(
		unsigned qid, 
		void * qdata, 
		G100Part * gp
		);


	virtual void onDiscarded(
		unsigned qid, 
		void * qdata, 
		G100Part * gp
		);


	virtual void onDisconnect(
		unsigned qid, 
		void * qdata, 
		G100Part * gp,
		int reason
		);


	virtual void onConnect(
		G100Part * gp
		);


	virtual void onMsg(
		G100Part * gp,
		unsigned len,
		const char * msg
		);

	virtual void onDebug(
		const char * str
		);

	virtual void onHomed(
		unsigned qid, 
		void * qdata, 
		G100Part * gp
		);

};
