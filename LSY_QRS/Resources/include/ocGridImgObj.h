//ocImgObj.h create in 2006.4
//影像对象类，支持对影像对象的合并，添加，删除等操作。

/**********************************************************************************
2006.5.11  修改影像对象,不在内部申请属性缓冲,用外部指针进行传递,外部控制文件指针的打开关闭

2006.5.16  修改迭代时创建新的属性文件，为每个影像对象创建两个属性文件

2006.5.18  修改有子对象的向上分割属性文件的创建方式，拷贝子对象属性作为初始读属性

2006.5.19  为向下分割增加接口：
GetGridPt		为扫描线查找子对象增加的接口，取对象层栅格指针
GetImgObjNums   取对象层总对象数	

2006.5.26  修改扫描线寻找邻域函数 把标志值为0修改为最大值，满足在影像中同时存在像元和对象时
找邻域的要求

2006.5.29  增加函数GetSubObjNeighbor,寻找子对象的邻域，由于在子像元向上合并时可能同时存在
对象和像元，取邻域时只取对象不取像元

2006.6.28  统一栅格文件名和属性文件名，栅格文件grd.msi，属性文件att0、att1；修改创建文件的函数

2006.7.12  对于栅格指针有两种关闭方式:在内部打开的在内部关闭，从外部传入的在外部关闭

2006.7.12  为解决当前对象层在显示和分割时的问题，显示当前分割影像同时设置新的当前层进行分割
增加函数强制把当前层影像指针赋空

2006.7.20  为属性缓冲增加PreReadObjAtt接口，在每次打开属性文件时都对属性缓冲中的记录清空。
在重复利用属性缓冲时出现问题，每次使用读缓冲时上一次的内容没有清空，因此做了相应的修改。

2006.7.31  增加修改色表的函数，当完成分割后用影像的均值来改写影像的色表
**********************************************************************************/
#pragma once
#ifndef _OC_ImageObjct_H_
#define _OC_ImageObjct_H_

#include "ObjAttBuf.h"
//#include "V7XAdapter.h"
#include "V7X_RasterIOAdapter.h"
#include "resource.h"

using namespace RASTER_IO;


class CImgObj //影像对象类 = 栅格信息 + 属性信息
{
public:

	CImgObj();
	virtual ~CImgObj();
	//影像对象属性缓冲初始化	
	bool	SetReadAttBuf(CObjAtt *pReadObjAtt);
	bool	SetWriteAttBuf(CObjAtt *pWriteObjAtt);

	CObjAtt*	GetReadAttBuf();
	CObjAtt*	GetWriteAttBuf();

	//{	对象初始化 设置文件指针
	bool	SetGrdFilePt(MSRSDatasetH hDS);
	bool	SetAttFilePt(IFILE *fpAtt);
	void	ForceGrdPtEmpty();
	
	
	
	//设置当前影像对象层的目录名
	bool	SetCurLayDir(char *pszDir);
	//{打开属性文件
	bool	OpenAttFile(char *pszOrgAttName);
	//打开栅格文件
	bool	OpenGridFile(char *pszGrdName);

	
	//无下层分割结果，直接创建新的栅格文件
	//pszGridName   新栅格文件名
	//hDS		    原始影像
	long    CreateNewGrid(MSRSDatasetH hDS);//long	CreateNewGrid(MSI *pOrgMsi);

	//拷贝属性文件并创建新的写属性文件
	bool	CreateAttFile(char *pszRAttName);
	//创建新属性文件,同时创建读属性文件和写属性文件
	bool	CreateNewAttFile();
	//更新读、写缓冲的内容
	bool	UpdateAtt();

	//取对象结果的栅格文件名
	bool    GetGridName(CString& strGridName);
	//取对象结果的属性文件名，(读属性文件的文件名)
	bool	GetAttName(CString& strAttName);

	//{		取栅格文件的行列值
	long	GetGridLines(long& lLines);
	long	GetGridLineCells(long& lLineCells);
	
	bool	GetGridPt(MSRSDatasetH *phDS);	//取栅格文件指针//bool	GetGridPt(MSI **pMsi);	//取栅格文件指针 
	//}

	//根据位置取影像对象ID
	long GetImgObjID1(OCREGPOS ObjPos, long& lObjID);

	long GetImgObjID2(long lRow,long lCol,long& lObjID);

	bool GetImgObjRect(long lObjID,RECT& rect);

	//取当前层对象数
	bool GetImgObjNums(long& lObjNums);

	//{	导出结果
	//导出矢量结果,待修改2006.6.12，栅格转矢量时通过每个种子点进行转换
	long CovGridToVecter(char *pszRegName,bool bIsSmooth,int nSmoothType,double dSmooth);
	
	//将分割结果导出，每个对象填充平均灰度值   待修改2006.5.17
	long ExportSegRstImg(char *pszImgName,long lBands);

	//导出分类结果影像，
	long ExportClsImg(MSRSDatasetH pClsMsi,long *lpClsID/*,char *pszObjImg,long lBands,int iPossibilityNums,
												int iPossibleNo*/);
	
