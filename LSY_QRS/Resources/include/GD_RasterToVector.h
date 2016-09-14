 #ifndef _GD_RASTER_TO_VECTOR_H_
#define _GD_RASTER_TO_VECTOR_H_

#include "myarry.h"		//动态顺序内存
#include "Common.h"
//#include "V7XAdapter.h"
#include "V7X_RasterIOAdapter.h"
#include "MSSFunction.h"
#include "ogr_geometry.h "	
#include "ogr_feature.h "	
#include "ogrsf_frmts.h "
#include <vector>
using std::vector;

namespace GDX
{

//利用宏来简化数据的声明
#define LPRCLINA CMyArray<M_RclLinA>*	//行程线段动态内存
#define LPREG	 CMyArray<M_Reg>*		//区数据动态内存

//内存处理中所用到的一些宏
#define MAX_LINASTEP	50000          //行程线段内存的最大增长步长
#define MAX_REGSTEP		1000		   //区数据内存最大增长步长
#define INIT_LINAMUTI   5			   //初始化线段内存，行数*INIT_LINAMUTI
#define INIT_REGMULTI	50			   //初始化区内存，线段数/INIT_REGMULTI

//自己定义的一些异常宏
#define OPEN_MSI_ERR	100			//打开图象文件错误
#define COPY_MSI_ERR    101			//复制图象文件错误
#define READ_LINE_ERR   102			//读取图象行信息错误
#define READ_COL_ERR	103         //读取图象列信息错误
#define NOTMSI_ERR		104			//图象文件不存在
#define NEW_REG_ERR     105			//新建区工作区失败
#define TRANS_ERR		106			//分配转换结构失败
#define BANDS_ERR       107         //图象的波段数超出范围
#define CELL_ERR        108			//象元类型错误
#define REGAI_TYPE_ERR  109			//传递进来的区工作区类型错误
#define ALLOC_MEM_ERR   110         //内存分配错误

typedef struct CLASSATTINFO MSCLASSATTINFO;

//用到的数据结构，对原来的数据结构做出扩充与修改
typedef	struct 						//线段文件单元
{
    //unsigned short  wCla;				//灰度(原来是1字节)
    //unsigned char	  byDel;			//删除标记
    //unsigned short  wLine;			//行号(最大支持65536)
    //unsigned short  wFrom,wTo;		//起止点
    //long			  lRegNo;			//该线段所属的区在区文件中序号

	//wyz-2012.6.18修改原因：扩充支持的数据类型，目前超过65535有问题
	unsigned long  wCla;				//灰度(原来是1字节)
	unsigned char	  byDel;			//删除标记
	unsigned long  wLine;			//行号(最大支持65536)
	unsigned long  wFrom,wTo;		//起止点
	long			  lRegNo;			//该线段所属的区在区文件中序号
} M_RclLinA;//21字节

typedef	struct 						//面积文件单元
{
    //unsigned short  wCla;				//灰度(原来是1个字节)
    //unsigned char	  byDel;			//删除标记
    //long			  lTotalNum;		//本区的面积
    //long			  lRclLinNo;		//构成本区的线段在线段文件中的地址
    //long            lRclLinNum;		//构成本区的线段总数
    //long			  lBiggestMateReg;	//与本区紧邻且最大的区

	//wyz-2012.6.18修改原因：扩充支持的数据类型，目前超过65535有问题
	unsigned long  wCla;				//灰度(原来是1个字节)
	unsigned char	  byDel;			//删除标记
	long			  lTotalNum;		//本区的面积
	long			  lRclLinNo;		//构成本区的线段在线段文件中的地址
	long            lRclLinNum;		//构成本区的线段总数
	long			  lBiggestMateReg;	//与本区紧邻且最大的区
} M_Reg;//35字节

typedef	struct 						//行程码文件单元 
{ 
    //unsigned short  wCla;				//灰度
    //unsigned short  wLine;			//行
    //unsigned short  wFrom,wTo;		//起止点

	//wyz-2012.6.18修改原因：扩充支持的数据类型，目前超过65535有问题
	unsigned long  wCla;				//灰度
	unsigned long  wLine;			//行
	unsigned long  wFrom,wTo;		//起止点
} M_RclLin;//12字节

//标志==0表示相应位置有栅格数据，所以若全部==0，则不是边界数据，至少有一个1才可能是
//边界数据，根据这个规则提取出边界栅格点
typedef struct
{
    //short		nX;
    //short		nY;			//格子坐标
    //BYTE       e0:2;		//左边格子
    //BYTE       e1:2;		//低一行扫描线
    //BYTE       e2:2;		//右边格子
    //BYTE       e3:2;		//高一行扫描线

	//wyz-2012.6.18修改原因：扩充支持的数据类型，目前超过65535有问题
	 long		nX;
	 long		nY;			//格子坐标
	BYTE       e0:2;		//左边格子
	BYTE       e1:2;		//低一行扫描线
	BYTE       e2:2;		//右边格子
	BYTE       e3:2;		//高一行扫描线
}MSI_POINT;

//边界点的保存坐标
typedef struct
{
    //short nX;
    //short nY;
    //BYTE  byNod;	//是否是结点 1/0 结点/拐点

	//wyz-2012.6.18修改原因：扩充支持的数据类型，目前超过65535有问题
	 long nX;
	 long nY;
	BYTE  byNod;	//是否是结点 1/0 结点/拐点
}EDGE_POINT;

typedef struct
{
	char   fieldname[MAX_FLD_NAME_LEN];	//字段名称
	int	   fieldtype;		//字段类型
	long   fieldoffset;		//字段偏移
	short  fieldlength;		//字段字节长度
	short  msk_leng;		//字段字符长度
	char   point_leng;		//小数位数
	short  edit_enable;		//编辑使能标志(0/1/2=不能/能/禁止)
	char   pt_flg;          //打印标志
	short  ptc_pos;		    //字段序号，依次为0,1,2...
	unsigned long wCla;		//灰度
	//设置属性结构时，老字段序号为原字段序号(>=0)，
	//    新字段序号必须为-1,设置属性结构之后，
	//    所有字段序号被重新排序，依次设置为0,1,2...

	char   isInherited;     //字段是否继承标志    2004-06-03
	// 1/0 - 继承父类的字段/自身的字段(仅用于有继承关系的子类中)
}CFIELD_HEAD;

typedef struct
{
//	short  	numbfield;    //字段数
	vector<CFIELD_HEAD>	STRU;//属性字段
}CATT_STRU;

typedef struct
{
//	short  	numbfield;    //字段数
	CFIELD_HEAD	STRU;//属性字段
}RECORD;//一条记录

//下面的图就是上面4个标志的形象说明（用图象坐标理解）
//            1 
//        --------
//        |      |
//       0|  Cur |2 
//        |      |
//        --------
//            3

//转换的类
class CRasToVect
{
public:
    CRasToVect();
    ~CRasToVect();
public:
    char		    m_ReRasName[MAX_PATH];    //中间栅格数据名.
    char            m_OutFClsName[MAX_XCLS_NAME_LEN];  //输出要素类名.
//  CGDataBase     *m_pReRasGDB;            //中间栅格数据保存的数据库.
 // CGDataBase     *m_pOutGDB;              //结果要素类保存的数据库.
//	CFeatureCls    *m_pOutFCls;             //输出区要素类.  
//	CSFeatureCls   *m_pOutSFCls;			//简单要素类
	int				IDCount;
	
