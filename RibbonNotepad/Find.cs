using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RibbonNotepad
{
	public class Find
	{
		private NotepadTextBox mTextBox;
		public FindOption findOption;
		private int mCurrentIndex;
		public event Events.StatusTextUpdateEvent statusTextUpdate;
		private Boolean mIsFound;
		public Boolean isFound { get { return mIsFound; } }

		public Find(NotepadTextBox textbox)
		{
			mTextBox = textbox;
			findOption = new FindOption();
			findOption.findDir = FindOption.FindDirection.DOWN;
			findOption.text = "";
			findOption.useEscapeSequence = false;
			findOption.useRegular = false;
			findOption.caseSensitive = false;
			mIsFound = false;
		}

		//先頭から検索をするときに呼ぶ　カーソルが自動的に移動する；
		public void findFirst()
		{
			textFind(0);
		}

		public void findNext()
		{
			textFind(mTextBox.SelectionStart + mTextBox.SelectionLength);//TODO 修正
		}

		private void textFind(int s)
		{
			statusTextUpdate(this, "");
			mIsFound = true;
			int i = find(s, findOption.text);
			if (i == -1)
			{
				statusTextUpdate(this, findOption.text + " が見つかりませんでした。");
				System.Media.SystemSounds.Beep.Play();
				mIsFound = false;
			}
			else mTextBox.Select(i, findOption.text.Length);
		}

		protected int find(int s, String text)
		{
			return mTextBox.Text.IndexOf(text, s);
		}

		public Boolean canFindNext()
		{
			if (findOption.text.Equals("")) return false;
			if (!mIsFound) return false;
			return true;
		}
	}

	public struct FindOption
	{
		public enum FindDirection { UP, DOWN };
		public FindDirection findDir { get; set; }
		public String text { get; set; }
		public Boolean useRegular { get; set; }
		public Boolean useEscapeSequence { get; set; }
		public Boolean caseSensitive { get; set; }

	}
}
