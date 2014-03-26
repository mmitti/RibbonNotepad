using RibbonNotepad;
using System;
using System.Collections.Generic;
using System.Linq;
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
        public MainWindow()
        {
            InitializeComponent();
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
            Init();

        }

        public void OnStatusTextUpdate(object sender, String text)
        {
            mainStatusText.Content = text;
        }

        public void OnWindowTextUpdate(object sender, String text)
        {
            this.Title = text;
        }

        private void Init(){
            if (note.New())
			{
				OnStatusTextUpdate(this, "Ready");
			}
            OnRibbonUpdate();
           
        }

        private void onTextSelectionChanged(object o, RoutedEventArgs a)
        {
            OnRibbonUpdate();
        }

        private void OnRibbonUpdate()
        {
            if (tbox.SelectionLength > 0) del.IsEnabled = true;
            else del.IsEnabled = false;
            if (tbox.TextWrapping == TextWrapping.NoWrap) wrap.IsChecked = false;
            else wrap.IsChecked = true;
            TabToLine.Visibility = Visibility.Hidden;
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
        }

        private  String[] DataTimeFormat = {   "HH:MM:ss", "HH時MM分ss秒", "yyyy/mm/dd",
                                                    "yyyy年mm月dd日", "yyyy/mm/dd HH:MM"};
       
        private void date_DropDownOpened(object sender, EventArgs e)
        {
            //更新
            dataItems.Items.Clear();
            foreach (String format in DataTimeFormat)
            {
                RibbonGalleryItem item = new RibbonGalleryItem();
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
    
        
        
    }
}
