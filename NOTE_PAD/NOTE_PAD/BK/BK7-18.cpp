//RichEditにする//RICHEDIT_CLASS//RichEdit
//完了//http://eternalwindows.jp/control/controlbase/controlbase09.html
//http://hp.vector.co.jp/authors/VA024411/vbtips03.html#05
//CheckMenuRadioItem(GetMenu(hwnd), メニューアイテム始まりのID,メニューアイテムおわりのID, メニューアイテムアイコンをセットするID, MF_BYCOMMAND ); ***ラジオボタンのチェック
//MessageBoxの改行*/\r\n/*

//EM_LINEFROMCHAR現在の行番号を取得
//http://support.microsoft.com/kb/186271/ja



#include<windows.h>
#include"resource.h"
#include <commctrl.h>
#pragma comment(lib,"Comctl32.lib")//Libのリンク

HFONT hFont1;
HWND edt;
HWND edtnr;
HWND edtr;
HWND bufEdt1,bufEdt2;
HWND Stas;
WNDPROC SubEditClass;
LOGFONT lf={0};//必須
CHOOSEFONT cf;//必須
LPCHOOSEFONT pcf;

char szFile[256];
char szFileTitle[256]="";
const char szWindowTitle[128] = "ただのテキストエディター";//ウインドウのタイトル
char szTitle[128];
char* szTitle2 = "ただのテキストエディター - %s";
LPCSTR EndD;
OPENFILENAME ofn;
HANDLE hFile;
DWORD dwAccBytes;
char *lpszBuf;
int nLen;
HGLOBAL hMem;
DWORD dwSize;

bool filesv = false;

int tS,tE;
const int TEXTsz=1024*384;
FINDREPLACE frp;//FindText

bool FTF1 = false,FTF2 = false;

const int insz = 256;//検索ダイアログ入力も文字数
TCHAR inBuf[insz] = "";
TCHAR repBuf[insz] = "";
bool tSE = false;//１回目かどうか＠検索
bool flFND = false;//検索をしたことがあるか
	
TCHAR DefStastext[128]="Ready";


