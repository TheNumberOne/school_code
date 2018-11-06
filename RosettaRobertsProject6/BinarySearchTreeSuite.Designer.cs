namespace RosettaRobertsProject6
{
	partial class BinarySearchTreeSuite
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
            this.label1 = new System.Windows.Forms.Label();
            this.TxtTree1 = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.TxtInput = new System.Windows.Forms.TextBox();
            this.TxtResult = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.button2 = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.TxtTree1Minimum = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.TxtTree1Maximum = new System.Windows.Forms.TextBox();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.TxtTree2Minimum = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.TxtTree2 = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.BtnTree1Active = new System.Windows.Forms.RadioButton();
            this.BtnTree2Active = new System.Windows.Forms.RadioButton();
            this.button5 = new System.Windows.Forms.Button();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.TxtTree1MaxDepth = new System.Windows.Forms.TextBox();
            this.TxtTree1MinDepth = new System.Windows.Forms.TextBox();
            this.TxtTree2MaxDepth = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.TxtTree2Maximum = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.TxtTree2MinDepth = new System.Windows.Forms.TextBox();
            this.button6 = new System.Windows.Forms.Button();
            this.NumTestSuiteSize = new System.Windows.Forms.NumericUpDown();
            this.label5 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.NumTestSuiteSize)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Tree 1:";
            // 
            // TxtTree1
            // 
            this.TxtTree1.Font = new System.Drawing.Font("Consolas", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TxtTree1.Location = new System.Drawing.Point(75, 12);
            this.TxtTree1.Multiline = true;
            this.TxtTree1.Name = "TxtTree1";
            this.TxtTree1.ReadOnly = true;
            this.TxtTree1.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.TxtTree1.Size = new System.Drawing.Size(713, 80);
            this.TxtTree1.TabIndex = 3;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(94, 351);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 18;
            this.button1.Text = "Find";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.Find);
            // 
            // TxtInput
            // 
            this.TxtInput.Location = new System.Drawing.Point(12, 296);
            this.TxtInput.Name = "TxtInput";
            this.TxtInput.Size = new System.Drawing.Size(100, 20);
            this.TxtInput.TabIndex = 14;
            // 
            // TxtResult
            // 
            this.TxtResult.Font = new System.Drawing.Font("Consolas", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TxtResult.Location = new System.Drawing.Point(217, 296);
            this.TxtResult.Multiline = true;
            this.TxtResult.Name = "TxtResult";
            this.TxtResult.ReadOnly = true;
            this.TxtResult.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.TxtResult.Size = new System.Drawing.Size(571, 107);
            this.TxtResult.TabIndex = 19;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(171, 299);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(40, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Result:";
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(12, 322);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 15;
            this.button2.Text = "Insert";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.Insert);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 102);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(51, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "Minimum:";
            // 
            // TxtTree1Minimum
            // 
            this.TxtTree1Minimum.Location = new System.Drawing.Point(75, 99);
            this.TxtTree1Minimum.Name = "TxtTree1Minimum";
            this.TxtTree1Minimum.ReadOnly = true;
            this.TxtTree1Minimum.Size = new System.Drawing.Size(100, 20);
            this.TxtTree1Minimum.TabIndex = 4;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(219, 102);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(54, 13);
            this.label4.TabIndex = 9;
            this.label4.Text = "Maximum:";
            // 
            // TxtTree1Maximum
            // 
            this.TxtTree1Maximum.Location = new System.Drawing.Point(279, 98);
            this.TxtTree1Maximum.Name = "TxtTree1Maximum";
            this.TxtTree1Maximum.ReadOnly = true;
            this.TxtTree1Maximum.Size = new System.Drawing.Size(100, 20);
            this.TxtTree1Maximum.TabIndex = 5;
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(93, 322);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(75, 23);
            this.button3.TabIndex = 16;
            this.button3.Text = "Delete";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.Delete);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(12, 351);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(75, 23);
            this.button4.TabIndex = 17;
            this.button4.Text = "Predecessor";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.Predecessor);
            // 
            // TxtTree2Minimum
            // 
            this.TxtTree2Minimum.Location = new System.Drawing.Point(75, 226);
            this.TxtTree2Minimum.Name = "TxtTree2Minimum";
            this.TxtTree2Minimum.ReadOnly = true;
            this.TxtTree2Minimum.Size = new System.Drawing.Size(100, 20);
            this.TxtTree2Minimum.TabIndex = 9;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(12, 228);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(51, 13);
            this.label6.TabIndex = 14;
            this.label6.Text = "Minimum:";
            // 
            // TxtTree2
            // 
            this.TxtTree2.Font = new System.Drawing.Font("Consolas", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TxtTree2.Location = new System.Drawing.Point(75, 138);
            this.TxtTree2.Multiline = true;
            this.TxtTree2.Name = "TxtTree2";
            this.TxtTree2.ReadOnly = true;
            this.TxtTree2.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.TxtTree2.Size = new System.Drawing.Size(713, 80);
            this.TxtTree2.TabIndex = 8;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(9, 141);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(41, 13);
            this.label7.TabIndex = 18;
            this.label7.Text = "Tree 2:";
            // 
            // BtnTree1Active
            // 
            this.BtnTree1Active.AutoSize = true;
            this.BtnTree1Active.Checked = true;
            this.BtnTree1Active.Location = new System.Drawing.Point(15, 46);
            this.BtnTree1Active.Name = "BtnTree1Active";
            this.BtnTree1Active.Size = new System.Drawing.Size(54, 17);
            this.BtnTree1Active.TabIndex = 1;
            this.BtnTree1Active.TabStop = true;
            this.BtnTree1Active.Text = "active";
            this.BtnTree1Active.UseVisualStyleBackColor = true;
            this.BtnTree1Active.CheckedChanged += new System.EventHandler(this.ActiveTreeChanged);
            // 
            // BtnTree2Active
            // 
            this.BtnTree2Active.AutoSize = true;
            this.BtnTree2Active.Location = new System.Drawing.Point(15, 177);
            this.BtnTree2Active.Name = "BtnTree2Active";
            this.BtnTree2Active.Size = new System.Drawing.Size(54, 17);
            this.BtnTree2Active.TabIndex = 2;
            this.BtnTree2Active.Text = "active";
            this.BtnTree2Active.UseVisualStyleBackColor = true;
            this.BtnTree2Active.CheckedChanged += new System.EventHandler(this.ActiveTreeChanged);
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(12, 252);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(75, 23);
            this.button5.TabIndex = 13;
            this.button5.Text = "Intersect";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.Intersect);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(418, 101);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(59, 13);
            this.label8.TabIndex = 22;
            this.label8.Text = "Min Depth:";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(623, 101);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(62, 13);
            this.label9.TabIndex = 23;
            this.label9.Text = "Max Depth:";
            // 
            // TxtTree1MaxDepth
            // 
            this.TxtTree1MaxDepth.Location = new System.Drawing.Point(688, 99);
            this.TxtTree1MaxDepth.Name = "TxtTree1MaxDepth";
            this.TxtTree1MaxDepth.ReadOnly = true;
            this.TxtTree1MaxDepth.Size = new System.Drawing.Size(100, 20);
            this.TxtTree1MaxDepth.TabIndex = 7;
            // 
            // TxtTree1MinDepth
            // 
            this.TxtTree1MinDepth.Location = new System.Drawing.Point(483, 99);
            this.TxtTree1MinDepth.Name = "TxtTree1MinDepth";
            this.TxtTree1MinDepth.ReadOnly = true;
            this.TxtTree1MinDepth.Size = new System.Drawing.Size(100, 20);
            this.TxtTree1MinDepth.TabIndex = 6;
            // 
            // TxtTree2MaxDepth
            // 
            this.TxtTree2MaxDepth.Location = new System.Drawing.Point(688, 226);
            this.TxtTree2MaxDepth.Name = "TxtTree2MaxDepth";
            this.TxtTree2MaxDepth.ReadOnly = true;
            this.TxtTree2MaxDepth.Size = new System.Drawing.Size(100, 20);
            this.TxtTree2MaxDepth.TabIndex = 12;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(623, 228);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(62, 13);
            this.label10.TabIndex = 29;
            this.label10.Text = "Max Depth:";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(418, 228);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(59, 13);
            this.label11.TabIndex = 28;
            this.label11.Text = "Min Depth:";
            // 
            // TxtTree2Maximum
            // 
            this.TxtTree2Maximum.Location = new System.Drawing.Point(279, 225);
            this.TxtTree2Maximum.Name = "TxtTree2Maximum";
            this.TxtTree2Maximum.ReadOnly = true;
            this.TxtTree2Maximum.Size = new System.Drawing.Size(100, 20);
            this.TxtTree2Maximum.TabIndex = 10;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(219, 229);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(54, 13);
            this.label12.TabIndex = 26;
            this.label12.Text = "Maximum:";
            // 
            // TxtTree2MinDepth
            // 
            this.TxtTree2MinDepth.Location = new System.Drawing.Point(483, 226);
            this.TxtTree2MinDepth.Name = "TxtTree2MinDepth";
            this.TxtTree2MinDepth.ReadOnly = true;
            this.TxtTree2MinDepth.Size = new System.Drawing.Size(100, 20);
            this.TxtTree2MinDepth.TabIndex = 11;
            // 
            // button6
            // 
            this.button6.Location = new System.Drawing.Point(223, 406);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(156, 23);
            this.button6.TabIndex = 21;
            this.button6.Text = "Run Test Suite";
            this.button6.UseVisualStyleBackColor = true;
            this.button6.Click += new System.EventHandler(this.RunTestSuite);
            // 
            // NumTestSuiteSize
            // 
            this.NumTestSuiteSize.Location = new System.Drawing.Point(96, 409);
            this.NumTestSuiteSize.Maximum = new decimal(new int[] {
            100000,
            0,
            0,
            0});
            this.NumTestSuiteSize.Name = "NumTestSuiteSize";
            this.NumTestSuiteSize.Size = new System.Drawing.Size(120, 20);
            this.NumTestSuiteSize.TabIndex = 20;
            this.NumTestSuiteSize.Value = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 411);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(81, 13);
            this.label5.TabIndex = 34;
            this.label5.Text = "Test Suite Size:";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Font = new System.Drawing.Font("Microsoft Sans Serif", 6F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label13.Location = new System.Drawing.Point(10, 432);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(617, 9);
            this.label13.TabIndex = 35;
            this.label13.Text = "(Warning: Run in release mode to make a stackoverflow exception less likely. If t" +
    "he test suite size is too large it will crash the application with an uncatchabl" +
    "e stackoverflow exception)";
            // 
            // BinarySearchTreeSuite
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.NumTestSuiteSize);
            this.Controls.Add(this.button6);
            this.Controls.Add(this.TxtTree2MinDepth);
            this.Controls.Add(this.TxtTree2MaxDepth);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.TxtTree2Maximum);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.TxtTree1MinDepth);
            this.Controls.Add(this.TxtTree1MaxDepth);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.BtnTree2Active);
            this.Controls.Add(this.BtnTree1Active);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.TxtTree2Minimum);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.TxtTree2);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.TxtTree1Maximum);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.TxtTree1Minimum);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.TxtResult);
            this.Controls.Add(this.TxtInput);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.TxtTree1);
            this.Controls.Add(this.label1);
            this.Name = "BinarySearchTreeSuite";
            this.Text = "Binary Search Tree Suite";
            ((System.ComponentModel.ISupportInitialize)(this.NumTestSuiteSize)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

		}

		#endregion
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox TxtTree1;
		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.TextBox TxtInput;
		private System.Windows.Forms.TextBox TxtResult;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Button button2;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.TextBox TxtTree1Minimum;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.TextBox TxtTree1Maximum;
		private System.Windows.Forms.Button button3;
		private System.Windows.Forms.Button button4;
		private System.Windows.Forms.TextBox TxtTree2Minimum;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.TextBox TxtTree2;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.RadioButton BtnTree1Active;
		private System.Windows.Forms.RadioButton BtnTree2Active;
		private System.Windows.Forms.Button button5;
		private System.Windows.Forms.Label label8;
		private System.Windows.Forms.Label label9;
		private System.Windows.Forms.TextBox TxtTree1MaxDepth;
		private System.Windows.Forms.TextBox TxtTree1MinDepth;
		private System.Windows.Forms.TextBox TxtTree2MaxDepth;
		private System.Windows.Forms.Label label10;
		private System.Windows.Forms.Label label11;
		private System.Windows.Forms.TextBox TxtTree2Maximum;
		private System.Windows.Forms.Label label12;
		private System.Windows.Forms.TextBox TxtTree2MinDepth;
		private System.Windows.Forms.Button button6;
		private System.Windows.Forms.NumericUpDown NumTestSuiteSize;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.Label label13;
	}
}

