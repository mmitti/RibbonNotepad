using RibbonNotepad;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Ribbon;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace ribbon
{
    /// <summary>
    /// MainWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class MainWindow : RibbonWindow
    {
        private Microsoft.Win32.OpenFileDialog mOpenDialog;
        private Microsoft.Win32.SaveFileDialog mSaveDialog;
        private RibbonNotepad.Notepad note;
        private Boolean mIsFindFirst;

        private String ASSEMBLY_NAME;

        private Find mFind;
        private Replace mReplace;
        public MainWindow()
        {
            Notif.Notification.TryCreateShortcut();
            InitializeComponent();

            mFind = new Find(tbox);
            mFind.statusTextUpdate += new RibbonNotepad.Events.StatusTextUpdateEvent(OnStatusTextUpdate);
            mReplace = new Replace(mFind, tbox);
            mReplace.statusTextUpdate += new RibbonNotepad.Events.StatusTextUpdateEvent(OnStatusTextUpdate);
            mIsFindFirst = false;

            ASSEMBLY_NAME = System.Reflection.Assembly.GetExecutingAssembly().GetName().Name;
			

            String filter = "テキスト文章 (*.txt)|*.txt|C/C++ソースファイル(*.c; *.cpp)|*.c;*.cpp|すべてのファイル (*.*)|*.*";
            mOpenDialog = new Microsoft.Win32.OpenFileDialog();
            mSaveDialog = new Microsoft.Win32.SaveFileDialog();
            mOpenDialog.Title = "開く";
            mOpenDialog.Filter = filter;
            mSaveDialog.Title = "名前を付けて保存";
            mSaveDialog.Filter = filter;
            note = new RibbonNotepad.Notepad(tbox);
            note.fileOpenHandler = new FileDialogHandler.FileOpenHandler(OpenFile);
            note.fileSaveHandler = new FileDialogHandler.FileSaveHandler(SaveFile);
            note.statusTextUpdateEvent += new RibbonNotepad.Events.StatusTextUpdateEvent(OnStatusTextUpdate);
            note.windowCaptionChangedEvent += new RibbonNotepad.Events.WindowCaptionChangedEvent(OnWindowTextUpdate);
            tbox.SelectionChanged += new RoutedEventHandler(onTextSelectionChanged);
            finddirdown.IsChecked = true;

            Init();

        }

        public void OnStatusTextUpdate(object sender, String text)
        {
            mainStatusText.Content = text;
        }

        public void OnWindowTextUpdate(object sender, String text)
        {
            this.Title = ASSEMBLY_NAME+" - "+text;
        }

        private void Init(){
            if (note.New())
			{
				OnStatusTextUpdate(this, "Ready");
                tbox.SelectionStart = 0;
                tbox.SelectionLength = 0;
                tbox.Focus();
			}
            OnRibbonUpdate();

            Notif.Notification.notif("RibbonNotepad", "Ready");
        }

        private void onTextSelectionChanged(object o, RoutedEventArgs a)
        {
            OnRibbonUpdate();
            updateStatusBar();
        }

        private void OnRibbonUpdate()
        {
            if (tbox.SelectionLength > 0) del.IsEnabled = true;
            else del.IsEnabled = false;
            if (tbox.TextWrapping == TextWrapping.NoWrap) wrap.IsChecked = false;
            else wrap.IsChecked = true;
            if (StatusBar.Visibility == Visibility.Visible) status.IsChecked = true;
            else status.IsChecked = false;
            TabToLine.Visibility = Visibility.Hidden;
            updateStatusBar();
            Boolean isCanFind = textFind.Text.Length > 0;
            findNext.IsEnabled = isCanFind && mFind.canFindNext();
            findFirst.IsEnabled = isCanFind;
            Boolean isCanReplace = textReplace.Text.Length > 0;
            replace.IsEnabled = replaceall.IsEnabled = isCanReplace;
        }

        private void updateStatusBar(){
            if (tbox.SelectionLength > 0)
            {
                statusColRow.Content = "文字選択中:" + tbox.SelectionLength;
            }
            else if (tbox.TextWrapping == TextWrapping.NoWrap)
            {
                int l = tbox.GetLineIndexFromCharacterIndex(tbox.SelectionStart);
                int lstart = tbox.GetCharacterIndexFromLineIndex(l);
                if (lstart < 0) lstart = 0;
                int r = tbox.SelectionStart - lstart;
                if (r < 0) r = 0;
                if (l < 0) l = 0;
                l++; r++;
                statusColRow.Content = "行:" + l + "列:" + r;
            }
            else
            {
                statusColRow.Content = "";
            }
            OnStatusTextUpdate(this, "Ready");
        }

        private FileDialogHandler.Result OpenFile()
        {
            mOpenDialog.FileName = "";
            mOpenDialog.FilterIndex = 1;
            Nullable<bool> result = mOpenDialog.ShowDialog();
            if (result == true)return new FileDialogHandler.Result(mOpenDialog.FileName);
            return FileDialogHandler.CANCEL;
        }

        private FileDialogHandler.Result SaveFile()
        {

            mSaveDialog.FileName = "*.txt";
            mSaveDialog.FilterIndex = 1;
            if (mSaveDialog.ShowDialog() == true) return new FileDialogHandler.Result(mSaveDialog.FileName);
            return FileDialogHandler.CANCEL;
        }

        private void new_Click(object sender, RoutedEventArgs e)
        {
            Init();
        }

        private void open_Click(object sender, RoutedEventArgs e)
        {
            note.Open();
        }

        private void save_Click(object sender, RoutedEventArgs e)
        {
            note.Save();
        }

        private void saveas_Click(object sender, RoutedEventArgs e)
        {
            note.SaveAs();
        }

        private void exit_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            note.Exit(e);
        }

        private void del_Click(object sender, RoutedEventArgs e)
        {
            if (tbox.SelectionLength > 0)
            {
                tbox.SelectedText = "";
            }
        }

        private void all_Click(object sender, RoutedEventArgs e)
        {
            tbox.SelectionStart = 0;
            tbox.SelectionLength = tbox.Text.Length;
        }

        private void wrap_Click(object sender, RoutedEventArgs e)
        {
            if (wrap.IsChecked==true) tbox.TextWrapping = TextWrapping.Wrap;
            else tbox.TextWrapping = TextWrapping.NoWrap;
            updateStatusBar();
        }

        private  String[] DataTimeFormat = {   "HH:MM:ss", "HH時MM分ss秒", "yyyy/mm/dd",
                                                    "yyyy年mm月dd日", "yyyy/mm/dd HH:MM"};
       
        private void date_DropDownOpened(object sender, EventArgs e)
        {
            //更新
            dataItems.Items.Clear();
            int i = 1;
            foreach (String format in DataTimeFormat)
            {
                RibbonGalleryItem item = new RibbonGalleryItem();
                item.MouseEnter += new MouseEventHandler(help_Enter);
                item.MouseLeave += new MouseEventHandler(help_Leave);
                item.Uid = "形式" + i + " : " + DateTime.Now.ToString(format);
                item.Content = format;
                dataItems.Items.Add(item);
                item.Selected += new RoutedEventHandler((o, arg) =>
                {
                    String s = (String)((RibbonGalleryItem)o).Content;
                    int l = tbox.SelectionStart;
                    tbox.SelectedText = DateTime.Now.ToString(s);
                    tbox.SelectionStart = l + tbox.SelectionLength;
                    tbox.SelectionLength = 0;

                });
                i++;
            }
        }

        private void showtoline_Click(object sender, RoutedEventArgs e)
        {
            TabToLine.Visibility = Visibility.Visible;
            TabToLine.Focus();
            RibbonHost.SelectedItem = TabToLine;
        }

        private void toLine_Click(object sender, RoutedEventArgs e)
        {
            String text = LineBox.Text;
            try
            {
                int l = Int32.Parse(text);
                l--;
                if (l < 0 || l >= tbox.LineCount) throw new FormatException();

                tbox.ScrollToLine(l);

                tbox.Select(tbox.GetCharacterIndexFromLineIndex(l), 0);
            }
            catch (Exception er)
            {
                OnStatusTextUpdate(this, "行番号の形式が不正です");
                System.Media.SystemSounds.Exclamation.Play();
            }
        }
        
        private void resetStatusText(object sender, KeyEventArgs e)
        {
            OnStatusTextUpdate(sender, "Ready");
        }
      
        private void RibbonHost_PreviewMouseDown(object sender, MouseButtonEventArgs e)
        {
            OnStatusTextUpdate(sender, "Ready");
        }

        private void status_Click(object sender, RoutedEventArgs e)
        {
            if (status.IsChecked == true) StatusBar.Visibility = Visibility.Visible;
            else StatusBar.Visibility = Visibility.Collapsed;
        }

        private void ThumbButtonInfo_Click(object sender, EventArgs e)
        {
            note.Save();
        }

        private void textFind_TextChanged(object sender, TextChangedEventArgs e)
        {
            mIsFindFirst = false;
            mFind.findOption.text = textFind.Text;
            OnRibbonUpdate();
        }

        private void textReplace_TextChanged(object sender, TextChangedEventArgs e)
        {
            mIsFindFirst = false;
            mReplace.replaceText = textReplace.Text;
            OnRibbonUpdate();
        }

        private void findFirst_Click(object sender, RoutedEventArgs e)
        {
            if (!mFind.isFound) mIsFindFirst = false;
            if (!mIsFindFirst)
            {
                mFind.findFirst();
                mIsFindFirst = true;
            }
            else mFind.findNext();
        }

        private void findNext_Click(object sender, RoutedEventArgs e)
        {
            mFind.findNext();
        }

        private void replace_Click(object sender, RoutedEventArgs e)
        {
            mReplace.replace();
        }

        private void replaceall_Click(object sender, RoutedEventArgs e)
        {
            mReplace.replaceAll();
        }

        private void finddir_Checked(object sender, RoutedEventArgs e)
        {
            mIsFindFirst = false;
            if (((RibbonRadioButton)sender).IsChecked == true)
            {
                if(sender.Equals(finddirup))mFind.findOption.findDir = FindOption.FindDirection.UP;
                else mFind.findOption.findDir = FindOption.FindDirection.DOWN;
            }
        }


        private void findOptionIdentifyCharSize_Click(object sender, RoutedEventArgs e)
        {
            mIsFindFirst = false;
            mFind.findOption.caseSensitive = (findOptionIdentifyCharSize.IsChecked == true);
        }

        private void findOptionUseEscSeq_Click(object sender, RoutedEventArgs e)
        {
            mIsFindFirst = false;
            mFind.findOption.useEscapeSequence = (findOptionUseEscSeq.IsChecked == true);

        }

        private void findOptionUseRegural_Click(object sender, RoutedEventArgs e)
        {
            mIsFindFirst = false;
            mFind.findOption.useRegular = (findOptionUseRegural.IsChecked == true);
            findOptionUseEscSeq.IsEnabled = findOptionIdentifyCharSize.IsEnabled = (findOptionUseRegural.IsChecked == false);
        }

        private void help_Enter(object sender, MouseEventArgs e)
        {
            UIElement elm = (UIElement)sender;
            //UIDでstringを探してなければそのまま出す
            String text = null;
            try
            {
                text = ribbon.Properties.Resources.ResourceManager.GetString("StatusText" + elm.Uid);
            }
            catch (Exception ex) { }
            if (text == null) text = elm.Uid;
            OnStatusTextUpdate(sender, text);
        }

        private void help_Leave(object sender, MouseEventArgs e)
        {
            OnStatusTextUpdate(sender, "Ready");
        }

        private void ThumbButtonInfo_Click_1(object sender, EventArgs e)
        {
            if (note.IsTextChanged)
                Process.Start(Assembly.GetEntryAssembly().Location);
            else this.Focus();
        }
        
    }
}
