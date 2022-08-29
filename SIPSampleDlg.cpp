
// SIPSampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SIPSample.h"
#include "SIPSampleDlg.h"

#include "TransferDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CSIPSampleDlg * g_MainDlg = NULL;
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSIPSampleDlg dialog
CSIPSampleDlg::CSIPSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSIPSampleDlg::IDD, pParent)
	, m_SIPLib(NULL)
	, m_SIPInitialized(false)
	, m_SIPRegistered(false)
	, m_ActiveLine(LINE_BASE)
	, m_UserName(_T("290001"))
	, m_Password(_T("1234"))
	, m_DisplayName(_T(""))
	, m_AuthName(_T(""))
	, m_UserDomain(_T(""))
	, m_SIPSever(_T("54.180.43.235"))
	, m_SIPSeverPort(5080)
	, m_StunServer(_T(""))
	, m_StunServerPort(0)
	, m_PhoneNumber(_T(""))
	, m_CallSDP(FALSE)
	, m_DND(FALSE)
	, m_AA(TRUE)
	, m_Conference(FALSE)
	, m_MicrophoneMute(FALSE)
	, m_PCMU(FALSE)
	, m_PCMA(FALSE)
	, m_G729(FALSE)
	, m_ILBC(FALSE)
	, m_GSM(FALSE)
	, m_G722(FALSE)
	, m_SPEEX(FALSE)
	, m_SPEEX_WB(FALSE)
	, m_Opus(FALSE)
	, m_H263(FALSE)
	, m_H2631998(FALSE)
	, m_H264(TRUE)
	, m_AEC(TRUE)
	, m_VAD(FALSE)
	, m_AGC(FALSE)
	, m_CNG(FALSE)
	, m_Nack(TRUE)
	, m_AudioStreamCallback(FALSE)
	, m_RecordFilePath(_T(""))
	, m_RecordFileName(_T(""))
	, m_PlayAudioFilePathName(_T(""))
	, m_ForwardTo(_T(""))
	, m_ANS(FALSE)
	, m_ForwardCallForBusy(FALSE)
	, m_strBitrate(_T(""))
	, m_AMRWB(FALSE)
	, m_G7221(FALSE)
	, m_AMR(FALSE)
	, m_VP8(FALSE)
	, m_VP9(FALSE)
	, m_PRACK(FALSE)
	, m_NeedRegister(TRUE)
	, m_MakeVideoCall(FALSE)
	, m_AnswerVideoCall(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSIPSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_UserName);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_Password);
	DDX_Text(pDX, IDC_EDIT_DISPLAY_NAME, m_DisplayName);
	DDX_Text(pDX, IDC_EDIT_AUTH_NAME, m_AuthName);
	DDX_Text(pDX, IDC_EDIT_USERDOMAIN, m_UserDomain);
	DDX_Text(pDX, IDC_EDIT_SIPSERVER, m_SIPSever);
	DDX_Text(pDX, IDC_EDIT_SIPSERVERPORT, m_SIPSeverPort);
	DDX_Text(pDX, IDC_EDIT_STUNSERVER, m_StunServer);
	DDX_Text(pDX, IDC_EDIT_STUNSERVERPORT, m_StunServerPort);
	DDX_Control(pDX, IDC_CMB_SIP_TRANSPORT, m_cmbSIPTransport);
	DDX_Control(pDX, IDC_CMB_SRTP_MODE, m_cmbSRTPMode);
	DDX_Text(pDX, IDC_EDIT_PHONENUMBER, m_PhoneNumber);
	DDX_Check(pDX, IDC_CHK_CALL_WITHOUT_SDP, m_CallSDP);
	DDX_Check(pDX, IDC_CHK_DND, m_DND);
	DDX_Check(pDX, IDC_CHK_AUTO_ANSWER, m_AA);
	DDX_Check(pDX, IDC_CHK_CONFERENCE, m_Conference);
	DDX_Control(pDX, IDC_COMBO_LINELIST, m_LineList);
	DDX_Control(pDX, IDC_SLIDER_SPEAKER, m_SpeakerVolume);
	DDX_Control(pDX, IDC_SLIDER_MICROPHONE, m_MicrophoneVolume);
	DDX_Check(pDX, IDC_CHECK_MICROPHONEMUTE, m_MicrophoneMute);
	DDX_Control(pDX, IDC_COMBO_SPEAKERS, m_SpeakersList);
	DDX_Control(pDX, IDC_COMBO_MICROPHONES, m_MicrophonesList);
	DDX_Control(pDX, IDC_COMBO_CAMERAS, m_CamerasList);
	DDX_Control(pDX, IDC_CMB_VIDEO_RESOLUTION, m_cmbVideoResolution);
	DDX_Control(pDX, IDC_SLIDER_VIDEO_BITRATE, m_sliderVideoBitrate);
	DDX_Control(pDX, IDC_LIST_LOG, m_LogList);
	DDX_Check(pDX, IDC_CHK_CODEC_G711U, m_PCMU);
	DDX_Check(pDX, IDC_CHK_CODEC_G711A, m_PCMA);
	DDX_Check(pDX, IDC_CHK_CODEC_G729, m_G729);
	DDX_Check(pDX, IDC_CHK_CODEC_ILBC, m_ILBC);
	DDX_Check(pDX, IDC_CHK_CODEC_GSM, m_GSM);
	DDX_Check(pDX, IDC_CHK_CODEC_G722, m_G722);
	DDX_Check(pDX, IDC_CHK_CODEC_SPEEX, m_SPEEX);
	DDX_Check(pDX, IDC_CHK_CODEC_SPEEXWB, m_SPEEX_WB);
	DDX_Check(pDX, IDC_CHK_H263, m_H263);
	DDX_Check(pDX, IDC_CHK_H263_1998, m_H2631998);
	DDX_Check(pDX, IDC_CHK_H264, m_H264);
	DDX_Check(pDX, IDC_CHK_AEC, m_AEC);
	DDX_Check(pDX, IDC_CHK_VAD, m_VAD);
	DDX_Check(pDX, IDC_CHK_AGC, m_AGC);
	DDX_Check(pDX, IDC_CHK_CNG, m_CNG);
	DDX_Check(pDX, IDC_CHK_AUDIO_STREAM_CALLBACK, m_AudioStreamCallback);
	DDX_Text(pDX, IDC_EDIT_RECORD_FILE_PATH, m_RecordFilePath);
	DDX_Text(pDX, IDC_EDIT_AUDIO_RECORD_FILENAME, m_RecordFileName);
	DDX_Text(pDX, IDC_EDIT_PLAY_AUDIO_PATH_NAME, m_PlayAudioFilePathName);
	DDX_Text(pDX, IDC_EDIT_FORWARD_TO, m_ForwardTo);
	DDX_Check(pDX, IDC_CHK_ANS, m_ANS);
	DDX_Control(pDX, IDC_VIDEO_REMOTE, m_RemoteVideo);
	DDX_Control(pDX, IDC_VIDEO_LOCAL, m_LocalVideo);
	DDX_Check(pDX, IDC_CHK_FORWARD_CALL_WHEN_ON_PHONE, m_ForwardCallForBusy);
	DDX_Control(pDX, IDC_PROGRESS_MICROPHONE, m_progMicroLevel);
	DDX_Control(pDX, IDC_PROGRESS_SPEAKER, m_progSpeakerLevel);
	DDX_Text(pDX, IDC_STATIC_BITRATE, m_strBitrate);
	DDX_Check(pDX, IDC_CHECK10, m_AMRWB);
	DDX_Check(pDX, IDC_CHECK21, m_G7221);
	DDX_Check(pDX, IDC_CHECK22, m_AMR);
	DDX_Check(pDX, IDC_CHECK23, m_VP8);
	DDX_Check(pDX, IDC_CHECK24, m_PRACK);
	DDX_Check(pDX, IDC_CHECK26, m_NeedRegister);
	DDX_Check(pDX, IDC_CHECK25, m_MakeVideoCall);
	DDX_Check(pDX, IDC_CHECK27, m_AnswerVideoCall);
	DDX_Check(pDX, IDC_CHK_CODEC_OPUS, m_Opus);
	DDX_Check(pDX, IDC_CHK_NACK, m_Nack);
	DDX_Check(pDX, IDC_CHK_VP9, m_VP9);
}

