using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RibbonNotepad
{
	class Find
	{
		private NotepadTextBox mTextBox;
		public FindOption findOption { get; set; }
		public Find(NotepadTextBox textbox)
		{
			mTextBox = textbox;
			findOption = new FindOption();
		}
	}

	struct FindOption
	{
		public enum FindDirection { UP, DOWN };
		public FindDirection findDir { get; set; }
		public String text { get; set; }
		public Boolean useRegular { get; set; }
		public Boolean useEscapeSequence { get; set; }
		public Boolean caseSensitive { get; set; }
		public FindOption()
		{
			findDir = FindDirection.DOWN;
			text = "";
			useEscapeSequence = false;
			useRegular = false;
			caseSensitive = false;
		}
	}
}
