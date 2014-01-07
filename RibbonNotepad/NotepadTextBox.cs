using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace RibbonNotepad
{
	public partial class NotepadTextBox : TextBox
	{
		public event EventHandler CaretChanged;
		[System.Runtime.InteropServices.DllImportAttribute("User32.DLL")]

		public static extern int SendMessage(IntPtr hWnd, uint msg, int wParam, int lParam);
		public const int EM_LINEINDEX = 0x00BB;
		private const int EM_LINEFROMCHAR = 0xC9;
		public NotepadTextBox()
		{
			InitializeComponent();
		}

		public void ToLine(int line)
		{
			int pos = SendMessage(this.Handle, EM_LINEINDEX, line-1, 0);
			this.Select(pos, 0);
		}

		public int getRow()
		{
			return SendMessage(this.Handle, EM_LINEFROMCHAR, -1, 0) + 1;
		}

		public int getCol()
		{
			int lineIndex = SendMessage(this.Handle, EM_LINEINDEX, -1, 0);
			return this.SelectionStart - lineIndex + 1;
		}

		protected override void OnKeyDown(KeyEventArgs e)
		{
			base.OnKeyDown(e);
			CaretChanged(this, null);
		}

		protected override void OnKeyUp(KeyEventArgs e)
		{
			base.OnKeyUp(e);
			CaretChanged(this, null);
		}

		protected override void OnTextChanged(EventArgs e)
		{
			base.OnTextChanged(e);
			CaretChanged(this, null);
		}

		protected override void OnKeyPress(KeyPressEventArgs e)
		{
			base.OnKeyPress(e);
			CaretChanged(this, null);
		}

	}
}
