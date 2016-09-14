#ifndef __RAS_BASE_DEFINE_H_     // prevent multiple includes.
#define __RAS_BASE_DEFINE_H_

//˵��:Ϊ������ֲ����,��DLL��������MFC,
//��basDefine70����������NT�Ĳ�������,������¶���(�ο�WinDef.h). 
/////////////////////////////////////////////////////////////////////////////////
#ifndef DWORD
typedef unsigned long DWORD;
#endif

#ifndef WORD
typedef unsigned short WORD;
#endif

#ifndef BYTE
typedef unsigned char BYTE;
#endif

#ifndef BOOL
typedef int BOOL;
#endif

#ifndef GUID_DEFINED
#define GUID_DEFINED
typedef struct _GUID 
{
    DWORD Data1;
    WORD  Data2;
    WORD  Data3;
    BYTE  Data4[8];
} GUID;
#endif // !GUID_DEFINED

/////////////////////////////////////////////////////////////////////////////////

#ifndef MAX_USER_LEN
//#define MAX_USER_LEN	30	//����û�������
#define MAX_PSW_LEN	64	//�������
#endif

#ifndef RAS_DATASET_ID
typedef long RAS_DATASET_ID;
#endif

#ifndef RAS_CATALOG_ID
typedef long RAS_CATALOG_ID;
#endif

///////////////////////դ�������������ͷ�Χ//////////////////////////////////////////

#define  RAS_MIN_BYTE    0 
#define  RAS_MAX_BYTE    255 

#define  RAS_MIN_WORD    0
#define  RAS_MAX_WORD    65535

#define  RAS_MIN_DWORD   0
#define  RAS_MAX_DWORD   4294967295

#define  RAS_MIN_CHAR    -128
#define  RAS_MAX_CHAR     127

#define  RAS_MIN_SHORT   -32768
#define  RAS_MAX_SHORT    32767

#define  RAS_MIN_LONG    -2147483640.8F  //-2147483648
#define  RAS_MAX_LONG     2147483640.8F  //2147483647 

#define  RAS_MIN_FLOAT   -3.402823466e+38F
#define  RAS_MAX_FLOAT    3.402823466e+38F

#define  RAS_MIN_DOUBLE  -1.7976931348623e+308
#define  RAS_MAX_DOUBLE   1.7976931348623e+308

#define  RAS_MIN_1BIT     0
#define  RAS_MAX_1BIT     1

#define  RAS_MAX_FLOAT10  3.402823466e+37F


////////////////////////////դ�������Ϣ����////////////////////////////////////////

enum RAS_BYTEORDER  //�ֽ�˳��. 
{
	RAS_INTEL      = 0,  //"IIII",���ֽ��������λ������ǰ(�Ͷ�).
	RAS_MOTOROLA   = 1,  //"MMMM",���ֽ��������λ�����ں�(�߶�).
};

enum RAS_IMAGETYPE  //ͼ������.
{
	RAS_DEM    = 0,
	RAS_IMAGE  = 1,
};

enum RAS_BANDINFO  //ͼ�񲨶ν�����Ϣ.
{
	RAS_BAI_MIN                = 0L,
	RAS_BAI_2VALUEMULTIBANDS   = 0L,	//�ನ�ζ�ֵͼ,�������ι�����ͬ�Ķ�ֵ��ɫ���ұ� 
	RAS_BAI_GRAYMULTIBANDS     = 1L,	//�ನ����������,������ι�����ͬ�Ĳ�ɫ���ұ�  
	RAS_BAI_RGB                = 2L,	//RGB ��ɫģ��--���������ε�RGB���ɫͼ,��ɫ���ұ�������ʾ�������ε�����  
	RAS_BAI_RGBP               = 3L,	//RGBP��ɫģ��--�����Ĳ��ε�RGBP͸�����ɫ����ͼ,��ɫ���ұ�������ʾ�������ε�����
	RAS_BAI_COLORLUT           = 4L,	//��ɫ���ұ�ͼ��--���ڵ����ε�256ɫͼ��64K�߲�ͼ
	RAS_BAI_COMPLEXDATA        = 5L,	//��������--���������ε�FFT�任��������,�������ι�����ͬ�Ĳ�ɫ���ұ� 
	RAS_BAI_MAX                = 5L,
};

