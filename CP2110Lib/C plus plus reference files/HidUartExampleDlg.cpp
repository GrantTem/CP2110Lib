/////////////////////////////////////////////////////////////////////////////
// HidUartExampleDlg.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HidUartExample.h"
#include "HidUartExampleDlg.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// Namespaces
/////////////////////////////////////////////////////////////////////////////

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// Linker library inputs
/////////////////////////////////////////////////////////////////////////////

#pragma comment(lib, "SLABHIDtoUART.lib")

/////////////////////////////////////////////////////////////////////////////
// Static Global Variables
/////////////////////////////////////////////////////////////////////////////

enum CHECKBOX_STYLE
{
    CBS_Default,        // Tri-state = false, Read-only = false
    CBS_ReadOnly,       // Tri-state = false, Read-only = true
    CBS_Indeterminate   // Tri-state = true,  Read-only = true
};

// Set status bar pane 0 indicator
static UINT BASED_CODE StatusBarIndicators[] =
{
    ID_INDICATOR_STATUS
};

static TCHAR* CP2110_PinCaptions[] =
{
//    Pin Modes:
//    Input         Output_OD     Output_PP     Function1        Function2
//    -----         ---------     ---------     ---------        ---------
/*0*/ _T("GPIO.0"), _T("GPIO.0"), _T("GPIO.0"), _T("CLK"),       _T(""), 
/*1*/ _T("GPIO.1"), _T("GPIO.1"), _T("GPIO.1"), _T("RTS"),       _T(""), 
/*2*/ _T("GPIO.2"), _T("GPIO.2"), _T("GPIO.2"), _T("CTS"),       _T(""), 
/*3*/ _T("GPIO.3"), _T("GPIO.3"), _T("GPIO.3"), _T("RS485"),     _T(""), 
/*4*/ _T("GPIO.4"), _T("GPIO.4"), _T("GPIO.4"), _T("TX Toggle"), _T(""), 
/*5*/ _T("GPIO.5"), _T("GPIO.5"), _T("GPIO.5"), _T("RX Toggle"), _T(""), 
/*6*/ _T("GPIO.6"), _T("GPIO.6"), _T("GPIO.6"), _T(""),          _T(""), 
/*7*/ _T("GPIO.7"), _T("GPIO.7"), _T("GPIO.7"), _T(""),          _T(""), 
/*8*/ _T("GPIO.8"), _T("GPIO.8"), _T("GPIO.8"), _T(""),          _T(""), 
/*9*/ _T("GPIO.9"), _T("GPIO.9"), _T("GPIO.9"), _T(""),          _T(""), 
};

static TCHAR* CP2110_PinDirections[] =
{
//    Pin Modes:
//    Input          Output_OD          Output_PP          Function1          Function2
//    -----          ---------          ---------          ---------          ---------
/*0*/ _T("(Input)"), _T("(Output OD)"), _T("(Output PP)"), _T("(Output PP)"), _T(""), 
/*1*/ _T("(Input)"), _T("(Output OD)"), _T("(Output PP)"), _T("(Output OD)"), _T(""), 
/*2*/ _T("(Input)"), _T("(Output OD)"), _T("(Output PP)"), _T("(Input)"),     _T(""), 
/*3*/ _T("(Input)"), _T("(Output OD)"), _T("(Output PP)"), _T("(Output OD)"), _T(""), 
/*4*/ _T("(Input)"), _T("(Output OD)"), _T("(Output PP)"), _T("(Output PP)"), _T(""), 
/*5*/ _T("(Input)"), _T("(Output OD)"), _T("(Output PP)"), _T("(Output PP)"), _T(""), 
/*6*/ _T("(Input)"), _T("(Output OD)"), _T("(Output PP)"), _T(""),            _T(""), 
/*7*/ _T("(Input)"), _T("(Output OD)"), _T("(Output PP)"), _T(""),            _T(""), 
/*8*/ _T("(Input)"), _T("(Output OD)"), _T("(Output PP)"), _T(""),            _T(""), 
/*9*/ _T("(Input)"), _T("(Output OD)"), _T("(Output PP)"), _T(""),            _T(""), 
};

static CHECKBOX_STYLE CP2110_PinStyle[] =
{
//    Pin Modes:
//    Input         Output_OD    Output_PP    Function1          Function2
//    -----         ---------    ---------    ---------          ---------
/*0*/ CBS_ReadOnly, CBS_Default, CBS_Default, CBS_Indeterminate, CBS_Indeterminate, 
/*1*/ CBS_ReadOnly, CBS_Default, CBS_Default, CBS_Indeterminate, CBS_Indeterminate, 
/*2*/ CBS_ReadOnly, CBS_Default, CBS_Default, CBS_Indeterminate, CBS_Indeterminate, 
/*3*/ CBS_ReadOnly, CBS_Default, CBS_Default, CBS_Indeterminate, CBS_Indeterminate, 
/*4*/ CBS_ReadOnly, CBS_Default, CBS_Default, CBS_Indeterminate, CBS_Indeterminate, 
/*5*/ CBS_ReadOnly, CBS_Default, CBS_Default, CBS_Indeterminate, CBS_Indeterminate, 
/*6*/ CBS_ReadOnly, CBS_Default, CBS_Default, CBS_Indeterminate, CBS_Indeterminate, 
/*7*/ CBS_ReadOnly, CBS_Default, CBS_Default, CBS_Indeterminate, CBS_Indeterminate, 
/*8*/ CBS_ReadOnly, CBS_Default, CBS_Default, CBS_Indeterminate, CBS_Indeterminate, 
/*9*/ CBS_ReadOnly, CBS_Default, CBS_Default, CBS_Indeterminate, CBS_Indeterminate, 
};

static TCHAR* CP2114_PinCaptions[] =
{
//    Pin Modes:
//    Input          Output_OD      Output_PP      Function1               Function2
//    -----          ---------      ---------      ---------               ---------
/*0*/ _T("GPIO.0"),  _T("GPIO.0"),  _T("GPIO.0"),  _T("Record Mute"),      _T(""), 
/*1*/ _T("GPIO.1"),  _T("GPIO.1"),  _T("GPIO.1"),  _T("Play Mute"),        _T(""), 
/*2*/ _T("GPIO.2"),  _T("GPIO.2"),  _T("GPIO.2"),  _T("Volume Down"),      _T(""), 
/*3*/ _T("GPIO.3"),  _T("GPIO.3"),  _T("GPIO.3"),  _T("Volume Up"),        _T(""), 
/*4*/ _T("GPIO.4"),  _T("GPIO.4"),  _T("GPIO.4"),  _T("LED1 Record Mute"), _T(""), 
/*5*/ _T("GPIO.5"),  _T("GPIO.5"),  _T("GPIO.5"),  _T("TX Toggle"),        _T("DAC S0"), 
/*6*/ _T("GPIO.6"),  _T("GPIO.6"),  _T("GPIO.6"),  _T("RX Toggle"),        _T("DAC S1"), 
/*7*/ _T("GPIO.7"),  _T("GPIO.7"),  _T("GPIO.7"),  _T("RTS"),              _T("DAC S2"), 
/*8*/ _T("GPIO.8"),  _T("GPIO.8"),  _T("GPIO.8"),  _T("CTS"),              _T("DAC S3"), 
/*9*/ _T("GPIO.9"),  _T("GPIO.9"),  _T("GPIO.9"),  _T("CLK"),              _T(""), 
/*10*/_T("GPIO.10"), _T("GPIO.10"), _T("GPIO.10"), _T("TX"),               _T("TX"), 
/*11*/_T("GPIO.11"), _T("GPIO.11"), _T("GPIO.11"), _T("RX"),               _T("N/A"), 
};

