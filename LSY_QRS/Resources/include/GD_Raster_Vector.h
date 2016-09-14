#ifndef _GD_RASTER_VECTOR_H_     // prevent multiple includes.
#define _GD_RASTER_VECTOR_H_

//#include "RasBase.h"
//#include <msRSDataIOApi.h>
#include "RasterIO.h"
using namespace RASTER_IO;

#ifndef __GD_RASTER_VECTOR_EXPORTS__
#define gdvecDll __declspec(dllimport)
#else
#define gdvecDll __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif


//===================================դ��תʸ��=====================================

//դ��תʸ���ӿ�(ֱ�Ӹ���դ�����)
//�������:
//hRaster                ��ת��Ӱͨ�����ݼ����(֧��RAS_1BIT,RAS_UINT8,RAS_UINT16).
//BandNo                 ��ת��Ӱ�񲨶κ�(��1��ʼ).
//lMaxCellNumOfSmallReg  �ϲ�С��������Ԫ��,<1��ʾ������С���ϲ�����.
//bMakeTopo              �Ƿ��������� 
//dTolerence             �����ؽ�ƽ��뾶
//�������:
//strReOutType           ���Ӱ���ʽ��(���)
//pReRasGDB              ���Ӱ�����ڵ������ݿ����(����ΪNULL).
//pReRasName             ���Ӱ�����ݼ���(����ΪNULL).
//pOutGDB                �����Ҫ�������ڵ������ݿ����.
//pFClsName              �����Ҫ������.
//����ֵ:                0/1--�ɹ�/ʧ��
long gdvecDll msRSRaster2FCls(MSRSDatasetH hRaster, 
                              short BandNo,
                              /*CGDataBase *pReRasGDB,*/
							  const char *strReOutType,
                              const char *pReRasName,
                              /*CGDataBase *pOutGDB, */
                              const char *pFClsName,
                              long lMaxCellNumOfSmallReg=0,
                              BOOL bMakeTopo=FALSE,
							  double dTolerence=0.0001);

//դ��תʸ���ӿ�(ֱ�Ӹ���դ�����)
//�������:
//hRaster                ��ת��Ӱͨ�����ݼ����(֧��RAS_1BIT,RAS_UINT8,RAS_UINT16).
//BandNo                 ��ת��Ӱ�񲨶κ�(��1��ʼ).
//lMaxCellNumOfSmallReg  �ϲ�С��������Ԫ��,<1��ʾ������С���ϲ�����.
//bMakeTopo              �Ƿ��������� 
//dTolerence             �����ؽ�ƽ��뾶
//�������:
//strReOutType           ���Ӱ���ʽ��(���)
//pReRasGDB              ���Ӱ�����ڵ������ݿ����(����ΪNULL).
//pReRasName             ���Ӱ�����ݼ���(����ΪNULL).
//pOutGDB                �����Ҫ�������ڵ������ݿ����.
//pFClsName              �������Ҫ������.
//����ֵ:                0/1--�ɹ�/ʧ��
long gdvecDll msRSRaster2SFCls(MSRSDatasetH hRaster, 
							  short BandNo,
							  /*CGDataBase *pReRasGDB,*/
							  const char *strReOutType,
							  const char *pReRasName,
							  /*CGDataBase *pOutGDB, */
							  const char *pFClsName,
							  long lMaxCellNumOfSmallReg=0,
							  BOOL bMakeTopo=FALSE,
							  double dTolerence=0.0001);

//С���ϲ�
//�������:
//hRaster                ��ת��Ӱͨ�����ݼ����(֧��RAS_1BIT,RAS_UINT8,RAS_UINT16).
//BandNo                 ��ת��Ӱ�񲨶κ�(��1��ʼ).
//strReOutType           ���Ӱ���ʽ��
//pReRasGDB              ���Ӱ�����ڵ������ݿ����(����ΪNULL).
//pReRasName             ���Ӱ�����ݼ���(����ΪNULL).
//lMaxCellNumOfSmallReg  �ϲ�С��������Ԫ��,<1��ʾ������С���ϲ�����.
//����ֵ                 0/1--�ɹ�/ʧ��
//long gdvecDll msRSMergeRasterSmallRegion(MSRSDatasetH hRaster, short BandNo,
//	                                   CGDataBase *pReRasGDB, const char *strReOutType,
//									   const char *pReRasName,long lMaxCellNumOfSmallReg);

//===================================================================================

//===================================Ӱ��ü�=======================================

