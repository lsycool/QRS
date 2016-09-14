// ObjAttBuf.h: interface for the CObjAtt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJATTBUF_H__5FA00FAC_90DA_401D_A0D9_A617792F05D4__INCLUDED_)
#define AFX_OBJATTBUF_H__5FA00FAC_90DA_401D_A0D9_A617792F05D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IFILE.h"
#include "msOOdef.h"

const char oc_ImgOBjATT_FILE10[]="OC_IMGOBJATT_FILE_VER1.0";

//���Ի���������״̬:����д
class CObjAtt  
{
public:
	CObjAtt();
	virtual ~CObjAtt();
	void	ReleaseBuffer();

	bool	InitReadBuffer(long lBufLen,long lBands);
	bool	InitWriteBuffer(long lBufLen,long lBands);

	//Ϊ�˱��ⷴ���Ĵ��ļ����ļ�ָ�����������
	bool	SetAttFilePointer(IFILE *fpAttFile);
	void	FreeAttFilePointer();
	IFILE*	GetFilePointer();
	bool	CloseObjAttFile();

	//ȡ��ǰ��������
	long	GetTotalObjNums();
	//ȡ�ֿ黺�峤��
	long	GetBufLength();

	//������ 
	bool	GetObjAttFromBlock(long lObjID, OOOBJATT *pObjAtt);
	//�ϲ�������������ԣ���������д���һ�������У����ڶ���������Ϊdel
	bool	UniteTwoObjAtt(long lObjID1,long lObjID2, OOOBJATT *pNewObjAtt);

	//д����
	bool	PreWriteObjAtt();	//��д����ʱ������Ӧ�ĳ�ʼ������
	bool	PreReadObjAtt();
	bool	SetObjAttInBlock(OOOBJATT *pObjAtt);	//������+1
	bool	SaveCurBuffer();//����ǰ�������ݴ���

	//����ɾ�����
	bool	SetDelFlag(long	lObjID);
	bool	SetOneObjAtt(long lObjID, OOOBJATT *pObjAtt);//�����������ӣ������޸�����	
	bool	GetOneObjAtt(long lObjID, OOOBJATT *pObjAtt);
	bool	ReadOneObjRect(long lObjID, RECT& rect);
	bool	UpdateBufObjAtt(long lObjID, OOOBJATT *pObjAtt);

	///{�ֿ�����Ժ������ڶ�����ʱʹ�ã�����ָ�����ֱ��ʹ���ڲ�������ڴ�
	////ע�ⲻҪ�޸Ļ����е�����
	//ȡ��ǰ�����ļ��ֿ��������ڶ����Բ���ʱ��Ч
	long	GetBlockNums();	
	bool	GetOneBlock(long lBlockNo, long& lBlockRcdNums);

	//}

public:
	//�ļ�ͷ����
	bool	CheckFileValidity();
	bool	WriteFileHeader();				//todo 3.28
	bool	ReadObjNums(long& lObjNums);	//todo 3.28
	//bool	WriteObjNums();					//todo 3.28

private:
	bool	WriteOneBlock();		//д����ʱ����
	//bool GetObjAttFromBlock0(long lObjID, OOOBJATT *pObjAtt) 
	//{
	//	const long lRecordNo((lObjID-1)%m_lBufLen);

	//	if(lRecordNo<0 || (lObjID-1)/m_lBufLen!=m_lCurBlockNo || lRecordNo>=m_lCurBufRcdNums)
	//		return	false;

	//	pObjAtt->bIsDel=m_pObjAttBuf[lRecordNo].bIsDel;
	//	pObjAtt->lObjNo=m_pObjAttBuf[lRecordNo].lObjNo;
	//	pObjAtt->lPerim=m_pObjAttBuf[lRecordNo].lPerim;
	//	pObjAtt->lPixNum=m_pObjAttBuf[lRecordNo].lPixNum;
	//	memcpy(&(pObjAtt->lrRect),&(m_pObjAttBuf[lRecordNo].lrRect),sizeof(RECT));
	//	memcpy(&(pObjAtt->ObjPos),&(m_pObjAttBuf[lRecordNo].ObjPos),sizeof(OCREGPOS));
	//	for(long li=0;li<m_lBands;li++)
	//	{
	//		pObjAtt->pdMean[li]=m_pObjAttBuf[lRecordNo].pdMean[li];
	//		pObjAtt->pdStdDev[li]=m_pObjAttBuf[lRecordNo].pdStdDev[li];
	//	}

	//	return	true;
	//}

private:
	IFILE	   *m_fpAttFile;
	long		m_lBands;
	long		m_lBufLen;
	OOOBJATT   *m_pObjAttBuf;		//���Ի���
	long		m_lCurBufRcdNums;	//��ǰ�����д��ڵļ�¼��(<=���峤��)
	long		m_lCurBlockNo;		//��ǰ����Ŀ��
	long		m_lBlockNums;		//��ǰ�ļ��ܵķֿ���

private:
	long		m_lOffSet;			//�����ļ��е�һ����¼��ƫ��ֵ
	long		m_lObjNums;			//��ǰ�����ļ��ж�������  ��дʱ�ı䣬�ڶ�ʱ���ֲ���
};

#endif // !defined(AFX_OBJATTBUF_H__5FA00FAC_90DA_401D_A0D9_A617792F05D4__INCLUDED_)
