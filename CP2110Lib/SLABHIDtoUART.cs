

/***************************************************************************   
**  2022-06-16 modify by ноеё╬Щ iFancyit
**  make HID_UART_STATUS to enum
**  make HID_UART_XXXXXX to enum
***************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace SLABHIDTOUART_DLL
{
    internal class SLABHIDTOUART
    {
        /////////////////////////////////////////////////////////////////////////////
        // SLABHIDtoUART.h
        // For SLABHIDtoUART.dll version 2.0
        // and Silicon Labs CP2110/CP2114 HID to UART
        /////////////////////////////////////////////////////////////////////////////

        // The following ifdef block is the standard way of creating macros which make exporting
        // from a DLL simpler. All files within this DLL are compiled with the HID_TO_UART_EXPORTS
        // symbol defined on the command line. this symbol should not be defined on any project
        // that uses this DLL. This way any other project whose source files include this file see
        // functions as being imported from a DLL, whereas this DLL sees symbols
        // defined with this macro as being exported.

        /////////////////////////////////////////////////////////////////////////////
        // Return Code Definitions
        /////////////////////////////////////////////////////////////////////////////

        // HID_UART_STATUS

        // Return Codes
        public enum HID_UART_STATUS
        {
            HID_UART_SUCCESS = 0x00,
            HID_UART_DEVICE_NOT_FOUND = 0x01,
            HID_UART_INVALID_HANDLE = 0x02,
            HID_UART_INVALID_DEVICE_OBJECT = 0x03,
            HID_UART_INVALID_PARAMETER = 0x04,
            HID_UART_INVALID_REQUEST_LENGTH = 0x05,

            HID_UART_READ_ERROR = 0x10,
            HID_UART_WRITE_ERROR = 0x11,
            HID_UART_READ_TIMED_OUT = 0x12,
            HID_UART_WRITE_TIMED_OUT = 0x13,
            HID_UART_DEVICE_IO_FAILED = 0x14,
            HID_UART_DEVICE_ACCESS_ERROR = 0x15,
            HID_UART_DEVICE_NOT_SUPPORTED = 0x16,

            HID_UART_UNKNOWN_ERROR = 0xFF,
        }

        /////////////////////////////////////////////////////////////////////////////
        // String Definitions
        /////////////////////////////////////////////////////////////////////////////

        // Product String Types
        public const byte HID_UART_GET_VID_STR = 0x01;
        public const byte HID_UART_GET_PID_STR = 0x02;
        public const byte HID_UART_GET_PATH_STR = 0x03;
        public const byte HID_UART_GET_SERIAL_STR = 0x04;
        public const byte HID_UART_GET_MANUFACTURER_STR = 0x05;
        public const byte HID_UART_GET_PRODUCT_STR = 0x06;

        // String Lengths
        public const int HID_UART_DEVICE_STRLEN = 260;

        // HID_UART_DEVICE_STR

        /////////////////////////////////////////////////////////////////////////////
        // UART Definitions
        /////////////////////////////////////////////////////////////////////////////

        // Error Status
        public const byte HID_UART_PARITY_ERROR = 0x01;
        public const byte HID_UART_OVERRUN_ERROR = 0x02;

        // Line Break Status
        public const byte HID_UART_LINE_BREAK_INACTIVE = 0x00;
        public const byte HID_UART_LINE_BREAK_ACTIVE = 0x01;

  

        // Read/Write Limits
        public const int HID_UART_MIN_READ_SIZE = 1;
        public const int HID_UART_MAX_READ_SIZE = 32768;
        public const int HID_UART_MIN_WRITE_SIZE = 1;
        public const int HID_UART_MAX_WRITE_SIZE = 4096;

        /////////////////////////////////////////////////////////////////////////////
        // Part Number Definitions
        /////////////////////////////////////////////////////////////////////////////

        // Part Numbers
        public const byte HID_UART_PART_CP2110 = 0x0A;
        public const byte HID_UART_PART_CP2114 = 0x0E;

        /////////////////////////////////////////////////////////////////////////////
        // User Customization Definitions
        /////////////////////////////////////////////////////////////////////////////

        // User-Customizable Field Lock Bitmasks
        public const ushort HID_UART_LOCK_PRODUCT_STR_1 = 0x0001;
        public const ushort HID_UART_LOCK_PRODUCT_STR_2 = 0x0002;
        public const ushort HID_UART_LOCK_SERIAL_STR = 0x0004;
        public const ushort HID_UART_LOCK_PIN_CONFIG = 0x0008;
        public const ushort HID_UART_LOCK_VID = 0x0100;
        public const ushort HID_UART_LOCK_PID = 0x0200;
        public const ushort HID_UART_LOCK_POWER = 0x0400;
        public const ushort HID_UART_LOCK_POWER_MODE = 0x0800;
        public const ushort HID_UART_LOCK_RELEASE_VERSION = 0x1000;
        public const ushort HID_UART_LOCK_FLUSH_BUFFERS = 0x2000;
        public const ushort HID_UART_LOCK_MFG_STR_1 = 0x4000;
        public const ushort HID_UART_LOCK_MFG_STR_2 = 0x8000;

        // Field Lock Bit Values
        public const int HID_UART_LOCK_UNLOCKED = 1;
        public const int HID_UART_LOCK_LOCKED = 0;

        // Power Max Value (500 mA)
        public const byte HID_UART_BUS_POWER_MAX = 0xFA;

        // Power Modes
        public const byte HID_UART_BUS_POWER = 0x00;
        public const byte HID_UART_SELF_POWER_VREG_DIS = 0x01;
        public const byte HID_UART_SELF_POWER_VREG_EN = 0x02;

        // Flush Buffers Bitmasks
        public const byte HID_UART_FLUSH_TX_OPEN = 0x01;
        public const byte HID_UART_FLUSH_TX_CLOSE = 0x02;
        public const byte HID_UART_FLUSH_RX_OPEN = 0x04;
        public const byte HID_UART_FLUSH_RX_CLOSE = 0x08;

        // USB Config Bitmasks
        public const byte HID_UART_SET_VID = 0x01;
        public const byte HID_UART_SET_PID = 0x02;
        public const byte HID_UART_SET_POWER = 0x04;
        public const byte HID_UART_SET_POWER_MODE = 0x08;
        public const byte HID_UART_SET_RELEASE_VERSION = 0x10;
        public const byte HID_UART_SET_FLUSH_BUFFERS = 0x20;

        // USB Config Bit Values
        public const int HID_UART_SET_IGNORE = 0;
        public const int HID_UART_SET_PROGRAM = 1;

        // String Lengths
        public const int HID_UART_MFG_STRLEN = 62;
        public const int HID_UART_PRODUCT_STRLEN = 62;
        public const int HID_UART_SERIAL_STRLEN = 30;

        // HID_UART_MFG_STR

        // HID_UART_PRODUCT_STR

        // HID_UART_SERIAL_STR

        /////////////////////////////////////////////////////////////////////////////
        // Pin Definitions
        /////////////////////////////////////////////////////////////////////////////

        // Pin Config Modes
        public const byte HID_UART_GPIO_MODE_INPUT = 0x00;
        public const byte HID_UART_GPIO_MODE_OUTPUT_OD = 0x01;
        public const byte HID_UART_GPIO_MODE_OUTPUT_PP = 0x02;
        public const byte HID_UART_GPIO_MODE_FUNCTION1 = 0x03;
        public const byte HID_UART_GPIO_MODE_FUNCTION2 = 0x04;

        // Suspend Value Bit Values
        public const int HID_UART_VALUE_SUSPEND_LO = 0;
        public const int HID_UART_VALUE_SUSPEND_HI = 1;

        // Suspend Mode Bit Values
        public const int HID_UART_MODE_SUSPEND_OD = 0;
        public const int HID_UART_MODE_SUSPEND_PP = 1;

        // RS485 Active Levels
        public const byte HID_UART_MODE_RS485_ACTIVE_LO = 0x00;
        public const byte HID_UART_MODE_RS485_ACTIVE_HI = 0x01;

        /////////////////////////////////////////////////////////////////////////////
        // Typedefs
        /////////////////////////////////////////////////////////////////////////////

        /////////////////////////////////////////////////////////////////////////////
        // Exported Library Functions
        /////////////////////////////////////////////////////////////////////////////

        // HidUart_GetNumDevices
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_GetNumDevices(ref uint numDevices, ushort vid, ushort pid);

        // HidUart_GetString
        [DllImport("SLABHIDtoUART.dll")]
        //public static extern int HidUart_GetString(uint deviceNum, ushort vid, ushort pid, StringBuilder deviceString, uint options);
        public static extern HID_UART_STATUS HidUart_GetString(uint deviceNum, ushort vid, ushort pid, ref byte deviceString, uint options);

        // HidUart_GetOpenedString
        [DllImport("SLABHIDtoUART.dll")]
        //public static extern HID_UART_STATUS HidUart_GetOpenedString(IntPtr device, StringBuilder deviceString, uint options);
        public static extern HID_UART_STATUS HidUart_GetOpenedString(IntPtr device, ref byte deviceString, uint options);

        // HidUart_GetIndexedString
        [DllImport("SLABHIDtoUART.dll")]
        //public static extern HID_UART_STATUS HidUart_GetIndexedString(uint deviceNum, ushort vid, ushort pid, uint stringIndex, StringBuilder deviceString);
        public static extern HID_UART_STATUS HidUart_GetIndexedString(uint deviceNum, ushort vid, ushort pid, uint stringIndex, ref byte deviceString);

        // HidUart_GetOpenedIndexedString
        [DllImport("SLABHIDtoUART.dll")]
        //public static extern HID_UART_STATUS HidUart_GetOpenedIndexedString(IntPtr device, uint stringIndex, StringBuilder deviceString);
        public static extern HID_UART_STATUS HidUart_GetOpenedIndexedString(IntPtr device, uint stringIndex, ref byte deviceString);

        // HidUart_GetAttributes
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_GetAttributes(uint deviceNum, ushort vid, ushort pid, ref ushort deviceVid, ref ushort devicePid, ref ushort deviceReleaseNumber);

        // HidUart_GetOpenedAttributes
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_GetOpenedAttributes(IntPtr device, ref ushort deviceVid, ref ushort devicePid, ref ushort deviceReleaseNumber);

        // HidUart_Open
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_Open(ref IntPtr device, uint deviceNum, ushort vid, ushort pid);

        // HidUart_Close
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_Close(IntPtr device);

        // HidUart_IsOpened
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_IsOpened(IntPtr device, ref bool opened);

        // HidUart_SetUartEnable
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_SetUartEnable(IntPtr device, bool enable);

        // HidUart_GetUartEnable
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_GetUartEnable(IntPtr device, ref bool enable);

        // HidUart_Read
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_Read(IntPtr device, byte[] buffer, uint numBytesToRead, ref uint numBytesRead);

        // HidUart_Write
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_Write(IntPtr device, byte[] buffer, uint numBytesToWrite, ref uint numBytesWritten);

        // HidUart_FlushBuffers
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_FlushBuffers(IntPtr device, bool flushTransmit, bool flushReceive);

        // HidUart_CancelIo
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_CancelIo(IntPtr device);

        // HidUart_SetTimeouts
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_SetTimeouts(IntPtr device, uint readTimeout, uint writeTimeout);

        // HidUart_GetTimeouts
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_GetTimeouts(IntPtr device, ref uint readTimeout, ref uint writeTimeout);

        // HidUart_GetUARTStatus
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_GetUartStatus(IntPtr device, ref ushort transmitFifoSize, ref ushort receiveFifoSize, ref byte errorStatus, ref byte lineBreakStatus);

        // HidUart_SetUARTConfig
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_SetUartConfig(IntPtr device, uint baudRate, byte dataBits, byte parity, byte stopBits, byte flowControl);

        // HidUart_GetUARTConfig
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_GetUartConfig(IntPtr device, ref uint baudRate, ref byte dataBits, ref byte parity, ref byte stopBits, ref byte flowControl);

        // HidUart_StartBreak
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_StartBreak(IntPtr device, byte duration);

        // HidUart_StopBreak
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_StopBreak(IntPtr device);

        // HidUart_Reset
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_Reset(IntPtr device);

        // HidUart_ReadLatch
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_ReadLatch(IntPtr device, ref ushort latchValue);

        // HidUart_WriteLatch
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_WriteLatch(IntPtr device, ushort latchValue, ushort latchMask);

        // HidUart_GetPartNumber
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_GetPartNumber(IntPtr device, ref byte partNumber, ref byte version);

        // HidUart_GetLibraryVersion
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_GetLibraryVersion(ref byte major, ref byte minor, ref bool release);

        // HidUart_GetHidLibraryVersion
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_GetHidLibraryVersion(ref byte major, ref byte minor, ref bool release);

        // HidUart_GetHidGuid
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_GetHidGuid(ref Guid guid);

        // HidUart_SetLock
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_SetLock(IntPtr device, ushort _lock);

        // HidUart_GetLock
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_GetLock(IntPtr device, ref ushort _lock);

        // HidUart_SetUsbConfig
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_SetUsbConfig(IntPtr device, ushort vid, ushort pid, byte power, byte powerMode, ushort releaseVersion, byte flushBuffers, byte mask);

        // HidUart_GetUsbConfig
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_GetUsbConfig(IntPtr device, ref ushort vid, ref ushort pid, ref byte power, ref byte powerMode, ref ushort releaseVersion, ref byte flushBuffers);

        // HidUart_SetManufacturingString
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_SetManufacturingString(IntPtr device, string manufacturingString, byte strlen);

        // HidUart_GetManufacturingString
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_GetManufacturingString(IntPtr device, StringBuilder manufacturingString, ref byte strlen);

        // HidUart_SetProductString
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_SetProductString(IntPtr device, string productString, byte strlen);

        // HidUart_GetProductString
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_GetProductString(IntPtr device, StringBuilder productString, ref byte strlen);

        // HidUart_SetSerialString
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_SetSerialString(IntPtr device, string serialString, byte strlen);

        // HidUart_GetSerialString
        [DllImport("SLABHIDtoUART.dll")]
        public static extern HID_UART_STATUS HidUart_GetSerialString(IntPtr device, StringBuilder serialString, ref byte strlen);
    }
}
