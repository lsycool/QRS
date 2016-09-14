 #ifndef _GD_RASTER_TO_VECTOR_H_
#define _GD_RASTER_TO_VECTOR_H_

#include "myarry.h"		//��̬˳���ڴ�
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

//���ú��������ݵ�����
#define LPRCLINA CMyArray<M_RclLinA>*	//�г��߶ζ�̬�ڴ�
#define LPREG	 CMyArray<M_Reg>*		//�����ݶ�̬�ڴ�

//�ڴ洦�������õ���һЩ��
#define MAX_LINASTEP	50000          //�г��߶��ڴ�������������
#define MAX_REGSTEP		1000		   //�������ڴ������������
#define INIT_LINAMUTI   5			   //��ʼ���߶��ڴ棬����*INIT_LINAMUTI
#define INIT_REGMULTI	50			   //��ʼ�����ڴ棬�߶���/INIT_REGMULTI

//�Լ������һЩ�쳣��
#define OPEN_MSI_ERR	100			//��ͼ���ļ�����
#define COPY_MSI_ERR    101			//����ͼ���ļ�����
#define READ_LINE_ERR   102			//��ȡͼ������Ϣ����
#define READ_COL_ERR	103         //��ȡͼ������Ϣ����
#define NOTMSI_ERR		104			//ͼ���ļ�������
#define NEW_REG_ERR     105			//�½���������ʧ��
#define TRANS_ERR		106			//����ת���ṹʧ��
#define BANDS_ERR       107         //ͼ��Ĳ�����������Χ
#define CELL_ERR        108			//��Ԫ���ʹ���
#define REGAI_TYPE_ERR  109			//���ݽ����������������ʹ���
#define ALLOC_MEM_ERR   110         //�ڴ�������

typedef struct CLASSATTINFO MSCLASSATTINFO;

//�õ������ݽṹ����ԭ�������ݽṹ�����������޸�
typedef	struct 						//�߶��ļ���Ԫ
{
    //unsigned short  wCla;				//�Ҷ�(ԭ����1�ֽ�)
    //unsigned char	  byDel;			//ɾ�����
    //unsigned short  wLine;			//�к�(���֧��65536)
    //unsigned short  wFrom,wTo;		//��ֹ��
    //long			  lRegNo;			//���߶��������������ļ������

	//wyz-2012.6.18�޸�ԭ������֧�ֵ��������ͣ�Ŀǰ����65535������
	unsigned long  wCla;				//�Ҷ�(ԭ����1�ֽ�)
	unsigned char	  byDel;			//ɾ�����
	unsigned long  wLine;			//�к�(���֧��65536)
	unsigned long  wFrom,wTo;		//��ֹ��
	long			  lRegNo;			//���߶��������������ļ������
} M_RclLinA;//21�ֽ�

typedef	struct 						//����ļ���Ԫ
{
    //unsigned short  wCla;				//�Ҷ�(ԭ����1���ֽ�)
    //unsigned char	  byDel;			//ɾ�����
    //long			  lTotalNum;		//���������
    //long			  lRclLinNo;		//���ɱ������߶����߶��ļ��еĵ�ַ
    //long            lRclLinNum;		//���ɱ������߶�����
    //long			  lBiggestMateReg;	//�뱾��������������

	//wyz-2012.6.18�޸�ԭ������֧�ֵ��������ͣ�Ŀǰ����65535������
	unsigned long  wCla;				//�Ҷ�(ԭ����1���ֽ�)
	unsigned char	  byDel;			//ɾ�����
	long			  lTotalNum;		//���������
	long			  lRclLinNo;		//���ɱ������߶����߶��ļ��еĵ�ַ
	long            lRclLinNum;		//���ɱ������߶�����
	long			  lBiggestMateReg;	//�뱾��������������
} M_Reg;//35�ֽ�

