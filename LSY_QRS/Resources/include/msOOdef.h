// msOOdef.h
// 基本结构定义
#pragma once
#ifndef _MS_OBJECT_ORIENTED_DEFINE_H_
#define _MS_OBJECT_ORIENTED_DEFINE_H_

#include "afxtempl.h"
#include "RasterIOBaseDefine.h"
#include <vector>
using namespace std;

//特征统计中为定义的特征值

// 对象影像颜色查找表数目
#define   OO_COLORLUT_NUM	65536

// 无定义特征值
#define	 OO_FEATUREVALUE_UNDEFINED	-1.7976931348623e+308//-1.7e+308

// 未分类ID
#define	UNCLASSIFIED 0

// 寻找相邻对象时，判断过的位置填上该标记值
#define  FILL_FLAGVAL  2147483647		

//特征文件扩展名
const char  FtrFileExpandName[]="ofi";

// 取消对话框
#define   CANCEL  -1

#define   HAVEPRJANDCANCEL -2  //new add pp 2011-1124

//工程单位	2006.6.21  to add more	0x00    空出
#define OC_PrjUnit_pixel			0x01	//像元
#define OC_PrjUnit_kilometer		0x02	//公里
#define OC_PrjUnit_meter			0x03	//米	
#define OC_PrjUnit_centimeter		0x04	//厘米 

// 特征单位
#define  FU_PIXEL	1
#define  FU_KILOM	2
#define  FU_METER	3
#define  FU_CENTM	4


typedef struct ocRegPos // 对象位置,左上角为坐标原点
{
	long	x;		// 列
	long	y;		// 行
}OCREGPOS;		


typedef struct ocNabObj	// 相邻对象信息
{
	OCREGPOS ObjPos;	// 对象位置
	long	 lObjNo;	// 对象号
	long	 lComBrdNum;// 公共边数
}OCNABOBJ;	


typedef struct ooClsArea // 分类区域
{
	long	lXOff;		// X方向偏移
	long	lYOff;		// Y方向偏移
	long	lLineCells;	// 区域列数
	long	lLines;		// 区域行数
}OOCLSAREA;	


typedef struct ooObjAtt		// 对象属性
{
	bool		bIsDel;     // 对象是否删除  3.28增加
	long		lObjNo;		// 对象号,对象在属性文件中的位置
	OCREGPOS	ObjPos;		// 对象位置,对象在栅格文件中的位置
	long		lPixNum;	// 像元数
	long		lPerim;		// 对象周长
	RECT		lrRect;		// 对象包络矩形范围  影像坐标系	----->向右和向下
	double	   *pdMean;		// 各波段均值
	double	   *pdStdDev;	// 各波段方差，非标准差

	ooObjAtt()
	{
		memset(this,0,sizeof(ooObjAtt));
	}

}OOOBJATT;


/*
typedef	struct	ooObjLevel	//分割层信息
{
char	pGrdName[128];	//当前层栅格文件名
MSI		*pMsi;			//栅格指针，文件未打开时为NULL
char	pAttName[128];	//当前层属性文件名
FILE	*fpAtt;			//属性指针，文件未打开时为NULL

float	fScale;			//分割尺度
float	fWColor;		//颜色权
float	fWCompact;		//紧致度权
bool	bIsBF;			//true BF合并/false LMBF合并
long	lBands;			//波段数
float	*fpWBands;		//波段权值
}OOOBJLEVEL;*/


//typedef CArray<long,long&>	SUBOBJECTS;		//记录子对象号的数组
typedef CArray<long,long&>	OBJECTSARR;			//对象号的数组

typedef CArray<OCREGPOS, OCREGPOS&> AryObjPos;	// 对象位置数组
typedef CArray<OCNABOBJ, OCNABOBJ&> AryNabObj;	// 邻近对象数组


//{	工程中记录的层次信息  2006.6
//分割参数
typedef struct SegParam
{
	float	fScale;		//尺度参数，在分割内部平方
	float	*fpWBands;	//各波段权值
	float	fWColor;	//颜色权值
	float	fWSmooth;	//光滑度权值
	bool	IsNormal;	//分割方式 BF/LMBF;  true/false
}SEGPARAM;


