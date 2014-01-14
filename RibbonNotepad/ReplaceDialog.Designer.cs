namespace RibbonNotepad
{
	partial class ReplaceDialog
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
			this.groupFindDir = new System.Windows.Forms.GroupBox();
			this.FindDirDown = new System.Windows.Forms.RadioButton();
			this.FindDirUp = new System.Windows.Forms.RadioButton();
			this.groupOption = new System.Windows.Forms.GroupBox();
			this.checkBoxUseRegular = new System.Windows.Forms.CheckBox();
			this.checkBoxUseEscapeSequence = new System.Windows.Forms.CheckBox();
			this.checkBoxCaseSensitive = new System.Windows.Forms.CheckBox();
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.buttonFindFirst = new System.Windows.Forms.Button();
			this.buttonFindNext = new System.Windows.Forms.Button();
			this.buttonCancel = new System.Windows.Forms.Button();
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.textBox2 = new System.Windows.Forms.TextBox();
			this.buttonReplaceNext = new System.Windows.Forms.Button();
			this.buttonReplaceAll = new System.Windows.Forms.Button();
			this.groupFindDir.SuspendLayout();
			this.groupOption.SuspendLayout();
			this.SuspendLayout();
			// 
			// groupFindDir
			// 
			this.groupFindDir.Controls.Add(this.FindDirDown);
			this.groupFindDir.Controls.Add(this.FindDirUp);
			this.groupFindDir.Location = new System.Drawing.Point(218, 70);
			this.groupFindDir.Name = "groupFindDir";
			this.groupFindDir.Size = new System.Drawing.Size(139, 47);
			this.groupFindDir.TabIndex = 0;
			this.groupFindDir.TabStop = false;
			this.groupFindDir.Text = "検索方向";
			// 
			// FindDirDown
			// 
			this.FindDirDown.AutoSize = true;
			this.FindDirDown.Checked = true;
			this.FindDirDown.Location = new System.Drawing.Point(72, 19);
			this.FindDirDown.Name = "FindDirDown";
			this.FindDirDown.Size = new System.Drawing.Size(61, 16);
			this.FindDirDown.TabIndex = 1;
			this.FindDirDown.TabStop = true;
			this.FindDirDown.Text = "下へ(&D)";
			this.FindDirDown.UseVisualStyleBackColor = true;
			// 
			// FindDirUp
			// 
			this.FindDirUp.AutoSize = true;
			this.FindDirUp.Location = new System.Drawing.Point(7, 19);
			this.FindDirUp.Name = "FindDirUp";
			this.FindDirUp.Size = new System.Drawing.Size(61, 16);
			this.FindDirUp.TabIndex = 0;
			this.FindDirUp.Text = "上へ(&U)";
			this.FindDirUp.UseVisualStyleBackColor = true;
			// 
			// groupOption
			// 
			this.groupOption.Controls.Add(this.checkBoxUseRegular);
			this.groupOption.Controls.Add(this.checkBoxUseEscapeSequence);
			this.groupOption.Controls.Add(this.checkBoxCaseSensitive);
			this.groupOption.Location = new System.Drawing.Point(12, 70);
			this.groupOption.Name = "groupOption";
			this.groupOption.Size = new System.Drawing.Size(200, 86);
			this.groupOption.TabIndex = 1;
			this.groupOption.TabStop = false;
			this.groupOption.Text = "オプション";
			// 
			// checkBoxUseRegular
			// 
			this.checkBoxUseRegular.AutoSize = true;
			this.checkBoxUseRegular.Location = new System.Drawing.Point(7, 65);
			this.checkBoxUseRegular.Name = "checkBoxUseRegular";
			this.checkBoxUseRegular.Size = new System.Drawing.Size(149, 16);
			this.checkBoxUseRegular.TabIndex = 2;
			this.checkBoxUseRegular.Text = "検索に正規表現を使う(&R)";
			this.checkBoxUseRegular.UseVisualStyleBackColor = true;
			// 
			// checkBoxUseEscapeSequence
			// 
			this.checkBoxUseEscapeSequence.AutoSize = true;
			this.checkBoxUseEscapeSequence.Location = new System.Drawing.Point(7, 42);
			this.checkBoxUseEscapeSequence.Name = "checkBoxUseEscapeSequence";
			this.checkBoxUseEscapeSequence.Size = new System.Drawing.Size(146, 16);
			this.checkBoxUseEscapeSequence.TabIndex = 1;
			this.checkBoxUseEscapeSequence.Text = "改行=\\n タブ=\\t \\=\\\\(&E)";
			this.checkBoxUseEscapeSequence.UseVisualStyleBackColor = true;
			// 
			// checkBoxCaseSensitive
			// 
			this.checkBoxCaseSensitive.AutoSize = true;
			this.checkBoxCaseSensitive.Location = new System.Drawing.Point(7, 19);
			this.checkBoxCaseSensitive.Name = "checkBoxCaseSensitive";
			this.checkBoxCaseSensitive.Size = new System.Drawing.Size(172, 16);
			this.checkBoxCaseSensitive.TabIndex = 0;
			this.checkBoxCaseSensitive.Text = "大文字と小文字を区別する(&C)";
			this.checkBoxCaseSensitive.UseVisualStyleBackColor = true;
			// 
			// textBox1
			// 
			this.textBox1.Location = new System.Drawing.Point(118, 12);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new System.Drawing.Size(239, 19);
			this.textBox1.TabIndex = 2;
			// 
			// buttonFindFirst
			// 
			this.buttonFindFirst.Location = new System.Drawing.Point(370, 12);
			this.buttonFindFirst.Name = "buttonFindFirst";
			this.buttonFindFirst.Size = new System.Drawing.Size(106, 23);
			this.buttonFindFirst.TabIndex = 3;
			this.buttonFindFirst.Text = "先頭から検索(&O)";
			this.buttonFindFirst.UseVisualStyleBackColor = true;
			this.buttonFindFirst.Click += new System.EventHandler(this.buttonFindFirst_Click);
			// 
			// buttonFindNext
			// 
			this.buttonFindNext.Location = new System.Drawing.Point(370, 41);
			this.buttonFindNext.Name = "buttonFindNext";
			this.buttonFindNext.Size = new System.Drawing.Size(106, 23);
			this.buttonFindNext.TabIndex = 4;
			this.buttonFindNext.Text = "次を検索(&F)";
			this.buttonFindNext.UseVisualStyleBackColor = true;
			this.buttonFindNext.Click += new System.EventHandler(this.buttonFindNext_Click);
			// 
			// buttonCancel
			// 
			this.buttonCancel.Location = new System.Drawing.Point(370, 128);
			this.buttonCancel.Name = "buttonCancel";
			this.buttonCancel.Size = new System.Drawing.Size(106, 23);
			this.buttonCancel.TabIndex = 5;
			this.buttonCancel.Text = "キャンセル";
			this.buttonCancel.UseVisualStyleBackColor = true;
			this.buttonCancel.Click += new System.EventHandler(this.buttonCancel_Click);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(12, 15);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(100, 12);
			this.label1.TabIndex = 6;
			this.label1.Text = "検索する文字列(&N)";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(12, 41);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(102, 12);
			this.label2.TabIndex = 7;
			this.label2.Text = "置換後の文字列(&P)";
			// 
			// textBox2
			// 
			this.textBox2.Location = new System.Drawing.Point(118, 38);
			this.textBox2.Name = "textBox2";
			this.textBox2.Size = new System.Drawing.Size(239, 19);
			this.textBox2.TabIndex = 8;
			this.textBox2.TextChanged += new System.EventHandler(this.textBox2_TextChanged);
			// 
			// buttonReplaceNext
			// 
			this.buttonReplaceNext.Location = new System.Drawing.Point(370, 70);
			this.buttonReplaceNext.Name = "buttonReplaceNext";
			this.buttonReplaceNext.Size = new System.Drawing.Size(106, 23);
			this.buttonReplaceNext.TabIndex = 9;
			this.buttonReplaceNext.Text = "置換して次へ(&X)";
			this.buttonReplaceNext.UseVisualStyleBackColor = true;
			this.buttonReplaceNext.Click += new System.EventHandler(this.buttonReplaceNext_Click);
			// 
			// buttonReplaceAll
			// 
			this.buttonReplaceAll.Location = new System.Drawing.Point(370, 99);
			this.buttonReplaceAll.Name = "buttonReplaceAll";
			this.buttonReplaceAll.Size = new System.Drawing.Size(106, 23);
			this.buttonReplaceAll.TabIndex = 10;
			this.buttonReplaceAll.Text = "すべて置換(&A)";
			this.buttonReplaceAll.UseVisualStyleBackColor = true;
			this.buttonReplaceAll.Click += new System.EventHandler(this.buttonReplaceAll_Click);
			// 
			// ReplaceDialog
			// 
			this.AcceptButton = this.buttonFindNext;
			this.AutoScaleDimensions = new System.Drawing.SizeF(96F, 96F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
			this.ClientSize = new System.Drawing.Size(488, 183);
			this.Controls.Add(this.buttonReplaceAll);
			this.Controls.Add(this.buttonReplaceNext);
			this.Controls.Add(this.textBox2);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.buttonCancel);
			this.Controls.Add(this.buttonFindNext);
			this.Controls.Add(this.buttonFindFirst);
			this.Controls.Add(this.textBox1);
			this.Controls.Add(this.groupOption);
			this.Controls.Add(this.groupFindDir);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "ReplaceDialog";
			this.ShowIcon = false;
			this.Text = "置換";
			this.groupFindDir.ResumeLayout(false);
			this.groupFindDir.PerformLayout();
			this.groupOption.ResumeLayout(false);
			this.groupOption.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.GroupBox groupFindDir;
		private System.Windows.Forms.RadioButton FindDirDown;
		private System.Windows.Forms.RadioButton FindDirUp;
		private System.Windows.Forms.GroupBox groupOption;
		private System.Windows.Forms.CheckBox checkBoxUseRegular;
		private System.Windows.Forms.CheckBox checkBoxUseEscapeSequence;
		private System.Windows.Forms.CheckBox checkBoxCaseSensitive;
		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.Button buttonFindFirst;
		private System.Windows.Forms.Button buttonFindNext;
		private System.Windows.Forms.Button buttonCancel;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.TextBox textBox2;
		private System.Windows.Forms.Button buttonReplaceNext;
		private System.Windows.Forms.Button buttonReplaceAll;
	}
}