BEGIN_MESSAGE_MAP(CSIPSampleDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_MESSAGE(WM_SIPEVENT, OnSIPCallbackEvent)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_ONLINE, &CSIPSampleDlg::OnBnClickedBtnOnline)
	ON_BN_CLICKED(IDC_BTN_OFFLINE, &CSIPSampleDlg::OnBnClickedBtnOffline)
	ON_BN_CLICKED(IDC_BTN_DIAL, &CSIPSampleDlg::OnBnClickedBtnDial)
	ON_BN_CLICKED(IDC_BTN_HANG_UP, &CSIPSampleDlg::OnBnClickedBtnHangUp)
	ON_BN_CLICKED(IDC_BTN_REJECT, &CSIPSampleDlg::OnBnClickedBtnReject)
	ON_BN_CLICKED(IDC_IDC_BTN_HOLD, &CSIPSampleDlg::OnBnClickedIdcBtnHold)
	ON_BN_CLICKED(IDC_BTN_UN_HOLD, &CSIPSampleDlg::OnBnClickedBtnUnHold)
	ON_BN_CLICKED(IDC_BTN_TRANSFER, &CSIPSampleDlg::OnBnClickedBtnTransfer)
	ON_BN_CLICKED(IDC_BTN_ANSWER, &CSIPSampleDlg::OnBnClickedBtnAnswer)
	ON_BN_CLICKED(IDC_BTN_ATTENDED_TRANSFER, &CSIPSampleDlg::OnBnClickedBtnAttendedTransfer)
	ON_CBN_SELCHANGE(IDC_CMB_VIDEO_RESOLUTION, &CSIPSampleDlg::OnCbnSelchangeCmbVideoResolution)
	ON_CBN_SELCHANGE(IDC_CMB_SRTP_MODE, &CSIPSampleDlg::OnCbnSelchangeCmbSrtpMode)
	ON_CBN_SELCHANGE(IDC_COMBO_LINELIST, &CSIPSampleDlg::OnCbnSelchangeComboLinelist)
	ON_BN_CLICKED(IDC_CHK_CONFERENCE, &CSIPSampleDlg::OnBnClickedChkConference)
	ON_CBN_SELCHANGE(IDC_COMBO_SPEAKERS, &CSIPSampleDlg::OnCbnSelchangeComboSpeakers)
	ON_CBN_SELCHANGE(IDC_COMBO_MICROPHONES, &CSIPSampleDlg::OnCbnSelchangeComboMicrophones)
	ON_CBN_SELCHANGE(IDC_COMBO_CAMERAS, &CSIPSampleDlg::OnCbnSelchangeComboCameras)
	ON_BN_CLICKED(IDC_CHECK_MICROPHONEMUTE, &CSIPSampleDlg::OnBnClickedCheckMicrophonemute)
	ON_BN_CLICKED(IDC_BTN_NUM1, &CSIPSampleDlg::OnBnClickedBtnNum1)
	ON_BN_CLICKED(IDC_BTN_NUM2, &CSIPSampleDlg::OnBnClickedBtnNum2)
	ON_BN_CLICKED(IDC_BTN_NUM3, &CSIPSampleDlg::OnBnClickedBtnNum3)
	ON_BN_CLICKED(IDC_BTN_NUM4, &CSIPSampleDlg::OnBnClickedBtnNum4)
	ON_BN_CLICKED(IDC_BTN_NUM5, &CSIPSampleDlg::OnBnClickedBtnNum5)
	ON_BN_CLICKED(IDC_BTN_NUM6, &CSIPSampleDlg::OnBnClickedBtnNum6)
	ON_BN_CLICKED(IDC_BTN_NUM7, &CSIPSampleDlg::OnBnClickedBtnNum7)
	ON_BN_CLICKED(IDC_BTN_NUM8, &CSIPSampleDlg::OnBnClickedBtnNum8)
	ON_BN_CLICKED(IDC_BTN_NUM9, &CSIPSampleDlg::OnBnClickedBtnNum9)
	ON_BN_CLICKED(IDC_BTN_NUM10, &CSIPSampleDlg::OnBnClickedBtnNum10)
	ON_BN_CLICKED(IDC_BTN_NUM11, &CSIPSampleDlg::OnBnClickedBtnNum11)
	ON_BN_CLICKED(IDC_BTN_NUM12, &CSIPSampleDlg::OnBnClickedBtnNum12)
	ON_WM_CLOSE()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CSIPSampleDlg::OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_CHK_CODEC_G711U, &CSIPSampleDlg::OnBnClickedChkCodecG711u)
	ON_BN_CLICKED(IDC_CHK_CODEC_G711A, &CSIPSampleDlg::OnBnClickedChkCodecG711a)
	ON_BN_CLICKED(IDC_CHK_CODEC_G729, &CSIPSampleDlg::OnBnClickedChkCodecG729)
	ON_BN_CLICKED(IDC_CHK_CODEC_ILBC, &CSIPSampleDlg::OnBnClickedChkCodecIlbc)
	ON_BN_CLICKED(IDC_CHK_CODEC_GSM, &CSIPSampleDlg::OnBnClickedChkCodecGsm)
	ON_BN_CLICKED(IDC_CHK_CODEC_G722, &CSIPSampleDlg::OnBnClickedChkCodecG722)
	ON_BN_CLICKED(IDC_CHK_CODEC_SPEEX, &CSIPSampleDlg::OnBnClickedChkCodecSpeex)
	ON_BN_CLICKED(IDC_CHK_CODEC_SPEEXWB, &CSIPSampleDlg::OnBnClickedChkCodecSpeexwb)
	ON_BN_CLICKED(IDC_CHK_H263, &CSIPSampleDlg::OnBnClickedChkH263)
	ON_BN_CLICKED(IDC_CHK_H263_1998, &CSIPSampleDlg::OnBnClickedChkH2631998)
	ON_BN_CLICKED(IDC_CHK_H264, &CSIPSampleDlg::OnBnClickedChkH264)
	ON_BN_CLICKED(IDC_CHK_AEC, &CSIPSampleDlg::OnBnClickedChkAec)
	ON_BN_CLICKED(IDC_CHK_VAD, &CSIPSampleDlg::OnBnClickedChkVad)
	ON_BN_CLICKED(IDC_CHK_CNG, &CSIPSampleDlg::OnBnClickedChkCng)
	ON_BN_CLICKED(IDC_CHK_AGC, &CSIPSampleDlg::OnBnClickedChkAgc)
	ON_BN_CLICKED(IDC_CHK_ANS, &CSIPSampleDlg::OnBnClickedChkAns)
	ON_BN_CLICKED(IDC_BTN_RECORD_DIRECTORY, &CSIPSampleDlg::OnBnClickedBtnRecordDirectory)
	ON_BN_CLICKED(IDC_CHK_AUDIO_STREAM_CALLBACK, &CSIPSampleDlg::OnBnClickedChkAudioStreamCallback)
	ON_BN_CLICKED(IDC_BTN_START_AUDIO_RECORDING, &CSIPSampleDlg::OnBnClickedBtnStartAudioRecording)
	ON_BN_CLICKED(IDC_BTN_STOP_AUDIO_RECORDING, &CSIPSampleDlg::OnBnClickedBtnStopAudioRecording)
	ON_BN_CLICKED(IDC_BTN_SELECT_PALY_AUDIOFILE, &CSIPSampleDlg::OnBnClickedBtnSelectPalyAudiofile)
	ON_BN_CLICKED(IDC_BTN_START_PLAY_AUDIOFILE, &CSIPSampleDlg::OnBnClickedBtnStartPlayAudiofile)
	ON_BN_CLICKED(IDC_BTN_STOP_PLAY_AUDIOFILE, &CSIPSampleDlg::OnBnClickedBtnStopPlayAudiofile)
	ON_BN_CLICKED(IDC_BTN_ENABLE_FORWARD, &CSIPSampleDlg::OnBnClickedBtnEnableForward)
	ON_BN_CLICKED(IDC_BTN_DISABLE_FORWARD, &CSIPSampleDlg::OnBnClickedBtnDisableForward)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_LOCAL_VIDEO, &CSIPSampleDlg::OnBnClickedBtnLocalVideo)
	ON_BN_CLICKED(IDC_BTN_VIDEO_OPTIONS, &CSIPSampleDlg::OnBnClickedBtnVideoOptions)
	ON_BN_CLICKED(IDC_BTN_SEND_VIDEO, &CSIPSampleDlg::OnBnClickedBtnSendVideo)
	ON_BN_CLICKED(IDC_BTN_STOP_VIDEO, &CSIPSampleDlg::OnBnClickedBtnStopVideo)
	ON_BN_CLICKED(IDC_CHECK23, &CSIPSampleDlg::OnBnClickedCheck23)
	ON_BN_CLICKED(IDC_CHECK24, &CSIPSampleDlg::OnBnClickedCheck24)
	ON_BN_CLICKED(IDC_CHK_CODEC_OPUS, &CSIPSampleDlg::OnBnClickedChkCodecOpus)
	ON_BN_CLICKED(IDC_CHK_DND, &CSIPSampleDlg::OnBnClickedChkDnd)
	ON_BN_CLICKED(IDC_CHK_NACK, &CSIPSampleDlg::OnBnClickedChkNack)
END_MESSAGE_MAP()


// CSIPSampleDlg message handlers

void CSIPSampleDlg::onMessage(void * parameters)
{
	if (!parameters)
	{
		return;
	}


	if (!this->PostMessage(WM_SIPEVENT, (WPARAM)parameters, 0))
	{
		PortSIP_delCallbackParameters(parameters);
	}
}

BOOL CSIPSampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	srand((unsigned int)time(NULL));

	m_cmbSIPTransport.SetCurSel(0);
	m_cmbSRTPMode.SetCurSel(0);

	g_MainDlg = this;


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSIPSampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSIPSampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSIPSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSIPSampleDlg::showErrorMessage(int errorCode)
{
	switch(errorCode)
	{
	case 0:
		break;
	case INVALID_SESSION_ID:
		break;
	case ECoreAlreadyInitialized:
		break;
	case ECoreNotInitialized:
		break;
	case ECoreSDKObjectNull:
		break;
	case ECoreArgumentNull:
		break;
	case ECoreInitializeWinsockFailure:
		break;
	case ECoreUserNameAuthNameEmpty:
		break;
	case ECoreInitializeStackFailure:
		break;
	case ECorePortOutOfRange:
		break;
	case ECoreAddTcpTransportFailure:
		break;
	case ECoreAddTlsTransportFailure:
		break;
	case ECoreAddUdpTransportFailure:
		break;
	case ECoreMiniAudioPortOutOfRange:
		break;
	case ECoreMaxAudioPortOutOfRange:
		break;
	case ECoreMiniVideoPortOutOfRange:
		break;
	case ECoreMaxVideoPortOutOfRange:
		break;
	case ECoreMiniAudioPortNotEvenNumber:
		break;
	case ECoreMaxAudioPortNotEvenNumber:
		break;
	case ECoreMiniVideoPortNotEvenNumber:
		break;
	case ECoreMaxVideoPortNotEvenNumber:
		break;
	case ECoreAudioVideoPortOverlapped:
		break;
	case ECoreAudioVideoPortRangeTooSmall:
		break;
	case ECoreAlreadyRegistered:
		break;
	case ECoreSIPServerEmpty:
		break;
	case ECoreExpiresValueTooSmall:
		break;
	case ECoreCallIdNotFound:
		break;
	case ECoreNotRegistered:
		break;
	case ECoreCalleeEmpty:
		break;
	case ECoreInvalidUri:
		break;
	case ECoreAudioVideoCodecEmpty:
		break;
	case ECoreNoFreeDialogSession:
		break;
	case ECoreCreateAudioChannelFailed:
		break;
	case ECoreSessionTimerValueTooSmall:
		break;
	case ECoreAudioHandleNull:
		break;
	case ECoreVideoHandleNull:
		break;
	case ECoreCallIsClosed:
		break;
	case ECoreCallAlreadyHold:
		break;
	case ECoreCallNotEstablished:
		break;
	case ECoreCallNotHold:
		break;
	case ECoreSipMessaegEmpty:
		break;
	case ECoreSipHeaderNotExist:
		break;
	case ECoreSipHeaderValueEmpty:
		break;
	case ECoreSipHeaderBadFormed:
		break;
	case ECoreBufferTooSmall:
		break;
	case ECoreSipHeaderValueListEmpty:
		break;
	case ECoreSipHeaderParserEmpty:
		break;
	case ECoreSipHeaderValueListNull:
		break;
	case ECoreSipHeaderNameEmpty:
		break;
	case ECoreAudioSampleNotmultiple:
		break;	//	The audio sample should be multiple of 10
	case ECoreAudioSampleOutOfRange:
		break;	//	The audio sample range is 10 - 60
	case ECoreInviteSessionNotFound:
		break;
	case ECoreStackException:
		break;
	case ECoreMimeTypeUnknown:
		break;
	case ECoreDataSizeTooLarge:
		break;
	case ECoreSessionNumsOutOfRange:
		break;

		// audio
	case EAudioFileNameEmpty:
		break;
	case EAudioChannelNotFound:
		break;
	case EAudioStartRecordFailure:
		break;
	case EAudioRegisterRecodingFailure:
		break;
	case EAudioRegisterPlaybackFailure:
		break;
	case EAudioGetStatisticsFailure:
		break;


		// video
	case EVideoFileNameEmpty:
		break;
	case EVideoGetDeviceNameFailure:
		break;
	case EVideoGetDeviceIdFailure:
		break;
	case EVideoStartCaptureFailure:
		break;
	case EVideoChannelNotFound:
		break;
	case EVideoStartSendFailure:
		break;
	case EVideoGetStatisticsFailure:
		break;
		// Device
	case EDeviceGetDeviceNameFailure:
		break;

	}
}


bool CSIPSampleDlg::loadDevices()
{
	int nums = PortSIP_getNumOfPlayoutDevices(m_SIPLib);

	char deviceName[1024] = { 0 };

	m_SpeakersList.ResetContent();
	for (int i=0; i<nums; ++i)
	{
		PortSIP_getPlayoutDeviceName(m_SIPLib, i, deviceName, 1024);
		m_SpeakersList.AddString(deviceName);
	}

	m_SpeakersList.SetCurSel(0);



	ZeroMemory(deviceName, 1024);
	nums = PortSIP_getNumOfRecordingDevices(m_SIPLib);

	m_MicrophonesList.ResetContent();
	for (int i=0; i<nums; ++i)
	{
		PortSIP_getRecordingDeviceName(m_SIPLib, i, deviceName, 1024);
		m_MicrophonesList.AddString(deviceName);
	}

	m_MicrophonesList.SetCurSel(0);



	ZeroMemory(deviceName, 1024);
	char uniqueIdUTF8[1024] = { 0 };
	nums = PortSIP_getNumOfVideoCaptureDevices(m_SIPLib);

	m_CamerasList.ResetContent();
	for (int i=0; i<nums; ++i)
	{
		PortSIP_getVideoCaptureDeviceName(m_SIPLib, i,uniqueIdUTF8,1024, deviceName, 1024);
		m_CamerasList.AddString(deviceName);
	}
	m_CamerasList.SetCurSel(0);



	m_SpeakerVolume.SetRange(0, 255);
	m_MicrophoneVolume.SetRange(0, 255);
	m_sliderVideoBitrate.SetRange(100,2000);
	m_sliderVideoBitrate.SetPos(300);

	int audioVolume = PortSIP_getMicVolume(m_SIPLib);
	m_MicrophoneVolume.SetPos(audioVolume);

	audioVolume = PortSIP_getSpeakerVolume(m_SIPLib);
	m_SpeakerVolume.SetPos(audioVolume);

	m_progSpeakerLevel.SetRange(0, 9);
	m_progMicroLevel.SetRange(0, 9);

	m_LineList.AddString("Line - 1");
	m_LineList.AddString("Line - 2");
	m_LineList.AddString("Line - 3");
	m_LineList.AddString("Line - 4");
	m_LineList.AddString("Line - 5");
	m_LineList.AddString("Line - 6");
	m_LineList.AddString("Line - 7");
	m_LineList.AddString("Line - 8");

	m_LineList.SetCurSel(0);



	m_PCMA = TRUE;
	m_PCMU = TRUE;
	m_G729 = TRUE;

	m_H264 = TRUE;

	m_AEC = TRUE;
	m_VAD = TRUE;
	m_AGC = TRUE;
	m_CNG = TRUE;
	m_ANS = TRUE;
	m_Nack = TRUE;

	m_cmbSIPTransport.SetCurSel(0);
	m_cmbSRTPMode.SetCurSel(0);
	m_cmbVideoResolution.SetCurSel(1);
	UpdateData(FALSE);
	return true;
}

void CSIPSampleDlg::setSRTPType()
{
	if (m_SIPInitialized == false)
	{
		return;
	}

	SRTP_POLICY srtpPolicy = SRTP_POLICY_NONE;

	switch (m_cmbSRTPMode.GetCurSel())
	{
	case 0:
		srtpPolicy = SRTP_POLICY_NONE;
		break;
	case 1:
		srtpPolicy = SRTP_POLICY_PREFER;
		break;
	case 2:
		srtpPolicy = SRTP_POLICY_FORCE;
		break;
	}

	PortSIP_setSrtpPolicy(m_SIPLib,srtpPolicy, true);
}