typedef struct LayerInfo    //每层需要记录的信息
{
	bool	bIsDel;			//当前层文件是否被删除
	//	long	lLayerNo;		//层号,当前层在分级结构中的位置
	SEGPARAM *pParam;		//分割参数
	char	LayerTitle[128];//层名
	char	GrdName[128];	//栅格文件名
	char	AttName[128];	//属性文件名
	char	ClsName[128];	//分类文件名
	char	ClsImg[128];	//分类影像名	lc20100317添加
	char	VecName[128];	//矢量文件名
	bool	bIsCls;			//是否分类
	bool	bIsVec;			//是否矢量化
	//	MSI		*pGrdMsi;		//栅格指针，为打开时为NULL
}LAYERINFO;

typedef struct LevelIdx
{
	long	Idx;
	bool	IsNew;
} LEVELIDX;

typedef LAYERINFO* LEVELINFO;

typedef CArray<LEVELINFO, LEVELINFO&> LAYERNET;	//分级网
typedef CArray<LEVELIDX, LEVELIDX&>	  LAYERIDX;	//多层网络的索引
//}


// =================== for fuzzycls dll ==================
enum OOTERMOPER		// 条件操作符
{
	//	NOOPER = -1,	// 无操作
	AndMin,			// 求最小值		min(f1,f2,…)
	AndMult,		// 求乘积		(f1*f2*…)
	OrMax,			// 求最大值		max(f1,f2,…)
	MeanArith,		// 算术平均		(f1+f2+…) /n
	MeanGeo,		// 几何平均		(f1*f2*…)^(1/n)
	Not				// 取反			(1-fn)
};

/*typedef struct NodeData
{
OOTERMOPER	oper;	// 操作符
double		dMemb;	// 模糊度
}TNODEDATA;*/

enum OOSUPCLS		// 监督分类方法		
{
	StdNN,			// 标准最近邻
	CstNN,			// 自定义最近邻
	MLC,			// 最大似然法
	BPNN,			// BP神经网络
	RBFNN,			// RBF神经网络
	LVQNN,			// LVQ神经网络
	HRNN			// HR神经网络
};

// 模糊函数类型 Membership Function Type
#define  MF_UNDEFINE	-1		// 未定义类型
#define  MF_LARGER		0		// 大于
#define  MF_SMALLER		1		// 小于
#define  MF_LARGERBL	2		// 大于(布尔)
#define  MF_SMALLERBL	3		// 小于(布尔)
#define  MF_LARGERLN	4		// 大于(线性)  /
#define  MF_SMALLERLN	5		// 小于(线性)  \	
#define  MF_RAGEVREV	6		// 反V型
#define  MF_RAGEV		7		// V型		   V
#define  MF_SINGLE		8		// 单值
#define  MF_GAUSS		9		// 高斯
#define  MF_GAUSS3		10		// 3次高斯
#define  MF_BOOL		11		// 布尔


typedef struct ooClsPara	// 类参数
{
	long	lImgBands;		// 影像波段数
	BYTE	nNumGisChnl;	// 专题图层数
	BYTE	byPrjctUnit;	// 工程单位
	float	fMinProb;		// 最小模糊度
	float	fNNSlope;		// 最近邻函数的斜率
	short	sGreyScale;		// 纹理参数，灰度压缩级别
	short	sWinSizeX;		// 纹理参数，窗口大小X
	short	sWinSizeY;		// 纹理参数，窗口大小Y
	short	sRadius;		// 纹理参数，差值半径
}OOCLSPARA;

typedef struct ooClsInfo	// 类信息
{
	long	iClsID;			// 类号
	char	chName[128];	// 类名
	BYTE	byR;			// 颜色，R
	BYTE	byG;			// 颜色，G
	BYTE	byB;			// 颜色，B
	char	chComment[512];	// 注释
	BYTE	byFlag;			// 标志，Active(a),Abstract(b);flag/4=0,a+!b; =1,a+b; =2,!a+!b; else, !a+b 
	long	iMaskID;		// 保留，暂未用-1
	BYTE	byTermType;		// 保留，暂未用0
}OOCLSINFO;

typedef struct ooPropDesc	// 属性描述
{
	long	lFlagID;		// 标识ID
	short	sAttr;			// 暂未用，属性
	short	sChksm;			// 暂未用，?
	long	lChnl;			// 波段号	[0, n-1]
	short	sChnlAttr;		// 暂未用，波段属性
	long	lClsID;			// 类号
	long	lDist;			// 距离
	short	sUnit;			// 特征单位
	long	lFeatureID;		// 特征ID
}OOPROPDESC;

