Imports System
Imports System.Collections.Generic
Imports System.Text
Imports System.Runtime.InteropServices

Module SLABCP2110
    '///////////////////////////////////////////////////////////////////////////
    ' SLABCP2110.h
    ' For SLABHIDtoUART.dll version 2.0
    ' and Silicon Labs CP2110 HID to UART
    '///////////////////////////////////////////////////////////////////////////

    '///////////////////////////////////////////////////////////////////////////
    ' Includes
    '///////////////////////////////////////////////////////////////////////////

    '///////////////////////////////////////////////////////////////////////////
    ' Pin Definitions
    '///////////////////////////////////////////////////////////////////////////

    ' Pin Config Mode Array Indices
    Public Const CP2110_INDEX_GPIO_0_CLK As Integer = 0
    Public Const CP2110_INDEX_GPIO_1_RTS As Integer = 1
    Public Const CP2110_INDEX_GPIO_2_CTS As Integer = 2
    Public Const CP2110_INDEX_GPIO_3_RS485 As Integer = 3
    Public Const CP2110_INDEX_GPIO_4_TX_TOGGLE As Integer = 4
    Public Const CP2110_INDEX_GPIO_5_RX_TOGGLE As Integer = 5
    Public Const CP2110_INDEX_GPIO_6 As Integer = 6
    Public Const CP2110_INDEX_GPIO_7 As Integer = 7
    Public Const CP2110_INDEX_GPIO_8 As Integer = 8
    Public Const CP2110_INDEX_GPIO_9 As Integer = 9
    Public Const CP2110_INDEX_TX As Integer = 10
    Public Const CP2110_INDEX_SUSPEND As Integer = 11
    Public Const CP2110_INDEX_SUSPEND_BAR As Integer = 12

    ' Pin Bitmasks
    Public Const CP2110_MASK_GPIO_0_CLK As UShort = &H0001
    Public Const CP2110_MASK_GPIO_1_RTS As UShort = &H0002
    Public Const CP2110_MASK_GPIO_2_CTS As UShort = &H0004
    Public Const CP2110_MASK_GPIO_3_RS485 As UShort = &H0008
    Public Const CP2110_MASK_TX As UShort = &H0010
    Public Const CP2110_MASK_RX As UShort = &H0020
    Public Const CP2110_MASK_GPIO_4_TX_TOGGLE As UShort = &H0040
    Public Const CP2110_MASK_GPIO_5_RX_TOGGLE As UShort = &H0080
    Public Const CP2110_MASK_SUSPEND_BAR As UShort = &H0100
    ' NA
    Public Const CP2110_MASK_GPIO_6 As UShort = &H0400
    Public Const CP2110_MASK_GPIO_7 As UShort = &H0800
    Public Const CP2110_MASK_GPIO_8 As UShort = &H1000
    Public Const CP2110_MASK_GPIO_9 As UShort = &H2000
    Public Const CP2110_MASK_SUSPEND As UShort = &H4000

    '///////////////////////////////////////////////////////////////////////////
    ' Exported Library Functions
    '///////////////////////////////////////////////////////////////////////////

    ' HidUart_SetPinConfig
    Public Declare Function HidUart_SetPinConfig Lib "SLABHIDtoUART.dll" (device As IntPtr, pinConfig() As Byte, useSuspendValues As Boolean, suspendValue As UShort, suspendMode As UShort, rs485Level As Byte, clkDiv As Byte) As Integer

    ' HidUart_GetPinConfig
    Public Declare Function HidUart_GetPinConfig Lib "SLABHIDtoUART.dll" (device As IntPtr, pinConfig() As Byte, ByRef useSuspendValues As Boolean, ByRef suspendValue As UShort, ByRef suspendMode As UShort, ByRef rs485Level As Byte, ByRef clkDiv As Byte) As Integer
End Module
