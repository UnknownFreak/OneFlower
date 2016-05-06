using BaseEditor.Editor.MouseHook;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BaseEditor
{
    public partial class MainEditorWindow : Form
    {
        public MainEditorWindow()
        {
            MouseHook.Start();
            MouseHook.MouseActionR += new EventHandler(MouseEvent);
            InitializeComponent();
            //Could be better organized, but this will have to do for now.
            Program.mg = new ManagedGame.ManagedGame();

            Program.messageWindow = new DragNDropWindow();
            Program.messages = new MessageWindow();
            Program.messages.Dock = DockStyle.Fill;
            Program.messageWindow.Size = BaseEditor.Program.messages.Size;
            Program.messageWindow.addOnPanel.Dock = DockStyle.Fill;
            Program.messageWindow.addOnPanel.Controls.Add(BaseEditor.Program.messages);
            Program.messageWindow.Show(this);
            Program.messageWindow.Text = "Messages";

            Program.renderWindow = new DragNDropWindow();
            Program.renderControls = new RenderAreaControls();
            Program.renderWindow.addComponent(BaseEditor.Program.renderControls);
            Program.renderWindow.Size = new Size(800, 667);
            Program.renderWindow.Show(this);
            Program.renderWindow.Text = "C++ Window <Render Window>";


            Program.mg.setUpWindows(getRenderWindowHandle());

            Program.itemCreator = new DragNDropWindow();
            Program.creatorField = new ItemCreator();
            Program.creatorField.Dock = DockStyle.Fill;
            Program.itemCreator.ClientSize = new Size(BaseEditor.Program.creatorField.ClientSize.Width + 4, BaseEditor.Program.creatorField.ClientSize.Height + 24);
            Program.itemCreator.addOnPanel.Dock = DockStyle.Fill;
            Program.itemCreator.addOnPanel.Controls.Add(BaseEditor.Program.creatorField);
            Program.itemCreator.Show(this);
            Program.itemCreator.Hide();


            Program.questCreator = new DragNDropWindow();
            Program.questCreatorField = new QuestCreator();
            Program.questCreatorField.Dock = DockStyle.Fill;
            Program.questCreator.ClientSize = BaseEditor.Program.questCreatorField.Size;
            Program.questCreator.ClientSize = new Size(BaseEditor.Program.questCreator.ClientSize.Width + 4, BaseEditor.Program.questCreator.ClientSize.Height + 35);
            Program.questCreator.addOnPanel.Controls.Add(BaseEditor.Program.questCreatorField);
            Program.questCreator.Show(this);
            Program.questCreator.Hide();


            Program.prefabCreator = new DragNDropWindow();
            Program.prefabField = new PrefabCreator();
            Program.prefabField.Dock = DockStyle.Fill;
            Program.prefabCreator.ClientSize = BaseEditor.Program.prefabField.Size;
            Program.prefabCreator.ClientSize = new Size(BaseEditor.Program.prefabCreator.ClientSize.Width + 4, BaseEditor.Program.prefabCreator.ClientSize.Height + 35);
            Program.prefabCreator.addOnPanel.Controls.Add(BaseEditor.Program.prefabField);
            Program.prefabCreator.Show(this);
            Program.prefabCreator.Hide();


            Program.objectViewWindow = new DragNDropWindow();
            Program.objectViewWindow.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Sizable;
            Program.objectView = new ObjectArea();
            Program.objectView.Dock = DockStyle.Fill;
            Program.objectViewWindow.Size = BaseEditor.Program.objectView.Size;
            Program.objectViewWindow.addOnPanel.Dock = DockStyle.Fill;
            Program.objectViewWindow.addOnPanel.Controls.Add(BaseEditor.Program.objectView);
            Program.objectViewWindow.Show(this);
            Program.objectViewWindow.Text ="Object List";


            Program.zoneViewWindow = new DragNDropWindow();
            Program.zoneViewWindow.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Sizable;
            Program.zoneView = new zonefield();
            Program.zoneView.Dock = DockStyle.Fill;
            Program.zoneViewWindow.Size = BaseEditor.Program.zoneView.Size;
            Program.zoneViewWindow.addOnPanel.Dock = DockStyle.Fill;
            Program.zoneViewWindow.addOnPanel.Controls.Add(BaseEditor.Program.zoneView);
            Program.zoneViewWindow.Show(this);
            Program.zoneViewWindow.Text = "Zone view";

            Program.spriterSceneWindow = new DragNDropWindow();
            Program.spriterScene = new SpriterScene.SpriterScene();
            Program.spriterScene.Dock = DockStyle.Fill;
            Program.spriterSceneWindow.Size = new Size(BaseEditor.Program.spriterScene.ClientSize.Width + 10, BaseEditor.Program.spriterScene.ClientSize.Height + 60);
            Program.spriterSceneWindow.addOnPanel.Dock = DockStyle.Fill;
            Program.spriterSceneWindow.addOnPanel.Controls.Add(BaseEditor.Program.spriterScene);
            Program.spriterSceneWindow.Show(this);
            Program.spriterSceneWindow.Hide();
            Program.spriterSceneWindow.Text = "Manage Spriter Scenes";
            //Program.spriterScene.onListChange += Program.prefabField.renderPanel.spriterScene_onListChange;

            Program.messageWindow.Left = Left;
            Program.messageWindow.Top = Bottom - BaseEditor.Program.messageWindow.Size.Height;

            Program.renderWindow.Left = Left + BaseEditor.Program.objectViewWindow.Size.Width;
            Program.renderWindow.Top = Top + 55;

            Program.zoneViewWindow.Left = Left + BaseEditor.Program.objectViewWindow.Size.Width;
            Program.zoneViewWindow.Top = Bottom - BaseEditor.Program.zoneViewWindow.Size.Height;

            Program.objectViewWindow.Left = Left;
            Program.objectViewWindow.Top = Top + 55;

            Program.mainDrawThread = new Thread(BaseEditor.Program.mg.ManagedWindowLoop);
            Program.mainDrawThread.Start();
            Program.zoneView.init();
        }

        private void MouseEvent(object sender, EventArgs e)
        {
            Rectangle r = Program.renderWindow.addOnPanel.RectangleToScreen(Program.renderWindow.addOnPanel.ClientRectangle);
            Point Mpos = MousePosition;
            bool inside = r.Contains(Mpos);
            if (inside)
            {
                if (Program.mg.getRightClickedObject())
                    Console.WriteLine("Yay! We has selected");
                else
                    Console.WriteLine("Daww! We has no selected");

            }
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BaseEditor.Program.mg.save();
        }

        private void renderWindowToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (BaseEditor.Program.renderWindow.Visible != true)
                BaseEditor.Program.renderWindow.Show(this);
        }
        public IntPtr getRenderWindowHandle()
        {
            return BaseEditor.Program.renderControls.renderPanel.Handle;
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            BaseEditor.Program.mg.ManagedQuit();
            BaseEditor.Program.mainDrawThread.Join();

            BaseEditor.Program.renderWindow.Dispose();
            BaseEditor.Program.itemCreator.Dispose();
            BaseEditor.Program.messageWindow.Dispose();
            BaseEditor.Program.objectViewWindow.Dispose();
            MouseHook.stop();
        }

        private void MainEditorWindow_LocationChanged(object sender, EventArgs e)
        {
            if (BaseEditor.Program.renderWindow != null)
            {
                BaseEditor.Program.renderWindow.Left = Left + BaseEditor.Program.objectViewWindow.Size.Width;
                BaseEditor.Program.renderWindow.Top = Top + 55;
            }
            if (BaseEditor.Program.messageWindow != null)
            {
                BaseEditor.Program.messageWindow.Left = Left;
                BaseEditor.Program.messageWindow.Top = Bottom - BaseEditor.Program.messageWindow.Size.Height;
            }
            if(BaseEditor.Program.zoneViewWindow != null)
            {
                BaseEditor.Program.zoneViewWindow.Left = Left + BaseEditor.Program.objectViewWindow.Size.Width;
                BaseEditor.Program.zoneViewWindow.Top = Bottom - BaseEditor.Program.zoneViewWindow.Size.Height;
            }
            if(BaseEditor.Program.objectViewWindow != null)
            {
                BaseEditor.Program.objectViewWindow.Left = Left;
                BaseEditor.Program.objectViewWindow.Top = Top + 55;
            }
        }

        private void newModToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ModManager mm = new ModManager();
            mm.Text = "New Mod";
            mm.Controls.Add(new AddMod(this));
            mm.ShowDialog(this);
        }

        private void loadToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog opf = new OpenFileDialog();
            opf.InitialDirectory = Directory.GetCurrentDirectory();
            opf.Filter = "GameFile (*.main .*mod)|*.main;*.mod|MAIN (*.main)|*.main|MOD (*.mod)|*.mod";
            opf.Multiselect = false;
            opf.ShowDialog(this);
            if (opf.FileName.EndsWith(".main") || opf.FileName.EndsWith(".mod"))
            {
                String myLoadedMod = Program.mg.loadMod(opf.SafeFileName);
                if (myLoadedMod != "<Not Set>")
                {
                    Text = "Editor  " + myLoadedMod;
                    Program.zoneView.init();
                    Program.objectView.init();
                    Program.spriterScene.init();
                }
            }
        }

        public void loadMod(String str)
        {
            String myLoadedMod = Program.mg.loadMod(str);
            if (myLoadedMod != "<Not Set>")
            {
                Text = "Editor  " + myLoadedMod;
                Program.zoneView.init();
                Program.objectView.init();
                Program.spriterScene.init();
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void spriterScenesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Program.spriterSceneWindow.Show();
        }

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }
    }
}