enum RAS_CELLTYPE  //��Ԫ����.
{
	RAS_UINT8	= 0,	// 8λ�޷�������
	RAS_ASCII	= 1,	// ��0��β��ASCLL��
	RAS_UINT16	= 2,	// 16λ�޷�������
	RAS_UINT32	= 3,	// 32λ�޷�������
	RAS_INT8	= 4,	// 8λ�з�������
	RAS_INT16	= 5,	// 16λ�з�������
	RAS_INT32	= 6,	// 32λ�з�������
	RAS_IEEE4	= 7,	// ���ֽڸ�������
	RAS_IEEE8   	= 8,	// ˫���ȸ�������
	RAS_1BIT        = 9,    // 1λ��ֵͼ������
};

//��Ӧ��Ԫ��������������ռ��BITλ��:
#define   RAS_CT_1BIT_BITSIZE           1L     //1λ�Ķ�ֵͼ
#define   RAS_CT_UINT8_BITSIZE    	8L     //8λ�޷�������
#define   RAS_CT_UINT16_BITSIZE    	16L    //16λ�޷�������
#define   RAS_CT_UINT32_BITSIZE    	32L    //32λ�޷�������
#define   RAS_CT_INT8_BITSIZE      	8L     //8λ�з�������
#define   RAS_CT_INT16_BITSIZE  	16L    //16λ�з�������
#define   RAS_CT_INT32_BITSIZE     	32L    //32λ�з�������
#define   RAS_CT_IEEE4_BITSIZE     	32L    //���ֽڸ�������
#define   RAS_CT_IEEE8_BITSIZE  	64L    //˫���ȸ�������

enum RAS_SENSORTYPE  //����������.
{
	RAS_SENSOR_UNKNOW	= 0L,
	RAS_SENSOR_SPOT		= 1L,
	RAS_SENSOR_TM		= 2L,
	RAS_SENSOR_DEFAULT	= RAS_SENSOR_UNKNOW,    //ȱʡ.
};

enum RAS_COMPRESSTYPE //����ѹ������.
{
	RAS_COMPRESSION_NO 		= 0L,	  
	RAS_COMPRESSION_RCL_HUMAN	= 1L,	  // �г̹���������
	RAS_COMPRESSION_DPCM_HUMAN	= 2L,	  // ��ֹ���������
	RAS_COMPRESSION_JPEGMSI		= 3L,	  // JPEG��ʽ����
	RAS_COMPRESSION_2VALUE_RCL_HUMAN= 4L,	  // 2ֵ�г̱���
	RAS_COMPRESSION_DEFLATE_ADOBE	= 5L,	  // ADOBE֮DEFLATE����.
	RAS_COMPRESSION_ZIP             = 6L,     // ZIPѹ��.
	RAS_COMPRESSION_DEFAULT	        = RAS_COMPRESSION_NO,  //ȱʡ.
};

///////////////////////////դ����չ��Ϣ����///////////////////////////////////////////

enum RASTER_EXTEND_ITEM
{
    RASTAG_BANDSNOTEINFO            =  0L,    //��������ע����Ϣ          
    RASTAG_BANDSNOTEINFOLENGTH      =  1L,    //��������ע����Ϣ�Ĵ�С
	
 	RASTAG_COLORLUT				    =  2L,    //��ɫ���ұ�
	
	//ͼ��������豸����Ĳ���
    RASTAG_XRESOLUTION			    =  3L,    //��Ԫ�з���(X)�ֱ���
	RASTAG_YRESOLUTION			    =  4L,    //��Ԫ�з���(Y)�ֱ���
	RASTAG_RESOLUTIONUNIT		    =  5L,    //�ֱ��ʵ�λ.   
	
