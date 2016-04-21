using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BaseEditor.Quest
{
    public partial class RewardField : UserControl
    {
        public event EventHandler<OnModifyRewardEvent> onModify = null;
        private _Reward myReward;
        public RewardField()
        {
            InitializeComponent();
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
                onModifyFnc(new OnModifyRewardEvent() { Text = myReward.Name, index = 1 });
                onModifyFnc(new OnModifyRewardEvent() { Text = "(" + myReward.Item.Item1 + "," + myReward.Item.Item2 + ")", index = 0 });

            }
        }
        private void onModifyFnc(OnModifyRewardEvent args)
        {
            if (onModify != null)
                onModify(this, args);
        }
        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            myReward.Count = (UInt32)numericUpDown1.Value;
            onModifyFnc(new OnModifyRewardEvent() { Text = myReward.Count.ToString(), index = 2 });
        }
        public void setUpFields(_Reward rwd)
        {
            myReward = rwd;
            if (rwd.Item != null)
                textBox1.Text = rwd.Name +" (" + rwd.Item.Item1 + "," + rwd.Item.Item2 + ")";
            numericUpDown1.Value = (UInt32)rwd.Count;
        }
    }
    public class OnModifyRewardEvent : EventArgs
    {
        public String Text { get; set; }
        public int index { get; set; }
    }
    public class _Reward
    {
        public ManagedGame.Reward Reward { get; set; }
        public Tuple<String, UInt32> Item { get { return this.Reward.Item; } set { this.Reward.Item = value;} }
        public String Name { get { return this.Reward.Name; } set { this.Reward.Name = value; } }
        public UInt32 Count { get { return System.Convert.ToUInt32(this.Reward.Count); } set { this.Reward.Count = value; } }
    }
}
