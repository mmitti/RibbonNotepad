using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Windows.Controls;
using System.Windows;
namespace RibbonNotepad
{
	class Notepad
	{
		private TextBox mText;
		private Boolean mIsTextChanged;
		private String mFilePath;
		private String mFileName;
//		public event Events.WindowCaptionChangedEvent windowCaptionChangedEvent;
//		public event Events.StatusTextUpdateEvent statusTextUpdateEvent;
		public FileDialogHandler.FileOpenHandler fileOpenHandler;
		public FileDialogHandler.FileSaveHandler fileSaveHandler;

		public Notepad(TextBox box)
		{
			mText = box;
			mText.TextChanged += new TextChangedEventHandler(onTextChanged);
		}

		public Boolean New()
		{
			if (mIsTextChanged)
			{
				if (MessageBox.Show("変更されているけど保存するかい?", null, MessageBoxButton.YesNo, MessageBoxImage.Question) == MessageBoxResult.Yes)
				{
					if(!Save())return false;
				}
			}
			mText.Text = "";
			mFileName = "無題";
			mIsTextChanged = false;
			updateCaption();
			mFilePath = "";
			return true;
		}

		public Boolean Save()
		{
			//上書き保存
			//新規の場合はSaveAsを呼ぶ
			if (mFilePath == "")
			{
				return SaveAs();
			}
			else
			{
				writeFile(mFilePath);
				mIsTextChanged = false;
				updateCaption();
				return true;
			}
		}

		private void writeFile(String path)
		{
			StreamWriter sw = new StreamWriter(path, false, Encoding.GetEncoding("Shift_JIS"));
			sw.Write(mText.Text);
			sw.Flush();
			sw.Close();
			mFilePath = path;
			mFileName = Path.GetFileName(path);
//			statusTextUpdateEvent(this, "保存しました。");
		}

		private void readFile(String path)
		{
			if (!File.Exists(path)) {
				MessageBox.Show("ファイルが見つかりません", "エラー", MessageBoxButton.OK, MessageBoxImage.Error);
				return;
			}
			StreamReader sr = new StreamReader(path, Encoding.GetEncoding("Shift_JIS"));
			String s = sr.ReadToEnd();
			mText.Text = s;
			sr.Close();
			mFilePath = path;
			mFileName = Path.GetFileName(path);
//			statusTextUpdateEvent(this, "ファイルを開きました。");
		}

		public Boolean SaveAs()
		{
			//ダイアログを出してセーブ
			FileDialogHandler.Result r = fileSaveHandler();
			if (r.isCancel)
			{
				return false;
			}
			writeFile(r.filePath);
			return true;
		}

		public void Open()
		{
			if (mIsTextChanged)
			{
				if (MessageBox.Show("変更されているけど保存するかい?", null, MessageBoxButton.YesNo, MessageBoxImage.Question) == MessageBoxResult.Yes)
				{
					if (!Save()) return;
				}
			}			
			FileDialogHandler.Result r = fileOpenHandler();
			if (!r.isCancel)
			{
				readFile(r.filePath);
				mIsTextChanged = false;
				updateCaption();
			}
		}

		public void OpenAs(String path)
		{
			if (mIsTextChanged)
			{
				if (MessageBox.Show("変更されているけど保存するかい?", null, MessageBoxButton.YesNo, MessageBoxImage.Question) == MessageBoxResult.Yes)
				{
					if (!Save()) return;
				}
			}
			readFile(path);
			mIsTextChanged = false;
			updateCaption();
			
		}

		private void onTextChanged(object sender, System.EventArgs e)
		{
			mIsTextChanged = true;
			updateCaption();
		}

		private void updateCaption()
		{
//			if (mIsTextChanged) windowCaptionChangedEvent(this, mFileName + "*");
//			else windowCaptionChangedEvent(this, mFileName);
		}

        public void Exit(System.ComponentModel.CancelEventArgs e)
		{
            
			//TODO 終了していいか判定
			if (mIsTextChanged)
			{
				if (MessageBox.Show("変更されているけど保存するかい?", null, MessageBoxButton.YesNo, MessageBoxImage.Question) == MessageBoxResult.Yes)
				{
					Save();
				}
			}
		}
	}
}