typedef	struct 						//�г����ļ���Ԫ 
{ 
    //unsigned short  wCla;				//�Ҷ�
    //unsigned short  wLine;			//��
    //unsigned short  wFrom,wTo;		//��ֹ��

	//wyz-2012.6.18�޸�ԭ������֧�ֵ��������ͣ�Ŀǰ����65535������
	unsigned long  wCla;				//�Ҷ�
	unsigned long  wLine;			//��
	unsigned long  wFrom,wTo;		//��ֹ��
} M_RclLin;//12�ֽ�

//��־==0��ʾ��Ӧλ����դ�����ݣ�������ȫ��==0�����Ǳ߽����ݣ�������һ��1�ſ�����
//�߽����ݣ��������������ȡ���߽�դ���
typedef struct
{
    //short		nX;
    //short		nY;			//��������
    //BYTE       e0:2;		//��߸���
    //BYTE       e1:2;		//��һ��ɨ����
    //BYTE       e2:2;		//�ұ߸���
    //BYTE       e3:2;		//��һ��ɨ����

	//wyz-2012.6.18�޸�ԭ������֧�ֵ��������ͣ�Ŀǰ����65535������
	 long		nX;
	 long		nY;			//��������
	BYTE       e0:2;		//��߸���
	BYTE       e1:2;		//��һ��ɨ����
	BYTE       e2:2;		//�ұ߸���
	BYTE       e3:2;		//��һ��ɨ����
}MSI_POINT;

//�߽��ı�������
typedef struct
{
    //short nX;
    //short nY;
    //BYTE  byNod;	//�Ƿ��ǽ�� 1/0 ���/�յ�

	//wyz-2012.6.18�޸�ԭ������֧�ֵ��������ͣ�Ŀǰ����65535������
	 long nX;
	 long nY;
	BYTE  byNod;	//�Ƿ��ǽ�� 1/0 ���/�յ�
}EDGE_POINT;

typedef struct
{
	char   fieldname[MAX_FLD_NAME_LEN];	//�ֶ�����
	int	   fieldtype;		//�ֶ�����
	long   fieldoffset;		//�ֶ�ƫ��
	short  fieldlength;		//�ֶ��ֽڳ���
	short  msk_leng;		//�ֶ��ַ�����
	char   point_leng;		//С��λ��
	short  edit_enable;		//�༭ʹ�ܱ�־(0/1/2=����/��/��ֹ)
	char   pt_flg;          //��ӡ��־
	short  ptc_pos;		    //�ֶ���ţ�����Ϊ0,1,2...
	unsigned long wCla;		//�Ҷ�
	//�������Խṹʱ�����ֶ����Ϊԭ�ֶ����(>=0)��
	//    ���ֶ���ű���Ϊ-1,�������Խṹ֮��
	//    �����ֶ���ű�����������������Ϊ0,1,2...

	char   isInherited;     //�ֶ��Ƿ�̳б�־    2004-06-03
	// 1/0 - �̳и�����ֶ�/������ֶ�(�������м̳й�ϵ��������)
}CFIELD_HEAD;

typedef struct
{
//	short  	numbfield;    //�ֶ���
	vector<CFIELD_HEAD>	STRU;//�����ֶ�
}CATT_STRU;

typedef struct
{
//	short  	numbfield;    //�ֶ���
	CFIELD_HEAD	STRU;//�����ֶ�
}RECORD;//һ����¼

//�����ͼ��������4����־������˵������ͼ��������⣩
//            1 
//        --------
//        |      |
//       0|  Cur |2 
//        |      |
//        --------
//            3

//ת������
class CRasToVect
{
public:
    CRasToVect();
    ~CRasToVect();
public:
    char		    m_ReRasName[MAX_PATH];    //�м�դ��������.
    char            m_OutFClsName[MAX_XCLS_NAME_LEN];  //���Ҫ������.
//  CGDataBase     *m_pReRasGDB;            //�м�դ�����ݱ�������ݿ�.
 // CGDataBase     *m_pOutGDB;              //���Ҫ���ౣ������ݿ�.
//	CFeatureCls    *m_pOutFCls;             //�����Ҫ����.  
//	CSFeatureCls   *m_pOutSFCls;			//��Ҫ����
	int				IDCount;
	
