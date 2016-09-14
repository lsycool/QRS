/********************************************************************
	created:	2008/05/27
	created:	27:5:2008   16:11
	filename: 	e:\work\MapGIS71\RSPSRC\RASTERBASE\RasterIOAdapter\V7XAdapter.h
	file path:	e:\work\MapGIS71\RSPSRC\RASTERBASE\RasterIOAdapter
	file base:	V7XAdapter
	file ext:	h
	author:		Alpha
	
	purpose:	
*********************************************************************/

#pragma once
//#include "RasterIO.h"
#include "StripBuffer.h"
//#include "msOOdef.h"
#include "V7X_RasterIOAdapter.h"

//#include "V7X_RasterIOAdapter.h"
//#include "StripBuffer.h"

class CV7XAdapter
{
public:
    CV7XAdapter(void);
    // m_hRaster引用计数减1
    ~CV7XAdapter(void);

    // 初始化,m_hRaster引用计数加1
    long Init(MSRSDatasetH hRaster);

    // m_hRaster的Getter方法
    MSRSDatasetH GetRasterH () const { return m_hRaster; }
//    CGDataBase* GetGDBPtr() const { return m_ptGDB; }

    // 得到总行数
    long GetLineCount(long &lLineCount);
    
    // 得到总列数
    long GetSampleCount(long &lSampleCount);

    // 得到波段数
    long GetBandCount(int &nBandCount);

    // 得到数据类型
    long GetDataType(V7X_RAS_CELLTYPE &eDT);

    // 打开关闭金子塔层
    long OpenPyramidLayer(int nPyrLayerNum);
    long ClosePyramidLayer();

    //////////////////////////////////////////////////////////////////////////
    // 以下操作需要打开金字塔层
    //////////////////////////////////////////////////////////////////////////

	// 刷新缓冲区
	long Flush();

	// 读入某个波段的一个像元值
	inline long GetCell(const long &lBand, const long &lRow, const long &lCol, double &dVal);
	inline long GetCell(const long &lBand, const long &lRow, const long &lCol, double &dVal, bool &bIsNoData);

	// 写入某个波段的一个像元值
	inline long SetCell(const long &lBand, const long &lRow, const long &lCol, const double &dVal);
    

private:
    MSRSDatasetH    m_hRaster;  // 通用数据集句柄
//    CGDataBase*     m_ptGDB;    // 地理数据库指针,已打开

    int m_nBandCount;       // 波段数目
    long m_lLineCount;      // 行数
    long m_lSampleCount;    // 列数
    MSRSDataType m_eDT;     // 数据类型

    BOOL m_bHasNoDataVal;   // 是否有无效值      
	double m_dNoDataVal;	// 无效值
	double m_dInsteadVal;	// 无效值替代值

    STRIPBUF*       m_pBuffReader;  // 缓冲读取器
	long InitStripBuffers(MSRSDatasetH hRaster, int nBandCount);    // 初始化缓冲
	void FreeStripBuffers(int nBandCount);  // 释放缓冲

private:
	void Destroy();

    
#define IfInvalidThenReturnVoid() {if (!m_hRaster) return;}

#define IfInvalidThenReturnCode(err) {if (!m_hRaster) return err;}

#define ReturnWithV7XErr(err) \
        {\
            if (MS_SUCCESS==err) return V7X_RAS_FAIL; \
            else return V7X_RAS_SUCCESS;\
        }

};

LPRASTER_ADAPT WINAPI _CreateRasterAdaptInstance(MSRSDatasetH hImg)
{
	long lErr = V7X_RAS_SUCCESS;

	CV7XAdapter* pRasObjAdpt = new CV7XAdapter();
	lErr = pRasObjAdpt->Init(hImg);

	if (V7X_RAS_FAIL==lErr)
	{
		delete pRasObjAdpt;
		return NULL;
	}
	else
	{
		return pRasObjAdpt;
	}
}

long WINAPI _FlushInstance(LPRASTER_ADAPT pRasObjAdpt)
{
	long lErr = V7X_RAS_FAIL;
	if (pRasObjAdpt)
	{
		CV7XAdapter* pRas = static_cast<CV7XAdapter*>(pRasObjAdpt);
		if (NULL != pRas)
		{
			lErr = pRas->Flush();
		}
	}

	return lErr;
}

void WINAPI _ReleaseRasterAdaptInstance(LPRASTER_ADAPT pRasObjAdpt)
{
	if (pRasObjAdpt)
	{
		_FlushInstance(pRasObjAdpt);
		delete (CV7XAdapter*)pRasObjAdpt;
	}
}

MSRSDatasetH WINAPI _GetDatasetHandle(LPRASTER_ADAPT pRasObjAdpt)
{
    MSRSDatasetH hDS = NULL;

    if (pRasObjAdpt)
    {
        CV7XAdapter* pRas = static_cast<CV7XAdapter*>(pRasObjAdpt);
        if (NULL != pRas)
        {
            hDS = pRas->GetRasterH();
        }
    } 

    return hDS;
}

long WINAPI v7x_rsOpenPyramidLayer(LPRASTER_ADAPT pRasObjAdpt, short PyLayerNo)
{
	long lErr = V7X_RAS_FAIL;
	if (pRasObjAdpt)
	{
		CV7XAdapter *pRas = static_cast<CV7XAdapter *>(pRasObjAdpt);
		if (NULL != pRas)
		{
			lErr = pRas->OpenPyramidLayer(PyLayerNo);
		}
	}

	return lErr;
}

long WINAPI v7x_rsClosePyramidLayer(LPRASTER_ADAPT pRasOBJ)
{
	long lErr = V7X_RAS_FAIL;
	if (pRasOBJ)
	{
		
		CV7XAdapter* pRas = static_cast<CV7XAdapter *>(pRasOBJ);
		if (pRasOBJ)
		{
			lErr = pRas->ClosePyramidLayer();
		}
	}

	return lErr;
}

long WINAPI v7x_rsSetCell(LPRASTER_ADAPT pRasOBJ, short BandNo, long RowNo, long ColNo, double Value)
{
	long lErr = V7X_RAS_FAIL;

	if (pRasOBJ)
	{
		CV7XAdapter* pRas = (CV7XAdapter*)pRasOBJ;
		lErr = pRas->SetCell(BandNo, RowNo, ColNo, Value);
	}

	return lErr;
}

long WINAPI v7x_rsGetCell(LPRASTER_ADAPT pRasOBJ, short BandNo, long RowNo, long ColNo, double &Value, char *pInvalidFlag)
{
	long lErr = V7X_RAS_SUCCESS;
	bool bIsNoData;

	if (pRasOBJ)
	{
		CV7XAdapter* pRas = (CV7XAdapter*)pRasOBJ;
		
		if (pInvalidFlag)
		{
            lErr = pRas->GetCell(BandNo, RowNo, ColNo, Value, bIsNoData);
			*pInvalidFlag = bIsNoData ? 1 : 0;
		}
        else
        {
            lErr = pRas->GetCell(BandNo, RowNo, ColNo, Value);
        }
	}

	return lErr;
}
