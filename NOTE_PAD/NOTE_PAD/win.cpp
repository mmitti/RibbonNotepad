//RichEditにする//RICHEDIT_CLASS//RichEdit
			  //--------------------//
			 //!!"/DEL"は削除予定!!//
			//--------------------//
//完了//http://eternalwindows.jp/control/controlbase/controlbase09.html
//EditMessage//http://hp.vector.co.jp/authors/VA024411/vbtips03.html#05
//CheckMenuRadioItem(GetMenu(hwnd), メニューアイテム始まりのID,メニューアイテムおわりのID, メニューアイテムアイコンをセットするID, MF_BYCOMMAND ); ***ラジオボタンのチェック
//MessageBoxの改行*/\r\n/*
//ステータスバーの中央,右揃えは\t,\t\t

//EM_LINEFROMCHAR現在の行番号を取得
//http://support.microsoft.com/kb/186271/ja
//SendMessage(edt,EM_SETSEL,0,(SendMessage(edt,EM_LINEINDEX,3,0)));

//TODO
//dmCollate SetPrinter関数内　これで印刷時の部単位で印刷が実装できる？
//完了//dmDuplex SetPrinter関数内およびRC,PageSetHook 両面印刷も実装しようよ
//ヘッダーとフッター
//置換中にいくつ置き換えたかをステータスバーへ



#include<windows.h>
#include"resource.h"
#include <commctrl.h>
#pragma comment(lib,"Comctl32.lib")//Libのリンク
#pragma comment(lib, "imm32.lib")



HFONT hFont1;
HWND edt;
HWND edtnr;
HWND edtr;
HWND bufEdt1,bufEdt2;
HWND State;
HWND prbufedt;
WNDPROC SubEditClass;
LOGFONT lf={0};//必須
CHOOSEFONT cf;//必須
LPCHOOSEFONT pcf;
PAGESETUPDLG psd;//PrintDialog用

TCHAR szFile[256];
TCHAR szFileTitle[256] = TEXT("");
const TCHAR szWindowTitle[128] = TEXT("ただのテキストエディター");//ウインドウのタイトル
TCHAR szTitle[128];
TCHAR* szTitle2 = TEXT("ただのテキストエディター - %s");
LPCTSTR EndD;
OPENFILENAME ofn;
HANDLE hFile;
DWORD dwAccBytes;
TCHAR *lpszBuf;
int nLen;
HGLOBAL hMem;
DWORD dwSize;

HGLOBAL h_devMode;//setPage, Printよう

bool filesv = false;

int tS,tE;
const int TEXTsz=1024*384;
FINDREPLACE frp;//FindText

bool FTF1 = false,FTF2 = false;

const int insz = 256;//検索ダイアログ入力も文字数
TCHAR inBuf[insz] = TEXT("");
TCHAR repBuf[insz] = TEXT("");
bool tSE = false;//１回目かどうか＠検索
bool flFND = false;//検索をしたことがあるか
	
TCHAR DefStastext[128] = TEXT("Ready");
TCHAR StasBuf[1024];//ステータスバーのテキスト用Buf
TCHAR TextBuf[1024];//リソースからのテキストを読み込む

RECT rcMargin={2000,2500,2000,2500};//余白の初期値2000=20mm

enum CheckEncode_ {ANSI_en, UNICODE_en} cEncode;

int LoadStr(LPTSTR out, size_t size, DWORD resource){

	return LoadString(GetModuleHandle(NULL), resource, out, size);
}
int ShowErrorMessageBox(DWORD mode, int ErrorCode = 0, HWND hwnd = NULL, UINT MsgType = MB_OK | MB_ICONERROR){
	TCHAR caption[1024], msgtext[1024], format[1024];
	
	switch(mode){//共通でないテキストの読み込み
	case IDT_ERT_PSET1:
		LoadStr(msgtext, sizeof(caption), IDT_ERT_PSET1);
		break;

	case IDT_ERT_PSET2:
		LoadStr(msgtext, sizeof(caption), IDT_ERT_PSET2);
		break;

	case IDT_ERT_PSET3:
		LoadStr(msgtext, sizeof(caption), IDT_ERT_PSET3);
		break;

	case IDT_ERT_PSET4:
		LoadStr(msgtext, sizeof(caption), IDT_ERT_PSET4);
		break;

	case IDT_ERT_PSET5:
		LoadStr(msgtext, sizeof(caption), IDT_ERT_PSET5);
		break;

	}

	switch(mode){//共通部分のテキストの読み込み

	case IDT_ERT_PSET1:
	case IDT_ERT_PSET2:
	case IDT_ERT_PSET3:
	case IDT_ERT_PSET4:
	case IDT_ERT_PSET5:
		LoadStr(caption, sizeof(caption), IDT_ERC_PSET);
		LoadStr(format, sizeof(caption), IDT_ERF_PSET);
		wsprintf(msgtext, format, msgtext, ErrorCode);
		break;

	default:
		break;
	}

	MessageBox(hwnd, msgtext, caption, MsgType);
	return 0;
}