typedef struct ooIDMemb		// 类号-模糊度
{
	long	lClsID;			// 类号
	double	dMemb;			// 模糊度
}OOIDMEMB;

typedef struct ooClsNode		// 类层次树结点结构
{
	bool		bIsIn;			// 是否已插入
	long		lClsID;			// 类号
	long		lPrntID;		// 父结点类号
	HTREEITEM	hNode;			// 结点句柄
}OOCLSNODE;

typedef struct ooClsMNode	// 模糊度树结点结构
{
	bool	bIsIn;			// 是否已处理
	bool	bIsValid;		// 是否有效
	long	lClsID;			// 类号
	long	lPrntID;		// 父结点类号
	double	dMemb;			// 结点模糊度
}OOCLSMNODE;

// 结点类型
#define PRNTISROOT	-1
#define HASNOCHILD	-2
#define EQPRNTMEMB	-1.0f

typedef struct ooTermNode		// 规则结点数据
{
	BYTE		byFlag;			// 标志；结点为操作符-0；规则-1；监督分类-2；NN特征-3
	bool		bIsNot;			// 表达式是否取反
	OOPROPDESC	prop;			// 属性
	double		dHist[22];		// 模糊函数
}OOTERMNODE;

typedef struct ooNNTermNode		// NN特征结点
{
	BYTE		byFlag;			// 标志；结点为操作符-0；规则-1；监督分类-2；NN特征-3
	OOPROPDESC  pProp;			// 属性
}OONNTERMNODE;

typedef struct ooOperNode
{
	BYTE		byFlag;			// 标志；结点为操作符-0；规则-1；监督分类-2；分类规则-3
	bool		bIsNot;			// 表达式是否取反
	BYTE		byType;			// 操作符或监督分类类型
}OOOPERNODE;

/*typedef struct ooFtrNode		// 特征结点结构
{
BYTE		byFlag;			// 标志，特征与波段无关-0，有关-1，无拒类-2，有拒类-3
long		lNo;			// 波段号或类号
long		lFtrID;			// 特征号
long		lDist;			// 距离，-1 - 无该描述项
short		sUnit;			// 距离单位，-1 - 无该描述项
}OOFTRNODE;*/

typedef struct ooFtrInfo		// 特征信息结构
{
	long		lFtrID;			// 特征号
	char		chName[128];	// 特征名
	BYTE		byFlag;			// 标志位，特征与波段无关-0，有关-1，无拒类-2，有拒类-3
	long		lDist;			// 距离，-1 - 无该描述项
	short		sUnit;			// 距离单位，-1 - 无该描述项
	char        chFormular[512];// 自定义公式
	
	ooFtrInfo()
	{
		lFtrID=0;
		chName[0]='\0';
		byFlag = -1;
		lDist = -1;
		sUnit = -1;
		chFormular[0]='\0';
	}
}OOFTRINFO;

typedef struct ooName		// 波段名称
{
	char  chName[128];
	ooName()
	{
		memset(this,0,sizeof(ooName));
	}
}OONAME;

typedef struct ooIDName	 // 类ID名称
{
	long	lClsID;
	char	chName[128];
}OOIDNAME;

typedef struct ooObjClsInf	// 对象分类信息
{
	long	lClsID1;		// 最佳类号
	double	dMemb1;			// 最大隶属度
	long	lClsID2;
	double	dMemb2;
	long	lClsID3;
	double	dMemb3;
}OOOBJCLSINF;

typedef struct ooFtrIDVal	// 特征ID及特征值
{
	long	lFtrID;
	double *pFtrVal;
}OOFTRIDVAL;

typedef struct ooRGB
{
	BYTE	r;
	BYTE	g;
	BYTE	b;
}OORGB;

typedef CArray<long,long&>	ARRAYCLSID;				// 类号的数组
typedef CArray<OOPROPDESC, OOPROPDESC&> ARRAYPROP;	// 特征数组


//特征参数		2006.7.7
typedef struct FeatureParam
{
	long	FeatureID;	//特征标识
	long	BandNo;		//波段号
	long	ClsID;		//分类号
	int		FeatureDis;	//特征距离
	char	Unit;		//单位
}FEATUREPARAM;

