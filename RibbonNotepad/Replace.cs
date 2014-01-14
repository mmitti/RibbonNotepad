using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RibbonNotepad
{
	public class Replace
	{
		private Find mFind;
		private NotepadTextBox mTextBox;
		public Find find { get { return mFind; } }
		public String replaceText;
		public Replace(Find f, NotepadTextBox t)
		{
			mFind = f;
			mTextBox = t;
		}

		public void replace()
		{
			if (mFind.isFound)
			{
				int s = mTextBox.SelectionStart;
				mTextBox.SelectedText = replaceText;
				mTextBox.SelectionStart = s;
				mTextBox.SelectionLength = replaceText.Length;
				//正規表現の時だけ別処理
			}
			mFind.findNext();
		}

		public void replaceAll()
		{
			//検索→置換を繰り返す
			mTextBox.Text.Replace(mFind.findOption.text, replaceText);
			//正規表現の時だけ別処理
		}
	}
}