void CSIPSampleDlg::setVideoResolution()
{
	if (m_SIPInitialized == false)
	{
		return;
	}

	int width, height;
	getVideoResolution(width, height);
	PortSIP_setVideoResolution(m_SIPLib, width, height);
}

void CSIPSampleDlg::setVideoBitrate()
{
	if (m_SIPInitialized == false)
	{
		return;
	}

	if(m_SIPInitialized)
	{
		PortSIP_setVideoBitrate(m_SIPLib, m_SessionArray[m_ActiveLine].getSessionId(), m_sliderVideoBitrate.GetPos());
	}
	m_strBitrate.Format("%dKbps",m_sliderVideoBitrate.GetPos());
	UpdateData(FALSE);
}


void CSIPSampleDlg::initDefaultAudioCodecs()
{
	if (m_SIPInitialized == false)
	{
		return;
	}


	PortSIP_clearAudioCodec(m_SIPLib);


	// Default we just used PCMA, PCMU, G729
	PortSIP_addAudioCodec(m_SIPLib, AUDIOCODEC_PCMA);
	PortSIP_addAudioCodec(m_SIPLib, AUDIOCODEC_PCMU);
	PortSIP_addAudioCodec(m_SIPLib, AUDIOCODEC_G729);
	
	// The DTMF MUST last added
	PortSIP_addAudioCodec(m_SIPLib, AUDIOCODEC_DTMF);
}


int CSIPSampleDlg::findSession(long sessionId)
{
	int index = -1;
	for (int i=LINE_BASE; i<MAX_LINES; ++i)
	{
		if (sessionId == m_SessionArray[i].getSessionId())
		{
			index = i;
			break;
		}
	}

	return index;
}


void CSIPSampleDlg::initSettings()
{
	if (m_SIPInitialized == false)
	{
		return;
	}

	UpdateData(TRUE);

	PortSIP_enableAEC(m_SIPLib, m_AEC == TRUE ? EC_DEFAULT : EC_NONE);
	PortSIP_enableCNG(m_SIPLib, m_CNG==TRUE); 
	PortSIP_enableAGC(m_SIPLib, m_AGC == TRUE ? AGC_DEFAULT : AGC_NONE);
	PortSIP_enableANS(m_SIPLib, m_ANS == TRUE ? NS_DEFAULT : NS_NONE);
	PortSIP_enableVAD(m_SIPLib, m_VAD==TRUE);

	PortSIP_setVideoNackStatus(m_SIPLib, m_Nack==TRUE);

	PortSIP_setDoNotDisturb(m_SIPLib, m_DND==TRUE);
}



void CSIPSampleDlg::updateAudioCodecs()
{
	if (m_SIPInitialized == false)
	{
		return;
	}

	PortSIP_clearAudioCodec(m_SIPLib);

	

	if (m_PCMU)
	{
		PortSIP_addAudioCodec(m_SIPLib, AUDIOCODEC_PCMU);
	}

	if (m_PCMA)
	{
		PortSIP_addAudioCodec(m_SIPLib, AUDIOCODEC_PCMA);
	}
	if (m_G729)
	{
		PortSIP_addAudioCodec(m_SIPLib, AUDIOCODEC_G729);
	}
	if (m_ILBC)
	{
		PortSIP_addAudioCodec(m_SIPLib, AUDIOCODEC_ILBC);
	}
	if (m_GSM)
	{
		PortSIP_addAudioCodec(m_SIPLib, AUDIOCODEC_GSM);
	}

	if (m_G722)
	{
		PortSIP_addAudioCodec(m_SIPLib, AUDIOCODEC_G722);
	}
	if (m_SPEEX)
	{
		PortSIP_addAudioCodec(m_SIPLib, AUDIOCODEC_SPEEX);
	}

	if (m_SPEEX_WB)
	{
		PortSIP_addAudioCodec(m_SIPLib, AUDIOCODEC_SPEEXWB);
	}

	if (m_AMR)
	{
		PortSIP_addAudioCodec(m_SIPLib, AUDIOCODEC_AMR);
	}

	if (m_AMRWB)
	{
		PortSIP_addAudioCodec(m_SIPLib, AUDIOCODEC_AMRWB);
	}
	if (m_G7221)
	{
		PortSIP_addAudioCodec(m_SIPLib, AUDIOCODEC_G7221);
	}

	if (m_Opus)
	{
		PortSIP_addAudioCodec(m_SIPLib, AUDIOCODEC_OPUS);
	}


	PortSIP_addAudioCodec(m_SIPLib, AUDIOCODEC_DTMF);
}



void CSIPSampleDlg::updateVideoCodecs()
{
	if (m_SIPInitialized == false)
	{
		return;
	}

	PortSIP_clearVideoCodec(m_SIPLib);


	UpdateData(TRUE);

	if (m_H263)
	{
		PortSIP_addVideoCodec(m_SIPLib, VIDEO_CODEC_H263);
	}

	if (m_H2631998)
	{
		PortSIP_addVideoCodec(m_SIPLib, VIDEO_CODEC_H263_1998);
	}

	if (m_H264)
	{
		PortSIP_addVideoCodec(m_SIPLib, VIDEO_CODEC_H264);
	}

	if (m_VP8)
	{
		PortSIP_addVideoCodec(m_SIPLib, VIDEO_CODEC_VP8);
	}
	if (m_VP8)
	{
		PortSIP_addVideoCodec(m_SIPLib, VIDEO_CODEC_VP9);
	}
}


void CSIPSampleDlg::SIPUnRegister()
{
	if (!m_SIPLib)
	{
		return;
	}

	for (int i=LINE_BASE; i<MAX_LINES; ++i)
	{
		if (m_SessionArray[i].getRecvCallState() == true)
		{
			PortSIP_rejectCall(m_SIPLib, m_SessionArray[i].getSessionId(), 486);
		}
		else if (m_SessionArray[i].getSessionState() == true)
		{
			PortSIP_hangUp(m_SIPLib, m_SessionArray[i].getSessionId());
		}

		m_SessionArray[i].reset();
	}


	if (m_SIPRegistered == true)
	{
		PortSIP_unRegisterServer(m_SIPLib);
		PortSIP_removeUser(m_SIPLib);
	}

	if (m_SIPInitialized == true)
	{
		PortSIP_unInitialize(m_SIPLib);
		m_SIPLib = NULL;
	}

	m_SIPRegistered = false;
	m_SIPInitialized = false;

	KillTimer(TIMER_EVENT_AUDIO_LEVEL);

	m_LogList.ResetContent();
	m_SpeakersList.ResetContent();
	m_MicrophonesList.ResetContent();
	m_CamerasList.ResetContent();
}


bool CSIPSampleDlg::joinConference(int index)
{
	if (m_SIPInitialized == false)
	{
		return false;
	}

	UpdateData(TRUE);
	if (!m_Conference)
	{
		return false;
	}

	PortSIP_setRemoteVideoWindow(m_SIPLib, m_SessionArray[index].getSessionId(), nullptr);
	int rt = PortSIP_joinToConference(m_SIPLib, m_SessionArray[index].getSessionId());

	// We need to unhold the line in conference
	if (m_SessionArray[index].getSessionState())
	{
		PortSIP_unHold(m_SIPLib, m_SessionArray[index].getSessionId());
		m_SessionArray[index].setHoldState(false);
	}

	return true;
}


void CSIPSampleDlg::updatePrackSetting()
{
	if (m_SIPInitialized == false)
	{
		return;
	}

	UpdateData(TRUE);

	if (m_PRACK)
	{
		PortSIP_enableReliableProvisional(m_SIPLib, true);
	}
	else
	{
		PortSIP_enableReliableProvisional(m_SIPLib, false);
	}
}


void CSIPSampleDlg::getVideoResolution(int& width, int& height)
{
	//QCIF;CIF;VGA;SVGA;XVGA;720P;QVGA;
	switch (m_cmbVideoResolution.GetCurSel())
	{
	case 0://qcif
		width = 176;
		height = 144;
		break;
	case 1://cif
		width = 352;
		height = 288;
		break;
	case 2://VGA
		width = 640;
		height = 480;
		break;
	case 3://svga
		width = 800;
		height = 600;
		break;
	case 4://xvga
		width = 1024;
		height = 768;
		break;
	case 5://q720
		width = 1280;
		height = 720;
		break;
	case 6://QVGA
		width = 320;
		height = 240;
		break;
	default:
		width = 352;
		height = 288;
	}
}

void CSIPSampleDlg::addPhoneNumber(char number)
{
	UpdateData(TRUE);

	CString Text;
	GetDlgItem(IDC_EDIT_PHONENUMBER)->GetWindowText(Text);
	Text += number;

	GetDlgItem(IDC_EDIT_PHONENUMBER)->SetWindowText(Text);

	if (m_SIPInitialized==false || (m_NeedRegister&&m_SIPRegistered==false))
	{
		return;
	}

	int dtmfTone = -1;
	if (m_SessionArray[m_ActiveLine].getSessionState() == true)
	{
		switch (number)
		{
		case '0':
			dtmfTone = 0;
			break;

		case '1':
			dtmfTone = 1;
			break;

		case '2':
			dtmfTone = 2;
			break;

		case '3':
			dtmfTone = 3;
			break;

		case '4':
			dtmfTone = 4;
			break;

		case '5':
			dtmfTone = 5;
			break;

		case '6':
			dtmfTone = 6;
			break;

		case '7':
			dtmfTone = 7;
			break;

		case '8':
			dtmfTone = 8;
			break;

		case '9':
			dtmfTone = 9;
			break;

		case '*':
			dtmfTone = 10;
			break;

			case '#':
			dtmfTone = 11;
			break;

		default:
			return;
		}

		PortSIP_sendDtmf(m_SIPLib, m_SessionArray[m_ActiveLine].getSessionId(), DTMF_RFC2833, dtmfTone, 160, true);
	}	
}


