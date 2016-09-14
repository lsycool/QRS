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
    // m_hRaster���ü�����1
    ~CV7XAdapter(void);

    // ��ʼ��,m_hRaster���ü�����1
    long Init(MSRSDatasetH hRaster);

    // m_hRaster��Getter����
    MSRSDatasetH GetRasterH () const { return m_hRaster; }
//    CGDataBase* GetGDBPtr() const { return m_ptGDB; }

    // �õ�������
    long GetLineCount(long &lLineCount);
    
    // �õ�������
    long GetSampleCount(long &lSampleCount);

    // �õ�������
    long GetBandCount(int &nBandCount);

    // �õ���������
    long GetDataType(V7X_RAS_CELLTYPE &eDT);

    // �򿪹رս�������
    long OpenPyramidLayer(int nPyrLayerNum);
    long ClosePyramidLayer();

    //////////////////////////////////////////////////////////////////////////
    // ���²�����Ҫ�򿪽�������
    //////////////////////////////////////////////////////////////////////////

	// ˢ�»�����
	long Flush();

	// ����ĳ�����ε�һ����Ԫֵ
	inline long GetCell(const long &lBand, const long &lRow, const long &lCol, double &dVal);
	inline long GetCell(const long &lBand, const long &lRow, const long &lCol, double &dVal, bool &bIsNoData);

	// д��ĳ�����ε�һ����Ԫֵ
	inline long SetCell(const long &lBand, const long &lRow, const long &lCol, const double &dVal);
    

private:
    MSRSDatasetH    m_hRaster;  // ͨ�����ݼ����
//    CGDataBase*     m_ptGDB;    // �������ݿ�ָ��,�Ѵ�

    int m_nBandCount;       // ������Ŀ
    long m_lLineCount;      // ����
    long m_lSampleCount;    // ����
    MSRSDataType m_eDT;     // ��������

    BOOL m_bHasNoDataVal;   // �Ƿ�����Чֵ      
	double m_dNoDataVal;	// ��Чֵ
	double m_dInsteadVal;	// ��Чֵ���ֵ

    STRIPBUF*       m_pBuffReader;  // �����ȡ��
	long InitStripBuffers(MSRSDatasetH hRaster, int nBandCount);    // ��ʼ������
	void FreeStripBuffers(int nBandCount);  // �ͷŻ���

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