int setup(){

	memset(&ofn,0,sizeof(OPENFILENAME));//ofnに0を代入

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = edt;
	ofn.lpstrFilter = "テキストファイル(*.txt)\0*.txt\0c++ファイル(*.cpp)\0*.cpp\0cファイル(*.c)\0*.c\0All files(*.*)\0*.*\0\0";
	ofn.lpstrFile = szFile;
	ofn.lpstrFileTitle = szFileTitle;
	ofn.nFilterIndex = 1;
	ofn.nMaxFile = MAX_PATH;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.Flags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY ;
	ofn.lpstrDefExt = "txt";
	return 0;
}
int clipck1(HWND bufEdt2){
	if(IsClipboardFormatAvailable(CF_TEXT)){
		SendMessage(bufEdt2,WM_PASTE,0,0);
	}
	return 0;
}
int clipck2(HWND bufEdt2){	
	if(IsClipboardFormatAvailable(CF_TEXT)){
		SendMessage(bufEdt2,EM_SETSEL,0,-1);
		SendMessage(bufEdt2,WM_COPY,0,0);
		SetWindowText(bufEdt2,"");
	}
	return 0;
}
int MySaveAs(HWND edt){
	

	nLen = GetWindowTextLength(edt);
	hMem = GlobalAlloc(GHND,sizeof(char)*nLen + 1);
	lpszBuf = (char *)GlobalLock(hMem);
	GetWindowText(edt,lpszBuf,nLen + 1);

	
	setup();
	wsprintf(szTitle,"%s - 名前を付けて保存",szWindowTitle);
	ofn.lpstrTitle = "名前を付けて保存";

	if(GetSaveFileName(&ofn) == 0)return -1;
	wsprintf(szTitle,"保存中");
	SetWindowText(GetParent(edt),szTitle);	
	hFile = CreateFile(szFile,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	WriteFile(hFile,lpszBuf,(DWORD)strlen(lpszBuf),&dwAccBytes,NULL);
	
	if(CloseHandle(hFile) == 0){
		MessageBox(edt,"NOT CLOSE HANDLE","ERROR",MB_OK);
		wsprintf(szTitle,szTitle,szFileTitle);
		SetWindowText(GetParent(edt),szTitle);
	}

	wsprintf(szTitle,szTitle2,szFileTitle);
	SetWindowText(GetParent(edt),szTitle);
	
	SendMessage(edt,EM_SETMODIFY,FALSE,0);

	GlobalUnlock(hMem);
	GlobalFree(hMem);
	filesv = true;
	return 0;
}
int MySave(HWND edt){
	
	if(strcmp(szFile,"") == 0){
		MySaveAs(edt);
		return -1;
	}

	nLen = GetWindowTextLength(edt);
	hMem = GlobalAlloc(GHND,sizeof(char)*nLen + 1);
	lpszBuf = (char *)GlobalLock(hMem);
	GetWindowText(edt,lpszBuf,nLen + 1);

	wsprintf(szTitle,"上書き保存中");
	SetWindowText(GetParent(edt),szTitle);

	hFile = CreateFile(szFile,GENERIC_WRITE,0,NULL,TRUNCATE_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	WriteFile(hFile,lpszBuf,(DWORD)strlen(lpszBuf),&dwAccBytes,NULL);

	if(CloseHandle(hFile) == 0){
		hFile = CreateFile(szFile,GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL);
		WriteFile(hFile,lpszBuf,(DWORD)strlen(lpszBuf),&dwAccBytes,NULL);
		if(CloseHandle(hFile) == 0){
			MessageBox(edt,"NOT CLOSE HANDLE","ERROR",MB_OK);
			wsprintf(szTitle,szTitle,szFileTitle);
			SetWindowText(GetParent(edt),szTitle);
		}
	}
	
	wsprintf(szTitle,szTitle2,szFileTitle);
	SetWindowText(GetParent(edt),szTitle);
	
	SendMessage(edt,EM_SETMODIFY,FALSE,0);

	GlobalUnlock(hMem);
	GlobalFree(hMem);
	return 0;
}
int SaveEx(HWND edt){
	int id;
	nLen = GetWindowTextLength(edt);
	if(nLen == 0 && filesv == false)SendMessage(edt,EM_SETMODIFY,0,0);
	if (SendMessage(edt,EM_GETMODIFY,0,0)){
				id =MessageBox(edt , TEXT("変更されているようだけど\n保存するかい？") ,
				TEXT(EndD) ,MB_YESNOCANCEL | MB_ICONINFORMATION);
		switch (id){
			case IDYES:
				MySave(edt);
				break;
			case IDCANCEL:
				return IDCANCEL;
			case IDNO:
				return IDNO;
		}
	}return 0;
}
int MyOpenF(HWND edt){
	int id;
	
	EndD="問い合わせ - ファイルを開く";
	id = SaveEx(edt);
	if(id == IDCANCEL)return 0;

	//dwSize =OL;
	setup();
	wsprintf(szTitle,"%s - ファイルを開く",szWindowTitle);
	ofn.lpstrTitle = szTitle;

	if(GetOpenFileName(&ofn) == 0)return -1;

	hFile =CreateFile(szFile,GENERIC_READ,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	dwSize = GetFileSize(hFile,NULL);
	hMem = GlobalAlloc(GHND,sizeof(char)*dwSize + 1);
	if(hMem == NULL){
		MessageBox(edt,"NOT OPEN FILE","ERROR",MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}
	lpszBuf = (char *)GlobalLock(hMem);

	ReadFile(hFile,lpszBuf,dwSize,&dwAccBytes,NULL);
	lpszBuf[dwAccBytes] = '\0';
	SetWindowText(edt,lpszBuf);

	wsprintf(szTitle,szTitle2,szFileTitle);
	SetWindowText(GetParent(edt),szTitle);
	CloseHandle(hFile);
	GlobalUnlock(hMem);
	GlobalFree(hMem);
	filesv = true;
	return 0;
}
int NewF(HWND edt){
	int id;
	
	EndD="問い合わせ - 新規作成";
	id = SaveEx(edt);
	if(id == IDCANCEL)return 0;
	SetWindowText(edt,"");
	SetWindowText(GetParent(edt),szWindowTitle);
	strcpy_s(szFile,"");
	return 0;
}
int DandT(HWND edt,HWND  bufEdt1,HWND bufEdt2,int op,bool MenuMes=false){
	SYSTEMTIME st;
	char szBuf[256];
	LPTSTR str;
	GetLocalTime(&st);
	
	switch(op){
		case ID_OP1:
			if(MenuMes) wsprintf(szBuf,"形式1:%d:%d:%d",st.wHour,st.wMinute,st.wSecond);
			else wsprintf(szBuf,"%d:%d:%d",st.wHour,st.wMinute,st.wSecond);
			break;
		case ID_OP2:
			if(MenuMes) wsprintf(szBuf,"形式2:%d時%d分%d秒",st.wHour,st.wMinute,st.wSecond);
			else wsprintf(szBuf,"%d時%d分%d秒",st.wHour,st.wMinute,st.wSecond);
			break;
		case ID_OP3:
			if(st.wHour/12 >= 1)str="PM";
			else str="AM";
			if(MenuMes) wsprintf(szBuf,"形式3:%d:%d(%s)",st.wHour%12,st.wMinute,str);
			else wsprintf(szBuf,"%d:%d(%s)",st.wHour%12,st.wMinute,str);
			break;
		case ID_OP4:
			if(MenuMes) wsprintf(szBuf,"形式4:%d/%d/%d",st.wYear,st.wMonth,st.wDay);
			else wsprintf(szBuf,"%d/%d/%d",st.wYear,st.wMonth,st.wDay);
			break;
		case ID_OP5:
			if(MenuMes) wsprintf(szBuf,"形式5:%d年%d月%d日",st.wYear,st.wMonth,st.wDay);
			else wsprintf(szBuf,"%d年%d月%d日",st.wYear,st.wMonth,st.wDay);
			break;
		case ID_OP6:
			if(MenuMes) wsprintf(szBuf,"形式6:%d/%d/%d %d:%d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute);
			else wsprintf(szBuf,"%d/%d/%d %d:%d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute);
			break;
		case ID_OP7:
			switch(st.wDayOfWeek){
				case 0:
					str="（日）";
					break;
				case 1:
					str="（月）";
					break;
				case 2:
					str="（火）";
					break;
				case 3:
					str="（水）";
					break;
				case 4:
					str="（木）";
					break;
				case 5:
					str="（金）";
					break;
				case 6:
					str="（土）";
					break;
			}
			if(MenuMes) wsprintf(szBuf,"形式7:%s",str);
			else wsprintf(szBuf,"%s",str);
			break;
		case ID_OP8:
			switch(st.wDayOfWeek){
				case 0:
					str="SUN";
					break;
				case 1:
					str="MON";
					break;
				case 2:
					str="TUE";
					break;
				case 3:
					str="WED";
					break;
				case 4:
					str="THU";
					break;
				case 5:
					str="FRY";
					break;
				case 6:
					str="SAT";
					break;
			}
			if(MenuMes)wsprintf(szBuf,"形式8：%s",str);
			else wsprintf(szBuf,"%s",str);
			break;
	}
	if(MenuMes){SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)szBuf);}
	else{
		SetWindowText(bufEdt1,szBuf);
		clipck1(bufEdt2);

		SendMessage(bufEdt1,EM_SETSEL,0,-1);
		SendMessage(bufEdt1,WM_COPY,0,0);
		SendMessage(edt,WM_PASTE,0,0);

		clipck2(bufEdt2);
	}
	return 0;
}
int FINDTEXT(HWND edt,bool ud,int* x=0,bool xF=false,bool rep =false){
//リターン値	1:見つかりました	2:全く見つかりませんでした	3:すべて検索しました
	static bool sw;
	
	int i = 0;
	static int m = 0;
	bool Flag =true;
	static int end,rm;
	static TCHAR bkBuf[insz];
	static int fs=0;//見つからなかったとき一回目かどうか
	if(xF) *x = m + 1;
	flFND = true;

	nLen = GetWindowTextLength(edt);
	char* textBuf = new char[nLen + 16];
	GetWindowText(edt,textBuf,nLen + 1);

	for(int j=0;j<=m;j++){
		if(bkBuf[j] != inBuf[j]){
			tSE = false;
		}
	}

	if(ud){
		if(tSE){
			tS++;
			fs = 1;
		}
	else {
			sw = false;
			end = 0;
			tS = 0;
			tE = 0;
			rm = 0;
			SendMessage(edt,EM_GETSEL,(WPARAM)&tS,(LPARAM)&tE);
			end = tS;
			m=lstrlen(inBuf)-1;//inBufの文字の長さ
			if(rep) rm = lstrlen(repBuf)-1;
			fs = 0;
			for(int k=0;k<=m;k++){
				bkBuf[k] = inBuf[k];
			}
		}
	
		while(Flag){
		
			if(tS >= end &&sw == true){
				SendMessage(edt,EM_SETSEL,end,end);
				delete[] textBuf;
				return 2+fs;
			}//NOTFOUND
			else if(tS>nLen){
				tS = -1;
				sw = true;
			}
	
			else{
				i = 0;
				if(textBuf[tS] == inBuf[0]){
					while(i+1){
						if(i == m){
							i = -1;
							if(textBuf[tS+m] == inBuf[m]){
								tE = tS + m + 1;
								Flag = false;
								if(rep&&sw) end += rm - m;
								delete[] textBuf;
								return 1;
							}//FOUND
						}
						else if(textBuf[tS+i] != inBuf[i]){
							i = -1;
						}
						else i++;
					}
				}
				else i=-1;
			
		
			}
		tS++;	
		}
	}

	else{
		if(tSE){
			tS--;
		}
		else {
			sw = false;
			end = 0;
			tS = 0;
			tE = 0;
			SendMessage(edt,EM_GETSEL,(WPARAM)&tS,(LPARAM)&tE);
			end = tS;
			for(int k=0;k<=m;k++){
				bkBuf[k] = inBuf[k];
			}
		}
        
		while(Flag){
                
			if(tS<=end&&sw==true){
				SendMessage(edt,EM_SETSEL,end,end);
				delete[] textBuf;
				return 2+fs;
			}//NOTFOUND
			else if(tS<0){
				tS = nLen+1;
				sw = true;
			}

			else{
				i = 0;
				if(textBuf[tS] == inBuf[/*0*/m]){
					while(i+1){
						if(i == m){
							i = -1;
							if(textBuf[tS-m] == inBuf[0]){
								tS -= m;
								tE = tS + m + 1;
								if(rep&&(!sw)) end += rm - m;
								Flag = false;
								delete[] textBuf;
								return 1;
							}//FOUND
						}
						else if(textBuf[tS-i] != inBuf[m-i]){i=-1;}
						else i++;
					}
				}
				else i=-1;
                        
                
			 }
        tS--;
        }

	}
	delete[] textBuf;
	return 2+fs;//NOT
}
int FINDTEXTR2(HWND edt,int ct,HWND Bufedt){
	char* rc ="";
	int Loop=0,i=0,inLen=0,REPLen=0,OutLen=0,BufLen=0;
	inLen=lstrlen(inBuf);
	REPLen=lstrlen(repBuf);
	nLen = GetWindowTextLength(edt);
	char* textBuf = new char[nLen + 16];
	GetWindowText(edt,textBuf,nLen + 1);
	char* textOutBuf = new char[nLen + ((REPLen - inLen) * ct)+16];
	memcpy( textOutBuf,rc,sizeof(rc));
	while(1){
		
		if(Loop>nLen){
			break;
		}
	
		else{
			if(textBuf[Loop] == inBuf[0]){
				i = 0;
				while(i+1){

					if(textBuf[Loop+i] != inBuf[i]){
						textOutBuf[Loop + OutLen] = textBuf[Loop];
						Loop++;	
						i = -1;
					}
					else if(i == (inLen - 1)){
						i = -1;
						if(textBuf[Loop + inLen-1] == inBuf[inLen-1]){
							for(int k = 0;k < REPLen;k++){
								textOutBuf[Loop + OutLen + k] = repBuf[k];
							}
							OutLen += REPLen - inLen;
							BufLen += inLen - 1;
							i = -1;
							Loop+=inLen;
						}
					}

					else i++;
					
				}
			}
			else {
			
				textOutBuf[Loop + OutLen] = textBuf[Loop];
				Loop++;	
				
			}
		}
	}

	SetWindowText(Bufedt,textOutBuf);
	SendMessage(Bufedt,EM_SETSEL,0,-1);
	SendMessage(Bufedt,WM_CUT,0,0);
	SendMessage(edt,EM_SETSEL,0,-1);
	SendMessage(edt,WM_PASTE,0,0);
	SendMessage(edt,EM_SETSEL,0,-1);

	delete[] textOutBuf;
	delete[] textBuf;
	return 0;
}
int REPLACETEXT(HWND edt,bool all,HWND Bufedt = NULL,HWND Bufedtcl = NULL){
//リターン値	1:置換しました	2:全く見つかりませんでした	3:すべて置換しました
	int i = 1;
	int ct =0;
	bool ud = true;
	if(all){//ESCでwhile抜ける！
		tS=0;
		tSE = false;
		while(i){
			switch(FINDTEXT(edt,ud,NULL,NULL,true)){
				case 1:
					tSE = true;
					ct++;
					break;
				case 2:
					tSE = false;
					return 2;
				case 3:
					tSE = false;
					clipck1(Bufedtcl);
					FINDTEXTR2(edt,ct,Bufedt);
					clipck2(Bufedtcl);
					tE = -1;
					tS = 0;
					return 3;
			}
		}
	}
	else{
		switch(FINDTEXT(edt,ud,NULL,NULL,true)){
			case 1:
				SetFocus(edt);
				SendMessage(edt,EM_SETSEL,tS,tE);
				SendMessage(edt,EM_SCROLLCARET,NULL,NULL);
				SendMessage(edt,EM_REPLACESEL,1,(LPARAM)((LPTSTR)repBuf));
				SendMessage(edt,EM_SETSEL,tE,tE);
				tSE = true;
				return 1;
			case 2:
				tSE = false;
				return 2;
			case 3:
				tS = tE;
				tSE = false;
				return 3;
		}
	}
return 0;
}
int Print(HWND hwnd,HWND edt){
	PRINTDLG prt;
	DOCINFO di;
	int fonts = 0;
	int dpi;

	RECT txrc = {0,0,0,0};
	
	LPTSTR lpszBuf;
	LPWSTR Buf;

	int Len;
	nLen = GetWindowTextLength(edt);
	hMem = GlobalAlloc(GHND,sizeof(char)*nLen + 1);
	lpszBuf = (char *)GlobalLock(hMem);
	GetWindowText(edt,lpszBuf,nLen + 1);

	if(nLen == 0){
		int mb = MessageBox(hwnd,"空白だけど印刷する？","確認 - 印刷",MB_YESNO|MB_ICONQUESTION);
		if(mb == IDNO)return 0;
		wsprintf(szTitle,szWindowTitle);
	}
	else{
	
	Len = MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,lpszBuf,nLen,NULL,0);
	Buf = new WCHAR[Len+8];
	MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,lpszBuf,nLen,Buf,Len);
	wsprintf(szTitle,szTitle2,szFileTitle);
	}

	memset(&prt,9,sizeof(PRINTDLG));

	prt.lStructSize = sizeof(PRINTDLG);
	prt.hwndOwner = hwnd;//DialogBoxのオーナー
	prt.hDevMode = NULL;
	prt.hDevNames = NULL;
	prt.Flags = PD_USEDEVMODECOPIESANDCOLLATE|PD_RETURNDC|PD_NOPAGENUMS|PD_NOSELECTION|PD_HIDEPRINTTOFILE;
	prt.nMinPage = 1;//ページ範囲の最小
	prt.nMaxPage = 1;//"			"最大
	prt.nFromPage = 1;//開始ページ
	prt.nToPage = 1;//終了ページ
	prt.nCopies = 1;//部数の初期値


	if(PrintDlg(&prt) == 0)return -1;//ダイアログ

	dpi = GetDeviceCaps(prt.hDC,LOGPIXELSX);//プリンターのdpi取得
	txrc.right = GetDeviceCaps(prt.hDC,HORZRES);//幅取得
	txrc.bottom = GetDeviceCaps(prt.hDC,VERTRES);//高さ取得
	fonts = lf.lfHeight;
	lf.lfHeight = (fonts/(96/72))*(dpi/96);//dpi換算
	hFont1 = CreateFontIndirect(&lf);

	memset(&di,0,sizeof(DOCINFO));

	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = szTitle;//ドキュメント名
	
	StartDoc(prt.hDC,&di);//印刷開始
	StartPage(prt.hDC);//ページ開始(複数ページの場合ループ開始)
	
	SelectObject(prt.hDC,hFont1);

	DrawTextW(prt.hDC,Buf,Len,&txrc,DT_WORDBREAK|DT_EDITCONTROL);//10,10+~のところで余白をいじれる


	EndPage(prt.hDC);//ページ終わり(複数ページの場合ループ終わり)
	EndDoc(prt.hDC);//印刷終わり
	DeleteDC(prt.hDC);
	lf.lfHeight = fonts;
	return 0;
}
int MenuMes(DWORD Hwp,DWORD Lwp,DWORD lp,HWND hwnd){
	TCHAR StasBuf[1024];
	UINT Hflag = UINT(Hwp);
	HMENU hMainMenu = GetMenu(hwnd);
	HMENU hSubMenuDT = GetSubMenu(hMainMenu, 1);
	HMENU hmenu = (HMENU)lp;
	if((Hwp & MF_POPUP)==MF_POPUP){

		switch(Lwp){
			case 0:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_TMFILE , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case 1:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_TMEDIT , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case 2:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_TMFORM , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case 3:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_TMVIEW , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case 4:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_TMHELP , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			default:
				if(hmenu==hSubMenuDT){
					LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
						IDM_PMDT , StasBuf , 1024
					);
					SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);		
				}
				break;
			
		}
	}
	else{
		switch(Lwp){
			case IDM_NEW:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_NEW , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_OPEN:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_OPEN , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_SV:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_SV , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_SVA:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_SVA , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_PAGS:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_PAGS , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_PRT:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_PRT , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_EXIT:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_EXIT , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_UND:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_UND , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_CUT:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_CUT , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_COPY:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_COPY , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_PAST:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_PAST , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_DEL:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_DEL , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_FND:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_FND , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_NFND:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_NFND , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_REP:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_REP , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_CL:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_CL , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_OMZ:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_OMZ , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_SETA:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_SETA , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_DT1:
				DandT(NULL,NULL,NULL,ID_OP1,true);
				break;

			case IDM_DT2:
				DandT(NULL,NULL,NULL,ID_OP2,true);
				break;

			case IDM_DT3:
				DandT(NULL,NULL,NULL,ID_OP3,true);
				break;

			case IDM_DT4:
				DandT(NULL,NULL,NULL,ID_OP4,true);
				break;

			case IDM_DT5:
				DandT(NULL,NULL,NULL,ID_OP5,true);
				break;

			case IDM_DT6:
				DandT(NULL,NULL,NULL,ID_OP6,true);
				break;

			case IDM_DT7:
				DandT(NULL,NULL,NULL,ID_OP7,true);
				break;

			case IDM_DT8:
				DandT(NULL,NULL,NULL,ID_OP8,true);
				break;

			case IDM_WRT:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_WRT , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_FONT:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_FONT , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_STE:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_STE , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_HELP:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_HELP , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_VER:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_VER , StasBuf , 1024
				);
				SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;
		}
	}
	return 0;
}