	OGRLayer	   *poLayer;			 //创建一个图层
	OGRFeature	   *m_pOutFCl;				//输出区要素类  
	OGRFeature     *m_pOutSFCl;			//简单要素类
	OGRSFDriver *poDriver;
	OGRDataSource *poDS; //创建文件  

    BOOL            m_bRasIsOut;		    //原始图象是否是外面传递进来的
    BOOL            m_IsGenTempRas;         //是否产生临时影像集.
//  TempGDBInfoStrcT  m_TempGDBInfo;          //临时数据库.
    RAS_DATASET_ID    m_ReRasDataSetID;       //中间栅格数据ID.

    LIN_INFO	    m_linInf;			    //弧段的缺省线参数
    REG_INFO	    m_regInf;			    //区的缺省参数

    LPRCLINA	    m_pRclLinA;			//行程线段数据内存
    long		    m_lLinANum;			//线段的数目，用于在追踪的时候设置范围
    long		   *m_pLLineIndex;		//行程线段数据索引,用于提供行到线段的查询 //[LINE+1]
    long			m_lLines;			//图象行数
    long			m_lLineCells;		//图象列数
    LPREG			m_pRegArry;			//区数据(动态数组模式)
    M_Reg		   *m_pReg;				//区数据，直接内存方式
    long			m_lRegNum;			//区的数目
    M_RclLin	   *m_pRclLin;		    //以区为索引的线段数据
    long			m_lMaxCellNumOfSmallReg;//合并小区的时候的最大的面积
    BOOL			m_b4Near;
    short			m_lBandNo;			//要转换的波段号
    BOOL			m_bMakeTopo;        //2008-6-4添加，是否建立拓扑
    
	//20080825添加，是否将产生的要素类转存为简单要素类
	BOOL            m_bGenSFcls;

	// Add By Whp 2010.03.25 增加光滑设置参数的支持
	double		m_dSmoothRadius;		//光滑半径
	short		m_nSmoothType;			//光滑类型

	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////Added by psq for Common Test ---08.06.17////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
//	CGDataBase *m_pTempGDB;
	MSRSDatasetH m_hDS;                     //转换的原始影像
	MSRSDatasetH m_hReDS;                  //m_pReRasOBJ-进行合并之后的新的图象文件
	BOOL         m_bReDSInitCreateCpy;     //定义m_hReDS是否需要在初始化中作考贝创建

