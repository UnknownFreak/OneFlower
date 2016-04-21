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
            BaseEditor.Program.mg = new ManagedGame.ManagedGame();

            BaseEditor.Program.messageWindow = new DragNDropWindow();
            BaseEditor.Program.messages = new MessageWindow();
            BaseEditor.Program.messages.Dock = DockStyle.Fill;
            BaseEditor.Program.messageWindow.Size = BaseEditor.Program.messages.Size;
            BaseEditor.Program.messageWindow.addOnPanel.Dock = DockStyle.Fill;
            BaseEditor.Program.messageWindow.addOnPanel.Controls.Add(BaseEditor.Program.messages);
            BaseEditor.Program.messageWindow.Show(this);
            BaseEditor.Program.messageWindow.Text = "Messages";

            BaseEditor.Program.renderWindow = new DragNDropWindow();
            BaseEditor.Program.renderControls = new RenderAreaControls();
            BaseEditor.Program.renderWindow.addComponent(BaseEditor.Program.renderControls);
            BaseEditor.Program.renderWindow.Size = new Size(800, 667);
            BaseEditor.Program.renderWindow.Show(this);
            BaseEditor.Program.renderWindow.Text = "C++ Window <Render Window>";


            BaseEditor.Program.mg.setUpWindows(getRenderWindowHandle());

            BaseEditor.Program.itemCreator = new DragNDropWindow();
            BaseEditor.Program.creatorField = new ItemCreator();
            BaseEditor.Program.creatorField.Dock = DockStyle.Fill;
            BaseEditor.Program.itemCreator.ClientSize = new Size(BaseEditor.Program.creatorField.ClientSize.Width + 4, BaseEditor.Program.creatorField.ClientSize.Height + 24);
            BaseEditor.Program.itemCreator.addOnPanel.Dock = DockStyle.Fill;
            BaseEditor.Program.itemCreator.addOnPanel.Controls.Add(BaseEditor.Program.creatorField);
            BaseEditor.Program.itemCreator.Show(this);
            BaseEditor.Program.itemCreator.Hide();


            BaseEditor.Program.questCreator = new DragNDropWindow();
            BaseEditor.Program.questCreatorField = new QuestCreator();
            BaseEditor.Program.questCreatorField.Dock = DockStyle.Fill;
            BaseEditor.Program.questCreator.ClientSize = BaseEditor.Program.questCreatorField.Size;
            BaseEditor.Program.questCreator.ClientSize = new Size(BaseEditor.Program.questCreator.ClientSize.Width + 4, BaseEditor.Program.questCreator.ClientSize.Height + 35);
            BaseEditor.Program.questCreator.addOnPanel.Controls.Add(BaseEditor.Program.questCreatorField);
            BaseEditor.Program.questCreator.Show(this);
            BaseEditor.Program.questCreator.Hide();


            BaseEditor.Program.prefabCreator = new DragNDropWindow();
            BaseEditor.Program.prefabField = new PrefabCreator();
            BaseEditor.Program.prefabField.Dock = DockStyle.Fill;
            BaseEditor.Program.prefabCreator.ClientSize = BaseEditor.Program.prefabField.Size;
            BaseEditor.Program.prefabCreator.ClientSize = new Size(BaseEditor.Program.prefabCreator.ClientSize.Width + 4, BaseEditor.Program.prefabCreator.ClientSize.Height + 35);
            BaseEditor.Program.prefabCreator.addOnPanel.Controls.Add(BaseEditor.Program.prefabField);
            BaseEditor.Program.prefabCreator.Show(this);
            BaseEditor.Program.prefabCreator.Hide();


            BaseEditor.Program.objectViewWindow = new DragNDropWindow();
            BaseEditor.Program.objectViewWindow.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Sizable;
            BaseEditor.Program.objectView = new ObjectArea();
            BaseEditor.Program.objectView.Dock = DockStyle.Fill;
            BaseEditor.Program.objectViewWindow.Size = BaseEditor.Program.objectView.Size;
            BaseEditor.Program.objectViewWindow.addOnPanel.Dock = DockStyle.Fill;
            BaseEditor.Program.objectViewWindow.addOnPanel.Controls.Add(BaseEditor.Program.objectView);
            BaseEditor.Program.objectViewWindow.Show(this);
            BaseEditor.Program.objectViewWindow.Text ="Object List";


            BaseEditor.Program.zoneViewWindow = new DragNDropWindow();
            BaseEditor.Program.zoneViewWindow.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Sizable;
            BaseEditor.Program.zoneView = new zonefield();
            BaseEditor.Program.zoneView.Dock = DockStyle.Fill;
            BaseEditor.Program.zoneViewWindow.Size = BaseEditor.Program.zoneView.Size;
            BaseEditor.Program.zoneViewWindow.addOnPanel.Dock = DockStyle.Fill;
            BaseEditor.Program.zoneViewWindow.addOnPanel.Controls.Add(BaseEditor.Program.zoneView);
            BaseEditor.Program.zoneViewWindow.Show(this);
            BaseEditor.Program.zoneViewWindow.Text = "Zone view";

            BaseEditor.Program.messageWindow.Left = Left;
            BaseEditor.Program.messageWindow.Top = Bottom - BaseEditor.Program.messageWindow.Size.Height;

            BaseEditor.Program.renderWindow.Left = Left + BaseEditor.Program.objectViewWindow.Size.Width;
            BaseEditor.Program.renderWindow.Top = Top + 55;

            BaseEditor.Program.zoneViewWindow.Left = Left + BaseEditor.Program.objectViewWindow.Size.Width;
            BaseEditor.Program.zoneViewWindow.Top = Bottom - BaseEditor.Program.zoneViewWindow.Size.Height;

            BaseEditor.Program.objectViewWindow.Left = Left;
            BaseEditor.Program.objectViewWindow.Top = Top + 55;

            BaseEditor.Program.mainDrawThread = new Thread(BaseEditor.Program.mg.ManagedWindowLoop);
            BaseEditor.Program.mainDrawThread.Start();
            BaseEditor.Program.zoneView.init();
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
            opf.InitialDirectory = Path.GetDirectoryName(Application.ExecutablePath);
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
                }
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
