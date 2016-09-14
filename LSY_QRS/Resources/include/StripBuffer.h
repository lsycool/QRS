/********************************************************************
	created:	2008/05/29
	created:	29:5:2008   10:41
	filename: 	e:\work\MapGIS71\RSPSRC\RASTERBASE\RasterIOAdapter\StripBuffer.h
	file path:	e:\work\MapGIS71\RSPSRC\RASTERBASE\RasterIOAdapter
	file base:	StripBuffer
	file ext:	h
	author:		Alpha
	
	purpose:	
*********************************************************************/

#pragma once
#include "RasterIO.h"
using namespace RASTER_IO;
//Linux-2010.4.14
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))

//////////////////////////////////////////////////////////////////////////
// Definition of CMsStripBuffer
//////////////////////////////////////////////////////////////////////////

#define BUFFER_MODE_STRIP   (1)
#define BUFFER_MODE_BLOCK   (2)

#define STRIP_TILE_HEIGHT   (32)
#define STRIP_TILE_WIDTH    (32)

#define BLOCK_TILE_HEIGHT   (512)
#define BLOCK_TILE_WIDTH    (512)
#define BLOCK_TILE_NUM      (8)

union PixValPtr
{
    unsigned  char      *pByte;
	signed	char	*pSChar;

    unsigned  short     *pUInt16;

    signed    short     *pInt16;

    unsigned __int32    *pUInt32;

    signed   __int32    *pInt32;	

    float   *pIEEE32;

    double  *pIEEE64;
};


#define BUFFER_TILE_FAULT   (-1) 

/**
 *	缓冲读写器
 *
 *  @note
 *
 *  1 数据块号 --  将影像等间距划分为格网, 每一格网为一个数据块. 数据块号就是按照先
 *                  列后行的规则, 以影像左上角开始, 对每一数据块进行的编号. 知道某一
 *                  像素的行列值可以快速定位它所在的数据块
 *
 *  2 缓冲块号 --  缓冲区中某一块数据的索引号. 
 *
 *  3 数据读取规则 -- 根据像素的行列值(c, r), 得到其所在的数据块号TileNo;
 *                      在缓冲区中查找此数据块号是否已经缓存;
 *                      (1) 如果已缓存, 得到其所在的缓冲块号CacheNo;
 *                      (2) 如果没有缓冲, 根据淘汰策略, 替换缓冲中的数据, 并得到替换后
 *                          的缓冲块号, 被替换的数据回写.
 *                      根据像素的块内偏移, 得到像元值.
 *
 *  4 数据写入规则 -- 根据像素的行列值(c, r), 得到其所在的数据块号TileNo;
 *                      在缓冲区中查找此数据块号是否已经缓存;
 *                      (1) 如果已缓存, 得到其所在的缓冲块号CacheNo;
 *                      (2) 如果没有缓冲, 根据淘汰策略, 替换缓冲中的数据, 并得到替换后
 *                          的缓冲块号, 被替换的数据回写.
 *                      根据像素的块内偏移, 将像元值写入缓存
 */

class CMsStripBuffer
{
public:
	CMsStripBuffer();
	~CMsStripBuffer();

	void	SetCacheMax(long lTileTotalNums);

	long	AddOneTileData(long TileNo);

	void	InitDataset(MSRSDatasetH hDS,long lBandNo);

	void	SetPyraLayerNo(long lPyraNo);

	bool	InitBuffer(MSRSDatasetH	hDS, int nBufMode);

	bool	LoadInitData(long lInitCol, long lBandNo);

	long    GetOneCellFromBuffer(const long &lCol, const long &lRow, double &dVal);

	// 返回值：
	//  0 - hit
	//  1 - load
	//  2 - replaced
	// -1 - out of range
	long	SetOneCellToBuffer(const long &lCol, const long &lRow, const double &dVal);

	long	FlushAll();

    void    PrintStatus();

protected:

    long	FlushOneTile(long lBfIdx);
    void ReadFromCache(const int &lCol, const int &lRow, int &lCacheIdx, int &lColInner, int &lRowInner, int &lActualWidth, int &lActualHeight);

public:

    //===================================================================
    // 影像信息
    //===================================================================

