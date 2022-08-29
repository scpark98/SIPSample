
// SIPSampleDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "Session.h"

struct SIPEvent;

#define TIMER_EVENT_AUDIO_LEVEL			1003

// CSIPSampleDlg dialog
class CSIPSampleDlg : public CDialog, public AbstractCallbackDispatcher
{
// Construction
public:
	CSIPSampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SIPSAMPLE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	virtual void onMessage(void * parameters);


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnSIPCallbackEvent(WPARAM WParam, LPARAM LParam);
	DECLARE_MESSAGE_MAP()


	static int audioRawCallback(void * obj, long sessionId, AUDIOSTREAM_CALLBACK_MODE type, unsigned char * data, int dataLength,int samplingFreqHz);
	static int videoRawCallback(void * obj, 
								long sessionId,
								VIDEOSTREAM_CALLBACK_MODE type, 
								int width, 
								int height, 
								unsigned char * data, 
								int dataLength);


	static int receivedRTPPacket(void *obj, long sessionId, bool isAudio, unsigned char * RTPPacket, int packetSize);
	static int sendingRTPPacket(void *obj, long sessionId, bool isAudio, unsigned char * RTPPacket, int packetSize);

private:
	void showErrorMessage(int errorCode);
	bool loadDevices();
	void initDefaultAudioCodecs();
	void setSRTPType();
	void setVideoResolution();
	void setVideoBitrate();

	void initSettings();
	int findSession(long sessionId);

	void updateAudioCodecs();
	void updateVideoCodecs();

	void SIPUnRegister();
	void addPhoneNumber(char number);
	bool joinConference(int index);

	void updatePrackSetting();

	void getVideoResolution(int& width, int& height);
protected:


	//SIP Event

	void onSIPCallIncoming(ICallbackParameters * parameters);
	void onSIPCallTrying(ICallbackParameters * parameters);
	void onSIPCallRinging(ICallbackParameters * parameters);
	void onSIPCallSessionProgress(ICallbackParameters * parameters);
	void onSIPCallAnswered(ICallbackParameters * parameters);
	void onSIPCallFailure(ICallbackParameters * parameters);
	void onSIPCallClosed(ICallbackParameters * parameters);
	void onSIPDialogStateUpdated(ICallbackParameters * parameters);
	void onSIPCallRemoteHold(ICallbackParameters * parameters);
	void onSIPCallRemoteUnhold(ICallbackParameters * parameters);
	void onSIPTransferTrying(ICallbackParameters * parameters);
	void onSIPTransferRinging(ICallbackParameters * parameters);
	void onSIPACTVTrasferFailure(ICallbackParameters * parameters);
	void onSIPACTVTransferSuccess(ICallbackParameters * parameters);	
	void onSIPInviteUpdated(ICallbackParameters * parameters);
	void onSIPInviteConnected(ICallbackParameters * parameters);
	void onSIPReceivedDtmfTone(ICallbackParameters * parameters);
	void onSIPCallForwarding(ICallbackParameters * parameters);
	void onSIPReceivedRefer(ICallbackParameters * parameters);
	void onSIPReferAccepted(ICallbackParameters * parameters);
	void onSIPReferRejected(ICallbackParameters * parameters);
	void onSIPRecvOptions(ICallbackParameters * parameters);
	void onSIPRecvInfo(ICallbackParameters * parameters);
	void onSIPRecvNotifyOfSubscription(ICallbackParameters * parameter);
	void onSIPSubscriptionFailure(ICallbackParameters * parameter);
	void onSIPSubscriptionTerminated(ICallbackParameters * parameter);
	void onSIPRecvMesage(ICallbackParameters * parameters);
	void onSIPRecvOutOfDialogMessage(ICallbackParameters * parameters);
	void onSIPSendMessageSuccess(ICallbackParameters * parameters);
	void onSIPSendMessageFailure(ICallbackParameters * parameters);
	void onSIPSendOutOfDialogMessageSuccess(ICallbackParameters * parameters);
	void onSIPSendOutOfDialogMessageFailure(ICallbackParameters * parameters);
	void onSIPPlayAudioFileFinished(ICallbackParameters * parameters);
	void onSIPPlayVideoFileFinished(ICallbackParameters * parameters);



public:
	CString m_UserName;
	CString m_Password;
	CString m_DisplayName;
	CString m_AuthName;
	CString m_UserDomain;
	CString m_SIPSever;
	int m_SIPSeverPort;
	CString m_StunServer;
	int m_StunServerPort;
	CComboBox m_cmbSIPTransport;
	CComboBox m_cmbSRTPMode;
	CString m_PhoneNumber;
	BOOL m_CallSDP;
	BOOL m_DND;
	// Auto Answer
	BOOL m_AA;
	BOOL m_Conference;
	CComboBox m_LineList;
	CSliderCtrl m_SpeakerVolume;
	CSliderCtrl m_MicrophoneVolume;
	BOOL m_MicrophoneMute;
	CComboBox m_SpeakersList;
	CComboBox m_MicrophonesList;
	CComboBox m_CamerasList;
	CComboBox m_cmbVideoResolution;
	CSliderCtrl m_sliderVideoBitrate;
	CListBox m_LogList;
	BOOL m_PCMU;
	BOOL m_PCMA;
	BOOL m_G729;
	BOOL m_ILBC;
	BOOL m_GSM;
	BOOL m_G722;
	BOOL m_SPEEX;
	BOOL m_SPEEX_WB;
	BOOL m_H263;
	BOOL m_H2631998;
	BOOL m_H264;
	BOOL m_AEC;
	BOOL m_VAD;
	BOOL m_AGC;
	BOOL m_CNG;
	BOOL m_ANS;
	BOOL m_AudioStreamCallback;
	CString m_RecordFilePath;
	CString m_RecordFileName;
	CString m_PlayAudioFilePathName;
	CString m_ForwardTo;
	CStatic m_RemoteVideo;
	CStatic m_LocalVideo;
	BOOL m_ForwardCallForBusy;
	CProgressCtrl m_progMicroLevel;
	CProgressCtrl m_progSpeakerLevel;
	CString m_strBitrate;
	BOOL m_AMRWB;
	BOOL m_G7221;
	BOOL m_AMR;
	BOOL m_VP8;
	BOOL m_PRACK;


public:
	Session m_SessionArray[MAX_LINES];

private:
	void * m_SIPLib;
	bool m_SIPInitialized;
	bool m_SIPRegistered;
	int m_ActiveLine;
	BOOL m_NeedRegister;