	RASTAG_DOCUMENTNAME			    =  6L,    //ͼ���ļ��� 
	RASTAG_IMAGEDESCRIPTION		    =  7L,    //ͼ��������Ϣ
	RASTAG_SOFTWARE				    =  8L,    //����ͼ������
	RASTAG_DATETIME				    =  9L,    //����ͼ������ں�ʱ��
	RASTAG_ARTIST   			    = 10L,    //����ͼ�������
	RASTAG_HOSTCOMPUTER		        = 11L,    //����ͼ�������
	
	//��չ��־--����ͼ����ʾ������ϵͳ��ͼ�����������У����ͼ����Ƕ��.
	RASTAG_DISPLAYFORM              = 12L,    //ͼ�����ʾ��ʽ
	RASTAG_DISPLAYFORMCEFF          = 13L,    //ͼ�����ʾ��ʽ�Ĳ���
	RASTAG_DISPLAYPROCESSFORM       = 14L,    //��ʾͼ��Ĵ���ʽ
	RASTAG_DISPLAYPROCESSFORMCEFF   = 15L,    //��ʾͼ��Ĵ���ʽ�Ĳ���
	RASTAG_ISSUPPORTPROJECTION      = 16L,    //�Ƿ�֧��ͶӰ�任
	RASTAG_PROJECTIONCEFF           = 17L,    //��ǰͶӰ����(ͶӰ����ϵ,ͶӰ����)
	RASTAG_COORDINATESYSTYPE        = 18L,    //����ϵͳ
	RASTAG_COORDINATEUNIT           = 19L,    //���굥λ
	RASTAG_HWTOCOFORM               = 20L,	  //�������任��ʽ
	
	//FFT�任ר�õ�������־.
	RASTAG_FFTSCELLTYPE		        = 21L,
	RASTAG_FFTSLINES				= 22L,
	RASTAG_FFTSLINECELLS			= 23L,
	
	//��־ͼ���Ӧ�����(��һЩӦ�ÿ����������汾��ͼ��).
	RASTAG_DATA_USE_FORM			= 24L,	  //����֧��һЩֻ������ʾЧ����Ӧ�ã����ѹ���ȣ���INTERNET�Ĳ�ѯ��
	
	//ȫ��ͳ����Ϣ
	RASTAG_RESAMPLE_STEP			= 25L,	  //��������,ȱʡΪ1.
	
	//��Ԫ���ű���.
	RASTAG_X_SCALE				    = 26L,	  //��ԪX��������ű���.
	RASTAG_Y_SCALE				    = 27L,	  //��ԪY��������ű���.
	RASTAG_Z_SCALE				    = 28L,	  //��ԪZ��������ű���.
	//(���ø̵߳ķŴ���,ʹ�߳����ݿ��������ͷ�ʽ����,��߳̾��Ⱦ�ȷ������,�̵߳ķŴ���Ϊ100)
	
	//MAP_INFO���Ͻǵ�ͼ������(��֧��ͶӰ��,������Ƕ)
	RASTAG_X0_COORDAINTION		    = 29L,	  //����X��ԭ��
	RASTAG_Y0_COORDAINTION		    = 30L,	  //����Y��ԭ��
	RASTAG_Z0_COORDAINTION		    = 31L,	  //����Z(�߳�)��ԭ��
	
	RASTAG_Z_UNIT				    = 32L,	  //�������굥λ(DEM���̣߳���)

	RASTAG_COLORLUTNAME				= 33L,    //��ɫ���ұ�����
	
	//////////////////////////////////////////////////////////////
	//����֮ǰ�����¼���ı�־
	//////////////////////////////////////////////////////////////
};

//��չ��Ϣ��صĸ����.

