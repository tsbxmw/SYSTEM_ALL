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


namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.listView1.GridLines = true;
            this.listView1.FullRowSelect = true;
            this.listView1.View = View.Details;
            this.listView1.Scrollable = true;
            this.listView1.MultiSelect = false;
            this.listView1.Items.Clear();
            FileStream fs = new FileStream("infofile.info", FileMode.Open, FileAccess.Read);
            StreamReader sr = new StreamReader(fs);
            sr.BaseStream.Seek(0, SeekOrigin.Begin);
            string str = sr.ReadToEnd();
            sr.Close();
            fs.Close();
            String[] sarray = str.Split('\n');
            foreach (string s in sarray)
            {
                ListViewItem item = new ListViewItem();
                item.SubItems.Clear();
                string[] ss = new String[5];
                ss = s.Split('-');
                item.SubItems[0].Text = ss[0];
                //   MessageBox.Show(ss.Count().ToString());

                //MessageBox.Show(ss[1]);
                if (ss.Count() > 4)
                {
                    item.SubItems.Add(ss[1]);
                    item.SubItems.Add(ss[2]);
                    item.SubItems.Add(ss[3]);
                    item.SubItems.Add(ss[4]);
                }
                //  MessageBox.Show("i am here");
                listView1.Items.Add(item);
            }
            for (int i = 0; i < listView1.Columns.Count; i++)
            {
                listView1.Columns[i].Width = -2;
            }

        }


        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            this.listView1.Items.Clear();
            FileStream fs = new FileStream("infofile.info",FileMode.Open,FileAccess.Read);
            StreamReader sr = new StreamReader(fs);
            sr.BaseStream.Seek(0, SeekOrigin.Begin);
            string str = sr.ReadToEnd();
            sr.Close();
            fs.Close();
            String[] sarray = str.Split('\n');
            foreach (string s in sarray)
            {
                ListViewItem item = new ListViewItem();
                item.SubItems.Clear();
                string[] ss = new String[5];
                ss = s.Split('-');
                item.SubItems[0].Text = ss[0];
             //   MessageBox.Show(ss.Count().ToString());
                
                //MessageBox.Show(ss[1]);
                if (ss.Count() > 4)
                {
                    item.SubItems.Add(ss[1]);
                    item.SubItems.Add(ss[2]);
                    item.SubItems.Add(ss[3]);
                    item.SubItems.Add(ss[4]);
                }
              //  MessageBox.Show("i am here");
                listView1.Items.Add(item);
            }
            for (int i = 0; i < listView1.Columns.Count; i++)
            {
                listView1.Columns[i].Width = -2;
            }


        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void listView1_SelectedIndexChanged_1(object sender, EventArgs e)
        {

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void listView2_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}