void SetLLenState(HWND edt){
	int S=0,E=0,Line=0,LLen=0;
	Line=SendMessage(edt,EM_LINEFROMCHAR,-1,0);//行数取得
	LLen=SendMessage(edt,EM_LINEINDEX,-1,0);//文字数
	SendMessage(edt,EM_GETSEL,(WPARAM)&S,(LPARAM)&E);
	if(S==E){
		LoadStr(TextBuf, sizeof(TextBuf), IDT_STEXT1);
		wsprintf(StasBuf,TextBuf,Line+1,E-LLen);
	}
	else{
		LoadStr(TextBuf, sizeof(TextBuf), IDT_STEXT2);
		wsprintf(StasBuf,TextBuf,E-S);
	}
	SendMessage(State,SB_SETTEXT,1|0,(LPARAM)StasBuf);
}
void SetIMEState(HWND edt){
	DWORD ime_in, ime_mode;
	BOOL ime_on;
	static DWORD ime_bin = NULL, ime_bmode = NULL;
	static BOOL ime_bon = false;

	HIMC hImm;
	TCHAR ime_text[1024], ime_tin[1024], ime_tmode[1024] ,ime_tRomaKana[1024];
	
	hImm = ImmGetContext(edt);

	ImmGetConversionStatus(hImm, &ime_in, &ime_mode);
	ime_on = ImmGetOpenStatus(hImm);

	ImmReleaseContext(edt, hImm);
	if(ime_bin != ime_in || ime_bmode != ime_mode || ime_bon != ime_on){
	
	
		if(ime_on){
			if(ime_in & IME_CMODE_KATAKANA && ime_in & IME_CMODE_FULLSHAPE)LoadStr(ime_tin, sizeof(ime_tin), IDT_STIME_IFK);
			else if(ime_in & IME_CMODE_KATAKANA && ime_in ^ IME_CMODE_FULLSHAPE)LoadStr(ime_tin, sizeof(ime_tin), IDT_STIME_IK);
			else if(ime_in & IME_CMODE_JAPANESE && ime_in & IME_CMODE_FULLSHAPE)LoadStr(ime_tin, sizeof(ime_tin), IDT_STIME_IH);
			else if(ime_in & IME_CMODE_FULLSHAPE )LoadStr(ime_tin, sizeof(ime_tin), IDT_STIME_IFA);
			else LoadStr(ime_tin, sizeof(ime_tin), IDT_STIME_IA);
		}
		else LoadStr(ime_tin, sizeof(ime_tin), IDT_STIME_IA);
		
		if(ime_mode & IME_SMODE_PHRASEPREDICT)LoadStr(ime_tmode, sizeof(ime_tmode), IDT_STIME_MG);
		else if(ime_mode & IME_SMODE_PLAURALCLAUSE)LoadStr(ime_tmode, sizeof(ime_tmode), IDT_STIME_MN);
		else if(ime_mode & IME_SMODE_CONVERSATION)LoadStr(ime_tmode, sizeof(ime_tmode), IDT_STIME_MS);
		else LoadStr(ime_tmode, sizeof(ime_tmode), IDT_STIME_MNA);

		if(ime_in & IME_CMODE_ROMAN)LoadStr(ime_tRomaKana, sizeof(ime_tRomaKana), IDT_STIME_ROMA);
		else LoadStr(ime_tRomaKana, sizeof(ime_tRomaKana), IDT_STIME_KANA);

		LoadStr(TextBuf, sizeof(TextBuf), IDT_STIME_T);
		wsprintf(ime_text, TextBuf, ime_tin, ime_tmode, ime_tRomaKana);
		SendMessage(State,SB_SETTEXT,3|0,(LPARAM)ime_text);
	}
	ime_bin = ime_in;
	ime_bmode = ime_mode;
	ime_bon = ime_on;

}
void SetEncodeState(){

	if(cEncode == ANSI_en) LoadStr(TextBuf, sizeof(TextBuf), IDT_STEN_ANSI);
	else if(cEncode == UNICODE_en) LoadStr(TextBuf, sizeof(TextBuf), IDT_STEN_UNI);

	SendMessage(State,SB_SETTEXT,2|0,(LPARAM)TextBuf);
}

