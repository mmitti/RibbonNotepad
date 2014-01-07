//RichEdit�ɂ���//RICHEDIT_CLASS//RichEdit
//����//http://eternalwindows.jp/control/controlbase/controlbase09.html
//EditMessage//http://hp.vector.co.jp/authors/VA024411/vbtips03.html#05
//CheckMenuRadioItem(GetMenu(hwnd), ���j���[�A�C�e���n�܂��ID,���j���[�A�C�e��������ID, ���j���[�A�C�e���A�C�R�����Z�b�g����ID, MF_BYCOMMAND ); ***���W�I�{�^���̃`�F�b�N
//MessageBox�̉��s*/\r\n/*

//EM_LINEFROMCHAR���݂̍s�ԍ����擾
//http://support.microsoft.com/kb/186271/ja
//SendMessage(edt,EM_SETSEL,0,(SendMessage(edt,EM_LINEINDEX,3,0)));

//PrintDialog//http://homepage2.nifty.com/c_lang/sdk3/sdk_298.htm



#include<windows.h>
#include"resource.h"
#include <commctrl.h>
#pragma comment(lib,"Comctl32.lib")//Lib�̃����N



HFONT hFont1;
HWND edt;
HWND edtnr;
HWND edtr;
HWND bufEdt1,bufEdt2;
HWND Stas;
HWND prbufedt;
WNDPROC SubEditClass;
LOGFONT lf={0};//�K�{
CHOOSEFONT cf;//�K�{
LPCHOOSEFONT pcf;
PAGESETUPDLG psd;//PrintDialog�p

char szFile[256];
char szFileTitle[256]="";
const char szWindowTitle[128] = "�����̃e�L�X�g�G�f�B�^�[";//�E�C���h�E�̃^�C�g��
char szTitle[128];
char* szTitle2 = "�����̃e�L�X�g�G�f�B�^�[ - %s";
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

const int insz = 256;//�����_�C�A���O���͂�������
TCHAR inBuf[insz] = "";
TCHAR repBuf[insz] = "";
bool tSE = false;//�P��ڂ��ǂ���������
bool flFND = false;//�������������Ƃ����邩
	
TCHAR DefStastext[128]="Ready";
TCHAR StasBuf[1024];//�X�e�[�^�X�o�[�̃e�L�X�g�pBuf

RECT rcMargin={2000,2500,2000,2500};//�]���̏����l2000=20mm