void CSIPSampleDlg::OnBnClickedBtnOnline()
{

#define SIPPORT_MIN	5000

	UpdateData(TRUE);


	if (m_SIPInitialized==true || m_SIPRegistered==true)
	{
		::MessageBox(GetSafeHwnd(), "You already Logged in!", "Information", MB_ICONINFORMATION);	
		return;		
	}

	if (m_UserName.IsEmpty())
	{
		::MessageBox(GetSafeHwnd(), "Please enter user name!", "Information", MB_ICONINFORMATION);	
		return;	
	}

	if (m_Password.IsEmpty())
	{
		::MessageBox(GetSafeHwnd(), "Please enter password!", "Information", MB_ICONINFORMATION);	
		return;	
	}

	if (m_SIPSever.IsEmpty())
	{
		::MessageBox(GetSafeHwnd(), "Please enter SIP server!", "Information", MB_ICONINFORMATION);	
		return;	
	}

	if (m_SIPSeverPort <= 0)
	{
		::MessageBox(GetSafeHwnd(), "Please enter SIP server port!", "Information", MB_ICONINFORMATION);	
		return;	
	}

	srand(GetTickCount());
	int localSIPPort = SIPPORT_MIN + rand() % 5000;

	TRANSPORT_TYPE transport = TRANSPORT_UDP;
	if (m_cmbSIPTransport.GetCurSel() == 1)
	{
		transport = TRANSPORT_TLS;
	}
	else if (m_cmbSIPTransport.GetCurSel() == 2)
	{
		transport = TRANSPORT_TCP;
	}
	else if (m_cmbSIPTransport.GetCurSel() == 3)
	{
		transport = TRANSPORT_PERS_UDP;
	}
	else if (m_cmbSIPTransport.GetCurSel() == 4)
	{
		transport = TRANSPORT_PERS_TCP;
	}

	//  Default we don't use outbound server, set the outboundServer as NULL and the port as 0
	char * outboundServer = NULL;
	int outboundServerPort = 0;

	int errorCode = 0;
	m_SIPLib = PortSIP_initialize(this,
		transport,
		// Use 0.0.0.0 for local IP then the SDK will choose an available local IP automatically.
		// You also can specify a certain local IP to instead of "0.0.0.0", more details please read the SDK User Manual
		"0.0.0.0",
		localSIPPort,
		PORTSIP_LOG_DEBUG,
		"d:\\",
		8,
		"PortSIP VoIP SDK",
		0,
		0,
		"/",
		"",
		false,
		&errorCode);

	if(errorCode != 0)
	{
		::MessageBox(GetSafeHwnd(), "PortSIP_initialize failure.", "Information", MB_ICONWARNING);	
		return;		
	}

	m_SIPInitialized = true;
	m_LogList.InsertString(m_LogList.GetCount(), "Initialized the SDK.");

	errorCode = PortSIP_setUser(m_SIPLib,
		(LPTSTR)(LPCTSTR)m_UserName,
		(LPTSTR)(LPCTSTR)m_DisplayName,
		(LPTSTR)(LPCTSTR)m_AuthName,
		(LPTSTR)(LPCTSTR)m_Password,		
		(LPTSTR)(LPCTSTR)m_UserDomain,
		(LPTSTR)(LPCTSTR)m_SIPSever,
		m_SIPSeverPort,
		(LPTSTR)(LPCTSTR)m_StunServer,
		m_StunServerPort,
		outboundServer,
		outboundServerPort);
	if(errorCode != 0)
	{
		PortSIP_unInitialize(m_SIPLib);	
		m_LogList.ResetContent();
		m_SIPLib = NULL;
		m_SIPInitialized = false;

		::MessageBox(GetSafeHwnd(), "PortSIP_setUser failure.", "Information", MB_ICONWARNING);	
		return;	
	}

	m_LogList.InsertString(m_LogList.GetCount(), "Set user succeeded.");

	loadDevices();

	setSRTPType();

	int rt = PortSIP_setLicenseKey(m_SIPLib, "4WINkx5ERjQ2RTg4MDM4NTNFMzY3ODVCMzRENjA1RjFDRjI0OUA5QUNFNEIzQjc4Qjg2Mzc4RDZDMURDRDFBQkYxOTAyOUAyNEQ2REJBRUE2RDNCQUNFRURDRDkyQTJGOUFDRUYwRUA1QzlBRkVBQjREQzJFMUM4NjE1NUJCRDQ3MjVBMzdFOQ");
	if (rt == ECoreTrialVersionLicenseKey)
	{
		::MessageBox(GetSafeHwnd(), "This sample was built base on evaluation PortSIP VoIP SDK, which allows only three minutes conversation. The conversation will be cut off automatically after three minutes, then you can't hearing anything. Feel free contact us at: sales@portsip.com to purchase the official version.", "Information", MB_ICONINFORMATION);
	}
	else if (rt == ECoreWrongLicenseKey)
	{
		::MessageBox(GetSafeHwnd(), "The wrong license key was detected, please check with sales@portsip.com or support@portsip.com", "Information", MB_ICONINFORMATION);
	}

	PortSIP_setLocalVideoWindow(m_SIPLib, m_LocalVideo.m_hWnd);

	updateAudioCodecs();
	updateVideoCodecs();

	initSettings();

	setVideoResolution();
	setVideoBitrate();


	if (m_NeedRegister)
	{
		errorCode = PortSIP_registerServer(m_SIPLib, 120, 3);
		if (errorCode != 0)
		{
			PortSIP_removeUser(m_SIPLib);
			PortSIP_unInitialize(m_SIPLib);

			m_SIPLib = NULL;
			m_SIPInitialized = false;

			::MessageBox(GetSafeHwnd(), "Register to SIP server failure.", "Information", MB_ICONWARNING);

			m_LogList.ResetContent();

			return;
		}

		SetTimer(TIMER_EVENT_AUDIO_LEVEL, 100, NULL);

		m_LogList.InsertString(m_LogList.GetCount(), "Registering....");
	}
}

void CSIPSampleDlg::OnBnClickedBtnOffline()
{
	// TODO: Add your control notification handler code here
	SIPUnRegister();
}

void CSIPSampleDlg::OnBnClickedBtnDial()
{
	UpdateData(TRUE);

	if (m_SIPInitialized==false || (m_NeedRegister&&m_SIPRegistered==false))
	{
		return;
	}

	if (m_PhoneNumber.IsEmpty())
	{
		::MessageBox(GetSafeHwnd(), "The phone number is empty.", "Information", MB_ICONWARNING);	
		return;
	}

	if (m_SessionArray[m_ActiveLine].getSessionState()==true || m_SessionArray[m_ActiveLine].getRecvCallState()==true)
	{
		::MessageBox(GetSafeHwnd(), "Current line is busy now, please switch a line", "Information", MB_ICONINFORMATION);
		return;
	}



	updateAudioCodecs();
	updateVideoCodecs();

	updatePrackSetting();

	if (PortSIP_isAudioCodecEmpty(m_SIPLib) == true)
	{
		initDefaultAudioCodecs();
	}

	stringstream to;
	to << (LPTSTR)(LPCTSTR)m_PhoneNumber;



	bool hasSDP = true;  // Usually to make the 3PCC, you need to make an invite without SDP
	if (m_CallSDP)
	{
		hasSDP = false;
	}


	PortSIP_setAudioDeviceId(m_SIPLib, m_MicrophonesList.GetCurSel(), m_SpeakersList.GetCurSel());


	// The callee MUST likes sip:number@sip.portsip.com
	int errorCode = 0;
	bool makeVideoCall = false;
	if (m_MakeVideoCall)
	{
		makeVideoCall = true;
	}

	long sessionId = PortSIP_call(m_SIPLib, to.str().c_str(), hasSDP, makeVideoCall);
	if (sessionId <= 0)
	{
		if(errorCode != 0)
		{
			showErrorMessage(errorCode);
		}
		::MessageBox(GetSafeHwnd(), "PortSIP_call failure.", "Information", MB_ICONINFORMATION);
		return;		
	}

	PortSIP_setRemoteVideoWindow(m_SIPLib, sessionId, m_RemoteVideo.m_hWnd);

	m_SessionArray[m_ActiveLine].setSessionId(sessionId);
	m_SessionArray[m_ActiveLine].setSessionState(true);


	stringstream text;
	text << "Calling on line " << m_ActiveLine << "";

	m_LogList.InsertString(m_LogList.GetCount(), text.str().c_str());	
}

void CSIPSampleDlg::OnBnClickedBtnHangUp()
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

	if (m_SIPInitialized==false || (m_NeedRegister&&m_SIPRegistered==false))
	{
		return;
	}

	if (m_SessionArray[m_ActiveLine].getSessionState() == true)
	{
		PortSIP_hangUp(m_SIPLib, m_SessionArray[m_ActiveLine].getSessionId());
		m_SessionArray[m_ActiveLine].reset();

		stringstream log;
		log << "Hang up call on line " << m_ActiveLine << "";
		m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());	
	}
	else if (m_SessionArray[m_ActiveLine].getRecvCallState() == true)
	{
		PortSIP_rejectCall(m_SIPLib, m_SessionArray[m_ActiveLine].getSessionId(), 486);
		m_SessionArray[m_ActiveLine].reset();

		stringstream log;
		log << "Rejected call on line " << m_ActiveLine << "";
		m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());	
	}
}

void CSIPSampleDlg::OnBnClickedBtnReject()
{
	UpdateData(TRUE);


	if (m_SIPInitialized==false || (m_NeedRegister&&m_SIPRegistered==false))
	{
		return;
	}

	if (m_SessionArray[m_ActiveLine].getRecvCallState() == true)
	{
		PortSIP_rejectCall(m_SIPLib, m_SessionArray[m_ActiveLine].getSessionId(), 486);
		m_SessionArray[m_ActiveLine].reset();

		stringstream log;
		log << "Rejected call on line " << m_ActiveLine << "";
		m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());	
	}
}

void CSIPSampleDlg::OnBnClickedIdcBtnHold()
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);


	if (m_SIPInitialized==false || (m_NeedRegister&&m_SIPRegistered==false))
	{
		return;
	}

	if (m_SessionArray[m_ActiveLine].getSessionState() == false)
	{
		return;
	}


	if (m_SessionArray[m_ActiveLine].getHoldState() == true)
	{
		return;
	}

	PortSIP_hold(m_SIPLib, m_SessionArray[m_ActiveLine].getSessionId());
	m_SessionArray[m_ActiveLine].setHoldState(true);

	stringstream log;
	log << "Hold the call on line " << m_ActiveLine << "";
	m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());
}

void CSIPSampleDlg::OnBnClickedBtnUnHold()
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

	if (m_SIPInitialized==false || (m_NeedRegister&&m_SIPRegistered==false))
	{
		return;
	}

	if (m_SessionArray[m_ActiveLine].getSessionState() == false)
	{
		return;
	}


	if (m_SessionArray[m_ActiveLine].getHoldState() == false)
	{
		return;
	}

	PortSIP_unHold(m_SIPLib, m_SessionArray[m_ActiveLine].getSessionId());
	m_SessionArray[m_ActiveLine].setHoldState(false);

	stringstream log;
	log << "UnHold the call on line " << m_ActiveLine << "";
	m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());
}

void CSIPSampleDlg::OnBnClickedBtnTransfer()
{

	// TODO: Add your control notification handler code here


	UpdateData(TRUE);
	if (m_SIPInitialized==false || (m_NeedRegister&&m_SIPRegistered==false))
	{
		return;
	}

	if (m_SessionArray[m_ActiveLine].getSessionState() == false)
	{
		::MessageBox(GetSafeHwnd(), "Need to make the call established first", "Information", MB_ICONINFORMATION);
		return;
	}

	CTransferDlg Dlg;
	if (Dlg.DoModal() == IDOK)
	{
		if (Dlg.getTransferNumber().IsEmpty())
		{
			::MessageBox(GetSafeHwnd(), "Transfer failed, transfer number is empty", "Information", MB_ICONINFORMATION);
			return;
		}
	}
	else
	{
		::MessageBox(GetSafeHwnd(), "Transfer failed, you have canceled the transfer", "Information", MB_ICONINFORMATION);
		return;
	}


	int errorCodec = PortSIP_refer(m_SIPLib, m_SessionArray[m_ActiveLine].getSessionId(), (LPTSTR)(LPCTSTR)Dlg.getTransferNumber());
	if (errorCodec != 0)
	{
		::MessageBox(GetSafeHwnd(), "PortSIP_refer failed", "Transfer", MB_ICONINFORMATION);
		return;
	}


	stringstream log;
	log << "Transfer the call on line " << m_ActiveLine << "";
	m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());
}

void CSIPSampleDlg::OnBnClickedBtnAnswer()
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

	if (m_SIPInitialized==false || (m_NeedRegister&&m_SIPRegistered==false))
	{
		return;
	}

	if (m_SessionArray[m_ActiveLine].getRecvCallState() == false)
	{
		::MessageBox(GetSafeHwnd(), "Current line does not has incoming call, please switch a line.", "Information", MB_ICONINFORMATION);
		return;
	}

	m_SessionArray[m_ActiveLine].setSessionState(true);
	m_SessionArray[m_ActiveLine].setRecvCallState(false);

	PortSIP_setRemoteVideoWindow(m_SIPLib, m_SessionArray[m_ActiveLine].getSessionId(), m_RemoteVideo.m_hWnd);

	bool answerVideoCall = false;
	if (m_AnswerVideoCall)
	{
		answerVideoCall = true;
	}
	if (PortSIP_answerCall(m_SIPLib, m_SessionArray[m_ActiveLine].getSessionId(), answerVideoCall) == 0)
	{
		stringstream log;
		log << "Answered the call on line " << m_ActiveLine << "";
		m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());

		joinConference(m_ActiveLine);
	}
	else
	{
		m_SessionArray[m_ActiveLine].reset();

		stringstream log;
		log << "Answer call failed on line " << m_ActiveLine << "";
		m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());	
	}
}

void CSIPSampleDlg::OnBnClickedBtnAttendedTransfer()
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

	if (m_SIPInitialized==false || (m_NeedRegister&&m_SIPRegistered==false))
	{
		return;
	}

	if (m_SessionArray[m_ActiveLine].getSessionState() == false)
	{
		::MessageBox(GetSafeHwnd(), "Need to make the call established first", "Information", MB_ICONINFORMATION);
		return;
	}

	CTransferDlg Dlg;
	int replaceLine = 0;

	if (Dlg.DoModal() == IDOK)
	{
		if (Dlg.getTransferNumber().IsEmpty())
		{
			::MessageBox(GetSafeHwnd(), "Transfer failed, transfer number is empty", "Information", MB_ICONINFORMATION);
			return;
		}

		replaceLine = Dlg.GetReplaceLine();
		if (replaceLine<=0 || replaceLine>=MAX_LINES)
		{
			::MessageBox(GetSafeHwnd(), "The replace line out of range", "Information", MB_ICONINFORMATION);
			return;
		}

		if (m_SessionArray[replaceLine].getSessionState() == false)
		{
			::MessageBox(GetSafeHwnd(), "The replace line does not established yet", "Information", MB_ICONINFORMATION);
			return;
		}
	}
	else
	{
		::MessageBox(GetSafeHwnd(), "Transfer failed, you have canceled the transfer", "Information", MB_ICONINFORMATION);
		return;
	}

	int errorCodec = PortSIP_attendedRefer(m_SIPLib, m_SessionArray[m_ActiveLine].getSessionId(), m_SessionArray[replaceLine].getSessionId(), (LPTSTR)(LPCTSTR)Dlg.getTransferNumber());
	if (errorCodec != 0)
	{
		showErrorMessage(errorCodec);
		::MessageBox(GetSafeHwnd(), "PortSIP_attendedRefer failed", "Transfer", MB_ICONINFORMATION);
		return;
	}


	stringstream log;
	log << "Attended refer on line " << m_ActiveLine << "";

	m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());
}


