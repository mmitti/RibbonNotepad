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
			textBox1 = find.findOption.text;
		}

		public new void Show()
		{
			//if (Visible) return;
			mIsFindFirst = false;
			base.Show();
		}

		private void onFindTextChanged(object sender, EventArgs args)
		{
			mIsFindFirst = false;
		}
	 

		private void buttonFindFirst_Click(object sender, EventArgs e)
		{
			if (!mIsFindFirst)
			{
				//検索開始位置をいじる
				mIsFindFirst = true;
			}
			//次を検索を呼ぶ
		}

		private void buttonFindNext_Click(object sender, EventArgs e)
		{

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
				checkBoxCaseSensitive.Checked = !checkBoxUseEscapeSequence.Checked;
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
				//先頭から検索
			}
			else if (keyData == (Keys.Alt | Keys.F))
			{
				//次を検索
			}
			else
			{
				return base.ProcessCmdKey(ref msg, keyData);
			}
			return true;
		}
	}
}
