// msOOdef.h
// �����ṹ����
#pragma once
#ifndef _MS_OBJECT_ORIENTED_DEFINE_H_
#define _MS_OBJECT_ORIENTED_DEFINE_H_

#include "afxtempl.h"
#include "RasterIOBaseDefine.h"
#include <vector>
using namespace std;

//����ͳ����Ϊ���������ֵ

// ����Ӱ����ɫ���ұ���Ŀ
#define   OO_COLORLUT_NUM	65536

// �޶�������ֵ
#define	 OO_FEATUREVALUE_UNDEFINED	-1.7976931348623e+308//-1.7e+308

// δ����ID
#define	UNCLASSIFIED 0

// Ѱ�����ڶ���ʱ���жϹ���λ�����ϸñ��ֵ
#define  FILL_FLAGVAL  2147483647		

//�����ļ���չ��
const char  FtrFileExpandName[]="ofi";

// ȡ���Ի���
#define   CANCEL  -1

#define   HAVEPRJANDCANCEL -2  //new add pp 2011-1124

//���̵�λ	2006.6.21  to add more	0x00    �ճ�
#define OC_PrjUnit_pixel			0x01	//��Ԫ
#define OC_PrjUnit_kilometer		0x02	//����
#define OC_PrjUnit_meter			0x03	//��	
#define OC_PrjUnit_centimeter		0x04	//���� 

// ������λ
#define  FU_PIXEL	1
#define  FU_KILOM	2
#define  FU_METER	3
#define  FU_CENTM	4


typedef struct ocRegPos // ����λ��,���Ͻ�Ϊ����ԭ��
{
	long	x;		// ��
	long	y;		// ��
}OCREGPOS;		


typedef struct ocNabObj	// ���ڶ�����Ϣ
{
	OCREGPOS ObjPos;	// ����λ��
	long	 lObjNo;	// �����
	long	 lComBrdNum;// ��������
}OCNABOBJ;	


typedef struct ooClsArea // ��������
{
	long	lXOff;		// X����ƫ��
	long	lYOff;		// Y����ƫ��
	long	lLineCells;	// ��������
	long	lLines;		// ��������
}OOCLSAREA;	


typedef struct ooObjAtt		// ��������
{
	bool		bIsDel;     // �����Ƿ�ɾ��  3.28����
	long		lObjNo;		// �����,�����������ļ��е�λ��
	OCREGPOS	ObjPos;		// ����λ��,������դ���ļ��е�λ��
	long		lPixNum;	// ��Ԫ��
	long		lPerim;		// �����ܳ�
	RECT		lrRect;		// ���������η�Χ  Ӱ������ϵ	----->���Һ�����
	double	   *pdMean;		// �����ξ�ֵ
	double	   *pdStdDev;	// �����η���Ǳ�׼��

	ooObjAtt()
	{
		memset(this,0,sizeof(ooObjAtt));
	}

}OOOBJATT;


/*
typedef	struct	ooObjLevel	//�ָ����Ϣ
{
char	pGrdName[128];	//��ǰ��դ���ļ���
MSI		*pMsi;			//դ��ָ�룬�ļ�δ��ʱΪNULL
char	pAttName[128];	//��ǰ�������ļ���
FILE	*fpAtt;			//����ָ�룬�ļ�δ��ʱΪNULL

float	fScale;			//�ָ�߶�
float	fWColor;		//��ɫȨ
float	fWCompact;		//���¶�Ȩ
bool	bIsBF;			//true BF�ϲ�/false LMBF�ϲ�
long	lBands;			//������
float	*fpWBands;		//����Ȩֵ
}OOOBJLEVEL;*/


//typedef CArray<long,long&>	SUBOBJECTS;		//��¼�Ӷ���ŵ�����
typedef CArray<long,long&>	OBJECTSARR;			//����ŵ�����

typedef CArray<OCREGPOS, OCREGPOS&> AryObjPos;	// ����λ������
typedef CArray<OCNABOBJ, OCNABOBJ&> AryNabObj;	// �ڽ���������


