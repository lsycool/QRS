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
// 宏定义
//////////////////////////////////////////////////////////////////////////

#define V7X_RAS_SUCCESS     0L 
#define V7X_RAS_FAIL       -10000000L

//////////////////////////////////////////////////////////////////////////
// 自定义数据类型
//////////////////////////////////////////////////////////////////////////

//typedef void*	LPRASTER_ADAPT;

//////////////////////////////////////////////////////////////////////////
// 枚举变量
//////////////////////////////////////////////////////////////////////////

//enum V7X_RAS_CELLTYPE  //像元类型.
//{
//    V7X_RAS_UNKNOWN = MS_Unknown,
//    V7X_RAS_UINT8	= MS_Byte,	    // 8位无符号整数
//    //V7X_RAS_ASCII	= MS_Unknown,   // 以0结尾的ASCLL串
//    V7X_RAS_UINT16	= MS_UInt16,	// 16位无符号整数
//    V7X_RAS_UINT32	= MS_UInt32,	// 32位无符号整数
//    V7X_RAS_INT8	= MS_Int8,	    // 8位有符号整数
//    V7X_RAS_INT16	= MS_Int16,	    // 16位有符号整数
//    V7X_RAS_INT32	= MS_Int32,	    // 32位有符号整数
//    V7X_RAS_IEEE4	= MS_Float32,	// 四字节浮点数据
//    V7X_RAS_IEEE8  	= MS_Float64,	// 双精度浮点数据
//    V7X_RAS_1BIT    = MS_1Bit       // 1位二值图的数据
//};
// 注意:
//     一下几点会对移植的时候有一些影响
//     2. 通用数据集不支持以0结尾的ASCII数据

//////////////////////////////////////////////////////////////////////////
// 接口
//////////////////////////////////////////////////////////////////////////

// 创建
LPRASTER_ADAPT WINAPI _CreateRasterAdaptInstance(MSRSDatasetH hImg);
void WINAPI _ReleaseRasterAdaptInstance(LPRASTER_ADAPT pRasObjAdpt);

// 更新缓冲
long WINAPI _FlushInstance(LPRASTER_ADAPT pRasObjAdpt);

// 得到内部数据集句柄
MSRSDatasetH WINAPI _GetDatasetHandle(LPRASTER_ADAPT pRasObjAdpt);

// 金子塔操作
long WINAPI v7x_rsOpenPyramidLayer(LPRASTER_ADAPT pRasObjAdpt, short PyLayerNo);
long WINAPI v7x_rsClosePyramidLayer(LPRASTER_ADAPT pRasOBJ);

//===================================================================
// 以下操作需要打开金字塔
//===================================================================

// 读写操作
long WINAPI v7x_rsSetCell(LPRASTER_ADAPT pRasOBJ, short BandNo, long RowNo, long ColNo, double Value);
long WINAPI v7x_rsGetCell(LPRASTER_ADAPT pRasOBJ, short BandNo, long RowNo, long ColNo, double &Value, char *pInvalidFlag=NULL);


#endif // __V7X_RASTERIOADAPTER_H__