void CSIPSampleDlg::OnCbnSelchangeCmbSrtpMode()
{
	setSRTPType();
}


void CSIPSampleDlg::OnCbnSelchangeCmbVideoResolution()
{
	// TODO: Add your control notification handler code here
	setVideoResolution();
}



void CSIPSampleDlg::OnCbnSelchangeComboLinelist()
{
	UpdateData(TRUE);

	if (m_SIPInitialized==false || (m_NeedRegister&&m_SIPRegistered==false))
	{
		m_LineList.SetCurSel(0);
		return;
	}

	if (m_ActiveLine == (m_LineList.GetCurSel() + LINE_BASE))
	{
		return;
	}


	// If in conference, then do not need to hold the line
	if (m_Conference)
	{
		m_ActiveLine = m_LineList.GetCurSel() + LINE_BASE;
		return;
	}


	if (m_SessionArray[m_ActiveLine].getSessionState()==true && m_SessionArray[m_ActiveLine].getHoldState()==false)
	{
		// Need to hold this line

		PortSIP_hold(m_SIPLib, m_SessionArray[m_ActiveLine].getSessionId());
		PortSIP_setRemoteVideoWindow(m_SIPLib, m_SessionArray[m_ActiveLine].getSessionId(), NULL);
		m_SessionArray[m_ActiveLine].setHoldState(true);

		stringstream log;
		log << "Hold call on line " << m_ActiveLine << "";
		m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());

	}


	m_ActiveLine = m_LineList.GetCurSel() + LINE_BASE;

	if (m_SessionArray[m_ActiveLine].getSessionState()==true && m_SessionArray[m_ActiveLine].getHoldState()==true)
	{
		// Need to unhold this line
		PortSIP_unHold(m_SIPLib, m_SessionArray[m_ActiveLine].getSessionId());
		PortSIP_setRemoteVideoWindow(m_SIPLib, m_SessionArray[m_ActiveLine].getSessionId(), m_RemoteVideo.GetSafeHwnd());
		m_SessionArray[m_ActiveLine].setHoldState(false);

		stringstream log;
		log << "unHold call on line " << m_ActiveLine << "";
		m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());

	}
}

void CSIPSampleDlg::OnBnClickedChkDnd()
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

	if (m_SIPInitialized == false)
	{
		m_DND = FALSE;
		UpdateData(FALSE);

		::MessageBox(GetSafeHwnd(), "The SDK does not initialized.", "Information", MB_ICONWARNING);
		return;
	}

	bool doNotDisturb = false;
	if (m_DND)
	{
		doNotDisturb = true;
	}
	PortSIP_setDoNotDisturb(m_SIPLib, doNotDisturb);
}


void CSIPSampleDlg::OnBnClickedChkConference()
{
	UpdateData(TRUE);

	if (m_SIPInitialized==false || (m_NeedRegister&&m_SIPRegistered==false))
	{
		m_Conference = FALSE;
		UpdateData(FALSE);

		::MessageBox(GetSafeHwnd(), "The SDK does not initialized.", "Information", MB_ICONWARNING);
		return;
	}
	
	if (m_Conference)
	{
		int width, height;
		getVideoResolution(width, height);
		int rt = PortSIP_createVideoConference(m_SIPLib, m_RemoteVideo.m_hWnd, width, height, true);
		if (rt != 0)
		{
			m_LogList.InsertString(m_LogList.GetCount(), "Conference failed");
			m_Conference = FALSE;
			UpdateData(FALSE);
		}
		else
		{
			m_LogList.InsertString(m_LogList.GetCount(), "Make conference succeeded");
			for (int i=LINE_BASE; i<MAX_LINES; ++i)
			{
				if (m_SessionArray[i].getSessionState()==true )
				{
					joinConference(i);

					stringstream log;
					log << "Add line %d to conference " << i;
					m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());
				}
			}
		}
	}
	else
	{
		// Must place all calls in HOLD after the conference is stopped.
		int sessionIds[MAX_LINES];
		for (int i=LINE_BASE; i<MAX_LINES; ++i)
		{
			sessionIds[i] = 0;
		}

		for (int i=LINE_BASE; i<MAX_LINES; ++i)
		{
			if (m_SessionArray[i].getSessionState()==true && m_SessionArray[i].getHoldState()==false)
			{
				sessionIds[i] = m_SessionArray[i].getSessionId();

				if(m_ActiveLine != i)
				{
					// Hold the line 
					PortSIP_hold(m_SIPLib, sessionIds[i]);

					m_SessionArray[i].setHoldState(true);
				}
			}
		}

		
		m_LogList.InsertString(m_LogList.GetCount(), "Taken off Conference");
		PortSIP_destroyConference(m_SIPLib);
		m_Conference = 0;

	}
}

void CSIPSampleDlg::OnCbnSelchangeComboSpeakers()
{
	if (m_SIPInitialized == true)
	{
		PortSIP_setAudioDeviceId(m_SIPLib, m_MicrophonesList.GetCurSel(), m_SpeakersList.GetCurSel());
	}
}

void CSIPSampleDlg::OnCbnSelchangeComboMicrophones()
{
	if (m_SIPInitialized == true)
	{
		PortSIP_setAudioDeviceId(m_SIPLib, m_MicrophonesList.GetCurSel(), m_SpeakersList.GetCurSel());
	}
}

void CSIPSampleDlg::OnCbnSelchangeComboCameras()
{
	if (m_SIPInitialized == true)
	{
		PortSIP_setVideoDeviceId(m_SIPLib, m_CamerasList.GetCurSel());
	}
}

void CSIPSampleDlg::OnBnClickedCheckMicrophonemute()
{
	// TODO: Add your control notification handler code here

	if (m_SIPInitialized == false)
	{
		::MessageBox(GetSafeHwnd(), "Please initialize the SDK first.", "Information", MB_ICONINFORMATION);
		return;
	}

	UpdateData(TRUE);

	if (m_MicrophoneMute)
	{
		PortSIP_muteMicrophone(m_SIPLib, true);
	}
	else
	{
		PortSIP_muteMicrophone(m_SIPLib, false);
	}
}

void CSIPSampleDlg::OnBnClickedBtnNum1()
{
	addPhoneNumber('1');
}

void CSIPSampleDlg::OnBnClickedBtnNum2()
{
	addPhoneNumber('2');
}

void CSIPSampleDlg::OnBnClickedBtnNum3()
{
	addPhoneNumber('3');
}

void CSIPSampleDlg::OnBnClickedBtnNum4()
{
	addPhoneNumber('4');
}

void CSIPSampleDlg::OnBnClickedBtnNum5()
{
	addPhoneNumber('5');
}

void CSIPSampleDlg::OnBnClickedBtnNum6()
{
	addPhoneNumber('6');
}

void CSIPSampleDlg::OnBnClickedBtnNum7()
{
	addPhoneNumber('7');
}

void CSIPSampleDlg::OnBnClickedBtnNum8()
{
	addPhoneNumber('8');
}

void CSIPSampleDlg::OnBnClickedBtnNum9()
{
	addPhoneNumber('9');
}

void CSIPSampleDlg::OnBnClickedBtnNum10()
{
	addPhoneNumber('*');
}

void CSIPSampleDlg::OnBnClickedBtnNum11()
{
	addPhoneNumber('0');
}

void CSIPSampleDlg::OnBnClickedBtnNum12()
{
	addPhoneNumber('#');
}

void CSIPSampleDlg::OnClose()
{

	SIPUnRegister();

	CDialog::OnClose();
}

void CSIPSampleDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (m_SIPLib)
	{
		CSliderCtrl * sliderMicroPhone = (CSliderCtrl *)GetDlgItem(IDC_SLIDER_MICROPHONE);
		CSliderCtrl * sliderSpeaker = (CSliderCtrl *)GetDlgItem(IDC_SLIDER_SPEAKER);


		if (sliderMicroPhone == (CSliderCtrl *)pScrollBar)
		{
			PortSIP_setMicVolume(m_SIPLib, sliderMicroPhone->GetPos());
		}
		else if (sliderSpeaker == ((CSliderCtrl *)pScrollBar))
		{
			PortSIP_setSpeakerVolume(m_SIPLib, sliderSpeaker->GetPos());
		}
	}

	CSliderCtrl * sliderVideoQuality = (CSliderCtrl *)GetDlgItem(IDC_SLIDER_VIDEO_QUALITY);
	if(sliderVideoQuality == (CSliderCtrl *)pScrollBar)
	{
		setVideoBitrate();
	}



	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CSIPSampleDlg::OnBnClickedBtnClear()
{
	m_LogList.ResetContent();
}

void CSIPSampleDlg::OnBnClickedChkCodecG711u()
{
	updateAudioCodecs();
}

void CSIPSampleDlg::OnBnClickedChkCodecG711a()
{
	updateAudioCodecs();
}

void CSIPSampleDlg::OnBnClickedChkCodecG729()
{
	updateAudioCodecs();
}

void CSIPSampleDlg::OnBnClickedChkCodecIlbc()
{
	updateAudioCodecs();
}

void CSIPSampleDlg::OnBnClickedChkCodecGsm()
{
	updateAudioCodecs();
}

void CSIPSampleDlg::OnBnClickedChkCodecG722()
{
	updateAudioCodecs();
}

void CSIPSampleDlg::OnBnClickedChkCodecSpeex()
{
	updateAudioCodecs();
}

void CSIPSampleDlg::OnBnClickedChkCodecSpeexwb()
{
	updateAudioCodecs();
}


void CSIPSampleDlg::OnBnClickedChkCodecOpus()
{
	// TODO: Add your control notification handler code here

	updateAudioCodecs();
}

void CSIPSampleDlg::OnBnClickedChkH263()
{
	updateVideoCodecs();
}

void CSIPSampleDlg::OnBnClickedChkH2631998()
{
	updateVideoCodecs();
}

void CSIPSampleDlg::OnBnClickedChkH264()
{
	updateVideoCodecs();
}

void CSIPSampleDlg::OnBnClickedCheck23()
{
	// TODO: Add your control notification handler code here

	updateVideoCodecs();
}



void CSIPSampleDlg::OnBnClickedChkAec()
{
	if (m_SIPInitialized == false)
	{
		::MessageBox(GetSafeHwnd(), "Please initialize the SDK first.", "Information", MB_ICONINFORMATION);
		return;
	}

	UpdateData(TRUE);

	if (m_AEC)
	{
		PortSIP_enableAEC(m_SIPLib, EC_DEFAULT);
	}
	else
	{
		PortSIP_enableAEC(m_SIPLib, EC_NONE);
	}	
}

void CSIPSampleDlg::OnBnClickedChkVad()
{
	if (m_SIPInitialized == false)
	{
		::MessageBox(GetSafeHwnd(), "Please initialize the SDK first.", "Information", MB_ICONINFORMATION);
		return;
	}

	UpdateData(TRUE);

	if (m_VAD)
	{
		PortSIP_enableVAD(m_SIPLib, true);
	}
	else
	{
		PortSIP_enableVAD(m_SIPLib, false);
	}
}

void CSIPSampleDlg::OnBnClickedChkCng()
{
	if (m_SIPInitialized == false)
	{
		::MessageBox(GetSafeHwnd(), "Please initialize the SDK first.", "Information", MB_ICONINFORMATION);
		return;
	}


	UpdateData(TRUE);

	if (m_CNG)
	{
		PortSIP_enableCNG(m_SIPLib, true);
	}
	else
	{
		PortSIP_enableCNG(m_SIPLib, false);
	}
}

void CSIPSampleDlg::OnBnClickedChkAgc()
{
	if (m_SIPInitialized == false)
	{
		::MessageBox(GetSafeHwnd(), "Please initialize the SDK first.", "Information", MB_ICONINFORMATION);
		return;
	}

	UpdateData(TRUE);

	if (m_AGC)
	{
		PortSIP_enableAGC(m_SIPLib, AGC_DEFAULT);
	}
	else
	{
		PortSIP_enableAGC(m_SIPLib, AGC_NONE);
	}
}

