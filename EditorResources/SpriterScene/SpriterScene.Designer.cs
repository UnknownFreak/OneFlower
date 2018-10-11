namespace BaseEditor.SpriterScene
{
    partial class SpriterScene
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.sceneFilesList = new System.Windows.Forms.ListView();
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.panel3 = new System.Windows.Forms.Panel();
            this.button1 = new System.Windows.Forms.Button();
            this.panel4 = new System.Windows.Forms.Panel();
            this.rotated = new System.Windows.Forms.CheckBox();
            this.height = new System.Windows.Forms.NumericUpDown();
            this.label9 = new System.Windows.Forms.Label();
            this.width = new System.Windows.Forms.NumericUpDown();
            this.label10 = new System.Windows.Forms.Label();
            this.yPos = new System.Windows.Forms.NumericUpDown();
            this.label6 = new System.Windows.Forms.Label();
            this.xPos = new System.Windows.Forms.NumericUpDown();
            this.label5 = new System.Windows.Forms.Label();
            this.pointName = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.textureMapPoints = new System.Windows.Forms.ListView();
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader4 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader5 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader6 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.TextureMap = new System.Windows.Forms.ListBox();
            this.removeTextureMap = new System.Windows.Forms.Button();
            this.addTextureMap = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.removeSpriterSceneFile = new System.Windows.Forms.Button();
            this.addSpriterSceneFile = new System.Windows.Forms.Button();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.panel1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.panel3.SuspendLayout();
            this.panel4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.height)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.width)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.yPos)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.xPos)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(11, 8);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(95, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Spriter Scene Files";
            // 
            // sceneFilesList
            // 
            this.sceneFilesList.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1});
            this.sceneFilesList.FullRowSelect = true;
            this.sceneFilesList.GridLines = true;
            this.sceneFilesList.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
            this.sceneFilesList.HideSelection = false;
            this.sceneFilesList.LabelWrap = false;
            this.sceneFilesList.Location = new System.Drawing.Point(14, 24);
            this.sceneFilesList.MultiSelect = false;
            this.sceneFilesList.Name = "sceneFilesList";
            this.sceneFilesList.Size = new System.Drawing.Size(418, 120);
            this.sceneFilesList.TabIndex = 1;
            this.sceneFilesList.UseCompatibleStateImageBehavior = false;
            this.sceneFilesList.View = System.Windows.Forms.View.Details;
            this.sceneFilesList.SelectedIndexChanged += new System.EventHandler(this.sceneFilesList_SelectedIndexChanged);
            // 
            // columnHeader1
            // 
            this.columnHeader1.Text = "File Name";
            this.columnHeader1.Width = 319;
            // 
            // panel1
            // 
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Controls.Add(this.panel2);
            this.panel1.Controls.Add(this.removeSpriterSceneFile);
            this.panel1.Controls.Add(this.addSpriterSceneFile);
            this.panel1.Controls.Add(this.sceneFilesList);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Location = new System.Drawing.Point(3, 3);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(469, 629);
            this.panel1.TabIndex = 2;
            // 
            // panel2
            // 
            this.panel2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel2.Controls.Add(this.panel3);
            this.panel2.Controls.Add(this.TextureMap);
            this.panel2.Controls.Add(this.removeTextureMap);
            this.panel2.Controls.Add(this.addTextureMap);
            this.panel2.Controls.Add(this.label2);
            this.panel2.Location = new System.Drawing.Point(14, 150);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(418, 464);
            this.panel2.TabIndex = 8;
            // 
            // panel3
            // 
            this.panel3.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel3.Controls.Add(this.button1);
            this.panel3.Controls.Add(this.panel4);
            this.panel3.Controls.Add(this.label3);
            this.panel3.Controls.Add(this.textureMapPoints);
            this.panel3.Location = new System.Drawing.Point(13, 121);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(377, 328);
            this.panel3.TabIndex = 12;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(187, 138);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(174, 23);
            this.button1.TabIndex = 15;
            this.button1.Text = "Set Texture Map Points From File";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // panel4
            // 
            this.panel4.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel4.Controls.Add(this.rotated);
            this.panel4.Controls.Add(this.height);
            this.panel4.Controls.Add(this.label9);
            this.panel4.Controls.Add(this.width);
            this.panel4.Controls.Add(this.label10);
            this.panel4.Controls.Add(this.yPos);
            this.panel4.Controls.Add(this.label6);
            this.panel4.Controls.Add(this.xPos);
            this.panel4.Controls.Add(this.label5);
            this.panel4.Controls.Add(this.pointName);
            this.panel4.Controls.Add(this.label4);
            this.panel4.Location = new System.Drawing.Point(15, 167);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(346, 145);
            this.panel4.TabIndex = 14;
            // 
            // rotated
            // 
            this.rotated.AutoSize = true;
            this.rotated.Location = new System.Drawing.Point(15, 100);
            this.rotated.Name = "rotated";
            this.rotated.Size = new System.Drawing.Size(64, 17);
            this.rotated.TabIndex = 23;
            this.rotated.Text = "Rotated";
            this.rotated.UseVisualStyleBackColor = true;
            this.rotated.CheckedChanged += new System.EventHandler(this.rotated_CheckedChanged);
            // 
            // height
            // 
            this.height.Location = new System.Drawing.Point(261, 74);
            this.height.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.height.Name = "height";
            this.height.Size = new System.Drawing.Size(76, 20);
            this.height.TabIndex = 22;
            this.height.ValueChanged += new System.EventHandler(this.height_ValueChanged);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(258, 58);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(38, 13);
            this.label9.TabIndex = 21;
            this.label9.Text = "Height";
            // 
            // width
            // 
            this.width.Location = new System.Drawing.Point(179, 74);
            this.width.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.width.Name = "width";
            this.width.Size = new System.Drawing.Size(76, 20);
            this.width.TabIndex = 20;
            this.width.ValueChanged += new System.EventHandler(this.width_ValueChanged);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(176, 58);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(35, 13);
            this.label10.TabIndex = 19;
            this.label10.Text = "Width";
            // 
            // yPos
            // 
            this.yPos.Location = new System.Drawing.Point(97, 74);
            this.yPos.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.yPos.Name = "yPos";
            this.yPos.Size = new System.Drawing.Size(76, 20);
            this.yPos.TabIndex = 18;
            this.yPos.ValueChanged += new System.EventHandler(this.yPos_ValueChanged);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(94, 58);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(14, 13);
            this.label6.TabIndex = 17;
            this.label6.Text = "Y";
            // 
            // xPos
            // 
            this.xPos.Location = new System.Drawing.Point(15, 74);
            this.xPos.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.xPos.Name = "xPos";
            this.xPos.Size = new System.Drawing.Size(76, 20);
            this.xPos.TabIndex = 16;
            this.xPos.ValueChanged += new System.EventHandler(this.xPos_ValueChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 58);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(14, 13);
            this.label5.TabIndex = 15;
            this.label5.Text = "X";
            // 
            // pointName
            // 
            this.pointName.Location = new System.Drawing.Point(15, 25);
            this.pointName.Name = "pointName";
            this.pointName.ReadOnly = true;
            this.pointName.Size = new System.Drawing.Size(158, 20);
            this.pointName.TabIndex = 14;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 9);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(35, 13);
            this.label4.TabIndex = 13;
            this.label4.Text = "Name";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(36, 13);
            this.label3.TabIndex = 13;
            this.label3.Text = "Points";
            // 
            // textureMapPoints
            // 
            this.textureMapPoints.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader2,
            this.columnHeader3,
            this.columnHeader4,
            this.columnHeader5,
            this.columnHeader6});
            this.textureMapPoints.FullRowSelect = true;
            this.textureMapPoints.GridLines = true;
            this.textureMapPoints.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
            this.textureMapPoints.LabelWrap = false;
            this.textureMapPoints.Location = new System.Drawing.Point(15, 16);
            this.textureMapPoints.MultiSelect = false;
            this.textureMapPoints.Name = "textureMapPoints";
            this.textureMapPoints.Size = new System.Drawing.Size(346, 116);
            this.textureMapPoints.TabIndex = 9;
            this.textureMapPoints.UseCompatibleStateImageBehavior = false;
            this.textureMapPoints.View = System.Windows.Forms.View.Details;
            this.textureMapPoints.SelectedIndexChanged += new System.EventHandler(this.textureMapPoints_SelectedIndexChanged);
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = "Name";
            this.columnHeader2.Width = 153;
            // 
            // columnHeader3
            // 
            this.columnHeader3.Text = "X";
            this.columnHeader3.Width = 42;
            // 
            // columnHeader4
            // 
            this.columnHeader4.Text = "Y";
            this.columnHeader4.Width = 42;
            // 
            // columnHeader5
            // 
            this.columnHeader5.Text = "Width";
            this.columnHeader5.Width = 42;
            // 
            // columnHeader6
            // 
            this.columnHeader6.Text = "Height";
            this.columnHeader6.Width = 42;
            // 
            // TextureMap
            // 
            this.TextureMap.FormattingEnabled = true;
            this.TextureMap.Location = new System.Drawing.Point(13, 20);
            this.TextureMap.Name = "TextureMap";
            this.TextureMap.Size = new System.Drawing.Size(377, 95);
            this.TextureMap.TabIndex = 11;
            this.TextureMap.SelectedIndexChanged += new System.EventHandler(this.listBox1_SelectedIndexChanged);
            // 
            // removeTextureMap
            // 
            this.removeTextureMap.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.removeTextureMap.Location = new System.Drawing.Point(395, 44);
            this.removeTextureMap.Name = "removeTextureMap";
            this.removeTextureMap.Size = new System.Drawing.Size(18, 18);
            this.removeTextureMap.TabIndex = 10;
            this.removeTextureMap.Text = "-";
            this.removeTextureMap.UseVisualStyleBackColor = true;
            this.removeTextureMap.Click += new System.EventHandler(this.removeTextureMap_Click);
            // 
            // addTextureMap
            // 
            this.addTextureMap.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.addTextureMap.Location = new System.Drawing.Point(395, 20);
            this.addTextureMap.Name = "addTextureMap";
            this.addTextureMap.Size = new System.Drawing.Size(18, 18);
            this.addTextureMap.TabIndex = 9;
            this.addTextureMap.Text = "+";
            this.addTextureMap.UseVisualStyleBackColor = true;
            this.addTextureMap.Click += new System.EventHandler(this.addTextureMap_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(10, 4);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(67, 13);
            this.label2.TabIndex = 9;
            this.label2.Text = "Texture Map";
            // 
            // removeSpriterSceneFile
            // 
            this.removeSpriterSceneFile.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.removeSpriterSceneFile.Location = new System.Drawing.Point(439, 48);
            this.removeSpriterSceneFile.Name = "removeSpriterSceneFile";
            this.removeSpriterSceneFile.Size = new System.Drawing.Size(18, 18);
            this.removeSpriterSceneFile.TabIndex = 7;
            this.removeSpriterSceneFile.Text = "-";
            this.removeSpriterSceneFile.UseVisualStyleBackColor = true;
            this.removeSpriterSceneFile.Click += new System.EventHandler(this.removeSpriterSceneFile_Click);
            // 
            // addSpriterSceneFile
            // 
            this.addSpriterSceneFile.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.addSpriterSceneFile.Location = new System.Drawing.Point(439, 24);
            this.addSpriterSceneFile.Name = "addSpriterSceneFile";
            this.addSpriterSceneFile.Size = new System.Drawing.Size(18, 18);
            this.addSpriterSceneFile.TabIndex = 6;
            this.addSpriterSceneFile.Text = "+";
            this.addSpriterSceneFile.UseVisualStyleBackColor = true;
            this.addSpriterSceneFile.Click += new System.EventHandler(this.addSpriterSceneFile_Click);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.Filter = "Spriter XML files|*.scml";
            this.openFileDialog1.Title = "Add File";
            this.openFileDialog1.ValidateNames = false;
            this.openFileDialog1.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialog1_FileOk);
            // 
            // SpriterScene
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.panel1);
            this.Name = "SpriterScene";
            this.Size = new System.Drawing.Size(485, 642);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            this.panel4.ResumeLayout(false);
            this.panel4.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.height)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.width)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.yPos)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.xPos)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ListView sceneFilesList;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button removeSpriterSceneFile;
        private System.Windows.Forms.Button addSpriterSceneFile;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Button removeTextureMap;
        private System.Windows.Forms.Button addTextureMap;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ListBox TextureMap;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ListView textureMapPoints;
        private System.Windows.Forms.Panel panel4;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox pointName;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.NumericUpDown yPos;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.NumericUpDown xPos;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.ColumnHeader columnHeader3;
        private System.Windows.Forms.NumericUpDown height;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.NumericUpDown width;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.CheckBox rotated;
        private System.Windows.Forms.ColumnHeader columnHeader4;
        private System.Windows.Forms.ColumnHeader columnHeader5;
        private System.Windows.Forms.ColumnHeader columnHeader6;
        private System.Windows.Forms.Button button1;
    }
}