//typedef CArray<FEATUREPARAM,FEATUREPARAM&> FEATPARAMARR;	//特征参数数组
//typedef CArray<OONAME,OONAME&> FEATFILENAMEARR;	        //特征文件名数组


//导出结果的标志		2006.7.5 废掉  zj
//#define Exp_CLS		0x01
//#define Exp_SEG		0x02
//#define Exp_VEC		0x03

//工程文件标识
const char  OC_PROJECT_FILE01[]="OC_IMG_ANALYZE_PRJ_FILE_VER0.1";
//文件头标识
const char MS_OOCLASS_OBJFTR_FILEHEAD10[] = "MS_OOCLASS_OBJFTR_FILEHEAD1.0";
const char MS_OOCLASS_OBJCLS_FILEHEAD10[] = "MS_OOCLASS_OBJCLS_FILEHEAD1.0";
const char MS_OOCLASS_PROJECT_FILEHEAD10[] = "MS_OOCLASS_PROJECT_FILEHEAD1.0";

typedef struct OpjFileHeader
{
	char	pClsFileName[128];
	char	pFtrFileName[128];
	char	pOrgImgName[256];
	long	PrjLines;		//工程行数
	long	PrjLineCells;	//工程列数
	long	PrjBands;		//工程波段数
	char	CellUnit;		//工程计量单位
	double	Resolution;		//像元分辨率，以m为单位	
	long	LayerNums;		//层数
	int		CurLayerNo;		//当前层号(当前进行处理的层号)

	OpjFileHeader()
	{
		memset(this,0,sizeof(OpjFileHeader));
	}

}OPJFILEHEADER;

//训练区样本信息(在用矢量区样本方法做精度评价时会用到)
typedef struct TrainArea_Struct
{
	long lID;        //记录各类别ID
	unsigned char R;  
	unsigned char G; //记录各类别所对应的R、G、B值
	unsigned char B;  
	char cClsName[128];
}TRAINAREA;

typedef struct MatchID_Struct
{
	char cClsName[128];
	long lRefID; //参照ID
	long lUseID; //结果ID
}MATCHID;

typedef struct ClasssInfo_Struct
{
	long   lObjNums;//记录各类的对象
	double dMean;   //记录各类对象隶属度的均值
	double dStdv;   //记录各类对象隶属度的标准差
	double dMin;    //记录各类对象隶属度的最小值
	double dMax;    //记录各类对象隶属度的最大值
}ClassINFO;

//psq 2011.12.14 add
typedef struct ooRuleOper 
{
	OOOPERNODE OperInfo;
	char       szOrCold[128];		//每层顺序编码(深度为1234…，无需记录)
	char       szOpCold[128];		//运算符编码(比OrCold少一位),1-and(min); 2-and(*); 3-or(max); 4-mean(arithm.); 5-mean(geo.); 6-not
	vector<OOTERMNODE> vctTerms;
	vector<struct ooRuleOper> vctSubOpers;
	long	   lClsID;//PP ADD 2012-0531

	ooRuleOper()
	{
		szOpCold[0] = '\0';
		szOrCold[0] = '\0';
	}

}OORULEOPER;
typedef struct ComboRuleInfo 
{
	long		lClsID;
	long        lDtID;
	char        szClsName[128];
	OOCLSINFO   oClsInfo;

	OORULEOPER  CoboRule;

	ComboRuleInfo()
	{
		lDtID = -1;
		lClsID = -1;
		szClsName[0] = '\0';
	}

}OOCOMBORULEINFO;

typedef CArray<OCREGPOS, OCREGPOS&> AryObjPos;	// 对象位置数组
typedef CArray<OCNABOBJ, OCNABOBJ&> AryNabObj;	// 邻近对象数组
typedef void*	LPRASTER_ADAPT;					//v7x驱动

#define MS_SUCCESS						0L
#define MS_FAIL							-1L			// 定义未知类型的错误，cqh, 20080319

