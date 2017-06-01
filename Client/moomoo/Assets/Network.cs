using UnityEngine;
using System.Collections;
using System.Net.Sockets;
using System.Net;
using System.Text;
using System.Threading;
using PT;

public class Network
{
    private static Network _instance;

    private static Socket m_Socket;

    string iPAdress = "13.124.83.116";
    int kPort = 9095;

    Thread readThread;

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

        ThreadStart readThreadStart = new ThreadStart(receive);
        readThread = new Thread(readThreadStart);
        readThread.IsBackground = true;
        readThread.Start();
    }
    
    public void send(byte[] buffer, int size)
    {
        try
        {
            m_Socket.Send(buffer, size, 0);
        }
        catch (SocketException err)
        {
            Debug.Log("Socket send or receive error! : " + err.ToString());
        }
    }
    
    public static void receive()
    {
        byte[] Receivebyte = new byte[2000];    // Receive data by this array to save.
        string ReceiveString;
        int ReceivedataLength;

        while (true)
        {
            try
            {
                m_Socket.Receive(Receivebyte);
                ReceiveString = Encoding.Default.GetString(Receivebyte);
                ReceivedataLength = Encoding.Default.GetByteCount(ReceiveString.ToString());

                _header ack = new _header();
                ack.Deserialize(Receivebyte);
                
                switch ((Protocol)ack.protocolID)
                {
                    case Protocol.PROTOCOL_JOIN_ACK:
                        S_PROTOCOL_JOIN_ACK join_ack = new S_PROTOCOL_JOIN_ACK();
                        join_ack.Deserialize(Receivebyte);
                        Communicator.I().cb.Enqueue(ack);
                        Communicator.I().cb.Enqueue(join_ack);
                        break;

                    case Protocol.PROTOCOL_LOGIN_ACK:
                        S_PROTOCOL_LOGIN_ACK login_ack = new S_PROTOCOL_LOGIN_ACK();
                        login_ack.Deserialize(Receivebyte);
                        Communicator.I().cb.Enqueue(ack);
                        Communicator.I().cb.Enqueue(login_ack);
                        break;
                }
            }
            catch (SocketException err)
            {
                Debug.Log("Socket send or receive error! : " + err.ToString());
            }
        }
    }

    public static Network i()
    {
        if (_instance == null) _instance = new Network();
        return _instance;
    }

    public void terminate()
    {
        if (readThread != null)
            readThread.Abort();
    }

    ~Network()
    {
        Debug.Log("NETWORK DESTROYED");

        m_Socket.Close();
        m_Socket = null;
    }

}