int setup(){
	static TCHAR BufFil[1024], BufDef[1024];

	memset(&ofn,0,sizeof(OPENFILENAME));//ofnに0を代入

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = edt;
	
	//ofn.lpstrFilter = TEXT("テキストファイル(*.txt)\0*.txt\0c++ファイル(*.cpp)\0*.cpp\0cファイル(*.c)\0*.c\0All files(*.*)\0*.*\0\0");/DEL
	LoadStr(BufFil, sizeof(BufFil), IDT_FFILTER);
	ofn.lpstrFilter = BufFil;
	ofn.lpstrFile = szFile;
	ofn.lpstrFileTitle = szFileTitle;
	ofn.nFilterIndex = 1;
	ofn.nMaxFile = MAX_PATH;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.Flags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY ;
	LoadStr(BufDef, sizeof(BufDef), IDT_FOPENDEF);
	ofn.lpstrDefExt = BufDef;
	return 0;
}
int clipck1(HWND bufEdt2,bool ck=true){
	if(IsClipboardFormatAvailable(CF_TEXT)&&ck){
		SendMessage(bufEdt2,WM_PASTE,0,0);
	}
	else if(!ck)SendMessage(bufEdt2,WM_PASTE,0,0);
	return 0;
}
int clipck2(HWND bufEdt2,bool ck=true){	
	if(IsClipboardFormatAvailable(CF_TEXT)&&ck){
		SendMessage(bufEdt2,EM_SETSEL,0,-1);
		SendMessage(bufEdt2,WM_COPY,0,0);
		SetWindowText(bufEdt2,TEXT(""));
	}
	else if (!ck){
		SendMessage(bufEdt2,EM_SETSEL,0,-1);
		SendMessage(bufEdt2,WM_COPY,0,0);
		SetWindowText(bufEdt2,TEXT(""));
	}
	return 0;
}
int MySaveAs(HWND edt){
	int Len;

	nLen = GetWindowTextLength(edt);
	//hMem = GlobalAlloc(GHND,sizeof(TCHAR)*nLen + 1);/DEL
	lpszBuf = new TCHAR[sizeof(TCHAR)*nLen + 1];
	GetWindowText(edt,lpszBuf,nLen + 1);

	
	setup();
	LoadStr(TextBuf, sizeof(TextBuf), IDT_DTSAVEAS);
	wsprintf(szTitle,TextBuf,szWindowTitle);

	ofn.lpstrTitle = TEXT("名前を付けて保存");
	

	if(GetSaveFileName(&ofn) == 0)return -1;

	LoadStr(szTitle, sizeof(szTitle), IDT_WTSAVEASI);

	SetWindowText(GetParent(edt),szTitle);	
	hFile = CreateFile(szFile,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(cEncode == UNICODE_en){
		/*UNICODE*/
		WriteFile(hFile,lpszBuf,(DWORD)(wcslen(lpszBuf) * sizeof(TCHAR)),&dwAccBytes,NULL);
	}
	else if(cEncode == ANSI_en){
		/*Shift-JIS*/
		Len = WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, lpszBuf, nLen, NULL, 0, NULL, NULL);
		DWORD er = GetLastError();
		CHAR* lpszcBuf = new CHAR[Len + 8];
		lpszcBuf[Len] = TEXT('\0');
		WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, lpszBuf, nLen, lpszcBuf, Len, NULL, NULL);
		WriteFile(hFile,lpszcBuf,(DWORD)strlen(lpszcBuf),&dwAccBytes,NULL);
	}
	if(CloseHandle(hFile) == 0){
		MessageBox(edt,TEXT("NOT CLOSE HANDLE"),TEXT("ERROR"),MB_OK);
		wsprintf(szTitle,szTitle,szFileTitle);
		SetWindowText(GetParent(edt),szTitle);
	}

	wsprintf(szTitle,szTitle2,szFileTitle);
	SetWindowText(GetParent(edt),szTitle);
	
	SendMessage(edt,EM_SETMODIFY,FALSE,0);

	//GlobalUnlock(hMem);/DEL
	//GlobalFree(hMem);/DEL
	delete [] lpszBuf;
	filesv = true;
	return 0;
}
int MySave(HWND edt){
	int Len;
	if(wcscmp(szFile,TEXT("")) == 0){
		MySaveAs(edt);
		return -1;
	}

	nLen = GetWindowTextLength(edt);
	hMem = GlobalAlloc(GHND,sizeof(TCHAR)*nLen + 1);
	lpszBuf = (TCHAR *)GlobalLock(hMem);
	GetWindowText(edt,lpszBuf,nLen + 1);

	LoadStr(TextBuf, sizeof(TextBuf), IDT_WTSAVEI);
	wsprintf(szTitle,TextBuf);
	SetWindowText(GetParent(edt),szTitle);

	hFile = CreateFile(szFile,GENERIC_WRITE,0,NULL,TRUNCATE_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(cEncode == UNICODE_en){	
		/*UNICODE*/
				WriteFile(hFile,lpszBuf,(DWORD)(wcslen(lpszBuf) * sizeof(TCHAR)),&dwAccBytes,NULL);
	}
	else if(cEncode == ANSI_en){
		/*Shift-JIS*/
		Len = WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, lpszBuf, nLen, NULL, 0, NULL, NULL);
		DWORD er = GetLastError();
		CHAR* lpszcBuf = new CHAR[Len + 8];
		lpszcBuf[Len] = TEXT('\0');
		WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, lpszBuf, nLen, lpszcBuf, Len, NULL, NULL);
		WriteFile(hFile,lpszcBuf,(DWORD)strlen(lpszcBuf),&dwAccBytes,NULL);
	}

	if(CloseHandle(hFile) == 0){
		hFile = CreateFile(szFile,GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL);
		WriteFile(hFile,lpszBuf,(DWORD)wcslen(lpszBuf),&dwAccBytes,NULL);
		if(CloseHandle(hFile) == 0){
			MessageBox(edt,TEXT("NOT CLOSE HANDLE"),TEXT("ERROR"),MB_OK);
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
				LoadStr(TextBuf, sizeof(TextBuf), IDT_EXMSAVE);
				id =MessageBox(edt , TextBuf,
				EndD ,MB_YESNOCANCEL | MB_ICONINFORMATION);
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
int MyOpenF(HWND edt, bool showD = true){
	int id, Len;

	LoadStr(TextBuf, sizeof(TextBuf), IDT_EXTOPEN);
	EndD = TextBuf;
	id = SaveEx(edt);
	if(id == IDCANCEL)return 0;

	if(showD){
		//dwSize =OL;
		setup();
		LoadStr(TextBuf, sizeof(TextBuf), IDT_DTOPEN);
		wsprintf(szTitle,TextBuf,szWindowTitle);
		ofn.lpstrTitle = szTitle;


		if(GetOpenFileName(&ofn) == 0)return -1;//szFile に　パスが入る
	}

	hFile =CreateFile(szFile,GENERIC_READ,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	dwSize = GetFileSize(hFile,NULL);
	//hMem = GlobalAlloc(GHND,sizeof(TCHAR)*dwSize + 1);/DEL
	/*if(hMem == NULL){
		MessageBox(edt,TEXT("NOT OPEN FILE"),TEXT("ERROR"),MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}*///DEL
	//lpszBuf = (TCHAR *)GlobalLock(hMem);/DEL

	if(cEncode == UNICODE_en){
		//UNICODE
		lpszBuf = new TCHAR[dwSize/sizeof(TCHAR) + 1];//危ないかも？
		lpszBuf[dwSize/sizeof(TCHAR)] = TEXT('\0');//ゴミけし
		ReadFile(hFile,lpszBuf,dwSize,&dwAccBytes,NULL);

		SetWindowText(edt,lpszBuf);
	}
	else if(cEncode == ANSI_en){
		//Shift-JIS
		CHAR* lpszcBuf = new CHAR[sizeof(TCHAR)*dwSize + 1];
		ReadFile(hFile,lpszcBuf,dwSize,&dwAccBytes,NULL);
		lpszcBuf[dwAccBytes] = TEXT('\0');
		Len = MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,lpszcBuf,dwSize,NULL,0);
		LPTSTR Buf = new TCHAR[Len];
		lpszcBuf[Len+1] = TEXT('\0');//'ゴミ'をつけないため
		MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,lpszcBuf,dwSize,Buf,Len);
		SetWindowText(edt,Buf);
		delete [] Buf;
	}

	wsprintf(szTitle,szTitle2,szFileTitle);
	SetWindowText(GetParent(edt),szTitle);
	CloseHandle(hFile);
	//GlobalUnlock(hMem);/DEL
	//GlobalFree(hMem);/DEL
	delete [] lpszBuf;
	filesv = true;
	return 0;
}
int NewF(HWND edt){
	int id;
	
	LoadStr(TextBuf, sizeof(TextBuf), IDT_EXTNEW);
	EndD = TextBuf;
	id = SaveEx(edt);
	if(id == IDCANCEL)return 0;
	SetWindowText(edt,TEXT(""));
	SetWindowText(GetParent(edt),szWindowTitle);
	wcscpy_s(szFile,TEXT(""));
	return 0;
}
int DandT(HWND edt,HWND  bufEdt1,HWND bufEdt2,int op,bool MenuMes=false){
	SYSTEMTIME st;
	TCHAR szBuf[256];
	LPTSTR str;
	GetLocalTime(&st);
	
	switch(op){
		case ID_OP1:
			if(MenuMes) wsprintf(szBuf,TEXT("形式1:%d:%d:%d"),st.wHour,st.wMinute,st.wSecond);
			else wsprintf(szBuf,TEXT("%d:%d:%d"),st.wHour,st.wMinute,st.wSecond);
			break;
		case ID_OP2:
			if(MenuMes) wsprintf(szBuf,TEXT("形式2:%d時%d分%d秒"),st.wHour,st.wMinute,st.wSecond);
			else wsprintf(szBuf,TEXT("%d時%d分%d秒"),st.wHour,st.wMinute,st.wSecond);
			break;
		case ID_OP3:
			if(st.wHour/12 >= 1)str = TEXT("PM");
			else str = TEXT("AM");
			if(MenuMes) wsprintf(szBuf,TEXT("形式3:%d:%d(%s)"),st.wHour%12,st.wMinute,str);
			else wsprintf(szBuf,TEXT("%d:%d(%s)"),st.wHour%12,st.wMinute,str);
			break;
		case ID_OP4:
			if(MenuMes) wsprintf(szBuf,TEXT("形式4:%d/%d/%d"),st.wYear,st.wMonth,st.wDay);
			else wsprintf(szBuf,TEXT("%d/%d/%d"),st.wYear,st.wMonth,st.wDay);
			break;
		case ID_OP5:
			if(MenuMes) wsprintf(szBuf,TEXT("形式5:%d年%d月%d日"),st.wYear,st.wMonth,st.wDay);
			else wsprintf(szBuf,TEXT("%d年%d月%d日"),st.wYear,st.wMonth,st.wDay);
			break;
		case ID_OP6:
			if(MenuMes) wsprintf(szBuf,TEXT("形式6:%d/%d/%d %d:%d"),st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute);
			else wsprintf(szBuf,TEXT("%d/%d/%d %d:%d"),st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute);
			break;
		case ID_OP7:
			switch(st.wDayOfWeek){
				case 0:
					str = TEXT("（日）");
					break;
				case 1:
					str = TEXT("（月）");
					break;
				case 2:
					str = TEXT("（火）");
					break;
				case 3:
					str = TEXT("（水）");
					break;
				case 4:
					str = TEXT("（木）");
					break;
				case 5:
					str = TEXT("（金）");
					break;
				case 6:
					str = TEXT("（土）");
					break;
			}
			if(MenuMes) wsprintf(szBuf,TEXT("形式7:%s"),str);
			else wsprintf(szBuf,TEXT("%s"),str);
			break;
		case ID_OP8:
			switch(st.wDayOfWeek){
				case 0:
					str = TEXT("SUN");
					break;
				case 1:
					str = TEXT("MON");
					break;
				case 2:
					str = TEXT("TUE");
					break;
				case 3:
					str = TEXT("WED");
					break;
				case 4:
					str = TEXT("THU");
					break;
				case 5:
					str = TEXT("FRY");
					break;
				case 6:
					str = TEXT("SAT");
					break;
			}
			if(MenuMes)wsprintf(szBuf,TEXT("形式8：%s"),str);
			else wsprintf(szBuf,TEXT("%s"),str);
			break;
	}
	if(MenuMes){SendMessage(State,SB_SETTEXT,0|0,(LPARAM)szBuf);}
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
//置き換えもやってるようだ（）恐ろしい
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
	TCHAR* textBuf = new TCHAR[nLen + 16];
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
	TCHAR* rc = TEXT("");
	int Loop=0,i=0,inLen=0,REPLen=0,OutLen=0,BufLen=0;
	inLen=lstrlen(inBuf);
	REPLen=lstrlen(repBuf);
	nLen = GetWindowTextLength(edt);
	TCHAR* textBuf = new TCHAR[nLen + 16];
	GetWindowText(edt,textBuf,nLen + 1);
	TCHAR* textOutBuf = new TCHAR[nLen + ((REPLen - inLen) * ct)+16];
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

					LoadStr(TextBuf, sizeof(TextBuf), IDT_SREPALL);
					wsprintf(StasBuf,TextBuf,ct);
					SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
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
int Print(HWND hwnd,HWND edt,HWND bufedt,HWND bufEdt1,HWND bufEdt2){
	//タブが改行に解釈されているっポイ
	//幅の換算がおかしい？
	LoadStr(TextBuf, sizeof(TextBuf), IDT_WTPRINT);
	wsprintf(StasBuf,TextBuf);
	SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
	PRINTDLG prt;
	DOCINFO di;
	int fonts = 0;
	int dpi,allLine,loop;
	TEXTMETRIC tm;
	RECT bufEdit={0,0,0,0};


	RECT txrc = {0,0,0,0};
	
	LPTSTR lpszBuf;

	int Len=0;
	nLen = GetWindowTextLength(edt);
	hMem = GlobalAlloc(GHND,sizeof(TCHAR)*nLen + 1);
	lpszBuf = (TCHAR *)GlobalLock(hMem);
	GetWindowText(edt,lpszBuf,nLen + 1);

	if(nLen == 0){
		TCHAR TextBuf1[1024], TextBuf2[1024];
		LoadStr(TextBuf1, sizeof(TextBuf), IDT_MPRINT);
		LoadStr(TextBuf2, sizeof(TextBuf), IDT_MTPRINT);
		int mb = MessageBox(hwnd,TextBuf1,TextBuf2,MB_YESNO|MB_ICONQUESTION);
		if(mb == IDNO)return 0;
		wsprintf(szTitle,szWindowTitle);
	}
	else{
		wsprintf(szTitle,szTitle2,szFileTitle);
	}
	//Len = MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,lpszBuf,nLen,NULL,0);/DEL
	Len = wcslen(lpszBuf);
	//Buf = new TCHAR[Len+8];/DEL
	//MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,lpszBuf,nLen,Buf,Len);/DEL
	//wcscpy_s(Buf,Len + 16,lpszBuf);/DEL

	memset(&prt,9,sizeof(PRINTDLG));
	SetWindowText(bufedt,lpszBuf);
	//delete[] Buf;//落ちる/DEL
	clipck1(bufEdt2,false);

	prt.lStructSize = sizeof(PRINTDLG);
	prt.hwndOwner = hwnd;//DialogBoxのオーナー
	prt.hDevMode = NULL;
	prt.hDevNames = NULL;
	prt.Flags = PD_USEDEVMODECOPIESANDCOLLATE|PD_RETURNDC|PD_NOPAGENUMS|PD_NOSELECTION|PD_HIDEPRINTTOFILE|PD_NOPAGENUMS;
	/*	prt.nMinPage = 1;//ページ範囲の最小
	prt.nMaxPage = 1;//"			"最大
	prt.nFromPage = 1;//開始ページ
	prt.nToPage = 1;//終了ページ*/
	prt.nCopies = 1;//部数の初期値

	prt.hDevMode = h_devMode;


	if(PrintDlg(&prt) == 0)
		return -1;//ダイアログ

	h_devMode = prt.hDevMode;

	LoadStr(TextBuf, sizeof(TextBuf), IDT_SPRINT1);
	wsprintf(StasBuf,TextBuf);
	SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);

	dpi = GetDeviceCaps(prt.hDC,LOGPIXELSX);//プリンターのdpi取得
	txrc.right = GetDeviceCaps(prt.hDC,HORZRES);//幅取得
	txrc.bottom = GetDeviceCaps(prt.hDC,VERTRES);//高さ取得
	fonts = lf.lfHeight;
	hFont1 = CreateFontIndirect(&lf);
	SendMessage(bufedt, WM_SETFONT, (WPARAM)hFont1, MAKELPARAM(FALSE, 0));
	lf.lfHeight = (fonts/(96/72))*(dpi/96);//dpi換算
	hFont1 = CreateFontIndirect(&lf);

	SelectObject(prt.hDC,hFont1);//FontSet

	GetTextMetrics(prt.hDC,&tm);
	txrc.bottom-=(int)((psd.rtMargin.bottom/100)*dpi/25.4);
	txrc.left=(int)((psd.rtMargin.left/100)*dpi/25.4);
	txrc.right-=(int)((psd.rtMargin.right/100)*dpi/25.4);
	txrc.top=(int)((psd.rtMargin.top/100)*dpi/25.4);

	int t=(txrc.bottom-txrc.top)/(tm.tmHeight);//1ページの最大行数
	bufEdit.bottom=(int)(((txrc.bottom-txrc.top)*25.4/dpi)*96/25.4);
	bufEdit.right=(int)(((txrc.right-txrc.left)*25.4/dpi)*96/25.4);

	MoveWindow(bufedt,0-bufEdit.right,0-bufEdit.bottom,bufEdit.right,bufEdit.bottom,1);
//MoveWindow(bufedt,0 ,0,bufEdit.right,bufEdit.bottom,1);

	allLine=SendMessage(bufedt,EM_GETLINECOUNT,0,0);

	loop=(int)(allLine/t)+1;//10/5=2+1となるのでそこの判定


	memset(&di,0,sizeof(DOCINFO));

	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = szTitle;//ドキュメント名
	
	StartDoc(prt.hDC,&di);//印刷開始
	LoadStr(TextBuf, sizeof(TextBuf), IDT_SPRINT2);
	wsprintf(StasBuf,TextBuf);
	SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
	for(int k=1;k<=loop;k++){
		SetWindowText(bufEdt1,TEXT(""));
		LoadStr(TextBuf, sizeof(TextBuf), IDT_SPRINT3);
		wsprintf(StasBuf,TextBuf,loop,k);
		SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);

		if(k==loop)SendMessage(bufedt,EM_SETSEL,0,-1);
		else SendMessage(bufedt,EM_SETSEL,0,(SendMessage(bufedt,EM_LINEINDEX,t,0)));
		SendMessage(bufedt,WM_CUT,0,0);
		SendMessage(bufEdt1,WM_PASTE,0,0);

		lpszBuf = TEXT("");
		nLen = GetWindowTextLength(bufEdt1);
		hMem = GlobalAlloc(GHND,sizeof(TCHAR)*nLen + 1);
		lpszBuf = (TCHAR *)GlobalLock(hMem);
		GetWindowText(bufEdt1,lpszBuf,nLen + 1);

		//Len = MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,lpszBuf,nLen,NULL,0);/DEL
		Len = wcslen(lpszBuf);
		//Buf = new TCHAR[Len+8];/DEL
		//MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,lpszBuf,nLen,Buf,Len);/DEL
		//wcscpy_s(Buf,Len + 16,lpszBuf);/DEL

		StartPage(prt.hDC);//ページ開始(複数ページの場合ループ開始)
		DrawText(prt.hDC,lpszBuf,Len,&txrc,DT_WORDBREAK|DT_EDITCONTROL|DT_LEFT|DT_EXPANDTABS);//10,10+~のところで余白をいじれる
		EndPage(prt.hDC);//ページ終わり(複数ページの場合ループ終わり)
		//delete[] Buf;/DEL

	}

	EndDoc(prt.hDC);//印刷終わり
	LoadStr(TextBuf, sizeof(TextBuf), IDT_SPRINT4);
	wsprintf(StasBuf,TextBuf);
	SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
	DeleteDC(prt.hDC);
	lf.lfHeight = fonts;
	clipck2(bufEdt2,false);
	ShowWindow(edt,SW_SHOW);
	SetFocus(edt);
	return 0;
}
/*int SerPrint(HWND hdlg){//プリンターへページ設定を反映
	//DEVMODE構造体//http://www.activebasic.com/help_center/Pages/API/GDI/Printer/type_DEVMODE.htm
	//PrintDialog//http://homepage2.nifty.com/c_lang/sdk3/sdk_298.htm
	DEVMODE *dlgDate = NULL;
	LPHANDLE printerHandle;
	PRINTER_DEFAULTS pdef;

	DWORD prtSize, prtSum;//サイズ, プリンターの個数

	LoadStr(TextBuf, sizeof(TextBuf), IDT_SPSETDO1);
	wsprintf(StasBuf,TextBuf);
	SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);

	dlgDate = (DEVMODE *)GlobalLock(psd.hDevMode);

	EnumPrinters(PRINTER_ENUM_LOCAL | PRINTER_ENUM_NETWORK, NULL, 2, NULL, 0, &prtSize, &prtSum);

	LPPRINTER_INFO_2 printerInfo =(LPPRINTER_INFO_2)malloc(prtSize);

	if(EnumPrinters(PRINTER_ENUM_LOCAL | PRINTER_ENUM_NETWORK, NULL, 2, (LPBYTE)printerInfo, prtSize, &prtSize, &prtSum) == 0){//プリンター情報取得
		ShowErrorMessageBox(IDT_ERT_PSET1, GetLastError(), hdlg);
		//return -1;
	}

	memset(&pdef, 0, sizeof(PRINTER_DEFAULTS));//初期化
	pdef.DesiredAccess = PRINTER_ALL_ACCESS;//プリンターのアクセス権を変更（しないとsetPrinterでエラーになる

	for(DWORD i = 0; i < prtSum; i++){
		LoadStr(TextBuf, sizeof(TextBuf), IDT_SPSETDO2);
		wsprintf(StasBuf, TextBuf, prtSum, i+1);
		SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
		
		printerHandle = new HANDLE;

		if(OpenPrinter((LPWSTR)printerInfo[i].pPrinterName, printerHandle, &pdef) == 0){
			ShowErrorMessageBox(IDT_ERT_PSET2, GetLastError(), hdlg);
			//return -1;
		}

		printerInfo[i].pDevMode->dmOrientation = dlgDate->dmOrientation;//用紙の向き
		printerInfo[i].pDevMode->dmPaperSize = dlgDate->dmPaperSize;//用紙のサイズ
		wcscpy_s(printerInfo[i].pDevMode->dmFormName,sizeof(dlgDate->dmFormName) , dlgDate->dmFormName);//用紙の名前
		printerInfo[i].pDevMode->dmPaperLength = dlgDate->dmPaperLength;//用紙の高さ
		printerInfo[i].pDevMode->dmPaperWidth = dlgDate->dmPaperWidth;//用紙の幅
		printerInfo[i].pDevMode->dmDefaultSource = dlgDate->dmDefaultSource;//給紙方法
		printerInfo[i].pDevMode->dmPrintQuality = dlgDate->dmPrintQuality;//品質
		printerInfo[i].pDevMode->dmColor = dlgDate->dmColor;//色
		printerInfo[i].pDevMode->dmDuplex = dlgDate->dmDuplex;//両面印刷
		//printerInfo[i].pSecurityDescriptor = 

		if(DocumentProperties(GetParent(hdlg), *printerHandle, printerInfo[i].pDriverName, printerInfo[i].pDevMode, printerInfo[i].pDevMode, DM_IN_BUFFER | DM_OUT_BUFFER) < 0){
			ShowErrorMessageBox(IDT_ERT_PSET3, GetLastError(), hdlg);
		}

		if(SetPrinter(*printerHandle, 2, (LPBYTE)&printerInfo[i], 0) == 0){
			ShowErrorMessageBox(IDT_ERT_PSET4, GetLastError(), hdlg);
			//return -1;
		}

		if(ClosePrinter(*printerHandle) == 0){
			ShowErrorMessageBox(IDT_ERT_PSET5, GetLastError(), hdlg);
			//return -1;
		}

		delete printerHandle;
	}

	LoadStr(TextBuf, sizeof(TextBuf), IDT_SPSET);
	wsprintf(StasBuf, TextBuf);
	SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);

	GlobalUnlock(psd.hDevMode);
	free(printerInfo);
	return 0;
}*/
int MenuMes(DWORD Hwp,DWORD Lwp,DWORD lp,HWND hwnd){
	UINT Hflag = UINT(Hwp);
	HMENU hMainMenu = GetMenu(hwnd);
	HMENU hSubMenuEN = GetSubMenu(hMainMenu, 0);
	HMENU hSubMenuDT = GetSubMenu(hMainMenu, 1);
	HMENU hmenu = (HMENU)lp;
	if((Hwp & MF_POPUP)==MF_POPUP){

		switch(Lwp){
			case 0:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_TMFILE , StasBuf , 1024
				);
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case 1:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_TMEDIT , StasBuf , 1024
				);
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case 2:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_TMFORM , StasBuf , 1024
				);
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case 3:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_TMVIEW , StasBuf , 1024
				);
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case 4:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_TMHELP , StasBuf , 1024
				);
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			default:
				if(hmenu==hSubMenuDT){
					LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
						IDM_PMDT , StasBuf , 1024
					);
					SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);		
				}
				else if(hmenu==hSubMenuEN){
					LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
						IDM_PMEN , StasBuf , 1024
					);
					SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);		
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
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_OPEN:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_OPEN , StasBuf , 1024
				);
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_SV:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_SV , StasBuf , 1024
				);
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_SVA:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_SVA , StasBuf , 1024
				);
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_PAGS:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_PAGS , StasBuf , 1024
				);
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_PRT:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_PRT , StasBuf , 1024
				);
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_EXIT:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_EXIT , StasBuf , 1024
				);
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_UND:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_UND , StasBuf , 1024
				);
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_CUT:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_CUT , StasBuf , 1024
				);
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_COPY:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_COPY , StasBuf , 1024
				);
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_PAST:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_PAST , StasBuf , 1024
				);
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_DEL:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_DEL , StasBuf , 1024
				);
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_FND:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_FND , StasBuf , 1024
				);
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_NFND:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_NFND , StasBuf , 1024
				);
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_REP:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_REP , StasBuf , 1024
				);
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_CL:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_CL , StasBuf , 1024
				);
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_OMZ:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_OMZ , StasBuf , 1024
				);
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_SETA:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_SETA , StasBuf , 1024
				);
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
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
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_FONT:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_FONT , StasBuf , 1024
				);
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_STE:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_STE , StasBuf , 1024
				);
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_HELP:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_HELP , StasBuf , 1024
				);
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;

			case IDM_VER:
				LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
					IDM_VER , StasBuf , 1024
				);
				SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
				break;
		}
	}
	return 0;
}

