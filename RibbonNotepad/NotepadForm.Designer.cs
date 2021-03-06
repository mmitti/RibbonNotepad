﻿namespace RibbonNotepad
{
	partial class NotepadForm
	{
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		/// <param name="disposing">マネージ リソースが破棄される場合 true、破棄されない場合は false です。</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows フォーム デザイナーで生成されたコード

		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		private void InitializeComponent()
		{
            this.menu = new System.Windows.Forms.MenuStrip();
            this.FileMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.FileMenuItemNew = new System.Windows.Forms.ToolStripMenuItem();
            this.FileMenuItemOpen = new System.Windows.Forms.ToolStripMenuItem();
            this.FileMenuItemSave = new System.Windows.Forms.ToolStripMenuItem();
            this.FileMenuItemSaveAs = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.FileMenuItemPageSetting = new System.Windows.Forms.ToolStripMenuItem();
            this.FileMenuItemPrint = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.FileMenuItemExit = new System.Windows.Forms.ToolStripMenuItem();
            this.EditMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.EditMenuItemUndo = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.EditMenuItemCut = new System.Windows.Forms.ToolStripMenuItem();
            this.EditMenuItemCopy = new System.Windows.Forms.ToolStripMenuItem();
            this.EditMenuItemPaste = new System.Windows.Forms.ToolStripMenuItem();
            this.EditMenuItemDel = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.EditMenuItemFind = new System.Windows.Forms.ToolStripMenuItem();
            this.EditMenuItemFindNext = new System.Windows.Forms.ToolStripMenuItem();
            this.EditMenuItemReplace = new System.Windows.Forms.ToolStripMenuItem();
            this.EditMenuItemMoveToLine = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
            this.EditMenuItemSelectAll = new System.Windows.Forms.ToolStripMenuItem();
            this.EditMenuItemDayAndData = new System.Windows.Forms.ToolStripMenuItem();
            this.OptionMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.OptionMenuItemWrap = new System.Windows.Forms.ToolStripMenuItem();
            this.OptionMenuItemFont = new System.Windows.Forms.ToolStripMenuItem();
            this.ViewMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.ViewMenuItemStatus = new System.Windows.Forms.ToolStripMenuItem();
            this.HelpMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.HelpMenuItemVersion = new System.Windows.Forms.ToolStripMenuItem();
            this.statusStrip = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripSeparator6 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripRawColLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.textBox1 = new RibbonNotepad.NotepadTextBox();
            this.menu.SuspendLayout();
            this.statusStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // menu
            // 
            this.menu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.FileMenu,
            this.EditMenu,
            this.OptionMenu,
            this.ViewMenu,
            this.HelpMenu});
            this.menu.Location = new System.Drawing.Point(0, 0);
            this.menu.Name = "menu";
            this.menu.Size = new System.Drawing.Size(464, 24);
            this.menu.TabIndex = 0;
            this.menu.Text = "menu";
            this.menu.MenuDeactivate += new System.EventHandler(this.menu_MenuDeactivate);
            // 
            // FileMenu
            // 
            this.FileMenu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.FileMenuItemNew,
            this.FileMenuItemOpen,
            this.FileMenuItemSave,
            this.FileMenuItemSaveAs,
            this.toolStripSeparator1,
            this.FileMenuItemPageSetting,
            this.FileMenuItemPrint,
            this.toolStripSeparator2,
            this.FileMenuItemExit});
            this.FileMenu.Name = "FileMenu";
            this.FileMenu.Size = new System.Drawing.Size(70, 20);
            this.FileMenu.Text = "ファイル(&F)";
            this.FileMenu.MouseEnter += new System.EventHandler(this.menu_MouseEnter);
            this.FileMenu.MouseLeave += new System.EventHandler(this.menu_MenuDeactivate);
            // 
            // FileMenuItemNew
            // 
            this.FileMenuItemNew.Name = "FileMenuItemNew";
            this.FileMenuItemNew.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.N)));
            this.FileMenuItemNew.Size = new System.Drawing.Size(228, 22);
            this.FileMenuItemNew.Text = "新規(&N)";
            this.FileMenuItemNew.Click += new System.EventHandler(this.FileMenuItemNew_Click);
            this.FileMenuItemNew.MouseEnter += new System.EventHandler(this.menu_MouseEnter);
            // 
            // FileMenuItemOpen
            // 
            this.FileMenuItemOpen.Name = "FileMenuItemOpen";
            this.FileMenuItemOpen.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.FileMenuItemOpen.Size = new System.Drawing.Size(228, 22);
            this.FileMenuItemOpen.Text = "開く(&O)...";
            this.FileMenuItemOpen.Click += new System.EventHandler(this.FileMenuItemOpen_Click);
            this.FileMenuItemOpen.MouseEnter += new System.EventHandler(this.menu_MouseEnter);
            // 
            // FileMenuItemSave
            // 
            this.FileMenuItemSave.Name = "FileMenuItemSave";
            this.FileMenuItemSave.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.FileMenuItemSave.Size = new System.Drawing.Size(228, 22);
            this.FileMenuItemSave.Text = "上書き保存(&S)";
            this.FileMenuItemSave.Click += new System.EventHandler(this.FileMenuItemSave_Click);
            this.FileMenuItemSave.MouseEnter += new System.EventHandler(this.menu_MouseEnter);
            // 
            // FileMenuItemSaveAs
            // 
            this.FileMenuItemSaveAs.Name = "FileMenuItemSaveAs";
            this.FileMenuItemSaveAs.ShortcutKeyDisplayString = "        ";
            this.FileMenuItemSaveAs.Size = new System.Drawing.Size(228, 22);
            this.FileMenuItemSaveAs.Text = "名前をつけて保存(&A)...";
            this.FileMenuItemSaveAs.Click += new System.EventHandler(this.FileMenuItemSaveAs_Click);
            this.FileMenuItemSaveAs.MouseEnter += new System.EventHandler(this.menu_MouseEnter);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(225, 6);
            // 
            // FileMenuItemPageSetting
            // 
            this.FileMenuItemPageSetting.Name = "FileMenuItemPageSetting";
            this.FileMenuItemPageSetting.Size = new System.Drawing.Size(228, 22);
            this.FileMenuItemPageSetting.Text = "ページ設定(&U)";
            this.FileMenuItemPageSetting.MouseEnter += new System.EventHandler(this.menu_MouseEnter);
            // 
            // FileMenuItemPrint
            // 
            this.FileMenuItemPrint.Name = "FileMenuItemPrint";
            this.FileMenuItemPrint.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.P)));
            this.FileMenuItemPrint.Size = new System.Drawing.Size(228, 22);
            this.FileMenuItemPrint.Text = "印刷(&P)...";
            this.FileMenuItemPrint.MouseEnter += new System.EventHandler(this.menu_MouseEnter);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(225, 6);
            // 
            // FileMenuItemExit
            // 
            this.FileMenuItemExit.Name = "FileMenuItemExit";
            this.FileMenuItemExit.ShortcutKeyDisplayString = "";
            this.FileMenuItemExit.Size = new System.Drawing.Size(228, 22);
            this.FileMenuItemExit.Text = "終了(&X)";
            this.FileMenuItemExit.Click += new System.EventHandler(this.FileMenuItemExit_Click);
            this.FileMenuItemExit.MouseEnter += new System.EventHandler(this.FileMenuItemExit_MouseEnter);
            // 
            // EditMenu
            // 
            this.EditMenu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.EditMenuItemUndo,
            this.toolStripSeparator3,
            this.EditMenuItemCut,
            this.EditMenuItemCopy,
            this.EditMenuItemPaste,
            this.EditMenuItemDel,
            this.toolStripSeparator4,
            this.EditMenuItemFind,
            this.EditMenuItemFindNext,
            this.EditMenuItemReplace,
            this.EditMenuItemMoveToLine,
            this.toolStripSeparator5,
            this.EditMenuItemSelectAll,
            this.EditMenuItemDayAndData});
            this.EditMenu.Name = "EditMenu";
            this.EditMenu.Size = new System.Drawing.Size(60, 20);
            this.EditMenu.Text = "編集(&E)";
            this.EditMenu.DropDownClosed += new System.EventHandler(this.EditMenu_DropDownClosed);
            this.EditMenu.DropDownOpened += new System.EventHandler(this.EditMenu_DropDownOpened);
            this.EditMenu.MouseEnter += new System.EventHandler(this.menu_MouseEnter);
            this.EditMenu.MouseLeave += new System.EventHandler(this.menu_MenuDeactivate);
            // 
            // EditMenuItemUndo
            // 
            this.EditMenuItemUndo.Name = "EditMenuItemUndo";
            this.EditMenuItemUndo.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Z)));
            this.EditMenuItemUndo.Size = new System.Drawing.Size(198, 22);
            this.EditMenuItemUndo.Text = "元に戻す(&U)";
            this.EditMenuItemUndo.Click += new System.EventHandler(this.EditMenuItemUndo_Click);
            this.EditMenuItemUndo.MouseEnter += new System.EventHandler(this.menu_MouseEnter);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(195, 6);
            // 
            // EditMenuItemCut
            // 
            this.EditMenuItemCut.Name = "EditMenuItemCut";
            this.EditMenuItemCut.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.X)));
            this.EditMenuItemCut.Size = new System.Drawing.Size(198, 22);
            this.EditMenuItemCut.Text = "切り取り(&T)";
            this.EditMenuItemCut.Click += new System.EventHandler(this.EditMenuItemCut_Click);
            this.EditMenuItemCut.MouseEnter += new System.EventHandler(this.menu_MouseEnter);
            // 
            // EditMenuItemCopy
            // 
            this.EditMenuItemCopy.Name = "EditMenuItemCopy";
            this.EditMenuItemCopy.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.C)));
            this.EditMenuItemCopy.Size = new System.Drawing.Size(198, 22);
            this.EditMenuItemCopy.Text = "コピー(&C)";
            this.EditMenuItemCopy.Click += new System.EventHandler(this.EditMenuItemCopy_Click);
            this.EditMenuItemCopy.MouseEnter += new System.EventHandler(this.menu_MouseEnter);
            // 
            // EditMenuItemPaste
            // 
            this.EditMenuItemPaste.Name = "EditMenuItemPaste";
            this.EditMenuItemPaste.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.V)));
            this.EditMenuItemPaste.Size = new System.Drawing.Size(198, 22);
            this.EditMenuItemPaste.Text = "貼り付け(&P)";
            this.EditMenuItemPaste.Click += new System.EventHandler(this.EditMenuItemPaste_Click);
            this.EditMenuItemPaste.MouseEnter += new System.EventHandler(this.menu_MouseEnter);
            // 
            // EditMenuItemDel
            // 
            this.EditMenuItemDel.Name = "EditMenuItemDel";
            this.EditMenuItemDel.ShortcutKeyDisplayString = "Del";
            this.EditMenuItemDel.Size = new System.Drawing.Size(198, 22);
            this.EditMenuItemDel.Text = "削除(L)";
            this.EditMenuItemDel.Click += new System.EventHandler(this.EditMenuItemDel_Click);
            this.EditMenuItemDel.MouseEnter += new System.EventHandler(this.menu_MouseEnter);
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            this.toolStripSeparator4.Size = new System.Drawing.Size(195, 6);
            // 
            // EditMenuItemFind
            // 
            this.EditMenuItemFind.Name = "EditMenuItemFind";
            this.EditMenuItemFind.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.F)));
            this.EditMenuItemFind.Size = new System.Drawing.Size(198, 22);
            this.EditMenuItemFind.Text = "検索(&F)...";
            this.EditMenuItemFind.Click += new System.EventHandler(this.EditMenuItemFind_Click);
            this.EditMenuItemFind.MouseEnter += new System.EventHandler(this.menu_MouseEnter);
            // 
            // EditMenuItemFindNext
            // 
            this.EditMenuItemFindNext.Name = "EditMenuItemFindNext";
            this.EditMenuItemFindNext.ShortcutKeys = System.Windows.Forms.Keys.F3;
            this.EditMenuItemFindNext.Size = new System.Drawing.Size(198, 22);
            this.EditMenuItemFindNext.Text = "次を検索(&N)";
            this.EditMenuItemFindNext.Click += new System.EventHandler(this.EditMenuItemFindNext_Click);
            this.EditMenuItemFindNext.MouseEnter += new System.EventHandler(this.menu_MouseEnter);
            // 
            // EditMenuItemReplace
            // 
            this.EditMenuItemReplace.Name = "EditMenuItemReplace";
            this.EditMenuItemReplace.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.H)));
            this.EditMenuItemReplace.Size = new System.Drawing.Size(198, 22);
            this.EditMenuItemReplace.Text = "置換(&R)...";
            this.EditMenuItemReplace.Click += new System.EventHandler(this.EditMenuItemReplace_Click);
            this.EditMenuItemReplace.MouseEnter += new System.EventHandler(this.menu_MouseEnter);
            // 
            // EditMenuItemMoveToLine
            // 
            this.EditMenuItemMoveToLine.Name = "EditMenuItemMoveToLine";
            this.EditMenuItemMoveToLine.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.G)));
            this.EditMenuItemMoveToLine.Size = new System.Drawing.Size(198, 22);
            this.EditMenuItemMoveToLine.Text = "行へ移動(&G)...";
            this.EditMenuItemMoveToLine.Click += new System.EventHandler(this.EditMenuItemMoveToLine_Click);
            this.EditMenuItemMoveToLine.MouseEnter += new System.EventHandler(this.menu_MouseEnter);
            // 
            // toolStripSeparator5
            // 
            this.toolStripSeparator5.Name = "toolStripSeparator5";
            this.toolStripSeparator5.Size = new System.Drawing.Size(195, 6);
            // 
            // EditMenuItemSelectAll
            // 
            this.EditMenuItemSelectAll.Name = "EditMenuItemSelectAll";
            this.EditMenuItemSelectAll.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.A)));
            this.EditMenuItemSelectAll.Size = new System.Drawing.Size(198, 22);
            this.EditMenuItemSelectAll.Text = "すべて選択(&A)";
            this.EditMenuItemSelectAll.Click += new System.EventHandler(this.EditMenuItemSelectAll_Click);
            this.EditMenuItemSelectAll.MouseEnter += new System.EventHandler(this.menu_MouseEnter);
            // 
            // EditMenuItemDayAndData
            // 
            this.EditMenuItemDayAndData.Name = "EditMenuItemDayAndData";
            this.EditMenuItemDayAndData.Size = new System.Drawing.Size(198, 22);
            this.EditMenuItemDayAndData.Text = "日付と時刻(&D)";
            this.EditMenuItemDayAndData.MouseEnter += new System.EventHandler(this.menu_MouseEnter);
            // 
            // OptionMenu
            // 
            this.OptionMenu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.OptionMenuItemWrap,
            this.OptionMenuItemFont});
            this.OptionMenu.Name = "OptionMenu";
            this.OptionMenu.Size = new System.Drawing.Size(62, 20);
            this.OptionMenu.Text = "書式(&O)";
            this.OptionMenu.DropDownOpened += new System.EventHandler(this.OptionMenu_DropDownOpened);
            this.OptionMenu.MouseEnter += new System.EventHandler(this.menu_MouseEnter);
            // 
            // OptionMenuItemWrap
            // 
            this.OptionMenuItemWrap.Name = "OptionMenuItemWrap";
            this.OptionMenuItemWrap.Size = new System.Drawing.Size(172, 22);
            this.OptionMenuItemWrap.Text = "右端で折り返す(&W)";
            this.OptionMenuItemWrap.Click += new System.EventHandler(this.OptionMenuItemWrap_Click);
            this.OptionMenuItemWrap.MouseEnter += new System.EventHandler(this.menu_MouseEnter);
            // 
            // OptionMenuItemFont
            // 
            this.OptionMenuItemFont.Name = "OptionMenuItemFont";
            this.OptionMenuItemFont.Size = new System.Drawing.Size(172, 22);
            this.OptionMenuItemFont.Text = "フォント(&F)...";
            this.OptionMenuItemFont.MouseEnter += new System.EventHandler(this.menu_MouseEnter);
            // 
            // ViewMenu
            // 
            this.ViewMenu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ViewMenuItemStatus});
            this.ViewMenu.Name = "ViewMenu";
            this.ViewMenu.Size = new System.Drawing.Size(61, 20);
            this.ViewMenu.Text = "表示(&V)";
            this.ViewMenu.DropDownOpened += new System.EventHandler(this.ViewMenu_DropDownOpened);
            this.ViewMenu.MouseEnter += new System.EventHandler(this.menu_MouseEnter);
            // 
            // ViewMenuItemStatus
            // 
            this.ViewMenuItemStatus.Name = "ViewMenuItemStatus";
            this.ViewMenuItemStatus.Size = new System.Drawing.Size(161, 22);
            this.ViewMenuItemStatus.Text = "ステータス バー(&S)";
            this.ViewMenuItemStatus.Click += new System.EventHandler(this.ViewMenuItemStatus_Click);
            this.ViewMenuItemStatus.MouseEnter += new System.EventHandler(this.menu_MouseEnter);
            // 
            // HelpMenu
            // 
            this.HelpMenu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.HelpMenuItemVersion});
            this.HelpMenu.Name = "HelpMenu";
            this.HelpMenu.Size = new System.Drawing.Size(67, 20);
            this.HelpMenu.Text = "ヘルプ(&H)";
            this.HelpMenu.MouseEnter += new System.EventHandler(this.menu_MouseEnter);
            // 
            // HelpMenuItemVersion
            // 
            this.HelpMenuItemVersion.Name = "HelpMenuItemVersion";
            this.HelpMenuItemVersion.Size = new System.Drawing.Size(161, 22);
            this.HelpMenuItemVersion.Text = "バージョン情報(&V)";
            this.HelpMenuItemVersion.MouseEnter += new System.EventHandler(this.menu_MouseEnter);
            // 
            // statusStrip
            // 
            this.statusStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel,
            this.toolStripSeparator6,
            this.toolStripRawColLabel});
            this.statusStrip.Location = new System.Drawing.Point(0, 256);
            this.statusStrip.Name = "statusStrip";
            this.statusStrip.Size = new System.Drawing.Size(464, 23);
            this.statusStrip.TabIndex = 2;
            this.statusStrip.Text = "statusStrip";
            // 
            // toolStripStatusLabel
            // 
            this.toolStripStatusLabel.Name = "toolStripStatusLabel";
            this.toolStripStatusLabel.Size = new System.Drawing.Size(373, 18);
            this.toolStripStatusLabel.Spring = true;
            this.toolStripStatusLabel.Text = "Ready";
            this.toolStripStatusLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // toolStripSeparator6
            // 
            this.toolStripSeparator6.Name = "toolStripSeparator6";
            this.toolStripSeparator6.Size = new System.Drawing.Size(6, 23);
            // 
            // toolStripRawColLabel
            // 
            this.toolStripRawColLabel.Name = "toolStripRawColLabel";
            this.toolStripRawColLabel.Padding = new System.Windows.Forms.Padding(10, 0, 10, 0);
            this.toolStripRawColLabel.Size = new System.Drawing.Size(70, 18);
            this.toolStripRawColLabel.Text = "1行:1列";
            // 
            // openFileDialog
            // 
            this.openFileDialog.FileName = "openFileDialog";
            // 
            // textBox1
            // 
            this.textBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox1.HideSelection = false;
            this.textBox1.Location = new System.Drawing.Point(0, 29);
            this.textBox1.MaxLength = 999999999;
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBox1.Size = new System.Drawing.Size(464, 224);
            this.textBox1.TabIndex = 1;
            this.textBox1.TabStop = false;
            this.textBox1.WordWrap = false;
            // 
            // NotepadForm
            // 
            this.AllowDrop = true;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(464, 279);
            this.Controls.Add(this.statusStrip);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.menu);
            this.MainMenuStrip = this.menu;
            this.Name = "NotepadForm";
            this.Text = "Form1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.NotepadForm_FormClosing);
            this.DragDrop += new System.Windows.Forms.DragEventHandler(this.NotepadForm_DragDrop);
            this.DragEnter += new System.Windows.Forms.DragEventHandler(this.NotepadForm_DragEnter);
            this.menu.ResumeLayout(false);
            this.menu.PerformLayout();
            this.statusStrip.ResumeLayout(false);
            this.statusStrip.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.MenuStrip menu;
		private NotepadTextBox textBox1;
		private System.Windows.Forms.StatusStrip statusStrip;
		private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel;
		private System.Windows.Forms.OpenFileDialog openFileDialog;
		private System.Windows.Forms.SaveFileDialog saveFileDialog;
		private System.Windows.Forms.ToolStripMenuItem EditMenu;
		private System.Windows.Forms.ToolStripMenuItem EditMenuItemUndo;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
		private System.Windows.Forms.ToolStripMenuItem EditMenuItemCut;
		private System.Windows.Forms.ToolStripMenuItem EditMenuItemCopy;
		private System.Windows.Forms.ToolStripMenuItem EditMenuItemPaste;
		private System.Windows.Forms.ToolStripMenuItem EditMenuItemDel;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
		private System.Windows.Forms.ToolStripMenuItem EditMenuItemFind;
		private System.Windows.Forms.ToolStripMenuItem EditMenuItemFindNext;
		private System.Windows.Forms.ToolStripMenuItem EditMenuItemReplace;
		private System.Windows.Forms.ToolStripMenuItem EditMenuItemMoveToLine;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator5;
		private System.Windows.Forms.ToolStripMenuItem EditMenuItemSelectAll;
		private System.Windows.Forms.ToolStripMenuItem EditMenuItemDayAndData;
		private System.Windows.Forms.ToolStripMenuItem FileMenu;
		private System.Windows.Forms.ToolStripMenuItem FileMenuItemNew;
		private System.Windows.Forms.ToolStripMenuItem FileMenuItemOpen;
		private System.Windows.Forms.ToolStripMenuItem FileMenuItemSave;
		private System.Windows.Forms.ToolStripMenuItem FileMenuItemSaveAs;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
		private System.Windows.Forms.ToolStripMenuItem FileMenuItemPageSetting;
		private System.Windows.Forms.ToolStripMenuItem FileMenuItemPrint;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
		private System.Windows.Forms.ToolStripMenuItem FileMenuItemExit;
		private System.Windows.Forms.ToolStripStatusLabel toolStripRawColLabel;

		private System.Windows.Forms.ToolStripSeparator toolStripSeparator6;
		private System.Windows.Forms.ToolStripMenuItem OptionMenu;
		private System.Windows.Forms.ToolStripMenuItem OptionMenuItemWrap;
		private System.Windows.Forms.ToolStripMenuItem OptionMenuItemFont;
		private System.Windows.Forms.ToolStripMenuItem ViewMenu;
		private System.Windows.Forms.ToolStripMenuItem ViewMenuItemStatus;
		private System.Windows.Forms.ToolStripMenuItem HelpMenu;
		private System.Windows.Forms.ToolStripMenuItem HelpMenuItemVersion;

	}
}

