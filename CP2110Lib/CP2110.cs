using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SLABHIDTOUART_DLL;

namespace CP2110Lib
{
    public class CP2110
    {
		int readTimeout;
		int writeTimeout;


		public ushort vid;
        public ushort pid;
        public uint index;
		byte partNumber;
		byte version;
		string serial;
		string path;
		string manufacturer;
		string product;
		private IntPtr device;

		// Data Bits
		public enum HID_UART_DATA_BITS
		{
			HID_UART_FIVE_DATA_BITS = 0x00,
			HID_UART_SIX_DATA_BITS = 0x01,
			HID_UART_SEVEN_DATA_BITS = 0x02,
			HID_UART_EIGHT_DATA_BITS = 0x03,
		}

		// Parity
		public enum HID_UART_PARITY
		{
			HID_UART_NO_PARITY = 0x00,
			HID_UART_ODD_PARITY = 0x01,
			HID_UART_EVEN_PARITY = 0x02,
			HID_UART_MARK_PARITY = 0x03,
			HID_UART_SPACE_PARITY = 0x04,
		}

		// Stop Bits
		// Short = 1 stop bit
		// Long = 1.5 stop bits (5 data bits)
		// = 2 stop bits (6-8 data bits)
		public enum HID_UART_STOP_BIT
		{
			HID_UART_SHORT_STOP_BIT = 0x00,
			HID_UART_LONG_STOP_BIT = 0x01,
		}

		// Flow Control
		public enum HID_UART_FLOW_CONTROL
		{
			HID_UART_NO_FLOW_CONTROL = 0x00,
			HID_UART_RTS_CTS_FLOW_CONTROL = 0x01,
		}


		public CP2110(ushort vid, ushort pid, uint index)
        {
            this.vid = vid;
            this.pid = pid;
            this.index = index;
			this.partNumber = 0;
			this.version = 0;
			this.serial = string.Empty;
			this.path = string.Empty;
			this.manufacturer = string.Empty;	
			this.product = string.Empty;
			this.readTimeout = 60;
			this.writeTimeout = 60;
		}


		// Connect to the device with the specified serial string and configure the UART
		// - Search for device with matching serial string
		// - Open matching device
		// - Get the device part number and version
		// - Configure device UART settings
		// - Output any error messages
		public bool Connect(uint baudRate, HID_UART_DATA_BITS dataBits, HID_UART_PARITY parity, HID_UART_STOP_BIT stopBits, HID_UART_FLOW_CONTROL flowControl)
		{
			SLABHIDTOUART.HID_UART_STATUS status = SLABHIDTOUART.HID_UART_STATUS.HID_UART_DEVICE_NOT_FOUND;


		  status = SLABHIDTOUART.HidUart_Open(ref device, index, vid, pid);
		


			// Found and opened the device
			if (status == SLABHIDTOUART.HID_UART_STATUS.HID_UART_SUCCESS)
			{
				// Get part number and version
				status = SLABHIDTOUART.HidUart_GetPartNumber(device, ref partNumber, ref version);
			}

			// Got part number
			if (status == SLABHIDTOUART.HID_UART_STATUS.HID_UART_SUCCESS)
			{
				// Configure the UART
				status = SLABHIDTOUART.HidUart_SetUartConfig(device, baudRate, (byte)dataBits, (byte)parity, (byte)stopBits, (byte)flowControl);
			}

			// Confirm UART settings
			if (status == SLABHIDTOUART.HID_UART_STATUS.HID_UART_SUCCESS)
			{
				uint vBaudRate = 0;
				byte vDataBits = 0;
				byte vParity = 0;
				byte vStopBits = 0;
				byte vFlowControl = 0;

				status = SLABHIDTOUART.HidUart_GetUartConfig(device, ref vBaudRate, ref vDataBits, ref vParity, ref vStopBits, ref vFlowControl);

				if (status == SLABHIDTOUART.HID_UART_STATUS.HID_UART_SUCCESS)
				{
					if (vBaudRate != baudRate ||
						vDataBits != (byte)dataBits ||
						vParity != (byte)parity ||
						vStopBits != (byte)stopBits ||
						vFlowControl != (byte)flowControl)
					{
						status = SLABHIDTOUART.HID_UART_STATUS.HID_UART_INVALID_PARAMETER;
					}
				}
			}

			// Configured the UART
			if (status == SLABHIDTOUART.HID_UART_STATUS.HID_UART_SUCCESS)
			{
				// Set short read timeouts for periodic read timer
				// Set longer write timeouts for user transmits
				status = SLABHIDTOUART.HidUart_SetTimeouts(device, (uint)readTimeout, (uint)writeTimeout);
			}

			// Fully connected to the device
			if (status == SLABHIDTOUART.HID_UART_STATUS.HID_UART_SUCCESS)
			{
				// Output the connection status to the status bar
				return true;
			}
			// Connect failed
			else
			{
				// Disconnect
				SLABHIDTOUART.HidUart_Close(device);


				//Todo err code
				//// Notify the user that an error occurred
				//CString msg;
				//msg.Format(_T("Failed to connect to %s: %s"), serial.GetString(), GetHidUartStatusStr(status).GetString());
				//MessageBox(msg, 0, MB_ICONWARNING);

				//// Update status
				//SetStatusText(_T("Not Connected"));
				return false;
			}


		}