//{	�����м�¼�Ĳ����Ϣ  2006.6
//�ָ����
typedef struct SegParam
{
	float	fScale;		//�߶Ȳ������ڷָ��ڲ�ƽ��
	float	*fpWBands;	//������Ȩֵ
	float	fWColor;	//��ɫȨֵ
	float	fWSmooth;	//�⻬��Ȩֵ
	bool	IsNormal;	//�ָʽ BF/LMBF;  true/false
}SEGPARAM;


typedef struct LayerInfo    //ÿ����Ҫ��¼����Ϣ
{
	bool	bIsDel;			//��ǰ���ļ��Ƿ�ɾ��
	//	long	lLayerNo;		//���,��ǰ���ڷּ��ṹ�е�λ��
	SEGPARAM *pParam;		//�ָ����
	char	LayerTitle[128];//����
	char	GrdName[128];	//դ���ļ���
	char	AttName[128];	//�����ļ���
	char	ClsName[128];	//�����ļ���
	char	ClsImg[128];	//����Ӱ����	lc20100317���
	char	VecName[128];	//ʸ���ļ���
	bool	bIsCls;			//�Ƿ����
	bool	bIsVec;			//�Ƿ�ʸ����
	//	MSI		*pGrdMsi;		//դ��ָ�룬Ϊ��ʱΪNULL
}LAYERINFO;

typedef struct LevelIdx
{
	long	Idx;
	bool	IsNew;
} LEVELIDX;

typedef LAYERINFO* LEVELINFO;

typedef CArray<LEVELINFO, LEVELINFO&> LAYERNET;	//�ּ���
typedef CArray<LEVELIDX, LEVELIDX&>	  LAYERIDX;	//������������
//}


// =================== for fuzzycls dll ==================
enum OOTERMOPER		// ����������
{
	//	NOOPER = -1,	// �޲���
	AndMin,			// ����Сֵ		min(f1,f2,��)
	AndMult,		// ��˻�		(f1*f2*��)
	OrMax,			// �����ֵ		max(f1,f2,��)
	MeanArith,		// ����ƽ��		(f1+f2+��) /n
	MeanGeo,		// ����ƽ��		(f1*f2*��)^(1/n)
	Not				// ȡ��			(1-fn)
};

/*typedef struct NodeData
{
OOTERMOPER	oper;	// ������
double		dMemb;	// ģ����
}TNODEDATA;*/

enum OOSUPCLS		// �ල���෽��		
{
	StdNN,			// ��׼�����
	CstNN,			// �Զ��������
	MLC,			// �����Ȼ��
	BPNN,			// BP������
	RBFNN,			// RBF������
	LVQNN,			// LVQ������
	HRNN			// HR������
};

// ģ���������� Membership Function Type
#define  MF_UNDEFINE	-1		// δ��������
#define  MF_LARGER		0		// ����
#define  MF_SMALLER		1		// С��
#define  MF_LARGERBL	2		// ����(����)
#define  MF_SMALLERBL	3		// С��(����)
#define  MF_LARGERLN	4		// ����(����)  /
#define  MF_SMALLERLN	5		// С��(����)  \	
#define  MF_RAGEVREV	6		// ��V��
#define  MF_RAGEV		7		// V��		   V
#define  MF_SINGLE		8		// ��ֵ
#define  MF_GAUSS		9		// ��˹
#define  MF_GAUSS3		10		// 3�θ�˹
#define  MF_BOOL		11		// ����


typedef struct ooClsPara	// �����
{
	long	lImgBands;		// Ӱ�񲨶���
	BYTE	nNumGisChnl;	// ר��ͼ����
	BYTE	byPrjctUnit;	// ���̵�λ
	float	fMinProb;		// ��Сģ����
	float	fNNSlope;		// ����ں�����б��
	short	sGreyScale;		// ����������Ҷ�ѹ������
	short	sWinSizeX;		// ������������ڴ�СX
	short	sWinSizeY;		// ������������ڴ�СY
	short	sRadius;		// �����������ֵ�뾶
}OOCLSPARA;

