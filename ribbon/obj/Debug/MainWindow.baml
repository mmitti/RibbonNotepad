   M S B A M L   `   `   `  ����
  ribbon    ribbon.MainWindow   5   	   W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35e aSystem.Windows.Controls.Ribbon, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   -   5          � Title$  
MainWindow��5   	   $	��350��6   $	��750��6)    � 
ResizeMode$ CanResizeWithGrip=�6O    � Icon$ note.ico��5       � TaskbarItemInfo 5      *  $System.Windows.Shell.TaskbarItemInfo  5   
   -   5        taskBarInfo��   ThumbButtonInfos 5
      4  .System.Windows.Shell.ThumbButtonInfoCollection  *  $System.Windows.Shell.ThumbButtonInfo  5      -   5           DismissWhenClicked .    ImageSource$ img/save.png��5      5      5      5      .��5      ]� .+�5   
   +  %System.Windows.Controls.Ribbon.Ribbon  -   5          Name$ 
RibbonHost��5   Q   $	��Top=�6   
���   �$	��Top=�6<      ApplicationMenu 5      :  4System.Windows.Controls.Ribbon.RibbonApplicationMenu  5      .@�5      >  8System.Windows.Controls.Ribbon.RibbonApplicationMenuItem  -   5        	  Name$		 new��5   b   

 J� Uid$	
 new��60   $��新規作成��6:   3  -System.Windows.Controls.Ribbon.RibbonMenuItem   ImageSource$ img/new.png��6H   6�     5      -   5        $
	 open��5   b   $

 open��60   $��開く��6;   $ img/open.png��6G   6�     5      -   5        $
	 save��5   e   $

 save��60   $��上書き保存��6;   $ img/save.png��6J   6�     5      -   5        $	 saveas��5   l   $
 saveas��60   $��名前をつけて保存��6=   $ img/saveas.png��6O   6�   4  .System.Windows.Controls.Ribbon.RibbonSeparator  5        5      -	   5        $	 print��5   d   $
 print��60   $��印刷��6<   $ img/print.png��6H   6�     5      -
   5        $
	 exit��5   G   $

 exit��60   $��終了��6;   $ img/exit.png��6�   5         ContextualTabGroups 5!      =	  7System.Windows.Controls.Ribbon.RibbonContextualTabGroup	  5"      -   5         	 Name$ tabSetToLine��5"   +    	  Header$ 行ツール��6A   $y�Visible=�6O   
���  ��6d   .@�5&      .
  (System.Windows.Controls.Ribbon.RibbonTab
  -   5        $��edittab��5&   i   $
 TabEdit��6   $��編集��6&   $��88��62   $	��Top=�6>   
�������.@�5'      0  *System.Windows.Controls.Ribbon.RibbonGroup  $��元に戻す��6      GroupSizeDefinitions 5)      L  FSystem.Windows.Controls.Ribbon.RibbonGroupSizeDefinitionBaseCollection  >  8System.Windows.Controls.Ribbon.RibbonGroupSizeDefinition  5*         ControlSizeDefinitions. 5+   "   @  :System.Windows.Controls.Ribbon.RibbonControlSizeDefinition     	ImageSize$ Large=�6>      IsLabelVisible . 6P   5,      5-      .@�5/      1  +System.Windows.Controls.Ribbon.RibbonButton  -   5          Name$
 redo��5/   U   $

 Undo��6#   $
��Undo��6.      Label$ 元に戻す��6=      KeyTip$ Z��6J      LargeImageSource$ img/redo.png��6c   6�   50        51      $��クリップボード��6      LargeImageSource$ img/paste.png��6/    54          55      . 56   "     $ Large=�6>    . 6P     57   "   $ Large=�6>    . 6P     58   "   $ Large=�6>    . 6P   59        5:      . 5;   "     $ Large=�6>    . 6P     5<   "   $ Small=�6>    . 6P     5=   "   $ Small=�6>    . 6P   5>        5?      . 5@   "     $ Large=�6>    . 6P     5A   "   $ Small=�6>    .  6P     5B   "   $ Small=�6>    .  6P   5C      5F      .@�5I        -   5        $ paste��5I   T   $
 CV��6#   $��Paste��6,   $ 貼り付け��6<   $ V��6I   $ img/paste.png��6c   6�     5J      -   5        $
 copy��5J   R   $
 CC��6#   $
��Copy��6,   $ 	コピー��6;   $ C��6G      SmallImageSource$ img/copy.png��6`   $ img/copy.png��6�   6�     5K      -   5        $	 cut��5K   R   $
 CX��6#   $	��Cut��6,   $ 切り取り��6:   $ X��6G   $ img/cut.png��6_   $ img/cut.png��6~   6�   5M        5O      $$��テキスト・エディター��6   ��5P      �� 5Q       �� EndPoint$ 0.5,1&�6.    �� 
