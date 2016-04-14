using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BaseEditor.Quest
{
    public partial class Selector : Form
    {
        public event EventHandler<SelectedItemEvent> onSelectEvent = null;
        public Selector(String mode)
        {
            InitializeComponent();
            if (mode == "Zone")
                Program.mg.setUpDetailedListZone(listView1);
            else if (mode == "ZoneObj")
                ;
            else
                Program.mg.setUpDetailedList(mode, mode, listView1);
        }

        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void buttonSelect_Click(object sender, EventArgs e)
        {
            SelectedItemEvent evt = new SelectedItemEvent();
            if(listView1.SelectedItems.Count != 0)
                evt.item = listView1.SelectedItems[0];
            onSelect(evt);
            this.Close();
        }
        private void onSelect(SelectedItemEvent e)
        {
            if (onSelectEvent != null)
                onSelectEvent(this, e);
        }
        private void buttonAbort_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
    public class SelectedItemEvent : EventArgs
    {
        public ListViewItem item { get; set; }
    }
}