	MSRSDatasetH	m_pDataset;             // 缓冲的数据集句柄

    MSRSRasterBandH	m_pBand;                // 缓冲的波段

    long			m_lCurBandNo;           // 当前缓冲的波段号

	long			m_lBitSize;             // 一个像元所占字节(BYTE)数目

    MSRSDataType	m_Datatype;             // 像元类型

    long			m_lLineCells;           // 影像列数

    long			m_lLines;               // 影像行数


    //===================================================================
    // 数据读取 
    //===================================================================

    long    		m_pAddTileNums;         // 已加载过的总块数

    long			m_lRowTileNums;         // 行向数据分块

    long			m_lColTileNums;         // 列向数据分块

	void*           m_pDataRead;           // 读缓冲

	void*           m_pDataWrite;          // 写缓冲

    //===================================================================
    // 缓存存储
    //===================================================================

    void*           m_pBuffer;              // 全部的缓冲数据

    PixValPtr       m_pWrite, m_pRead;

    long            m_lMaxTileCached;       // 缓冲区中数据块的上限 

    long			m_lTileTotalNums;       // 缓冲区中已分配的数据块数

    long			m_TileHeight;           // 缓冲数据块的高度(Y方向)

    long			m_TileWidth;            // 缓冲数据块的宽度(X方向)

    long			m_lTileSize;            // 数据块大小(像元个数)

    int             m_nBufMode;             // 缓冲模式

    int             m_nWLog2;

    int             m_nHLog2;

    int             m_nWMask;

    int             m_nHMask;

    //===================================================================
    // 缓存查询
    //===================================================================

    long			m_lCurTileNo;           // 当前操作的数据块号

    long			m_lCurTileNums;         // 当前操作的缓冲块号

    long*           m_lTileNoArray;         // 索引数组. 缓冲块号对应的数据块号

    int*            m_cachedTile2Index;     // 数据块号到缓冲块号的映射

    //===================================================================
    // 缓存淘汰
    //===================================================================

    long			m_lFIFOIdx;          // 淘汰的缓冲块号

    bool*			m_pIsDirty;             // 是否回写的标志位. 如果是标志位为"脏", 回写



public:
    
    // 缓冲使用统计

	long _cache_hit_count;

	long _cache_load_count;

	long _cache_replace_count;
};

typedef CMsStripBuffer* STRIPBUF;

//////////////////////////////////////////////////////////////////////////
// Strip Buffer API
//////////////////////////////////////////////////////////////////////////

inline bool msAllocStripBuffer(STRIPBUF *pStripBuf)
{
    *pStripBuf=new CMsStripBuffer;
    if (NULL==pStripBuf)
        return false;
    else 
        return true;
}

inline void msFreeStripBuffer(STRIPBUF pStripBuf)
{
    if(pStripBuf) delete pStripBuf;	pStripBuf=NULL;
}

inline bool msInitStripBuffer(STRIPBUF pStripBuf,MSRSDatasetH hDS,int nBufMode)
{
    if(pStripBuf)
        return pStripBuf->InitBuffer(hDS, nBufMode);
    else
        return false;
}

inline bool msStripLoadInitData(STRIPBUF pStripBuf,long lInitCol,long lBandNo)
{
    if(pStripBuf)
        return pStripBuf->LoadInitData(lInitCol,lBandNo);
    else
        return false;
}

inline bool msStripGetOneCell(STRIPBUF pStripBuf,long lLineNo,long lLineCellNo,bool bFlag,double *dValue)
{
    if(pStripBuf)
    {
        pStripBuf->GetOneCellFromBuffer(lLineCellNo, lLineNo, *dValue);
        return true;
    }
    else
        return false;
}

inline bool msStripSetOneCell(STRIPBUF pStripBuf, long lLineNo, long lLineCellNo, double dValue)
{
    if (pStripBuf)
    {
        if (0 > pStripBuf->SetOneCellToBuffer(lLineCellNo, lLineNo, dValue))
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}

inline bool msFlushAllStripBuffer(STRIPBUF pStripBuf)
{
    if (pStripBuf)
    {
        if (pStripBuf->FlushAll())
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}