StartPoint$ 0.5,0&�6?   .��5R      �  � Color$ 	#FFFAFBFD��6+    � Offset$ 0.004Q�6=   � 5S      $ 	#FFEEF3F9��6+   $ 1Q�6=   � 5T      $ 	#FFECF1F9��6+   $
 0.49Q�6=   5U      .@�5W        -   5        $ 
showtoline��5W   F   $

 TEsl��6#   $ 行へ移動��6.   $ G��6;   $ img/gotoline.png��6Z   $ img/gotoline.png��6   6�     5X      -   5        $	 del��5X   F   $
 TEdel��6$   $ 削除��60   $ D��6;   $ img/del.png��6S   $ img/del.png��6r   6�   5  /System.Windows.Controls.Ribbon.RibbonMenuButton  5Y      -   5          Name$
 date��5Y   K   $

 TEdt��6'      Label$ 日付と時刻��62      KeyTip$ T��6@       SmallImageSource$  img/date.png��6Y   !   LargeImageSource$! img/date.png��6y   .@�5Z      2  ,System.Windows.Controls.Ribbon.RibbonGallery  .@�5[      :  4System.Windows.Controls.Ribbon.RibbonGalleryCategory  -   5        "  Name$" 	dataItems��5[   5   5\      5^        5`      -   5        $	 all��5`   G   $
 TEall��6#   $ 全て選択��6/   $ A��6<   .��5a      7  1System.Windows.Controls.Ribbon.RibbonToggleButton  $��RibbonToggleButton��6-   $	��100��6J   $	��100��6W   5b      5c        5d      $��表示��6   $ img/view.png��6+   ��5e      �� 5f      $ 0.5,1&�6.   $ 0.5,0&�6?   .��5g      � $ 	#FFFAFBFD��6+   $ 0.004Q�6=   � 5h      $ 	#FFEEF3F9��6+   $ 1Q�6=   � 5i      $ 	#FFECF1F9��6+   $
 0.49Q�6=   5j      .@�5l        -   5        $
 font��5l   G   $
 Vfont��6#   $ フォント��6/   $ H��6<   $ img/font.png��6U   6�     5m      -   5        #  Name$
# wrap��5m   P   $
 Vwrap��6)   $   Label$$ 右端で折り返す��65   %   KeyTip$% H��6E   6�     5n      -   5        $# status��5n   R   $
 Vstatus��6)   $$ ステータスバー��67   $% S��6G   6�   5o      5q      
  5r      -   5        $��findtab��5r   V   $
 TabFind��6   $��検索��6&   $��88��62   $	��Top=�6>   .@�5s        $��入力��6   $ img/input.png��6*   ��5u      �� 5v      $ 0.5,1&�6.   $ 0.5,0&�6?   .��5w      � $ 	#FFFAFBFD��6+   $ 0.004Q�6=   � 5x      $ 	#FFEEF3F9��6+   $ 1Q�6=   � 5y      $ 	#FFECF1F9��6+   $
 0.49Q�6=   5z      .@�5|      2  ,System.Windows.Controls.Ribbon.RibbonTextBox  -   5        &  Name$& textFind��5|   0   $
 tFind��6$   ' � ToolTip$' 検索する文字列��6B   (   Label$( 検索��6T   )   TextBoxWidth$	) 150Q�6_   6�     5}      -   5        $& textReplace��5}   /   $

 tRep��6$   $' 置換する文字列��6D   $( 置換��6V   $	) 150Q�6a   6�   5~        5      $��検索��6   $ img/search.png��6*   ��5�      �� 5�      $ 0.5,1&�6.   $ 0.5,0&�6?   .��5�      � $ 	#FFFAFBFD��6+   $ 0.004Q�6=   � 5�      $ 	#FFEEF3F9��6+   $ 1Q�6=   � 5�      $ 	#FFECF1F9��6+   $
 0.49Q�6=   5�       5�          5�      . 5�   "     $ Large=�6>    . 6P     5�   "   $ Large=�6>    . 6P   5�        5�      . 5�   "     $ Small=�6>    . 6P     5�   "   $ Small=�6>    . 6P   5�        5�      . 5�   "     $ Small=�6>    .  6P     5�   "   $ Small=�6>    .  6P   5�      5�      .@�5�        -   5        $ 	findFirst��5�   /   $
 findF��6#   $ 先頭から検索��6B   $ img/gotoline.png��6Q   $ img/findfirst.png��6u   6�     5�      -   5        $ findNext��5�   /   $
 findN��6#   $ 次を検索��6A   $ img/search.png��6N   $ img/search.png��6p   6�   5�        5�      $��置換��6   $ img/replace.png��6+   ��5�      �� 5�      $ 0.5,1&�6.   $ 0.5,0&�6?   .��5�      � $ 	#FFFAFBFD��6+   $ 0.004Q�6=   � 5�      $ 	#FFEEF3F9��6+   $ 1Q�6=   � 5�      $ 	#FFECF1F9��6+   $
 0.49Q�6=   5�       5�          5�      . 5�   "     $ Large=�6>    . 6P     5�   "   $ Large=�6>    . 6P   5�        5�      . 5�   "     $ Small=�6>    . 6P     5�   "   $ Small=�6>    . 6P   5�        5�      . 5�   "     $ Small=�6>    .  6P     5�   "   $ Small=�6>    .  6P   5�      5�      .@�5�        -   5        $ replace��5�   -   $	
 rep��6#   $ 置換��6>   $ img/replace.png��6I   $ img/replace.png��6l   6�     5�      -   5        $ 