void CSIPSampleDlg::OnBnClickedChkAns()
{
	if (m_SIPInitialized == false)
	{
		::MessageBox(GetSafeHwnd(), "Please initialize the SDK first.", "Information", MB_ICONINFORMATION);
		return;
	}


	UpdateData(TRUE);

	if (m_ANS)
	{
		PortSIP_enableANS(m_SIPLib, NS_DEFAULT);
	}
	else
	{
		PortSIP_enableANS(m_SIPLib, NS_NONE);
	}
}

void CSIPSampleDlg::OnBnClickedChkNack()
{
	if (m_SIPInitialized == false)
	{
		::MessageBox(GetSafeHwnd(), "Please initialize the SDK first.", "Information", MB_ICONINFORMATION);
		return;
	}


	UpdateData(TRUE);

	if (m_ANS)
	{
		PortSIP_enableANS(m_SIPLib, NS_DEFAULT);
	}
	else
	{
		PortSIP_enableANS(m_SIPLib, NS_NONE);
	}
}

void CSIPSampleDlg::OnBnClickedBtnRecordDirectory()
{
	char szPath[MAX_PATH];
	BROWSEINFO br;
	ITEMIDLIST *pItem;
	br.hwndOwner = this->GetSafeHwnd();
	br.iImage = 0;
	br.pszDisplayName = 0;
	br.lParam = 0;
	br.lpfn = 0;
	br.lpszTitle = "Please select a folder:";
	br.pidlRoot = 0;
	br.ulFlags = BIF_RETURNONLYFSDIRS;
	pItem = SHBrowseForFolder(&br);

	if (SHGetPathFromIDList(pItem, szPath))
	{
		m_RecordFilePath = szPath;
		UpdateData(FALSE);
	}
}

void CSIPSampleDlg::OnBnClickedChkAudioStreamCallback()
{
	if (m_SIPInitialized == false)
	{
		::MessageBox(GetSafeHwnd(), "Please initialize the SDK first.", "Information", MB_ICONINFORMATION);
		return;
	}

	UpdateData(TRUE);

	if (m_AudioStreamCallback)
	{
		PortSIP_enableAudioStreamCallback(m_SIPLib,
											m_SessionArray[m_ActiveLine].getSessionId(),
											true, AUDIOSTREAM_REMOTE_PER_CHANNEL, this, audioRawCallback);
	}
	else
	{
		// Disable audio stream callback
		
		PortSIP_enableAudioStreamCallback(m_SIPLib, m_SessionArray[m_ActiveLine].getSessionId(), false, AUDIOSTREAM_NONE, NULL, NULL);

	}
}

void CSIPSampleDlg::OnBnClickedBtnStartAudioRecording()
{
	if (m_SIPInitialized == false)
	{
		::MessageBox(GetSafeHwnd(), "Please initialize the SDK first.", "Information", MB_ICONINFORMATION);
		return;
	}

	UpdateData(TRUE);
	if (m_RecordFilePath.IsEmpty() || m_RecordFileName.IsEmpty())
	{
		::MessageBox(GetSafeHwnd(), "The file path or file name is empty.", "Information", MB_ICONINFORMATION);
		return;
	}

	AUDIO_FILE_FORMAT fileFormat =  FILEFORMAT_WAVE;

	// Start recording
	if (PortSIP_startRecord(m_SIPLib, 
						m_SessionArray[m_ActiveLine].getSessionId(),
						m_RecordFilePath, 
						m_RecordFileName, 
						true, 
						fileFormat, 
						RECORD_BOTH,
						VIDEO_CODEC_H264,
						RECORD_RECV) != 0)
	{
		::MessageBox(GetSafeHwnd(), "Failed to tart record conversation.", "Information", MB_ICONINFORMATION);
		return;
	}

	::MessageBox(GetSafeHwnd(), "Start record conversation.", "Information", MB_ICONINFORMATION);
}

void CSIPSampleDlg::OnBnClickedBtnStopAudioRecording()
{
	if (m_SIPInitialized == false)
	{
		::MessageBox(GetSafeHwnd(), "Please initialize the SDK first.", "Information", MB_ICONINFORMATION);
		return;
	}


	PortSIP_stopRecord(m_SIPLib, m_SessionArray[m_ActiveLine].getSessionId());

	::MessageBox(GetSafeHwnd(), "Stop record conversation.", "Information", MB_ICONINFORMATION);
}


