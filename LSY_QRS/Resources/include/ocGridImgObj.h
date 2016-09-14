//ocImgObj.h create in 2006.4
//Ӱ������֧࣬�ֶ�Ӱ�����ĺϲ�����ӣ�ɾ���Ȳ�����

/**********************************************************************************
2006.5.11  �޸�Ӱ�����,�����ڲ��������Ի���,���ⲿָ����д���,�ⲿ�����ļ�ָ��Ĵ򿪹ر�

2006.5.16  �޸ĵ���ʱ�����µ������ļ���Ϊÿ��Ӱ����󴴽����������ļ�

2006.5.18  �޸����Ӷ�������Ϸָ������ļ��Ĵ�����ʽ�������Ӷ���������Ϊ��ʼ������

2006.5.19  Ϊ���·ָ����ӽӿڣ�
GetGridPt		Ϊɨ���߲����Ӷ������ӵĽӿڣ�ȡ�����դ��ָ��
GetImgObjNums   ȡ������ܶ�����	

2006.5.26  �޸�ɨ����Ѱ�������� �ѱ�־ֵΪ0�޸�Ϊ���ֵ��������Ӱ����ͬʱ������Ԫ�Ͷ���ʱ
�������Ҫ��

2006.5.29  ���Ӻ���GetSubObjNeighbor,Ѱ���Ӷ������������������Ԫ���Ϻϲ�ʱ����ͬʱ����
�������Ԫ��ȡ����ʱֻȡ����ȡ��Ԫ

2006.6.28  ͳһդ���ļ����������ļ�����դ���ļ�grd.msi�������ļ�att0��att1���޸Ĵ����ļ��ĺ���

2006.7.12  ����դ��ָ�������ֹرշ�ʽ:���ڲ��򿪵����ڲ��رգ����ⲿ��������ⲿ�ر�

2006.7.12  Ϊ�����ǰ���������ʾ�ͷָ�ʱ�����⣬��ʾ��ǰ�ָ�Ӱ��ͬʱ�����µĵ�ǰ����зָ�
���Ӻ���ǿ�ưѵ�ǰ��Ӱ��ָ�븳��

2006.7.20  Ϊ���Ի�������PreReadObjAtt�ӿڣ���ÿ�δ������ļ�ʱ�������Ի����еļ�¼��ա�
���ظ��������Ի���ʱ�������⣬ÿ��ʹ�ö�����ʱ��һ�ε�����û����գ����������Ӧ���޸ġ�

2006.7.31  �����޸�ɫ��ĺ���������ɷָ����Ӱ��ľ�ֵ����дӰ���ɫ��
**********************************************************************************/
#pragma once
#ifndef _OC_ImageObjct_H_
#define _OC_ImageObjct_H_

#include "ObjAttBuf.h"
//#include "V7XAdapter.h"
#include "V7X_RasterIOAdapter.h"
#include "resource.h"

using namespace RASTER_IO;


class CImgObj //Ӱ������� = դ����Ϣ + ������Ϣ
{
public:

	CImgObj();
	virtual ~CImgObj();
	//Ӱ��������Ի����ʼ��	
	bool	SetReadAttBuf(CObjAtt *pReadObjAtt);
	bool	SetWriteAttBuf(CObjAtt *pWriteObjAtt);

	CObjAtt*	GetReadAttBuf();
	CObjAtt*	GetWriteAttBuf();

	//{	�����ʼ�� �����ļ�ָ��
	bool	SetGrdFilePt(MSRSDatasetH hDS);
	bool	SetAttFilePt(IFILE *fpAtt);
	void	ForceGrdPtEmpty();
	
	
	
	//���õ�ǰӰ�������Ŀ¼��
	bool	SetCurLayDir(char *pszDir);
	//{�������ļ�
	bool	OpenAttFile(char *pszOrgAttName);
	//��դ���ļ�
	bool	OpenGridFile(char *pszGrdName);

	
	//���²�ָ�����ֱ�Ӵ����µ�դ���ļ�
	//pszGridName   ��դ���ļ���
	//hDS		    ԭʼӰ��
	long    CreateNewGrid(MSRSDatasetH hDS);//long	CreateNewGrid(MSI *pOrgMsi);

