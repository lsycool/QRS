#ifndef _COMMON_H_
#define _COMMON_H_

#include "msOOdef.h"
#include "RasterIO.h"
using namespace RASTER_IO;
//#include "cln_bas70.h"
//#include "DTMBase_RasFunc.h"

//struct TempGDBInfoStrcT
//{
//	CGDBServer  *pServer;
//	CGDataBase  *pGDB;
//	
//	TempGDBInfoStrcT()
//	{
//		pServer=NULL;
//		pGDB=NULL;
//	}
//};

/////////////////////////////////////////////////////////////////////////////

//  ��������������ͼ��ͼ�η�Χ
void SetControlPnts(MSRSDatasetH  pOutRsDs, DemInfoStrcT *pDemInfo);

//����ʱ���ݿ�.
//short OpenRasterTempGDB(TempGDBInfoStrcT *pTempGDBInfo);

//�ر���ʱ���ݿ�.
//short CloseRasterTempGDB(TempGDBInfoStrcT *pTempGDBInfo);

//ȡ�ַ�������.
short GetString(UINT nIDPrompt, CString &Prompt);

void Frame_MessagePrompt(UINT nIDPrompt);

int Frame_SelectMessagePrompt(UINT nIDPrompt);

//����������һ�����ݿ⵽���ط�����
//��progamĿ¼�£����֣�RasTempDB.HDF
//BOOL CreateDBToMapGISLocal(BOOL& bExist);

//void DetachRasTmepDB();

//CGDataBase* GetRasTempDB();

//void FreeRasTempDB(CGDataBase* pTempGDB);

//Ϊ��Ҫ������ӻ���
//BOOL CreateCacheToSFCls(CSFeatureCls *SFCls);

#endif