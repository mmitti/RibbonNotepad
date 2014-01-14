using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace RibbonNotepad
{
	public class Find
	{
		private NotepadTextBox mTextBox;
		public FindOption findOption;
		private FindResult mFindResult;
		private int mCurrentIndex;
		public event Events.StatusTextUpdateEvent statusTextUpdate;
		private Boolean mIsFound;
		public Boolean isFound { get { return mIsFound; } }
		public FindResult result { get { return mFindResult; } }

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
			if (findOption.findDir == FindOption.FindDirection.UP && !findOption.useRegular) textFind(mTextBox.Text.Length);
			else textFind(0);
		}

		public void findNext()
		{
			if (findOption.findDir == FindOption.FindDirection.UP && !findOption.useRegular) textFind(mTextBox.SelectionStart - mTextBox.SelectionLength);//TODO 修正
			else textFind(mTextBox.SelectionStart + mTextBox.SelectionLength);
		}

		private void textFind(int s)
		{
			statusTextUpdate(this, "");
			mIsFound = true;
			mFindResult = find(s, findOption.text);
			if (mFindResult.success)
			{
				mTextBox.Select(mFindResult.index, mFindResult.length);
				mTextBox.ScrollToCaret();
			}
			else{
				statusTextUpdate(this, findOption.text + " が見つかりませんでした。");
				System.Media.SystemSounds.Beep.Play();
				mIsFound = false;	
			}
		}

		protected FindResult find(int s, String text)
		{
			if (s < 0 || s > mTextBox.Text.Length) return new FindResult(false);
			if (findOption.useRegular)
			{
				RegexOptions ropt = RegexOptions.IgnoreCase;
				if (findOption.caseSensitive) ropt = RegexOptions.None;
				Regex r = new Regex(text, ropt);
				Match m = r.Match(mTextBox.Text, s);
				return new FindResult(m);
			}
			if (findOption.useEscapeSequence) text = text.Replace("\\n", "\r\n").Replace("\\t", "\t").Replace("\\\\", "\\");
			FindResult ret = new FindResult();
			StringComparison sopt = StringComparison.OrdinalIgnoreCase;
			if (findOption.caseSensitive) sopt = StringComparison.Ordinal;
			if (findOption.findDir == FindOption.FindDirection.UP) ret.index = mTextBox.Text.LastIndexOf(text, s, sopt);
			else　ret.index = mTextBox.Text.IndexOf(text, s, sopt);
			ret.success = ret.index != -1;
			ret.value = text;
			ret.length = text.Length;
			return ret;
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

	public class FindResult
	{
		public Boolean success { get; set; }
		public int index { get; set; }
		public int length { get; set; }
		public String value { get; set; }
		public FindResult() { }
		public FindResult(Boolean success)
		{
			this.success = success;
		}
		public FindResult(Match m)
		{
			this.success = m.Success;
			this.index = m.Index;
			this.length = m.Length;
			this.value = m.Value;
		}
	}
}
