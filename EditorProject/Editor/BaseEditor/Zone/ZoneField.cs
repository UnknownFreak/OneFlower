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
    public partial class zonefield : UserControl
    {
        public zonefield()
        {
            InitializeComponent();
        }

        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (zoneView.SelectedItems.Count != 0)
            {
                String first = zoneView.SelectedItems[0].Text;
                String second = zoneView.SelectedItems[0].SubItems[1].Text;
                BaseEditor.Program.mg.loadZone(first, System.Convert.ToUInt32(second), listView2);
            }
        }
        public void init()
        {
            Program.mg.setUpZonesList(zoneView);
            listView2.Items.Clear();
        }

        private void addToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if(Program.mg.isModLoaded())
            {
                ModManager mm = new ModManager();
                mm.Text = "Add Zone";
                var zm = new ZoneManager("Add");
                mm.Controls.Add(zm);
                mm.ClientSize = zm.Size;
                mm.ShowDialog(Program.main);
            }
            else
            {
                Program.messages.addErrorMessage("No Mod Loaded!");
            }
        }

        private void editToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (Program.mg.isModLoaded())
            {
                ModManager mm = new ModManager();
                mm.Text = "Edit Zone";
                var zm = new ZoneManager("Edit");
                mm.Controls.Add(zm);
                mm.ClientSize = zm.Size;
                mm.ShowDialog(Program.main);
            }
            else
            {
                Program.messages.addErrorMessage("No Mod Loaded!");
            }
        }

        private void zoneView_MouseUp(object sender, MouseEventArgs e)
        {
            if(e.Button == MouseButtons.Right)
            {
                Console.WriteLine("Right btn pressed");
            }
        }
    }
}