static TCHAR* CP2114_PinDirections[] =
{
//    Pin Modes:
//    Input          Output_OD          Output_PP          Function1          Function2
//    -----          ---------          ---------          ---------          ---------
/*0*/ _T("(Input)"), _T("(Output OD)"), _T("(Output PP)"), _T("(Input)"),     _T(""), 
/*1*/ _T("(Input)"), _T("(Output OD)"), _T("(Output PP)"), _T("(Input)"),     _T(""), 
/*2*/ _T("(Input)"), _T("(Output OD)"), _T("(Output PP)"), _T("(Input)"),     _T(""), 
/*3*/ _T("(Input)"), _T("(Output OD)"), _T("(Output PP)"), _T("(Input)"),     _T(""), 
/*4*/ _T("(Input)"), _T("(Output OD)"), _T("(Output PP)"), _T("(Output PP)"), _T(""), 
/*5*/ _T("(Input)"), _T("(Output OD)"), _T("(Output PP)"), _T("(Output PP)"), _T("(Input)"), 
/*6*/ _T("(Input)"), _T("(Output OD)"), _T("(Output PP)"), _T("(Output PP)"), _T("(Input)"), 
/*7*/ _T("(Input)"), _T("(Output OD)"), _T("(Output PP)"), _T("(Output OD)"), _T("(Input)"), 
/*8*/ _T("(Input)"), _T("(Output OD)"), _T("(Output PP)"), _T("(Input)"),     _T("(Input)"), 
/*9*/ _T("(Input)"), _T("(Output OD)"), _T("(Output PP)"), _T("(Output PP)"), _T(""), 
/*10*/_T("(Input)"), _T("(Output OD)"), _T("(Output PP)"), _T("(Output OD)"), _T("(Output PP)"), 
/*11*/_T("(Input)"), _T("(Output OD)"), _T("(Output PP)"), _T("(Input)"),     _T(""), 
};

static CHECKBOX_STYLE CP2114_PinStyle[] =
{
//    Pin Modes:
//    Input         Output_OD    Output_PP    Function1          Function2
//    -----         ---------    ---------    ---------          ---------
/*0*/ CBS_ReadOnly, CBS_Default, CBS_Default, CBS_ReadOnly,      CBS_Indeterminate, 
/*1*/ CBS_ReadOnly, CBS_Default, CBS_Default, CBS_ReadOnly,      CBS_Indeterminate, 
/*2*/ CBS_ReadOnly, CBS_Default, CBS_Default, CBS_ReadOnly,      CBS_Indeterminate, 
/*3*/ CBS_ReadOnly, CBS_Default, CBS_Default, CBS_ReadOnly,      CBS_Indeterminate, 
/*4*/ CBS_ReadOnly, CBS_Default, CBS_Default, CBS_ReadOnly,      CBS_Indeterminate, 
/*5*/ CBS_ReadOnly, CBS_Default, CBS_Default, CBS_Indeterminate, CBS_Indeterminate, 
/*6*/ CBS_ReadOnly, CBS_Default, CBS_Default, CBS_Indeterminate, CBS_Indeterminate, 
/*7*/ CBS_ReadOnly, CBS_Default, CBS_Default, CBS_Indeterminate, CBS_Indeterminate, 
/*8*/ CBS_ReadOnly, CBS_Default, CBS_Default, CBS_Indeterminate, CBS_Indeterminate, 
/*9*/ CBS_ReadOnly, CBS_Default, CBS_Default, CBS_Indeterminate, CBS_Indeterminate, 
/*10*/CBS_ReadOnly, CBS_Default, CBS_Default, CBS_Indeterminate, CBS_Indeterminate, 
/*11*/CBS_ReadOnly, CBS_Default, CBS_Default, CBS_Indeterminate, CBS_Indeterminate, 
};

/////////////////////////////////////////////////////////////////////////////
// Global Prototypes
/////////////////////////////////////////////////////////////////////////////

// Return a string description for the specified status code
CString GetHidUartStatusStr(HID_UART_STATUS status);

// Remove whitespace and invalid characters from a string
// and return
CString CleanHexString(const CString& editStr);

/////////////////////////////////////////////////////////////////////////////
// Global Functions
/////////////////////////////////////////////////////////////////////////////

// Return a string description for the specified status code
CString GetHidUartStatusStr(const HID_UART_STATUS status)
{
	CString statusStr = _T("Unknown status");

	switch (status)
	{
	default:								statusStr = _T("Unknown status");			break;

	case HID_UART_SUCCESS:					statusStr = _T("Success");					break;
	case HID_UART_DEVICE_NOT_FOUND:			statusStr = _T("Device not found");			break;
	case HID_UART_INVALID_HANDLE:			statusStr = _T("Invalid handle");			break;
	case HID_UART_INVALID_DEVICE_OBJECT:	statusStr = _T("Invalid device object");	break;
	case HID_UART_INVALID_PARAMETER:		statusStr = _T("Invalid parameter");		break;
	case HID_UART_INVALID_REQUEST_LENGTH:	statusStr = _T("Invalid request length");	break;

	case HID_UART_READ_ERROR:				statusStr = _T("Read error");				break;
	case HID_UART_WRITE_ERROR:				statusStr = _T("Write error");				break;
	case HID_UART_READ_TIMED_OUT:			statusStr = _T("Read timed out");			break;
	case HID_UART_WRITE_TIMED_OUT:			statusStr = _T("Write timed out");			break;
	case HID_UART_DEVICE_IO_FAILED:			statusStr = _T("Device I/O failed");		break;
	case HID_UART_DEVICE_ACCESS_ERROR:		statusStr = _T("Device access error");		break;
	case HID_UART_DEVICE_NOT_SUPPORTED:		statusStr = _T("Device not supported");		break;

	case HID_UART_UNKNOWN_ERROR:			statusStr = _T("Unknown error");			break;
	}

	return statusStr;
}

