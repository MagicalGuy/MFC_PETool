#pragma once
class AnalysisOfPE {
public:
	AnalysisOfPE(void);
	~AnalysisOfPE(void);
public:
	CString PeFileName;
	char* buf;

	PIMAGE_DOS_HEADER pDosH;	//DOSͷ
	//PIMAGE_NT_HEADERS32 pNtH;	//NTͷ
	//PIMAGE_NT_HEADERS64 pNtH64;	//NTͷ64
	PIMAGE_NT_HEADERS pNtH;	//NTͷ

	IMAGE_FILE_HEADER* m_pFileHdr;		//�ļ�ͷ
	PIMAGE_OPTIONAL_HEADER32 pOptH;//��ѡͷ
	PIMAGE_OPTIONAL_HEADER64 pOptH64;//64λ�Ŀ�ѡPEͷ

	PIMAGE_SECTION_HEADER pSecH;//����ͷ
	PIMAGE_DATA_DIRECTORY pDatD;//����Ŀ¼
	PIMAGE_EXPORT_DIRECTORY pExpD;// ����������

	//IMAGE_OPTIONAL_HEADER* pOptHdr;


	void ObtainPeInfo(TCHAR *FileName);					//��ȡPE��Ϣ
	void ClosePeHandle();
	HANDLE hFile;
	DWORD ChangeNumber(CString NeedValue);			//����ת��
	void OutPutPeInfo(CString &StrPeValue, DWORD WithPeValue);
	DWORD CalcOffset(DWORD Rva);		//����λ��

};