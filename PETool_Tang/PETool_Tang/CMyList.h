#pragma once

class CMyList:public CListCtrl
{
	DECLARE_DYNAMIC(CMyList)

public:
	CMyList();
	virtual ~CMyList();

protected:
	DECLARE_MESSAGE_MAP()
	//����;
	static bool Isint;		//�Ƿ�int������;Ĭ����;
	static bool method;		//������;
	static int CALLBACK ListCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);		//����ص�������
public:
	void AddColumn(DWORD dwCount, ...);					//������;
	void AddItem(DWORD dwCount, ...);					//������;
	void SortItemsPlus(int nColum, bool Isint = true);	//����;
};

//����ṹ��;
typedef struct  _DATA
{
	int SubItem;
	CMyList* pList;
}DATA;