#define  MSI_MIN_BYTE    0 
#define  MSI_MAX_BYTE    255 
#define  MSI_MIN_WORD    0
#define  MSI_MAX_WORD    65535
#define  MSI_MIN_DWORD   0
#define  MSI_MAX_DWORD   4294967295
#define  MSI_MIN_CHAR    -128
#define  MSI_MAX_CHAR     127
#define  MSI_MIN_SHORT   -32768
#define  MSI_MAX_SHORT    32767
#define  MSI_MIN_LONG    -2147483640.8F//-2147483648
#define  MSI_MAX_LONG     2147483640.8F//2147483647 
#define  MSI_MIN_FLOAT   -3.402823466e+38F
#define  MSI_MAX_FLOAT    3.402823466e+38F
#define  MSI_MIN_DOUBLE  -1.7976931348623e+308
#define  MSI_MAX_DOUBLE   1.7976931348623e+308
#define  MSI_MIN_1BIT     0
#define  MSI_MAX_1BIT     1
#define  MSI_MAX_FLOAT10  3.402823466e+37F
#define  MSI_PI	 		  3.14159265358979323846

//内存管理/mem  错误类别：200                    
#define MS_CANNOT_ALLOCMEM						2000001L
#define MS_CANNOT_FREEMEM						2000002L
#define MS_CANNOT_REALLOCMEM					2000003L
#define MS_INVALID_POINTER						2000004L

//其它错误/other error 错误类别：400 
#define MS_CANCEL_OPERATION    				    4000001L
#define MS_FILE_HAS_EXISTED                     4000002L
#define MS_TIFF_TO_MSI_ERROR                    4000003L
#define MS_RAWFILESIZE_TOO_SMALL                4000004l
#define MS_CEFF_ERROR                           4000005l
#define MS_SYS_ERROR                            4000006l
#define MS_CEFF_CANNOT_GET                      4000007l
#define MS_INVALID_NULLCELL_VALUE               4000008l
#define MS_INVALID_INTERPOLATE_VALUE            4000009l
#define MS_INVALID_AOI_CEFF_VALUE               4000010l
#define MS_INSTEADOFNULLCELLVALUE_EQUAL_NULLCELLVALUE     4000011l
#define MS_INVALID_INSTEADOFNULLCELLVALUE       4000012l
#define MS_POINT_NUMS_TOO_LESS                  4000013l
#define MS_INVALID_GEOMOTRY_TRANSFORM_FORME     4000014l
#define MS_INVALID_INPUT_CEFF                   4000015l
#define MS_SOURCE_CONTRAL_POINT_NOT_ENOUGH      4000016l
#define MS_CONTRAL_POINT_HAS_EXIST              4000017l
#define MS_MAPGIS_ERROR                         4000018l
#define MS_SOURCE_AOI_NOT_ENOUGH                4000019l
#define MS_SOURCE_POLYGON_NOT_ENOUGH            4000020l
#define MS_SOURCE_POINT_NOT_ENOUGH              4000021l 
#define MS_NO_INSTALL_POINT                     4000022l 
#define MS_MOSAIC_MSI_FILE_ERROR                4000023l 
#define MS_MOSAIC_NO_INTERSECT_RECT             4000024l 
#define MS_DrawMSIsA8BitOneMsiScreen_FAILTURE   4000025l 
////////////////////////////////////////////////////////////

//MSI文件格式/MSI  错误类别：202
#define MS_BYTEORDER_CANNOT_SUPPORT				2020002L
#define MS_VERSION_CANNOT_SUPPORT				2020003L
#define MS_NO_MORE_DIRECTORY					2020004L
#define MS_DIR_ORDER_ERROR                      2020005L
#define MS_SCALE_EQUAL_ZERO                     2020006L
#define MS_MSIFILE_NEED_UPDATA                  2020007L
//////////////////////////////////////////////////////////////////////////

//{{数学常量定义
#define  PI		3.14159265358979323846

#define  MIN_FLOAT	(-3.402823E+38)
#define  ZERO_FLOAT (+1.401298E-45)
#define  MAX_FLOAT	(+3.402823E+38)

#define  MIN_DOUBLE		(-1.79769313486232E+307)
#define  MAX_DOUBLE		(+1.79769313486232E+307)
#define  ZERO_MIN_DBL   (-4.94065645841247E-324)
#define  ZERO_MAX_DBL   (+4.94065645841247E-324)
#define  MIN_VALUE		(+1.000000E-20)		    //绝对值小于此值即认为=0

#define  MIN_INT	-32768
#define  MAX_INT	+32767

#define  MIN_LONG	-2147483648
#define  MAX_LONG   +2147483647
//}}
//////////////////////////////////////////////////////////////////////////
// 通用栅格IO错误
#define MS_RSDATAIO_FAIL						5010000L	// 通用栅格数据集IO层错误

