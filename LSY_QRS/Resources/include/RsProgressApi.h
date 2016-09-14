#ifndef _RSPROGRESS_H_
#define _RSPROGRESS_H_

#ifdef  RSPROGRESS 
#define RsProgApiDll     __declspec(dllexport)    
#else
#define RsProgApiDll     __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"{
#endif


//=======================================�ر�˵��===============================//
//�����ں����������ܽ��ȣ�Ϊ��֤��������ֻ��һ�����ȿ����ڵ���
//���н��������Ӻ���֮ǰ����RsBeginProgressObj,��ں�������ʱ����RsEndProgressObj
//=============================================================================//

//������������������RsDestroyProgress�ɶԳ���   
//szWndTittle:�Ի������ƣ������������µ�һ��������Ч  szStateMsg:״̬��Ϣ   bAutoStyle:�Ƿ�Ϊ�Զ�ģʽ
long	RsProgApiDll RsBeginProgressObj(const char *szWndTittle,const char *szStateMsg,BOOL bAutoStyle = FALSE);

//��ֹ������,������RsBeginProgressObj�ɶԳ���
long	   RsProgApiDll RsEndProgressObj();

//���ý�������Χ            
//nLower:��Сֵ     nUpper:���ֵ
long		RsProgApiDll RsSetProgRange(int nLower,int nUpper);

//���ý�����λ��
long		RsProgApiDll RsSetProgPos(int nPos);

//���ò���
void  RsProgApiDll  RsSetProgStep(int nStep);

//����,��������ʹ��RsSetProgStep���ò���
void  RsProgApiDll  RsProgStepIt();

//�ж��Ƿ�ȡ��������,���ڳ������жϴ˱�־�����ж�
BOOL	RsProgApiDll RsIsProgStop();

#ifdef __cplusplus
}
#endif



#ifndef RSPROGRESS
#pragma comment(lib,"RsProgress.lib")
#endif

#endif
