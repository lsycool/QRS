#ifndef __RAS_BASE_DEFINE_H_     // prevent multiple includes.
#define __RAS_BASE_DEFINE_H_

//说明:为方便移植编译,该DLL不依赖于MFC,
//但basDefine70中有依赖于NT的部分声明,因此重新定义(参考WinDef.h). 
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
//#define MAX_USER_LEN	30	//最大用户名长度
#define MAX_PSW_LEN	64	//最大口令长度
#endif

#ifndef RAS_DATASET_ID
typedef long RAS_DATASET_ID;
#endif

#ifndef RAS_CATALOG_ID
typedef long RAS_CATALOG_ID;
#endif

///////////////////////栅格所用数据类型范围//////////////////////////////////////////

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


////////////////////////////栅格基本信息定义////////////////////////////////////////

enum RAS_BYTEORDER  //字节顺序. 
{
	RAS_INTEL      = 0,  //"IIII",多字节数据其低位存于在前(低端).
	RAS_MOTOROLA   = 1,  //"MMMM",多字节数据其低位存于在后(高端).
};

enum RAS_IMAGETYPE  //图像类型.
{
	RAS_DEM    = 0,
	RAS_IMAGE  = 1,
};

enum RAS_BANDINFO  //图像波段解释信息.
{
	RAS_BAI_MIN                = 0L,
	RAS_BAI_2VALUEMULTIBANDS   = 0L,	//多波段二值图,各个波段公用相同的二值彩色查找表 
	RAS_BAI_GRAYMULTIBANDS     = 1L,	//多波段有序数据,多个波段公用相同的彩色查找表  
	RAS_BAI_RGB                = 2L,	//RGB 彩色模型--用于三波段的RGB真彩色图,彩色查找表用于显示各个波段的数据  
	RAS_BAI_RGBP               = 3L,	//RGBP彩色模型--用于四波段的RGBP透明真彩色叠加图,彩色查找表用于显示各个波段的数据
	RAS_BAI_COLORLUT           = 4L,	//彩色查找表图像--用于单波段的256色图和64K高彩图
	RAS_BAI_COMPLEXDATA        = 5L,	//复数数据--用于两波段的FFT变换有序数据,两个波段公用相同的彩色查找表 
	RAS_BAI_MAX                = 5L,
};

enum RAS_CELLTYPE  //像元类型.
{
	RAS_UINT8	= 0,	// 8位无符号整数
	RAS_ASCII	= 1,	// 以0结尾的ASCLL串
	RAS_UINT16	= 2,	// 16位无符号整数
	RAS_UINT32	= 3,	// 32位无符号整数
	RAS_INT8	= 4,	// 8位有符号整数
	RAS_INT16	= 5,	// 16位有符号整数
	RAS_INT32	= 6,	// 32位有符号整数
	RAS_IEEE4	= 7,	// 四字节浮点数据
	RAS_IEEE8   	= 8,	// 双精度浮点数据
	RAS_1BIT        = 9,    // 1位二值图的数据
};

//对应像元类型数据类型所占的BIT位数:
#define   RAS_CT_1BIT_BITSIZE           1L     //1位的二值图
#define   RAS_CT_UINT8_BITSIZE    	8L     //8位无符号整数
#define   RAS_CT_UINT16_BITSIZE    	16L    //16位无符号整数
#define   RAS_CT_UINT32_BITSIZE    	32L    //32位无符号整数
#define   RAS_CT_INT8_BITSIZE      	8L     //8位有符号整数
#define   RAS_CT_INT16_BITSIZE  	16L    //16位有符号整数
#define   RAS_CT_INT32_BITSIZE     	32L    //32位有符号整数
#define   RAS_CT_IEEE4_BITSIZE     	32L    //四字节浮点数据
#define   RAS_CT_IEEE8_BITSIZE  	64L    //双精度浮点数据

enum RAS_SENSORTYPE  //传感器类型.
{
	RAS_SENSOR_UNKNOW	= 0L,
	RAS_SENSOR_SPOT		= 1L,
	RAS_SENSOR_TM		= 2L,
	RAS_SENSOR_DEFAULT	= RAS_SENSOR_UNKNOW,    //缺省.
};

