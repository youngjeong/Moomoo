using UnityEngine;
using System.Collections;
using System.Net.Sockets;
using System.Net;
using System.Text;

public class Network
{
    private static Network _instance;

    private Socket m_Socket;

    string iPAdress = "13.124.83.116";
    int kPort = 9090;

    private int SenddataLength;                     // Send Data Length. (byte)
    private int ReceivedataLength;                     // Receive Data Length. (byte)

    private byte[] Sendbyte;                        // Data encoding to send. ( to Change bytes)
    private byte[] Receivebyte = new byte[2000];    // Receive data by this array to save.
    private string ReceiveString;


    public Network()
    {
        Debug.Log("NETWORK CREATED");
        //=======================================================
        // Socket create.
        m_Socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        m_Socket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.SendTimeout, 10000);
        m_Socket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReceiveTimeout, 10000);

        //=======================================================
        // Socket connect.
        try
        {
            IPAddress ipAddr = System.Net.IPAddress.Parse(iPAdress);
            IPEndPoint ipEndPoint = new System.Net.IPEndPoint(ipAddr, kPort);
            m_Socket.Connect(ipEndPoint);
        }
        catch (SocketException SCE)
        {
            Debug.Log("Socket connect error! : " + SCE.ToString());
            return;
        }

        receive();
    }

    public void send(byte[] buffer, int size)
    {
        try
        {
            //=======================================================
            // Send.
            m_Socket.Send(buffer, size, 0);

            //=======================================================       
            // Receive.
            m_Socket.Receive(Receivebyte);
            ReceiveString = Encoding.Default.GetString(Receivebyte);
            ReceivedataLength = Encoding.Default.GetByteCount(ReceiveString.ToString());
            Debug.Log("Receive Data : " + ReceiveString + "(" + ReceivedataLength + ")");
        }
        catch (SocketException err)
        {
            Debug.Log("Socket send or receive error! : " + err.ToString());
        }
    }

    IEnumerator receive()
    {
        try
        {
            m_Socket.Receive(Receivebyte);
            ReceiveString = Encoding.Default.GetString(Receivebyte);
            ReceivedataLength = Encoding.Default.GetByteCount(ReceiveString.ToString());
            Debug.Log("Receive Data : " + ReceiveString + "(" + ReceivedataLength + ")");
        }
        catch (SocketException err)
        {
            Debug.Log("Socket send or receive error! : " + err.ToString());
        }

        yield return null;
    }

    public static Network i()
    {
        if (_instance == null) _instance = new Network();
        return _instance;
    }

    ~Network()
    {
        m_Socket.Close();
        m_Socket = null;
    }

}