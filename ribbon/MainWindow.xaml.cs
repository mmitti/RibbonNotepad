using RibbonNotepad;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
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
    public partial class MainWindow : Window
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
            Init();
        }

        private void Init(){
            if (note.New())
			{
//				onStatusTextUpdate(this, "Ready");
			}
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
    }
}
