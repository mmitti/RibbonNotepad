using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
// TODO
// ステータスバー 初期化
// ファイル
// -エンコード＋改行コード
// -印刷
// 編集
// 書式

namespace RibbonNotepad
{
	public partial class NotepadForm : Form
	{
		public readonly String ASSEMBLY_NAME;
		private Notepad notepad;
		private ToLineDialog mToLineDialog;
		private FindDialog mFindDialog;
		private ReplaceDialog mReplaceDialog;
		private Find mFind;
		private Replace mReplace;


		public NotepadForm()
		{
			InitializeComponent();
			mFind = new Find(textBox1);
			mFind.statusTextUpdate += new Events.StatusTextUpdateEvent(onStatusTextUpdate);
			mFindDialog = new FindDialog(mFind);
			mReplace = new Replace(mFind, textBox1);
			mReplaceDialog = new ReplaceDialog(mReplace);
			textBox1.CaretChanged += new EventHandler(OnRowColChanged);
			textBox1.StatusTextChanged += new Events.StatusTextUpdateEvent(onStatusTextUpdate);
			mToLineDialog = new ToLineDialog();
			ASSEMBLY_NAME = System.Reflection.Assembly.GetExecutingAssembly().GetName().Name;
			String filter = "テキスト文章 (*.txt)|*.txt|C/C++ソースファイル(*.c; *.cpp)|*.c;*.cpp|すべてのファイル (*.*)|*.*";
			openFileDialog.Title = "開く";
			openFileDialog.Filter = filter;
			saveFileDialog.Title = "名前を付けて保存";
			saveFileDialog.Filter = filter;
			onStatusTextUpdate(this, "Ready");

			notepad = new Notepad(this.textBox1);
			notepad.statusTextUpdateEvent += new Events.StatusTextUpdateEvent(onStatusTextUpdate);
			notepad.windowCaptionChangedEvent += new Events.WindowCaptionChangedEvent(onWindowCaptionChanged);
			notepad.fileOpenHandler = new FileDialogHandler.FileOpenHandler(OpenFile);
			notepad.fileSaveHandler = new FileDialogHandler.FileSaveHandler(SaveFile);
			init();
		}

		private void init()
		{
			if (notepad.New())
			{
			}
		}

		private void onWindowCaptionChanged(object sender, String caption){
			this.Text = ASSEMBLY_NAME +" - "+caption;
		}

		private void onStatusTextUpdate(object sender, String text)
		{
			toolStripStatusLabel.Text = text;
		}

		private FileDialogHandler.Result OpenFile()
		{
			openFileDialog.FileName = "";
			openFileDialog.FilterIndex = 1;
			if (openFileDialog.ShowDialog() == DialogResult.OK) return new FileDialogHandler.Result(openFileDialog.FileName);
			return FileDialogHandler.CANCEL;
		}

		private FileDialogHandler.Result SaveFile()
		{

			saveFileDialog.FileName = "*.txt";
			saveFileDialog.FilterIndex = 1;
			if (saveFileDialog.ShowDialog() == DialogResult.OK) return new FileDialogHandler.Result(saveFileDialog.FileName);
			return FileDialogHandler.CANCEL;
		}

		private void menu_MenuDeactivate(object sender, EventArgs e)
		{
			onStatusTextUpdate(this, "Ready");
		}


		private void menu_MouseEnter(object sender, EventArgs e)
		{
			onStatusTextUpdate(this,
				RibbonNotepad.Properties.Resources.ResourceManager.GetString("StatusText" + ((ToolStripMenuItem)sender).Name)); 

		}

		private void FileMenuItemExit_MouseEnter(object sender, EventArgs e)
		{
			onStatusTextUpdate(this, ASSEMBLY_NAME + "を終了");
		}

		private void FileMenuItemNew_Click(object sender, EventArgs e)
		{
			init();
		}