	BOOL m_MakeVideoCall;
	BOOL m_AnswerVideoCall;
	BOOL m_Opus;

public:
	afx_msg void OnBnClickedBtnOnline();
	afx_msg void OnBnClickedBtnOffline();
	afx_msg void OnBnClickedBtnDial();
	afx_msg void OnBnClickedBtnHangUp();
	afx_msg void OnBnClickedBtnReject();
	afx_msg void OnBnClickedIdcBtnHold();
	afx_msg void OnBnClickedBtnUnHold();
	afx_msg void OnBnClickedBtnTransfer();
	afx_msg void OnBnClickedBtnAnswer();
	afx_msg void OnBnClickedBtnAttendedTransfer();
	afx_msg void OnCbnSelchangeCmbVideoResolution();
	afx_msg void OnCbnSelchangeCmbSrtpMode();
	afx_msg void OnCbnSelchangeComboLinelist();
	afx_msg void OnBnClickedChkConference();
	afx_msg void OnCbnSelchangeComboSpeakers();
	afx_msg void OnCbnSelchangeComboMicrophones();
	afx_msg void OnCbnSelchangeComboCameras();
	afx_msg void OnBnClickedCheckMicrophonemute();
	afx_msg void OnBnClickedBtnNum1();
	afx_msg void OnBnClickedBtnNum2();
	afx_msg void OnBnClickedBtnNum3();
	afx_msg void OnBnClickedBtnNum4();
	afx_msg void OnBnClickedBtnNum5();
	afx_msg void OnBnClickedBtnNum6();
	afx_msg void OnBnClickedBtnNum7();
	afx_msg void OnBnClickedBtnNum8();
	afx_msg void OnBnClickedBtnNum9();
	afx_msg void OnBnClickedBtnNum10();
	afx_msg void OnBnClickedBtnNum11();
	afx_msg void OnBnClickedBtnNum12();
	afx_msg void OnClose();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedChkCodecG711u();
	afx_msg void OnBnClickedChkCodecG711a();
	afx_msg void OnBnClickedChkCodecG729();
	afx_msg void OnBnClickedChkCodecIlbc();
	afx_msg void OnBnClickedChkCodecGsm();
	afx_msg void OnBnClickedChkCodecG722();
	afx_msg void OnBnClickedChkCodecSpeex();
	afx_msg void OnBnClickedChkCodecSpeexwb();
	afx_msg void OnBnClickedChkH263();
	afx_msg void OnBnClickedChkH2631998();
	afx_msg void OnBnClickedChkH264();
	afx_msg void OnBnClickedChkAec();
	afx_msg void OnBnClickedChkVad();
	afx_msg void OnBnClickedChkCng();
	afx_msg void OnBnClickedChkAgc();
	afx_msg void OnBnClickedChkAns();
	afx_msg void OnBnClickedBtnRecordDirectory();
	afx_msg void OnBnClickedChkAudioStreamCallback();
	afx_msg void OnBnClickedBtnStartAudioRecording();
	afx_msg void OnBnClickedBtnStopAudioRecording();
	afx_msg void OnBnClickedBtnSelectPalyAudiofile();
	afx_msg void OnBnClickedBtnStartPlayAudiofile();
	afx_msg void OnBnClickedBtnStopPlayAudiofile();
	afx_msg void OnBnClickedBtnEnableForward();
	afx_msg void OnBnClickedBtnDisableForward();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnLocalVideo();
	afx_msg void OnBnClickedBtnVideoOptions();
	afx_msg void OnBnClickedBtnSendVideo();
	afx_msg void OnBnClickedBtnStopVideo();
	afx_msg void OnBnClickedCheck23();
	afx_msg void OnBnClickedCheck24();
	afx_msg void OnBnClickedChkCodecOpus();
	afx_msg void OnBnClickedChkDnd();
	afx_msg void OnBnClickedChkNack();
	BOOL m_Nack;
	BOOL m_VP9;
};