// Remove whitespace and invalid characters from a string
// and return
CString CleanHexString(const CString& editStr)
{
	CString cleanStr = editStr;

	// Remove spaces
	cleanStr.Replace(_T(" "), _T(""));

	// Remove commas
	cleanStr.Replace(_T(","), _T(""));

	// Remove carriage returns and newlines
	cleanStr.Replace(_T("\r"), _T(""));
	cleanStr.Replace(_T("\n"), _T(""));

	// Only parse text including valid hex characters
	// (stop at the first invalid character)
	cleanStr = cleanStr.SpanIncluding(_T("0123456789abcdefABCDEF"));

	// Odd number of characters
	if (cleanStr.GetLength() % 2 == 1)
	{
		// Insert a "0" before the last character to make a complete set of hex bytes (two characters each)
		cleanStr = cleanStr.Left(cleanStr.GetLength() - 1) + _T("0") + cleanStr[cleanStr.GetLength() -1];
	}

	return cleanStr;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
/////////////////////////////////////////////////////////////////////////////

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString	versionStr;
	BYTE	major;
	BYTE	minor;
	BOOL	release;

	// Get the library version
	HidUart_GetLibraryVersion(&major, &minor, &release);

	// Display the version on the about dialog
	versionStr.Format(_T("SLABHIDtoUART.dll: Version %d.%d (%s)"), major, minor, (release) ? _T("Release") : _T("Debug"));
	SetDlgItemText(IDC_STATIC_LIBRARY_VERSION, versionStr);

	// Get the HID library version
	HidUart_GetHidLibraryVersion(&major, &minor, &release);

	// Display the version on the about dialog
	versionStr.Format(_T("SLABHIDDevice.dll: Version %d.%d (%s)"), major, minor, (release) ? _T("Release") : _T("Debug"));
	SetDlgItemText(IDC_STATIC_HID_LIBRARY_VERSION, versionStr);

	return TRUE;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHidUartExampleDlg dialog
/////////////////////////////////////////////////////////////////////////////

CHidUartExampleDlg::CHidUartExampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHidUartExampleDlg::IDD, pParent)
	, m_hidUart(NULL)
	, m_baudRate(115200)
	, m_hNotifyDevNode(NULL)
{
	m_hIcon			= AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hSmallIcon	= (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME), IMAGE_ICON, 16, 16, 0);
}

void CHidUartExampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DEVICE_LIST, m_comboDeviceList);
	DDX_Control(pDX, IDC_COMBO_DATA_BITS, m_comboDataBits);
	DDX_Control(pDX, IDC_COMBO_PARITY, m_comboParity);
	DDX_Control(pDX, IDC_COMBO_STOP_BITS, m_comboStopBits);
	DDX_Control(pDX, IDC_COMBO_FLOW_CONTROL, m_comboFlowControl);
	DDX_Text(pDX, IDC_EDIT_BAUD_RATE, m_baudRate);
	DDX_Control(pDX, IDC_EDIT_RECEIVE, m_hexEditReceive);
}

BEGIN_MESSAGE_MAP(CHidUartExampleDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DEVICECHANGE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_CHECK_CONNECT, &CHidUartExampleDlg::OnBnClickedCheckConnect)
	ON_BN_CLICKED(IDC_BUTTON_GET_LATCH, &CHidUartExampleDlg::OnBnClickedButtonGetLatch)
	ON_BN_CLICKED(IDC_BUTTON_SET_LATCH, &CHidUartExampleDlg::OnBnClickedButtonSetLatch)
	ON_BN_CLICKED(IDC_BUTTON_TRANSMIT, &CHidUartExampleDlg::OnBnClickedButtonTransmit)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CHidUartExampleDlg::OnBnClickedButtonClear)
	ON_CBN_DROPDOWN(IDC_COMBO_DEVICE_LIST, &CHidUartExampleDlg::OnCbnDropdownComboDeviceList)
	ON_CBN_CLOSEUP(IDC_COMBO_DEVICE_LIST, &CHidUartExampleDlg::OnCbnCloseupComboDeviceList)
	ON_BN_CLICKED(IDOK, &CHidUartExampleDlg::OnBnClickedButtonOK)
	ON_BN_CLICKED(IDCANCEL, &CHidUartExampleDlg::OnBnClickedButtonCancel)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHidUartExampleDlg message handlers
/////////////////////////////////////////////////////////////////////////////

BOOL CHidUartExampleDlg::OnInitDialog()
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
	SetIcon(m_hIcon, TRUE);				// Set big icon
	SetIcon(m_hSmallIcon, FALSE);		// Set small icon

	InitializeDialog();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHidUartExampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHidUartExampleDlg::OnPaint()
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
HCURSOR CHidUartExampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Periodically call read and append to receive window
void CHidUartExampleDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == READ_TIMER_ID)
	{
		ReceiveData();
	}

	CDialog::OnTimer(nIDEvent);
}

// Stop the read timer
void CHidUartExampleDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// Disconnect from the device
	if (IsDlgButtonChecked(IDC_CHECK_CONNECT))
	{
		Disconnect();
	}

	// Unregister device change notification
	UnregisterDeviceChange();
}

// Disable F1 help
BOOL CHidUartExampleDlg::OnHelpInfo(HELPINFO* pHelpInfo)
{
	UNREFERENCED_PARAMETER(pHelpInfo);

	return TRUE;
}