//����βü�ͨ��Ӱ��
//hDS				����Ӱ�����ݼ�����
//pPolySet			�ü����������(��Ȧ).
//pLenSet			ÿȦ��������.
//SetNum			�ü�����ε�Ȧ��.
//ReserveMode		1/2/else,����ͼ�ε�/���ĵ�/�߽�ȫ·��.
//CoordSysType		��������(ͼ������/ͼ������).
//bAddClipRangeAsAoi�Ƿ񽫲ü��������ΪAOI��ӵ����Ӱ��
//�������:
//pOutGDB			����������ݿ����.
//pOutImageName		���Ӱ��ȫ·����.
//strOutDriver      ���Ӱ������
//strFrameName      ��ͼ���ü���ͼ����
//pProcBandList     ѡ��Ĳü����κ����飬���Ҫ������Ӱ��ü���NULL
//lProcBandNum      pProcBandList�ĳ���
//����ֵ:           0/1,�ɹ�/ʧ��.
//ע����ΪReserveMode����º��壬���Ķ�������������λ��������ͼ�ε�/���ĵ�/�߽�ȫ·�����ĺ��壬
//���Ķ�������ĵ�������λ��ʾ�ڲú���� add by wangbo
//0000 0100 ��ã�0000 00000�ڲ�
//0000 0001 ����ͼ�ε㣻0000 0010 ���ĵ㣻�����������ȫ·��
//0000 0101 ����ұ���ͼ�ε�
short gdvecDll msRSClipImage(MSRSDatasetH hDS,
							 D_DOT *pPolySet, long *pLenSet, long SetNum,
							 BYTE  ReserveMode,
							 RAS_COORDSYSTYPE CoordSysType,
							 BOOL bAddClipRangeAsAoi,
							 /*CGDataBase *pOutGDB,*/ const char *pOutImageName,
							 const char *strOutDriver,const char *strFrameName=_T(""),
							 long *pProcBandList=NULL,long *lProcBandNum=NULL);

//Ӱ���ڲ�AOI�ü�ͨ��Ӱ��
//hDS			��������Ӱ�����ݼ�����.
//ReserveMode		1/2/else,����ͼ�ε�/���ĵ�/�߽�ȫ·��.
//CoordSysType		��������(ͼ������/ͼ������).
//bMultiAoiClip     TRUR����AOI�ü�����һ���Ӱ��FALSE-ÿ��AOI����һ���Ӱ��
//�������:
//pOutGDB			����������ݿ����.
//pOutImageName		���Ӱ��ȫ·����.
//strOutDriver      ���Ӱ������
//pProcBandList     ѡ��Ĳü����κ����飬���Ҫ������Ӱ��ü���NULL
//lProcBandNum      pProcBandList�ĳ���
//����ֵ:           0/1,�ɹ�/ʧ��.
short gdvecDll msRSClipImgByAOI(MSRSDatasetH hDS,BYTE  ReserveMode, RAS_COORDSYSTYPE CoordSysTypelong ,BOOL bMultiAoiClip,
	                            /*CGDataBase *pOutGDB,*/const char *pOutImageName,const char *strOutDriver,long *pProcBandList=NULL,long *lProcBandNum=NULL);

//��Ҫ����ü�Ӱ��
//hDS			��������Ӱ�����ݼ�����.
//CFeatureCls &ClipFeature  �ü�����Ҫ����
//ReserveMode		1/2/else,����ͼ�ε�/���ĵ�/�߽�ȫ·��.
//CoordSysType		��������(ͼ������/ͼ������)��ע����ü���Ҫ�������������һ��.
//plRegIDArr        Ҫ�����е���Ҫ�ص�ID����---�˴���ΪNULL,ΪNull��ʾҪ������������������ü�
//ClipRegNum        ����ü���Ҫ��������Ҫ�صĸ���
//bMultiPolygonClip TRUR�������еĲü���Ҫ������һ���Ӱ��FALSE-ÿ���ü���Ҫ������һ���Ӱ��
//�������:
//pOutGDB			����������ݿ����.
//pOutImageName		���Ӱ��ȫ·����.
//szFormat          ���Ӱ������
//pProcBandList     ѡ��Ĳü����κ����飬���Ҫ������Ӱ��ü���NULL
//lProcBandNum      pProcBandList�ĳ���
//����ֵ:           0/1,�ɹ�/ʧ��.
//˵����CoordSysType��ü���Ҫ������������ͱ���һ�£������㷨�������ѭ������psq 08.07.08
short gdvecDll msRSClipImgByFeature(MSRSDatasetH hDS,/*CFeatureCls &ClipFeature,*/BYTE  ReserveMode,RAS_COORDSYSTYPE CoordSysType,
	                                long* plRegIDArr,long ClipRegNum,BOOL bMultiPolygonClip,/*CGDataBase *pOutGDB,*/
	                                const char *pOutImageName,const char *szFormat,long *pProcBandList=NULL,long *lProcBandNum=NULL);