	//���������ļ��������µ�д�����ļ�
	bool	CreateAttFile(char *pszRAttName);
	//�����������ļ�,ͬʱ�����������ļ���д�����ļ�
	bool	CreateNewAttFile();
	//���¶���д���������
	bool	UpdateAtt();

	//ȡ��������դ���ļ���
	bool    GetGridName(CString& strGridName);
	//ȡ�������������ļ�����(�������ļ����ļ���)
	bool	GetAttName(CString& strAttName);

	//{		ȡդ���ļ�������ֵ
	long	GetGridLines(long& lLines);
	long	GetGridLineCells(long& lLineCells);
	
	bool	GetGridPt(MSRSDatasetH *phDS);	//ȡդ���ļ�ָ��//bool	GetGridPt(MSI **pMsi);	//ȡդ���ļ�ָ�� 
	//}

	//����λ��ȡӰ�����ID
	long GetImgObjID1(OCREGPOS ObjPos, long& lObjID);

	long GetImgObjID2(long lRow,long lCol,long& lObjID);

	bool GetImgObjRect(long lObjID,RECT& rect);

	//ȡ��ǰ�������
	bool GetImgObjNums(long& lObjNums);

	//{	�������
	//����ʸ�����,���޸�2006.6.12��դ��תʸ��ʱͨ��ÿ�����ӵ����ת��
	long CovGridToVecter(char *pszRegName,bool bIsSmooth,int nSmoothType,double dSmooth);
	
	//���ָ���������ÿ���������ƽ���Ҷ�ֵ   ���޸�2006.5.17
	long ExportSegRstImg(char *pszImgName,long lBands);

	//����������Ӱ��
	long ExportClsImg(MSRSDatasetH pClsMsi,long *lpClsID/*,char *pszObjImg,long lBands,int iPossibilityNums,
												int iPossibleNo*/);
	
	//������������Ѿ����ɵ�Ӱ���������
	long GetNabeObjects(OCREGPOS& ObjPos, AryNabObj& NabObjs);
	//���������ֻȡ����ȡ��Ԫ
	long GetSubObjNeighbor(OCREGPOS& ObjPos, AryNabObj& NabObjs);

	//�Ե�һ�ηָ�ʱ�ڶ���Ӱ������������
	long GetNabeObjectsFirst(long lRow, long lCol, OCNABOBJ	pNabObjs[4], int& iNabNum);
	long GetNabeObjectsFirst1(long lRow, long lCol, AryNabObj& NabObjs);


	// ��ObjPos1��ObjPos2�ϲ����¶���Ķ����ΪlObjID  todo �ϲ����Բ���
	// ��SetImgObjID��������
	long UniteTwoObjects(OCREGPOS& ObjPos1, OCREGPOS& ObjPos2, long lObjID);
	//����Ӱ�����ID(ID�Ŵ�1��ʼ)
	long SetImgObjID(OCREGPOS& ObjPos, long lObjFill);

	//���浱ǰ��ָ�����դ���ļ�
	long SaveRstGrid();	
	//���浱ǰ��ָ����������ļ�
	bool SaveRstAtt();

	//�ر�ֻ����դ���ļ�
	long CloseGridForRead();
	//�ر�ֻ���������ļ�
	bool CloseAttForRead();


	//{	���ϲ�Լ������ʱ������դ���ļ�
	//�������е��²�ָ������зָ�ʱ����Ҫ����դ���ļ�
	long	CreateGrid(char *pszOrgGrid);

	//��ʼ��V7X
	long	InitialV7X()
	{
		long	lErr=MS_SUCCESS;
		if (m_ObjhDS!=NULL)//2011-1207 PP ADD
		{
			CString		CurName = _T("");
//			CurName.Format("%s",msRSGetDescription(m_ObjhDS));
			CurName=msRSGetDescription(m_ObjhDS);
			m_lpRasAdpt = _CreateRasterAdaptInstance(m_ObjhDS);
		}
		
		if (!m_lpRasAdpt) {lErr=MS_FAIL;	return lErr;}
		v7x_rsOpenPyramidLayer(m_lpRasAdpt, 1);
		return lErr;
	}

