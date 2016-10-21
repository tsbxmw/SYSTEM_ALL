using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace WindowsFormsApplication2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.button1.Text = "刷新";
            this.AutoScroll = true;
            FileStream fs = new FileStream("openbat.ini", FileMode.Open, FileAccess.Read);
            StreamReader sr = new StreamReader(fs);
            sr.BaseStream.Seek(0, SeekOrigin.Begin);
            string str = sr.ReadToEnd();
            sr.Close();
            fs.Close();
            String[] sarray = str.Split('\n');
            int i = 0, j = 0;
            for (int k = 0; k < sarray.Count(); k++)
            {
                string ss = sarray[k];
                Console.WriteLine(ss);
                if (ss.Count() > 2 && ss[0] == ':' && ss[1] == ':' && ss[2] == ' ')
                {
                    TextBox tb = new TextBox();
                    tb.Text = ss;
                    tb.Left = 20;
                    tb.Top = 50 + i * 30;
                    this.Controls.Add(tb);
                    i++;
                }
                else
                {
                    Button button = new Button();
                    button.Text = ss;
                    button.Left = 150;
                    button.Top = 50 + j * 30;
                    button.Click += new System.EventHandler(button_click);
                    j++;
                    this.Controls.Add(button);
                }

            }
        }
        private void button_click(object sender, EventArgs e)
        {
            Button button = (Button)sender;
            string str = button.Text;
            System.Diagnostics.Process process = new System.Diagnostics.Process();
            process.StartInfo.FileName = "cmd.exe";
            process.StartInfo.UseShellExecute = false;
            process.StartInfo.RedirectStandardInput = true;
            process.StartInfo.RedirectStandardOutput = true;
            process.StartInfo.CreateNoWindow = true;
            process.Start();
            process.StandardInput.WriteLine(str);
            string soutput = process.StandardOutput.ReadToEnd();
            MessageBox.Show(str);
        }
        private void button1_Click(object sender, EventArgs e)
        {

            this.AutoScroll = true;
            FileStream fs = new FileStream("openbat.ini", FileMode.Open, FileAccess.Read);
            StreamReader sr = new StreamReader(fs);
            sr.BaseStream.Seek(0, SeekOrigin.Begin);
            string str = sr.ReadToEnd();
            sr.Close();
            fs.Close();
            String[] sarray = str.Split('\n');
            int i = 0, j = 0;
            for (int k = 0; k < sarray.Count(); k++)
            {
                string ss = sarray[k];
                Console.WriteLine(ss);
                if (ss.Count() > 2 && ss[0] == ':' && ss[1] == ':' && ss[2] == ' ')
                {
                    TextBox tb = new TextBox();
                    tb.Text = ss;
                    tb.Left = 20;
                    tb.Top = 50 + i * 30;
                    this.Controls.Add(tb);
                    i++;
                }
                else
                {
                    Button button = new Button();
                    button.Text = ss;
                    button.Left = 150;
                    button.Top = 50 + j * 30;
                    button.Click += new System.EventHandler(button_click);
                    j++;
                    this.Controls.Add(button);
                }

            }
        }
    }
}