//��������ͼ��Ĳ�����.
#define  RAS_BAND_NUM_MIN				 1L      //��С������
#define  RAS_COLORLUT_BAND_NUM			 1L	     //�����ε�256ɫͼ��64K�߲�ͼ
#define  RAS_COMPLEXDATA_BAND_NUM		 2L	     //���������ε�FFT�任��������
#define  RAS_RGB_BAND_NUM				 3L	     //�����ε�RGB���ɫͼ
#define  RAS_RGBP_BAND_NUM				 4L	     //�Ĳ��ε�RGBP͸�����ɫ����ͼ
#define  RAS_BAND_NUM_MAX				 1024L	 //��󲨶���

//��������ע����Ϣ����.
#define  RAS_BANDSNOTEINFO_NUM_MIN       RAS_BAND_NUM_MIN  
#define  RAS_BANDSNOTEINFO_NUM_MAX       RAS_BAND_NUM_MAX

//��������ע����Ϣ�ĳ���.
#define  RAS_BANDSNOTEINFO_LEN_MIN       0L		 //��С����.
#define  RAS_BANDSNOTEINFO_LEN_MAX       65536L  //��󳤶�.
#define  RAS_BANDSNOTEINFO_LEN_DEFAULT   256L    //ȱʡ����.

//��������ͼ��Ĳ�ɫ���ұ�ĳ���.
#define  RAS_CLUT_RGBINDEX_NUM           3L
#define  RAS_CLUT_NUMS_MIN               2L      //��С����.
#define  RAS_CLUT_NUMS_1BIT              2L
#define  RAS_CLUT_NUMS_UINT8             256L
#define  RAS_CLUT_NUMS_UINT16            65536L
#define  RAS_CLUT_NUMS_UINT32            65536L
#define  RAS_CLUT_NUMS_INT8              256L
#define  RAS_CLUT_NUMS_INT16             65536L
#define  RAS_CLUT_NUMS_INT32             65536L
#define  RAS_CLUT_NUMS_IEEE4             65536L
#define  RAS_CLUT_NUMS_IEEE8             65536L
#define  RAS_CLUT_NUMS_MAX               65536L  //��󳤶�.

//ȱʡͼ��ֱ���.
#define  RAS_DEFAULT_RESOLUTION          (double)72.00 

//��Ԫ�ֱ��ʵĵ�λ(Ŀǰ��ʱ�Զ���,�Ժ�ʹ��MAPGIS�ж���)
#define  RAS_RU_MIN                      1L  
#define	 RAS_RU_NONE				     1L		 //�޵�λ
#define	 RAS_RU_INCH		 			 2L		 //Ӣ��
#define	 RAS_RU_CENTIMETER			     3L		 //����
#define  RAS_RU_DEFAULT				     RAS_RU_INCH
#define  RAS_RU_MAX                      3L

//ͼ���ļ�������. 
#define  RAS_DNAME_LEN_MIN			     0L      //��С����.
#define  RAS_DNAME_LEN_MAX			     256L	 //��󳤶�.
#define  RAS_DNAME_LEN_DEFAULT		     256L    //ȱʡ����.

//ͼ��������Ϣ����.
#define  RAS_IMGSCR_LEN_MIN			     0L      //��С����.
#define  RAS_IMGSCR_LEN_MAX			     256L	 //��󳤶�.
#define  RAS_IMGSCR_LEN_DEFAULT		     256L    //ȱʡ����.

//����ͼ������������.
#define  RAS_SOFTWARE_LEN_MIN		     0L      //��С����.
#define  RAS_SOFTWARE_LEN_MAX		     256L	 //��󳤶�.
#define  RAS_SOFTWARE_LEN_DEFAULT	     256L    //ȱʡ����.

//����ͼ������ں�ʱ�䳤��.
#define  RAS_DATETIME_LEN_MIN		     0L      //��С����.
#define  RAS_DATETIME_LEN_MAX		     256L	 //��󳤶�.
#define  RAS_DATETIME_LEN_DEFAULT	     256L    //ȱʡ����.

