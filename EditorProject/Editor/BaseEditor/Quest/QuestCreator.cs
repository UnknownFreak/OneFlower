using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using BaseEditor.Quest;
using ManagedGame;

namespace BaseEditor
{
    public partial class QuestCreator : UserControl
    {
        public event EventHandler<AddQuestEvent> addQuest = null;
        List<Objective> myObjectives;
        List<Reward> myRewards;
        public QuestCreator()
        {
            myObjectives = new List<Objective>();
            myRewards = new List<Reward>();
            InitializeComponent();
            addQuest += QuestCreator_addQuest;
        }
        public void QuestCreator_addQuest(object sender, AddQuestEvent e)
        {
            Program.mg.addQuest(e.Name, e.Description, e.ID, e.Coins,e.Objectices,e.Rewards);
        }

        #region Objectives
        private void button1_Click(object sender, EventArgs e)
        {
            ModManager mm = new ModManager();
            mm.Text = "Add Objective";
            var zm = new ObjectiveField(mm,"Add");
            zm.onAdd += addObjective;
            mm.Controls.Add(zm);
            mm.ClientSize = zm.Size;
            mm.ShowDialog(Program.main);
        }
        private void button4_Click(object sender, EventArgs e)
        {
            ModManager mm = new ModManager();
            mm.Text = "Edit Objective";
            var zm = new ObjectiveField(mm, "Edit");
            zm.onAdd += EditObjective;
            if (listBox1.SelectedIndex != -1)
            {
                zm.setEditObjective(myObjectives[listBox1.SelectedIndex]);
                mm.Controls.Add(zm);
                mm.ClientSize = zm.Size;
                mm.ShowDialog(Program.main);
            }
        }
        private void EditObjective(object sender, AddObjectiveEventArgs e)
        {
            myObjectives[listBox1.SelectedIndex] = e.Objective;
            listBox1.Items[listBox1.SelectedIndex] = e.Objective.Name;
        }
        private void addObjective(object sender, AddObjectiveEventArgs e)
        {
            myObjectives.Add(e.Objective);
            listBox1.Items.Add(e.Objective.Name);
        }
        private void button3_Click(object sender, EventArgs e)
        {
            if (listBox1.SelectedIndex != -1)
            {
                myObjectives.RemoveAt(listBox1.SelectedIndex);
                listBox1.Items.RemoveAt(listBox1.SelectedIndex);
            }
        }
        #endregion

        private void button7_Click(object sender, EventArgs e)
        {
            ModManager mm = new ModManager();
            mm.Text = "Add Reward";
            var zm = new RewardField(mm, "Add");
            zm.onAdd += addReward;
            mm.Controls.Add(zm);
            mm.ClientSize = zm.Size;
            mm.ShowDialog(Program.main);
        }
        private void addReward(object sender, AddRewardEvent e)
        {
            if (e._Reward.Name != null)
            {
                myRewards.Add(e._Reward);
                listBox2.Items.Add(e._Reward.Name);
            }
            else
                Program.messages.addErrorMessage("Could not add reward.");
        }
        private void button5_Click(object sender, EventArgs e)
        {
            ModManager mm = new ModManager();
            mm.Text = "Edit Reward";
            var zm = new RewardField(mm, "Edit");
            zm.onAdd += editReward;
            if (listBox2.SelectedIndex != -1)
            {
                zm.editReward(myRewards[listBox2.SelectedIndex]);
                mm.Controls.Add(zm);
                mm.ClientSize = zm.Size;
                mm.ShowDialog(Program.main);
            }
        }

        private void editReward(object sender, AddRewardEvent e)
        {
            myRewards[listBox2.SelectedIndex] = e._Reward;
            listBox2.Items[listBox2.SelectedIndex] = e._Reward.Name;
        }

        private void button6_Click(object sender, EventArgs e)
        {
            if (listBox2.SelectedIndex != -1)
            {
                myRewards.RemoveAt(listBox2.SelectedIndex);
                listBox2.Items.RemoveAt(listBox2.SelectedIndex);
            }
        }

        private void button9_Click(object sender, EventArgs e)
        {
            AddQuestEvent evt = new AddQuestEvent() { Objectices = myObjectives, Rewards = myRewards };
            evt.Name = textBox2.Text;
            evt.Description = textBox4.Text;
            evt.ID = (UInt32)numericUpDown1.Value;
            evt.Coins = (UInt32)numericUpDown2.Value;
            onAdd(evt);
        }
        private void onAdd(AddQuestEvent e)
        {
            if (addQuest != null)
                addQuest(this, e);
            (Parent.Parent as Form).Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Program.messages.addInfoMessage("Not implemented yet");
            //<Suggest id>
        }

        private void button8_Click(object sender, EventArgs e)
        {
            (Parent as Form).Close();
        }
    }
    public class AddQuestEvent : EventArgs
    {
        public List<Objective> Objectices { get; set; }
        public List<Reward> Rewards { get; set; }
        public String Name { get; set; }
        public UInt32 Coins { get; set; }
        public String Description { get; set; }
        public UInt32 ID { get; set; }
    }
}
