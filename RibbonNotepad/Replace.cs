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
		public Replace(Find f, NotepadTextBox t)
		{
			mFind = f;
			mTextBox = t;
		}

		public void replace()
		{
			//置換可能なら置換
			//検索
		}

		public void replaceAll()
		{
			//検索→置換を繰り返す
		}
	}
}
