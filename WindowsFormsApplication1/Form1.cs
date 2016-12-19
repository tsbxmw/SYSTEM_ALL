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
using MySql.Data;
using MySql.Data.MySqlClient;



namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        String day = null;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.listView1.BeginUpdate();
            this.listView1.Items.Clear();
            this.listView1.EndUpdate();

        }

 
        
            
            

        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click_1(object sender, EventArgs e)
        {

            this.listView1.BeginUpdate();
            this.listView1.Items.Clear();
            string user_id, password, email, team, user_name, register_time;
            int sex;

            String constr = "server=10.63.220.3;User Id=root;password=root;Database=visual";
            MySqlConnection mysqlcon = new MySqlConnection(constr);
            mysqlcon.Open();
            MySqlCommand mycmd = new MySqlCommand("select * from user", mysqlcon);
            MySqlDataReader reader = mycmd.ExecuteReader();
            string [,] result = new string[100,6];
            int i = 0;

            while (reader.Read())
            {
                string tempsex = null;
                 user_id = reader.GetString(reader.GetOrdinal("user_id"));
                 password = reader.GetString(reader.GetOrdinal("password"));
                 email = reader.GetString(reader.GetOrdinal("email"));
                 sex = reader.GetInt32(reader.GetOrdinal("sex"));
                 if (sex == 0)
                     tempsex = "girl";
                 else
                     tempsex = "boy";
                 team = reader.GetString(reader.GetOrdinal("team"));
                 user_name = reader.GetString(reader.GetOrdinal("user_name"));
                 register_time = reader.GetString(reader.GetOrdinal("register_time"));
                 result[i,0] = user_id;
                 result[i,1] = email;
                 result[i,2] = tempsex;
                 result[i,3] = team;
                 result[i,4] = user_name;
                 result[i,5] = register_time;
                 i++;
            }
            mysqlcon.Close();
            int x = 1;

            listView1.Columns.Clear();
            this.listView1.Columns.Add("user_id");
            this.listView1.Columns.Add("email");
            this.listView1.Columns.Add("sex");
            this.listView1.Columns.Add("team");
            this.listView1.Columns.Add("name");
            this.listView1.Columns.Add("registertime");
            
            

            ListViewItem item = null;
            foreach (string s in result)
            {
                if (x % 6 == 1)
                {
                    item = new ListViewItem();
                    item.SubItems.Clear();
                    
                    item.Text = s;
                }
                else
                    item.SubItems.Add(s);

                if (x % 6 == 0)
                {
                    listView1.Items.Add(item);
                }
                x++;
               
            }
           for (int j = 0; j< listView1.Columns.Count; j++)
           {
               listView1.Columns[j].Width = -2;
            }
           this.listView1.EndUpdate();
        }
       

      

        private void dateTimePicker1_ValueChanged(object sender, EventArgs e)
        {
            day = dateTimePicker1.Value.Year.ToString() + "-" + dateTimePicker1.Value.Month.ToString() + "-" + dateTimePicker1.Value.Day.ToString();

            this.listView1.BeginUpdate();
            this.listView1.Items.Clear();

            string user_id, work, feel, team, date;
            String constr = "server=10.63.220.3;User Id=root;password=root;Database=visual";
            MySqlConnection mysqlcon = new MySqlConnection(constr);
            mysqlcon.Open();
            string cmd = "select * from workinfo where date=\'" + day+"\'";
            MySqlCommand mycmd = new MySqlCommand(cmd, mysqlcon);
           // MessageBox.Show(cmd);
            MySqlDataReader reader = mycmd.ExecuteReader();

            string[,] result = new string[100, 5];
            int i = 0;

            while (reader.Read())
            {

                user_id = reader.GetString(reader.GetOrdinal("name"));
                work = reader.GetString(reader.GetOrdinal("work"));
                feel = reader.GetString(reader.GetOrdinal("feel"));
                team = reader.GetString(reader.GetOrdinal("team"));
                date = reader.GetString(reader.GetOrdinal("date"));

                result[i, 0] = user_id;
                result[i, 1] = work;
                result[i, 2] = feel;
                result[i, 3] = team;
                result[i, 4] = date;
                i++;
            }
            mysqlcon.Close();
            int x = 1;
            listView1.Columns.Clear();
            this.listView1.Columns.Add("name");
            this.listView1.Columns.Add("work");
            this.listView1.Columns.Add("feel");
            this.listView1.Columns.Add("team");
            this.listView1.Columns.Add("date");

            ListViewItem item = null;
            foreach (string s in result)
            {
                if (x % 5 == 1)
                {
                    item = new ListViewItem();
                    item.SubItems.Clear();

                    item.Text = s;
                }
                else
                    item.SubItems.Add(s);

                if (x % 5 == 0)
                {
                    listView1.Items.Add(item);
                }
                x++;

            }
            for (int j = 0; j < listView1.Columns.Count; j++)
            {
                listView1.Columns[j].Width = -2;
            }

            this.listView1.EndUpdate();
        }

        private void listView1_SelectedIndexChanged_1(object sender, EventArgs e)
        {

        }

   
    }
}