	//�ͷ�V7X
	void	ReleaseV7X()
	{
		if(m_lpRasAdpt)
		{
			_FlushInstance(m_lpRasAdpt);
				(m_lpRasAdpt);
			_ReleaseRasterAdaptInstance(m_lpRasAdpt);
		}
	}

private:

	// �������ڶ��󣬿��ǻ�������ȡɨ���߷�
	long SearchNabeObjsByScanLin(OCREGPOS& ObjPos, AryNabObj& NabObjs);
	// GetSubObjNeighbor������Ҫ���õ�ɨ����
	long SearchNabeObjsByScanLin1(OCREGPOS& ObjPos, AryNabObj& NabObjs);

	// ���ջ�в����µ��ڽ�����
	long InsertANabObj(OCNABOBJ& InNabObj, AryNabObj& NabObjs);

	// �������Ӳ���ջ��Ѱ�����ڶ���
	// long lCurY,			��lYScan����������
	// long lXLeft, long lXRight, ��ǰɨ���д�������X����߽�
	// long lSeedNo,		���Ӷ����
	long SearchSeedNab(long lCurY, long lXLeft, long lXRight, long lSeedNo, AryObjPos& StackPos, AryNabObj& NabObjs);
	// GetSubObjNeighbor������Ҫ���õ�ɨ����
	long SearchSeedNab1(long lCurY, long lXLeft, long lXRight, long lSeedNo, AryObjPos& StackPos, AryNabObj& NabObjs);

	// ���Ķ���ţ�ɨ����������䷨
	// long lObjFill		���ֵ
	long FillAObject(OCREGPOS& ObjPos, long lObjFill);

	// �������Ӳ���ջ
	long SearchSeed(long lCurY, long lXLeft, long lXRight, long lCurVal, AryObjPos& StackPos);


	//ͨ��Ӱ����Ԫ��д---20090616 ��mssfunction.h��
	//double msGetDataSetCellValue(MSRSDatasetH hDS,long lBandNo,long Line,long LineCell);
	//long   msSetDataSetCellValue(MSRSDatasetH hDS,long lBandNo,long Line,long LineCell,double CellValue);
	

public:
	//{	դ�����	
	 
	MSRSDatasetH    m_ObjhDS;		//ͨ��Ӱ��---//MSI	*m_pObjMsi;	//�ڵ�ǰ���µķָ����Ӱ��
	long			m_lLines;		//�ָ�Ӱ�������
	long			m_lLineCells;	//�ָ�Ӱ�������
	LPRASTER_ADAPT	m_lpRasAdpt;	//V7X����
	
	CString			m_strGridName;	//Ӱ������դ���ļ���		
	CString			m_strRAttName;	//Ӱ�����Ķ������ļ���
	CString			m_strWAttName;	//Ӱ������д�����ļ���
	CString			m_strDir;		//��ǰ�ָ����ļ���·����

//private:
public:
	//{	���Թ���   
	CObjAtt			*m_pReadObjAtt;	//���Զ�����
	CObjAtt			*m_pWriteObjAtt;//����д����
	//}

//���̷ָ����
public:
	long SetImgObjID1(OCREGPOS& ObjPos, long lObjFill);
	long SetImgObjID2(OCREGPOS& ObjPos, long lObjFill);
	long SetImgObjID3(OCREGPOS& ObjPos, long lObjFill);
	long SetImgObjID4(OCREGPOS& ObjPos, long lObjFill,int size);//FOR �Ĳ���

//20090706���̡��Ĳ����ָ��
public:
	long SetImgObjID_1(OCREGPOS& ObjPos, long lObjFill,float fPreScale);
	long SetImgObjID_2(OCREGPOS& ObjPos, long lObjFill);
	long SetImgObjID_3(OCREGPOS& ObjPos, long lObjFill);
	long SetImgObjID_5(OCREGPOS& ObjPos, long lObjFill);
};

#endif
