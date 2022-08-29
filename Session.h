/*
    PortSIP 4.0
    Copyright (C) 2007 PortSIP Solutions, Inc.
   
    support@portsip.com

    Visit us at http://www.portsip.com
*/


#ifndef PORTSIP_SESSION_hxx
#define PORTSIP_SESSION_hxx



class Session
{
public:
	Session()
		:mSessionId(0)
		,mHoldSate(false)
		,mSessionState(false)
		,mConferenceState(false)
		,mRecvCallState(false)
		,mOriginCallSessionId(0)
		,mIsReferCall(false)
		,mExistEarlyMedia(false)
	{

	}
	virtual ~Session(){}

public:

	void setExistEarlyMedia(bool state)
	{
		mExistEarlyMedia = state;
	}

	bool getExistEarlyMedia()
	{
		return mExistEarlyMedia;
	}

	void setSessionId(long sessionId)
	{
		mSessionId = sessionId;
	}


	long getSessionId()
	{
		return mSessionId;
	}

	void setHoldState(bool state)
	{
		mHoldSate = state;
	}


	bool getHoldState()
	{
		return mHoldSate;
	}

	void setSessionState(bool state)
	{
		mSessionState = state;
	}



	bool getSessionState()
	{
		return mSessionState;
	}


	void setRecvCallState(bool state)
	{
		mRecvCallState = state;
	}

	bool getRecvCallState()
	{
		return mRecvCallState;
	}

	void reset()
	{
		mSessionId = 0;
		mHoldSate = false;
		mSessionState = false;
		mConferenceState = false;
		mRecvCallState = false;
		mIsReferCall = false;
		mOriginCallSessionId = 0;
		mExistEarlyMedia = false;
	}

	bool isReferCall() { return mIsReferCall; }
	long getOriginCallSessionId() { return mOriginCallSessionId; }
	void setReferCall(bool referCall, long originCallSessionId)
	{
		mIsReferCall = referCall;
		mOriginCallSessionId = originCallSessionId;
	}


protected:


private:

	long mSessionId;
	bool mHoldSate;
	bool mSessionState;
	bool mConferenceState;
	bool mRecvCallState;
	bool mIsReferCall;
	long mOriginCallSessionId;
	bool mExistEarlyMedia;
};




#endif

