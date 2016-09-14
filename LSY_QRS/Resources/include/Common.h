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

//  功能描述：设置图像图形范围
void SetControlPnts(MSRSDatasetH  pOutRsDs, DemInfoStrcT *pDemInfo);

//打开临时数据库.
//short OpenRasterTempGDB(TempGDBInfoStrcT *pTempGDBInfo);

//关闭临时数据库.
//short CloseRasterTempGDB(TempGDBInfoStrcT *pTempGDBInfo);

//取字符串内容.
short GetString(UINT nIDPrompt, CString &Prompt);

void Frame_MessagePrompt(UINT nIDPrompt);

int Frame_SelectMessagePrompt(UINT nIDPrompt);

//创建并附加一个数据库到本地服务器
//在progam目录下，名字：RasTempDB.HDF
//BOOL CreateDBToMapGISLocal(BOOL& bExist);

//void DetachRasTmepDB();

//CGDataBase* GetRasTempDB();

//void FreeRasTempDB(CGDataBase* pTempGDB);

//为简单要素类添加缓存
//BOOL CreateCacheToSFCls(CSFeatureCls *SFCls);

#endif