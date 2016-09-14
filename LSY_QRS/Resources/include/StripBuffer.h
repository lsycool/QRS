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
 *	�����д��
 *
 *  @note
 *
 *  1 ���ݿ�� --  ��Ӱ��ȼ�໮��Ϊ����, ÿһ����Ϊһ�����ݿ�. ���ݿ�ž��ǰ�����
 *                  �к��еĹ���, ��Ӱ�����Ͻǿ�ʼ, ��ÿһ���ݿ���еı��. ֪��ĳһ
 *                  ���ص�����ֵ���Կ��ٶ�λ�����ڵ����ݿ�
 *
 *  2 ������ --  ��������ĳһ�����ݵ�������. 
 *
 *  3 ���ݶ�ȡ���� -- �������ص�����ֵ(c, r), �õ������ڵ����ݿ��TileNo;
 *                      �ڻ������в��Ҵ����ݿ���Ƿ��Ѿ�����;
 *                      (1) ����ѻ���, �õ������ڵĻ�����CacheNo;
 *                      (2) ���û�л���, ������̭����, �滻�����е�����, ���õ��滻��
 *                          �Ļ�����, ���滻�����ݻ�д.
 *                      �������صĿ���ƫ��, �õ���Ԫֵ.
 *
 *  4 ����д����� -- �������ص�����ֵ(c, r), �õ������ڵ����ݿ��TileNo;
 *                      �ڻ������в��Ҵ����ݿ���Ƿ��Ѿ�����;
 *                      (1) ����ѻ���, �õ������ڵĻ�����CacheNo;
 *                      (2) ���û�л���, ������̭����, �滻�����е�����, ���õ��滻��
 *                          �Ļ�����, ���滻�����ݻ�д.
 *                      �������صĿ���ƫ��, ����Ԫֵд�뻺��
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

	// ����ֵ��
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
    // Ӱ����Ϣ
    //===================================================================

	MSRSDatasetH	m_pDataset;             // ��������ݼ����

    MSRSRasterBandH	m_pBand;                // ����Ĳ���

    long			m_lCurBandNo;           // ��ǰ����Ĳ��κ�

	long			m_lBitSize;             // һ����Ԫ��ռ�ֽ�(BYTE)��Ŀ

    MSRSDataType	m_Datatype;             // ��Ԫ����

    long			m_lLineCells;           // Ӱ������

    long			m_lLines;               // Ӱ������


    //===================================================================
    // ���ݶ�ȡ 
    //===================================================================

    long    		m_pAddTileNums;         // �Ѽ��ع����ܿ���

    long			m_lRowTileNums;         // �������ݷֿ�

    long			m_lColTileNums;         // �������ݷֿ�

	void*           m_pDataRead;           // ������

	void*           m_pDataWrite;          // д����

    //===================================================================
    // ����洢
    //===================================================================

    void*           m_pBuffer;              // ȫ���Ļ�������

    PixValPtr       m_pWrite, m_pRead;

    long            m_lMaxTileCached;       // �����������ݿ������ 

    long			m_lTileTotalNums;       // ���������ѷ�������ݿ���

    long			m_TileHeight;           // �������ݿ�ĸ߶�(Y����)

    long			m_TileWidth;            // �������ݿ�Ŀ��(X����)

    long			m_lTileSize;            // ���ݿ��С(��Ԫ����)

    int             m_nBufMode;             // ����ģʽ

    int             m_nWLog2;

    int             m_nHLog2;

    int             m_nWMask;

    int             m_nHMask;

    //===================================================================
    // �����ѯ
    //===================================================================

    long			m_lCurTileNo;           // ��ǰ���������ݿ��

    long			m_lCurTileNums;         // ��ǰ�����Ļ�����

    long*           m_lTileNoArray;         // ��������. �����Ŷ�Ӧ�����ݿ��

    int*            m_cachedTile2Index;     // ���ݿ�ŵ������ŵ�ӳ��

    //===================================================================
    // ������̭
    //===================================================================

    long			m_lFIFOIdx;          // ��̭�Ļ�����

    bool*			m_pIsDirty;             // �Ƿ��д�ı�־λ. ����Ǳ�־λΪ"��", ��д



public:
    
    // ����ʹ��ͳ��

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

