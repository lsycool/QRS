/********************************************************************
	created:	2008/05/27
	created:	27:5:2008   14:29
	filename: 	e:\work\MapGIS71\RSPSRC\RASTERBASE\RasterIOAdapter\V7X_RasterIOAdapter.h
	file path:	e:\work\MapGIS71\RSPSRC\RASTERBASE\RasterIOAdapter
	file base:	V7X_RasterIOAdapter
	file ext:	h
	author:		Alpha
	
	purpose:	Use a part of interfaces defined in rasbase.h to access
                MSRSDataset API. If your application is only used to
                support RasObj and you want to support more raster format,
                you can benefit from this API.
*********************************************************************/

#ifndef __V7X_RASTERIOADAPTER_H__
#define __V7X_RASTERIOADAPTER_H__
#pragma once

#include "RasterIO.h"
#include "msOOdef.h"
using namespace RASTER_IO;
//////////////////////////////////////////////////////////////////////////
// �궨��
//////////////////////////////////////////////////////////////////////////

#define V7X_RAS_SUCCESS     0L 
#define V7X_RAS_FAIL       -10000000L

//////////////////////////////////////////////////////////////////////////
// �Զ�����������
//////////////////////////////////////////////////////////////////////////

//typedef void*	LPRASTER_ADAPT;

//////////////////////////////////////////////////////////////////////////
// ö�ٱ���
//////////////////////////////////////////////////////////////////////////

//enum V7X_RAS_CELLTYPE  //��Ԫ����.
//{
//    V7X_RAS_UNKNOWN = MS_Unknown,
//    V7X_RAS_UINT8	= MS_Byte,	    // 8λ�޷�������
//    //V7X_RAS_ASCII	= MS_Unknown,   // ��0��β��ASCLL��
//    V7X_RAS_UINT16	= MS_UInt16,	// 16λ�޷�������
//    V7X_RAS_UINT32	= MS_UInt32,	// 32λ�޷�������
//    V7X_RAS_INT8	= MS_Int8,	    // 8λ�з�������
//    V7X_RAS_INT16	= MS_Int16,	    // 16λ�з�������
//    V7X_RAS_INT32	= MS_Int32,	    // 32λ�з�������
//    V7X_RAS_IEEE4	= MS_Float32,	// ���ֽڸ�������
//    V7X_RAS_IEEE8  	= MS_Float64,	// ˫���ȸ�������
//    V7X_RAS_1BIT    = MS_1Bit       // 1λ��ֵͼ������
//};
// ע��:
//     һ�¼�������ֲ��ʱ����һЩӰ��
//     2. ͨ�����ݼ���֧����0��β��ASCII����

//////////////////////////////////////////////////////////////////////////
// �ӿ�
//////////////////////////////////////////////////////////////////////////

// ����
LPRASTER_ADAPT WINAPI _CreateRasterAdaptInstance(MSRSDatasetH hImg);
void WINAPI _ReleaseRasterAdaptInstance(LPRASTER_ADAPT pRasObjAdpt);

// ���»���
long WINAPI _FlushInstance(LPRASTER_ADAPT pRasObjAdpt);

// �õ��ڲ����ݼ����
MSRSDatasetH WINAPI _GetDatasetHandle(LPRASTER_ADAPT pRasObjAdpt);

// ����������
long WINAPI v7x_rsOpenPyramidLayer(LPRASTER_ADAPT pRasObjAdpt, short PyLayerNo);
long WINAPI v7x_rsClosePyramidLayer(LPRASTER_ADAPT pRasOBJ);

//===================================================================
// ���²�����Ҫ�򿪽�����
//===================================================================

// ��д����
long WINAPI v7x_rsSetCell(LPRASTER_ADAPT pRasOBJ, short BandNo, long RowNo, long ColNo, double Value);
long WINAPI v7x_rsGetCell(LPRASTER_ADAPT pRasOBJ, short BandNo, long RowNo, long ColNo, double &Value, char *pInvalidFlag=NULL);


#endif // __V7X_RASTERIOADAPTER_H__