	OGRLayer	   *poLayer;			 //����һ��ͼ��
	OGRFeature	   *m_pOutFCl;				//�����Ҫ����  
	OGRFeature     *m_pOutSFCl;			//��Ҫ����
	OGRSFDriver *poDriver;
	OGRDataSource *poDS; //�����ļ�  

    BOOL            m_bRasIsOut;		    //ԭʼͼ���Ƿ������洫�ݽ�����
    BOOL            m_IsGenTempRas;         //�Ƿ������ʱӰ��.
//  TempGDBInfoStrcT  m_TempGDBInfo;          //��ʱ���ݿ�.
    RAS_DATASET_ID    m_ReRasDataSetID;       //�м�դ������ID.

    LIN_INFO	    m_linInf;			    //���ε�ȱʡ�߲���
    REG_INFO	    m_regInf;			    //����ȱʡ����

    LPRCLINA	    m_pRclLinA;			//�г��߶������ڴ�
    long		    m_lLinANum;			//�߶ε���Ŀ��������׷�ٵ�ʱ�����÷�Χ
    long		   *m_pLLineIndex;		//�г��߶���������,�����ṩ�е��߶εĲ�ѯ //[LINE+1]
    long			m_lLines;			//ͼ������
    long			m_lLineCells;		//ͼ������
    LPREG			m_pRegArry;			//������(��̬����ģʽ)
    M_Reg		   *m_pReg;				//�����ݣ�ֱ���ڴ淽ʽ
    long			m_lRegNum;			//������Ŀ
    M_RclLin	   *m_pRclLin;		    //����Ϊ�������߶�����
    long			m_lMaxCellNumOfSmallReg;//�ϲ�С����ʱ����������
    BOOL			m_b4Near;
    short			m_lBandNo;			//Ҫת���Ĳ��κ�
    BOOL			m_bMakeTopo;        //2008-6-4��ӣ��Ƿ�������
    
	//20080825��ӣ��Ƿ񽫲�����Ҫ����ת��Ϊ��Ҫ����
	BOOL            m_bGenSFcls;

	// Add By Whp 2010.03.25 ���ӹ⻬���ò�����֧��
	double		m_dSmoothRadius;		//�⻬�뾶
	short		m_nSmoothType;			//�⻬����

	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////Added by psq for Common Test ---08.06.17////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
//	CGDataBase *m_pTempGDB;
	MSRSDatasetH m_hDS;                     //ת����ԭʼӰ��
	MSRSDatasetH m_hReDS;                  //m_pReRasOBJ-���кϲ�֮����µ�ͼ���ļ�
	BOOL         m_bReDSInitCreateCpy;     //����m_hReDS�Ƿ���Ҫ�ڳ�ʼ��������������

	MSRSDatasetH m_hNewDS;                 //m_pNewRasOBJ-�ڽ��н�������жϵ�ʱ���ͼ���ļ�
	CString      m_strReOutType;           //�ϲ�С���Ľ��Ӱ�񱣴����ʹ�
	BOOL         m_bIsReSmall;
	double       m_dTolerence;
	BOOL         m_bSrc7O;

	//��ʶת�������ж�дGetCellValueByBuffer(...)
	//ʱ��ֵ�Ƿ��򣺶���û�е���Χ��ԴӰ��Ҳ��С���ϲ��м䴦��
	//�����д��ֵ������,���ʸ�������µߵ�(PSQ 20090422)
	BOOL         m_bYInvert;  

	// Add By Whp 2010.03.24 ���ӷ����ṹ�壬��¼����Ľṹ����Ϣ
	MSCLASSATTINFO*	m_pClsAtt;
	long			m_lClsNums;
	BYTE*			m_bpszRLut;		//��ɫ���ұ� Add By Whp 2010.03.25
	BYTE*			m_bpszGLut;
	BYTE*			m_bpszBLut;
	long			m_lLutNums;

