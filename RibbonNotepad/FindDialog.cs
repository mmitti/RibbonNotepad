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
	public partial class FindDialog : Form
	{
		private Find mFind;
		private Boolean mIsFindFirst;
		public FindDialog(Find find)
		{
			InitializeComponent();
			mFind = find;
			textBox1.TextChanged += new EventHandler(onFindTextChanged);
			checkBoxCaseSensitive.Checked = find.findOption.caseSensitive;
			checkBoxUseEscapeSequence.Checked = find.findOption.useEscapeSequence;
			checkBoxUseRegular.Checked = find.findOption.useRegular;
			if (find.findOption.findDir == FindOption.FindDirection.UP) FindDirUp.Checked = true;
			else FindDirDown.Checked = true;
			textBox1.Text = find.findOption.text;
		}

		public new void Show()
		{
			if (Visible) return;
			mIsFindFirst = false;
			base.Show();
		}

		private void onFindTextChanged(object sender, EventArgs args)
		{
			mIsFindFirst = false;
			mFind.findOption.text = textBox1.Text;
		}
	 

		private void buttonFindFirst_Click(object sender, EventArgs e)
		{
			if (!mIsFindFirst)
			{
				mFind.findFirst();
				mIsFindFirst = true;
			}
			else mFind.findNext();
		}

		private void buttonFindNext_Click(object sender, EventArgs e)
		{
			mFind.findNext();
		}

		private void buttonCancel_Click(object sender, EventArgs e)
		{
			this.Dispose();
		}


		protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
		{
			if (keyData == (Keys.Alt | Keys.N))
			{
				textBox1.Select(0, textBox1.Text.Length);
				textBox1.Focus();
			}
			else if (keyData == (Keys.Alt | Keys.C))
			{
				checkBoxCaseSensitive.Checked = !checkBoxCaseSensitive.Checked;
				checkBoxCaseSensitive.Focus();
				mFind.findOption.caseSensitive = checkBoxCaseSensitive.Checked;
			}
			else if (keyData == (Keys.Alt | Keys.E))
			{
				checkBoxUseEscapeSequence.Checked = !checkBoxUseEscapeSequence.Checked;
				checkBoxUseEscapeSequence.Focus();
				mFind.findOption.useEscapeSequence = checkBoxUseEscapeSequence.Checked;
			}
			else if (keyData == (Keys.Alt | Keys.R))
			{
				checkBoxUseRegular.Checked = !checkBoxUseRegular.Checked;
				checkBoxUseRegular.Focus();
				mFind.findOption.useRegular = checkBoxUseRegular.Checked;
			}
			else if (keyData == (Keys.Alt | Keys.U))
			{
				FindDirUp.Checked = true;
				FindDirUp.Focus();
				mFind.findOption.findDir = FindOption.FindDirection.UP;
			}
			else if (keyData == (Keys.Alt | Keys.D))
			{
				FindDirDown.Checked = true;
				FindDirDown.Focus(); 
				mFind.findOption.findDir = FindOption.FindDirection.DOWN;
			}
			else if (keyData == (Keys.Alt | Keys.O))
			{
				buttonFindFirst_Click(this, null);
				mIsFindFirst = false;
			}
			else if (keyData == (Keys.Alt | Keys.F))
			{
				buttonFindNext_Click(this, null);
				mIsFindFirst = false;
			}
			else
			{
				return base.ProcessCmdKey(ref msg, keyData);
			}
			return true;
		}
	}
}
