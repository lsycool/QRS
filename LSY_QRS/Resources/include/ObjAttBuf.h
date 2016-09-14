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

//属性缓冲有两种状态:读、写
class CObjAtt  
{
public:
	CObjAtt();
	virtual ~CObjAtt();
	void	ReleaseBuffer();

	bool	InitReadBuffer(long lBufLen,long lBands);
	bool	InitWriteBuffer(long lBufLen,long lBands);

	//为了避免反复的打开文件，文件指针在外面给定
	bool	SetAttFilePointer(IFILE *fpAttFile);
	void	FreeAttFilePointer();
	IFILE*	GetFilePointer();
	bool	CloseObjAttFile();

	//取当前对象总数
	long	GetTotalObjNums();
	//取分块缓冲长度
	long	GetBufLength();

	//读缓冲 
	bool	GetObjAttFromBlock(long lObjID, OOOBJATT *pObjAtt);
	//合并两个对象的属性，将新属性写入第一个对象中，将第二个对象标记为del
	bool	UniteTwoObjAtt(long lObjID1,long lObjID2, OOOBJATT *pNewObjAtt);

	//写缓冲
	bool	PreWriteObjAtt();	//在写属性时进行相应的初始化操作
	bool	PreReadObjAtt();
	bool	SetObjAttInBlock(OOOBJATT *pObjAtt);	//对象数+1
	bool	SaveCurBuffer();//将当前缓冲内容存盘

	//设置删除标记
	bool	SetDelFlag(long	lObjID);
	bool	SetOneObjAtt(long lObjID, OOOBJATT *pObjAtt);//对象数不增加，用于修改属性	
	bool	GetOneObjAtt(long lObjID, OOOBJATT *pObjAtt);
	bool	ReadOneObjRect(long lObjID, RECT& rect);
	bool	UpdateBufObjAtt(long lObjID, OOOBJATT *pObjAtt);

	///{分块读属性函数，在读操作时使用，返回指针可以直接使用内部分配的内存
	////注意不要修改缓冲中的内容
	//取当前属性文件分块数，仅在读属性操作时有效
	long	GetBlockNums();	
	bool	GetOneBlock(long lBlockNo, long& lBlockRcdNums);

	//}

public:
	//文件头操作
	bool	CheckFileValidity();
	bool	WriteFileHeader();				//todo 3.28
	bool	ReadObjNums(long& lObjNums);	//todo 3.28
	//bool	WriteObjNums();					//todo 3.28

private:
	bool	WriteOneBlock();		//写缓冲时调用
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
	OOOBJATT   *m_pObjAttBuf;		//属性缓冲
	long		m_lCurBufRcdNums;	//当前缓冲中存在的记录数(<=缓冲长度)
	long		m_lCurBlockNo;		//当前缓冲的块号
	long		m_lBlockNums;		//当前文件总的分块数

private:
	long		m_lOffSet;			//属性文件中第一条记录的偏移值
	long		m_lObjNums;			//当前属性文件中对象总数  在写时改变，在读时保持不变
};

#endif // !defined(AFX_OBJATTBUF_H__5FA00FAC_90DA_401D_A0D9_A617792F05D4__INCLUDED_)
