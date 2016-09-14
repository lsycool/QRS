//================================================================================
// �ļ���		 �� RasterIOBaseDefine.h 
// �汾			 �� this 1.0.0 ; QGIS1.7.4 ;QT 4.7.1 ;GDAL 1.8.1                            
// Ŀ�ļ���Ҫ���ܣ� 
// ��������		 �� 2012.04.25
// �޸����� 	 ��             
// ����			 ��  yq
// �޸���		 ��   
// ����			 �� ��Ҫ�޸�ö�����͵�˳�򣡣�
//================================================================================;
#ifndef RASTER_IO_BASE_DEFINE_H
#define RASTER_IO_BASE_DEFINE_H


//Ӱ����Ԫ����
typedef enum {
	MS_Unknown = 0,			// δ֪��������
	MS_Byte = 1,			//  8λ�޷�������
	MS_UInt16 = 2,			// 16λ�޷�������
	MS_Int16 = 3,			// 16λ�з�������
	MS_UInt32 = 4,			// 32λ�޷�������
	MS_Int32 = 5,			// 32λ�з�������
	MS_Float32 = 6,			// 32λ��������
	MS_Float64 = 7,			// 64λ��������
	MS_CInt16 = 8,			// 16λ���͸���
	MS_CInt32 = 9,			// 32λ���͸���
	MS_CFloat32 = 10,		// 32λ���㸴��
	MS_CFloat64 = 11,		// 64λ���㸴��
	MS_1Bit=12,
	MS_Int8=13,
	MS_TypeCount = 14       // ��������
} MSRSDataType;

//Ӱ���ļ���д��ʽ
typedef enum {
	MS_ReadOnly = 0,	// ֻ��
	MS_Update = 1		// ��д         
} MSRSAccess;

//IO������д��־λ
typedef enum {
	MS_Read = 0,			// ������
	MS_Write = 1			// д����
} MSRSRWFlag;


//{{���ο�궨��
typedef struct
{
	double xmin;
	double ymin;
	double xmax;
	double ymax;
}D_RECT;
//}}

//{{�����ṹ����
typedef struct
{
	double x;
	double y;
}D_DOT;

//����ϵͳ����.
//enum RAS_COORDSYSTYPE           
//{
//	RAS_IMG_COORDINATESYSTYPE       =     0L,    //ͼ��ʽ.
//	RAS_MAP_COORDINATESYSTYPE       =     1L,    //ͼ�η�ʽ.
//};

#endif