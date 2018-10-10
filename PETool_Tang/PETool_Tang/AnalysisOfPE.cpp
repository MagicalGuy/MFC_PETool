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
	//�õ��ļ����
	hFile = CreateFile(
		FileName, GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	//�õ��ļ���С
	DWORD dwFileSize = GetFileSize(hFile, NULL);
	//long long dwFileSize = GetFileSize(hFile, NULL);
	DWORD ReadSize = 0;
	//long long ReadSize = 0;
	buf = new char[dwFileSize];
	//���ļ���ȡ���ڴ�
	ReadFile(hFile, buf, dwFileSize, &
		ReadSize, NULL);
	pDosH = (PIMAGE_DOS_HEADER)buf;



	if (*(PWORD)buf != IMAGE_DOS_SIGNATURE)
	{
		MessageBox(NULL, L"������Ч��PE�ļ�", L"����", MB_OK);
		return;
	}
	pDosH = (IMAGE_DOS_HEADER*)buf;
	if (*(PDWORD)((byte*)buf + pDosH->e_lfanew) != IMAGE_NT_SIGNATURE)
	{
		MessageBox(NULL, L"������Ч��PE�ļ�", L"����", MB_OK);
		return;
	}
	m_pFileHdr = (IMAGE_FILE_HEADER*)((byte*)buf + pDosH->e_lfanew + sizeof(DWORD));

	//���߸�����չͷ��Magic����32λ64λ   0x010B   0x020B
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
		pNtH = (PIMAGE_NT_HEADERS)(buf + pDosH->e_lfanew);//Ĭ�ϻ���32
	}



	if (IMAGE_DOS_SIGNATURE != pDosH->e_magic)
	{
		//MessageBox(L"����DOSͷ",L"s")
		AfxMessageBox(L"����DOSͷ");
		return;
	}
	//printf_s("DOSͷ:0x%X\n",pDosH->e_magic);
	//printf_s("EXE�ļ���ƫ��ͷ:0x%X\n",pDosH->e_lfanew);
	//��ȡNTͷ


	//PIMAGE_NT_HEADERS32 pNtH=(PIMAGE_NT_HEADERS32)buf;  
	if (pNtH->Signature != IMAGE_NT_SIGNATURE)
	{
		AfxMessageBox(L"����NTͷ");
		return;
	}


	m_pFileHdr = &pNtH->FileHeader;


	//��ȡ����ͷ
	//pSecH = IMAGE_FIRST_SECTION(pNtH);
	//��ȡ��ѡͷ����
	//pOptH = &(pNtH->OptionalHeader);

	//��ȡ����Ŀ¼
	//pDatD = &(pOptH->DataDirectory[0]);
	//��ȡ����������
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
	char *p = PeValue.GetBuffer();	//ת��Ϊchar* ����
	return strtoul(p, 0, 16);		//ת��Ϊʮ��������

}



void AnalysisOfPE::OutPutPeInfo(CString &StrPeValue, DWORD WithPeValue)
{
	CString NewStrPeValue;
	NewStrPeValue.Format(L"%08X", WithPeValue);//ת16����
	StrPeValue = NewStrPeValue;

}

DWORD AnalysisOfPE::CalcOffset(DWORD Rva)
{
	//ѭ���Ƚ����Ǹ�����  ����������ξͼ���ѭ��  
	//PIMAGE_NT_HEADERS32 pnt=pNtH;
	PIMAGE_SECTION_HEADER pSecHTemp = IMAGE_FIRST_SECTION(pNtH);//����ͷ
	int index = 0;
	while (!(Rva >= pSecHTemp->VirtualAddress&&
		Rva < pSecHTemp->VirtualAddress + pSecHTemp->SizeOfRawData))
	{
		//�����������λ�û���ҵ�
		if (index > pNtH->FileHeader.NumberOfSections)
		{
			return Rva;
		}
		++index;
		++pSecHTemp;
	}
	return Rva - pSecHTemp->VirtualAddress + pSecHTemp->PointerToRawData;;
}
