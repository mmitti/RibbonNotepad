using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RibbonNotepad
{
	class FileDialogHandler
	{
		public delegate Result FileOpenHandler();
		public delegate Result FileSaveHandler();
		public struct Result
		{
			

			public readonly String filePath;
			public readonly Boolean isCancel;
			public Result(String path){
				filePath = path;
				isCancel = false;
			}
			public Result(Boolean cancel){
				isCancel = cancel;
				filePath = "";
			}
		}

		public static readonly Result CANCEL = new Result(true);
	}
}