enum RAS_COMPRESSTYPE //数据压缩类型.
{
	RAS_COMPRESSION_NO 		= 0L,	  
	RAS_COMPRESSION_RCL_HUMAN	= 1L,	  // 行程哈夫曼编码
	RAS_COMPRESSION_DPCM_HUMAN	= 2L,	  // 差分哈夫曼编码
	RAS_COMPRESSION_JPEGMSI		= 3L,	  // JPEG方式编码
	RAS_COMPRESSION_2VALUE_RCL_HUMAN= 4L,	  // 2值行程编码
	RAS_COMPRESSION_DEFLATE_ADOBE	= 5L,	  // ADOBE之DEFLATE编码.
	RAS_COMPRESSION_ZIP             = 6L,     // ZIP压缩.
	RAS_COMPRESSION_DEFAULT	        = RAS_COMPRESSION_NO,  //缺省.
};

///////////////////////////栅格扩展信息定义///////////////////////////////////////////

enum RASTER_EXTEND_ITEM
{
    RASTAG_BANDSNOTEINFO            =  0L,    //各个波段注释信息          
    RASTAG_BANDSNOTEINFOLENGTH      =  1L,    //各个波段注释信息的大小
	
 	RASTAG_COLORLUT				    =  2L,    //彩色查找表
	
	//图象坐标和设备坐标的参数
    RASTAG_XRESOLUTION			    =  3L,    //像元行方向(X)分辨率
	RASTAG_YRESOLUTION			    =  4L,    //像元列方向(Y)分辨率
	RASTAG_RESOLUTIONUNIT		    =  5L,    //分辨率单位.   
	
	RASTAG_DOCUMENTNAME			    =  6L,    //图像文件名 
	RASTAG_IMAGEDESCRIPTION		    =  7L,    //图像描述信息
	RASTAG_SOFTWARE				    =  8L,    //生成图像的软件
	RASTAG_DATETIME				    =  9L,    //生成图像的日期和时间
	RASTAG_ARTIST   			    = 10L,    //生成图像的作者
	RASTAG_HOSTCOMPUTER		        = 11L,    //生成图像的主机
	
	//扩展标志--用于图像显示、坐标系统、图像分析、几何校正、图像镶嵌等.
	RASTAG_DISPLAYFORM              = 12L,    //图象的显示方式
	RASTAG_DISPLAYFORMCEFF          = 13L,    //图象的显示方式的参数
	RASTAG_DISPLAYPROCESSFORM       = 14L,    //显示图象的处理方式
	RASTAG_DISPLAYPROCESSFORMCEFF   = 15L,    //显示图象的处理方式的参数
	RASTAG_ISSUPPORTPROJECTION      = 16L,    //是否支持投影变换
	RASTAG_PROJECTIONCEFF           = 17L,    //当前投影参数(投影坐标系,投影区号)
	RASTAG_COORDINATESYSTYPE        = 18L,    //坐标系统
	RASTAG_COORDINATEUNIT           = 19L,    //坐标单位
	RASTAG_HWTOCOFORM               = 20L,	  //坐标正变换方式
	
	//FFT变换专用的三个标志.
	RASTAG_FFTSCELLTYPE		        = 21L,
	RASTAG_FFTSLINES				= 22L,
	RASTAG_FFTSLINECELLS			= 23L,
	
	//标志图像的应用类别(对一些应用可生成两个版本的图象).
	RASTAG_DATA_USE_FORM			= 24L,	  //用于支持一些只关心显示效果的应用，提高压缩比，如INTERNET的查询，
	
	//全区统计信息
	RASTAG_RESAMPLE_STEP			= 25L,	  //采样步长,缺省为1.
	
	//像元缩放比例.
	RASTAG_X_SCALE				    = 26L,	  //像元X方向的缩放比例.
	RASTAG_Y_SCALE				    = 27L,	  //像元Y方向的缩放比例.
	RASTAG_Z_SCALE				    = 28L,	  //像元Z方向的缩放比例.
	//(设置高程的放大倍率,使高程数据可以以整型方式存贮,如高程精度精确到厘米,高程的放大倍率为100)
	
	//MAP_INFO左上角的图象坐标(不支持投影下,用于镶嵌)
	RASTAG_X0_COORDAINTION		    = 29L,	  //设置X的原点
	RASTAG_Y0_COORDAINTION		    = 30L,	  //设置Y的原点
	RASTAG_Z0_COORDAINTION		    = 31L,	  //设置Z(高程)的原点
	
	RASTAG_Z_UNIT				    = 32L,	  //属性坐标单位(DEM：高程，米)

	RASTAG_COLORLUTNAME				= 33L,    //彩色查找表名称
	
	//////////////////////////////////////////////////////////////
	//在这之前处理新加入的标志
	//////////////////////////////////////////////////////////////
};

//扩展信息相关的各项定义.