		private void FileMenuItemOpen_Click(object sender, EventArgs e)
		{
			notepad.Open();
		}

		private void FileMenuItemSave_Click(object sender, EventArgs e)
		{
			notepad.Save();
		}

		private void FileMenuItemSaveAs_Click(object sender, EventArgs e)
		{
			notepad.SaveAs();
		}

		private void FileMenuItemExit_Click(object sender, EventArgs e)
		{
			this.Close();
		}

		private void EditMenuItemUndo_Click(object sender, EventArgs e)
		{
			if (textBox1.CanUndo)
			{
				textBox1.Undo();
				textBox1.ClearUndo();
				EditMenuItemUndo.Enabled = false;
			}
		}

		private void EditMenuItemCut_Click(object sender, EventArgs e)
		{
			if (textBox1.SelectionLength > 0)
			{
				textBox1.Cut();
			}
		}

		private void EditMenuItemCopy_Click(object sender, EventArgs e)
		{
			if (textBox1.SelectionLength > 0)
			{
				textBox1.Copy();
			}
		}

		private void EditMenuItemPaste_Click(object sender, EventArgs e)
		{
			textBox1.Paste();
		}

		private void EditMenuItemDel_Click(object sender, EventArgs e)
		{
			if (textBox1.SelectionLength > 0)
			{
				textBox1.SelectedText = "";
			}
		}

		private void EditMenuItemSelectAll_Click(object sender, EventArgs e)
		{
			textBox1.SelectionStart = 0;
			textBox1.SelectionLength = textBox1.TextLength;
		}

		private void EditMenu_DropDownOpened(object sender, EventArgs e)
		{
			//TODO 項目更新
			bool text_menu_item_enable = false;
			if (textBox1.SelectionLength > 0)
			{
				text_menu_item_enable = true;
			}

			this.EditMenuItemCut.Enabled = text_menu_item_enable;
			this.EditMenuItemCopy.Enabled = text_menu_item_enable;
			this.EditMenuItemDel.Enabled = text_menu_item_enable;
			if (textBox1.CanUndo) EditMenuItemUndo.Enabled = true;
			else EditMenuItemUndo.Enabled = false;

			this.EditMenuItemFindNext.Enabled = textBox1.Text.Length > 0;
		}

		private void EditMenu_DropDownClosed(object sender, EventArgs e)
		{
			this.EditMenuItemFindNext.Enabled = true;
		}


		private void NotepadForm_FormClosing(object sender, FormClosingEventArgs e)
		{
			notepad.Exit(e);
		}

		private void OnRowColChanged(object sender, object e)
		{
			toolStripRawColLabel.Text = textBox1.getRow()+"行:"+textBox1.getCol()+"列";
		}

		private void EditMenuItemMoveToLine_Click(object sender, EventArgs e)
		{
			if (mToLineDialog.ShowDialog(textBox1.Lines.Length) == DialogResult.OK)
			{
				textBox1.ToLine((int)mToLineDialog.Value);
				textBox1.ScrollToCaret();
			}
		}

		private void EditMenuItemFind_Click(object sender, EventArgs e)
		{
			if (mFindDialog.Visible) return;
			if (mReplaceDialog.Visible) mReplaceDialog.Close();
			mFindDialog = new FindDialog(mFind);
			mFindDialog.Owner = this;
			mFindDialog.Show();
		}

		private void EditMenuItemFindNext_Click(object sender, EventArgs e)
		{
			if (textBox1.Text.Length == 0) return;
			if (mFind.canFindNext()) mFind.findNext();
			else EditMenuItemFind_Click(this, null);
		}

		private void EditMenuItemReplace_Click(object sender, EventArgs e)
		{
			if (mReplaceDialog.Visible) return;
			if (mFindDialog.Visible) mFindDialog.Close();
			mReplaceDialog = new ReplaceDialog(mReplace);
			mReplaceDialog.Owner = this;
			mReplaceDialog.Show();
		}

	


	}
}