replaceall��5�   .   $

 repA��6#   $ すべて置換��6B   $ img/replaceall.png��6P   $ img/replaceall.png��6v   6�   5�        5�      $��検索方向��6   $ img/dir.png��6-   ��5�      �� 5�      $ 0.5,1&�6.   $ 0.5,0&�6?   .��5�      � $ 	#FFFAFBFD��6+   $ 0.004Q�6=   � 5�      $ 	#FFEEF3F9��6+   $ 1Q�6=   � 5�      $ 	#FFECF1F9��6+   $
 0.49Q�6=   5�      .@�5�      6  0System.Windows.Controls.Ribbon.RibbonRadioButton  -    5        *  Name$* 	finddirup��5�   2   $	
 fdU��6(   +   Label$	+ 上��6E   ,   SmallImageSource$, 
img/up.png��6O   6�     5�      -!   5        $* finddirdown��5�   2   $	
 fdD��6(   $	+ 下��6G   $, img/down.png��6Q   6�   5�        5�      $��オプション��6   $ img/option.png��6-   ��5�      �� 5�      $ 0.5,1&�6.   $ 0.5,0&�6?   .��5�      � $ 	#FFFAFBFD��6+   $ 0.004Q�6=   � 5�      $ 	#FFEEF3F9��6+   $ 1Q�6=   � 5�      $ 	#FFECF1F9��6+   $
 0.49Q�6=   5�      .@�5�      3  -System.Windows.Controls.Ribbon.RibbonCheckBox  -"   5        $ ��findOptionIdentifyCharSize��5�   1   $
 foICS��6%   -   Label$'- !大文字小文字を区別する��6S   6�     5�      -#   5        $��findOptionUseEscSeq��5�   4   $
 foUseESC��6%   $- 改行=\n タブ=\t \=\\��6O   6�     5�      -$   5        $��findOptionUseRegural��5�   5   $
 	foUserReg��6%   $- 正規表現を使う��6Q   6�   5�      5�      
  5�      -%   5        . 
 Name$. 	TabToLine��5�   x   $
 TabLine��6   $��行へ移動��6&   $��88��64   $	��Top=�6@   / 
  ContextualTabGroupHeader$/ 行ツール��6X   .@�5�        $��行へ移動��6   ��5�      �� 5�      $ 0.5,1&�6.   $ 0.5,0&�6?   .��5�      � $ 	#FFFAFBFD��6+   $ 0.004Q�6=   � 5�      $ 	#FFEEF3F9��6+   $ 1Q�6=   � 5�      $ 	#FFECF1F9��6+   $
 0.49Q�6=   5�      .@�5�        -&   5        $& LineBox��5�   2   $
 LineBox��6$   $��0��6C   $( 	行番号��6L   0 �� TextAlignment$0 Right=�6X   5�   )     5�      -'   5        $ toLine��5�   K   $
 gotoLine��6#   $ 行へ移動!��62   $ G��6@   $ img/gotoline.png��6[   5�   )   5�      5�      5�      �� 5�   
   -(   5        $��	StatusBar��5�      $��Bottom=�6&   $��Bottom=�6>   $��30��6Y   
����������	#FF004488.@�5�      � ��6   �� *ActualWidth+1 �� ElementName$1 	statusBar��2 �� Mode$2 OneWay=�3 � ColumnDefinitions3 5�      �� 5�      $��* �6'   �� 5�      $	��100 �6'   .+�5�      �� -)   5        4 ��Name$4 mainStatusText��5�       $��Ready��69   5�      �� 5�      -*   5        $4 statusColRow��5�      $��	行0:列0��63   $��Right=�6C   $��0,0,10,0q�6_   5�      �� 5�   
   -+   5        5 ��Name$
5 tbox��5�      6 �� TextWrapping$6 NoWrap=�6"   $��TextBox��68   "7 �� VerticalScrollBarVisibility$7 Visible=�6G   $8 �� HorizontalScrollBarVisibility$8 Visible=�6m   9 �� AcceptsReturn9 . $	��Top=�6�   $
��16px(�6�   : �� 
AcceptsTab: . 6�   5�      5�      