//����ͼ�������������.
#define  RAS_ARTIST_LEN_MIN			     0L      //��С����.
#define  RAS_ARTIST_LEN_MAX			     256L	 //��󳤶�.
#define  RAS_ARTIST_LEN_DEFAULT		     256L    //ȱʡ����.

//����ͼ�������������.
#define  RAS_HOSTCOMPUTER_LEN_MIN        0L      //��С����.
#define  RAS_HOSTCOMPUTER_LEN_MAX        256L	 //��󳤶�. 
#define  RAS_HOSTCOMPUTER_LEN_DEFAULT    256L    //ȱʡ����.

//ͼ�����ʾ��ʽ.
enum RAS_DISPLAYFORM
{
	RAS_DISPLAYFORM_DEFAULT     =    0L,	 //ȱʡ����ʾ��ʽ
	RAS_DISPLAYFORM_RGB         =    1L,	 //RGB��ʾ��ʽ(Ӱ��)
	RAS_DISPLAYFORM_RGBP        =    2L,	 //RGBP��ʾ��ʽ(Ӱ��)
	RAS_DISPLAYFORM_GRAY        =    3L,	 //�Ҷ���ʾ��ʽ(Dem��Ӱ��)
	RAS_DISPLAYFORM_CLASSIFY    =    4L,     //������ʾ��ʽ(Dem)
};

//ͼ����ʾ�Ĵ���ʽ.
enum RAS_DISPLAYPROCESSFORM
{
	RAS_DISPLAYPROCESSFORM_DEFAULT   =   0L,     //ȱʡ����ʾͼ��Ĵ���ʽ��ԭ������ʾ
//	RAS_DISPLAYPROCESSFORM_NOCL      =   1L,     //������
	RAS_DISPLAYPROCESSFORM_ZSY       =   1L,     //����Ӧ��ʾ
	RAS_DISPLAYPROCESSFORM_JHH       =   2L,     //���⻯
	RAS_DISPLAYPROCESSFORM_ZGH       =   3L,     //���滯
	RAS_DISPLAYPROCESSFORM_XXLS      =   4L,     //��������
	RAS_DISPLAYPROCESSFORM_ZSBH	 =   5L,     //ָ���任
	RAS_DISPLAYPROCESSFORM_DSBH      =   6L,     //�����任
	RAS_DISPLAYPROCESSFORM_FDXX      =   7L,     //�ֶ�����
	RAS_DISPLAYPROCESSFORM_GDH       =   8L,     //�涨��
	RAS_DISPLAYPROCESSFORM_FZ   	 =   9L,     //��ת��ʾ
}; 


//�Ƿ�֧��ͶӰ�任.
#define  RAS_PROJECTION_NOSUPPORT        0L      //��֧��ͶӰ�任,ȱʡ��֧��ͶӰ�任
#define  RAS_PROJECTION_SUPPORT          1L      //֧��ͶӰ,���Խ�һ����ͶӰ�任


//����ϵͳ(�Ժ��ʹ��MAPGIS�ж���).
enum RAS_COORDINATESYSTYPE
{
	RAS_COORDINATETYPE_NOCOORDINATE   =   0L,    //������
	RAS_COORDINATETYPE_HWCOORDINATE   =   1L,    //ͼ����������
	RAS_COORDINATETYPE_ZJCOORDINATE   =   2L,    //ֱ������(��,��),��Ҫ���Ƶ���Ϣ�ͱ任����ʽ����Ϣ
	RAS_COORDINATETYPE_GEOCOORDINATE  =   3L,    //��������(��γ��),��Ҫ���Ƶ���Ϣ�ͱ任����ʽ����Ϣ
	//����ͼ����MAPGIS��ͼ�εĵ�����ʾ
	RAS_COORDINATETYPE_MAPGISCOORDINATE = 12L,   //MAPGIS��ͼֽ����(����Ϊ���ף��ף�����...),��Ҫ���Ƶ���Ϣ�ͱ任����ʽ����Ϣ
	//�ر�˵��:
	//������ϵͳΪRAS_COORDINATETYPE_ZJCOORDINATE��RAS_COORDINATETYPE_MAPGISCOORDINATE��RAS_COORDINATETYPE_GEOCOORDINATEʱ,
	//���б�־�������: RASTAG_COORDINATEUNIT��RASTAG_HWTOCOFORM��RASTAG_CONTRAL_POINT_FILE.
};

