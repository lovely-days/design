﻿namespace Sells_system.pages
{
    partial class employee_adds
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(employee_adds));
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.text_address = new System.Windows.Forms.TextBox();
            this.text_name = new System.Windows.Forms.TextBox();
            this.text_phone = new System.Windows.Forms.TextBox();
            this.ea_add = new System.Windows.Forms.Button();
            this.ea_reset = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label4.Location = new System.Drawing.Point(64, 118);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(92, 27);
            this.label4.TabIndex = 32;
            this.label4.Text = "员工电话";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label3.Location = new System.Drawing.Point(64, 197);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(92, 27);
            this.label3.TabIndex = 31;
            this.label3.Text = "员工地址";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label2.Location = new System.Drawing.Point(83, 50);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(52, 27);
            this.label2.TabIndex = 30;
            this.label2.Text = "姓名";
            // 
            // text_address
            // 
            this.text_address.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.text_address.Location = new System.Drawing.Point(220, 197);
            this.text_address.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.text_address.Name = "text_address";
            this.text_address.Size = new System.Drawing.Size(143, 27);
            this.text_address.TabIndex = 28;
            // 
            // text_name
            // 
            this.text_name.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.text_name.Location = new System.Drawing.Point(220, 50);
            this.text_name.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.text_name.Name = "text_name";
            this.text_name.Size = new System.Drawing.Size(143, 27);
            this.text_name.TabIndex = 27;
            // 
            // text_phone
            // 
            this.text_phone.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.text_phone.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.text_phone.Location = new System.Drawing.Point(220, 118);
            this.text_phone.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.text_phone.Name = "text_phone";
            this.text_phone.Size = new System.Drawing.Size(143, 27);
            this.text_phone.TabIndex = 26;
            // 
            // ea_add
            // 
            this.ea_add.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.ea_add.Location = new System.Drawing.Point(58, 279);
            this.ea_add.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.ea_add.Name = "ea_add";
            this.ea_add.Size = new System.Drawing.Size(111, 47);
            this.ea_add.TabIndex = 23;
            this.ea_add.Text = "添加";
            this.ea_add.UseVisualStyleBackColor = true;
            this.ea_add.Click += new System.EventHandler(this.Ea_add_Click);
            // 
            // ea_reset
            // 
            this.ea_reset.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.ea_reset.Location = new System.Drawing.Point(271, 279);
            this.ea_reset.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.ea_reset.Name = "ea_reset";
            this.ea_reset.Size = new System.Drawing.Size(111, 47);
            this.ea_reset.TabIndex = 33;
            this.ea_reset.Text = "返回";
            this.ea_reset.UseVisualStyleBackColor = true;
            this.ea_reset.Click += new System.EventHandler(this.Ea_return_Click);
            // 
            // employee_adds
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(437, 373);
            this.Controls.Add(this.ea_reset);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.text_address);
            this.Controls.Add(this.text_name);
            this.Controls.Add(this.text_phone);
            this.Controls.Add(this.ea_add);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "employee_adds";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "员工添加";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox text_address;
        private System.Windows.Forms.TextBox text_name;
        private System.Windows.Forms.TextBox text_phone;
        private System.Windows.Forms.Button ea_add;
        private System.Windows.Forms.Button ea_reset;
    }
}