TCHAR* GetFileName(TCHAR* FilePath){//ファイル名を取得
	TCHAR* FileName;
	int i = 0, re = 0;
	while(FilePath[i] != TEXT('\0')){
		if(FilePath[i] == TEXT('\\') || FilePath[i] == TEXT('/') || FilePath[i] == TEXT(':')){
			re = i + 1;
		}
		i++;
	}
	FileName = &FilePath[re];
	return FileName;
}

UINT CALLBACK PageSetHook(HWND hdlg , UINT uiMsg , WPARAM wp , LPARAM lp) {
	TCHAR TEST[1024];//ヘッダーのEditBoxのテキスト取得　テスト用
	TCHAR strItem[3][1024];
	static enum Duplex {simplex_dm = 0, horizontal_dm, vertical_dm} prt_duplex = simplex_dm;
	switch(uiMsg) {
		case WM_INITDIALOG:
			psd.hDevMode = h_devMode;
			LoadStr(TextBuf, sizeof(TextBuf), IDT_SPSET);
			wsprintf(StasBuf,TextBuf);
			SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);

			SetWindowText(hdlg , TEXT("Kitty on your lap"));
			SetWindowText(GetDlgItem(hdlg, IDC_EDITH), TEXT("ヘッダー"));
			SetWindowText(GetDlgItem(hdlg, IDC_EDITF), TEXT("フッター"));

			LoadStr(strItem[0], sizeof(strItem[0]), IDT_CMB_DUP1);
			LoadStr(strItem[1], sizeof(strItem[1]), IDT_CMB_DUP2);//ex上綴じ
			LoadStr(strItem[2], sizeof(strItem[2]), IDT_CMB_DUP3);//ex左綴じ

			for(int i = 0; i < 3; i++){
				SendMessage(GetDlgItem(hdlg, IDC_COMBO1), CB_INSERTSTRING , i, (LPARAM)strItem[i]);
			}

			SendMessage(GetDlgItem(hdlg, IDC_COMBO1), CB_SETCURSEL, prt_duplex, 0);

			return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wp)) {
				case IDOK:
					h_devMode =  psd.hDevMode;
					DEVMODE *devMode = (DEVMODE *)GlobalLock(h_devMode);
					switch(SendMessage(GetDlgItem(hdlg, IDC_COMBO1) , CB_GETCURSEL , 0 , 0)){
					case 0:
						prt_duplex = simplex_dm;
						devMode->dmDuplex = DMDUP_SIMPLEX;
						break;
					case 1:
						prt_duplex = horizontal_dm;
						devMode->dmDuplex = DMDUP_HORIZONTAL;
						break;
					case 2:
						prt_duplex = vertical_dm;
						devMode->dmDuplex = DMDUP_VERTICAL;
						break;
					}
					GlobalUnlock(h_devMode);
					//SerPrint(hdlg);
					GetWindowText(GetDlgItem(hdlg, IDC_EDITH), TEST, 1024);
					break;
			}
	}
	return FALSE;
}