//����Ҫ����ü�Ӱ��
//hDS			��������Ӱ�����ݼ�����.
//ClipSFeature      �ü��ļ���Ҫ����
//ReserveMode		1/2/else,����ͼ�ε�/���ĵ�/�߽�ȫ·��.
//CoordSysType		��������(ͼ������/ͼ������)��ע����ü���Ҫ�������������һ��.
//plRegIDArr        Ҫ�����е���Ҫ�ص�ID����---�˴���ΪNULL,ΪNull��ʾҪ������������������ü�
//ClipRegNum        ����ü���Ҫ��������Ҫ�صĸ���
//bMultiPolygonClip TRUR�������еĲü���Ҫ������һ���Ӱ��FALSE-ÿ���ü���Ҫ������һ���Ӱ��
//�������:
//pOutGDB			����������ݿ����.
//pOutImageName		���Ӱ��ȫ·����.
//szFormat          ���Ӱ������
//pProcBandList     ѡ��Ĳü����κ����飬���Ҫ������Ӱ��ü���NULL
//lProcBandNum      pProcBandList�ĳ���
//����ֵ:           0/1,�ɹ�/ʧ��.
//˵����CoordSysType��ü���Ҫ������������ͱ���һ�£������㷨�������ѭ��
short gdvecDll msRSClipImgBySFeature(MSRSDatasetH hDS,/*CSFeatureCls &ClipSFeature,*/BYTE  ReserveMode,RAS_COORDSYSTYPE CoordSysType,
									long* plRegIDArr,long ClipRegNum,BOOL bMultiPolygonClip,/*CGDataBase *pOutGDB,*/
									const char *pOutImageName,const char *szFormat,long *pProcBandList=NULL,long *lProcBandNum=NULL);


//---------------------------------------------------------------------//
// �ɹ�����0��ʧ�ܷ��ش�����(��mserrors.h) Created by zyk
// hSrcDS,plSrcBandNo,lSrcBandNum	[in]--����Ӱ�����ݼ�,���κ�,������
// pcClipScls,plObjID,lObjNum		[in]--�ü�Ҫ����,ѡ����OID,ѡ��������(plObjID==NULLʱ������ʸ�����Χ�ü�)
// pdClipDots,plDotNum,lDotRegNum	[in]--����Ȧ�㼯,��Ȧ�ĵ���,Ȧ��
// pszDstFile,lDstFileNum,pszDstFmt	[in]--���Ӱ��������,���Ӱ��������(�ü����),���Ӱ���ʽ(GTiff)
// pDstGdb,bMulClip					[in]--����������ݿ�,true/false--ÿ������һ��Ӱ��/����һ��Ӱ��
// lClipType,bGeoRange				[in]--0/1/2/3--��Ԫ���Ͻ�/����/����/ȫ�������ڻᱣ��,true/false--����Χ/���з�Χ
// pszSubProg						[in]--�������ӱ���(�����⡰Ӱ��ü�...��,��NULL�����н�����)
//---------------------------------------------------------------------//
// ��Ҫ����ü�
long gdvecDll msRSClipImgByScls(MSRSDatasetH hSrcDS, long *plSrcBandNo, long lSrcBandNum,/* CSFeatureCls *pcClipScls,*/ long *plObjID,
								long lObjNum, const char *pszDstFile, const char *pszDstFmt, void *pDstGdb=NULL,
								long lClipType=2, bool bGeoRange=true, const char *pszSubProg=NULL);

// �㼯�ü�
long gdvecDll msRSClipImgByDot(MSRSDatasetH hSrcDS, long *plSrcBandNo, long lSrcBandNum, D_DOT *pdClipDots, long *plDotNum, 
							   long lDotRegNum, const char *pszDstFile, const char *pszDstFmt, void *pDstGdb=NULL,
							   long lClipType=2, bool bGeoRange=true, const char *pszSubProg=NULL);

//===================================================================================

//////////////////////////////////////////////////////////////////////////
// ���ܣ�����Ӱ��Ĳü�AOI, �����Ի������ò���
// ���������
//	MSRSDatasetH hDataset -- ����Ӱ����
// ����ֵ��long 0/Success�� ����/������
long gdvecDll msRsAppendRasClipAoiByDlg(MSRSDatasetH hDataset);

//////////////////////////////////////////////////////////////////////////
// ���ܣ�����Ӱ��Ĳü�AOI, ָ����Чֵ���䣬��4�ǵ�/�߽�׷��2������
// ע�⣺�˽ӿ����67�ӿڹ��������仯��(1)������Ч��ֻ��һ�����ν���
//		(2)��Чֵ��һ�����Σ�������ǰ��һ��ֵ
// ���������
//	MSRSDatasetH hDataset -- ����Ӱ����
//	long lBandNo -- ����������Ч���Ĳ���ID����1��ʼ
//	double dExcludeMinVal -- ��Чֵ�ķ�Χ[MinVal, MaxVal]
//	double dExcludeMaxVal -- ��Чֵ��Χ�Ǳ�����
//	long lSrchType -- 0/�ǵ�ģʽ 1/�߽�ģʽ���߽�ģʽ��ʱ����׼ȷ
// ����ֵ��long 0/Success�� ����/������
long gdvecDll msRsAppendRasClipAoi(MSRSDatasetH hDataset, long lBandNo, double dExcludeMinVal, double dExcludeMaxVal, long lSrchType);

#ifdef __cplusplus
}
#endif

//#ifndef __GD_RASTER_VECTOR_EXPORTS__
//#pragma comment(lib, "W70_VRTr.lib")
//#endif	

#endif