// Handle device change messages (ie a device is added or removed)
// - If an HID device is connected, then add the device to the device list
// - If the device we were connected to was removed, then disconnect from the device
BOOL CHidUartExampleDlg::OnDeviceChange(UINT nEventType, DWORD dwData)
{
	// Device has been removed
	if (nEventType == DBT_DEVICEREMOVECOMPLETE ||
		nEventType == DBT_DEVICEARRIVAL)
	{
		if (dwData)
		{
			PDEV_BROADCAST_HDR pHdr = (PDEV_BROADCAST_HDR)dwData;

			if (pHdr->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
			{
				PDEV_BROADCAST_DEVICEINTERFACE pDevInf = (PDEV_BROADCAST_DEVICEINTERFACE)pHdr;

				// "\\?\hid#vid_10c4&pid_81ba..."
				CString deviceStr = pDevInf->dbcc_name;

				if (nEventType == DBT_DEVICEREMOVECOMPLETE)
				{
					HID_UART_DEVICE_STR devPath;

					if (HidUart_GetOpenedString(m_hidUart, devPath, HID_UART_GET_PATH_STR) == HID_UART_SUCCESS)
					{
						// Our device was removed
						if (deviceStr.CompareNoCase(CString(devPath)) == 0)
						{
							Disconnect();
						}
					}
				}

				UpdateDeviceList();
			}
		}
	}

	return TRUE;
}

// Toggle the device connection (Connect/Disconnect)
void CHidUartExampleDlg::OnBnClickedCheckConnect()
{
	// Connecting
	if (IsDlgButtonChecked(IDC_CHECK_CONNECT))
	{
		Connect();
	}
	// Disconnecting
	else
	{
		Disconnect();
	}
}

// Get the GPIO configuration from the device (input, output, function mode)
// Set GPIO checkbox properites
HID_UART_STATUS CHidUartExampleDlg::UpdateGpioButtonProperties()
{
	HID_UART_STATUS status = HID_UART_DEVICE_NOT_FOUND;

	BYTE pinConfig[14];
	BOOL useSuspendValues;
	WORD suspendValue;
	WORD suspendMode;
	BYTE rs485Level;
	BYTE clkDiv;

    if (m_partNumber == HID_UART_PART_CP2110)
    {
	    if ((status = HidUart_GetPinConfig(m_hidUart, pinConfig, &useSuspendValues, &suspendValue, &suspendMode, &rs485Level, &clkDiv)) == HID_UART_SUCCESS)
	    {
		    for (int i = 0; i < 10; i++)
		    {
                // The offset into the pin arrays for the current pin configuration
                int pinModeIndex = i * 5 + pinConfig[i];

			    CButton*        pBtn            = (CButton*)GetDlgItem(i + IDC_CHECK_GPIO0);
                CString         pinCaption      = CP2110_PinCaptions[pinModeIndex];
                CString         pinDirection    = CP2110_PinDirections[pinModeIndex];
                CHECKBOX_STYLE  pinStyle        = CP2110_PinStyle[pinModeIndex];

                // Set the pin caption and direction labels
                SetDlgItemText(i + IDC_CHECK_GPIO0, pinCaption);
                SetDlgItemText(i + IDC_STATIC_PIN_DIR0, pinDirection);

                // Set the checkbox styles
                if (pinStyle == CBS_Default)
                {
                    pBtn->SetButtonStyle(BS_AUTOCHECKBOX);
                    pBtn->SetCheck(BST_UNCHECKED);
				    pBtn->EnableWindow(TRUE);
                }
                else if (pinStyle == CBS_ReadOnly)
                {
                    pBtn->SetButtonStyle(BS_AUTOCHECKBOX);
                    pBtn->SetCheck(BST_UNCHECKED);
				    pBtn->EnableWindow(FALSE);
                }
                else
                {
                    pBtn->SetButtonStyle(BS_AUTO3STATE);
                    pBtn->SetCheck(BST_INDETERMINATE);
				    pBtn->EnableWindow(FALSE);
                }

			    // Redraw the button with the new button style
			    pBtn->Invalidate();
		    }

            // Hide GPIO.10 and GPIO.11 for CP2114
            ((CButton*)GetDlgItem(IDC_CHECK_GPIO10))->ShowWindow(FALSE);
            ((CButton*)GetDlgItem(IDC_CHECK_GPIO11))->ShowWindow(FALSE);
            ((CButton*)GetDlgItem(IDC_STATIC_PIN_DIR10))->ShowWindow(FALSE);
            ((CButton*)GetDlgItem(IDC_STATIC_PIN_DIR11))->ShowWindow(FALSE);

		    // GPIO.0 is configured as CLK output
		    if (pinConfig[CP2110_INDEX_GPIO_0_CLK] == HID_UART_GPIO_MODE_FUNCTION1)
		    {
			    // Show CLK Output controls
			    // (controls are disabled by default in Disconnect())
			    ShowClkOutputCtrls(TRUE);
		    }

		    // Calculate and display the CLK output speed in Hz
		    UpdateClkOutputSpeed(clkDiv);
	    }
    }
    else if (m_partNumber == HID_UART_PART_CP2114)
    {
	  	if ((status = CP2114_GetPinConfig(m_hidUart, pinConfig, &useSuspendValues, &suspendValue, &suspendMode, &clkDiv)) == HID_UART_SUCCESS)
	    {
            for (int i = 0; i < 12; i++)
		    {
                // The offset into the pin arrays for the current pin configuration
                int pinModeIndex = i * 5 + pinConfig[i];

			    CButton*        pBtn            = (CButton*)GetDlgItem(i + IDC_CHECK_GPIO0);
                CString         pinCaption      = CP2114_PinCaptions[pinModeIndex];
                CString         pinDirection    = CP2114_PinDirections[pinModeIndex];
                CHECKBOX_STYLE  pinStyle        = CP2114_PinStyle[pinModeIndex];

                // Set the pin caption and direction labels
                SetDlgItemText(i + IDC_CHECK_GPIO0, pinCaption);
                SetDlgItemText(i + IDC_STATIC_PIN_DIR0, pinDirection);

                // Set the checkbox styles
                if (pinStyle == CBS_Default)
                {
                    pBtn->SetButtonStyle(BS_AUTOCHECKBOX);
                    pBtn->SetCheck(BST_UNCHECKED);
				    pBtn->EnableWindow(TRUE);
                }
                else if (pinStyle == CBS_ReadOnly)
                {
                    pBtn->SetButtonStyle(BS_AUTOCHECKBOX);
                    pBtn->SetCheck(BST_UNCHECKED);
				    pBtn->EnableWindow(FALSE);
                }
                else
                {
                    pBtn->SetButtonStyle(BS_AUTO3STATE);
                    pBtn->SetCheck(BST_INDETERMINATE);
				    pBtn->EnableWindow(FALSE);
                }

			    // Redraw the button with the new button style
			    pBtn->Invalidate();
		    }

            // Show GPIO.10 and GPIO.11 for CP2114
            ((CButton*)GetDlgItem(IDC_CHECK_GPIO10))->ShowWindow(TRUE);
            ((CButton*)GetDlgItem(IDC_CHECK_GPIO11))->ShowWindow(TRUE);
            ((CButton*)GetDlgItem(IDC_STATIC_PIN_DIR10))->ShowWindow(TRUE);
            ((CButton*)GetDlgItem(IDC_STATIC_PIN_DIR11))->ShowWindow(TRUE);

			// Hide CLK Output controls
			// (controls are disabled by default in Disconnect())
			ShowClkOutputCtrls(FALSE);
	    }
    }

	return status;
}

void CHidUartExampleDlg::GetLatch(BOOL silent)
{
	HID_UART_STATUS		status;
	WORD				latchValue = 0x0000;
	BOOL				opened;

	// Check if the device is opened
	if (HidUart_IsOpened(m_hidUart, &opened) == HID_UART_SUCCESS && opened)
	{
		// Retrieve the GPIO latch values
		status = HidUart_ReadLatch(m_hidUart, &latchValue);

		if (status == HID_UART_SUCCESS)
		{
            if (m_partNumber == HID_UART_PART_CP2110)
            {
			    // Update GPIO checkboxes
			    UpdateGpioState(IDC_CHECK_GPIO0, latchValue & CP2110_MASK_GPIO_0_CLK);
			    UpdateGpioState(IDC_CHECK_GPIO1, latchValue & CP2110_MASK_GPIO_1_RTS);
			    UpdateGpioState(IDC_CHECK_GPIO2, latchValue & CP2110_MASK_GPIO_2_CTS);
			    UpdateGpioState(IDC_CHECK_GPIO3, latchValue & CP2110_MASK_GPIO_3_RS485);
			    UpdateGpioState(IDC_CHECK_GPIO4, latchValue & CP2110_MASK_GPIO_4_TX_TOGGLE);
			    UpdateGpioState(IDC_CHECK_GPIO5, latchValue & CP2110_MASK_GPIO_5_RX_TOGGLE);
			    UpdateGpioState(IDC_CHECK_GPIO6, latchValue & CP2110_MASK_GPIO_6);
			    UpdateGpioState(IDC_CHECK_GPIO7, latchValue & CP2110_MASK_GPIO_7);
			    UpdateGpioState(IDC_CHECK_GPIO8, latchValue & CP2110_MASK_GPIO_8);
			    UpdateGpioState(IDC_CHECK_GPIO9, latchValue & CP2110_MASK_GPIO_9);
            }
            else if (m_partNumber == HID_UART_PART_CP2114)
            {
			    // Update GPIO checkboxes
			    UpdateGpioState(IDC_CHECK_GPIO0, latchValue & CP2114_MASK_GPIO_0);
			    UpdateGpioState(IDC_CHECK_GPIO1, latchValue & CP2114_MASK_GPIO_1);
			    UpdateGpioState(IDC_CHECK_GPIO2, latchValue & CP2114_MASK_GPIO_2);
			    UpdateGpioState(IDC_CHECK_GPIO3, latchValue & CP2114_MASK_GPIO_3);
			    UpdateGpioState(IDC_CHECK_GPIO4, latchValue & CP2114_MASK_GPIO_4);
			    UpdateGpioState(IDC_CHECK_GPIO5, latchValue & CP2114_MASK_GPIO_5);
			    UpdateGpioState(IDC_CHECK_GPIO6, latchValue & CP2114_MASK_GPIO_6);
			    UpdateGpioState(IDC_CHECK_GPIO7, latchValue & CP2114_MASK_GPIO_7);
			    UpdateGpioState(IDC_CHECK_GPIO8, latchValue & CP2114_MASK_GPIO_8);
			    UpdateGpioState(IDC_CHECK_GPIO9, latchValue & CP2114_MASK_GPIO_9);
                UpdateGpioState(IDC_CHECK_GPIO10, latchValue & CP2114_MASK_TX);
                UpdateGpioState(IDC_CHECK_GPIO11, latchValue & CP2114_MASK_RX);
            }
		}
		else
		{
			if (!silent)
			{
				// Notify the user that an error occurred
				CString msg;
				msg.Format(_T("Failed to read latch values: %s"), GetHidUartStatusStr(status).GetString());
				MessageBox(msg, 0, MB_ICONWARNING);
			}
		}
	}
}

// Set the GPIO checkbox check state
void CHidUartExampleDlg::UpdateGpioState(int nID, BOOL bit)
{
	CButton* pBtn = (CButton*)GetDlgItem(nID);

	// If the pin is in function mode, then the
	// checkbox state is indeterminate
	if (pBtn->GetButtonStyle() == BS_AUTO3STATE)
	{
		pBtn->SetCheck(BST_INDETERMINATE);
	}
	else
	{
		// Latch bit value is 1
		if (bit)
		{
			pBtn->SetCheck(BST_CHECKED);
		}
		// Latch bit value is 0
		else
		{
			pBtn->SetCheck(BST_UNCHECKED);
		}
	}
}

// Update GPIO checkboxes to display the current value of the latch
void CHidUartExampleDlg::OnBnClickedButtonGetLatch()
{
	GetLatch();
}

// Set latch values based on dialog selections
void CHidUartExampleDlg::OnBnClickedButtonSetLatch()
{
	HID_UART_STATUS		status;
	WORD				latchValue	= 0x0000;
	WORD				latchMask	= 0xFFFF;
	BOOL				opened;

	// Check if the device is opened
	if (HidUart_IsOpened(m_hidUart, &opened) == HID_UART_SUCCESS && opened)
	{
        if (m_partNumber == HID_UART_PART_CP2110)
        {
		    // Set latch values based on dialog selection
		    if (IsDlgButtonChecked(IDC_CHECK_GPIO0))	latchValue |= CP2110_MASK_GPIO_0_CLK;
		    if (IsDlgButtonChecked(IDC_CHECK_GPIO1))	latchValue |= CP2110_MASK_GPIO_1_RTS;
		    if (IsDlgButtonChecked(IDC_CHECK_GPIO2))	latchValue |= CP2110_MASK_GPIO_2_CTS;
		    if (IsDlgButtonChecked(IDC_CHECK_GPIO3))	latchValue |= CP2110_MASK_GPIO_3_RS485;
		    if (IsDlgButtonChecked(IDC_CHECK_GPIO4))	latchValue |= CP2110_MASK_GPIO_4_TX_TOGGLE;
		    if (IsDlgButtonChecked(IDC_CHECK_GPIO5))	latchValue |= CP2110_MASK_GPIO_5_RX_TOGGLE;
		    if (IsDlgButtonChecked(IDC_CHECK_GPIO6))	latchValue |= CP2110_MASK_GPIO_6;
		    if (IsDlgButtonChecked(IDC_CHECK_GPIO7))	latchValue |= CP2110_MASK_GPIO_7;	
		    if (IsDlgButtonChecked(IDC_CHECK_GPIO8))	latchValue |= CP2110_MASK_GPIO_8;
		    if (IsDlgButtonChecked(IDC_CHECK_GPIO9))	latchValue |= CP2110_MASK_GPIO_9;
        }
        else if (m_partNumber == HID_UART_PART_CP2114)
        {
		    // Set latch values based on dialog selection
		    if (IsDlgButtonChecked(IDC_CHECK_GPIO0))	latchValue |= CP2114_MASK_GPIO_0;
		    if (IsDlgButtonChecked(IDC_CHECK_GPIO1))	latchValue |= CP2114_MASK_GPIO_1;
		    if (IsDlgButtonChecked(IDC_CHECK_GPIO2))	latchValue |= CP2114_MASK_GPIO_2;
		    if (IsDlgButtonChecked(IDC_CHECK_GPIO3))	latchValue |= CP2114_MASK_GPIO_3;
		    if (IsDlgButtonChecked(IDC_CHECK_GPIO4))	latchValue |= CP2114_MASK_GPIO_4;
		    if (IsDlgButtonChecked(IDC_CHECK_GPIO5))	latchValue |= CP2114_MASK_GPIO_5;
		    if (IsDlgButtonChecked(IDC_CHECK_GPIO6))	latchValue |= CP2114_MASK_GPIO_6;
		    if (IsDlgButtonChecked(IDC_CHECK_GPIO7))	latchValue |= CP2114_MASK_GPIO_7;	
		    if (IsDlgButtonChecked(IDC_CHECK_GPIO8))	latchValue |= CP2114_MASK_GPIO_8;
		    if (IsDlgButtonChecked(IDC_CHECK_GPIO9))	latchValue |= CP2114_MASK_GPIO_9;
            if (IsDlgButtonChecked(IDC_CHECK_GPIO10))	latchValue |= CP2114_MASK_TX;
            if (IsDlgButtonChecked(IDC_CHECK_GPIO11))	latchValue |= CP2114_MASK_RX;
        }

		// Set latch values
		status = HidUart_WriteLatch(m_hidUart, latchValue, latchMask);

		if (status != HID_UART_SUCCESS)
		{
			// Notify the user that an error occurred
			CString msg;
			msg.Format(_T("Failed to write latch values: %s"), GetHidUartStatusStr(status).GetString());
			MessageBox(msg, 0, MB_ICONWARNING);
		}
	}
}

// Transmit entered text using ASCII or hex format
void CHidUartExampleDlg::OnBnClickedButtonTransmit()
{
	BOOL opened;

	// Check if the device is opened
	if (HidUart_IsOpened(m_hidUart, &opened) == HID_UART_SUCCESS && opened)
	{
		CString transmitStr;

		// Get transmit edit text
		GetDlgItemText(IDC_EDIT_TRANSMIT, transmitStr);

		// String is empty
		if (transmitStr.IsEmpty())
		{
			// Do nothing
			return;
		}

		// Interpret edit text as ASCII
		if (IsDlgButtonChecked(IDC_RADIO_ASCII))
		{
			HID_UART_STATUS	status;
			DWORD			numBytesWritten		= 0;
			DWORD			numBytesToWrite		= transmitStr.GetLength();
			BYTE*			buffer				= new BYTE[numBytesToWrite];

			// Copy ASCII values to the new array
			for (DWORD i = 0; i < numBytesToWrite; i++)
			{
				// Use the LSB of the 2-byte unicode value
				buffer[i] = (BYTE)transmitStr[(int)i];
			}

			// Send the UART data to the device to transmit
			status = HidUart_Write(m_hidUart, buffer, numBytesToWrite, &numBytesWritten);

			// Notify the user that an error occurred
			if (status != HID_UART_SUCCESS)
			{
				CString msg;
				msg.Format(_T("Failed to transmit : %s"), GetHidUartStatusStr(status).GetString());
				MessageBox(msg, 0, MB_ICONWARNING);
			}

			delete [] buffer;
		}
		// Interpret edit text as hex
		else
		{
			// Remove invalid hex characters
			transmitStr = CleanHexString(transmitStr);

			if (!transmitStr.IsEmpty())
			{
				HID_UART_STATUS	status;
				DWORD			numBytesWritten		= 0;
				DWORD			numBytesToWrite		= transmitStr.GetLength() / 2;
				BYTE*			buffer				= new BYTE[numBytesToWrite];

				// Convert each hex byte string to a BYTE value
				for (DWORD i = 0; i < numBytesToWrite; i++)
				{
					CString hexByte = transmitStr.Mid(i * 2, 2);
					buffer[i] = (BYTE)_tcstol(hexByte, NULL, 16);
				}

				// Separate each hex pair with a space
				for (int i = transmitStr.GetLength() - 2; i >= 2; i -= 2)
				{
					transmitStr.Insert(i, _T(" "));
				}

				// Set transmit window text to the cleaned up string
				SetDlgItemText(IDC_EDIT_TRANSMIT, transmitStr);

				// Send the UART data to the device to transmit
				status = HidUart_Write(m_hidUart, buffer, numBytesToWrite, &numBytesWritten);

				// Notify the user that an error occurred
				if (status != HID_UART_SUCCESS)
				{
					CString msg;
					msg.Format(_T("Failed to transmit : %s"), GetHidUartStatusStr(status).GetString());
					MessageBox(msg, 0, MB_ICONWARNING);
				}

				delete [] buffer;
			}
		}
	}
}

// Clear the receive window
void CHidUartExampleDlg::OnBnClickedButtonClear()
{
	m_hexEditReceive.SetWindowHex(NULL, 0);
}

void CHidUartExampleDlg::OnCbnDropdownComboDeviceList()
{
	// Refresh the device list and reselect the
	// previous selection if possible
	UpdateDeviceList();
}

void CHidUartExampleDlg::OnCbnCloseupComboDeviceList()
{
	// Refresh the device list and reselect the
	// previous selection if possible
	UpdateDeviceList();
}

void CHidUartExampleDlg::OnBnClickedButtonOK()
{
	// Prevent Enter from closing the main dialog
}

void CHidUartExampleDlg::OnBnClickedButtonCancel()
{
	// Prevent Escape from closing the main dialog
}

void CHidUartExampleDlg::OnClose()
{
	// Allow the application to close
	CDialog::OnCancel();
}

/////////////////////////////////////////////////////////////////////////////
// CHidUartExampleDlg Class - Protected Methods
/////////////////////////////////////////////////////////////////////////////

// Set status bar pane 0 text
void CHidUartExampleDlg::SetStatusText(const CString& statusStr)
{
	// Set the status bar text
	m_statusBar.SetPaneText(0, statusStr);
}

void CHidUartExampleDlg::InitializeDialog()
{
	InitStatusBar();
	InitUartSettings();
	InitTransferSettings();
	InitHexEditCtrl();

	UpdateDeviceList();

	RegisterDeviceChange();
}

// Initialize the status bar
// - Create the status bar object
// - Set number of panes to 1
// - Make pane 0 fit the width of the dialog
// - Draw the status bar
// - Set default status bar text to "Not Connected"
void CHidUartExampleDlg::InitStatusBar()
{
	// Create the status bar
	m_statusBar.Create(this);

	// Set number of panes
	m_statusBar.SetIndicators(StatusBarIndicators, 1);

	// Make the pane max width
	m_statusBar.SetPaneInfo(0, ID_INDICATOR_STATUS, SBPS_STRETCH, 0);

	// Draw the status bar
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, ID_INDICATOR_STATUS);

	// Set default status bar text
	m_statusBar.SetPaneText(0, _T("Not Connected"));
}