		public bool Disconnect()
		{
			// Stop read timer

			// Close the device
			SLABHIDTOUART.HID_UART_STATUS status = SLABHIDTOUART.HidUart_Close(device);

			// Disconnect failed
			if (status != SLABHIDTOUART.HID_UART_STATUS.HID_UART_SUCCESS)
			{
				//Todo err code
				// Notify the user that an error occurred
				//CString msg;
				//msg.Format(_T("Failed to disconnect: %s"), GetHidUartStatusStr(status).GetString());
				//MessageBox(msg, 0, MB_ICONWARNING);
				return false;
			}


			return true;
		}



		private bool Receive(out byte[] RxData)
		{
			SLABHIDTOUART.HID_UART_STATUS status;
			uint numBytesRead = 0;
			uint numBytesToRead = 1000;
			byte[] buffer = new byte[numBytesToRead];

			// Receive UART data from the device (up to 1000 bytes)
			status = SLABHIDTOUART.HidUart_Read(device, buffer, numBytesToRead, ref numBytesRead);

			// HidUart_Read returns HID_UART_SUCCESS if numBytesRead == numBytesToRead
			// and returns HID_UART_READ_TIMED_OUT if numBytesRead < numBytesToRead
			if (status == SLABHIDTOUART.HID_UART_STATUS.HID_UART_SUCCESS || status == SLABHIDTOUART.HID_UART_STATUS.HID_UART_READ_TIMED_OUT)
			{
				// Output received data to the receive window
				if (numBytesRead > 0)
				{

					RxData = new byte[numBytesRead];
					if (numBytesRead > numBytesToRead)
					{
						numBytesRead = numBytesToRead;
					}
					Array.Copy(buffer, 0, RxData, 0, numBytesRead);
					//m_hexEditReceive.AppendWindowHex(buffer, numBytesRead);
					return true;
				}
			}

			RxData = new byte[1];
			return false;
		}


		// Transmit entered text using ASCII or hex format
		public void Send(byte[] TxData)
		{
			bool opened = false;
			SLABHIDTOUART.HID_UART_STATUS status;
			uint numBytesWritten = 0;

			if (TxData == null)
			{
				return;
			}

			// Check if the device is opened
			if (SLABHIDTOUART.HidUart_IsOpened(device, ref opened) == SLABHIDTOUART.HID_UART_STATUS.HID_UART_SUCCESS && opened)
			{
				uint numBytesToWrite = (uint)TxData.Length;

				// Send the UART data to the device to transmit
				status = SLABHIDTOUART.HidUart_Write(device, TxData, numBytesToWrite, ref numBytesWritten);

				// Notify the user that an error occurred
				if ((status == SLABHIDTOUART.HID_UART_STATUS.HID_UART_SUCCESS) && (numBytesToWrite == numBytesWritten))
				{
					//Todo:err code
					//CString msg;
					//msg.Format(_T("Failed to transmit : %s"), GetHidUartStatusStr(status).GetString());
					//MessageBox(msg, 0, MB_ICONWARNING);
					return;
				}


			}



		}




