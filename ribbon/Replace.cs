using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Text.RegularExpressions;
using System.Windows.Controls;

namespace RibbonNotepad
{
	public class Replace
	{
		private Find mFind;
		public event Events.StatusTextUpdateEvent statusTextUpdate;
		private TextBox mTextBox;
		public Find find { get { return mFind; } }
		public String replaceText;
		public Replace(Find f, TextBox t)
		{
			mFind = f;
			mTextBox = t;
		}

		public void replace()
		{
			if (mFind.isFound)
			{
				replaceSelectedText();
                statusTextUpdate(this, "置換を行いました。");
                System.Media.SystemSounds.Beep.Play();
				//正規表現の時だけ別処理
			}
			mFind.findNext();
		}

        private void replaceSelectedText()
        {
            int s = mTextBox.SelectionStart;
			String tmp = "";
			if (mFind.findOption.useRegular)
			{
				tmp = mTextBox.SelectedText;
				RegexOptions ropt = RegexOptions.IgnoreCase;
				if (mFind.findOption.caseSensitive) ropt = RegexOptions.None;
				Regex r = new Regex(mFind.findOption.text, ropt);
				tmp = r.Replace(tmp, replaceText);
			}
			else tmp = replaceText;
			mTextBox.SelectedText = tmp;
			mTextBox.SelectionStart = s;
			mTextBox.SelectionLength = tmp.Length;
        }

		public void replaceAll()
		{

            mTextBox.SelectionStart = 0;
            mTextBox.SelectionLength = mTextBox.Text.Length;
			//検索→置換を繰り返す
			if (mFind.findOption.useRegular)
			{
				RegexOptions ropt = RegexOptions.IgnoreCase;
				if (mFind.findOption.caseSensitive) ropt = RegexOptions.None;
				Regex r = new Regex(mFind.findOption.text, ropt);
				mTextBox.Text = r.Replace(mTextBox.Text, replaceText);
			}
			else
			{
				mTextBox.Text = mTextBox.Text.Replace(mFind.findOption.text, replaceText);
				
			}
            statusTextUpdate(this, "置換を行いました。");
            System.Media.SystemSounds.Beep.Play();
			//正規表現の時だけ別処理
			//成功時にcreateundo
			//ステータスバー更新 件数を出したいからループで
		}
	}
}
