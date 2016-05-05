namespace BaseEditor.Quest
{
    partial class ObjectiveField
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
            this.components = new System.ComponentModel.Container();
            this.types = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.bonusObjective = new System.Windows.Forms.CheckBox();
            this.nameBox = new System.Windows.Forms.TextBox();
            this.descriptionBox = new System.Windows.Forms.TextBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.button6 = new System.Windows.Forms.Button();
            this.button7 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.targetDestinationBox = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.button2 = new System.Windows.Forms.Button();
            this.destinationBox = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.repeatCount = new System.Windows.Forms.NumericUpDown();
            this.targetBox = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            this.label8 = new System.Windows.Forms.Label();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.repeatCount)).BeginInit();
            this.SuspendLayout();
            // 
            // types
            // 
            this.types.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.types.FormattingEnabled = true;
            this.types.Items.AddRange(new object[] {
            "Escort",
            "Explore",
            "Work",
            "Kill",
            "Fetch"});
            this.types.Location = new System.Drawing.Point(10, 150);
            this.types.Name = "types";
            this.types.Size = new System.Drawing.Size(176, 21);
            this.types.TabIndex = 0;
            this.types.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(7, 134);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(62, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Quest Type";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(9, 12);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(83, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Objective Name";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(9, 51);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(60, 13);
            this.label3.TabIndex = 3;
            this.label3.Text = "Description";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(7, 11);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(78, 13);
            this.label4.TabIndex = 4;
            this.label4.Text = "Target (Object)";
            // 
            // bonusObjective
            // 
            this.bonusObjective.AutoSize = true;
            this.bonusObjective.Location = new System.Drawing.Point(10, 177);
            this.bonusObjective.Name = "bonusObjective";
            this.bonusObjective.Size = new System.Drawing.Size(114, 17);
            this.bonusObjective.TabIndex = 5;
            this.bonusObjective.Text = "is Bouns Objective";
            this.bonusObjective.UseVisualStyleBackColor = true;
            this.bonusObjective.CheckedChanged += new System.EventHandler(this.checkBox1_CheckedChanged);
            // 
            // nameBox
            // 
            this.nameBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.nameBox.Location = new System.Drawing.Point(12, 28);
            this.nameBox.Name = "nameBox";
            this.nameBox.Size = new System.Drawing.Size(444, 20);
            this.nameBox.TabIndex = 6;
            this.nameBox.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // descriptionBox
            // 
            this.descriptionBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.descriptionBox.Location = new System.Drawing.Point(12, 67);
            this.descriptionBox.Multiline = true;
            this.descriptionBox.Name = "descriptionBox";
            this.descriptionBox.Size = new System.Drawing.Size(444, 55);
            this.descriptionBox.TabIndex = 7;
            this.descriptionBox.TextChanged += new System.EventHandler(this.textBox2_TextChanged);
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Controls.Add(this.button6);
            this.panel1.Controls.Add(this.button7);
            this.panel1.Controls.Add(this.button5);
            this.panel1.Controls.Add(this.targetDestinationBox);
            this.panel1.Controls.Add(this.label7);
            this.panel1.Controls.Add(this.button2);
            this.panel1.Controls.Add(this.destinationBox);
            this.panel1.Controls.Add(this.label6);
            this.panel1.Controls.Add(this.button1);
            this.panel1.Controls.Add(this.repeatCount);
            this.panel1.Controls.Add(this.targetBox);
            this.panel1.Controls.Add(this.label5);
            this.panel1.Controls.Add(this.label4);
            this.panel1.Location = new System.Drawing.Point(10, 215);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(446, 196);
            this.panel1.TabIndex = 8;
            // 
            // button6
            // 
            this.button6.Location = new System.Drawing.Point(160, 115);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(112, 20);
            this.button6.TabIndex = 21;
            this.button6.Text = "Select from Window";
            this.toolTip1.SetToolTip(this.button6, "Selects a object from the Editor window.\r\n(Will set the Destination Zone if it is" +
        " not set,\r\nor is not the current opened Zone in the Editor Window)\r\nUsed combine" +
        "d with Explore or Escort Quest");
            this.button6.UseVisualStyleBackColor = true;
            this.button6.Click += new System.EventHandler(this.button6_Click);
            // 
            // button7
            // 
            this.button7.Location = new System.Drawing.Point(160, 69);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(112, 20);
            this.button7.TabIndex = 20;
            this.button7.Text = "Use Current Zone";
            this.toolTip1.SetToolTip(this.button7, "Use the zone loaded in the Editor window.");
            this.button7.UseVisualStyleBackColor = true;
            this.button7.Click += new System.EventHandler(this.button7_Click);
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(116, 115);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(38, 20);
            this.button5.TabIndex = 19;
            this.button5.Text = "Set";
            this.toolTip1.SetToolTip(this.button5, "Set the target destination.\r\nUsed combined with Explore or Escort Quest");
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // targetDestinationBox
            // 
            this.targetDestinationBox.Location = new System.Drawing.Point(10, 115);
            this.targetDestinationBox.Name = "targetDestinationBox";
            this.targetDestinationBox.ReadOnly = true;
            this.targetDestinationBox.Size = new System.Drawing.Size(99, 20);
            this.targetDestinationBox.TabIndex = 18;
            this.toolTip1.SetToolTip(this.targetDestinationBox, "Identifier of the object selected from the Zone\r\n(Modname,ID)");
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(7, 99);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(100, 13);
            this.label7.TabIndex = 17;
            this.label7.Text = "Target (Destination)";
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(116, 69);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(38, 20);
            this.button2.TabIndex = 14;
            this.button2.Text = "Set";
            this.toolTip1.SetToolTip(this.button2, "Set the destination zone.\r\nUsed combined with Explore or Escort Quest");
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // destinationBox
            // 
            this.destinationBox.Location = new System.Drawing.Point(10, 69);
            this.destinationBox.Name = "destinationBox";
            this.destinationBox.ReadOnly = true;
            this.destinationBox.Size = new System.Drawing.Size(99, 20);
            this.destinationBox.TabIndex = 13;
            this.toolTip1.SetToolTip(this.destinationBox, "Identifier of the selected Zone\r\n(Modname,ID)");
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(7, 53);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(94, 13);
            this.label6.TabIndex = 12;
            this.label6.Text = "Destination (Zone)";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(116, 27);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(38, 20);
            this.button1.TabIndex = 11;
            this.button1.Text = "Set";
            this.toolTip1.SetToolTip(this.button1, "Select the target object.");
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // repeatCount
            // 
            this.repeatCount.Location = new System.Drawing.Point(10, 159);
            this.repeatCount.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.repeatCount.Name = "repeatCount";
            this.repeatCount.Size = new System.Drawing.Size(99, 20);
            this.repeatCount.TabIndex = 10;
            this.toolTip1.SetToolTip(this.repeatCount, "How many times to repeat this.\r\n(Only available for Fetch and Kill Quest)");
            this.repeatCount.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.repeatCount.ValueChanged += new System.EventHandler(this.numericUpDown1_ValueChanged);
            // 
            // targetBox
            // 
            this.targetBox.Location = new System.Drawing.Point(10, 27);
            this.targetBox.Name = "targetBox";
            this.targetBox.ReadOnly = true;
            this.targetBox.Size = new System.Drawing.Size(99, 20);
            this.targetBox.TabIndex = 9;
            this.toolTip1.SetToolTip(this.targetBox, "Identifier of the selected target\r\n(Modname,ID)");
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(7, 143);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(35, 13);
            this.label5.TabIndex = 5;
            this.label5.Text = "Count";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(9, 199);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(38, 13);
            this.label8.TabIndex = 9;
            this.label8.Text = "Target";
            // 
            // ObjectiveField
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Controls.Add(this.label8);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.descriptionBox);
            this.Controls.Add(this.nameBox);
            this.Controls.Add(this.bonusObjective);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.types);
            this.Name = "ObjectiveField";
            this.Size = new System.Drawing.Size(469, 428);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.repeatCount)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox types;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.CheckBox bonusObjective;
        private System.Windows.Forms.TextBox nameBox;
        private System.Windows.Forms.TextBox descriptionBox;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.NumericUpDown repeatCount;
        private System.Windows.Forms.TextBox targetBox;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.TextBox destinationBox;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ToolTip toolTip1;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.TextBox targetDestinationBox;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.Button button7;
        private System.Windows.Forms.Label label8;
    }
}