//各种类型图像的波段数.
#define  RAS_BAND_NUM_MIN				 1L      //最小波段数
#define  RAS_COLORLUT_BAND_NUM			 1L	     //单波段的256色图和64K高彩图
#define  RAS_COMPLEXDATA_BAND_NUM		 2L	     //用于两波段的FFT变换有序数据
#define  RAS_RGB_BAND_NUM				 3L	     //三波段的RGB真彩色图
#define  RAS_RGBP_BAND_NUM				 4L	     //四波段的RGBP透明真彩色叠加图
#define  RAS_BAND_NUM_MAX				 1024L	 //最大波段数

//各个波段注释信息个数.
#define  RAS_BANDSNOTEINFO_NUM_MIN       RAS_BAND_NUM_MIN  
#define  RAS_BANDSNOTEINFO_NUM_MAX       RAS_BAND_NUM_MAX

//各个波段注释信息的长度.
#define  RAS_BANDSNOTEINFO_LEN_MIN       0L		 //最小长度.
#define  RAS_BANDSNOTEINFO_LEN_MAX       65536L  //最大长度.
#define  RAS_BANDSNOTEINFO_LEN_DEFAULT   256L    //缺省长度.

//各种类型图像的彩色查找表的长度.
#define  RAS_CLUT_RGBINDEX_NUM           3L
#define  RAS_CLUT_NUMS_MIN               2L      //最小长度.
#define  RAS_CLUT_NUMS_1BIT              2L
#define  RAS_CLUT_NUMS_UINT8             256L
#define  RAS_CLUT_NUMS_UINT16            65536L
#define  RAS_CLUT_NUMS_UINT32            65536L
#define  RAS_CLUT_NUMS_INT8              256L
#define  RAS_CLUT_NUMS_INT16             65536L
#define  RAS_CLUT_NUMS_INT32             65536L
#define  RAS_CLUT_NUMS_IEEE4             65536L
#define  RAS_CLUT_NUMS_IEEE8             65536L
#define  RAS_CLUT_NUMS_MAX               65536L  //最大长度.

//缺省图像分辨率.
#define  RAS_DEFAULT_RESOLUTION          (double)72.00 

//像元分辨率的单位(目前暂时自定义,以后使用MAPGIS中定义)
#define  RAS_RU_MIN                      1L  
#define	 RAS_RU_NONE				     1L		 //无单位
#define	 RAS_RU_INCH		 			 2L		 //英寸
#define	 RAS_RU_CENTIMETER			     3L		 //厘米
#define  RAS_RU_DEFAULT				     RAS_RU_INCH
#define  RAS_RU_MAX                      3L

//图像文件名长度. 
#define  RAS_DNAME_LEN_MIN			     0L      //最小长度.
#define  RAS_DNAME_LEN_MAX			     256L	 //最大长度.
#define  RAS_DNAME_LEN_DEFAULT		     256L    //缺省长度.

//图像描述信息长度.
#define  RAS_IMGSCR_LEN_MIN			     0L      //最小长度.
#define  RAS_IMGSCR_LEN_MAX			     256L	 //最大长度.
#define  RAS_IMGSCR_LEN_DEFAULT		     256L    //缺省长度.

//生成图像的软件名长度.
#define  RAS_SOFTWARE_LEN_MIN		     0L      //最小长度.
#define  RAS_SOFTWARE_LEN_MAX		     256L	 //最大长度.
#define  RAS_SOFTWARE_LEN_DEFAULT	     256L    //缺省长度.

//生成图像的日期和时间长度.
#define  RAS_DATETIME_LEN_MIN		     0L      //最小长度.
#define  RAS_DATETIME_LEN_MAX		     256L	 //最大长度.
#define  RAS_DATETIME_LEN_DEFAULT	     256L    //缺省长度.

//生成图像的作者名长度.
#define  RAS_ARTIST_LEN_MIN			     0L      //最小长度.
#define  RAS_ARTIST_LEN_MAX			     256L	 //最大长度.
#define  RAS_ARTIST_LEN_DEFAULT		     256L    //缺省长度.

//生成图像的主机名长度.
#define  RAS_HOSTCOMPUTER_LEN_MIN        0L      //最小长度.
#define  RAS_HOSTCOMPUTER_LEN_MAX        256L	 //最大长度. 
#define  RAS_HOSTCOMPUTER_LEN_DEFAULT    256L    //缺省长度.