int setup(){

	memset(&ofn,0,sizeof(OPENFILENAME));//ofn��0����

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = edt;
	ofn.lpstrFilter = "�e�L�X�g�t�@�C��(*.txt)\0*.txt\0c++�t�@�C��(*.cpp)\0*.cpp\0c�t�@�C��(*.c)\0*.c\0All files(*.*)\0*.*\0\0";
	ofn.lpstrFile = szFile;
	ofn.lpstrFileTitle = szFileTitle;
	ofn.nFilterIndex = 1;
	ofn.nMaxFile = MAX_PATH;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.Flags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY ;
	ofn.lpstrDefExt = "txt";
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
		SetWindowText(bufEdt2,"");
	}
	else if (!ck){
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
	wsprintf(szTitle,"%s - ���O��t���ĕۑ�",szWindowTitle);
	ofn.lpstrTitle = "���O��t���ĕۑ�";

	if(GetSaveFileName(&ofn) == 0)return -1;
	wsprintf(szTitle,"�ۑ���");
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

	wsprintf(szTitle,"�㏑���ۑ���");
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
				id =MessageBox(edt , TEXT("�ύX����Ă���悤������\n�ۑ����邩���H") ,
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
	
	EndD="�₢���킹 - �t�@�C�����J��";
	id = SaveEx(edt);
	if(id == IDCANCEL)return 0;

	//dwSize =OL;
	setup();
	wsprintf(szTitle,"%s - �t�@�C�����J��",szWindowTitle);
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
	
	EndD="�₢���킹 - �V�K�쐬";
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
			if(MenuMes) wsprintf(szBuf,"�`��1:%d:%d:%d",st.wHour,st.wMinute,st.wSecond);
			else wsprintf(szBuf,"%d:%d:%d",st.wHour,st.wMinute,st.wSecond);
			break;
		case ID_OP2:
			if(MenuMes) wsprintf(szBuf,"�`��2:%d��%d��%d�b",st.wHour,st.wMinute,st.wSecond);
			else wsprintf(szBuf,"%d��%d��%d�b",st.wHour,st.wMinute,st.wSecond);
			break;
		case ID_OP3:
			if(st.wHour/12 >= 1)str="PM";
			else str="AM";
			if(MenuMes) wsprintf(szBuf,"�`��3:%d:%d(%s)",st.wHour%12,st.wMinute,str);
			else wsprintf(szBuf,"%d:%d(%s)",st.wHour%12,st.wMinute,str);
			break;
		case ID_OP4:
			if(MenuMes) wsprintf(szBuf,"�`��4:%d/%d/%d",st.wYear,st.wMonth,st.wDay);
			else wsprintf(szBuf,"%d/%d/%d",st.wYear,st.wMonth,st.wDay);
			break;
		case ID_OP5:
			if(MenuMes) wsprintf(szBuf,"�`��5:%d�N%d��%d��",st.wYear,st.wMonth,st.wDay);
			else wsprintf(szBuf,"%d�N%d��%d��",st.wYear,st.wMonth,st.wDay);
			break;
		case ID_OP6:
			if(MenuMes) wsprintf(szBuf,"�`��6:%d/%d/%d %d:%d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute);
			else wsprintf(szBuf,"%d/%d/%d %d:%d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute);
			break;
		case ID_OP7:
			switch(st.wDayOfWeek){
				case 0:
					str="�i���j";
					break;
				case 1:
					str="�i���j";
					break;
				case 2:
					str="�i�΁j";
					break;
				case 3:
					str="�i���j";
					break;
				case 4:
					str="�i�؁j";
					break;
				case 5:
					str="�i���j";
					break;
				case 6:
					str="�i�y�j";
					break;
			}
			if(MenuMes) wsprintf(szBuf,"�`��7:%s",str);
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
			if(MenuMes)wsprintf(szBuf,"�`��8�F%s",str);
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
//���^�[���l	1:������܂���	2:�S��������܂���ł���	3:���ׂČ������܂���
	static bool sw;
	
	int i = 0;
	static int m = 0;
	bool Flag =true;
	static int end,rm;
	static TCHAR bkBuf[insz];
	static int fs=0;//������Ȃ������Ƃ����ڂ��ǂ���
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
			m=lstrlen(inBuf)-1;//inBuf�̕����̒���
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
//���^�[���l	1:�u�����܂���	2:�S��������܂���ł���	3:���ׂĒu�����܂���
	int i = 1;
	int ct =0;
	bool ud = true;
	if(all){//ESC��while������I
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
int Print(HWND hwnd,HWND edt,HWND bufedt,HWND bufEdt1,HWND bufEdt2){
	wsprintf(StasBuf,"���������");
	SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
	PRINTDLG prt;
	DOCINFO di;
	int fonts = 0;
	int dpi,allLine,loop;
	TEXTMETRIC tm;
	RECT bufEdit={0,0,0,0};


	RECT txrc = {0,0,0,0};
	
	LPTSTR lpszBuf;
	LPWSTR Buf;

	int Len=0;
	nLen = GetWindowTextLength(edt);
	hMem = GlobalAlloc(GHND,sizeof(char)*nLen + 1);
	lpszBuf = (char *)GlobalLock(hMem);
	GetWindowText(edt,lpszBuf,nLen + 1);

	if(nLen == 0){
		int mb = MessageBox(hwnd,"�󔒂����ǈ������H","�m�F - ���",MB_YESNO|MB_ICONQUESTION);
		if(mb == IDNO)return 0;
		wsprintf(szTitle,szWindowTitle);
	}
	else{
		wsprintf(szTitle,szTitle2,szFileTitle);
	}
	Len = MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,lpszBuf,nLen,NULL,0);
	Buf = new WCHAR[Len+8];
	MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,lpszBuf,nLen,Buf,Len);

	memset(&prt,9,sizeof(PRINTDLG));
	SetWindowText(bufedt,lpszBuf);
	delete[] Buf;
	clipck1(bufEdt2,false);

	prt.lStructSize = sizeof(PRINTDLG);
	prt.hwndOwner = hwnd;//DialogBox�̃I�[�i�[
	prt.hDevMode = NULL;
	prt.hDevNames = NULL;
	prt.Flags = PD_USEDEVMODECOPIESANDCOLLATE|PD_RETURNDC|PD_NOPAGENUMS|PD_NOSELECTION|PD_HIDEPRINTTOFILE|PD_NOPAGENUMS;
/*	prt.nMinPage = 1;//�y�[�W�͈͂̍ŏ�
	prt.nMaxPage = 1;//"			"�ő�
	prt.nFromPage = 1;//�J�n�y�[�W
	prt.nToPage = 1;//�I���y�[�W*/
	prt.nCopies = 1;//�����̏����l


	if(PrintDlg(&prt) == 0)return -1;//�_�C�A���O

	wsprintf(StasBuf,"���������(�M�E�ցE�L)");
	SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
	SendMessage(bufedt, WM_SETFONT, (WPARAM)hFont1, MAKELPARAM(FALSE, 0));

	dpi = GetDeviceCaps(prt.hDC,LOGPIXELSX);//�v�����^�[��dpi�擾
	txrc.right = GetDeviceCaps(prt.hDC,HORZRES);//���擾
	txrc.bottom = GetDeviceCaps(prt.hDC,VERTRES);//�����擾
	fonts = lf.lfHeight;
	lf.lfHeight = (fonts/(96/72))*(dpi/96);//dpi���Z
	hFont1 = CreateFontIndirect(&lf);

	SelectObject(prt.hDC,hFont1);//FontSet

	GetTextMetrics(prt.hDC,&tm);
	txrc.bottom-=(int)((psd.rtMargin.bottom/100)*dpi/25.4);
	txrc.left=(int)((psd.rtMargin.left/100)*dpi/25.4);
	txrc.right-=(int)((psd.rtMargin.right/100)*dpi/25.4);
	txrc.top=(int)((psd.rtMargin.top/100)*dpi/25.4);

	int t=(txrc.bottom-txrc.top)/(tm.tmHeight);//1�y�[�W�̍ő�s��
	bufEdit.bottom=(int)(((txrc.bottom-txrc.top)*25.4/dpi)*96/25.4);
	bufEdit.right=(int)(((txrc.right-txrc.left)*25.4/dpi)*96/25.4);

		MoveWindow(bufedt,0-bufEdit.right,0-bufEdit.bottom,bufEdit.right,bufEdit.bottom,1);

	allLine=SendMessage(bufedt,EM_GETLINECOUNT,0,0);

	loop=(int)(allLine/t)+1;//10/5=2+1�ƂȂ�̂ł����̔���

	


	memset(&di,0,sizeof(DOCINFO));

	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = szTitle;//�h�L�������g��
	
	StartDoc(prt.hDC,&di);//����J�n
	wsprintf(StasBuf,"��� - �o�͒�");
	SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
	for(int k=1;k<=loop;k++){
		SetWindowText(bufEdt1,"");
		wsprintf(StasBuf,"��� - �o�͒��@%d�y�[�W��%d�y�[�W��",loop,k);
		SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
		if(k==loop)SendMessage(bufedt,EM_SETSEL,0,-1);
		else SendMessage(bufedt,EM_SETSEL,0,(SendMessage(bufedt,EM_LINEINDEX,t,0)));
		SendMessage(bufedt,WM_CUT,0,0);
		SendMessage(bufEdt1,WM_PASTE,0,0);

		lpszBuf="";
		nLen = GetWindowTextLength(bufEdt1);
		hMem = GlobalAlloc(GHND,sizeof(char)*nLen + 1);
		lpszBuf = (char *)GlobalLock(hMem);
		GetWindowText(bufEdt1,lpszBuf,nLen + 1);
		Len = MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,lpszBuf,nLen,NULL,0);
		Buf = new WCHAR[Len+8];
		MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,lpszBuf,nLen,Buf,Len);

		StartPage(prt.hDC);//�y�[�W�J�n(�����y�[�W�̏ꍇ���[�v�J�n)
		DrawTextW(prt.hDC,Buf,Len,&txrc,DT_WORDBREAK|DT_EDITCONTROL|DT_LEFT);//10,10+~�̂Ƃ���ŗ]�����������
		EndPage(prt.hDC);//�y�[�W�I���(�����y�[�W�̏ꍇ���[�v�I���)
		delete[] Buf;

	}

	EndDoc(prt.hDC);//����I���
	wsprintf(StasBuf,"��� - �o�͊����_(^o^)�^");
	SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)StasBuf);
	DeleteDC(prt.hDC);
	lf.lfHeight = fonts;
	clipck2(bufEdt2,false);
	ShowWindow(edt,SW_SHOW);
	SetFocus(edt);
	return 0;
}
int MenuMes(DWORD Hwp,DWORD Lwp,DWORD lp,HWND hwnd){
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
int SetStasLLen(HWND edt){
	int S=0,E=0,Line=0,LLen=0;
	Line=SendMessage(edt,EM_LINEFROMCHAR,-1,0);//�s���擾
	LLen=SendMessage(edt,EM_LINEINDEX,-1,0);//������
	SendMessage(edt,EM_GETSEL,(WPARAM)&S,(LPARAM)&E);
	if(S==E)wsprintf(StasBuf,"    �s:%d    ��:%d",Line+1,E-LLen);
	else wsprintf(StasBuf,"������:%d",E-S);
	SendMessage(Stas,SB_SETTEXT,1|0,(LPARAM)StasBuf);
	return 0;
}

LRESULT CALLBACK EditProc(HWND edt , UINT msg , WPARAM wp , LPARAM lp){
	switch(msg){
		case WM_MOUSEMOVE:
			SendMessage(Stas,SB_SETTEXT,0|0,(LPARAM)DefStastext);
			SetStasLLen(edt);
			break;
		case WM_LBUTTONDOWN://���������܂���
		case WM_LBUTTONUP:
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_PASTE:
		case WM_CUT:
		case WM_CHAR:
			CallWindowProc(SubEditClass,edt,msg,wp,lp);
			DefWindowProc(edt , msg , wp , lp);
			SetStasLLen(edt);
			return 0;
	}
	return CallWindowProc(SubEditClass,edt,msg,wp,lp);
}

LRESULT CALLBACK WndProc(HWND hwnd , UINT msg , WPARAM wp , LPARAM lp) {
	static UINT FNDm;
	static int S,E;
	static bool ud;//��������ւ����ւ�
	static bool Found;//�����Ȃ̂��u���Ȃ̂�
	TCHAR msgBuf[insz] = "";
	int FBLen;//FINDTEXT�֐�����inBuf�̒����擾
	static int Stassz[2]={50,-1};

	
	if(msg == FNDm && !(frp.Flags & FR_DIALOGTERM)){
		if(msg == FNDm && (frp.Flags & FR_DOWN))ud = true;
		else ud=false;

		if(msg == FNDm && (frp.Flags & FR_REPLACE)){//�u������
			switch(REPLACETEXT(edt,false)){
				case 1:
					FTF1 = true;
					tSE = true;
					SetStasLLen(edt);
					break;
				case 2:
					FTF1 = false;
					wsprintf(msgBuf,"\"%s\"��������܂���",inBuf);
					MessageBox(hwnd,msgBuf,"�u��",MB_ICONINFORMATION|MB_TOPMOST|MB_SYSTEMMODAL);
					tSE = false;
					break;
				case 3:
					FTF1 = false;
					MessageBox(hwnd,"���ׂĂ̒u�����I���܂���","�u�� - �����I",MB_ICONINFORMATION|MB_TOPMOST|MB_SYSTEMMODAL);
					tSE = false;
					SetStasLLen(edt);
					break;
			}
		}
		else if(msg == FNDm && (frp.Flags & FR_REPLACEALL)){//���ׂĒu������
			switch(REPLACETEXT(edt,true,bufEdt1,bufEdt2)){
				case 2:
					FTF1 = false;
					wsprintf(msgBuf,"\"%s\"��������܂���",inBuf);
					MessageBox(hwnd,msgBuf,"�u��",MB_ICONINFORMATION|MB_TOPMOST|MB_SYSTEMMODAL);
					tSE = false;
					break;
				case 3:
					FTF1 = false;
					MessageBox(hwnd,"���ׂĂ̒u�����I���܂���","�u�� - �����I",MB_ICONINFORMATION|MB_TOPMOST|MB_SYSTEMMODAL);
					tSE = false;
					SetStasLLen(edt);
					break;
			}
		}
		else{//����
			switch(FINDTEXT(edt,ud,&FBLen,true)){
			
				case 1:
					FTF1 = true;
					SetFocus(edt);
					SendMessage(edt,EM_SETSEL,tS,tE);
					SendMessage(edt,EM_SCROLLCARET,NULL,NULL);
					SendMessage(edt,EM_GETSEL,(WPARAM)&S,(LPARAM)&E);
					tSE = true;
					SetStasLLen(edt);
					break;
				case 2:			
					FTF1 = false;
					wsprintf(msgBuf,"\"%s\"��������܂���",inBuf);
					MessageBox(hwnd,msgBuf,"����",MB_ICONINFORMATION|MB_TOPMOST|MB_SYSTEMMODAL);
					tSE = false;
					break;
				case 3:
					FTF1 = false;
					tS = S;								//*-------------------------------//
					tE = tS + FBLen;					//�O�񌟍��Ɉ�����������������I��//
					SendMessage(edt,EM_SETSEL,tS,tE);	//-------------------------------*//
					SendMessage(edt,EM_SCROLLCARET,NULL,NULL);
					MessageBox(hwnd,"���ׂĂ̌������I���܂���","���� - �����I",MB_ICONINFORMATION|MB_TOPMOST|MB_SYSTEMMODAL);
					tSE = false;
					SetStasLLen(edt);
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
			EndD = "�₢���킹 - �I��";
			id = SaveEx(edt);
			if(id == IDCANCEL)return 0;
			
			DestroyWindow(hwnd);
			PostQuitMessage(0);
			return 0;
/*		case WM_KILLFOCUS:
			
				SendMessage(edt,EM_GETSEL,(WPARAM)&S,(LPARAM)&E);
			

			
			return 0;*///IE���̃t�H�[�J�X
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
			}*///IE���̃t�H�[�J�X
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
			edtnr = CreateWindow(//�܂�Ԃ��Ȃ�
						TEXT("EDIT") , NULL , 
						WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL |ES_AUTOHSCROLL | ES_AUTOVSCROLL | WS_BORDER | ES_NOHIDESEL | ES_LEFT | ES_MULTILINE ,
						0 , 0 , 0 , 0 , hwnd , (HMENU)1 ,
						((LPCREATESTRUCT)(lp))->hInstance , NULL
				);
			edtr = CreateWindow(//�܂�Ԃ�����
						TEXT("EDIT") , NULL , 
						WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_NOHIDESEL | ES_AUTOVSCROLL |WS_BORDER | ES_LEFT | ES_MULTILINE ,
						0 , 0 , 0 , 0 , hwnd , (HMENU)1 ,
						((LPCREATESTRUCT)(lp))->hInstance , NULL
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

			SubEditClass = (WNDPROC)SetWindowLong(edt,GWL_WNDPROC,(LONG)EditProc);//�T�u�N���X��
			
			lf.lfCharSet = 1;//�f�t�H���g �����Z�b�g�i�o
			lf.lfHeight = -19;//�f�t�H���g �傫���@14pt
			strcpy_s(lf.lfFaceName,"���C���I");//�f�t�H���gFont
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
			psd.Flags=PSD_MARGINS|PSD_INHUNDREDTHSOFMILLIMETERS;
			
			ShowWindow(edt,SW_SHOW);
			FNDm = RegisterWindowMessage(FINDMSGSTRING);
			SetFocus(hwnd);	
			SetFocus(edt);//�t�H�[�J�X��EDIT��

			SetStasLLen(edt);


			return 0;

		case WM_SIZE://�E�C���h�E�̃T�C�Y�ύX���̃C�x���g
			
			MoveWindow(edt,NULL,0,LOWORD(lp),HIWORD(lp)-24,1);//edt�T�C�Y�ύX
			MoveWindow(Stas,NULL,0,LOWORD(lp),NULL,1);
			Stassz[0]=(int)(LOWORD(lp)*0.75);
			Stassz[1]=-1;
			SendMessage(Stas , SB_SETPARTS , 2 , (LPARAM)Stassz);
			return 0;

		case WM_COMMAND:
			
			switch(LOWORD(wp)){
			
				//---File---///
				case IDM_NEW://�{�^�����b�Z�[�W
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
					if(PageSetupDlg(&psd)==0)break;
					break;

				case IDM_PRT:
					Print(hwnd,edt,prbufedt,bufEdt1,bufEdt2);
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
								wsprintf(msgBuf,"\"%s\"��������܂���",inBuf);
								MessageBox(hwnd,msgBuf,"����",MB_ICONINFORMATION|MB_TOPMOST|MB_SYSTEMMODAL);
								tSE = false;
								break;
							case 3:
								FTF1 = false;
								MessageBox(hwnd,"���ׂĂ̌������I���܂���","���� - �����I",MB_ICONINFORMATION|MB_TOPMOST|MB_SYSTEMMODAL);
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
					EndD = "�₢���킹 - ���܂��Ȃ�";
					id = SaveEx(edt);
					if(id == IDCANCEL)return 0;
					LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
						IDT_OMGTX , StasBuf , 1024
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
					LoadString((HINSTANCE)GetWindowLong(hwnd , GWL_HINSTANCE) ,
						IDT_HELPTX , StasBuf , 1024
					);
					MessageBox(hwnd,StasBuf,szWindowTitle,MB_ICONINFORMATION);
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
	case WM_NCMOUSEMOVE://�O���ł�MouseMove�������ł���
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

	hAcce = LoadAccelerators(hInstance,MAKEINTRESOURCE(IDR_ACCELERATOR));//�A�N�Z�����[�^�[�@���[�h

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
		if(!TranslateAccelerator(hwnd,hAcce,&msg)){//�A�N�Z�����[�^�[MSG
			TranslateMessage(&msg);DispatchMessage(&msg);
		}
	}
		
	return msg.wParam;

}