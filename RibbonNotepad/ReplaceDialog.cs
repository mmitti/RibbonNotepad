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
	public partial class ReplaceDialog : Form
	{
		private Replace mReplace;
		private Boolean mIsFindFirst;
		public ReplaceDialog(Replace r)
		{
			InitializeComponent();
			mReplace = r;
			textBox1.TextChanged += new EventHandler(onFindTextChanged);
			checkBoxCaseSensitive.Checked = mReplace.find.findOption.caseSensitive;
			checkBoxUseEscapeSequence.Checked = mReplace.find.findOption.useEscapeSequence;
			checkBoxUseRegular.Checked = mReplace.find.findOption.useRegular;
			if (mReplace.find.findOption.findDir == FindOption.FindDirection.UP) FindDirUp.Checked = true;
			else FindDirDown.Checked = true;
			textBox1.Text = mReplace.find.findOption.text;

			checkBoxCaseSensitive.CheckedChanged += new EventHandler(onFindOptionCaseSensitiveChanged);
			checkBoxUseEscapeSequence.CheckedChanged += new EventHandler(onFindOptionUseEscapeSequenceChanged);
			checkBoxUseRegular.CheckedChanged += new EventHandler(onFindOptionUseRegualr);
			FindDirDown.CheckedChanged += new EventHandler(onFindOptionFindDir);
			FindDirUp.CheckedChanged += new EventHandler(onFindOptionFindDir);
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
			mReplace.find.findOption.text = textBox1.Text;
		}

		private void onFindOptionCaseSensitiveChanged(object sender, EventArgs args)
		{
			mIsFindFirst = false;
			mReplace.find.findOption.caseSensitive = checkBoxCaseSensitive.Checked;
		}

		private void onFindOptionUseEscapeSequenceChanged(object sender, EventArgs args)
		{
			mIsFindFirst = false;
			mReplace.find.findOption.useEscapeSequence = checkBoxUseEscapeSequence.Checked;
		}

		private void onFindOptionUseRegualr(object sender, EventArgs args)
		{
			mIsFindFirst = false;
			mReplace.find.findOption.useRegular = checkBoxUseRegular.Checked;
			checkBoxUseEscapeSequence.Enabled = groupFindDir.Enabled = !checkBoxUseRegular.Checked;
		}

		private void onFindOptionFindDir(object sender, EventArgs args)
		{
			mIsFindFirst = false;
			if (((RadioButton)sender).Checked)
			{
				if (sender == FindDirDown) mReplace.find.findOption.findDir = FindOption.FindDirection.DOWN;
				else mReplace.find.findOption.findDir = FindOption.FindDirection.UP;
			}
		}


		private void buttonFindFirst_Click(object sender, EventArgs e)
		{
			if (!mReplace.find.isFound) mIsFindFirst = false;
			if (!mIsFindFirst)
			{
				mReplace.find.findFirst();
				mIsFindFirst = true;
			}
			else mReplace.find.findNext();
		}

		private void buttonFindNext_Click(object sender, EventArgs e)
		{
			mReplace.find.findNext();
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
			else if (keyData == (Keys.Alt | Keys.P))
			{
				textBox2.Select(0, textBox2.Text.Length);
				textBox2.Focus();
			}
			else if (keyData == (Keys.Alt | Keys.C))
			{
				checkBoxCaseSensitive.Checked = !checkBoxCaseSensitive.Checked;
				checkBoxCaseSensitive.Focus();
			}
			else if (keyData == (Keys.Alt | Keys.E))
			{
				checkBoxUseEscapeSequence.Checked = !checkBoxUseEscapeSequence.Checked;
				checkBoxUseEscapeSequence.Focus();
			}
			else if (keyData == (Keys.Alt | Keys.R))
			{
				checkBoxUseRegular.Checked = !checkBoxUseRegular.Checked;
				checkBoxUseRegular.Focus();
			}
			else if (keyData == (Keys.Alt | Keys.U))
			{
				FindDirUp.Checked = true;
				FindDirUp.Focus();
			}
			else if (keyData == (Keys.Alt | Keys.D))
			{
				FindDirDown.Checked = true;
				FindDirDown.Focus(); 
			}
			else if (keyData == (Keys.Alt | Keys.O))
			{
				buttonFindFirst_Click(this, null);
			}
			else if (keyData == (Keys.Alt | Keys.F))
			{
				buttonFindNext_Click(this, null);
			}
			else if (keyData == (Keys.Alt | Keys.A))
			{
				buttonReplaceAll_Click(this, null);
			}
			else if (keyData == (Keys.Alt | Keys.X))
			{
				buttonReplaceNext_Click(this, null);
			}
			else if (keyData == Keys.Escape)
			{
				this.Close();
			}
			else
			{
				return base.ProcessCmdKey(ref msg, keyData);
			}
			return true;
		}

		private void buttonReplaceNext_Click(object sender, EventArgs e)
		{

		}

		private void buttonReplaceAll_Click(object sender, EventArgs e)
		{

		}

	}
}
