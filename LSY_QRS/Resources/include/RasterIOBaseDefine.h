//================================================================================
// 文件名		 ： RasterIOBaseDefine.h 
// 版本			 ： this 1.0.0 ; QGIS1.7.4 ;QT 4.7.1 ;GDAL 1.8.1                            
// 目的及主要功能： 
// 创建日期		 ： 2012.04.25
// 修改日期 	 ：             
// 作者			 ：  yq
// 修改者		 ：   
// 描述			 ： 不要修改枚举类型的顺序！！
//================================================================================;
#ifndef RASTER_IO_BASE_DEFINE_H
#define RASTER_IO_BASE_DEFINE_H


//影像像元类型
typedef enum {
	MS_Unknown = 0,			// 未知数据类型
	MS_Byte = 1,			//  8位无符号整数
	MS_UInt16 = 2,			// 16位无符号整数
	MS_Int16 = 3,			// 16位有符号整数
	MS_UInt32 = 4,			// 32位无符号整数
	MS_Int32 = 5,			// 32位有符号整数
	MS_Float32 = 6,			// 32位浮点数据
	MS_Float64 = 7,			// 64位浮点数据
	MS_CInt16 = 8,			// 16位整型复数
	MS_CInt32 = 9,			// 32位整型复数
	MS_CFloat32 = 10,		// 32位浮点复数
	MS_CFloat64 = 11,		// 64位浮点复数
	MS_1Bit=12,
	MS_Int8=13,
	MS_TypeCount = 14       // 类型总数
} MSRSDataType;

//影像文件读写方式
typedef enum {
	MS_ReadOnly = 0,	// 只读
	MS_Update = 1		// 读写         
} MSRSAccess;

//IO操作读写标志位
typedef enum {
	MS_Read = 0,			// 读数据
	MS_Write = 1			// 写数据
} MSRSRWFlag;


//{{矩形框宏定义
typedef struct
{
	double xmin;
	double ymin;
	double xmax;
	double ymax;
}D_RECT;
//}}

//{{坐标点结构定义
typedef struct
{
	double x;
	double y;
}D_DOT;

//坐标系统类型.
//enum RAS_COORDSYSTYPE           
//{
//	RAS_IMG_COORDINATESYSTYPE       =     0L,    //图像方式.
//	RAS_MAP_COORDINATESYSTYPE       =     1L,    //图形方式.
//};

#endif