//����ϵͳ����.
enum RAS_COORDSYSTYPE           
{
	RAS_IMG_COORDINATESYSTYPE       =     0L,    //ͼ��ʽ.
	RAS_MAP_COORDINATESYSTYPE       =     1L,    //ͼ�η�ʽ.
};

//���굥λ(�Ժ��ʹ��MAPGIS�ж���).
enum RAS_COORDINATEUNIT
{
	RAS_COORDINATEUNIT_NOUNITS      =	 0L,	 //�޵�λ
	RAS_COORDINATEUNIT_PIXELS       =	 1L,	 //��Ԫ
	RAS_COORDINATEUNIT_INCHUNITS    =	 2L,	 //Ӣ��
	RAS_COORDINATEUNIT_MMUNITS      =	 3L,	 //����
	RAS_COORDINATEUNIT_CMUNITS      =	 4L,	 //����
	RAS_COORDINATEUNIT_MIUNITS      =	 5L,	 //��
	RAS_COORDINATEUNIT_KMUNITS      =	 6L,	 //����
	RAS_COORDINATEUNIT_DDMMSS       =	 7L,	 //�ȷ���,����DDDMMSS.SSSS��ʽ
	RAS_COORDINATEUNIT_DD           =	 8L,	 //��
	RAS_COORDINATEUNIT_MM           =	 9L,	 //��
	RAS_COORDINATEUNIT_SS           =	 10L,	 //��
	RAS_COORDINATEUNIT_RADIAN       =	 11L,	 //����
	//����ͼ����MAPGIS��ͼ�εĵ�����ʾ
	RAS_COORDINATEUNIT_MAPGISUNITS  =	 12L,	 //MAPGIS��ͼֽ��λ����(����Ϊ���ף��ף�����...)
	RAS_COORDINATEUNIT_FOOT		    =	 13L,	 //Ӣ��
	RAS_COORDINATEUNIT_YARD		    =	 14L,	 //��
	RAS_COORDINATEUNIT_SEAMAIL	    =	 15L,	 //����
	RAS_COORDINATEUNIT_MAIL			=	 16L,	 //Ӣ��
};

//�������任��ʽ.
enum RAS_HWTOCOFORM
{
	RAS_HWTOCOFORM_NOCONVERT        =    0L,     //�ޱ任
	RAS_HWTOCOFORM_1CONVERT         =    1L,	 //һ������
	RAS_HWTOCOFORM_2CONVERT         =    2L,	 //���ζ���ʽ
	RAS_HWTOCOFORM_3CONVERT         =    3L,	 //���ζ���ʽ
	RAS_HWTOCOFORM_4CONVERT         =    4L,	 //�Ĵζ���ʽ
	RAS_HWTOCOFORM_5CONVERT         =    5L,	 //��ζ���ʽ
};

//ͼ���Ӧ�����.
#define  RAS_HIGH_QUALITY_FORM		     0L	     //������Ӧ��.
#define  RAS_VIEW_QUALITY_FORM			 1L	     //��ʾ������Ӧ��.
#define  RAS_QUALITY_FORM_DEFAULT		 RAS_HIGH_QUALITY_FORM	