// Set the default UART control values
// - Set default baud rate to 115200
// - Set default UART combo settings to 8N1 (No flow control)
void CHidUartExampleDlg::InitUartSettings()
{
	UpdateData(TRUE);

	// Set default baud rate
	m_baudRate = 115200;

	// Set default UART settings
	m_comboDataBits.SelectString(-1, _T("8"));
	m_comboParity.SelectString(-1, _T("N"));
	m_comboStopBits.SelectString(-1, _T("1"));
	m_comboFlowControl.SelectString(-1, _T("No"));

	UpdateData(FALSE);
}

// Set the default transfer data settings
// - Set transmit format to ASCII
void CHidUartExampleDlg::InitTransferSettings()
{
	// Select ASCII format
	CheckRadioButton(IDC_RADIO_ASCII, IDC_RADIO_HEX, IDC_RADIO_ASCII);
}

// Set hex edit control settings
// - Set max history limit in hex bytes
void CHidUartExampleDlg::InitHexEditCtrl()
{
	// Set the maximum number of hex values to display
	// before resizing
	m_hexEditReceive.SetLimitHex(HEX_EDIT_LIMIT_SIZE);
}

// Register for device change notification for USB HID devices
// OnDeviceChange() will handle device arrival and removal
void CHidUartExampleDlg::RegisterDeviceChange()
{
	DEV_BROADCAST_DEVICEINTERFACE devIF = {0};

	devIF.dbcc_size			= sizeof(devIF);    
	devIF.dbcc_devicetype	= DBT_DEVTYP_DEVICEINTERFACE;    
	
	HidUart_GetHidGuid(&devIF.dbcc_classguid);
	
	m_hNotifyDevNode = RegisterDeviceNotification(GetSafeHwnd(), &devIF, DEVICE_NOTIFY_WINDOW_HANDLE);
}

