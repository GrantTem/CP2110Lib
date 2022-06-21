Imports System
Imports System.Collections.Generic
Imports System.Text
Imports System.Runtime.InteropServices

Module SLABHIDTOUART
    '///////////////////////////////////////////////////////////////////////////
    ' SLABHIDtoUART.h
    ' For SLABHIDtoUART.dll version 2.0
    ' and Silicon Labs CP2110/CP2114 HID to UART
    '///////////////////////////////////////////////////////////////////////////

    ' The following ifdef block is the standard way of creating macros which make exporting
    ' from a DLL simpler. All files within this DLL are compiled with the HID_TO_UART_EXPORTS
    ' symbol defined on the command line. this symbol should not be defined on any project
    ' that uses this DLL. This way any other project whose source files include this file see
    ' functions as being imported from a DLL, whereas this DLL sees symbols
    ' defined with this macro as being exported.

    '///////////////////////////////////////////////////////////////////////////
    ' Return Code Definitions
    '///////////////////////////////////////////////////////////////////////////

    ' HID_UART_STATUS

    ' Return Codes
    Public Const HID_UART_SUCCESS As Byte = &H00
    Public Const HID_UART_DEVICE_NOT_FOUND As Byte = &H01
    Public Const HID_UART_INVALID_HANDLE As Byte = &H02
    Public Const HID_UART_INVALID_DEVICE_OBJECT As Byte = &H03
    Public Const HID_UART_INVALID_PARAMETER As Byte = &H04
    Public Const HID_UART_INVALID_REQUEST_LENGTH As Byte = &H05

    Public Const HID_UART_READ_ERROR As Byte = &H10
    Public Const HID_UART_WRITE_ERROR As Byte = &H11
    Public Const HID_UART_READ_TIMED_OUT As Byte = &H12
    Public Const HID_UART_WRITE_TIMED_OUT As Byte = &H13
    Public Const HID_UART_DEVICE_IO_FAILED As Byte = &H14
    Public Const HID_UART_DEVICE_ACCESS_ERROR As Byte = &H15
    Public Const HID_UART_DEVICE_NOT_SUPPORTED As Byte = &H16

    Public Const HID_UART_UNKNOWN_ERROR As Byte = &HFF

    '///////////////////////////////////////////////////////////////////////////
    ' String Definitions
    '///////////////////////////////////////////////////////////////////////////

    ' Product String Types
    Public Const HID_UART_GET_VID_STR As Byte = &H01
    Public Const HID_UART_GET_PID_STR As Byte = &H02
    Public Const HID_UART_GET_PATH_STR As Byte = &H03
    Public Const HID_UART_GET_SERIAL_STR As Byte = &H04
    Public Const HID_UART_GET_MANUFACTURER_STR As Byte = &H05
    Public Const HID_UART_GET_PRODUCT_STR As Byte = &H06

    ' String Lengths
    Public Const HID_UART_DEVICE_STRLEN As Integer = 260

    ' HID_UART_DEVICE_STR

    '///////////////////////////////////////////////////////////////////////////
    ' UART Definitions
    '///////////////////////////////////////////////////////////////////////////

    ' Error Status
    Public Const HID_UART_PARITY_ERROR As Byte = &H01
    Public Const HID_UART_OVERRUN_ERROR As Byte = &H02

    ' Line Break Status
    Public Const HID_UART_LINE_BREAK_INACTIVE As Byte = &H00
    Public Const HID_UART_LINE_BREAK_ACTIVE As Byte = &H01

    ' Data Bits
    Public Const HID_UART_FIVE_DATA_BITS As Byte = &H00
    Public Const HID_UART_SIX_DATA_BITS As Byte = &H01
    Public Const HID_UART_SEVEN_DATA_BITS As Byte = &H02
    Public Const HID_UART_EIGHT_DATA_BITS As Byte = &H03

    ' Parity
    Public Const HID_UART_NO_PARITY As Byte = &H00
    Public Const HID_UART_ODD_PARITY As Byte = &H01
    Public Const HID_UART_EVEN_PARITY As Byte = &H02
    Public Const HID_UART_MARK_PARITY As Byte = &H03
    Public Const HID_UART_SPACE_PARITY As Byte = &H04

    ' Stop Bits
    ' Short = 1 stop bit
    ' Long = 1.5 stop bits (5 data bits)
    ' = 2 stop bits (6-8 data bits)
    Public Const HID_UART_SHORT_STOP_BIT As Byte = &H00
    Public Const HID_UART_LONG_STOP_BIT As Byte = &H01

    ' Flow Control
    Public Const HID_UART_NO_FLOW_CONTROL As Byte = &H00
    Public Const HID_UART_RTS_CTS_FLOW_CONTROL As Byte = &H01

    ' Read/Write Limits
    Public Const HID_UART_MIN_READ_SIZE As Integer = 1
    Public Const HID_UART_MAX_READ_SIZE As Integer = 32768
    Public Const HID_UART_MIN_WRITE_SIZE As Integer = 1
    Public Const HID_UART_MAX_WRITE_SIZE As Integer = 4096

    '///////////////////////////////////////////////////////////////////////////
    ' Part Number Definitions
    '///////////////////////////////////////////////////////////////////////////

    ' Part Numbers
    Public Const HID_UART_PART_CP2110 As Byte = &H0A
    Public Const HID_UART_PART_CP2114 As Byte = &H0E

    '///////////////////////////////////////////////////////////////////////////
    ' User Customization Definitions
    '///////////////////////////////////////////////////////////////////////////

    ' User-Customizable Field Lock Bitmasks
    Public Const HID_UART_LOCK_PRODUCT_STR_1 As UShort = &H0001
    Public Const HID_UART_LOCK_PRODUCT_STR_2 As UShort = &H0002
    Public Const HID_UART_LOCK_SERIAL_STR As UShort = &H0004
    Public Const HID_UART_LOCK_PIN_CONFIG As UShort = &H0008
    Public Const HID_UART_LOCK_VID As UShort = &H0100
    Public Const HID_UART_LOCK_PID As UShort = &H0200
    Public Const HID_UART_LOCK_POWER As UShort = &H0400
    Public Const HID_UART_LOCK_POWER_MODE As UShort = &H0800
    Public Const HID_UART_LOCK_RELEASE_VERSION As UShort = &H1000
    Public Const HID_UART_LOCK_FLUSH_BUFFERS As UShort = &H2000
    Public Const HID_UART_LOCK_MFG_STR_1 As UShort = &H4000
    Public Const HID_UART_LOCK_MFG_STR_2 As UShort = &H8000

    ' Field Lock Bit Values
    Public Const HID_UART_LOCK_UNLOCKED As Integer = 1
    Public Const HID_UART_LOCK_LOCKED As Integer = 0

    ' Power Max Value (500 mA)
    Public Const HID_UART_BUS_POWER_MAX As Byte = &HFA

    ' Power Modes
    Public Const HID_UART_BUS_POWER As Byte = &H00
    Public Const HID_UART_SELF_POWER_VREG_DIS As Byte = &H01
    Public Const HID_UART_SELF_POWER_VREG_EN As Byte = &H02

    ' Flush Buffers Bitmasks
    Public Const HID_UART_FLUSH_TX_OPEN As Byte = &H01
    Public Const HID_UART_FLUSH_TX_CLOSE As Byte = &H02
    Public Const HID_UART_FLUSH_RX_OPEN As Byte = &H04
    Public Const HID_UART_FLUSH_RX_CLOSE As Byte = &H08

    ' USB Config Bitmasks
    Public Const HID_UART_SET_VID As Byte = &H01
    Public Const HID_UART_SET_PID As Byte = &H02
    Public Const HID_UART_SET_POWER As Byte = &H04
    Public Const HID_UART_SET_POWER_MODE As Byte = &H08
    Public Const HID_UART_SET_RELEASE_VERSION As Byte = &H10
    Public Const HID_UART_SET_FLUSH_BUFFERS As Byte = &H20

    ' USB Config Bit Values
    Public Const HID_UART_SET_IGNORE As Integer = 0
    Public Const HID_UART_SET_PROGRAM As Integer = 1

    ' String Lengths
    Public Const HID_UART_MFG_STRLEN As Integer = 62
    Public Const HID_UART_PRODUCT_STRLEN As Integer = 62
    Public Const HID_UART_SERIAL_STRLEN As Integer = 30

    ' HID_UART_MFG_STR

    ' HID_UART_PRODUCT_STR

    ' HID_UART_SERIAL_STR

    '///////////////////////////////////////////////////////////////////////////
    ' Pin Definitions
    '///////////////////////////////////////////////////////////////////////////

    ' Pin Config Modes
    Public Const HID_UART_GPIO_MODE_INPUT As Byte = &H00
    Public Const HID_UART_GPIO_MODE_OUTPUT_OD As Byte = &H01
    Public Const HID_UART_GPIO_MODE_OUTPUT_PP As Byte = &H02
    Public Const HID_UART_GPIO_MODE_FUNCTION1 As Byte = &H03
    Public Const HID_UART_GPIO_MODE_FUNCTION2 As Byte = &H04

    ' Suspend Value Bit Values
    Public Const HID_UART_VALUE_SUSPEND_LO As Integer = 0
    Public Const HID_UART_VALUE_SUSPEND_HI As Integer = 1

    ' Suspend Mode Bit Values
    Public Const HID_UART_MODE_SUSPEND_OD As Integer = 0
    Public Const HID_UART_MODE_SUSPEND_PP As Integer = 1

    ' RS485 Active Levels
    Public Const HID_UART_MODE_RS485_ACTIVE_LO As Byte = &H00
    Public Const HID_UART_MODE_RS485_ACTIVE_HI As Byte = &H01

    '///////////////////////////////////////////////////////////////////////////
    ' Typedefs
    '///////////////////////////////////////////////////////////////////////////

    '///////////////////////////////////////////////////////////////////////////
    ' Exported Library Functions
    '///////////////////////////////////////////////////////////////////////////

    ' HidUart_GetNumDevices
    Public Declare Function HidUart_GetNumDevices Lib "SLABHIDtoUART.dll" (ByRef numDevices As UInteger, vid As UShort, pid As UShort) As Integer

    ' HidUart_GetString
    Public Declare Function HidUart_GetString Lib "SLABHIDtoUART.dll" (deviceNum As UInteger, vid As UShort, pid As UShort, deviceString As StringBuilder, options As UInteger) As Integer

    ' HidUart_GetOpenedString
    Public Declare Function HidUart_GetOpenedString Lib "SLABHIDtoUART.dll" (device As IntPtr, deviceString As StringBuilder, options As UInteger) As Integer

    ' HidUart_GetIndexedString
    Public Declare Function HidUart_GetIndexedString Lib "SLABHIDtoUART.dll" (deviceNum As UInteger, vid As UShort, pid As UShort, stringIndex As UInteger, deviceString As StringBuilder) As Integer

    ' HidUart_GetOpenedIndexedString
    Public Declare Function HidUart_GetOpenedIndexedString Lib "SLABHIDtoUART.dll" (device As IntPtr, stringIndex As UInteger, deviceString As StringBuilder) As Integer

    ' HidUart_GetAttributes
    Public Declare Function HidUart_GetAttributes Lib "SLABHIDtoUART.dll" (deviceNum As UInteger, vid As UShort, pid As UShort, ByRef deviceVid As UShort, ByRef devicePid As UShort, ByRef deviceReleaseNumber As UShort) As Integer

    ' HidUart_GetOpenedAttributes
    Public Declare Function HidUart_GetOpenedAttributes Lib "SLABHIDtoUART.dll" (device As IntPtr, ByRef deviceVid As UShort, ByRef devicePid As UShort, ByRef deviceReleaseNumber As UShort) As Integer

    ' HidUart_Open
    Public Declare Function HidUart_Open Lib "SLABHIDtoUART.dll" (ByRef device As IntPtr, deviceNum As UInteger, vid As UShort, pid As UShort) As Integer

    ' HidUart_Close
    Public Declare Function HidUart_Close Lib "SLABHIDtoUART.dll" (device As IntPtr) As Integer

    ' HidUart_IsOpened
    Public Declare Function HidUart_IsOpened Lib "SLABHIDtoUART.dll" (device As IntPtr, ByRef opened As Boolean) As Integer

    ' HidUart_SetUartEnable
    Public Declare Function HidUart_SetUartEnable Lib "SLABHIDtoUART.dll" (device As IntPtr, enable As Boolean) As Integer

    ' HidUart_GetUartEnable
    Public Declare Function HidUart_GetUartEnable Lib "SLABHIDtoUART.dll" (device As IntPtr, ByRef enable As Boolean) As Integer

    ' HidUart_Read
    Public Declare Function HidUart_Read Lib "SLABHIDtoUART.dll" (device As IntPtr, buffer() As Byte, numBytesToRead As UInteger, ByRef numBytesRead As UInteger) As Integer

    ' HidUart_Write
    Public Declare Function HidUart_Write Lib "SLABHIDtoUART.dll" (device As IntPtr, buffer() As Byte, numBytesToWrite As UInteger, ByRef numBytesWritten As UInteger) As Integer

    ' HidUart_FlushBuffers
    Public Declare Function HidUart_FlushBuffers Lib "SLABHIDtoUART.dll" (device As IntPtr, flushTransmit As Boolean, flushReceive As Boolean) As Integer

    ' HidUart_CancelIo
    Public Declare Function HidUart_CancelIo Lib "SLABHIDtoUART.dll" (device As IntPtr) As Integer

    ' HidUart_SetTimeouts
    Public Declare Function HidUart_SetTimeouts Lib "SLABHIDtoUART.dll" (device As IntPtr, readTimeout As UInteger, writeTimeout As UInteger) As Integer

    ' HidUart_GetTimeouts
    Public Declare Function HidUart_GetTimeouts Lib "SLABHIDtoUART.dll" (device As IntPtr, ByRef readTimeout As UInteger, ByRef writeTimeout As UInteger) As Integer

    ' HidUart_GetUARTStatus
    Public Declare Function HidUart_GetUartStatus Lib "SLABHIDtoUART.dll" (device As IntPtr, ByRef transmitFifoSize As UShort, ByRef receiveFifoSize As UShort, ByRef errorStatus As Byte, ByRef lineBreakStatus As Byte) As Integer

    ' HidUart_SetUARTConfig
    Public Declare Function HidUart_SetUartConfig Lib "SLABHIDtoUART.dll" (device As IntPtr, baudRate As UInteger, dataBits As Byte, parity As Byte, stopBits As Byte, flowControl As Byte) As Integer

    ' HidUart_GetUARTConfig
    Public Declare Function HidUart_GetUartConfig Lib "SLABHIDtoUART.dll" (device As IntPtr, ByRef baudRate As UInteger, ByRef dataBits As Byte, ByRef parity As Byte, ByRef stopBits As Byte, ByRef flowControl As Byte) As Integer

    ' HidUart_StartBreak
    Public Declare Function HidUart_StartBreak Lib "SLABHIDtoUART.dll" (device As IntPtr, duration As Byte) As Integer

    ' HidUart_StopBreak
    Public Declare Function HidUart_StopBreak Lib "SLABHIDtoUART.dll" (device As IntPtr) As Integer

    ' HidUart_Reset
    Public Declare Function HidUart_Reset Lib "SLABHIDtoUART.dll" (device As IntPtr) As Integer

    ' HidUart_ReadLatch
    Public Declare Function HidUart_ReadLatch Lib "SLABHIDtoUART.dll" (device As IntPtr, ByRef latchValue As UShort) As Integer

    ' HidUart_WriteLatch
    Public Declare Function HidUart_WriteLatch Lib "SLABHIDtoUART.dll" (device As IntPtr, latchValue As UShort, latchMask As UShort) As Integer

    ' HidUart_GetPartNumber
    Public Declare Function HidUart_GetPartNumber Lib "SLABHIDtoUART.dll" (device As IntPtr, ByRef partNumber As Byte, ByRef version As Byte) As Integer

    ' HidUart_GetLibraryVersion
    Public Declare Function HidUart_GetLibraryVersion Lib "SLABHIDtoUART.dll" (ByRef major As Byte, ByRef minor As Byte, ByRef release As Boolean) As Integer

    ' HidUart_GetHidLibraryVersion
    Public Declare Function HidUart_GetHidLibraryVersion Lib "SLABHIDtoUART.dll" (ByRef major As Byte, ByRef minor As Byte, ByRef release As Boolean) As Integer

    ' HidUart_GetHidGuid
    Public Declare Function HidUart_GetHidGuid Lib "SLABHIDtoUART.dll" (ByRef guid As Guid) As Integer

    ' HidUart_SetLock
    Public Declare Function HidUart_SetLock Lib "SLABHIDtoUART.dll" (device As IntPtr, lock As UShort) As Integer

    ' HidUart_GetLock
    Public Declare Function HidUart_GetLock Lib "SLABHIDtoUART.dll" (device As IntPtr, ByRef lock As UShort) As Integer

    ' HidUart_SetUsbConfig
    Public Declare Function HidUart_SetUsbConfig Lib "SLABHIDtoUART.dll" (device As IntPtr, vid As UShort, pid As UShort, power As Byte, powerMode As Byte, releaseVersion As UShort, flushBuffers As Byte, mask As Byte) As Integer

    ' HidUart_GetUsbConfig
    Public Declare Function HidUart_GetUsbConfig Lib "SLABHIDtoUART.dll" (device As IntPtr, ByRef vid As UShort, ByRef pid As UShort, ByRef power As Byte, ByRef powerMode As Byte, ByRef releaseVersion As UShort, ByRef flushBuffers As Byte) As Integer

    ' HidUart_SetManufacturingString
    Public Declare Function HidUart_SetManufacturingString Lib "SLABHIDtoUART.dll" (device As IntPtr, manufacturingString As String, strlen As Byte) As Integer

    ' HidUart_GetManufacturingString
    Public Declare Function HidUart_GetManufacturingString Lib "SLABHIDtoUART.dll" (device As IntPtr, manufacturingString As StringBuilder, ByRef strlen As Byte) As Integer

    ' HidUart_SetProductString
    Public Declare Function HidUart_SetProductString Lib "SLABHIDtoUART.dll" (device As IntPtr, productString As String, strlen As Byte) As Integer

    ' HidUart_GetProductString
    Public Declare Function HidUart_GetProductString Lib "SLABHIDtoUART.dll" (device As IntPtr, productString As StringBuilder, ByRef strlen As Byte) As Integer

    ' HidUart_SetSerialString
    Public Declare Function HidUart_SetSerialString Lib "SLABHIDtoUART.dll" (device As IntPtr, serialString As String, strlen As Byte) As Integer

    ' HidUart_GetSerialString
    Public Declare Function HidUart_GetSerialString Lib "SLABHIDtoUART.dll" (device As IntPtr, serialString As StringBuilder, ByRef strlen As Byte) As Integer
End Module
