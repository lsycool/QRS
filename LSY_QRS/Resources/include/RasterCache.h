//================================================================================
// 文件名		 ：RasterCache.h 
// 版本			 ：this 1.0.0 ; QGIS1.7.4 ;QT 4.7.1 ;GDAL 1.8.1                            
// 目的及主要功能：影像IO缓存类
// 创建日期		 ：2012.05.30
// 最后修改日期  ：2012.05.30 
// 作者			 ：yq
// 修改者		 ：yq
// 描述			 ：波段号从1开始；
//				 : 目前只能做一个波段的缓存
//				 ：整型返回值为CPLErr；成功/失败 0/错误代码
//================================================================================


#ifndef RASTER_CACHE_H
#define RASTER_CACHE_H
#include "gdal.h"
#include "gdal_priv.h"


/************************************************************************/
/*名称：栅格缓存类,只能对一个波段进行缓存
/*原理：每一个影像块的大小相同
/*		所有影像块使用同一缓存内存,该内存必须小于“影像块最大允许分配内存”（有缓冲区情况除外）；
/*		存在缓冲区时，影像块的缓存之间会存在重叠，缓冲区只会向下（行值增大的方向）扩张；最后一个块没有缓冲区。
/*		！！！！！！！！！！缓存的大小 不一定等于 影像块的大小！！！！！！！！！！！关系如下：
/*		缓存的内存 = 影像块占用的内存 + 缓冲区占用的内存 + 边界处多余内存（只能存在最后一块）
/*		每次次开始操作一个新影像块时，会自动把上一块缓存数据写入磁盘；
/*		类会对影像块使用的内存进行自动管理，不需要调用者来操心；
/*注意：要达到高效读写，最好是 完全 处理好一块影像块的数据后，再处理其他影像块的数据，
/*		否则会出现频繁的读写。
/*
/*
/*
/************************************************************************/


class CRasterCache
{
public:
	//计算影像块大小，并分配内存
	//lBandNo 从1开始
	//lMaxBlockSize 影像块最大允许分配内存（包括缓冲区要分配的内存，因此必须大于 “影像列数*(1+lBufferSize)”)。
	//				分配有错则会根据系统默认的“最大可分配内存”自动调整该值;最大2GB内存
	//lBufferSize  缓冲区的行列数，一般情况把影像块向四方向扩张lBufferLines行或列，(可以理解为块与块之间的重叠区)
	//				因此lBufferLines大于0时，影像块的缓存之间会存在重叠。
	//该构造函数中，影像块分配会以行优先，会尽可能把影像块填满一行
	CRasterCache(GDALDatasetH hSrcDS,long lBandNo,long lMaxBlockSize=0,long lBufferSize=0);
	//lXBlockSize	x方向块的大小，必须大于0，小于等于影像宽，为0时默认为影像宽
	//lYBlockSize	y方向块的大小，必须大于0，小于等于影像高，为0时默认为影像高
	//lXBlockSize 和 lYBlockSize都为0时，为整幅影像的指定波段全部分配缓存
	CRasterCache(long lBandNo,GDALDatasetH hSrcDS,long lXBlockSize=0,long lYBlockSize=0,long lBufferSize=0);


	//释放内存
	~CRasterCache();

	//根据行列值读栅格值，
	//行列值超出当前影像块时，会将上个影像块数据写入磁盘，并将当前影像块数据读入缓冲区
	long	GetCellValue(long lRowNo,long lColNo,double &dfValue);

	//根据行列值写栅格值
	//一般不会写入磁盘，除非开始操作另外一个影像块
	long	SetCellValue(long lRowNo,long lColNo,double dfValue);

	//将缓存的数据写入磁盘
	long	FlushCache();

	//是否已经成功初始化
	bool	IsInitialed();

	//释放缓存
	bool	ReleaseCache();

	//是否只存在一个块
	bool	IsOnlyOneBlock();

private:
	//根据行列号，更新当前块的缓存区
	long	UpdateCurBlockCache(long lRowNo,long lColNo);

private:
	//////////////////////////////////////////////////////////////////////////
	GDALDatasetH m_hSrcDS;//原始影像的数据集句柄
	//double		 m_dbNoDataValue;//无效值
	bool	m_bIsOnlyOneBlock;//是否整幅影像只为一个块

	long	m_lMaxBlockSize;//最大缓存的大小（字节）

	long	m_lXBuffer;//缓冲区的列数
	long	m_lYBuffer;//缓冲区的行数

	long	m_lXBlockCount;//x方向影像块的数量
	long	m_lYBlockCount;//y方向影像块的数量

	long	m_lXBlockSize;//x方向影像块的大小，不把缓冲区的大小考虑在内
	long	m_lYBlockSize;//y方向影像块的大小，不把缓冲区的大小考虑在内

	char*	m_pCacheData;//缓存的起始指针；
						  //作为一个二维数组考虑；在边界位置时，注意缓冲区不存在情况
						  //影像数据始终从 （0,0）开始存放，便于RasterIO处理
	long	m_lCacheSize; //实际缓存的大小，为缓存的“宽*高”
	long	m_lCacheMemSize;//实际缓存的内存大小（字节）
	bool	m_bIsCurCacheFlushed;//当前缓存是否已经写入影像

	long	m_lImgWidth;//原始影像宽（列数）
	long	m_lImgHeight;//原始影像高（行数）

	GDALDataType  m_eDataType;//波段的数据类型
	
	GDALRasterBand	*m_poBand;//
	GDALDataset *m_poDatase;
	//////////////////////////////////////////////////////////////////////////
	long	m_lCurBlockXIndex;//当前影像块x方向位置，从0开始
	long	m_lCurBlockYIndex;//当前影像块y方向位置，从0开始

	//当前影像块缓存对应在影像上的范围，因此取值在影像的行列值内
	//计算时包括缓冲区；边界处没有缓冲区
	//实际上包含了当前缓存坐标到影像坐标的转换关系
	long	m_lCurCacheXMin;//当前缓存对应影像上的最小列值
	long	m_lCurCacheXMax;//当前缓存对应影像上的最大列值
	long	m_lCurCacheYMin;//当前缓存对应影像上的最小行值
	long	m_lCurCacheYMax;//当前缓存对应影像上的最大行值


	long	m_lErrorCode;//错误代码

};


#endif