// Unregister for device change notification for USB HID devices
void CHidUartExampleDlg::UnregisterDeviceChange()
{
	if (m_hNotifyDevNode)
	{
		UnregisterDeviceNotification(m_hNotifyDevNode);
		m_hNotifyDevNode = NULL;
	}
}

// Populate the device list combo box with connected device serial strings
// - Save previous device serial string selection
// - Fill the device list with connected device serial strings
// - Restore previous device selection
void CHidUartExampleDlg::UpdateDeviceList()
{
	// Only update the combo list when the drop down list is closed
	if (!m_comboDeviceList.GetDroppedState())
	{
		vector<CString>		oldDeviceList;
		vector<CString>		newDeviceList;
		CString				itemText;
		CString				selText;
		DWORD				numDevices;
		HID_UART_DEVICE_STR	deviceString;

		// Populate old device serial string list
		for (int i = 0; i < m_comboDeviceList.GetCount(); i++)
		{
			m_comboDeviceList.GetLBText(i, itemText);
			oldDeviceList.push_back(itemText);
		}

		// Populate new device serial string list
		if (HidUart_GetNumDevices(&numDevices, VID, PID) == HID_UART_SUCCESS)
		{
			for (DWORD i = 0; i < numDevices; i++)
			{
				if (HidUart_GetString(i, VID, PID, deviceString, HID_UART_GET_SERIAL_STR) == HID_UART_SUCCESS)
				{
					newDeviceList.push_back(CString(deviceString));
				}
			}
		}

		// Check if the device list needs to be updated
		if (oldDeviceList != newDeviceList)
		{
			// Save old serial string selection
			m_comboDeviceList.GetWindowText(selText);
			m_comboDeviceList.ResetContent();

			// Update the device list
			for (size_t i = 0; i < newDeviceList.size(); i++)
			{
				m_comboDeviceList.AddString(newDeviceList[i]);
			}

			// Restore serial string selection
			if (m_comboDeviceList.SelectString(-1, selText) == CB_ERR)
			{
				m_comboDeviceList.SetCurSel(0);
			}
		}
	}
}

