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
            objectiveField1.onModify += objectiveField1_onAdd;
            rewardField1.onModify += rewardField1_onModify;
        }

        void rewardField1_onModify(object sender, OnModifyRewardEvent e)
        {
            if (RewardList.SelectedItems.Count != 0)
            {
                RewardList.SelectedItems[0].SubItems[e.index].Text = e.Text;
            }
        }

        void objectiveField1_onAdd(object sender, OnModifyObjectiveEventArgs e)
        {
            if(ObjectiveList.SelectedItems.Count != 0)
            {
                ObjectiveList.SelectedItems[0].SubItems[e.index].Text = e.Text;
            }
        }
        public void QuestCreator_addQuest(object sender, AddQuestEvent e)
        {
            Program.mg.addQuest(e.Name, e.Description, e.ID, e.Coins,e.Objectices,e.Rewards);
        }

        #region Objectives
        private void button1_Click(object sender, EventArgs e)
        {
            addObjective(this, new AddObjectiveEventArgs());
        }
        private void addObjective(object sender, AddObjectiveEventArgs e)
        {
            myObjectives.Add(e.Objective);
            String[] list = { e.Objective.Name, e.Objective.Type, e.Objective.IsBonusObjective.ToString() };
            ObjectiveList.Items.Add(new ListViewItem(list,-1));
        }
        private void button3_Click(object sender, EventArgs e)
        {
            if (ObjectiveList.SelectedItems.Count != 0)
            {
                myObjectives.RemoveAt(ObjectiveList.SelectedIndices[0]);
                ObjectiveList.Items.RemoveAt(ObjectiveList.SelectedIndices[0]);
            }
        }
        #endregion

        private void button7_Click(object sender, EventArgs e)
        {
            addReward(this, new AddRewardEvent());
        }
        private void addReward(object sender, AddRewardEvent e)
        {
            myRewards.Add(e.Reward);
            String[] list = { "("+e.Reward.Item.Item1+","+e.Reward.Item.Item2+")", e.Reward.Name, e.Reward.Count.ToString()};
            RewardList.Items.Add(new ListViewItem(list, -1));
        }
        private void button6_Click(object sender, EventArgs e)
        {
            if (RewardList.SelectedItems.Count != 0)
            {
                myRewards.RemoveAt(RewardList.SelectedIndices[0]);
                RewardList.Items.RemoveAt(RewardList.SelectedIndices[0]);
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
            (Parent.Parent as Form).Close();
        }

        private void ObjectiveList_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (ObjectiveList.SelectedItems.Count != 0)
            {
                objectiveField1.Enabled = true;
                objectiveField1.setEditObjective(new _Objective() { obj = myObjectives[ObjectiveList.SelectedIndices[0]] });
            }
            else
                objectiveField1.Enabled = false;
        }

        private void RewardList_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (RewardList.SelectedItems.Count != 0)
            {
                rewardField1.Enabled = true;
                rewardField1.setUpFields(new _Reward() { Reward = myRewards[RewardList.SelectedIndices[0]] });
            }
            else
                rewardField1.Enabled = false;
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
    public class AddObjectiveEventArgs : EventArgs
    {
        public AddObjectiveEventArgs()
        {
            Objective = new Objective { Count = 1, Description = "", DestinationZone = new Tuple<string,uint>("None",0),
             IsBonusObjective = false, Name = "New Objective", Target = new Tuple<string,uint> ("None",0), TargetDestination = 
             new Tuple<string,uint>("None",0), Type = "Excort", TypeIndex = 0};
        }
        public Objective Objective { get; set; }
    }
    public class AddRewardEvent : EventArgs
    {
        public AddRewardEvent()
        {
            Reward = new Reward { Count = 1, Item = new Tuple<string, uint>("None", 0), Name = "None" };
        }
        public Reward Reward { get; set; }
    }
}