	MSRSDatasetH m_hNewDS;                 //m_pNewRasOBJ-在进行结点性质判断的时候的图象文件
	CString      m_strReOutType;           //合并小区的结果影像保存类型串
	BOOL         m_bIsReSmall;
	double       m_dTolerence;
	BOOL         m_bSrc7O;

	//标识转换过程中读写GetCellValueByBuffer(...)
	//时行值是否反向：对于没有地理范围的源影像，也不小区合并中间处理
	//如果读写行值不反向,结果矢量会上下颠倒(PSQ 20090422)
	BOOL         m_bYInvert;  

	// Add By Whp 2010.03.24 增加分类后结构体，记录分类的结构体信息
	MSCLASSATTINFO*	m_pClsAtt;
	long			m_lClsNums;
	BYTE*			m_bpszRLut;		//颜色查找表 Add By Whp 2010.03.25
	BYTE*			m_bpszGLut;
	BYTE*			m_bpszBLut;
	long			m_lLutNums;

	double			m_dBandMinVal;
	double			m_dBandMaxVal;

protected:
    long GetRclLinAData();			//生成行程线段数据
    long MergeSmallRegion();		//合并小区
	long MergeSmallRegionByUpdate(MSRSDatasetH hUpdateRaster,long lRowOff,long lColOff);//按照块更新方式合并小区
    long GetRegData();				//产生区数据m_pReg,返回区总数;产生行程数据 m_pRclLin
    virtual long CompareRclLinAndRecodeMaxReg(long *plRegRclLinIndex, long lBegRclLinAInd, long lEndRclLinAInd,
							long lCurLine,long lCurRegNo, unsigned long  wCurCla, unsigned long wCurFrom, unsigned long wCurTo/* unsigned short  wCurCla, WORD wCurFrom, WORD wCurTo*/);
    void GetNewMsi();				//得到在判断结点性质的时候所使用的图象
    BYTE IsNod(LPRASTER_ADAPT ReadAdapter,long nX,long nY);	//当前追踪点是否是结点
    long TrackRegMaxEdge();			//追踪各个区的外圈多边形
	//生成要素类
//    virtual long CreateAPolygon(EDGE_POINT *pPoly,long &lNum,unsigned long wCla,CATT_STRU *pFldStru,short FieldNo);
	//生成简单要素类
	long CreateAPolygonToSFCls(EDGE_POINT *pPoly,long &lNum,unsigned long wCla,CATT_STRU *pFldStru,short FieldNo);

    void GetOkPoly(EDGE_POINT *pPoly,long &lNum);
    void MakeTopo();				//利用底层函数来重建拓扑
    void DspMyErrMsg(int n);
	
    //一些内存处理函数
protected:
    void CloseAllDataSet();		//关闭所有的数据集.
    void FreeAllMem();			//释放所有的内存
    void FreeLinAMem();			//释放行程线段数据
    void FreeRegMem();			//释放区所占用的数据
    void FreeLinMem();			//释放以区为索引的线段数据
    void FreeLinAIndexMem();	//释放线段索引内存
    long InitRegMem();			//初始化区数据的内存
    long InitLinMem();			//初始化以区为索引的线段的内存
	bool InitLutTbl();			//初始化颜色查找表 Add By Whp 2010.03.25

public:
    //设置缺省参数
    void SetDefGraphInf(const LIN_INFO *linf,const REG_INFO *rinf);

    //设置转换的文件(直接给出栅格对象)
	long SetTransFile(MSRSDatasetH hDS,CString strReOutType, const char *pReRasName, const char *pFClsName);

	//设置光滑参数 Add By Whp 2010.03.25
	void SetSmoothOption(double dSmoothRad,short nSmoothType);

    //对一些变量进行初始化	
    long Init();	            
    //进行转换的主函数
    short Run();
    //进行小区合并的主函数
	short Run2();
	short Run3(MSRSDatasetH hUpdateRaster,long lRowOff,long lColOff);//分块更新模式

public:
	short ReSaveFcls2SFcls();  //将内部处理的要素结果保存为简单要素类
	void GetCellValueByBuffer(LPRASTER_ADAPT ReadAdapter,long row,long col,double &dValue,char *pInvalidFlag = NULL);//zk 2010-7-31
	long att_SetStru(OGRLayer * poLayer,CATT_STRU stru );
	long polygon_Append(OGRPolygon* AnyPolygon,OGRFeature* poFeature,CATT_STRU* stru,RECORD* reco,REG_INFO* m_regInf);
	void cbs2(double *buf_in,double *buf_out,long n);
};

} // End Namespace GDX

#endif