// Enable/disable the device settings controls:
// - Device list
// - Update button
// - Baud rate edit box
// - Data bits, parity, stop bits, and flow control combo boxes
void CHidUartExampleDlg::EnableSettingsCtrls(BOOL enable)
{
	// Enable/disable the device list, update button, and UART settings
	m_comboDeviceList.EnableWindow(enable);
	GetDlgItem(IDC_EDIT_BAUD_RATE)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_DATA_BITS)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_PARITY)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_STOP_BITS)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_FLOW_CONTROL)->EnableWindow(enable);
}

// Show/hide the CLK Output controls:
// - CLK Output labels
// - CLK Output edit box
void CHidUartExampleDlg::ShowClkOutputCtrls(BOOL show)
{
	// Show/hide the CLK Output labels
	GetDlgItem(IDC_STATIC_CLK_OUTPUT)->ShowWindow(show);
	GetDlgItem(IDC_STATIC_CLK_OUTPUT_SUFFIX)->ShowWindow(show);

	// Show hide the CLK Output edit box
	GetDlgItem(IDC_EDIT_CLK_OUTPUT)->ShowWindow(show);
}

// Return the UART control settings
// - Get UART setting combo selections
// - Get device list serial string
BOOL CHidUartExampleDlg::GetConnectSettings(CString& serial, DWORD& baudRate, BYTE& dataBits, BYTE& parity, BYTE& stopBits, BYTE& flowControl)
{
	if (UpdateData(TRUE))
	{
		// Get UART settings combo box selections
		int dataBitsSel		= m_comboDataBits.GetCurSel();
		int paritySel		= m_comboParity.GetCurSel();
		int stopBitsSel		= m_comboStopBits.GetCurSel();
		int flowControlSel	= m_comboFlowControl.GetCurSel();

		// Make sure selections are valid
		if (dataBitsSel		!= CB_ERR &&
			paritySel		!= CB_ERR &&
			stopBitsSel		!= CB_ERR &&
			flowControlSel	!= CB_ERR)
		{
			baudRate		= m_baudRate;
			dataBits		= (dataBitsSel + HID_UART_FIVE_DATA_BITS) & 0xFF;
			parity			= (paritySel + HID_UART_NO_PARITY) & 0xFF;
			stopBits		= (stopBitsSel + HID_UART_SHORT_STOP_BIT) & 0xFF;
			flowControl		= (flowControlSel + HID_UART_NO_FLOW_CONTROL) & 0xFF;

			m_comboDeviceList.GetWindowText(serial);

			if (!serial.IsEmpty())
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

// Connect to the device with the specified serial string and configure the UART
// - Search for device with matching serial string
// - Open matching device
// - Get the device part number and version
// - Configure device UART settings
// - Output any error messages
// - Display "Not Connected" or "Connected to ..." in the status bar
BOOL CHidUartExampleDlg::Connect(CString serial, DWORD baudRate, BYTE dataBits, BYTE parity, BYTE stopBits, BYTE flowControl)
{
	HID_UART_STATUS		status		= HID_UART_DEVICE_NOT_FOUND;
	DWORD				numDevices	= 0;

	if (HidUart_GetNumDevices(&numDevices, VID, PID) == HID_UART_SUCCESS)
	{
		for (DWORD i = 0; i < numDevices; i++)
		{
			HID_UART_DEVICE_STR deviceString;

			// Search through all HID devices for a matching serial string
			if (HidUart_GetString(i, VID, PID, deviceString, HID_UART_GET_SERIAL_STR) == HID_UART_SUCCESS)
			{
				// Found a matching device
				if (serial == deviceString)
				{
					// Open the device
					status = HidUart_Open(&m_hidUart, i, VID, PID);
					break;
				}
			}
		}
	}

	// Found and opened the device
	if (status == HID_UART_SUCCESS)
	{
		// Get part number and version
		status = HidUart_GetPartNumber(m_hidUart, &m_partNumber, &m_version);
	}
	
	// Got part number
	if (status == HID_UART_SUCCESS)
	{
		// Configure the UART
		status = HidUart_SetUartConfig(m_hidUart, baudRate, dataBits, parity, stopBits, flowControl);
	}

	// Confirm UART settings
	if (status == HID_UART_SUCCESS)
	{
		DWORD vBaudRate;
		BYTE vDataBits;
		BYTE vParity;
		BYTE vStopBits;
		BYTE vFlowControl;

		status = HidUart_GetUartConfig(m_hidUart, &vBaudRate, &vDataBits, &vParity, &vStopBits, &vFlowControl);

		if (status == HID_UART_SUCCESS)
		{
			if (vBaudRate != baudRate ||
				vDataBits != dataBits ||
				vParity != parity ||
				vStopBits != stopBits ||
				vFlowControl != flowControl)
			{
				status = HID_UART_INVALID_PARAMETER;
			}
		}
	}

	// Configured the UART
	if (status == HID_UART_SUCCESS)
	{
		// Set short read timeouts for periodic read timer
		// Set longer write timeouts for user transmits
		status = HidUart_SetTimeouts(m_hidUart, READ_TIMEOUT, WRITE_TIMEOUT);
	}

	// Fully connected to the device
	if (status == HID_UART_SUCCESS)
	{
		// Output the connection status to the status bar
		CString statusMsg;
		statusMsg.Format(_T("Connected to %s"), serial.GetString());
		SetStatusText(statusMsg);
	}
	// Connect failed
	else
	{
		// Disconnect
		HidUart_Close(m_hidUart);

		// Notify the user that an error occurred
		CString msg;
		msg.Format(_T("Failed to connect to %s: %s"), serial.GetString(), GetHidUartStatusStr(status).GetString());
		MessageBox(msg, 0, MB_ICONWARNING);
		
		// Update status
		SetStatusText(_T("Not Connected"));
	}

	// Return TRUE if the device was opened successfully
	return (status == HID_UART_SUCCESS);
}

// Connect to the device with the serial string selected
// in the device list using the device settings specified
// on the dialog
// - Read settings from the dialog controls
// - Connect to the device specified in the device list
// - Disable device settings controls
// - Update the device information text boxes
// - Set Connect checkbox/button caption and pressed state
// - Start the read timer
BOOL CHidUartExampleDlg::Connect()
{
	CString serial;
	DWORD	baudRate;
	BYTE	dataBits;
	BYTE	parity;
	BYTE	stopBits;
	BYTE	flowControl;

	// Retrieve UART settings from the dialog
	if (GetConnectSettings(serial, baudRate, dataBits, parity, stopBits, flowControl))
	{
		// Connect to the device and configure the UART
		if (Connect(serial, baudRate, dataBits, parity, stopBits, flowControl))
		{
			// Disable the device list, update button, and UART settings
			EnableSettingsCtrls(FALSE);

			// Get pin configuration and set checkbox properties
			// accordingly
			UpdateGpioButtonProperties();

			// Update the latch values
			GetLatch(TRUE);

			// Update device information strings
			UpdateDeviceInformation();

			// Check the connect checkbox/button
			CheckDlgButton(IDC_CHECK_CONNECT, TRUE);

			// Next button press should disconnect
			SetDlgItemText(IDC_CHECK_CONNECT, _T("&Disconnect"));

			// Start read timer to display received data in the receive window
			StartReadTimer();

			return TRUE;
		}
	}

	// Connect failed, uncheck the button
	CheckDlgButton(IDC_CHECK_CONNECT, FALSE);

	// Next button press should connect
	SetDlgItemText(IDC_CHECK_CONNECT, _T("&Connect"));

	return FALSE;
}

// Disconnect from the currently connected device
// - Stop the read timer
// - Disconnect from the current device
// - Output any error messages
// - Display "Not Connected" in the status bar
// - Re-enable all device settings controls
// - Update the device information text boxes (clear text)
// - Set Connect checkbox/button caption and pressed state
BOOL CHidUartExampleDlg::Disconnect()
{
	// Stop read timer
	StopReadTimer();

	// Close the device
	HID_UART_STATUS status = HidUart_Close(m_hidUart);

	// Disconnect failed
	if (status != HID_UART_SUCCESS)
	{
		// Notify the user that an error occurred
		CString msg;
		msg.Format(_T("Failed to disconnect: %s"), GetHidUartStatusStr(status).GetString());
		MessageBox(msg, 0, MB_ICONWARNING);
	}

	// Output the disconnect status to the status bar
	SetStatusText(_T("Not Connected"));

	// Re-enable the device list, update button, and UART settings
	EnableSettingsCtrls(TRUE);

	// Hide CLK Output controls
	ShowClkOutputCtrls(FALSE);

	// Update device information strings
	UpdateDeviceInformation();

	// Uncheck the connect checkbox/button
	CheckDlgButton(IDC_CHECK_CONNECT, FALSE);

	// Next button press should connect
	SetDlgItemText(IDC_CHECK_CONNECT, _T("&Connect"));

	// Return TRUE if the device was closed successfully
	return (status == HID_UART_SUCCESS);
}

// Retrieve device information strings and display on the dialog
void CHidUartExampleDlg::UpdateDeviceInformation()
{
	HID_UART_DEVICE_STR deviceString;
	BOOL opened;

	// Clear all strings
	SetDlgItemText(IDC_EDIT_VID, _T(""));
	SetDlgItemText(IDC_EDIT_PID, _T(""));
	SetDlgItemText(IDC_EDIT_SERIAL, _T(""));
	SetDlgItemText(IDC_EDIT_PATH, _T(""));
	SetDlgItemText(IDC_EDIT_PART_NUMBER, _T(""));
	SetDlgItemText(IDC_EDIT_VERSION, _T(""));
	SetDlgItemText(IDC_EDIT_MFR, _T(""));
	SetDlgItemText(IDC_EDIT_PRODUCT, _T(""));

	// Update VID string
	if (HidUart_GetOpenedString(m_hidUart, deviceString, HID_UART_GET_VID_STR) == HID_UART_SUCCESS)
	{
		SetDlgItemText(IDC_EDIT_VID, CString(deviceString));
	}

	// Update PID string
	if (HidUart_GetOpenedString(m_hidUart, deviceString, HID_UART_GET_PID_STR) == HID_UART_SUCCESS)
	{
		SetDlgItemText(IDC_EDIT_PID, CString(deviceString));
	}

	// Update serial string
	if (HidUart_GetOpenedString(m_hidUart, deviceString, HID_UART_GET_SERIAL_STR) == HID_UART_SUCCESS)
	{
		SetDlgItemText(IDC_EDIT_SERIAL, CString(deviceString));
	}

	// Update device path string
	if (HidUart_GetOpenedString(m_hidUart, deviceString, HID_UART_GET_PATH_STR) == HID_UART_SUCCESS)
	{
		SetDlgItemText(IDC_EDIT_PATH, CString(deviceString));
	}

	// Update manufacturer string
	if (HidUart_GetOpenedString(m_hidUart, deviceString, HID_UART_GET_MANUFACTURER_STR) == HID_UART_SUCCESS)
	{
		SetDlgItemText(IDC_EDIT_MFR, CString(deviceString));
	}

	// Update product string
	if (HidUart_GetOpenedString(m_hidUart, deviceString, HID_UART_GET_PRODUCT_STR) == HID_UART_SUCCESS)
	{
		SetDlgItemText(IDC_EDIT_PRODUCT, CString(deviceString));
	}

	// Update part number and version
	if (HidUart_IsOpened(m_hidUart, &opened) == HID_UART_SUCCESS && opened)
	{
		// Update part number and version
		CString partNumStr;
		CString versionStr;

		partNumStr.Format(_T("%d"), m_partNumber);
		versionStr.Format(_T("%d"), m_version);

		SetDlgItemText(IDC_EDIT_PART_NUMBER, partNumStr);
		SetDlgItemText(IDC_EDIT_VERSION, versionStr);
	}
}

// Calculate and display the CLK output speed in Hz
// CLK = 24000000 Hz / (2 x clkDiv)
// If clkDiv = 0, then CLK = 24000000 Hz
void CHidUartExampleDlg::UpdateClkOutputSpeed(BYTE clkDiv)
{
	CString clk;

	if (clkDiv == 0)
	{
		clk = _T("24000000");
	}
	else
	{
		clk.Format(_T("%u"), 24000000 / (2*clkDiv));
	}

	SetDlgItemText(IDC_EDIT_CLK_OUTPUT, clk);
}

// Receive UART data from the device and output to the receive window
void CHidUartExampleDlg::ReceiveData()
{
	HID_UART_STATUS status;
	DWORD			numBytesRead	= 0;
	DWORD			numBytesToRead	= READ_SIZE;
	BYTE*			buffer			= new BYTE[numBytesToRead];

	// Receive UART data from the device (up to 1000 bytes)
	status = HidUart_Read(m_hidUart, buffer, numBytesToRead, &numBytesRead);

	// HidUart_Read returns HID_UART_SUCCESS if numBytesRead == numBytesToRead
	// and returns HID_UART_READ_TIMED_OUT if numBytesRead < numBytesToRead
	if (status == HID_UART_SUCCESS || status == HID_UART_READ_TIMED_OUT)
	{
		// Output received data to the receive window
		if (numBytesRead > 0)
		{
			m_hexEditReceive.AppendWindowHex(buffer, numBytesRead);
		}
	}

	delete [] buffer;
}

// Start the read timer which displays received UART
// data in the receive window
void CHidUartExampleDlg::StartReadTimer()
{
	SetTimer(READ_TIMER_ID, READ_TIMER_ELAPSE, NULL);
}

// Stop the read timer which displays received UART
// data in the receive window
void CHidUartExampleDlg::StopReadTimer()
{
	KillTimer(READ_TIMER_ID);
}