//图象的显示方式.
enum RAS_DISPLAYFORM
{
	RAS_DISPLAYFORM_DEFAULT     =    0L,	 //缺省的显示方式
	RAS_DISPLAYFORM_RGB         =    1L,	 //RGB显示方式(影像)
	RAS_DISPLAYFORM_RGBP        =    2L,	 //RGBP显示方式(影像)
	RAS_DISPLAYFORM_GRAY        =    3L,	 //灰度显示方式(Dem和影像)
	RAS_DISPLAYFORM_CLASSIFY    =    4L,     //分类显示方式(Dem)
};

//图象显示的处理方式.
enum RAS_DISPLAYPROCESSFORM
{
	RAS_DISPLAYPROCESSFORM_DEFAULT   =   0L,     //缺省的显示图象的处理方式，原数据显示
//	RAS_DISPLAYPROCESSFORM_NOCL      =   1L,     //不处理
	RAS_DISPLAYPROCESSFORM_ZSY       =   1L,     //自适应显示
	RAS_DISPLAYPROCESSFORM_JHH       =   2L,     //均衡化
	RAS_DISPLAYPROCESSFORM_ZGH       =   3L,     //正规化
	RAS_DISPLAYPROCESSFORM_XXLS      =   4L,     //线性拉伸
	RAS_DISPLAYPROCESSFORM_ZSBH	 =   5L,     //指数变换
	RAS_DISPLAYPROCESSFORM_DSBH      =   6L,     //对数变换
	RAS_DISPLAYPROCESSFORM_FDXX      =   7L,     //分段线性
	RAS_DISPLAYPROCESSFORM_GDH       =   8L,     //规定化
	RAS_DISPLAYPROCESSFORM_FZ   	 =   9L,     //反转显示
}; 


//是否支持投影变换.
#define  RAS_PROJECTION_NOSUPPORT        0L      //不支持投影变换,缺省不支持投影变换
#define  RAS_PROJECTION_SUPPORT          1L      //支持投影,可以进一步做投影变换


//坐标系统(以后可使用MAPGIS中定义).
enum RAS_COORDINATESYSTYPE
{
	RAS_COORDINATETYPE_NOCOORDINATE   =   0L,    //无坐标
	RAS_COORDINATETYPE_HWCOORDINATE   =   1L,    //图象行列坐标
	RAS_COORDINATETYPE_ZJCOORDINATE   =   2L,    //直角坐标(东,北),需要控制点信息和变换多项式的信息
	RAS_COORDINATETYPE_GEOCOORDINATE  =   3L,    //地理坐标(经纬度),需要控制点信息和变换多项式的信息
	//用于图像与MAPGIS的图形的叠加显示
	RAS_COORDINATETYPE_MAPGISCOORDINATE = 12L,   //MAPGIS的图纸坐标(可能为毫米，米，公里...),需要控制点信息和变换多项式的信息
	//特别说明:
	//当坐标系统为RAS_COORDINATETYPE_ZJCOORDINATE、RAS_COORDINATETYPE_MAPGISCOORDINATE和RAS_COORDINATETYPE_GEOCOORDINATE时,
	//下列标志必须存在: RASTAG_COORDINATEUNIT、RASTAG_HWTOCOFORM、RASTAG_CONTRAL_POINT_FILE.
};

//坐标系统类型.
enum RAS_COORDSYSTYPE           
{
	RAS_IMG_COORDINATESYSTYPE       =     0L,    //图像方式.
	RAS_MAP_COORDINATESYSTYPE       =     1L,    //图形方式.
};

//坐标单位(以后可使用MAPGIS中定义).
enum RAS_COORDINATEUNIT
{
	RAS_COORDINATEUNIT_NOUNITS      =	 0L,	 //无单位
	RAS_COORDINATEUNIT_PIXELS       =	 1L,	 //象元
	RAS_COORDINATEUNIT_INCHUNITS    =	 2L,	 //英寸
	RAS_COORDINATEUNIT_MMUNITS      =	 3L,	 //毫米
	RAS_COORDINATEUNIT_CMUNITS      =	 4L,	 //厘米
	RAS_COORDINATEUNIT_MIUNITS      =	 5L,	 //米
	RAS_COORDINATEUNIT_KMUNITS      =	 6L,	 //公里
	RAS_COORDINATEUNIT_DDMMSS       =	 7L,	 //度分秒,即±DDDMMSS.SSSS格式
	RAS_COORDINATEUNIT_DD           =	 8L,	 //度
	RAS_COORDINATEUNIT_MM           =	 9L,	 //分
	RAS_COORDINATEUNIT_SS           =	 10L,	 //秒
	RAS_COORDINATEUNIT_RADIAN       =	 11L,	 //弧度
	//用于图像与MAPGIS的图形的叠加显示
	RAS_COORDINATEUNIT_MAPGISUNITS  =	 12L,	 //MAPGIS的图纸单位坐标(可能为毫米，米，公里...)
	RAS_COORDINATEUNIT_FOOT		    =	 13L,	 //英尺
	RAS_COORDINATEUNIT_YARD		    =	 14L,	 //码
	RAS_COORDINATEUNIT_SEAMAIL	    =	 15L,	 //海里
	RAS_COORDINATEUNIT_MAIL			=	 16L,	 //英里
};