typedef struct ooClsInfo	// ����Ϣ
{
	long	iClsID;			// ���
	char	chName[128];	// ����
	BYTE	byR;			// ��ɫ��R
	BYTE	byG;			// ��ɫ��G
	BYTE	byB;			// ��ɫ��B
	char	chComment[512];	// ע��
	BYTE	byFlag;			// ��־��Active(a),Abstract(b);flag/4=0,a+!b; =1,a+b; =2,!a+!b; else, !a+b 
	long	iMaskID;		// ��������δ��-1
	BYTE	byTermType;		// ��������δ��0
}OOCLSINFO;

typedef struct ooPropDesc	// ��������
{
	long	lFlagID;		// ��ʶID
	short	sAttr;			// ��δ�ã�����
	short	sChksm;			// ��δ�ã�?
	long	lChnl;			// ���κ�	[0, n-1]
	short	sChnlAttr;		// ��δ�ã���������
	long	lClsID;			// ���
	long	lDist;			// ����
	short	sUnit;			// ������λ
	long	lFeatureID;		// ����ID
}OOPROPDESC;

typedef struct ooIDMemb		// ���-ģ����
{
	long	lClsID;			// ���
	double	dMemb;			// ģ����
}OOIDMEMB;

typedef struct ooClsNode		// ���������ṹ
{
	bool		bIsIn;			// �Ƿ��Ѳ���
	long		lClsID;			// ���
	long		lPrntID;		// ��������
	HTREEITEM	hNode;			// �����
}OOCLSNODE;

typedef struct ooClsMNode	// ģ���������ṹ
{
	bool	bIsIn;			// �Ƿ��Ѵ���
	bool	bIsValid;		// �Ƿ���Ч
	long	lClsID;			// ���
	long	lPrntID;		// ��������
	double	dMemb;			// ���ģ����
}OOCLSMNODE;

// �������
#define PRNTISROOT	-1
#define HASNOCHILD	-2
#define EQPRNTMEMB	-1.0f

typedef struct ooTermNode		// ����������
{
	BYTE		byFlag;			// ��־�����Ϊ������-0������-1���ල����-2��NN����-3
	bool		bIsNot;			// ���ʽ�Ƿ�ȡ��
	OOPROPDESC	prop;			// ����
	double		dHist[22];		// ģ������
}OOTERMNODE;

typedef struct ooNNTermNode		// NN�������
{
	BYTE		byFlag;			// ��־�����Ϊ������-0������-1���ල����-2��NN����-3
	OOPROPDESC  pProp;			// ����
}OONNTERMNODE;

typedef struct ooOperNode
{
	BYTE		byFlag;			// ��־�����Ϊ������-0������-1���ල����-2���������-3
	bool		bIsNot;			// ���ʽ�Ƿ�ȡ��
	BYTE		byType;			// ��������ල��������
}OOOPERNODE;

/*typedef struct ooFtrNode		// �������ṹ
{
BYTE		byFlag;			// ��־�������벨���޹�-0���й�-1���޾���-2���о���-3
long		lNo;			// ���κŻ����
long		lFtrID;			// ������
long		lDist;			// ���룬-1 - �޸�������
short		sUnit;			// ���뵥λ��-1 - �޸�������
}OOFTRNODE;*/

