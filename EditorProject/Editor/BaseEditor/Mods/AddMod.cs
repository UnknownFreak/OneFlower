using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace BaseEditor
{
    public partial class AddMod : UserControl
    {
        Form pForm;
        public AddMod(Form pForm)
        {
            this.pForm = pForm;
            InitializeComponent();
            checkedListBox1.Size = checkedListBox1.MaximumSize;
            String path = Path.GetDirectoryName(Application.ExecutablePath);
            String [] mods = System.IO.Directory.GetFiles(path, "*.main");
            foreach (String m in mods)
                checkedListBox1.Items.Add(m.Remove(0, path.Count()+1));
            mods = System.IO.Directory.GetFiles(path, "*.mod");
            foreach (String m in mods)
                checkedListBox1.Items.Add(m.Remove(0, path.Count()+1));
        }

        private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(checkedListBox1.SelectedItem != null)
                Program.mg.getDependencies(checkedListBox1.SelectedItem.ToString(),listBox1);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            List<String> myList = new List<string>();
            if(textBox1.Text.Count() != 0)
            {
                foreach (String str in checkedListBox1.CheckedItems)
                {
                    myList.Add(str);
                }
                String myLoadedMod = Program.mg.newMod(textBox1.Text,myList);
                pForm.Text = "Editor  " + myLoadedMod;
                Program.objectView.init();
                Program.zoneView.init();
                (this.Parent as Form).Close();
            }

        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form q = this.Parent as Form;
            q.Close();
        }
    }
}