//////////////////////////////////////////////////////////////////////////
enum V7X_RAS_CELLTYPE  //像元类型.
{
	V7X_RAS_UNKNOWN = MS_Unknown,
	V7X_RAS_UINT8	= MS_Byte,	    // 8位无符号整数
	//V7X_RAS_ASCII	= MS_Unknown,   // 以0结尾的ASCLL串
	V7X_RAS_UINT16	= MS_UInt16,	// 16位无符号整数
	V7X_RAS_UINT32	= MS_UInt32,	// 32位无符号整数
	V7X_RAS_INT8	= MS_Int8,	    // 8位有符号整数
	V7X_RAS_INT16	= MS_Int16,	    // 16位有符号整数
	V7X_RAS_INT32	= MS_Int32,	    // 32位有符号整数
	V7X_RAS_IEEE4	= MS_Float32,	// 四字节浮点数据
	V7X_RAS_IEEE8  	= MS_Float64,	// 双精度浮点数据
	V7X_RAS_1BIT    = MS_1Bit       // 1位二值图的数据
};
//////////////////////////////////////////////////////////////////////////

// 宏定义
//////////////////////////////////////////////////////////////////////////
#define V7X_RAS_SUCCESS     0L 
#define V7X_RAS_FAIL       -10000000L

//////////////////////////////////////////////////////////////////////////
//标志的数值错/NUMBERS_ERROR  错误类别：101
#define MS_BANDSOFFSET_NUMBERS_ERROR			1010001L 
#define MS_COLORLUT_NUMBERS_ERROR				1010002L 
#define MS_BANDS_NUMBERS_ERROR					1010003L
#define MS_LINES_NUMBERS_ERROR					1010004L
#define MS_LINECELLS_NUMBERS_ERROR				1010005L
#define MS_NOTEINFO_NUMBERS_ERROR				1010006L
#define MS_MINCELLVALUE_NUMBERS_ERROR			1010007L
#define MS_MAXCELLVALUE_NUMBERS_ERROR			1010008L
#define MS_CELLTYPE_NUMBERS_ERROR		    	1010009L
#define MS_BANDS_NOTE_INFO_LENGTH_NUMBER_ERROR  1010010L
#define MS_BANDS_NOTE_INFO_LENGTH_ERROR         1010011L
#define MS_RESOLUTIONUNIT_ERROR                 1010012L 
#define MS_DOCUMENT_NAME_LENGTH__ERROR          1010013L
#define MS_IMAGE_DESCRIPTION_LENGTH__ERROR      1010014L
#define MS_SOFTWARE_LENGTH__ERROR               1010015L
#define MS_DATETIME_LENGTH__ERROR               1010016L
#define MS_ARTIST_LENGTH__ERROR                 1010017L 
#define MS_HOSTCOMPUTER_LENGTH__ERROR           1010018L 
#define MS_COLORLUTNAME_NUMBERS_ERROR           1010019L 
#define MS_COLORLUT_NAME_LENGTH_ERROR           1010020L
#define MS_COLORLUT_NO_ERROR                    1010021L
#define MS_BAND_NO_ERROR                        1010022L
#define MS_PYRAMIDLAYER_NO_ERROR   				1010023L
#define MS_ROW_COL_TILE__NO_ERROR   			1010024L
#define MS_TILE__NO_ERROR			   			1010025L
#define MS_GRAYSCALE_NUMBERS_ERROR	   			1010026L
#define MS_AOIS_NUMBERS_ERROR					1010027L	// added by cqh 20070703
//////////////////////////////////////////////////////////////////////////
#define MS_NULL_INPUT                           4000025l 
#define MS_MISS_OPAN					        4000026l 
#define MS_MISS_OPAND							4000027l 
#define MS_MISS_FILE						    4000028l 
#define MS_ERROR_SIGN							4000029l 
#define MS_UNDEF_TOKEN							4000030l 
#define MS_MISS_LPARE							4000031l 
#define MS_ERROR_FILE							4000032l 
#define MS_MISS_RPARE							4000033l 
#define MS_ERROR_IF								4000034l 
#define MS_MISS_SPACE                           4000035l 
//////////////////////////////////////////////////////////////////////////
#define XCLS_TYPE_SFCLS			30		//简单要素类
#define XCLS_TYPE_SFSET			31		//简单要素集
#define XCLS_TYPE_MGEOMSET		32		//多集合实体集
#define XCLS_TYPE_MSPTSET		33		//多空间元素集
//////////////////////////////////////////////////////////////////////////
#define RAS_SUCCESS 1
#define RAS_FAIL    0
//////////////////////////////////////////////////////////////////////////
//================================================================================
// 网格高程数据信息结构..
//================================================================================
#ifndef DEMINFOSTRCT_DEFINED
#define DEMINFOSTRCT_DEFINED
typedef struct tagDemInfoStrcT
{
	long   nx,ny;
	double xmin,xmax;
	double ymin,ymax;
	double zmin,zmax;
	tagDemInfoStrcT()
	{
		nx = ny = 0;
		xmin = xmax = 0;
		ymin = ymax = 0;
		zmin = zmax = 0;
	}
} DemInfoStrcT;
#endif
//////////////////////////////////////////////////////////////////////////
//系统环境结构定义
typedef struct
{
	char clib[128];	//汉字库目录
	char sys[128];	//系统目录
	char cur[128];	//当前工作目录
	char temp[128];	//临时工作目录
	char slib[128];	//系统库目录
}GISENV;
//////////////////////////////////////////////////////////////////////////
//标识类型定义：
typedef long    TYPE_XCLS_ID;  		//XCLS标识
typedef long    TYPE_FCLS_ID;   	//要素类标识
typedef long    TYPE_OCLS_ID;   	//对象类标识
typedef long    TYPE_ACLS_ID;   	//注记类标识
typedef long    TYPE_RCLS_ID;   	//关系类标识
typedef long    TYPE_DCLS_ID;   	//动态要素类标识
typedef long    TYPE_DRSCLS_ID;   	//修饰类标识
typedef	long	TYPE_TMPL_ID;
typedef long	TYPE_TMPLLIB_ID;
typedef long    TYPE_RULE_ID  ;   	//规则标识 
//////////////////////////////////////////////////////////////////////////
#ifndef   _MS_IMAGE_CLASS_BASE_H_
#define   _MS_IMAGE_CLASS_BASE_H_

