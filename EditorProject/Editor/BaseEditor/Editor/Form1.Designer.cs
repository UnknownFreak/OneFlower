namespace BaseEditor
{
    partial class MainEditorWindow
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainEditorWindow));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newModToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.windowToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.renderWindowToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.objectsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.zonesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.messagesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.worldToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addZoneToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openZoneToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.removeZoneToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.editZoneToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.objectsToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.spriterScenesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.windowToolStripMenuItem,
            this.worldToolStripMenuItem,
            this.objectsToolStripMenuItem1,
            this.spriterScenesToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1335, 24);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            this.menuStrip1.ItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler(this.menuStrip1_ItemClicked);
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newModToolStripMenuItem,
            this.loadToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.toolStripSeparator1,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // newModToolStripMenuItem
            // 
            this.newModToolStripMenuItem.Name = "newModToolStripMenuItem";
            this.newModToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.N)));
            this.newModToolStripMenuItem.Size = new System.Drawing.Size(174, 22);
            this.newModToolStripMenuItem.Text = "New Mod";
            this.newModToolStripMenuItem.Click += new System.EventHandler(this.newModToolStripMenuItem_Click);
            // 
            // loadToolStripMenuItem
            // 
            this.loadToolStripMenuItem.Name = "loadToolStripMenuItem";
            this.loadToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.loadToolStripMenuItem.Size = new System.Drawing.Size(174, 22);
            this.loadToolStripMenuItem.Text = "Open Mod";
            this.loadToolStripMenuItem.Click += new System.EventHandler(this.loadToolStripMenuItem_Click);
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(174, 22);
            this.saveToolStripMenuItem.Text = "Save Mod";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(171, 6);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(174, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // windowToolStripMenuItem
            // 
            this.windowToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.renderWindowToolStripMenuItem,
            this.objectsToolStripMenuItem,
            this.zonesToolStripMenuItem,
            this.toolStripSeparator2,
            this.messagesToolStripMenuItem});
            this.windowToolStripMenuItem.Name = "windowToolStripMenuItem";
            this.windowToolStripMenuItem.Size = new System.Drawing.Size(63, 20);
            this.windowToolStripMenuItem.Text = "Window";
            // 
            // renderWindowToolStripMenuItem
            // 
            this.renderWindowToolStripMenuItem.Name = "renderWindowToolStripMenuItem";
            this.renderWindowToolStripMenuItem.Size = new System.Drawing.Size(158, 22);
            this.renderWindowToolStripMenuItem.Text = "Render Window";
            this.renderWindowToolStripMenuItem.Click += new System.EventHandler(this.renderWindowToolStripMenuItem_Click);
            // 
            // objectsToolStripMenuItem
            // 
            this.objectsToolStripMenuItem.Name = "objectsToolStripMenuItem";
            this.objectsToolStripMenuItem.Size = new System.Drawing.Size(158, 22);
            this.objectsToolStripMenuItem.Text = "Objects";
            // 
            // zonesToolStripMenuItem
            // 
            this.zonesToolStripMenuItem.Name = "zonesToolStripMenuItem";
            this.zonesToolStripMenuItem.Size = new System.Drawing.Size(158, 22);
            this.zonesToolStripMenuItem.Text = "Zones";
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(155, 6);
            // 
            // messagesToolStripMenuItem
            // 
            this.messagesToolStripMenuItem.Name = "messagesToolStripMenuItem";
            this.messagesToolStripMenuItem.Size = new System.Drawing.Size(158, 22);
            this.messagesToolStripMenuItem.Text = "Messages";
            // 
            // worldToolStripMenuItem
            // 
            this.worldToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addZoneToolStripMenuItem,
            this.openZoneToolStripMenuItem,
            this.removeZoneToolStripMenuItem,
            this.editZoneToolStripMenuItem});
            this.worldToolStripMenuItem.Name = "worldToolStripMenuItem";
            this.worldToolStripMenuItem.Size = new System.Drawing.Size(51, 20);
            this.worldToolStripMenuItem.Text = "World";
            // 
            // addZoneToolStripMenuItem
            // 
            this.addZoneToolStripMenuItem.Name = "addZoneToolStripMenuItem";
            this.addZoneToolStripMenuItem.Size = new System.Drawing.Size(147, 22);
            this.addZoneToolStripMenuItem.Text = "Add Zone";
            // 
            // openZoneToolStripMenuItem
            // 
            this.openZoneToolStripMenuItem.Name = "openZoneToolStripMenuItem";
            this.openZoneToolStripMenuItem.Size = new System.Drawing.Size(147, 22);
            this.openZoneToolStripMenuItem.Text = "Open Zone";
            // 
            // removeZoneToolStripMenuItem
            // 
            this.removeZoneToolStripMenuItem.Name = "removeZoneToolStripMenuItem";
            this.removeZoneToolStripMenuItem.Size = new System.Drawing.Size(147, 22);
            this.removeZoneToolStripMenuItem.Text = "Remove Zone";
            // 
            // editZoneToolStripMenuItem
            // 
            this.editZoneToolStripMenuItem.Name = "editZoneToolStripMenuItem";
            this.editZoneToolStripMenuItem.Size = new System.Drawing.Size(147, 22);
            this.editZoneToolStripMenuItem.Text = "Edit Zone";
            // 
            // objectsToolStripMenuItem1
            // 
            this.objectsToolStripMenuItem1.Name = "objectsToolStripMenuItem1";
            this.objectsToolStripMenuItem1.Size = new System.Drawing.Size(59, 20);
            this.objectsToolStripMenuItem1.Text = "Objects";
            // 
            // spriterScenesToolStripMenuItem
            // 
            this.spriterScenesToolStripMenuItem.Name = "spriterScenesToolStripMenuItem";
            this.spriterScenesToolStripMenuItem.Size = new System.Drawing.Size(92, 20);
            this.spriterScenesToolStripMenuItem.Text = "Spriter Scenes";
            this.spriterScenesToolStripMenuItem.Click += new System.EventHandler(this.spriterScenesToolStripMenuItem_Click);
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.helpToolStripMenuItem.Text = "Help";
            // 
            // MainEditorWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1335, 1007);
            this.Controls.Add(this.menuStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.IsMdiContainer = true;
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainEditorWindow";
            this.Text = "Editor <No file opened>";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.LocationChanged += new System.EventHandler(this.MainEditorWindow_LocationChanged);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newModToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem windowToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem renderWindowToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem objectsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem zonesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem worldToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addZoneToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openZoneToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem removeZoneToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem editZoneToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem objectsToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem messagesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem spriterScenesToolStripMenuItem;


    }
}