void CSIPSampleDlg::OnBnClickedBtnSelectPalyAudiofile()
{
	string playFilePath = "c:\\";

	CString Filter("WAV Files (*.wav)|*.wav||");
	CFileDialog FileDlg(TRUE, NULL, NULL, NULL, Filter);	


	FileDlg.m_ofn.lpstrInitialDir = playFilePath.c_str();

	if (FileDlg.DoModal() == IDOK)
	{
		m_PlayAudioFilePathName = FileDlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CSIPSampleDlg::OnBnClickedBtnStartPlayAudiofile()
{
	if (m_SIPInitialized == false)
	{
		::MessageBox(GetSafeHwnd(), "Please initialize the SDK first.", "Information", MB_ICONINFORMATION);
		return;
	}

	UpdateData(TRUE);

	PortSIP_playAudioFileToRemote(m_SIPLib,
									m_SessionArray[m_ActiveLine].getSessionId(), 
									(LPTSTR)(LPCTSTR)m_PlayAudioFilePathName, 
									16000,
									false);
}

void CSIPSampleDlg::OnBnClickedBtnStopPlayAudiofile()
{
	if (m_SIPInitialized == false)
	{
		::MessageBox(GetSafeHwnd(), "Please initialize the SDK first.", "Information", MB_ICONINFORMATION);
		return;
	}

	PortSIP_stopPlayAudioFileToRemote(m_SIPLib, m_SessionArray[m_ActiveLine].getSessionId());
}



int CSIPSampleDlg::videoRawCallback(void * obj, 
									 long sessionId,
									 VIDEOSTREAM_CALLBACK_MODE type, 
									 int width, 
									 int height, 
									 unsigned char * data, 
									 int dataLength)
{
/*
	!!! IMPORTANT !!!

	Don¡¯t call any PortSIP SDK API functions in here directly. If you want to call the PortSIP API functions or 
	other code which will spend long time, you should post a message to main thread(main window) or other thread,
	let the thread to call SDK API functions or other code.

	The video data format is YUV420.
*/

	CSIPSampleDlg * pthis = (CSIPSampleDlg *)obj;

	int index = LINE_BASE;


	if (type == VIDEOSTREAM_LOCAL)
	{

	}
	else if (type == VIDEOSTREAM_REMOTE)
	{

	}

	return 0;
}



int CSIPSampleDlg::audioRawCallback(void * obj, long sessionId, AUDIOSTREAM_CALLBACK_MODE type,unsigned char * data, int dataLength,int samplingFreqHz)
{
	CSIPSampleDlg * pthis = (CSIPSampleDlg *)obj;

/*
	!!! IMPORTANT !!!

	Don¡¯t call any PortSIP SDK API functions in here directly. If you want to call the PortSIP API functions or 
	other code which will spend long time, you should post a message to main thread(main window) or other thread,
	let the thread to call SDK API functions or other code.

*/

	// The data parameter is audio stream as PCM format, 16bit, Mono.
	// the dataLength parameter is audio steam data length.


	if (type == AUDIOSTREAM_LOCAL_PER_CHANNEL)
	{
		TRACE("audioRawCallback streamType = AUDIOSTREAM_LOCAL_PER_CHANNEL dataLen=%d\r\n",dataLength);
		// This is the audio stream which received from remote side
	}
	else if (type == AUDIOSTREAM_REMOTE_PER_CHANNEL)
	{
		TRACE("audioRawCallback streamType = AUDIOSTREAM_REMOTE_PER_CHANNEL dataLen=%d\r\n",dataLength);
		// This is audio stream which mixed of local sound card captured audio and received remote audio  
	}


	return 0;
}




int CSIPSampleDlg::receivedRTPPacket(void *obj, long sessionId, bool isAudio, unsigned char * RTPPacket, int packetSize)
{
/*
	!!! IMPORTANT !!!

	Don¡¯t call any PortSIP SDK API functions in here directly. If you want to call the PortSIP API functions or 
	other code which will spend long time, you should post a message to main thread(main window) or other thread,
	let the thread to call SDK API functions or other code.

*/

	return 0;
}


int CSIPSampleDlg::sendingRTPPacket(void *obj, long sessionId, bool isAudio, unsigned char * RTPPacket, int packetSize)
{
/*
	!!! IMPORTANT !!!

	Don¡¯t call any PortSIP SDK API functions in here directly. If you want to call the PortSIP API functions or 
	other code which will spend long time, you should post a message to main thread(main window) or other thread,
	let the thread to call SDK API functions or other code.

*/

	return 0;
}



void CSIPSampleDlg::OnBnClickedBtnEnableForward()
{
	if (m_SIPInitialized == false)
	{
		::MessageBox(GetSafeHwnd(), "Please initialize the SDK first.", "Information", MB_ICONINFORMATION);
		return;
	}

	UpdateData(TRUE);

	if (m_ForwardTo.Find("sip:")==-1 || m_ForwardTo.Find("@")==-1)
	{
		::MessageBoxA(GetSafeHwnd(), "The forward address must likes sip:xxxx@sip.portsip.com:5060", "Forward", MB_ICONINFORMATION);
		UpdateData(FALSE);

		return;
	}


	if (m_ForwardCallForBusy)
	{
		PortSIP_enableCallForward(m_SIPLib, true, (LPTSTR)(LPCTSTR)m_ForwardTo);
	}
	else
	{
		PortSIP_enableCallForward(m_SIPLib, false, (LPTSTR)(LPCTSTR)m_ForwardTo);
	}

	::MessageBoxA(GetSafeHwnd(), "The call forward is enabled.", "Forward", MB_ICONINFORMATION);
}

void CSIPSampleDlg::OnBnClickedBtnDisableForward()
{
	if (m_SIPInitialized == false)
	{
		::MessageBox(GetSafeHwnd(), "Please initialize the SDK first.", "Information", MB_ICONINFORMATION);
		return;
	}

	PortSIP_disableCallForward(m_SIPLib);

	::MessageBoxA(GetSafeHwnd(), "The call forward is disabled.", "Forward", MB_ICONINFORMATION);
}

void CSIPSampleDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == TIMER_EVENT_AUDIO_LEVEL)
	{
		if(m_SIPLib)
		{
			if (m_SessionArray[m_ActiveLine].getSessionState())
			{
				int  sendBytes = 0;
				int  sendPackets = 0;
				int  sendPacketsLost = 0;
				int  sendFractionLost = 0;
				int sendRttMS = 0;
				int  sendCodecType;
				int  sendJitterMS = 0;
				int  sendAudioLevel = 0;
				int  sendTotalInputEnergy = 0;

				int  recvBytes = 0;
				int  recvPackets = 0;
				int  recvPacketsLost = 0;
				int  recvFractionLost = 0;
				int  recvCodecType;
				int  recvJitterMS = 0;
				int  recvAudioLevel = 0;
				int  recvTotalOutputEnergys = 0;

				PortSIP_getAudioStatistics(m_SIPLib, m_SessionArray[m_ActiveLine].getSessionId(),
					&sendBytes, &sendPackets,
					&sendPacketsLost, &sendFractionLost,
					&sendRttMS,
					&sendCodecType,
					&sendJitterMS, &sendAudioLevel,
					&recvBytes, &recvPackets,
					&recvPacketsLost, &recvFractionLost,
					&recvCodecType, &recvJitterMS,
					&recvAudioLevel);

				m_progSpeakerLevel.SetPos(recvAudioLevel);
				m_progMicroLevel.SetPos(sendAudioLevel);
			}
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CSIPSampleDlg::OnBnClickedBtnLocalVideo()
{
	if (m_SIPInitialized == false)
	{
		return;
	}

	UpdateData(TRUE);

	CString Text;
	GetDlgItem(IDC_BUTTON27)->GetWindowText(Text);
	if (Text == "Local Video")
	{
		PortSIP_displayLocalVideo(m_SIPLib, true);
		GetDlgItem(IDC_BUTTON27)->SetWindowText("Stop Local");
	}
	else
	{
		PortSIP_displayLocalVideo(m_SIPLib, false);
		GetDlgItem(IDC_BUTTON27)->SetWindowText("Local Video");
	}
}

void CSIPSampleDlg::OnBnClickedBtnVideoOptions()
{
	PortSIP_sendOptions(m_SIPLib, "loadtest11", "");
	if (!m_SIPLib)
	{
		return;
	}

	char szCameraName[256];
	m_CamerasList.GetLBText(m_CamerasList.GetCurSel(),szCameraName);

	PortSIP_showVideoCaptureSettingsDialogBox(m_SIPLib, szCameraName,strlen(szCameraName),"Camera Options",GetSafeHwnd(),200,200);
}

void CSIPSampleDlg::OnBnClickedBtnSendVideo()
{
	if (m_SIPInitialized==false || (m_NeedRegister&&m_SIPRegistered==false))
	{
		return;
	}

	if (m_SessionArray[m_ActiveLine].getSessionState() == false && m_SessionArray[m_ActiveLine].getRecvCallState() == false)
	{
		return;
	}


	PortSIP_sendVideo(m_SIPLib, m_SessionArray[m_ActiveLine].getSessionId(), true);
}

void CSIPSampleDlg::OnBnClickedBtnStopVideo()
{
	if (m_SIPInitialized==false || (m_NeedRegister&&m_SIPRegistered==false))
	{
		return;
	}

	if (m_SessionArray[m_ActiveLine].getSessionState() == false)
	{
		return;
	}


	PortSIP_sendVideo(m_SIPLib, m_SessionArray[m_ActiveLine].getSessionId(), false);
}


void CSIPSampleDlg::OnBnClickedCheck24()
{
	// TODO: Add your control notification handler code here

	updatePrackSetting();
}



LRESULT CSIPSampleDlg::OnSIPCallbackEvent(WPARAM WParam, LPARAM LParam)
{
	ICallbackParameters * parameter = (ICallbackParameters *)WParam;

	switch(parameter->getEventType())
	{
	case SIP_UNKNOWN:
		break;

	case SIP_REGISTER_SUCCESS:
		{
			m_LogList.InsertString(m_LogList.GetCount(), "Registration succeeded.");
			m_SIPRegistered = true;
		}
		break;

	case SIP_REGISTER_FAILURE:
		m_LogList.InsertString(m_LogList.GetCount(), "Registration failed.");
		m_SIPRegistered = false;
		break;

	case SIP_INVITE_INCOMING:
		onSIPCallIncoming(parameter);
		break;

	case SIP_INVITE_TRYING:
		onSIPCallTrying(parameter);
		break;

	case SIP_INVITE_SESSION_PROGRESS:
		onSIPCallSessionProgress(parameter);
		break;

	case SIP_INVITE_RINGING:
		onSIPCallRinging(parameter);
		break;

	case SIP_INVITE_ANSWERED:
		onSIPCallAnswered(parameter);
		break;

	case SIP_INVITE_FAILURE:
		onSIPCallFailure(parameter);
		break;

	case SIP_INVITE_UPDATED:
		onSIPInviteUpdated(parameter);
		break;


	case SIP_INVITE_CONNECTED:
		onSIPInviteConnected(parameter);
		break;

	case SIP_INVITE_BEGINING_FORWARD:
		onSIPCallForwarding(parameter);
		break;

	case SIP_INVITE_CLOSED:
		onSIPCallClosed(parameter);
		break;


	case SIP_DIALOG_STATE_UPDATED:
		onSIPDialogStateUpdated(parameter);
		break;


	case SIP_REMOTE_HOLD:
		onSIPCallRemoteHold(parameter);
		break;

	case SIP_REMOTE_UNHOLD:
		onSIPCallRemoteUnhold(parameter);
		break;

	case SIP_RECEIVED_REFER:
		onSIPReceivedRefer(parameter);
		break;


	case SIP_REFER_ACCEPTED:
		onSIPReferAccepted(parameter);
		break;


	case SIP_REFER_REJECTED:
		onSIPReferRejected(parameter);
		break;


	case SIP_TRANSFER_TRYING:
		onSIPTransferTrying(parameter);
		break;


	case SIP_TRANSFER_RINGING:
		onSIPTransferRinging(parameter);
		break;

	case SIP_ACTV_TRANSFER_SUCCESS:
		onSIPACTVTransferSuccess(parameter);
		break;

	case SIP_ACTV_TRANSFER_FAILURE:
		onSIPACTVTrasferFailure(parameter);
		break;

	case SIP_RECEIVED_SIGNALING:
		{
			const char* data = parameter->getSignaling();
		}
		break;

	case SIP_SENDING_SIGNALING:
		{
			const char* data = parameter->getSignaling();
		}
		break;



	case SIP_WAITING_VOICEMESSAGE:
		{
			const char* messageAcount = parameter->getWaitingMessageAccount();
			int urgentNewMessageCount = parameter->getUrgentNewWaitingMessageCount();
			int urgentOldMessageCount = parameter->getUrgentOldWaitingMessageCount();
			int newMessageCount = parameter->getNewWaitingMessageCount();
			int oldMessageCount = parameter->getOldWaitingMessageCount();

			CString Text = "Has voice messages, message account: ";
			Text += messageAcount;
			Text += "";

			m_LogList.InsertString(m_LogList.GetCount(), Text);
		}
		break;


	case SIP_WAITING_FAXMESSAGE:
		{
			const char* messageAcount = parameter->getWaitingMessageAccount();
			int urgentNewFaxCount = parameter->getUrgentNewWaitingMessageCount();
			int urgentOldFaxCount = parameter->getUrgentOldWaitingMessageCount();
			int newFaxCount = parameter->getNewWaitingMessageCount();
			int oldFaxCount = parameter->getOldWaitingMessageCount();

			CString Text = "Has FAX messages, message account: ";
			Text += messageAcount;
			Text += "";

			m_LogList.InsertString(m_LogList.GetCount(), Text);
		}


	case SIP_RECV_DTMFTONE:
		onSIPReceivedDtmfTone(parameter);
		break;

	case SIP_PRESENCE_RECV_SUBSCRIBE:
		break;

	case SIP_PRESENCE_ONLINE:
		break;


	case SIP_PRESENCE_OFFLINE:
		break;


	case SIP_RECV_OPTIONS:
		onSIPRecvOptions(parameter);
		break;

	case SIP_RECV_INFO:
		onSIPRecvInfo(parameter);
		break;

	case SIP_RECV_NOTIFY_OF_SUBSCRIPTION:
		onSIPRecvNotifyOfSubscription(parameter);
		break;

	case SIP_SUBSCRIPTION_FAILURE:
		onSIPSubscriptionFailure(parameter);
		break;

	case SIP_SUBSCRIPTION_TERMINATED:
		onSIPSubscriptionTerminated(parameter);
		break;


	case SIP_RECV_MESSAGE:
		onSIPRecvMesage(parameter);
		break;

	case SIP_RECV_OUTOFDIALOG_MESSAGE:
		onSIPRecvOutOfDialogMessage(parameter);
		break;

	case SIP_SEND_MESSAGE_SUCCESS:
		onSIPSendMessageSuccess(parameter);
		break;


	case SIP_SEND_MESSAGE_FAILURE:
		onSIPSendMessageFailure(parameter);
		break;

	case SIP_SEND_OUTOFDIALOG_MESSAGE_SUCCESS:
		onSIPSendOutOfDialogMessageSuccess(parameter);
		break;


	case SIP_SEND_OUTOFDIALOG_MESSAGE_FAILURE:
		onSIPSendOutOfDialogMessageFailure(parameter);
		break;

	case SIP_PLAY_AUDIO_FILE_FINISHED:

		break;


	case SIP_PLAY_VIDEO_FILE_FINISHED:

		break;

	}

	PortSIP_delCallbackParameters(parameter);
	parameter = NULL;

	return S_OK;
}




void CSIPSampleDlg::onSIPCallIncoming(ICallbackParameters * parameters)
{
	UpdateData(TRUE);

	int index = -1;
	for (int i=LINE_BASE; i<MAX_LINES; ++i)
	{
		if (m_SessionArray[i].getSessionState()==false && m_SessionArray[i].getRecvCallState()==false)
		{
			m_SessionArray[i].setRecvCallState(true);
			index = i;
			break;
		}
	}

	if (index == -1)
	{
		PortSIP_rejectCall(m_SIPLib, parameters->getSessionId(), 486);
		return;
	}

	if (parameters->getExistsAudio())
	{
		// This incoming call has audio

		// If more than one codecs using, then they are separated with "#",
		// for example: "g.729#GSM#AMR", "H264#H263", you have to parse them by yourself.

		const char* audioCodecs = parameters->getAudioCodecs();
	}


	// Checking does this call has video
	if (parameters->getExistsVideo() == true)
	{
		// This incoming call has video

		// If more than one codecs using, then they are separated with "#",
		// for example: "g.729#GSM#AMR", "H264#H263", you have to parse them by yourself.

		const char* videoCodecs = parameters->getVideoCodecs();
	}

	// Search in all lines, ignore the auto answer if have a line is established.
	bool needIgnoreAutoAnswer = false;
	for (int i=LINE_BASE; i<MAX_LINES; ++i)
	{
		if (m_SessionArray[i].getSessionState() == true)
		{
			needIgnoreAutoAnswer = true; // Need to ignore the auto answer
			break;
		}
	}

	m_SessionArray[index].setSessionId(parameters->getSessionId());
	if (parameters->getExistsVideo() == true)
	{
		PortSIP_setRemoteVideoWindow(m_SIPLib, m_SessionArray[index].getSessionId(), m_RemoteVideo.GetSafeHwnd());
	}


	if (needIgnoreAutoAnswer==false && m_AA)
	{
		m_SessionArray[index].setSessionState(true);
		m_SessionArray[index].setRecvCallState(false);

		bool answerVideoCall = false;
		if (m_AnswerVideoCall)
		{
			answerVideoCall = true;
		}
		int rt = PortSIP_answerCall(m_SIPLib, parameters->getSessionId(), answerVideoCall);
		if (rt == 0)
		{
			stringstream log;
			log << "Answered the call on line " << index << " by Auto Answer";
			m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());
		}
		else
		{
			m_SessionArray[index].reset();

			stringstream log;
			log << "Failed to answer call on line " << index << " by Auto Answer";
			m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());	
		}

		return;
	}

	const char* caller = parameters->getCaller();

	stringstream log;
	log << "Incoming call from " << caller << " on line " << index <<"";
	m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());
}


void CSIPSampleDlg::onSIPCallTrying(ICallbackParameters * parameters)
{
	int index = findSession(parameters->getSessionId());
	if (index == -1)
	{
		return;
	}

	stringstream text;
	text << "Call is trying on line " << index << "";
	m_LogList.InsertString(m_LogList.GetCount(), text.str().c_str());	
}



void CSIPSampleDlg::onSIPCallSessionProgress(ICallbackParameters * parameters)
{
	int index = findSession(parameters->getSessionId());
	if (index == -1)
	{
		return;
	}

	if (parameters->getExistsEarlyMedia())
	{
		// Checking does this call has video
		if (parameters->getExistsVideo())
		{
			// This incoming call has video
			// If more than one codecs using, then they are separated with "#",
			// for example: "g.729#GSM#AMR", "H264#H263", you have to parse them by yourself.
			const char* videoCodecs = parameters->getVideoCodecs();
		}

		if (parameters->getExistsAudio())
		{
			// If more than one codecs using, then they are separated with "#",
			// for example: "g.729#GSM#AMR", "H264#H263", you have to parse them by yourself.

			const char* audioCodecs = parameters->getAudioCodecs();
		}
	}

	m_SessionArray[index].setExistEarlyMedia(parameters->getExistsEarlyMedia());

	stringstream log;
	log << "Call session progress on line  " << index << "";
	m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());
}

void CSIPSampleDlg::onSIPCallRinging(ICallbackParameters * parameters)
{
	int index = findSession(parameters->getSessionId());
	if (index == -1)
	{
		return;
	}

	if (!m_SessionArray[index].getExistEarlyMedia())
	{
		// No early media, you must play the local WAVE file for ringing tone
	}

	stringstream log;
	log << "Call ringing on line " << index << "";
	m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());
}



void CSIPSampleDlg::onSIPCallAnswered(ICallbackParameters * parameters)
{
	int index = findSession(parameters->getSessionId());
	if (index == -1)
	{
		return;
	}

	// If more than one codecs using, then they are separated with "#",
	// for example: "g.729#GSM#AMR", "H264#H263", you have to parse them by yourself.
	// Checking does this call has video
	if (parameters->getExistsVideo())
	{
		const char* videoCodecs = parameters->getVideoCodecs();
	}

	if (parameters->getExistsAudio())
	{
		// Audio codecs name
		const char* audioCodecs = parameters->getAudioCodecs();
	}

	m_SessionArray[index].setSessionState(true);

	stringstream log;
	log << "Call Established on line " << index << "";
	m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());

	// If this is the refer call then need set it to normal
	if (m_SessionArray[index].isReferCall())
	{
		m_SessionArray[index].setReferCall(false, 0);
	}

	joinConference(index);
}