		/// <summary>
		/// 发收(指定最大等待时间)
		/// </summary>
		/// <param name="TxData"></param>
		/// <param name="RxData"></param>
		/// <returns></returns>
		public bool SendAndReceive(byte[] TxData, out byte[] RxData)
		{
			return SendAndReceive(TxData, out RxData, 10000);//原先为1000
		}

		/// <summary>
		/// 发送接收
		/// </summary>
		/// <param name="TxData"></param>
		/// <param name="RxData"></param>
		/// <param name="iMaxWaitTime"></param>
		/// <returns></returns>
		public bool WaitReply(out byte[] RxData, int iMaxWaitTime)
		{

			try
			{

				int iTry = iMaxWaitTime / readTimeout;
				int iLoop = 0;
				bool bReceived = false;
				byte[] DataTmp = new byte[1];

				RxData = new byte[0];



				for (iLoop = 0; iLoop < iTry; iLoop++)
				{
					if (Receive(out DataTmp))
					{
						bReceived = true;
						//RxData = Result;
						byte[] btTotal = new byte[DataTmp.Length + RxData.Length];
						RxData.CopyTo(btTotal, 0);
						DataTmp.CopyTo(btTotal, RxData.Length);


						RxData = new byte[btTotal.Length];
						RxData = btTotal;

						iLoop = -1;  
						continue;
					}
					else
					{
						if (bReceived) 
						{
							return true;
						}
					}
				}

				if (iLoop >= iTry)
				{
					RxData = new byte[1];
					return false;
				}

				RxData = new byte[1];
				return false;

			}
			catch
			{
				RxData = new byte[1];
				return false;
			}

		}

		/// <summary>
		/// 发送接收
		/// </summary>
		/// <param name="TxData"></param>
		/// <param name="RxData"></param>
		/// <param name="iMaxWaitTime"></param>
		/// <returns></returns>
		public bool SendAndReceive(byte[] TxData, out byte[] RxData, int iMaxWaitTime)
		{

			try
			{

				int iTry = iMaxWaitTime / readTimeout;
				int iLoop = 0;
				bool bReceived = false;
				byte[] DataTmp = new byte[1];

				RxData = new byte[0];

				Send(TxData);

				for (iLoop = 0; iLoop < iTry; iLoop++)
				{
					if (Receive(out DataTmp))
					{
						bReceived = true;
						//RxData = Result;
						byte[] btTotal = new byte[DataTmp.Length + RxData.Length];
						RxData.CopyTo(btTotal, 0);
						DataTmp.CopyTo(btTotal, RxData.Length);


						RxData = new byte[btTotal.Length];
						RxData = btTotal;

						iLoop = -1; 
						continue;
					}
					else
					{
						if (bReceived)
						{
							return true;
						}
					}
				}

				if (iLoop >= iTry)
				{
					RxData = new byte[1];
					return false;
				}

				RxData = new byte[1];
				return false;

			}
			catch
			{
				RxData = new byte[1];
				return false;
			}

		}