typedef struct ooFtrInfo		// ������Ϣ�ṹ
{
	long		lFtrID;			// ������
	char		chName[128];	// ������
	BYTE		byFlag;			// ��־λ�������벨���޹�-0���й�-1���޾���-2���о���-3
	long		lDist;			// ���룬-1 - �޸�������
	short		sUnit;			// ���뵥λ��-1 - �޸�������
	char        chFormular[512];// �Զ��幫ʽ
	
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

typedef struct ooName		// ��������
{
	char  chName[128];
	ooName()
	{
		memset(this,0,sizeof(ooName));
	}
}OONAME;

typedef struct ooIDName	 // ��ID����
{
	long	lClsID;
	char	chName[128];
}OOIDNAME;

typedef struct ooObjClsInf	// ���������Ϣ
{
	long	lClsID1;		// ������
	double	dMemb1;			// ���������
	long	lClsID2;
	double	dMemb2;
	long	lClsID3;
	double	dMemb3;
}OOOBJCLSINF;

typedef struct ooFtrIDVal	// ����ID������ֵ
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

typedef CArray<long,long&>	ARRAYCLSID;				// ��ŵ�����
typedef CArray<OOPROPDESC, OOPROPDESC&> ARRAYPROP;	// ��������


//��������		2006.7.7
typedef struct FeatureParam
{
	long	FeatureID;	//������ʶ
	long	BandNo;		//���κ�
	long	ClsID;		//�����
	int		FeatureDis;	//��������
	char	Unit;		//��λ
}FEATUREPARAM;

//typedef CArray<FEATUREPARAM,FEATUREPARAM&> FEATPARAMARR;	//������������
//typedef CArray<OONAME,OONAME&> FEATFILENAMEARR;	        //�����ļ�������


//��������ı�־		2006.7.5 �ϵ�  zj
//#define Exp_CLS		0x01
//#define Exp_SEG		0x02
//#define Exp_VEC		0x03

//�����ļ���ʶ
const char  OC_PROJECT_FILE01[]="OC_IMG_ANALYZE_PRJ_FILE_VER0.1";
//�ļ�ͷ��ʶ
const char MS_OOCLASS_OBJFTR_FILEHEAD10[] = "MS_OOCLASS_OBJFTR_FILEHEAD1.0";
const char MS_OOCLASS_OBJCLS_FILEHEAD10[] = "MS_OOCLASS_OBJCLS_FILEHEAD1.0";
const char MS_OOCLASS_PROJECT_FILEHEAD10[] = "MS_OOCLASS_PROJECT_FILEHEAD1.0";

typedef struct OpjFileHeader
{
	char	pClsFileName[128];
	char	pFtrFileName[128];
	char	pOrgImgName[256];
	long	PrjLines;		//��������
	long	PrjLineCells;	//��������
	long	PrjBands;		//���̲�����
	char	CellUnit;		//���̼�����λ
	double	Resolution;		//��Ԫ�ֱ��ʣ���mΪ��λ	
	long	LayerNums;		//����
	int		CurLayerNo;		//��ǰ���(��ǰ���д���Ĳ��)

	OpjFileHeader()
	{
		memset(this,0,sizeof(OpjFileHeader));
	}

}OPJFILEHEADER;

//ѵ����������Ϣ(����ʸ����������������������ʱ���õ�)
typedef struct TrainArea_Struct
{
	long lID;        //��¼�����ID
	unsigned char R;  
	unsigned char G; //��¼���������Ӧ��R��G��Bֵ
	unsigned char B;  
	char cClsName[128];
}TRAINAREA;

typedef struct MatchID_Struct
{
	char cClsName[128];
	long lRefID; //����ID
	long lUseID; //���ID
}MATCHID;

typedef struct ClasssInfo_Struct
{
	long   lObjNums;//��¼����Ķ���
	double dMean;   //��¼������������ȵľ�ֵ
	double dStdv;   //��¼������������ȵı�׼��
	double dMin;    //��¼������������ȵ���Сֵ
	double dMax;    //��¼������������ȵ����ֵ
}ClassINFO;

//psq 2011.12.14 add
typedef struct ooRuleOper 
{
	OOOPERNODE OperInfo;
	char       szOrCold[128];		//ÿ��˳�����(���Ϊ1234���������¼)
	char       szOpCold[128];		//���������(��OrCold��һλ),1-and(min); 2-and(*); 3-or(max); 4-mean(arithm.); 5-mean(geo.); 6-not
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

typedef CArray<OCREGPOS, OCREGPOS&> AryObjPos;	// ����λ������
typedef CArray<OCNABOBJ, OCNABOBJ&> AryNabObj;	// �ڽ���������
typedef void*	LPRASTER_ADAPT;					//v7x����

#define MS_SUCCESS						0L
#define MS_FAIL							-1L			// ����δ֪���͵Ĵ���cqh, 20080319

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

//�ڴ����/mem  �������200                    
#define MS_CANNOT_ALLOCMEM						2000001L
#define MS_CANNOT_FREEMEM						2000002L
#define MS_CANNOT_REALLOCMEM					2000003L
#define MS_INVALID_POINTER						2000004L

//��������/other error �������400 
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

//MSI�ļ���ʽ/MSI  �������202
#define MS_BYTEORDER_CANNOT_SUPPORT				2020002L
#define MS_VERSION_CANNOT_SUPPORT				2020003L
#define MS_NO_MORE_DIRECTORY					2020004L
#define MS_DIR_ORDER_ERROR                      2020005L
#define MS_SCALE_EQUAL_ZERO                     2020006L
#define MS_MSIFILE_NEED_UPDATA                  2020007L
//////////////////////////////////////////////////////////////////////////

//{{��ѧ��������
#define  PI		3.14159265358979323846

#define  MIN_FLOAT	(-3.402823E+38)
#define  ZERO_FLOAT (+1.401298E-45)
#define  MAX_FLOAT	(+3.402823E+38)

#define  MIN_DOUBLE		(-1.79769313486232E+307)
#define  MAX_DOUBLE		(+1.79769313486232E+307)
#define  ZERO_MIN_DBL   (-4.94065645841247E-324)
#define  ZERO_MAX_DBL   (+4.94065645841247E-324)
#define  MIN_VALUE		(+1.000000E-20)		    //����ֵС�ڴ�ֵ����Ϊ=0

#define  MIN_INT	-32768
#define  MAX_INT	+32767

#define  MIN_LONG	-2147483648
#define  MAX_LONG   +2147483647
//}}
//////////////////////////////////////////////////////////////////////////
// ͨ��դ��IO����
#define MS_RSDATAIO_FAIL						5010000L	// ͨ��դ�����ݼ�IO�����

//////////////////////////////////////////////////////////////////////////
enum V7X_RAS_CELLTYPE  //��Ԫ����.
{
	V7X_RAS_UNKNOWN = MS_Unknown,
	V7X_RAS_UINT8	= MS_Byte,	    // 8λ�޷�������
	//V7X_RAS_ASCII	= MS_Unknown,   // ��0��β��ASCLL��
	V7X_RAS_UINT16	= MS_UInt16,	// 16λ�޷�������
	V7X_RAS_UINT32	= MS_UInt32,	// 32λ�޷�������
	V7X_RAS_INT8	= MS_Int8,	    // 8λ�з�������
	V7X_RAS_INT16	= MS_Int16,	    // 16λ�з�������
	V7X_RAS_INT32	= MS_Int32,	    // 32λ�з�������
	V7X_RAS_IEEE4	= MS_Float32,	// ���ֽڸ�������
	V7X_RAS_IEEE8  	= MS_Float64,	// ˫���ȸ�������
	V7X_RAS_1BIT    = MS_1Bit       // 1λ��ֵͼ������
};
//////////////////////////////////////////////////////////////////////////

// �궨��
//////////////////////////////////////////////////////////////////////////
#define V7X_RAS_SUCCESS     0L 
#define V7X_RAS_FAIL       -10000000L

//////////////////////////////////////////////////////////////////////////
//��־����ֵ��/NUMBERS_ERROR  �������101
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
#define XCLS_TYPE_SFCLS			30		//��Ҫ����
#define XCLS_TYPE_SFSET			31		//��Ҫ�ؼ�
#define XCLS_TYPE_MGEOMSET		32		//�༯��ʵ�弯
#define XCLS_TYPE_MSPTSET		33		//��ռ�Ԫ�ؼ�
//////////////////////////////////////////////////////////////////////////
#define RAS_SUCCESS 1
#define RAS_FAIL    0
//////////////////////////////////////////////////////////////////////////
//================================================================================
// ����߳�������Ϣ�ṹ..
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
//ϵͳ�����ṹ����
typedef struct
{
	char clib[128];	//���ֿ�Ŀ¼
	char sys[128];	//ϵͳĿ¼
	char cur[128];	//��ǰ����Ŀ¼
	char temp[128];	//��ʱ����Ŀ¼
	char slib[128];	//ϵͳ��Ŀ¼
}GISENV;
//////////////////////////////////////////////////////////////////////////
//��ʶ���Ͷ��壺
typedef long    TYPE_XCLS_ID;  		//XCLS��ʶ
typedef long    TYPE_FCLS_ID;   	//Ҫ�����ʶ
typedef long    TYPE_OCLS_ID;   	//�������ʶ
typedef long    TYPE_ACLS_ID;   	//ע�����ʶ
typedef long    TYPE_RCLS_ID;   	//��ϵ���ʶ
typedef long    TYPE_DCLS_ID;   	//��̬Ҫ�����ʶ
typedef long    TYPE_DRSCLS_ID;   	//�������ʶ
typedef	long	TYPE_TMPL_ID;
typedef long	TYPE_TMPLLIB_ID;
typedef long    TYPE_RULE_ID  ;   	//�����ʶ 
//////////////////////////////////////////////////////////////////////////
#ifndef   _MS_IMAGE_CLASS_BASE_H_
#define   _MS_IMAGE_CLASS_BASE_H_

// AOI������Ϣ�ṹ���� add by cqh
struct AOICELL
{
	long lAoiNo;//AOI���[1,N]
	long lRow;//�к�
	long lCol;//�к�
	double *pBandVal;//��Ԫֵ
};

// ������Ϣ�ṹ���� add by cqh
struct CLASSATTINFO
{
	BYTE	byValue;		// ��Ԫֵ
	BYTE	byName[128];	// ������
	BYTE	byR;			// ��ɫ
	BYTE	byG;
	BYTE	byB;
	BYTE	byDescrip[128];	// ����
};

// �������۽���ṹ
//��ͼ���ȣ�����ȷ�������Ԫ��/�����ʵ�ʵ���Ԫ��
//���徫�ȣ����б���ȷ�������Ԫ��֮��/�ܵ�������Ԫ��
struct CLASSACCURACY
{
	long	lTotal;			//������������
	long	lClassNum;		//�����
	long	**lppErrorMatrix;	//������
	long	*lpColTotal;		//������ÿ1�е��ܺ�
	long	*lpRowTotal;		//������ÿ1�е��ܺ�
	double	*dpAccuracy;		//ÿ����ͼ����
	double	dTotalAccuracy;	//���徫��
	double	dKappa;			// Kappa ϵ��
};

// ������ṹ
struct CLASSSAMPLEPNT	
{
	double	dSx;			// ����
	double	dSy;
	long	lClassNo;		// �����
};
#endif	// end #define   _MS_IMAGE_CLASS_BASE_H_
//////////////////////////////////////////////////////////////////////////
typedef struct LINSTYLE_INFOstruct
{
	short   libID;		  //����	
	long    linstyID;	  //���ͺ�

	char    ovprnt;  	 //���Ƿ�ʽ
	float   outpenw[3];	 //�����ⲿ�ʿ�
	long    outclr[3];	 //�����ɱ���ɫ
	char    headtype;	 //��ͷ����
	char    jointype;    //�ս�����
	char    adjustflg;   //���͵�������       
	char    makemethod;  //�������ɷ������������������͡������Ƶ���������
	float   xscale;		  //Xϵ��
	float   yscale;       //Yϵ��			
}LINSTYLE_INFO,LIN_INFO;
//////////////////////////////////////////////////////////////////////////
//===================����ͼ��ͼ�β����ṹ��
//ͼ�����ӻ���Ҫ���ǵ����⣺
//1.	ͼ������ת��
//2.	�����ߵ����
//3.	�����γɶ���,��ʯɽ��ͼ��
typedef struct PATTERN_INFOstruct
{
	short  libID;		 //����
	long   patID;	 	 //���ű��
	char   ovprnt;		 //���Ƿ�ʽ
	short  fillmode;     //���ģʽ��  0��ͨ����ɫ��䣬1��8�ֱ��ʾ8���򽥱���䣬
	long   fillclr;	     //�������ɫ���������ʱΪ��ʼɫ
	long   endclr;		 //�������ɫ���������ʱ�Ľ���ɫ

	float   pathei;	       //ͼ����
	float   patwid;	       //ͼ����
	float   ang;	       //ͼ���Ƕ�
	long    patclr;	       //ͼ����ɫ��ͼ����ɫ�̶�����ʹ�������ʱҲ���䡣
	float   outpenw;       //ͼ���ʿ�
	char    fullpatflg;    //�Ƿ���Ҫ����ͼ�����
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
//���Ƶ�ṹ
typedef struct
{
	char        *pszId;		// Ψһ��ʶID����Ϊ��������
	char        *pszInfo;	// ���Ƶ�������Ϣ����Ϊ"" 
	double      dfGCPPixel;	// ���Ƶ�ͼ������X
	double      dfGCPLine;	// ���Ƶ�ͼ������Y
	double      dfGCPX;		// ���Ƶ����ο�����X
	double      dfGCPY;		// ���Ƶ����ο�����Y
	double      dfGCPZ;		// ���Ƶ�߳�ֵ����0����δ֪
	char		bIsInUse;	// ʹ�ñ�־λ��Gw20061218��ӣ���ͬ��ԭ��MSI�ļ��е�UseOnoff��־
#ifndef WIN32   //Linux-2010.5.19
	long		invalidlinux;
#endif
} MSRS_GCP;
//////////////////////////////////////////////////////////////////////////
#define MAX_FLD_NAME_LEN 	20	//����ֶ�������(VFOXPRO����ֶ�������)
#define FLD_NAME_LEN		MAX_FLD_NAME_LEN
#define MAX_OWNER_LEN 		30	//�������������
#define MAX_USER_LEN		MAX_OWNER_LEN	//����û�������
#define MAX_PSW_LEN			64	//�������
//////////////////////////////////////////////////////////////////////////
#define MAX_SVR_NAME_LEN    64	//�����������Ƴ���(����������)
#define MAX_DB_NAME_LEN     32  //������ݿ����Ƴ���(����������)
#define MAX_GDB_NAME_LEN	64  //���������ݿ����Ƴ���(����������)
#define MAX_XCLS_NAME_LEN   128 //���XCLS���Ƴ���(����������)
#define MAX_DS_NAME_LEN	    128	//������ݼ�������
#define MAX_VER_NAME_LEN    128 //���汾������(����������)
#define MAX_HDF_PATH_LEN    256 //������ݿ�������(����������)
//////////////////////////////////////////////////////////////////////////
const char MS_RSCOMDISPINFO_FILE10[64]="msRSComDispInfoFile1.0";
//////////////////////////////////////////////////////////////////////////
//Ӱ��ɫ������
typedef enum 
{
	MS_Gray=0,					// �Ҷ� (in GDALColorEntry.c1) 
	MS_RGB=1,					// RGB��ɫ��Red, Green, Blue and Alpha in (in c1, c2, c3 and c4)
	MS_CMYK=2,					// CMYK��ɫ��Cyan, Magenta, Yellow and Black (in c1, c2, c3 and c4)
	MS_HLS=3					// HLS��ɫ��Hue, Lightness and Saturation (in c1, c2, and c3)
} MSRSPaletteInterp;
//////////////////////////////////////////////////////////////////////////
// Ӱ����ʾ��Ϣ
typedef struct
{
	char	cDispType;		//ͼ����ʾ��ʽ��1-RGB,2-RGBP,3-GRAY,4-CLASSIFY,0-DEFAULT
	//�μ�RAS_DISPLAYFORM,rasbasedefine.h
	short	nRBandNo;		//R����
	short	nGBandNo;		//G����
	short	nBBandNo;		//B����
}RASImgDispInfo;
//////////////////////////////////////////////////////////////////////////
#endif