// AOI样本信息结构定义 add by cqh
struct AOICELL
{
	long lAoiNo;//AOI序号[1,N]
	long lRow;//行号
	long lCol;//列号
	double *pBandVal;//像元值
};

// 分类信息结构定义 add by cqh
struct CLASSATTINFO
{
	BYTE	byValue;		// 像元值
	BYTE	byName[128];	// 类名称
	BYTE	byR;			// 颜色
	BYTE	byG;
	BYTE	byB;
	BYTE	byDescrip[128];	// 描述
};

// 精度评价结果结构
//制图精度：被正确分类的像元数/该类别实际的像元数
//总体精度：所有被正确分类的像元数之和/总的样本像元数
struct CLASSACCURACY
{
	long	lTotal;			//测试样本总数
	long	lClassNum;		//类别数
	long	**lppErrorMatrix;	//误差矩阵
	long	*lpColTotal;		//误差矩阵每1列的总和
	long	*lpRowTotal;		//误差矩阵每1行的总和
	double	*dpAccuracy;		//每类制图精度
	double	dTotalAccuracy;	//总体精度
	double	dKappa;			// Kappa 系数
};

// 采样点结构
struct CLASSSAMPLEPNT	
{
	double	dSx;			// 坐标
	double	dSy;
	long	lClassNo;		// 分类号
};
#endif	// end #define   _MS_IMAGE_CLASS_BASE_H_
//////////////////////////////////////////////////////////////////////////
typedef struct LINSTYLE_INFOstruct
{
	short   libID;		  //库编号	
	long    linstyID;	  //线型号

	char    ovprnt;  	 //覆盖方式
	float   outpenw[3];	 //三个外部笔宽
	long    outclr[3];	 //三个可变颜色
	char    headtype;	 //线头类型
	char    jointype;    //拐角类型
	char    adjustflg;   //线型调整方法       
	char    makemethod;  //线型生成方法：规律性生成线型、按控制点生成线型
	float   xscale;		  //X系数
	float   yscale;       //Y系数			
}LINSTYLE_INFO,LIN_INFO;
//////////////////////////////////////////////////////////////////////////
//===================三、图案图形参数结构：
//图案可视化主要考虑的问题：
//1.	图案的旋转。
//2.	晕渲线的填充
//3.	基线形成陡崖,陡石山等图案
typedef struct PATTERN_INFOstruct
{
	short  libID;		 //库编号
	long   patID;	 	 //符号编号
	char   ovprnt;		 //覆盖方式
	short  fillmode;     //填充模式：  0：通常单色填充，1－8分别表示8方向渐变填充，
	long   fillclr;	     //区域填充色，渐变填充时为起始色
	long   endclr;		 //结束填充色，渐变填充时的结束色

	float   pathei;	       //图案高
	float   patwid;	       //图案宽
	float   ang;	       //图案角度
	long    patclr;	       //图案颜色，图案颜色固定，即使渐变填充时也不变。
	float   outpenw;       //图案笔宽
	char    fullpatflg;    //是否需要完整图案填充
}PATTERN_INFO,REG_INFO;
//////////////////////////////////////////////////////////////////////////
typedef struct
{
	short      c1;      // red,	cyan, hue, or gray
	short      c2;      // green, magenta, or lightness
	short      c3;      // blue, yellow, or saturation
	short      c4;      // alpha, or black
} MSRSColorEntry;
//////////////////////////////////////////////////////////////////////////
//控制点结构
typedef struct
{
	char        *pszId;		// 唯一标识ID，常为数字类型
	char        *pszInfo;	// 控制点描述信息，或为"" 
	double      dfGCPPixel;	// 控制点图象坐标X
	double      dfGCPLine;	// 控制点图象坐标Y
	double      dfGCPX;		// 控制点地理参考坐标X
	double      dfGCPY;		// 控制点地理参考坐标Y
	double      dfGCPZ;		// 控制点高程值，或0，或未知
	char		bIsInUse;	// 使用标志位；Gw20061218添加，等同于原来MSI文件中的UseOnoff标志
#ifndef WIN32   //Linux-2010.5.19
	long		invalidlinux;
#endif
} MSRS_GCP;
//////////////////////////////////////////////////////////////////////////
#define MAX_FLD_NAME_LEN 	20	//最大字段名长度(VFOXPRO最大字段名长度)
#define FLD_NAME_LEN		MAX_FLD_NAME_LEN
#define MAX_OWNER_LEN 		30	//最大属主名长度
#define MAX_USER_LEN		MAX_OWNER_LEN	//最大用户名长度
#define MAX_PSW_LEN			64	//最大口令长度
//////////////////////////////////////////////////////////////////////////
#define MAX_SVR_NAME_LEN    64	//最大服务器名称长度(包括结束符)
#define MAX_DB_NAME_LEN     32  //最大数据库名称长度(包括结束符)
#define MAX_GDB_NAME_LEN	64  //最大地理数据库名称长度(包括结束符)
#define MAX_XCLS_NAME_LEN   128 //最大XCLS名称长度(包括结束符)
#define MAX_DS_NAME_LEN	    128	//最大数据集名长度
#define MAX_VER_NAME_LEN    128 //最大版本名长度(包括结束符)
#define MAX_HDF_PATH_LEN    256 //最大数据库名长度(包括结束符)
//////////////////////////////////////////////////////////////////////////
const char MS_RSCOMDISPINFO_FILE10[64]="msRSComDispInfoFile1.0";
//////////////////////////////////////////////////////////////////////////
//影像色表类型
typedef enum 
{
	MS_Gray=0,					// 灰度 (in GDALColorEntry.c1) 
	MS_RGB=1,					// RGB彩色，Red, Green, Blue and Alpha in (in c1, c2, c3 and c4)
	MS_CMYK=2,					// CMYK彩色，Cyan, Magenta, Yellow and Black (in c1, c2, c3 and c4)
	MS_HLS=3					// HLS彩色，Hue, Lightness and Saturation (in c1, c2, and c3)
} MSRSPaletteInterp;
//////////////////////////////////////////////////////////////////////////
// 影像显示信息
typedef struct
{
	char	cDispType;		//图像显示方式，1-RGB,2-RGBP,3-GRAY,4-CLASSIFY,0-DEFAULT
	//参见RAS_DISPLAYFORM,rasbasedefine.h
	short	nRBandNo;		//R波段
	short	nGBandNo;		//G波段
	short	nBBandNo;		//B波段
}RASImgDispInfo;
//////////////////////////////////////////////////////////////////////////
#endif
