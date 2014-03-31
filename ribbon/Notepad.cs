using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Windows.Controls;
using System.Windows;
using System.Threading.Tasks;
namespace RibbonNotepad
{
	class Notepad
	{
		private TextBox mText;
		private Boolean mIsTextChanged;
		private String mFilePath;
		private String mFileName;
		public event Events.WindowCaptionChangedEvent windowCaptionChangedEvent;
		public event Events.StatusTextUpdateEvent statusTextUpdateEvent;
		public FileDialogHandler.FileOpenHandler fileOpenHandler;
		public FileDialogHandler.FileSaveHandler fileSaveHandler;
        public Boolean IsTextChanged { get {return mIsTextChanged; } }

        private Tick mTick;
		public Notepad(TextBox box)
		{
			mText = box;
			mText.TextChanged += new TextChangedEventHandler(onTextChanged);
            mTick = new Tick();
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
            mTick.init();
            mTick.start();
			return true;
		}

		public Boolean Save()
		{
            mTick.init();
            mTick.start();
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


        //一定時間ごとに通知を出すうざいやつ
        private class Tick
        {
            private long mStart;
            private Boolean mIsEnable;
            private const long WAIT_TIME = 5 * 60;
            public void init(){
                mStart = DateTime.Now.Ticks / 10000000;
            }
            public async void start()
            {
                mIsEnable = true;

                while (mIsEnable)
                {
                    await Task.Delay(3000);
                    if (DateTime.Now.Ticks / 10000000 > mStart + WAIT_TIME) ribbon.Notif.Notification.notif("RibbonNotepad Warning", "ファイルを保存してください。");
                }
            }

            public void stop()
            {
                mIsEnable = false;
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
			statusTextUpdateEvent(this, "保存しました。");
            ribbon.Notif.Notification.notif("RibbonNotepad", "保存完了");
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
			statusTextUpdateEvent(this, "ファイルを開きました。");
            ribbon.Notif.Notification.notif("RibbonNotepad", "読み込み完了");
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
			if (mIsTextChanged) windowCaptionChangedEvent(this, mFileName + "*");
			else windowCaptionChangedEvent(this, mFileName);
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
