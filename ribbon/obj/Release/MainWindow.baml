   M S B A M L   `   `   `  ���� 
  ribbon    ribbon.MainWindow   W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35e aSystem.Windows.Controls.Ribbon, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     -     � Title$  
MainWindow��$	��350��$	��750�� � 
ResizeMode$ CanResizeWithGrip=� � Icon$ note.ico�� � TaskbarItemInfo *  $System.Windows.Shell.TaskbarItemInfo  -   taskBarInfo��   ThumbButtonInfos 4  .System.Windows.Shell.ThumbButtonInfoCollection  *  $System.Windows.Shell.ThumbButtonInfo  -      DismissWhenClicked .    ImageSource$ img/save.png��  -    . $ img/new.png��.��]� .+�+  %System.Windows.Controls.Ribbon.Ribbon  -     Name$ 
RibbonHost��$	��Top=�
���   �$	��Top=�   ApplicationMenu :  4System.Windows.Controls.Ribbon.RibbonApplicationMenu  .@�>  8System.Windows.Controls.Ribbon.RibbonApplicationMenuItem  -   	  Name$		 new��

 J� Uid$	
 new��$��新規作成��3  -System.Windows.Controls.Ribbon.RibbonMenuItem   ImageSource$ img/new.png��  -   $
	 open��$

 open��$��開く��$ img/open.png��  -   $
	 save��$

 save��$��上書き保存��$ img/save.png��  -	   $	 saveas��$
 saveas��$��名前をつけて保存��$ img/saveas.png��4  .System.Windows.Controls.Ribbon.RibbonSeparator    -
   $	 print��$
 print��$��印刷��$ img/print.png��  -   $
	 exit��$

 exit��$��終了��$ img/exit.png��   ContextualTabGroups =	  7System.Windows.Controls.Ribbon.RibbonContextualTabGroup	  -    	 Name$ tabSetToLine�� 	  Header$ 行ツール��$y�Visible=�
���  ��.@�.
  (System.Windows.Controls.Ribbon.RibbonTab
  -   $��edittab��$
 TabEdit��$��編集��$��88��$	��Top=�
�������.@�0  *System.Windows.Controls.Ribbon.RibbonGroup  $��元に戻す��   GroupSizeDefinitions L  FSystem.Windows.Controls.Ribbon.RibbonGroupSizeDefinitionBaseCollection  >  8System.Windows.Controls.Ribbon.RibbonGroupSizeDefinition     ControlSizeDefinitions. @  :System.Windows.Controls.Ribbon.RibbonControlSizeDefinition     	ImageSize$ Large=�   IsLabelVisible . .@�1  +System.Windows.Controls.Ribbon.RibbonButton  -     Name$
 redo��$

 Undo��$
��Undo��   Label$ 元に戻す��   KeyTip$ Z��   LargeImageSource$ img/redo.png��  $��クリップボード��   LargeImageSource$ img/paste.png��     .   $ Large=� .   $ Large=� .   $ Large=� .   .   $ Large=� .   $ Small=� .   $ Small=� .   .   $ Large=� .   $ Small=� .    $ Small=� .  .@�  -   $ paste��$
 CV��$��Paste��$ 貼り付け��$ V��$ img/paste.png��  -   $
 copy��$
 CC��$
��Copy��$ 	コピー��$ C��   SmallImageSource$ img/copy.png��$ img/copy.png��  -   $	 cut��$
 CX��$	��Cut��$ 切り取り��$ X��$ img/cut.png��$ img/cut.png��  $$��テキスト・エディター������  �� EndPoint$ 0.5,1&� �� 
StartPoint$ 0.5,0&�.���  � Color$ 	#FFFAFBFD�� � Offset$ 0.004Q�� $ 	#FFEEF3F9��$ 1Q�� $ 	#FFECF1F9��$
 0.49Q�.@�  -   $ 
showtoline��$

 TEsl��$ 行へ移動��$ G��$ img/gotoline.png��$ img/gotoline.png��  -   $	 del��$
 TEdel��$ 削除��$ D��$ img/del.png��$ img/del.png��5  /System.Windows.Controls.Ribbon.RibbonMenuButton  -     Name$
 date��$

 TEdt��   Label$ 日付と時刻��   KeyTip$ T��    SmallImageSource$  img/date.png��!   LargeImageSource$! img/date.png��.@�2  ,System.Windows.Controls.Ribbon.RibbonGallery  .@�:  4System.Windows.Controls.Ribbon.RibbonGalleryCategory  -   "  Name$" 	dataItems��  -   $	 all��$
 TEall��$ 全て選択��$ A��.��7  1System.Windows.Controls.Ribbon.RibbonToggleButton  $��RibbonToggleButton��$	��100��$	��100��  $��表示��$ img/view.png������ $ 0.5,1&�$ 0.5,0&�.��� $ 	#FFFAFBFD��$ 0.004Q�� $ 	#FFEEF3F9��$ 1Q�� $ 	#FFECF1F9��$
 0.49Q�.@�  -   $
 font��$
 Vfont��$ フォント��$ H��$ img/font.png��  -   #  Name$
# wrap��$
 Vwrap��$   Label$$ 右端で折り返す��%   KeyTip$% H��  -   $# status��$
 Vstatus��$$ ステータスバー��$% S��
  -   $��findtab��$
 TabFind��$��検索��$��88��$	��Top=�.@�  $��入力��$ img/input.png������ $ 0.5,1&�$ 0.5,0&�.��� $ 	#FFFAFBFD��$ 0.004Q�� $ 	#FFEEF3F9��$ 1Q�� $ 	#FFECF1F9��$
 0.49Q�.@�2  ,System.Windows.Controls.Ribbon.RibbonTextBox  -   &  Name$& textFind��$
 tFind��' � ToolTip$' 検索する文字列��(   Label$( 検索��)   TextBoxWidth$	) 150Q�  -   $& textReplace��$

 tRep��$' 置換する文字列��$( 置換��$	) 150Q�  $��検索��$ img/search.png������ $ 0.5,1&�$ 0.5,0&�.��� $ 	#FFFAFBFD��$ 0.004Q�� $ 	#FFEEF3F9��$ 1Q�� $ 	#FFECF1F9��$
 0.49Q�     .   $ Large=� .   $ Large=� .   .   $ Small=� .   $ Small=� .   .   $ Small=� .    $ Small=� .  .@�  -   $ 	findFirst��$
 findF��$ 先頭から検索��$ img/gotoline.png��$ img/findfirst.png��  -   $ findNext��$
 findN��$ 次を検索��$ img/search.png��$ img/search.png��  $��置換��$ img/replace.png������ $ 0.5,1&�$ 0.5,0&�.��� $ 	#FFFAFBFD��$ 0.004Q�� $ 	#FFEEF3F9��$ 1Q�� $ 	#FFECF1F9��$
 0.49Q�     .   $ Large=� .   $ Large=� .   .   $ Small=� .   $ Small=� .   .   $ Small=� .    $ Small=� .  .@�  -   $ replace��$	
 rep��$ 置換��$ img/replace.png��$ img/replace.png��  -    $ 
replaceall��$

 repA��$ すべて置換��$ img/replaceall.png��$ img/replaceall.png��  $��検索方向��$ img/dir.png������ $ 0.5,1&�$ 0.5,0&�.��� $ 	#FFFAFBFD��$ 0.004Q�� $ 	#FFEEF3F9��$ 1Q�� $ 	#FFECF1F9��$
 0.49Q�.@�6  0System.Windows.Controls.Ribbon.RibbonRadioButton  -!   *  Name$* 	finddirup��$	
 fdU��+   Label$	+ 上��,   SmallImageSource$, 
img/up.png��  -"   $* finddirdown��$	
 fdD��$	+ 下��$, img/down.png��  $��オプション��$ img/option.png������ $ 0.5,1&�$ 0.5,0&�.��� $ 	#FFFAFBFD��$ 0.004Q�� $ 	#FFEEF3F9��$ 1Q�� $ 	#FFECF1F9��$
 0.49Q�.@�3  -System.Windows.Controls.Ribbon.RibbonCheckBox  -#   $ ��findOptionIdentifyCharSize��$
 foICS��-   Label$'- !大文字小文字を区別する��  -$   $��findOptionUseEscSeq��$
 foUseESC��$- 改行=\n タブ=\t \=\\��  -%   $��findOptionUseRegural��$
 	foUserReg��$- 正規表現を使う��
  -&   . 
 Name$. 	TabToLine��$
 TabLine��$��行へ移動��$��88��$	��Top=�/ 
  ContextualTabGroupHeader$/ 行ツール��.@�  $��行へ移動������ $ 0.5,1&�$ 0.5,0&�.��� $ 	#FFFAFBFD��$ 0.004Q�� $ 	#FFEEF3F9��$ 1Q�� $ 	#FFECF1F9��$
 0.49Q�.@�  -'   $& LineBox��$
 LineBox��$��0��$( 	行番号��0 �� TextAlignment$0 Right=�  -(   $ toLine��$
 gotoLine��$ 行へ移動!��$ G��$ img/gotoline.png���� -)   $��	StatusBar��$��Bottom=�$��Bottom=�$��30��
����������	#FF004488.@�� ���� *ActualWidth+1 �� ElementName$1 	statusBar��2 �� Mode$2 OneWay=�3 � ColumnDefinitions3 �� $��* ��� $	��100 �.+��� -*   4 ��Name$4 mainStatusText��$��Ready���� -+   $4 statusColRow��$��	行0:列0��$��Right=�$��0,0,10,0q��� -,   5 ��Name$
5 tbox��6 �� TextWrapping$6 NoWrap=�$��TextBox��"7 �� VerticalScrollBarVisibility$7 Visible=�$8 �� HorizontalScrollBarVisibility$8 Visible=�9 �� AcceptsReturn9 . $	��Top=�$
��16px(�: �� 
AcceptsTab: . 