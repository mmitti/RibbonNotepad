using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace RibbonNotepad
{
	public partial class ToLineDialog : Form
	{
		private decimal mValue;
		public decimal Value { get { return mValue; } }
		public ToLineDialog()
		{
			InitializeComponent();
		}

		protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
		{
			if (keyData == (Keys.Alt | Keys.L))
			{
				numericUpDown1.Select(0, numericUpDown1.Value.ToString().Length);
				numericUpDown1.Focus();
				return true;
			}
			else if (keyData == Keys.Escape)
			{
				this.Close();
				return true;
			}
			return base.ProcessCmdKey(ref msg, keyData);
		}

		public DialogResult ShowDialog(int maxLine)
		{
			if (maxLine <= 0) maxLine = 1;
			this.AcceptButton = buttonOK;
			numericUpDown1.Maximum = maxLine;
			return ShowDialog();
		}

		private void buttonOK_Click(object sender, EventArgs e)
		{
			mValue = numericUpDown1.Value;
			this.DialogResult = DialogResult.OK;
			this.Close();
		}

		private void buttonCancel_Click(object sender, EventArgs e)
		{
			this.DialogResult = DialogResult.Cancel;
			this.Close();
		}

	}
}
