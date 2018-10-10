#include "stdafx.h"
#include "AnalysisOfPE.h"


AnalysisOfPE::AnalysisOfPE(void)
{
}


AnalysisOfPE::~AnalysisOfPE(void)
{
}
void AnalysisOfPE::ObtainPeInfo(TCHAR *FileName)
{

	if (AnalPE.buf != NULL) {
		delete buf;
		buf = NULL;
	}

	AnalPE.pDosH = NULL;
	AnalPE.pNtH = NULL;
	AnalPE.m_pFileHdr = NULL;
	AnalPE.pOptH = NULL;
	AnalPE.pSecH = NULL;
	AnalPE.pDatD = NULL;
	AnalPE.pOptH64 = NULL;
	AnalPE.pExpD = NULL;


	PeFileName = FileName;
	buf = nullptr;
	//得到文件句柄
	hFile = CreateFile(
		FileName, GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	//得到文件大小
	DWORD dwFileSize = GetFileSize(hFile, NULL);
	//long long dwFileSize = GetFileSize(hFile, NULL);
	DWORD ReadSize = 0;
	//long long ReadSize = 0;
	buf = new char[dwFileSize];
	//将文件读取到内存
	ReadFile(hFile, buf, dwFileSize, &
		ReadSize, NULL);
	pDosH = (PIMAGE_DOS_HEADER)buf;



	if (*(PWORD)buf != IMAGE_DOS_SIGNATURE)
	{
		MessageBox(NULL, L"不是有效的PE文件", L"错误", MB_OK);
		return;
	}
	pDosH = (IMAGE_DOS_HEADER*)buf;
	if (*(PDWORD)((byte*)buf + pDosH->e_lfanew) != IMAGE_NT_SIGNATURE)
	{
		MessageBox(NULL, L"不是有效的PE文件", L"错误", MB_OK);
		return;
	}
	m_pFileHdr = (IMAGE_FILE_HEADER*)((byte*)buf + pDosH->e_lfanew + sizeof(DWORD));

	//或者根据扩展头的Magic区分32位64位   0x010B   0x020B
	if (m_pFileHdr->Machine == IMAGE_FILE_MACHINE_I386)
	{
		pOptH = (IMAGE_OPTIONAL_HEADER32*)((byte*)buf + pDosH->e_lfanew + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER));
		pSecH = (IMAGE_SECTION_HEADER *)((byte*)pOptH + m_pFileHdr->SizeOfOptionalHeader);
		pDatD = &(pOptH->DataDirectory[0]);
		pNtH = (PIMAGE_NT_HEADERS32)(buf + pDosH->e_lfanew);

	}
	else if (m_pFileHdr->Machine == IMAGE_FILE_MACHINE_IA64 || m_pFileHdr->Machine == IMAGE_FILE_MACHINE_AMD64)
	{
		pOptH64 = (IMAGE_OPTIONAL_HEADER64*)((byte*)buf + pDosH->e_lfanew + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER));
		pSecH = (IMAGE_SECTION_HEADER *)((byte*)pOptH64 + m_pFileHdr->SizeOfOptionalHeader);
		pDatD = &(pOptH64->DataDirectory[0]);
		pNtH = (PIMAGE_NT_HEADERS)(buf + pDosH->e_lfanew);//默认还是32
	}



	if (IMAGE_DOS_SIGNATURE != pDosH->e_magic)
	{
		//MessageBox(L"不是DOS头",L"s")
		AfxMessageBox(L"不是DOS头");
		return;
	}
	//printf_s("DOS头:0x%X\n",pDosH->e_magic);
	//printf_s("EXE文件的偏移头:0x%X\n",pDosH->e_lfanew);
	//获取NT头


	//PIMAGE_NT_HEADERS32 pNtH=(PIMAGE_NT_HEADERS32)buf;  
	if (pNtH->Signature != IMAGE_NT_SIGNATURE)
	{
		AfxMessageBox(L"不是NT头");
		return;
	}


	m_pFileHdr = &pNtH->FileHeader;


	//获取区段头
	//pSecH = IMAGE_FIRST_SECTION(pNtH);
	//获取可选头数据
	//pOptH = &(pNtH->OptionalHeader);

	//获取数据目录
	//pDatD = &(pOptH->DataDirectory[0]);
	//获取导出表数据
	//pExpD=(PIMAGE_EXPORT_DIRECTORY)(buf+CalcOffset(pDatD->VirtualAddress));

	ClosePeHandle();
}

void AnalysisOfPE::ClosePeHandle()
{
	CloseHandle(hFile);
}

DWORD AnalysisOfPE::ChangeNumber(CString NeedValue)
{
	CStringA PeValue(NeedValue);
	char *p = PeValue.GetBuffer();	//转换为char* 类型
	return strtoul(p, 0, 16);		//转换为十进制数字

}



void AnalysisOfPE::OutPutPeInfo(CString &StrPeValue, DWORD WithPeValue)
{
	CString NewStrPeValue;
	NewStrPeValue.Format(L"%08X", WithPeValue);//转16进制
	StrPeValue = NewStrPeValue;

}

DWORD AnalysisOfPE::CalcOffset(DWORD Rva)
{
	//循环比较在那个区段  不在这个区段就继续循环  
	//PIMAGE_NT_HEADERS32 pnt=pNtH;
	PIMAGE_SECTION_HEADER pSecHTemp = IMAGE_FIRST_SECTION(pNtH);//区段头
	int index = 0;
	while (!(Rva >= pSecHTemp->VirtualAddress&&
		Rva < pSecHTemp->VirtualAddress + pSecHTemp->SizeOfRawData))
	{
		//找完所有区段还没有找到
		if (index > pNtH->FileHeader.NumberOfSections)
		{
			return Rva;
		}
		++index;
		++pSecHTemp;
	}
	return Rva - pSecHTemp->VirtualAddress + pSecHTemp->PointerToRawData;;
}