//坐标正变换方式.
enum RAS_HWTOCOFORM
{
	RAS_HWTOCOFORM_NOCONVERT        =    0L,     //无变换
	RAS_HWTOCOFORM_1CONVERT         =    1L,	 //一次线性
	RAS_HWTOCOFORM_2CONVERT         =    2L,	 //二次多项式
	RAS_HWTOCOFORM_3CONVERT         =    3L,	 //三次多项式
	RAS_HWTOCOFORM_4CONVERT         =    4L,	 //四次多项式
	RAS_HWTOCOFORM_5CONVERT         =    5L,	 //五次多项式
};

//图像的应用类别.
#define  RAS_HIGH_QUALITY_FORM		     0L	     //高质量应用.
#define  RAS_VIEW_QUALITY_FORM			 1L	     //显示发布等应用.
#define  RAS_QUALITY_FORM_DEFAULT		 RAS_HIGH_QUALITY_FORM	

//属性坐标单位(以后可使用MAPGIS中定义)
enum RAS_ZUNIT
{
	RAS_Z_UNIT_NOUNITS			    =     0L,    //无单位
	RAS_Z_UNIT_INCHUNITS            =	  1L,    //英寸
	RAS_Z_UNIT_MMUNITS              =	  2L,    //毫米
	RAS_Z_UNIT_CMUNITS              =	  3L,    //厘米
	RAS_Z_UNIT_MIUNITS              =	  4L,    //米
	RAS_Z_UNIT_KMUNITS              =	  5L,    //公里
};

//栅格重采样方式.
enum RAS_RESAMPLETYPE
{
	RAS_RSP_NearestNeighbor			=	  0L,    //最邻近.
	RAS_RSP_BilinearInterpolation	=     1L,    //双线性.
	RAS_RSP_CubicConvolution		=     2L,    //双三次. 
};


////////////////////////////栅格目录基本信息定义//////////////////////////////////////

enum RAS_SERVERTYPE  //数据库服务器类型.
{
	NULL_TYPE   = 0, 
	_ORACLE     = 1,
	_SQL_SERVER = 2,
	_IBM_DB2    = 3,
	_SYBASE     = 4,
	_INFORMIX   = 5,
	_MYSQL      = 6,
	_DM_DB		= 7,
	//可扩充...
};

enum RAS_ITEM_TYPE  //目录条目类型.
{
	LOCAL_FILE     = 0,  //本地文件.
	LOCAL_DATASET  = 1,  //本地数据集.
	REMOTE_DATASET = 2,  //数据库中数据集.
};

//struct RAS_SDE_CONNECTINFO   //SDE连接信息.
//{
//	RAS_SERVERTYPE ServerType;               //服务连接信息.
//	char           DataSource[128];
//	char           UserName[MAX_USER_LEN];
//	char           Password[MAX_PSW_LEN];
//	char           GDBName[MAX_DB_NAME_LEN]; //地理数据库名. 
//};

//struct RASTER_CATALOG_ITEM   //栅格目录条目.
//{
//	char                  RasterName[256]; //栅格数据名.
//	RAS_SDE_CONNECTINFO   SDEConnectInfo;  //栅格数据连接信息.
//	RAS_ITEM_TYPE         ItemType;        //栅格数据类型.
//};

//wyz-2010.02.04-栅格数据集基本信息结构体
//typedef struct tagRasGDBInfoStrcT
//{
//	//服务信息.
//	char			ServerName[MAX_SVR_NAME_LEN];
//	char			LogName[MAX_USER_LEN];
//	char			Password[MAX_PSW_LEN];
//	//所属地理数据库信息
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


//栅格数据集/目录信息.
//typedef struct tagRasDataInfoStrcT
//{
//	RasGDBInfoStrcT	RasGDBInfo;
//	//栅格数据信息
//	char			RasterName[MAX_XCLS_NAME_LEN];    //栅格数据名.
//	long			RasterID;							//栅格数据集ID.
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
//	//可扩充...
//};

#endif