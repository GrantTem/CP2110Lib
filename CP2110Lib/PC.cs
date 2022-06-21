using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SLABHIDTOUART_DLL;

namespace CP2110Lib
{
    public class PC
    {

        public static List<string> GetSerialList(ushort pid, ushort vid)
        {

       
            try
            {
                List<string> list = new List<string>();
                uint numDevices = 0;
                if (SLABHIDTOUART.HidUart_GetNumDevices(ref numDevices, vid, pid) == SLABHIDTOUART.HID_UART_STATUS.HID_UART_SUCCESS)
                {

                    string[] names = new string[numDevices];

                    for (uint i = 0; i < numDevices; i++)
                    {
                        Byte[] data = new Byte[100];

                        // Search through all HID devices for a %matching serial string
                        if (SLABHIDTOUART.HidUart_GetString(i, vid, pid, ref data[0], SLABHIDTOUART.HID_UART_GET_SERIAL_STR) == SLABHIDTOUART.HID_UART_STATUS.HID_UART_SUCCESS)
                        {

                            list.Add(System.Text.Encoding.Default.GetString(data));

                        }
      
                    }

                }

                return list;
            }
            catch (Exception ex)
            {
                return null;
                //   MessageBox.Show(ex.Message);
            }

        }

    }
}
