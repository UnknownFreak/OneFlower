using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ManagedGame;

namespace BaseEditor.Quest
{
    public partial class RewardField : UserControl
    {
        public event EventHandler<AddRewardEvent> onAdd = null;
        Reward myReward;
        public RewardField(Form parent, String mode)
        {
            myReward = new Reward() { Count = 1 };
            InitializeComponent();
            parent.AcceptButton = Add;
            parent.CancelButton = Cancel;
            Add.Text = mode;
        }

        private void Set_Click(object sender, EventArgs e)
        {
            Selector s = new Selector("Items");
            s.onSelectEvent +=s_onSelectEvent;
            s.ShowDialog(this);
        }

        private void s_onSelectEvent(object sender, SelectedItemEvent e)
        {
            if (e.item != null)
            {
                String name = e.item.SubItems[3].Text;
                String _iname = e.item.SubItems[0].Text;
                uint id = Convert.ToUInt32(e.item.SubItems[1].Text);
                myReward.Item = new Tuple<string, uint>(name, id);
                myReward.Name = _iname;
                textBox1.Text = _iname + " (" + name + "," + id + ")";
            }
        }

        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            myReward.Count = (UInt32)numericUpDown1.Value;
        }

        private void Add_Click(object sender, EventArgs e)
        {
            AddRewardEvent evt = new AddRewardEvent();
            evt._Reward = myReward;
            if (onAdd != null)
                onAdd(this, evt);
            (Parent as Form).Close();
        }

        private void Cancel_Click(object sender, EventArgs e)
        {
            (Parent as Form).Close();
        }


        internal void editReward(Reward reward)
        {
            numericUpDown1.Value = (UInt32)reward.Count;
            textBox1.Text = reward.Name + " (" + reward.Item.Item1 + "," + reward.Item.Item2 + ")";
            myReward = reward;
        }
    }
    public class AddRewardEvent : EventArgs
    {
        public Reward _Reward{ get; set; }
    }
    /*public class Reward
    {
        public Tuple<String, UInt32> Item { get; set; }
        public String Name { get; set; }
        public UInt32 Count { get; set; }
    }*/
}