void CSIPSampleDlg::onSIPCallFailure(ICallbackParameters * parameters)
{
	int index = findSession(parameters->getSessionId());
	if (index == -1)
	{
		return;
	}

	int statusCode = parameters->getStatusCode();
	const char* statusText= parameters->getStatusText();

	stringstream log;
	log << "Failed to call on line " << index << ": " << statusText << " " << statusCode << "";
	m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());

	if (m_SessionArray[index].isReferCall())
	{
		// Take off the origin call from HOLD if the refer call is failure
		long originIndex = -1;
		for (int i=LINE_BASE; i<MAX_LINES; ++i)
		{
			// Looking for the origin call
			if (m_SessionArray[i].getSessionId() == m_SessionArray[index].getOriginCallSessionId())
			{
				originIndex = i;
				break;
			}
		}

		if (originIndex != -1)
		{
			stringstream log;
			log << "Call failure on line " << index << ": " << statusText << " " << statusCode << "";
			m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());

			// Now take off the origin call
			PortSIP_unHold(m_SIPLib, m_SessionArray[index].getOriginCallSessionId());
			m_SessionArray[originIndex].setHoldState(false);

			// Switch the currently line to origin call line
			m_ActiveLine = originIndex;
			m_LineList.SetCurSel(m_ActiveLine-1);

			log.str("");
			log << "Current line is: " << m_ActiveLine;
			m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());
		}
	}

	m_SessionArray[index].reset();
}


void CSIPSampleDlg::onSIPInviteUpdated(ICallbackParameters * parameters)
{
	int index = findSession(parameters->getSessionId());
	if (index == -1)
	{
		return;
	}

	// Checking does this call has video
	if (parameters->getExistsVideo())
	{
		const char* videoCodecs = parameters->getVideoCodecs();
	}
	if (parameters->getExistsAudio())
	{
		const char* audioCodecs = parameters->getAudioCodecs();
	}

	stringstream log;
	log << "The call has been updated on line " << index << "";

	m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());
}


void CSIPSampleDlg::onSIPInviteConnected(ICallbackParameters * parameters)
{
	int index = findSession(parameters->getSessionId());
	if (index == -1)
	{
		return;
	}
	stringstream log;
	log << "The call is connected on line " << index << "";
	m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());
}


void CSIPSampleDlg::onSIPCallForwarding(ICallbackParameters * parameters)
{
	const char* value = parameters->getForwardTo();

	stringstream text;
	text << "Call has been forward to: " << value;
	m_LogList.InsertString(m_LogList.GetCount(), text.str().c_str());	
}



void CSIPSampleDlg::onSIPCallClosed(ICallbackParameters * parameters)
{
	int index = findSession(parameters->getSessionId());
	if (index == -1)
	{
		return;
	}

	stringstream log;
	log << "Call closed by remote on line " << index << "";
	m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());
	m_SessionArray[index].reset();
}


void CSIPSampleDlg::onSIPDialogStateUpdated(ICallbackParameters * parameters)
{
	stringstream log;

	const char * uri = parameters->getBLFMonitoredUri();
	const char * state = parameters->getBLFDialogState();
	const char * dialogId = parameters->getBLFDialogId();
	const char * direction = parameters->getBLFDialogDirection();

	log << "The user: " << uri << " dialog state is updated: " << state << ", dialog id: " << dialogId << ", direction: " << direction;
	m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());
}


void CSIPSampleDlg::onSIPCallRemoteHold(ICallbackParameters * parameters)
{
	int index = findSession(parameters->getSessionId());
	if (index == -1)
	{
		return;
	}

	stringstream log;
	log << "Placed on hold by remote on line " << index << "";
	m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());
}


void CSIPSampleDlg::onSIPCallRemoteUnhold(ICallbackParameters * parameters)
{
	int index = findSession(parameters->getSessionId());
	if (index == -1)
	{
		return;
	}

	stringstream log;
	log << "Take off hold by remote on line " << index << "";
	m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());
}


void CSIPSampleDlg::onSIPReceivedRefer(ICallbackParameters * parameters)
{
	int index = findSession(parameters->getSessionId());
	if (index == -1)
	{
		PortSIP_rejectRefer(m_SIPLib, parameters->getReferId());
		return;
	}


	const char* referTo= parameters->getReferTo();
	const char* signaling = parameters->getSignaling();


	stringstream log;
	log << "Received the refer on line " << index << ", refer to " << referTo;
	m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());

	// Accept the REFER automatically
	long referSessionId = PortSIP_acceptRefer(m_SIPLib, parameters->getReferId(), signaling);
	if (referSessionId <= 0)
	{
		log.str("");
		log << "Failed to accept the refer.";
		m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());
	}
	else
	{
		PortSIP_hangUp(m_SIPLib, m_SessionArray[index].getSessionId());
		m_SessionArray[index].reset();


		m_SessionArray[index].setSessionId(referSessionId);
		m_SessionArray[index].setSessionState(true);

		log.str("");
		log << "Accepted the refer";
		m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());
	}
}


void CSIPSampleDlg::onSIPReferAccepted(ICallbackParameters * parameters)
{
	int index = findSession(parameters->getSessionId());
	if (index == -1)
	{
		return;
	}

	stringstream log;
	log << "Line " << index << ", the REFER was accepted.";
	m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());
}


void CSIPSampleDlg::onSIPReferRejected(ICallbackParameters * parameters)
{
	int index = findSession(parameters->getSessionId());
	if (index == -1)
	{
		return;
	}

	stringstream log;
	log << "LINE " << index << ", the REFER was rejected.";
	m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());
}



void CSIPSampleDlg::onSIPTransferTrying(ICallbackParameters * parameters)
{
	int index = findSession(parameters->getSessionId());
	if (index == -1)
	{
		return;
	}

	const char* referTo = parameters->getReferTo();

	stringstream log;
	log << "Transfer trying on line " << index << "";
	m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());
}


void CSIPSampleDlg::onSIPTransferRinging(ICallbackParameters * parameters)
{
	int index = findSession(parameters->getSessionId());
	if (index == -1)
	{
		return;
	}

	stringstream log;
	log << "Transfer ringing on line " << index << "";
	m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());
}


void CSIPSampleDlg::onSIPACTVTransferSuccess(ICallbackParameters * parameters)
{
	int index = findSession(parameters->getSessionId());
	if (index == -1)
	{
		return;
	}

	PortSIP_hangUp(m_SIPLib, m_SessionArray[index].getSessionId());
	m_SessionArray[index].reset();

	stringstream log;
	log << "Transfer succeeded on line "<< index << ", close the call";
	m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());
}




void CSIPSampleDlg::onSIPACTVTrasferFailure(ICallbackParameters * parameters)
{
	int index = findSession(parameters->getSessionId());
	if (index == -1)
	{
		return;
	}

	stringstream log;
	log << "Failed to transfer on line " << index << "";
	m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());

	const char* reason = parameters->getStatusText();
	int code = parameters->getStatusCode(); // error code

}



void CSIPSampleDlg::onSIPReceivedDtmfTone(ICallbackParameters * parameters)
{
	int index = findSession(parameters->getSessionId());
	if (index == -1)
	{
		return;
	}

	stringstream log;
	int tone = parameters->getDTMFTone();

	log << "Received DTMF tone: ";
	if (tone == 10)
	{
		log << "*";
	}
	else if (tone == 11)
	{
		log << "#";
	}
	else if (tone == 12)
	{
		log << "A";
	}
	else if (tone == 13)
	{
		log << "B";
	}
	else if (tone == 14)
	{
		log << "C";
	}
	else if (tone == 15)
	{
		log << "D";
	}
	else if (tone == 16)
	{
		log << "FLASH";
	}
	else 
	{
		log << tone;
	}

	log << " on line " << index;
	m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());

}



void CSIPSampleDlg::onSIPRecvOptions(ICallbackParameters * parameters)
{
	const char* data = parameters->getSignaling();

	stringstream Text;
	Text << "Received an OPTIONS message: ";
	Text << data;
}

void CSIPSampleDlg::onSIPRecvInfo(ICallbackParameters * parameters)
{	
	int index = findSession(parameters->getSessionId());
	if (index == -1)
	{
		return;
	}

	const char* data = parameters->getSignaling();

	stringstream Text;
	Text << "Received a INFO message on line " << index << ": ";
	Text << data;

	::MessageBoxA(GetSafeHwnd(), Text.str().c_str(), "Received a INFO message", MB_ICONINFORMATION);
}


void CSIPSampleDlg::onSIPRecvNotifyOfSubscription(ICallbackParameters * parameter)
{
	const char * sipMsg = parameter->getSignaling();
	const unsigned char * contentData = parameter->getMessageData();
	int contentDataSize = parameter->getMessageDataLength();
}


void CSIPSampleDlg::onSIPSubscriptionFailure(ICallbackParameters * parameter)
{
	stringstream Text;
	Text << "Failed to send the SUBSCRIBE id = " << parameter->getSubscribeId();
}

void CSIPSampleDlg::onSIPSubscriptionTerminated(ICallbackParameters * parameter)
{
	stringstream Text;
	Text << "The subscription has been terminated: id = " << parameter->getSubscribeId();

}


void CSIPSampleDlg::onSIPRecvMesage(ICallbackParameters * parameters)
{
	int index = findSession(parameters->getSessionId());
	if (index == -1)
	{
		return;
	}

	const char* mimeType = parameters->getMimeType();
	const char* subMimeType = parameters->getSubMimeType();

	const unsigned char * data = parameters->getMessageData();
	int len = parameters->getMessageDataLength();

	if (strstr(mimeType, "text") && strstr(subMimeType, "plain"))
	{
		stringstream Text;
		Text << "Received a MESSAGE message on line " << index << ": ";
		Text << data;
		::MessageBoxA(GetSafeHwnd(), Text.str().c_str(), "Received a MESSAGE message", MB_ICONINFORMATION);
	}
	else if (strstr(mimeType, "application") && (strstr(subMimeType, "vnd.3gpp.sms") || strstr(subMimeType, "vnd.3gpp2.sms")))
	{
		stringstream Text;
		Text << "Received a binary MESSAGE message on line " << index;
		::MessageBoxA(GetSafeHwnd(), Text.str().c_str(), "Received a MESSAGE message", MB_ICONINFORMATION);
	}
}


void CSIPSampleDlg::onSIPRecvOutOfDialogMessage(ICallbackParameters * parameters)
{
	const char* mimeType = parameters->getMimeType();
	const char* subMimeType = parameters->getSubMimeType();

	const unsigned char * data = parameters->getMessageData();
	int len = parameters->getMessageDataLength();

	if (strstr(mimeType, "text") && strstr(subMimeType, "plain"))
	{
		stringstream Text;
		Text << "Received a MESSAGE message out of dialog: ";
		Text << data;
		::MessageBoxA(GetSafeHwnd(), Text.str().c_str(), "Received a out of dialog MESSAGE message", MB_ICONINFORMATION);
	}
	else if (strstr(mimeType, "application") && (strstr(subMimeType, "vnd.3gpp.sms") || strstr(subMimeType, "vnd.3gpp2.sms")))
	{
		stringstream Text;
		Text << "Received a binary MESSAGE message out of dialog.";
		::MessageBoxA(GetSafeHwnd(), Text.str().c_str(), "Received a MESSAGE message", MB_ICONINFORMATION);
	}
}


void CSIPSampleDlg::onSIPSendMessageSuccess(ICallbackParameters * parameters)
{
	int index = findSession(parameters->getSessionId());
	if (index == -1)
	{
		return;
	}

	stringstream log;
	log << "Send message succeed on line " << index;
	m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());
}


void CSIPSampleDlg::onSIPSendMessageFailure(ICallbackParameters * parameters)
{
	int index = findSession(parameters->getSessionId());
	if (index == -1)
	{
		return;
	}

	stringstream log;
	log << "Send message failure on line " << index;
	m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());
}


void CSIPSampleDlg::onSIPSendOutOfDialogMessageSuccess(ICallbackParameters * parameters)
{
	m_LogList.InsertString(m_LogList.GetCount(), "Send out of dialog message succeed.");
}


void CSIPSampleDlg::onSIPSendOutOfDialogMessageFailure(ICallbackParameters * parameters)
{
	m_LogList.InsertString(m_LogList.GetCount(), "Send out of dialog message failure.");
}


void CSIPSampleDlg::onSIPPlayAudioFileFinished(ICallbackParameters * parameters)
{
	int index = findSession(parameters->getSessionId());
	if (index == -1)
	{
		return;
	}

	const char* audioFileName = parameters->getPlayedAudioFileName();

	stringstream log;
	log << "Play audio file: " << audioFileName << " is finished on line " << index;
	m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());
}


void CSIPSampleDlg::onSIPPlayVideoFileFinished(ICallbackParameters * parameters)
{
	int index = findSession(parameters->getSessionId());
	if (index == -1)
	{
		return;
	}

	stringstream log;
	log << "Play video file is finished on line " << index;
	m_LogList.InsertString(m_LogList.GetCount(), log.str().c_str());
}