	//找邻域对象，在已经生成的影像对象上找
	long GetNabeObjects(OCREGPOS& ObjPos, AryNabObj& NabObjs);
	//找邻域对象，只取对象不取像元
	long GetSubObjNeighbor(OCREGPOS& ObjPos, AryNabObj& NabObjs);

	//对第一次分割时在对象影像上找四邻域
	long GetNabeObjectsFirst(long lRow, long lCol, OCNABOBJ	pNabObjs[4], int& iNabNum);
	long GetNabeObjectsFirst1(long lRow, long lCol, AryNabObj& NabObjs);


	// 将ObjPos1与ObjPos2合并，新对象的对象号为lObjID  todo 合并属性部分
	// 用SetImgObjID函数代替
	long UniteTwoObjects(OCREGPOS& ObjPos1, OCREGPOS& ObjPos2, long lObjID);
	//设置影像对象ID(ID号从1开始)
	long SetImgObjID(OCREGPOS& ObjPos, long lObjFill);

	//保存当前层分割结果的栅格文件
	long SaveRstGrid();	
	//保存当前层分割结果的属性文件
	bool SaveRstAtt();

	//关闭只读的栅格文件
	long CloseGridForRead();
	//关闭只读的属性文件
	bool CloseAttForRead();


	//{	无上层约束对象时，创建栅格文件
	//根据已有的下层分割结果进行分割时首先要拷贝栅格文件
	long	CreateGrid(char *pszOrgGrid);

	//初始化V7X
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

	//释放V7X
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

	// 搜索相邻对象，考虑环岛，采取扫描线法
	long SearchNabeObjsByScanLin(OCREGPOS& ObjPos, AryNabObj& NabObjs);
	// GetSubObjNeighbor函数需要调用的扫描线
	long SearchNabeObjsByScanLin1(OCREGPOS& ObjPos, AryNabObj& NabObjs);

	// 向堆栈中插入新的邻近对象
	long InsertANabObj(OCNABOBJ& InNabObj, AryNabObj& NabObjs);

	// 搜索种子并入栈，寻找相邻对象
	// long lCurY,			在lYScan行搜索种子
	// long lXLeft, long lXRight, 当前扫描行待填充对象X方向边界
	// long lSeedNo,		种子对象号
	long SearchSeedNab(long lCurY, long lXLeft, long lXRight, long lSeedNo, AryObjPos& StackPos, AryNabObj& NabObjs);
	// GetSubObjNeighbor函数需要调用的扫描线
	long SearchSeedNab1(long lCurY, long lXLeft, long lXRight, long lSeedNo, AryObjPos& StackPos, AryNabObj& NabObjs);

	// 更改对象号，扫描线种子填充法
	// long lObjFill		填充值
	long FillAObject(OCREGPOS& ObjPos, long lObjFill);

	// 搜索种子并入栈
	long SearchSeed(long lCurY, long lXLeft, long lXRight, long lCurVal, AryObjPos& StackPos);


	//通用影像像元读写---20090616 在mssfunction.h中
	//double msGetDataSetCellValue(MSRSDatasetH hDS,long lBandNo,long Line,long LineCell);
	//long   msSetDataSetCellValue(MSRSDatasetH hDS,long lBandNo,long Line,long LineCell,double CellValue);
	

public:
	//{	栅格管理	
	 
	MSRSDatasetH    m_ObjhDS;		//通用影像---//MSI	*m_pObjMsi;	//在当前层新的分割对象影像
	long			m_lLines;		//分割影像的行数
	long			m_lLineCells;	//分割影像的列数
	LPRASTER_ADAPT	m_lpRasAdpt;	//V7X驱动
	
	CString			m_strGridName;	//影像对象的栅格文件名		
	CString			m_strRAttName;	//影像对象的读属性文件名
	CString			m_strWAttName;	//影像对象的写属性文件名
	CString			m_strDir;		//当前分割层的文件夹路径名

//private:
public:
	//{	属性管理   
	CObjAtt			*m_pReadObjAtt;	//属性读缓冲
	CObjAtt			*m_pWriteObjAtt;//属性写缓冲
	//}

//棋盘分割测试
public:
	long SetImgObjID1(OCREGPOS& ObjPos, long lObjFill);
	long SetImgObjID2(OCREGPOS& ObjPos, long lObjFill);
	long SetImgObjID3(OCREGPOS& ObjPos, long lObjFill);
	long SetImgObjID4(OCREGPOS& ObjPos, long lObjFill,int size);//FOR 四叉树

//20090706棋盘、四叉树分割集成
public:
	long SetImgObjID_1(OCREGPOS& ObjPos, long lObjFill,float fPreScale);
	long SetImgObjID_2(OCREGPOS& ObjPos, long lObjFill);
	long SetImgObjID_3(OCREGPOS& ObjPos, long lObjFill);
	long SetImgObjID_5(OCREGPOS& ObjPos, long lObjFill);
};

#endif
