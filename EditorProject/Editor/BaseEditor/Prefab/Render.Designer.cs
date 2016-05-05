namespace BaseEditor.Prefab
{
    partial class Render
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
            this.panel2 = new System.Windows.Forms.Panel();
            this.armatureAnimation = new System.Windows.Forms.Panel();
            this.textureMap = new System.Windows.Forms.ComboBox();
            this.label6 = new System.Windows.Forms.Label();
            this.SceneFileDropDown = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.AnimationDropDown = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.EntityNameDropDown = new System.Windows.Forms.ComboBox();
            this.button1 = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.label41 = new System.Windows.Forms.Label();
            this.spriteSheet = new System.Windows.Forms.Panel();
            this.panel14 = new System.Windows.Forms.Panel();
            this.button2 = new System.Windows.Forms.Button();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.button3 = new System.Windows.Forms.Button();
            this.panel15 = new System.Windows.Forms.Panel();
            this.numericUpDown19 = new System.Windows.Forms.NumericUpDown();
            this.label32 = new System.Windows.Forms.Label();
            this.numericUpDown20 = new System.Windows.Forms.NumericUpDown();
            this.label33 = new System.Windows.Forms.Label();
            this.numericUpDown18 = new System.Windows.Forms.NumericUpDown();
            this.label31 = new System.Windows.Forms.Label();
            this.numericUpDown17 = new System.Windows.Forms.NumericUpDown();
            this.label30 = new System.Windows.Forms.Label();
            this.label29 = new System.Windows.Forms.Label();
            this.Loop = new System.Windows.Forms.CheckBox();
            this.textBox10 = new System.Windows.Forms.TextBox();
            this.label28 = new System.Windows.Forms.Label();
            this.numericUpDown16 = new System.Windows.Forms.NumericUpDown();
            this.label27 = new System.Windows.Forms.Label();
            this.button13 = new System.Windows.Forms.Button();
            this.button12 = new System.Windows.Forms.Button();
            this.listBox3 = new System.Windows.Forms.ListBox();
            this.label26 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.animationType = new System.Windows.Forms.ComboBox();
            this.panel12 = new System.Windows.Forms.Panel();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.button4 = new System.Windows.Forms.Button();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.label1 = new System.Windows.Forms.Label();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.panel2.SuspendLayout();
            this.armatureAnimation.SuspendLayout();
            this.spriteSheet.SuspendLayout();
            this.panel14.SuspendLayout();
            this.panel15.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown19)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown20)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown18)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown17)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown16)).BeginInit();
            this.panel12.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.SuspendLayout();
            // 
            // panel2
            // 
            this.panel2.AutoScroll = true;
            this.panel2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel2.Controls.Add(this.armatureAnimation);
            this.panel2.Controls.Add(this.label41);
            this.panel2.Controls.Add(this.spriteSheet);
            this.panel2.Controls.Add(this.label26);
            this.panel2.Controls.Add(this.label2);
            this.panel2.Controls.Add(this.animationType);
            this.panel2.Controls.Add(this.panel12);
            this.panel2.Controls.Add(this.label1);
            this.panel2.Enabled = false;
            this.panel2.Location = new System.Drawing.Point(3, 24);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(416, 628);
            this.panel2.TabIndex = 3;
            // 
            // armatureAnimation
            // 
            this.armatureAnimation.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.armatureAnimation.Controls.Add(this.textureMap);
            this.armatureAnimation.Controls.Add(this.label6);
            this.armatureAnimation.Controls.Add(this.SceneFileDropDown);
            this.armatureAnimation.Controls.Add(this.label5);
            this.armatureAnimation.Controls.Add(this.AnimationDropDown);
            this.armatureAnimation.Controls.Add(this.label4);
            this.armatureAnimation.Controls.Add(this.EntityNameDropDown);
            this.armatureAnimation.Controls.Add(this.button1);
            this.armatureAnimation.Controls.Add(this.label3);
            this.armatureAnimation.Location = new System.Drawing.Point(18, 885);
            this.armatureAnimation.Name = "armatureAnimation";
            this.armatureAnimation.Size = new System.Drawing.Size(372, 184);
            this.armatureAnimation.TabIndex = 22;
            // 
            // textureMap
            // 
            this.textureMap.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.textureMap.FormattingEnabled = true;
            this.textureMap.Location = new System.Drawing.Point(14, 104);
            this.textureMap.Name = "textureMap";
            this.textureMap.Size = new System.Drawing.Size(189, 21);
            this.textureMap.TabIndex = 33;
            this.textureMap.SelectedIndexChanged += new System.EventHandler(this.textureMap_SelectedIndexChanged);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(11, 88);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(67, 13);
            this.label6.TabIndex = 29;
            this.label6.Text = "Texture Map";
            // 
            // SceneFileDropDown
            // 
            this.SceneFileDropDown.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.SceneFileDropDown.FormattingEnabled = true;
            this.SceneFileDropDown.Location = new System.Drawing.Point(14, 24);
            this.SceneFileDropDown.Name = "SceneFileDropDown";
            this.SceneFileDropDown.Size = new System.Drawing.Size(189, 21);
            this.SceneFileDropDown.TabIndex = 28;
            this.SceneFileDropDown.SelectedIndexChanged += new System.EventHandler(this.SceneFileDropDown_SelectedIndexChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(11, 128);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(155, 13);
            this.label5.TabIndex = 27;
            this.label5.Text = "Animation Name (Preview Only)";
            // 
            // AnimationDropDown
            // 
            this.AnimationDropDown.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.AnimationDropDown.FormattingEnabled = true;
            this.AnimationDropDown.Location = new System.Drawing.Point(14, 144);
            this.AnimationDropDown.Name = "AnimationDropDown";
            this.AnimationDropDown.Size = new System.Drawing.Size(189, 21);
            this.AnimationDropDown.TabIndex = 26;
            this.AnimationDropDown.SelectedIndexChanged += new System.EventHandler(this.AnimationDropDown_SelectedIndexChanged);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(11, 48);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(64, 13);
            this.label4.TabIndex = 25;
            this.label4.Text = "Entity Name";
            // 
            // EntityNameDropDown
            // 
            this.EntityNameDropDown.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.EntityNameDropDown.FormattingEnabled = true;
            this.EntityNameDropDown.Location = new System.Drawing.Point(14, 64);
            this.EntityNameDropDown.Name = "EntityNameDropDown";
            this.EntityNameDropDown.Size = new System.Drawing.Size(189, 21);
            this.EntityNameDropDown.TabIndex = 24;
            this.EntityNameDropDown.SelectedIndexChanged += new System.EventHandler(this.EntityNameDropDown_SelectedIndexChanged);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(209, 24);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 22);
            this.button1.TabIndex = 16;
            this.button1.Text = "Manage...";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(11, 6);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(90, 13);
            this.label3.TabIndex = 23;
            this.label3.Text = "Spriter Scene File";
            // 
            // label41
            // 
            this.label41.AutoSize = true;
            this.label41.Location = new System.Drawing.Point(15, 869);
            this.label41.Name = "label41";
            this.label41.Size = new System.Drawing.Size(98, 13);
            this.label41.TabIndex = 21;
            this.label41.Text = "Armature Animation";
            // 
            // spriteSheet
            // 
            this.spriteSheet.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.spriteSheet.Controls.Add(this.panel14);
            this.spriteSheet.Controls.Add(this.button13);
            this.spriteSheet.Controls.Add(this.button12);
            this.spriteSheet.Controls.Add(this.listBox3);
            this.spriteSheet.Location = new System.Drawing.Point(18, 418);
            this.spriteSheet.Name = "spriteSheet";
            this.spriteSheet.Size = new System.Drawing.Size(372, 438);
            this.spriteSheet.TabIndex = 20;
            // 
            // panel14
            // 
            this.panel14.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel14.Controls.Add(this.button2);
            this.panel14.Controls.Add(this.listBox1);
            this.panel14.Controls.Add(this.button3);
            this.panel14.Controls.Add(this.panel15);
            this.panel14.Controls.Add(this.label29);
            this.panel14.Controls.Add(this.Loop);
            this.panel14.Controls.Add(this.textBox10);
            this.panel14.Controls.Add(this.label28);
            this.panel14.Controls.Add(this.numericUpDown16);
            this.panel14.Controls.Add(this.label27);
            this.panel14.Location = new System.Drawing.Point(14, 91);
            this.panel14.Name = "panel14";
            this.panel14.Size = new System.Drawing.Size(326, 325);
            this.panel14.TabIndex = 3;
            // 
            // button2
            // 
            this.button2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.button2.Location = new System.Drawing.Point(291, 146);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(18, 18);
            this.button2.TabIndex = 5;
            this.button2.Text = "-";
            this.button2.UseVisualStyleBackColor = true;
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.Location = new System.Drawing.Point(10, 122);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(275, 82);
            this.listBox1.TabIndex = 4;
            // 
            // button3
            // 
            this.button3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.button3.Location = new System.Drawing.Point(291, 122);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(18, 18);
            this.button3.TabIndex = 4;
            this.button3.Text = "+";
            this.button3.UseVisualStyleBackColor = true;
            // 
            // panel15
            // 
            this.panel15.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel15.Controls.Add(this.numericUpDown19);
            this.panel15.Controls.Add(this.label32);
            this.panel15.Controls.Add(this.numericUpDown20);
            this.panel15.Controls.Add(this.label33);
            this.panel15.Controls.Add(this.numericUpDown18);
            this.panel15.Controls.Add(this.label31);
            this.panel15.Controls.Add(this.numericUpDown17);
            this.panel15.Controls.Add(this.label30);
            this.panel15.Location = new System.Drawing.Point(10, 210);
            this.panel15.Name = "panel15";
            this.panel15.Size = new System.Drawing.Size(299, 100);
            this.panel15.TabIndex = 30;
            // 
            // numericUpDown19
            // 
            this.numericUpDown19.Location = new System.Drawing.Point(98, 64);
            this.numericUpDown19.Name = "numericUpDown19";
            this.numericUpDown19.Size = new System.Drawing.Size(79, 20);
            this.numericUpDown19.TabIndex = 36;
            // 
            // label32
            // 
            this.label32.AutoSize = true;
            this.label32.Location = new System.Drawing.Point(95, 48);
            this.label32.Name = "label32";
            this.label32.Size = new System.Drawing.Size(38, 13);
            this.label32.TabIndex = 37;
            this.label32.Text = "Height";
            // 
            // numericUpDown20
            // 
            this.numericUpDown20.Location = new System.Drawing.Point(13, 64);
            this.numericUpDown20.Name = "numericUpDown20";
            this.numericUpDown20.Size = new System.Drawing.Size(79, 20);
            this.numericUpDown20.TabIndex = 34;
            // 
            // label33
            // 
            this.label33.AutoSize = true;
            this.label33.Location = new System.Drawing.Point(10, 48);
            this.label33.Name = "label33";
            this.label33.Size = new System.Drawing.Size(35, 13);
            this.label33.TabIndex = 35;
            this.label33.Text = "Width";
            // 
            // numericUpDown18
            // 
            this.numericUpDown18.Location = new System.Drawing.Point(98, 25);
            this.numericUpDown18.Name = "numericUpDown18";
            this.numericUpDown18.Size = new System.Drawing.Size(79, 20);
            this.numericUpDown18.TabIndex = 32;
            // 
            // label31
            // 
            this.label31.AutoSize = true;
            this.label31.Location = new System.Drawing.Point(95, 9);
            this.label31.Name = "label31";
            this.label31.Size = new System.Drawing.Size(26, 13);
            this.label31.TabIndex = 33;
            this.label31.Text = "Top";
            // 
            // numericUpDown17
            // 
            this.numericUpDown17.Location = new System.Drawing.Point(13, 25);
            this.numericUpDown17.Name = "numericUpDown17";
            this.numericUpDown17.Size = new System.Drawing.Size(79, 20);
            this.numericUpDown17.TabIndex = 31;
            // 
            // label30
            // 
            this.label30.AutoSize = true;
            this.label30.Location = new System.Drawing.Point(10, 9);
            this.label30.Name = "label30";
            this.label30.Size = new System.Drawing.Size(25, 13);
            this.label30.TabIndex = 31;
            this.label30.Text = "Left";
            // 
            // label29
            // 
            this.label29.AutoSize = true;
            this.label29.Location = new System.Drawing.Point(7, 106);
            this.label29.Name = "label29";
            this.label29.Size = new System.Drawing.Size(66, 13);
            this.label29.TabIndex = 29;
            this.label29.Text = "TextureRect";
            // 
            // Loop
            // 
            this.Loop.AutoSize = true;
            this.Loop.Location = new System.Drawing.Point(10, 86);
            this.Loop.Name = "Loop";
            this.Loop.Size = new System.Drawing.Size(50, 17);
            this.Loop.TabIndex = 28;
            this.Loop.Text = "Loop";
            this.Loop.UseVisualStyleBackColor = true;
            // 
            // textBox10
            // 
            this.textBox10.Location = new System.Drawing.Point(10, 20);
            this.textBox10.Name = "textBox10";
            this.textBox10.Size = new System.Drawing.Size(158, 20);
            this.textBox10.TabIndex = 27;
            // 
            // label28
            // 
            this.label28.AutoSize = true;
            this.label28.Location = new System.Drawing.Point(7, 4);
            this.label28.Name = "label28";
            this.label28.Size = new System.Drawing.Size(35, 13);
            this.label28.TabIndex = 2;
            this.label28.Text = "Name";
            // 
            // numericUpDown16
            // 
            this.numericUpDown16.DecimalPlaces = 2;
            this.numericUpDown16.Location = new System.Drawing.Point(10, 59);
            this.numericUpDown16.Name = "numericUpDown16";
            this.numericUpDown16.Size = new System.Drawing.Size(158, 20);
            this.numericUpDown16.TabIndex = 1;
            // 
            // label27
            // 
            this.label27.AutoSize = true;
            this.label27.Location = new System.Drawing.Point(7, 43);
            this.label27.Name = "label27";
            this.label27.Size = new System.Drawing.Size(79, 13);
            this.label27.TabIndex = 0;
            this.label27.Text = "Animation Time";
            // 
            // button13
            // 
            this.button13.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.button13.Location = new System.Drawing.Point(346, 27);
            this.button13.Name = "button13";
            this.button13.Size = new System.Drawing.Size(18, 18);
            this.button13.TabIndex = 2;
            this.button13.Text = "-";
            this.button13.UseVisualStyleBackColor = true;
            // 
            // button12
            // 
            this.button12.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.button12.Location = new System.Drawing.Point(346, 3);
            this.button12.Name = "button12";
            this.button12.Size = new System.Drawing.Size(18, 18);
            this.button12.TabIndex = 1;
            this.button12.Text = "+";
            this.button12.UseVisualStyleBackColor = true;
            // 
            // listBox3
            // 
            this.listBox3.FormattingEnabled = true;
            this.listBox3.Location = new System.Drawing.Point(14, 3);
            this.listBox3.Name = "listBox3";
            this.listBox3.Size = new System.Drawing.Size(326, 82);
            this.listBox3.TabIndex = 0;
            // 
            // label26
            // 
            this.label26.AutoSize = true;
            this.label26.Location = new System.Drawing.Point(15, 402);
            this.label26.Name = "label26";
            this.label26.Size = new System.Drawing.Size(114, 13);
            this.label26.TabIndex = 19;
            this.label26.Text = "Sprite Sheet Animation";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(15, 351);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(80, 13);
            this.label2.TabIndex = 18;
            this.label2.Text = "Animation Type";
            // 
            // animationType
            // 
            this.animationType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.animationType.FormattingEnabled = true;
            this.animationType.Items.AddRange(new object[] {
            "Static",
            "SpriteSheet",
            "Armature"});
            this.animationType.Location = new System.Drawing.Point(18, 367);
            this.animationType.Name = "animationType";
            this.animationType.Size = new System.Drawing.Size(184, 21);
            this.animationType.TabIndex = 16;
            this.animationType.SelectedIndexChanged += new System.EventHandler(this.animationType_SelectedIndexChanged);
            // 
            // panel12
            // 
            this.panel12.AutoScroll = true;
            this.panel12.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel12.Controls.Add(this.textBox3);
            this.panel12.Controls.Add(this.button4);
            this.panel12.Controls.Add(this.pictureBox2);
            this.panel12.Location = new System.Drawing.Point(18, 25);
            this.panel12.Name = "panel12";
            this.panel12.Size = new System.Drawing.Size(372, 313);
            this.panel12.TabIndex = 17;
            // 
            // textBox3
            // 
            this.textBox3.Enabled = false;
            this.textBox3.Location = new System.Drawing.Point(14, 17);
            this.textBox3.Name = "textBox3";
            this.textBox3.ReadOnly = true;
            this.textBox3.Size = new System.Drawing.Size(169, 20);
            this.textBox3.TabIndex = 14;
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(189, 15);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(75, 22);
            this.button4.TabIndex = 15;
            this.button4.Text = "Set Texture";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // pictureBox2
            // 
            this.pictureBox2.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.pictureBox2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBox2.Location = new System.Drawing.Point(14, 43);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(256, 256);
            this.pictureBox2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pictureBox2.TabIndex = 13;
            this.pictureBox2.TabStop = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(15, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(43, 13);
            this.label1.TabIndex = 16;
            this.label1.Text = "Texture";
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(3, 4);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(137, 17);
            this.checkBox1.TabIndex = 2;
            this.checkBox1.Text = "Use RenderComponent";
            this.checkBox1.UseVisualStyleBackColor = true;
            this.checkBox1.CheckedChanged += new System.EventHandler(this.checkBox1_CheckedChanged);
            // 
            // Render
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.checkBox1);
            this.Name = "Render";
            this.Size = new System.Drawing.Size(425, 664);
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.armatureAnimation.ResumeLayout(false);
            this.armatureAnimation.PerformLayout();
            this.spriteSheet.ResumeLayout(false);
            this.panel14.ResumeLayout(false);
            this.panel14.PerformLayout();
            this.panel15.ResumeLayout(false);
            this.panel15.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown19)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown20)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown18)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown17)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown16)).EndInit();
            this.panel12.ResumeLayout(false);
            this.panel12.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Panel armatureAnimation;
        private System.Windows.Forms.Label label41;
        private System.Windows.Forms.Panel spriteSheet;
        private System.Windows.Forms.Panel panel14;
        private System.Windows.Forms.Panel panel15;
        private System.Windows.Forms.NumericUpDown numericUpDown19;
        private System.Windows.Forms.Label label32;
        private System.Windows.Forms.NumericUpDown numericUpDown20;
        private System.Windows.Forms.Label label33;
        private System.Windows.Forms.NumericUpDown numericUpDown18;
        private System.Windows.Forms.Label label31;
        private System.Windows.Forms.NumericUpDown numericUpDown17;
        private System.Windows.Forms.Label label30;
        private System.Windows.Forms.Label label29;
        private System.Windows.Forms.CheckBox Loop;
        private System.Windows.Forms.TextBox textBox10;
        private System.Windows.Forms.Label label28;
        private System.Windows.Forms.NumericUpDown numericUpDown16;
        private System.Windows.Forms.Label label27;
        private System.Windows.Forms.Button button13;
        private System.Windows.Forms.Button button12;
        private System.Windows.Forms.ListBox listBox3;
        private System.Windows.Forms.Label label26;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox animationType;
        private System.Windows.Forms.Panel panel12;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.ComboBox EntityNameDropDown;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox AnimationDropDown;
        private System.Windows.Forms.ComboBox SceneFileDropDown;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.ComboBox textureMap;
    }
}
