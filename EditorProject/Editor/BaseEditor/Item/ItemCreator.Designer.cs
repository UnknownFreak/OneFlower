namespace BaseEditor
{
    partial class ItemCreator
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
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.nameField = new System.Windows.Forms.TextBox();
            this.descriptionField = new System.Windows.Forms.TextBox();
            this.panel2 = new System.Windows.Forms.Panel();
            this.panel4 = new System.Windows.Forms.Panel();
            this.numericUpDown1 = new System.Windows.Forms.NumericUpDown();
            this.button2 = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.itemTypeField = new System.Windows.Forms.ComboBox();
            this.label6 = new System.Windows.Forms.Label();
            this.button3 = new System.Windows.Forms.Button();
            this.panel3 = new System.Windows.Forms.Panel();
            this.rarityField = new System.Windows.Forms.ComboBox();
            this.label16 = new System.Windows.Forms.Label();
            this.priceField = new System.Windows.Forms.NumericUpDown();
            this.label10 = new System.Windows.Forms.Label();
            this.weightField = new System.Windows.Forms.NumericUpDown();
            this.twoHandedField = new System.Windows.Forms.CheckBox();
            this.stackableFeld = new System.Windows.Forms.CheckBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.button4 = new System.Windows.Forms.Button();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.inventoryIconField = new System.Windows.Forms.TextBox();
            this.subTypeField = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            this.panel5 = new System.Windows.Forms.Panel();
            this.BagSlotField = new System.Windows.Forms.NumericUpDown();
            this.label13 = new System.Windows.Forms.Label();
            this.damageField = new System.Windows.Forms.NumericUpDown();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.defenseField = new System.Windows.Forms.NumericUpDown();
            this.label5 = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.textureField = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.attachmentPoints1 = new BaseEditor.AttachmentPoints();
            this.panel6 = new System.Windows.Forms.Panel();
            this.label14 = new System.Windows.Forms.Label();
            this.panel7 = new System.Windows.Forms.Panel();
            this.label15 = new System.Windows.Forms.Label();
            this.panel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
            this.panel3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.priceField)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.weightField)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.panel5.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.BagSlotField)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.damageField)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.defenseField)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.panel1.SuspendLayout();
            this.panel6.SuspendLayout();
            this.panel7.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(11, 6);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(58, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Item Name";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(51, 31);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(18, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "ID";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(9, 59);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(60, 13);
            this.label3.TabIndex = 3;
            this.label3.Text = "Description";
            // 
            // nameField
            // 
            this.nameField.Location = new System.Drawing.Point(75, 3);
            this.nameField.Name = "nameField";
            this.nameField.Size = new System.Drawing.Size(179, 20);
            this.nameField.TabIndex = 4;
            this.nameField.TextChanged += new System.EventHandler(this._TextChanged);
            // 
            // descriptionField
            // 
            this.descriptionField.Location = new System.Drawing.Point(75, 56);
            this.descriptionField.Multiline = true;
            this.descriptionField.Name = "descriptionField";
            this.descriptionField.Size = new System.Drawing.Size(179, 105);
            this.descriptionField.TabIndex = 6;
            this.descriptionField.TextChanged += new System.EventHandler(this._TextChanged);
            // 
            // panel2
            // 
            this.panel2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panel2.Controls.Add(this.panel4);
            this.panel2.Controls.Add(this.numericUpDown1);
            this.panel2.Controls.Add(this.button2);
            this.panel2.Controls.Add(this.label4);
            this.panel2.Controls.Add(this.nameField);
            this.panel2.Controls.Add(this.descriptionField);
            this.panel2.Controls.Add(this.label1);
            this.panel2.Controls.Add(this.label2);
            this.panel2.Controls.Add(this.label3);
            this.panel2.Location = new System.Drawing.Point(3, 3);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(261, 358);
            this.panel2.TabIndex = 7;
            // 
            // panel4
            // 
            this.panel4.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel4.Location = new System.Drawing.Point(3, 182);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(251, 169);
            this.panel4.TabIndex = 12;
            // 
            // numericUpDown1
            // 
            this.numericUpDown1.Location = new System.Drawing.Point(75, 29);
            this.numericUpDown1.Maximum = new decimal(new int[] {
            0,
            1,
            0,
            0});
            this.numericUpDown1.Name = "numericUpDown1";
            this.numericUpDown1.Size = new System.Drawing.Size(98, 20);
            this.numericUpDown1.TabIndex = 8;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(179, 27);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 22);
            this.button2.TabIndex = 4;
            this.button2.Text = "Suggest";
            this.button2.UseVisualStyleBackColor = true;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(2, 166);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(87, 13);
            this.label4.TabIndex = 8;
            this.label4.Text = "Tool Tip Preview";
            // 
            // itemTypeField
            // 
            this.itemTypeField.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.itemTypeField.FormattingEnabled = true;
            this.itemTypeField.Items.AddRange(new object[] {
            "Ammo",
            "Armor",
            "Bag",
            "Consumable",
            "Crafting Material",
            "Junk",
            "Trophy",
            "Weapon",
            "Undefined"});
            this.itemTypeField.Location = new System.Drawing.Point(72, 119);
            this.itemTypeField.Name = "itemTypeField";
            this.itemTypeField.Size = new System.Drawing.Size(121, 21);
            this.itemTypeField.TabIndex = 8;
            this.itemTypeField.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(12, 122);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(54, 13);
            this.label6.TabIndex = 9;
            this.label6.Text = "Item Type";
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(476, 641);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(200, 23);
            this.button3.TabIndex = 10;
            this.button3.Text = "Add";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // panel3
            // 
            this.panel3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panel3.Controls.Add(this.rarityField);
            this.panel3.Controls.Add(this.label16);
            this.panel3.Controls.Add(this.priceField);
            this.panel3.Controls.Add(this.label10);
            this.panel3.Controls.Add(this.weightField);
            this.panel3.Controls.Add(this.twoHandedField);
            this.panel3.Controls.Add(this.stackableFeld);
            this.panel3.Controls.Add(this.label9);
            this.panel3.Controls.Add(this.label8);
            this.panel3.Controls.Add(this.button4);
            this.panel3.Controls.Add(this.pictureBox2);
            this.panel3.Controls.Add(this.inventoryIconField);
            this.panel3.Controls.Add(this.subTypeField);
            this.panel3.Controls.Add(this.label7);
            this.panel3.Controls.Add(this.itemTypeField);
            this.panel3.Controls.Add(this.label6);
            this.panel3.Location = new System.Drawing.Point(270, 3);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(200, 358);
            this.panel3.TabIndex = 11;
            // 
            // rarityField
            // 
            this.rarityField.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.rarityField.FormattingEnabled = true;
            this.rarityField.Items.AddRange(new object[] {
            "Basic",
            "Common",
            "Fine",
            "Rare",
            "Exotic",
            "Legendary"});
            this.rarityField.Location = new System.Drawing.Point(72, 92);
            this.rarityField.Name = "rarityField";
            this.rarityField.Size = new System.Drawing.Size(121, 21);
            this.rarityField.TabIndex = 18;
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(32, 95);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(34, 13);
            this.label16.TabIndex = 19;
            this.label16.Text = "Rarity";
            // 
            // priceField
            // 
            this.priceField.Location = new System.Drawing.Point(72, 198);
            this.priceField.Maximum = new decimal(new int[] {
            0,
            1,
            0,
            0});
            this.priceField.Name = "priceField";
            this.priceField.Size = new System.Drawing.Size(121, 20);
            this.priceField.TabIndex = 15;
            this.priceField.ValueChanged += new System.EventHandler(this.ValueChanged);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(35, 200);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(31, 13);
            this.label10.TabIndex = 16;
            this.label10.Text = "Price";
            // 
            // weightField
            // 
            this.weightField.DecimalPlaces = 2;
            this.weightField.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.weightField.Location = new System.Drawing.Point(72, 172);
            this.weightField.Maximum = new decimal(new int[] {
            0,
            1,
            0,
            0});
            this.weightField.Name = "weightField";
            this.weightField.Size = new System.Drawing.Size(121, 20);
            this.weightField.TabIndex = 13;
            this.weightField.ValueChanged += new System.EventHandler(this.ValueChanged);
            // 
            // twoHandedField
            // 
            this.twoHandedField.AutoSize = true;
            this.twoHandedField.Enabled = false;
            this.twoHandedField.Location = new System.Drawing.Point(12, 334);
            this.twoHandedField.Name = "twoHandedField";
            this.twoHandedField.Size = new System.Drawing.Size(88, 17);
            this.twoHandedField.TabIndex = 12;
            this.twoHandedField.Text = "Two Handed";
            this.twoHandedField.UseVisualStyleBackColor = true;
            // 
            // stackableFeld
            // 
            this.stackableFeld.AutoSize = true;
            this.stackableFeld.Checked = true;
            this.stackableFeld.CheckState = System.Windows.Forms.CheckState.Checked;
            this.stackableFeld.Enabled = false;
            this.stackableFeld.Location = new System.Drawing.Point(12, 311);
            this.stackableFeld.Name = "stackableFeld";
            this.stackableFeld.Size = new System.Drawing.Size(77, 17);
            this.stackableFeld.TabIndex = 13;
            this.stackableFeld.Text = "Stack-able";
            this.stackableFeld.UseVisualStyleBackColor = true;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(25, 174);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(41, 13);
            this.label9.TabIndex = 14;
            this.label9.Text = "Weight";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(9, 6);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(98, 13);
            this.label8.TabIndex = 10;
            this.label8.Text = "Item Inventory Icon";
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(118, 28);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(75, 22);
            this.button4.TabIndex = 12;
            this.button4.Text = "Set Texture";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // pictureBox2
            // 
            this.pictureBox2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBox2.Location = new System.Drawing.Point(12, 54);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(32, 32);
            this.pictureBox2.TabIndex = 10;
            this.pictureBox2.TabStop = false;
            // 
            // inventoryIconField
            // 
            this.inventoryIconField.Enabled = false;
            this.inventoryIconField.Location = new System.Drawing.Point(12, 28);
            this.inventoryIconField.Name = "inventoryIconField";
            this.inventoryIconField.Size = new System.Drawing.Size(100, 20);
            this.inventoryIconField.TabIndex = 11;
            // 
            // subTypeField
            // 
            this.subTypeField.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.subTypeField.FormattingEnabled = true;
            this.subTypeField.Location = new System.Drawing.Point(72, 145);
            this.subTypeField.Name = "subTypeField";
            this.subTypeField.Size = new System.Drawing.Size(121, 21);
            this.subTypeField.TabIndex = 11;
            this.subTypeField.SelectedIndexChanged += new System.EventHandler(this.comboBox2_SelectedIndexChanged);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(13, 148);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(53, 13);
            this.label7.TabIndex = 10;
            this.label7.Text = "Sub Type";
            // 
            // panel5
            // 
            this.panel5.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panel5.Controls.Add(this.BagSlotField);
            this.panel5.Controls.Add(this.label13);
            this.panel5.Controls.Add(this.damageField);
            this.panel5.Controls.Add(this.label11);
            this.panel5.Controls.Add(this.label12);
            this.panel5.Controls.Add(this.defenseField);
            this.panel5.Location = new System.Drawing.Point(270, 229);
            this.panel5.Name = "panel5";
            this.panel5.Size = new System.Drawing.Size(200, 81);
            this.panel5.TabIndex = 17;
            // 
            // BagSlotField
            // 
            this.BagSlotField.Enabled = false;
            this.BagSlotField.Location = new System.Drawing.Point(72, 55);
            this.BagSlotField.Maximum = new decimal(new int[] {
            15,
            0,
            0,
            0});
            this.BagSlotField.Name = "BagSlotField";
            this.BagSlotField.Size = new System.Drawing.Size(121, 20);
            this.BagSlotField.TabIndex = 22;
            this.BagSlotField.ValueChanged += new System.EventHandler(this.ValueChanged);
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(14, 57);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(52, 13);
            this.label13.TabIndex = 23;
            this.label13.Text = "Bag Slots";
            // 
            // damageField
            // 
            this.damageField.Enabled = false;
            this.damageField.Location = new System.Drawing.Point(72, 29);
            this.damageField.Maximum = new decimal(new int[] {
            0,
            1,
            0,
            0});
            this.damageField.Name = "damageField";
            this.damageField.Size = new System.Drawing.Size(121, 20);
            this.damageField.TabIndex = 20;
            this.damageField.ValueChanged += new System.EventHandler(this.ValueChanged);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(19, 31);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(47, 13);
            this.label11.TabIndex = 21;
            this.label11.Text = "Damage";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(19, 5);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(47, 13);
            this.label12.TabIndex = 19;
            this.label12.Text = "Defense";
            // 
            // defenseField
            // 
            this.defenseField.Enabled = false;
            this.defenseField.Location = new System.Drawing.Point(72, 3);
            this.defenseField.Maximum = new decimal(new int[] {
            0,
            1,
            0,
            0});
            this.defenseField.Name = "defenseField";
            this.defenseField.Size = new System.Drawing.Size(121, 20);
            this.defenseField.TabIndex = 18;
            this.defenseField.ValueChanged += new System.EventHandler(this.ValueChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(3, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(57, 13);
            this.label5.TabIndex = 9;
            this.label5.Text = "Item Sprite";
            // 
            // pictureBox1
            // 
            this.pictureBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBox1.Location = new System.Drawing.Point(3, 12);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(256, 256);
            this.pictureBox1.TabIndex = 1;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseDown);
            // 
            // textureField
            // 
            this.textureField.Enabled = false;
            this.textureField.Location = new System.Drawing.Point(3, 272);
            this.textureField.Name = "textureField";
            this.textureField.Size = new System.Drawing.Size(175, 20);
            this.textureField.TabIndex = 2;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(184, 272);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 22);
            this.button1.TabIndex = 3;
            this.button1.Text = "Set Texture";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // panel1
            // 
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panel1.Controls.Add(this.button1);
            this.panel1.Controls.Add(this.textureField);
            this.panel1.Controls.Add(this.pictureBox1);
            this.panel1.Controls.Add(this.attachmentPoints1);
            this.panel1.Controls.Add(this.label5);
            this.panel1.Enabled = false;
            this.panel1.Location = new System.Drawing.Point(3, 367);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(467, 301);
            this.panel1.TabIndex = 0;
            // 
            // attachmentPoints1
            // 
            this.attachmentPoints1.Location = new System.Drawing.Point(265, 12);
            this.attachmentPoints1.Name = "attachmentPoints1";
            this.attachmentPoints1.Size = new System.Drawing.Size(195, 282);
            this.attachmentPoints1.TabIndex = 0;
            // 
            // panel6
            // 
            this.panel6.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panel6.Controls.Add(this.label14);
            this.panel6.Location = new System.Drawing.Point(476, 3);
            this.panel6.Name = "panel6";
            this.panel6.Size = new System.Drawing.Size(200, 314);
            this.panel6.TabIndex = 12;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(32, 124);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(140, 13);
            this.label14.TabIndex = 24;
            this.label14.Text = "EFFECT/ ENCHANT FIELD";
            // 
            // panel7
            // 
            this.panel7.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panel7.Controls.Add(this.label15);
            this.panel7.Location = new System.Drawing.Point(476, 323);
            this.panel7.Name = "panel7";
            this.panel7.Size = new System.Drawing.Size(200, 314);
            this.panel7.TabIndex = 25;
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(46, 113);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(85, 13);
            this.label15.TabIndex = 24;
            this.label15.Text = "SCRIPT FIELD?";
            // 
            // ItemCreator
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.Controls.Add(this.panel7);
            this.Controls.Add(this.panel6);
            this.Controls.Add(this.panel5);
            this.Controls.Add(this.panel3);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel1);
            this.Name = "ItemCreator";
            this.Size = new System.Drawing.Size(679, 671);
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.priceField)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.weightField)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.panel5.ResumeLayout(false);
            this.panel5.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.BagSlotField)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.damageField)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.defenseField)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.panel6.ResumeLayout(false);
            this.panel6.PerformLayout();
            this.panel7.ResumeLayout(false);
            this.panel7.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox nameField;
        private System.Windows.Forms.TextBox descriptionField;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.NumericUpDown numericUpDown1;
        private System.Windows.Forms.ComboBox itemTypeField;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.ComboBox subTypeField;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Panel panel4;
        private System.Windows.Forms.NumericUpDown priceField;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.NumericUpDown weightField;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.TextBox inventoryIconField;
        private System.Windows.Forms.CheckBox twoHandedField;
        private System.Windows.Forms.Label label5;
        private AttachmentPoints attachmentPoints1;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.TextBox textureField;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.CheckBox stackableFeld;
        private System.Windows.Forms.Panel panel5;
        private System.Windows.Forms.NumericUpDown BagSlotField;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.NumericUpDown damageField;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.NumericUpDown defenseField;
        private System.Windows.Forms.Panel panel6;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Panel panel7;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.ComboBox rarityField;
        private System.Windows.Forms.Label label16;
    }
}