LRESULT CALLBACK EditProc(HWND edt , UINT msg , WPARAM wp , LPARAM lp){

	switch(msg){
		case WM_MOUSEMOVE:
			SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)DefStastext);
			return 0;
	}
	return CallWindowProc(SubEditClass,edt,msg,wp,lp);
}

LRESULT CALLBACK WndProc(HWND hwnd , UINT msg , WPARAM wp , LPARAM lp) {
	static UINT FNDm;
	static int S,E;
	static bool ud;//検索を上へか下へか
	static bool Found;//検索なのか置換なのか
	TCHAR msgBuf[insz] = "";
	int FBLen;//FINDTEXT関数内のinBufの長さ取得
	static int Stassz[2]={50,-1};

	
	if(msg == FNDm && !(frp.Flags & FR_DIALOGTERM)){
		if(msg == FNDm && (frp.Flags & FR_DOWN))ud = true;
		else ud=false;

		if(msg == FNDm && (frp.Flags & FR_REPLACE)){//置き換え
			switch(REPLACETEXT(edt,false)){
				case 1:
					FTF1 = true;
					tSE = true;
					break;
				case 2:
					FTF1 = false;
					wsprintf(msgBuf,"\"%s\"が見つかりません",inBuf);
					MessageBox(hwnd,msgBuf,"置換",MB_ICONINFORMATION|MB_TOPMOST|MB_SYSTEMMODAL);
					tSE = false;
					break;
				case 3:
					FTF1 = false;
					MessageBox(hwnd,"すべての置換が終わりました","置換 - 完了！",MB_ICONINFORMATION|MB_TOPMOST|MB_SYSTEMMODAL);
					tSE = false;
					break;
			}
		}
		else if(msg == FNDm && (frp.Flags & FR_REPLACEALL)){//すべて置き換え
			switch(REPLACETEXT(edt,true,bufEdt1,bufEdt2)){
				case 2:
					FTF1 = false;
					wsprintf(msgBuf,"\"%s\"が見つかりません",inBuf);
					MessageBox(hwnd,msgBuf,"置換",MB_ICONINFORMATION|MB_TOPMOST|MB_SYSTEMMODAL);
					tSE = false;
					break;
				case 3:
					FTF1 = false;
					MessageBox(hwnd,"すべての置換が終わりました","置換 - 完了！",MB_ICONINFORMATION|MB_TOPMOST|MB_SYSTEMMODAL);
					tSE = false;
					break;
			}
		}
		else{//検索
			switch(FINDTEXT(edt,ud,&FBLen,true)){
			
				case 1:
					FTF1 = true;
					SetFocus(edt);
					SendMessage(edt,EM_SETSEL,tS,tE);
					SendMessage(edt,EM_SCROLLCARET,NULL,NULL);
					SendMessage(edt,EM_GETSEL,(WPARAM)&S,(LPARAM)&E);
					tSE = true;
					break;
				case 2:			
					FTF1 = false;
					wsprintf(msgBuf,"\"%s\"が見つかりません",inBuf);
					MessageBox(hwnd,msgBuf,"検索",MB_ICONINFORMATION|MB_TOPMOST|MB_SYSTEMMODAL);
					tSE = false;
					break;
				case 3:
					FTF1 = false;
					tS = S;								//*-------------------------------//
					tE = tS + FBLen;					//前回検索に引っかかった文字を選択//
					SendMessage(edt,EM_SETSEL,tS,tE);	//-------------------------------*//
					SendMessage(edt,EM_SCROLLCARET,NULL,NULL);
					MessageBox(hwnd,"すべての検索が終わりました","検索 - 完了！",MB_ICONINFORMATION|MB_TOPMOST|MB_SYSTEMMODAL);
					tSE = false;
					break;
		
			}
		}
	}
	else if(msg == FNDm && (frp.Flags & FR_DIALOGTERM)){
		FTF2 = true;
	}

	switch (msg) {
		case WM_DESTROY:
			
			MessageBox(hwnd , TEXT("End processing.Please Wait...") ,
			TEXT("...End...") , MB_ICONINFORMATION);
			PostQuitMessage(0);
			return 0;

		case WM_CLOSE:
			int id;
			EndD = "問い合わせ - 終了";
			id = SaveEx(edt);
			if(id == IDCANCEL)return 0;
			
			DestroyWindow(hwnd);
			PostQuitMessage(0);
			return 0;
/*		case WM_KILLFOCUS:
			
				SendMessage(edt,EM_GETSEL,(WPARAM)&S,(LPARAM)&E);
			

			
			return 0;*///IE風のフォーカス
		case WM_SETFOCUS:
			if(FTF1){
				SetFocus(edt);
				SendMessage(edt,EM_SETSEL,tS,tE);
			}
			else if(FTF2){
				FTF2 = false;
				SetFocus(edt);
				SendMessage(edt,EM_SETSEL,tS,tE);
			}
/*			else{
				SetFocus(edt);
				SendMessage(edt,EM_SETSEL,S,E);
			}*///IE風のフォーカス
				return 0;

		case WM_CREATE:

			
			SetWindowText(hwnd,szWindowTitle);
			InitCommonControls();


			bufEdt1 = CreateWindow(
						TEXT("EDIT") , NULL , 
						WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL | WS_BORDER | ES_LEFT | ES_MULTILINE ,
						0 , 0 , 0 , 0 , hwnd , (HMENU)1 ,
						((LPCREATESTRUCT)(lp))->hInstance , NULL
					);
			bufEdt2 = CreateWindow(
						TEXT("EDIT") , NULL , 
						WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL | WS_BORDER | ES_LEFT | ES_MULTILINE ,
						0 , 0 , 0 , 0 , hwnd , (HMENU)1 ,
						((LPCREATESTRUCT)(lp))->hInstance , NULL
					);
			edtnr = CreateWindow(//折り返しなし
						TEXT("EDIT") , NULL , 
						WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL |ES_AUTOHSCROLL | ES_AUTOVSCROLL | WS_BORDER | ES_NOHIDESEL | ES_LEFT | ES_MULTILINE ,
						0 , 0 , 0 , 0 , hwnd , (HMENU)1 ,
						((LPCREATESTRUCT)(lp))->hInstance , NULL
				);
			edtr = CreateWindow(//折り返しあり
						TEXT("EDIT") , NULL , 
						WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_NOHIDESEL | ES_AUTOVSCROLL |WS_BORDER | ES_LEFT | ES_MULTILINE ,
						0 , 0 , 0 , 0 , hwnd , (HMENU)1 ,
						((LPCREATESTRUCT)(lp))->hInstance , NULL,
				);
			Stas = CreateStatusWindow(WS_CHILD | CCS_BOTTOM | WS_VISIBLE |  SBARS_SIZEGRIP ,
						NULL,hwnd,NULL
				);

			SendMessage(Stas , SB_SETPARTS , 2 , (LPARAM)Stassz);

			SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)DefStastext);
						


			SendMessage(bufEdt1, EM_LIMITTEXT , TEXTsz, 0);
			SendMessage(bufEdt2, EM_LIMITTEXT , TEXTsz, 0);
			SendMessage(edtnr, EM_LIMITTEXT , TEXTsz, 0);
			SendMessage(edtr, EM_LIMITTEXT , TEXTsz, 0);
			edt = edtnr;

			SubEditClass = (WNDPROC)SetWindowLong(edt,GWL_WNDPROC,(LONG)EditProc);//サブクラス化
			
			lf.lfCharSet = 1;//デフォルト 文字セットＪＰ
			lf.lfHeight = -19;//デフォルト 大きさ　14pt
			strcpy_s(lf.lfFaceName,"メイリオ");//デフォルトFont
			lf.lfItalic = FALSE;
			cf.lStructSize = sizeof (CHOOSEFONT);
			cf.hwndOwner = hwnd;
			cf.lpLogFont = &lf;
			cf.Flags = CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT | CF_SELECTSCRIPT;//Option
			hFont1 = CreateFontIndirect(&lf);
			SendMessage(edt, WM_SETFONT, (WPARAM)hFont1, MAKELPARAM(FALSE, 0));

			frp.lStructSize = sizeof(FINDREPLACE);
			frp.hwndOwner = hwnd;
			frp.Flags = FR_DOWN|FR_HIDEMATCHCASE;
			frp.lpstrFindWhat = inBuf;
			frp.lpstrReplaceWith = repBuf;
			frp.wFindWhatLen = insz;
			frp.wReplaceWithLen = insz;
			
			FNDm = RegisterWindowMessage(FINDMSGSTRING);
			SetFocus(hwnd);	
			SetFocus(edt);//フォーカスをEDITに



			return 0;

		case WM_SIZE://ウインドウのサイズ変更時のイベント
			
			MoveWindow(edt,NULL,0,LOWORD(lp),HIWORD(lp)-24,1);//edtサイズ変更
			MoveWindow(Stas,NULL,0,LOWORD(lp),NULL,1);
			Stassz[0]=LOWORD(lp)*0.75;
			Stassz[1]=-1;
			SendMessage(Stas , SB_SETPARTS , 2 , (LPARAM)Stassz);
			return 0;

		case WM_COMMAND:
			
			switch(LOWORD(wp)){
			
				//---File---///
				case IDM_NEW://ボタンメッセージ
					NewF(edt);
					SetFocus(edt);
					break;

				case IDM_OPEN:
					MyOpenF(edt);
					SetFocus(edt);
					break;

				case IDM_SV:
					MySave(edt);
					SetFocus(edt);
					break;

				case IDM_SVA:
					MySaveAs(edt);
					SetFocus(edt);
					break;

				case IDM_PRT:
					Print(hwnd,edt);
					break;

				case IDM_EXIT:
					SendMessage(hwnd,WM_CLOSE,0,0);
					return 0;
		   
				//---Edit---//
				case IDM_UND:
					if(SendMessage(edt,EM_CANUNDO,0,0))
					SendMessage(edt,EM_UNDO,0,0);
					break;

				case IDM_CUT:
					SendMessage(edt,WM_CUT,0,0);
					break;

				case IDM_COPY:
					SendMessage(edt,WM_COPY,0,0);
					break;

				case IDM_PAST:
					SendMessage(edt,WM_PASTE,0,0);
					break;
				
				case IDM_DEL:
					SendMessage(edt,WM_CLEAR,0,0);
					break;

				case IDM_FND:
					tSE = false;
					Found = true;
					frp.Flags=FR_DOWN|FR_HIDEMATCHCASE;
					FindText(&frp);
					break;

				case IDM_NFND:
					if(!flFND){
						tSE = false;
						Found = true;
						frp.Flags=FR_DOWN|FR_HIDEMATCHCASE;
						FindText(&frp);
					}
					else{
						switch(FINDTEXT(edt,ud)){
							case 1:
								FTF1 = true;
								SetFocus(edt);
								SendMessage(edt,EM_SETSEL,tS,tE);
								SendMessage(edt,EM_SCROLLCARET,NULL,NULL);
								tSE = true;
								break;
							case 2:			
								FTF1 = false;
								wsprintf(msgBuf,"\"%s\"が見つかりません",inBuf);
								MessageBox(hwnd,msgBuf,"検索",MB_ICONINFORMATION|MB_TOPMOST|MB_SYSTEMMODAL);
								tSE = false;
								break;
							case 3:
								FTF1 = false;
								MessageBox(hwnd,"すべての検索が終わりました","検索 - 完了！",MB_ICONINFORMATION|MB_TOPMOST|MB_SYSTEMMODAL);
								tSE = false;
								break;
						}
					}
					break;

				case IDM_REP:
					tSE = false;
					Found = false;
					frp.Flags = FR_DOWN|FR_HIDEMATCHCASE;
					ReplaceText(&frp);
					break;

				case IDM_OMZ:
					int id;
					EndD = "問い合わせ - おまじない";
					id = SaveEx(edt);
					if(id == IDCANCEL)return 0;
					SetWindowText(edt,"#include<iostream>\r\nusing namespace std;\r\n\r\nint main(){\r\n\r\t\r\n\r\t\r\n\r\treturn 0;\r\n}");
					SendMessage(edt,EM_SETMODIFY,FALSE,0);
					SetFocus(edt);
					break;

				case IDM_SETA:
					SendMessage(edt,EM_SETSEL,0,-1);
					break;
	

				case IDM_DT1:
					DandT(edt,bufEdt1,bufEdt2,ID_OP1);
					break;

				case IDM_DT2:
					DandT(edt,bufEdt1,bufEdt2,ID_OP2);
					break;

				case IDM_DT3:
					DandT(edt,bufEdt1,bufEdt2,ID_OP3);
					break;

				case IDM_DT4:
					DandT(edt,bufEdt1,bufEdt2,ID_OP4);
					break;

				case IDM_DT5:
					DandT(edt,bufEdt1,bufEdt2,ID_OP5);
					break;

				case IDM_DT6:
					DandT(edt,bufEdt1,bufEdt2,ID_OP6);
					break;

				case IDM_DT7:
					DandT(edt,bufEdt1,bufEdt2,ID_OP7);
					break;
				case IDM_DT8:
					DandT(edt,bufEdt1,bufEdt2,ID_OP8);
					break;

				//---fOrmat---//
				case IDM_WRT:
					
					nLen = GetWindowTextLength(edt);
					hMem = GlobalAlloc(GHND,sizeof(char)*nLen + 1);
					lpszBuf = (char *)GlobalLock(hMem);
					GetWindowText(edt,lpszBuf,nLen + 1);
					ShowWindow(edt,SW_HIDE);
					RECT rectw;

					if(edt == edtnr){	
						edt = edtr;
						CheckMenuItem(GetMenu(hwnd),IDM_WRT, MF_CHECKED);
					}
					else{
						edt = edtnr;
						CheckMenuItem(GetMenu(hwnd),IDM_WRT, MF_UNCHECKED);
					}
					ShowWindow(edt,SW_SHOW);
					GetClientRect(hwnd,&rectw);//SIZE
					SendMessage(hwnd,WM_SIZE,NULL,MAKELPARAM(rectw.right,rectw.bottom));//SIZE

					SetFocus(edt);
					SendMessage(edt, WM_SETFONT, (WPARAM)hFont1, MAKELPARAM(FALSE, 0));
					SetWindowText(edt,lpszBuf);
				
					break;

				case IDM_FONT:
					ChooseFont(&cf);
					hFont1 = CreateFontIndirect(&lf);//font;
					SendMessage(edt, WM_SETFONT, (WPARAM)hFont1, MAKELPARAM(FALSE, 0));
					InvalidateRect(hwnd, NULL, TRUE);
					SetFocus(edt);
					break;

				//---Help---//
				case IDM_HELP:
					MessageBox(hwnd,"このプログラムは試作段階です\r\nメニューコマンドの\"-\"は未完成orデバッグ中です\r\nVer:0.6\r\nUNICODE対応！検索強化+高速置換ver.",szWindowTitle,MB_ICONINFORMATION);
					break;

				}
			return 0;
	
	case WM_INITMENUPOPUP:
		switch(LOWORD(lp)){
		case 1:
			if(SendMessage(edt,EM_CANUNDO,0,0)) {
				EnableMenuItem(GetMenu(hwnd),IDM_UND,MF_ENABLED);
			}
			else{
				EnableMenuItem(GetMenu(hwnd),IDM_UND,MF_GRAYED);
			}

			int tStart,tEnd;
			SendMessage(edt,EM_GETSEL,(WPARAM)&tStart,(LPARAM)&tEnd);

			if(tStart == tEnd){
				EnableMenuItem(GetMenu(hwnd),IDM_CUT,MF_GRAYED);
				EnableMenuItem(GetMenu(hwnd),IDM_COPY,MF_GRAYED);
				EnableMenuItem(GetMenu(hwnd),IDM_DEL,MF_GRAYED);
			}
			else{
				EnableMenuItem(GetMenu(hwnd),IDM_CUT,MF_ENABLED);
				EnableMenuItem(GetMenu(hwnd),IDM_COPY,MF_ENABLED);
				EnableMenuItem(GetMenu(hwnd),IDM_DEL,MF_ENABLED);
			}

			if(IsClipboardFormatAvailable(CF_TEXT)){
				EnableMenuItem(GetMenu(hwnd),IDM_PAST,MF_ENABLED);
			}
			else {
				EnableMenuItem(GetMenu(hwnd),IDM_PAST,MF_GRAYED);
			}
		}
			return 0;
	case WM_NCMOUSEMOVE://外部でもMouseMoveを処理できる
	case WM_MOUSEMOVE:
		SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)DefStastext);
		return 0;
	
	case WM_MENUSELECT:
		MenuMes(HIWORD(wp),LOWORD(wp),lp,hwnd);
		return 0;

}

	return DefWindowProc(hwnd , msg , wp , lp);
}



int WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInstance ,
		 PSTR lpCmdLine , int nCmdShow )  {
	HWND hwnd;
	MSG msg;
	WNDCLASS winc;
	HACCEL hAcce;

	hAcce = LoadAccelerators(hInstance,MAKEINTRESOURCE(IDR_ACCELERATOR));//アクセラレーター　ロード

	winc.style		= CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc	= WndProc;
	winc.cbClsExtra	= winc.cbWndExtra	= 0;
	winc.hInstance		= hInstance;
	winc.hIcon		= LoadIcon(hInstance , TEXT("ICON1"));
	winc.hCursor		= LoadCursor(hInstance , TEXT("cursol1"));
	winc.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName	= MAKEINTRESOURCE(IDR_NOTEM);
	winc.lpszClassName	= TEXT("TextEditer");

	if (!RegisterClass(&winc)) return 0;

	hwnd = CreateWindow(
			TEXT("TextEditer") , TEXT("Editer") ,
			WS_OVERLAPPEDWINDOW  | WS_VISIBLE ,
			CW_USEDEFAULT , CW_USEDEFAULT , CW_USEDEFAULT ,CW_USEDEFAULT  , NULL , LoadMenu(hInstance , MAKEINTRESOURCE(IDR_NOTEM))  ,
			hInstance , NULL
	);



	if (hwnd == NULL) return 0;
	while (GetMessage(&msg , NULL , 0 , 0)) {
		if(!TranslateAccelerator(hwnd,hAcce,&msg)){//アクセラレーターMSG
			TranslateMessage(&msg);DispatchMessage(&msg);
		}
	}
		
	return msg.wParam;

}