LRESULT CALLBACK EditProc(HWND edt , UINT msg , WPARAM wp , LPARAM lp){
	static bool mbdown = false;
	switch(msg){
		case WM_IME_NOTIFY:
			SetIMEState(edt);
			break;
		case WM_MOUSEMOVE:
			SendMessage(State,SB_SETTEXT,0|0,(LPARAM)DefStastext);
			if(mbdown)SetLLenState(edt);
			break;
		case WM_LBUTTONDOWN://挙動がいまいち
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_LBUTTONUP:
		case WM_PASTE:
		case WM_CUT:
		case WM_CHAR:
			CallWindowProc(SubEditClass,edt,msg,wp,lp);
			DefWindowProc(edt , msg , wp , lp);
			SetLLenState(edt);
			if(msg == WM_KEYDOWN || msg == WM_LBUTTONDOWN)mbdown = true;
			else if(msg == WM_KEYUP || msg == WM_LBUTTONUP)mbdown = false;
			return 0;
	}
	return CallWindowProc(SubEditClass,edt,msg,wp,lp);
}

LRESULT CALLBACK WndProc(HWND hwnd , UINT msg , WPARAM wp , LPARAM lp) {
	static UINT FNDm;
	static int S,E;
	static bool ud;//検索を上へか下へか
	static bool Found;//検索なのか置換なのか
	TCHAR msgBuf[insz] = TEXT("");
	int FBLen;//FINDTEXT関数内のinBufの長さ取得
	static int Stassz[4]={0,0,0,-1};
	HDROP hDrop;

	
	if(msg == FNDm && !(frp.Flags & FR_DIALOGTERM)){
		if(msg == FNDm && (frp.Flags & FR_DOWN))ud = true;
		else ud=false;

		if(msg == FNDm && (frp.Flags & FR_REPLACE)){//置き換え
			switch(REPLACETEXT(edt,false)){
				case 1:
					FTF1 = true;
					tSE = true;
					SetLLenState(edt);
					break;
				case 2:
					FTF1 = false;
					LoadStr(TextBuf, sizeof(TextBuf), IDT_MNOTFOUND);
					wsprintf(msgBuf,TextBuf,inBuf);
					LoadStr(TextBuf, sizeof(TextBuf), IDT_MTREP);
					MessageBox(hwnd,msgBuf,TextBuf,MB_ICONINFORMATION|MB_TOPMOST|MB_SYSTEMMODAL);
					tSE = false;
					break;
				case 3:
					TCHAR TextBuf1[1024], TextBuf2[1024];
					FTF1 = false;
					LoadStr(TextBuf1, sizeof(TextBuf), IDT_MREPALL);
					LoadStr(TextBuf2, sizeof(TextBuf), IDT_MTREPALL);
					MessageBox(hwnd,TextBuf1,TextBuf2,MB_ICONINFORMATION|MB_TOPMOST|MB_SYSTEMMODAL);
					tSE = false;
					SetLLenState(edt);
					break;
			}
		}
		else if(msg == FNDm && (frp.Flags & FR_REPLACEALL)){//すべて置き換え
			switch(REPLACETEXT(edt,true,bufEdt1,bufEdt2)){
				case 2:
					FTF1 = false;
					LoadStr(TextBuf, sizeof(TextBuf), IDT_MNOTFOUND);
					wsprintf(msgBuf,TextBuf,inBuf);
					LoadStr(TextBuf, sizeof(TextBuf), IDT_MTREP);
					MessageBox(hwnd,msgBuf,TextBuf,MB_ICONINFORMATION|MB_TOPMOST|MB_SYSTEMMODAL);
					tSE = false;
					break;
				case 3:
					TCHAR TextBuf1[1024], TextBuf2[1024];
					FTF1 = false;
					LoadStr(TextBuf1, sizeof(TextBuf), IDT_MREPALL);
					LoadStr(TextBuf2, sizeof(TextBuf), IDT_MTREPALL);
					MessageBox(hwnd,TextBuf1,TextBuf2,MB_ICONINFORMATION|MB_TOPMOST|MB_SYSTEMMODAL);
					tSE = false;
					SetLLenState(edt);
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
					SetLLenState(edt);
					break;
				case 2:			
					FTF1 = false;
					LoadStr(TextBuf, sizeof(TextBuf), IDT_MNOTFOUND);
					wsprintf(msgBuf,TextBuf,inBuf);
					LoadStr(TextBuf, sizeof(TextBuf), IDT_MTFIN);
					MessageBox(hwnd,msgBuf,TextBuf,MB_ICONINFORMATION|MB_TOPMOST|MB_SYSTEMMODAL);
					tSE = false;
					break;
				case 3:
					TCHAR TextBuf1[1024], TextBuf2[1024];
					FTF1 = false;
					tS = S;								//*-------------------------------//
					tE = tS + FBLen;					//前回検索に引っかかった文字を選択//
					SendMessage(edt,EM_SETSEL,tS,tE);	//-------------------------------*//
					SendMessage(edt,EM_SCROLLCARET,NULL,NULL);
					LoadStr(TextBuf1, sizeof(TextBuf), IDT_MFINALL);
					LoadStr(TextBuf2, sizeof(TextBuf), IDT_MTFINALL);
					MessageBox(hwnd,TextBuf1,TextBuf2,MB_ICONINFORMATION|MB_TOPMOST|MB_SYSTEMMODAL);
					tSE = false;
					SetLLenState(edt);
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
			LoadStr(TextBuf, sizeof(TextBuf), IDT_EXEND);
			EndD = TextBuf;
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

			prbufedt= CreateWindow(
						TEXT("EDIT") , NULL , 
						WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_NOHIDESEL | ES_AUTOVSCROLL |WS_BORDER | ES_LEFT | ES_MULTILINE ,
						0 , 0 , 0 , 0 , hwnd , (HMENU)1 ,
						((LPCREATESTRUCT)(lp))->hInstance , NULL
				);
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
						((LPCREATESTRUCT)(lp))->hInstance , NULL
				);
			State = CreateStatusWindow(WS_CHILD | CCS_BOTTOM | WS_VISIBLE |  SBARS_SIZEGRIP ,
						NULL,hwnd,NULL
				);

			SendMessage(State , SB_SETPARTS , 4 , (LPARAM)Stassz);//StatusBar

			SendMessage(State,SB_SETTEXT,0|0,(LPARAM)DefStastext);
						
			CheckMenuRadioItem(GetMenu(hwnd), IDM_EAN, IDM_EUN, IDM_EAN, MF_BYCOMMAND);
			cEncode = ANSI_en;//エンコードを指定
			SetEncodeState();//エンコードの設定の状態をステータスバーへ

			SendMessage(bufEdt1, EM_LIMITTEXT , TEXTsz, 0);
			SendMessage(bufEdt2, EM_LIMITTEXT , TEXTsz, 0);
			SendMessage(edtnr, EM_LIMITTEXT , TEXTsz, 0);
			SendMessage(edtr, EM_LIMITTEXT , TEXTsz, 0);
			edt = edtnr;

			SubEditClass = (WNDPROC)SetWindowLong(edt,GWL_WNDPROC,(LONG)EditProc);//サブクラス化
			
			lf.lfCharSet = 1;//デフォルト 文字セットＪＰ
			lf.lfHeight = -19;//デフォルト 大きさ　14pt
			wcscpy_s(lf.lfFaceName,TEXT("メイリオ"));//デフォルトFont
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
			
			psd.lStructSize = sizeof (PAGESETUPDLG);
			psd.hwndOwner = hwnd;
			psd.rtMargin=rcMargin;
			psd.Flags=PSD_MARGINS | PSD_INHUNDREDTHSOFMILLIMETERS | PSD_ENABLEPAGESETUPHOOK | PSD_ENABLEPAGESETUPTEMPLATE;
			psd.lpfnPageSetupHook = PageSetHook;
			psd.hInstance = ((LPCREATESTRUCT)(lp))->hInstance;
			psd.lpPageSetupTemplateName = TEXT("MyPageSetupDLG");

			h_devMode = psd.hDevMode;//初期化　クラス化時にはNULLなら
			
			ShowWindow(edt,SW_SHOW);
			FNDm = RegisterWindowMessage(FINDMSGSTRING);
			SetFocus(hwnd);	
			SetFocus(edt);//フォーカスをEDITに

			SetLLenState(edt);
			
			DragAcceptFiles(hwnd, true);//D&D許可
			return 0;

		case WM_SIZE://ウインドウのサイズ変更時のイベント
			
			MoveWindow(edt,NULL,0,LOWORD(lp),HIWORD(lp)-24,1);//edtサイズ変更
			MoveWindow(State,NULL,0,LOWORD(lp),NULL,1);

			if(LOWORD(lp) * 0.8 <= LOWORD(lp) - 200) Stassz[0] = (int)(LOWORD(lp) * 0.8);
			else if(LOWORD(lp) <= 300) Stassz[0] = LOWORD(lp);//300以下これだけ
			else if(LOWORD(lp) - 270 <= 270) Stassz[0] = (int)(LOWORD(lp) * 0.5);
			else Stassz[0] = (int)(LOWORD(lp) - 270);

			if(LOWORD(lp) * (1- 0.6) <= 50) Stassz[1] = (int)(LOWORD(lp) - 50);
			else if(LOWORD(lp) <= 300) Stassz[1] =-1;//Close（複数個所が同じになりその間の領域が非表示となる）
			else if(LOWORD(lp) <= 400) Stassz[1] = (int)(LOWORD(lp) * 0.7875);//Close
			else if(LOWORD(lp) <= 480) Stassz[1] =(int)(LOWORD(lp) - 95);//Close
			else Stassz[1] = (int)(LOWORD(lp) - 150);

			if(LOWORD(lp) <= 300) Stassz[2] =-1;//Close
			else if(LOWORD(lp) <= 400) Stassz[2] = (int)(LOWORD(lp) * 0.7875);
			else Stassz[2] = (LOWORD(lp) - 95);

			Stassz[3] = -1;

			SendMessage(State , SB_SETPARTS , 4 , (LPARAM)Stassz);
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

				case IDM_PAGS:
					LoadStr(TextBuf, sizeof(TextBuf), IDT_SPSET);
					wsprintf(StasBuf,TextBuf);
					SendMessage(State,SB_SETTEXT,0|0,(LPARAM)StasBuf);
					if(PageSetupDlg(&psd)==0)break;
					break;

				case IDM_PRT:
					Print(hwnd,edt,prbufedt,bufEdt1,bufEdt2);
					break;

				case IDM_EXIT:
					SendMessage(hwnd,WM_CLOSE,0,0);
					return 0;

				case IDM_EAN:
					CheckMenuRadioItem(GetMenu(hwnd), IDM_EAN, IDM_EUN, IDM_EAN, MF_BYCOMMAND);
					cEncode = ANSI_en;
					SetEncodeState();
					return 0;

				case IDM_EUN:
					CheckMenuRadioItem(GetMenu(hwnd), IDM_EAN, IDM_EUN, IDM_EUN, MF_BYCOMMAND);
					cEncode = UNICODE_en;
					SetEncodeState();
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
								LoadStr(TextBuf, sizeof(TextBuf), IDT_MNOTFOUND);
								wsprintf(msgBuf,TextBuf,inBuf);
								LoadStr(TextBuf, sizeof(TextBuf), IDT_MTFIN);
								MessageBox(hwnd,msgBuf,TextBuf,MB_ICONINFORMATION|MB_TOPMOST|MB_SYSTEMMODAL);
								tSE = false;
								break;
							case 3:
								TCHAR TextBuf1[1024], TextBuf2[1024];
								FTF1 = false;
								LoadStr(TextBuf1, sizeof(TextBuf), IDT_MFINALL);
								LoadStr(TextBuf2, sizeof(TextBuf), IDT_MTFINALL);
								MessageBox(hwnd,TextBuf1,TextBuf2,MB_ICONINFORMATION|MB_TOPMOST|MB_SYSTEMMODAL);
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

				case IDM_CL:
					

					break;

				case IDM_OMZ:
					int id;
					LoadStr(TextBuf, sizeof(TextBuf), IDT_EXOMG);
					EndD = TextBuf;
					id = SaveEx(edt);
					if(id == IDCANCEL)return 0;
					LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
						IDT_OMGTX , StasBuf , sizeof(StasBuf)
					);
					SetWindowText(edt,StasBuf);
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
					hMem = GlobalAlloc(GHND,sizeof(TCHAR)*nLen + 1);
					lpszBuf = (TCHAR *)GlobalLock(hMem);
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
					LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
						IDT_HELPTX , StasBuf , sizeof(StasBuf)
					);
					MessageBox(hwnd,StasBuf,szWindowTitle,MB_ICONINFORMATION);
					break;
				
				case IDM_VER:
					LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
						IDT_VERSIONTX , StasBuf , sizeof(StasBuf)
					);
					ShellAbout(hwnd, szWindowTitle, StasBuf, NULL);
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
		SendMessage(State,SB_SETTEXT,0|0,(LPARAM)DefStastext);
		return 0;
	
	case WM_MENUSELECT:
		MenuMes(HIWORD(wp),LOWORD(wp),lp,hwnd);
		return 0;

	case WM_DROPFILES://D&D
		hDrop = (HDROP)wp;
		DragQueryFile(hDrop, 0, szFile, sizeof(szFile));
		wsprintf(szFileTitle, TEXT("%s"), GetFileName(szFile));
		MyOpenF(edt, false);
		return 0;
	case WM_IME_NOTIFY:
		SetIMEState(edt);
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