		// Retrieve device information strings and display on the dialog
		void UpdateDeviceInformation()
		{
			string deviceString = String.Empty;

			Byte[] data = new Byte[100];


			// Update VID string
			if (SLABHIDTOUART.HidUart_GetOpenedString(device, ref data[0], SLABHIDTOUART.HID_UART_GET_VID_STR) == SLABHIDTOUART.HID_UART_STATUS.HID_UART_SUCCESS)
			{
				deviceString = System.Text.Encoding.Default.GetString(data);
				vid = Convert.ToUInt16(deviceString);
			}

			// Update PID string
			if (SLABHIDTOUART.HidUart_GetOpenedString(device, ref data[0], SLABHIDTOUART.HID_UART_GET_PID_STR) == SLABHIDTOUART.HID_UART_STATUS.HID_UART_SUCCESS)
			{
				deviceString = System.Text.Encoding.Default.GetString(data);
				pid = Convert.ToUInt16(deviceString);
			}

			// Update serial string
			if (SLABHIDTOUART.HidUart_GetOpenedString(device, ref data[0], SLABHIDTOUART.HID_UART_GET_SERIAL_STR) == SLABHIDTOUART.HID_UART_STATUS.HID_UART_SUCCESS)
			{
				deviceString = System.Text.Encoding.Default.GetString(data);
				serial = deviceString;
			}

			// Update device path string
			if (SLABHIDTOUART.HidUart_GetOpenedString(device, ref data[0], SLABHIDTOUART.HID_UART_GET_PATH_STR) == SLABHIDTOUART.HID_UART_STATUS.HID_UART_SUCCESS)
			{
				deviceString = System.Text.Encoding.Default.GetString(data);
				path = deviceString;
			}

			// Update manufacturer string
			if (SLABHIDTOUART.HidUart_GetOpenedString(device, ref data[0], SLABHIDTOUART.HID_UART_GET_MANUFACTURER_STR) == SLABHIDTOUART.HID_UART_STATUS.HID_UART_SUCCESS)
			{
				deviceString = System.Text.Encoding.Default.GetString(data);
				manufacturer = deviceString;
			}

			// Update product string
			if (SLABHIDTOUART.HidUart_GetOpenedString(device, ref data[0], SLABHIDTOUART.HID_UART_GET_PRODUCT_STR) == SLABHIDTOUART.HID_UART_STATUS.HID_UART_SUCCESS)
			{
				deviceString = System.Text.Encoding.Default.GetString(data);
				product = deviceString;
			}

		}







		//public string serial
		//{

		//    get
		//    {


		//        uint numDevices = 0;

		//        try
		//        {
		//            if (SLABHIDTOUART.HidUart_GetNumDevices(ref numDevices, VID, PID) == SLABHIDTOUART.HID_UART_SUCCESS)
		//            {

		//                string[] names = new string[numDevices];

		//                for (uint i = 0; i < numDevices; i++)
		//                {
		//                    Byte[] data = new Byte[100];

		//                    // Search through all HID devices for a %matching serial string
		//                    if (SLABHIDTOUART.HidUart_GetString(i, VID, PID, ref data[0], SLABHIDTOUART.HID_UART_GET_SERIAL_STR) == SLABHIDTOUART.HID_UART_SUCCESS)
		//                    {

		//                        names[i] = System.Text.Encoding.Default.GetString(data);
		//                        // cbPort.Items.Add(names[i]);
		//                    }
		//                    else
		//                    {
		//                        names[i] = deviceString.ToString();
		//                        //cbPort.Items.Add(names[i]);

		//                    }
		//                }

		//            }



		//        }


		//}




		//{

		//    uint numDevices = 0;

		//    try
		//    {
		//        if (SLABHIDTOUART.HidUart_GetNumDevices(ref numDevices, VID, PID) == SLABHIDTOUART.HID_UART_SUCCESS)
		//        {

		//            string[] names = new string[numDevices];

		//            for (uint i = 0; i < numDevices; i++)
		//            {
		//                Byte[] data = new Byte[100];

		//                // Search through all HID devices for a %matching serial string
		//                if (SLABHIDTOUART.HidUart_GetString(i, VID, PID, ref data[0], SLABHIDTOUART.HID_UART_GET_SERIAL_STR) == SLABHIDTOUART.HID_UART_SUCCESS)
		//                {

		//                     names[i] = System.Text.Encoding.Default.GetString(data);
		//                   // cbPort.Items.Add(names[i]);
		//                }
		//                else
		//                {
		//                    names[i] = deviceString.ToString();
		//                    //cbPort.Items.Add(names[i]);

		//                }
		//            }

		//        }
		//    }
		//    catch (Exception ex)
		//    {

		//     //   MessageBox.Show(ex.Message);
		//    }


		//}






	}
}
