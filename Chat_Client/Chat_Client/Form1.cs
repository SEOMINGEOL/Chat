using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net.Sockets;
using System.Threading;

namespace Chat_Client
{
    public partial class Form1 : Form
    {
        TcpClient user = new TcpClient();
        NetworkStream net_stream = default(NetworkStream);
        string data = string.Empty;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                user.Connect("127.0.0.1", 5678);
                net_stream = user.GetStream();
            }
            catch(Exception ex)
            {
                ShowText("Connect Failed. " + ex.ToString());
            }

            ShowText("Connect Server");

            Thread thread_user = new Thread(GetData);
            thread_user.IsBackground = true;
            thread_user.Start();
        }

        private void ShowText(string text)
        {
            if(textBox2.InvokeRequired)
            {
                textBox2.BeginInvoke(new MethodInvoker(delegate
                {
                    textBox2.AppendText(Environment.NewLine + text + Environment.NewLine);
                }));
            }
            else
                textBox2.AppendText(Environment.NewLine + text + Environment.NewLine);
        }

        private void GetData()
        {
            while(true)
            {
                net_stream = user.GetStream();
                int buf_size = user.ReceiveBufferSize;
                byte[] buf = new byte[buf_size];
                int byte_length = net_stream.Read(buf, 0, buf.Length);

                if (byte_length == 0)
                {
                    ShowText("서버에 접속할 수 없습니다. 잠시 후 다시 시도해주세요.");
                    return;
                }

                if (buf[0] == '*')
                    label2.Text = Encoding.Default.GetString(buf, 0, byte_length).Replace("*","");
                else
                    ShowText(Encoding.Default.GetString(buf, 0, byte_length));
            }
        }
        
        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
                this.button1_Click(this, e);
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            textBox1.Focus();
            byte[] buf = Encoding.GetEncoding("euc-kr").GetBytes("&" + textBox1.Text);
            net_stream.Write(buf, 0, buf.Length);
            net_stream.Flush();
            textBox1.Text = "";
        }

        private void button2_Click(object sender, EventArgs e)
        {
            textBox1.Focus();
            byte[] buf = Encoding.GetEncoding("euc-kr").GetBytes("*" + textBox3.Text);
            net_stream.Write(buf, 0, buf.Length);
            net_stream.Flush();
            textBox1.Text = "";
        }
    }
}