	double			m_dBandMinVal;
	double			m_dBandMaxVal;

protected:
    long GetRclLinAData();			//�����г��߶�����
    long MergeSmallRegion();		//�ϲ�С��
	long MergeSmallRegionByUpdate(MSRSDatasetH hUpdateRaster,long lRowOff,long lColOff);//���տ���·�ʽ�ϲ�С��
    long GetRegData();				//����������m_pReg,����������;�����г����� m_pRclLin
    virtual long CompareRclLinAndRecodeMaxReg(long *plRegRclLinIndex, long lBegRclLinAInd, long lEndRclLinAInd,
							long lCurLine,long lCurRegNo, unsigned long  wCurCla, unsigned long wCurFrom, unsigned long wCurTo/* unsigned short  wCurCla, WORD wCurFrom, WORD wCurTo*/);
    void GetNewMsi();				//�õ����жϽ�����ʵ�ʱ����ʹ�õ�ͼ��
    BYTE IsNod(LPRASTER_ADAPT ReadAdapter,long nX,long nY);	//��ǰ׷�ٵ��Ƿ��ǽ��
    long TrackRegMaxEdge();			//׷�ٸ���������Ȧ�����
	//����Ҫ����
//    virtual long CreateAPolygon(EDGE_POINT *pPoly,long &lNum,unsigned long wCla,CATT_STRU *pFldStru,short FieldNo);
	//���ɼ�Ҫ����
	long CreateAPolygonToSFCls(EDGE_POINT *pPoly,long &lNum,unsigned long wCla,CATT_STRU *pFldStru,short FieldNo);

    void GetOkPoly(EDGE_POINT *pPoly,long &lNum);
    void MakeTopo();				//���õײ㺯�����ؽ�����
    void DspMyErrMsg(int n);
	
    //һЩ�ڴ洦����
protected:
    void CloseAllDataSet();		//�ر����е����ݼ�.
    void FreeAllMem();			//�ͷ����е��ڴ�
    void FreeLinAMem();			//�ͷ��г��߶�����
    void FreeRegMem();			//�ͷ�����ռ�õ�����
    void FreeLinMem();			//�ͷ�����Ϊ�������߶�����
    void FreeLinAIndexMem();	//�ͷ��߶������ڴ�
    long InitRegMem();			//��ʼ�������ݵ��ڴ�
    long InitLinMem();			//��ʼ������Ϊ�������߶ε��ڴ�
	bool InitLutTbl();			//��ʼ����ɫ���ұ� Add By Whp 2010.03.25

public:
    //����ȱʡ����
    void SetDefGraphInf(const LIN_INFO *linf,const REG_INFO *rinf);

    //����ת�����ļ�(ֱ�Ӹ���դ�����)
	long SetTransFile(MSRSDatasetH hDS,CString strReOutType, const char *pReRasName, const char *pFClsName);

	//���ù⻬���� Add By Whp 2010.03.25
	void SetSmoothOption(double dSmoothRad,short nSmoothType);

    //��һЩ�������г�ʼ��	
    long Init();	            
    //����ת����������
    short Run();
    //����С���ϲ���������
	short Run2();
	short Run3(MSRSDatasetH hUpdateRaster,long lRowOff,long lColOff);//�ֿ����ģʽ

public:
	short ReSaveFcls2SFcls();  //���ڲ������Ҫ�ؽ������Ϊ��Ҫ����
	void GetCellValueByBuffer(LPRASTER_ADAPT ReadAdapter,long row,long col,double &dValue,char *pInvalidFlag = NULL);//zk 2010-7-31
	long att_SetStru(OGRLayer * poLayer,CATT_STRU stru );
	long polygon_Append(OGRPolygon* AnyPolygon,OGRFeature* poFeature,CATT_STRU* stru,RECORD* reco,REG_INFO* m_regInf);
	void cbs2(double *buf_in,double *buf_out,long n);
};

} // End Namespace GDX

#endif