//�������굥λ(�Ժ��ʹ��MAPGIS�ж���)
enum RAS_ZUNIT
{
	RAS_Z_UNIT_NOUNITS			    =     0L,    //�޵�λ
	RAS_Z_UNIT_INCHUNITS            =	  1L,    //Ӣ��
	RAS_Z_UNIT_MMUNITS              =	  2L,    //����
	RAS_Z_UNIT_CMUNITS              =	  3L,    //����
	RAS_Z_UNIT_MIUNITS              =	  4L,    //��
	RAS_Z_UNIT_KMUNITS              =	  5L,    //����
};

//դ���ز�����ʽ.
enum RAS_RESAMPLETYPE
{
	RAS_RSP_NearestNeighbor			=	  0L,    //���ڽ�.
	RAS_RSP_BilinearInterpolation	=     1L,    //˫����.
	RAS_RSP_CubicConvolution		=     2L,    //˫����. 
};


////////////////////////////դ��Ŀ¼������Ϣ����//////////////////////////////////////

enum RAS_SERVERTYPE  //���ݿ����������.
{
	NULL_TYPE   = 0, 
	_ORACLE     = 1,
	_SQL_SERVER = 2,
	_IBM_DB2    = 3,
	_SYBASE     = 4,
	_INFORMIX   = 5,
	_MYSQL      = 6,
	_DM_DB		= 7,
	//������...
};

enum RAS_ITEM_TYPE  //Ŀ¼��Ŀ����.
{
	LOCAL_FILE     = 0,  //�����ļ�.
	LOCAL_DATASET  = 1,  //�������ݼ�.
	REMOTE_DATASET = 2,  //���ݿ������ݼ�.
};

//struct RAS_SDE_CONNECTINFO   //SDE������Ϣ.
//{
//	RAS_SERVERTYPE ServerType;               //����������Ϣ.
//	char           DataSource[128];
//	char           UserName[MAX_USER_LEN];
//	char           Password[MAX_PSW_LEN];
//	char           GDBName[MAX_DB_NAME_LEN]; //�������ݿ���. 
//};

//struct RASTER_CATALOG_ITEM   //դ��Ŀ¼��Ŀ.
//{
//	char                  RasterName[256]; //դ��������.
//	RAS_SDE_CONNECTINFO   SDEConnectInfo;  //դ������������Ϣ.
//	RAS_ITEM_TYPE         ItemType;        //դ����������.
//};

//wyz-2010.02.04-դ�����ݼ�������Ϣ�ṹ��
//typedef struct tagRasGDBInfoStrcT
//{
//	//������Ϣ.
//	char			ServerName[MAX_SVR_NAME_LEN];
//	char			LogName[MAX_USER_LEN];
//	char			Password[MAX_PSW_LEN];
//	//�����������ݿ���Ϣ
//	char			GDBName[MAX_GDB_NAME_LEN];
//	long			GDB_ID;
//
//	tagRasGDBInfoStrcT()
//	{
//		memset(ServerName,0,MAX_SVR_NAME_LEN*sizeof(char));
//		memset(LogName,0,MAX_USER_LEN*sizeof(char));
//		memset(Password,0,MAX_PSW_LEN*sizeof(char));
//		memset(GDBName,0,MAX_GDB_NAME_LEN*sizeof(char));
//		GDB_ID=0;
//	}
//
//}RasGDBInfoStrcT;


//դ�����ݼ�/Ŀ¼��Ϣ.
//typedef struct tagRasDataInfoStrcT
//{
//	RasGDBInfoStrcT	RasGDBInfo;
//	//դ��������Ϣ
//	char			RasterName[MAX_XCLS_NAME_LEN];    //դ��������.
//	long			RasterID;							//դ�����ݼ�ID.
//
//	tagRasDataInfoStrcT()
//	{
//		memset(RasterName,0,MAX_XCLS_NAME_LEN*sizeof(char));
//		RasterID=0;
//	}
//
//}RasDataInfoStrcT;
//struct SystemConfigInfo
//{
//	RasGDBInfoStrcT TempGDBInfo;
//	//������...
//};

#endif