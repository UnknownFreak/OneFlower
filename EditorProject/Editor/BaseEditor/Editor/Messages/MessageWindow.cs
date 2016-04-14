using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BaseEditor
{
    public partial class MessageWindow : UserControl
    {
        public MessageWindow()
        {
            InitializeComponent();
            BaseEditor.Program.mg.setMessageWindow(listView1);
        }

        public void addErrorMessage(String message)
        {
            System.Windows.Forms.ListViewItem.ListViewSubItem sub = new ListViewItem.ListViewSubItem();
            sub.Text = message;

            ListViewItem li = new ListViewItem();
            li.BackColor = Color.LightCoral;
            li.Text = "Error";
            li.ImageIndex = 0;
            li.SubItems.Add(sub);
            listView1.Items.Add(li);
        }
        public void addInfoMessage(String message)
        {
            System.Windows.Forms.ListViewItem.ListViewSubItem sub = new ListViewItem.ListViewSubItem();
            sub.Text = message;
            ListViewItem li = new ListViewItem();
            li.BackColor = Color.LightGreen;
            li.Text = "Info";
            li.ImageIndex = 1;
            li.SubItems.Add(sub);
            listView1.Items.Add(li);
        }
        public void addMessage(Color c, String message)
        {

            System.Windows.Forms.ListViewItem.ListViewSubItem sub = new ListViewItem.ListViewSubItem();
            sub.Text = message;
            ListViewItem li = new ListViewItem();
            li.BackColor = c;
            li.ImageIndex = 1;
            li.Text = "Info";
            li.SubItems.Add(sub);
            listView1.Items.Add(li);
        }
        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {
        }
    }
}
