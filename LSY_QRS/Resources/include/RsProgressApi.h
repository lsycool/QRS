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


//=======================================特别说明===============================//
//如果入口函数不存在总进度，为保证程序最终只是一个进度框，请在调用
//含有进度条的子函数之前调用RsBeginProgressObj,入口函数结束时调用RsEndProgressObj
//=============================================================================//

//创建进度条，必须与RsDestroyProgress成对出现   
//szWndTittle:对话框名称，多次设置情况下第一次设置有效  szStateMsg:状态信息   bAutoStyle:是否为自动模式
long	RsProgApiDll RsBeginProgressObj(const char *szWndTittle,const char *szStateMsg,BOOL bAutoStyle = FALSE);

//终止进度条,必须与RsBeginProgressObj成对出现
long	   RsProgApiDll RsEndProgressObj();

//设置进度条范围            
//nLower:最小值     nUpper:最大值
long		RsProgApiDll RsSetProgRange(int nLower,int nUpper);

//设置进度条位置
long		RsProgApiDll RsSetProgPos(int nPos);

//设置步长
void  RsProgApiDll  RsSetProgStep(int nStep);

//步进,必须首先使用RsSetProgStep设置步长
void  RsProgApiDll  RsProgStepIt();

//判断是否取消进度条,请在程序当中判断此标志进行中断
BOOL	RsProgApiDll RsIsProgStop();

#ifdef __cplusplus
}
#endif



#ifndef RSPROGRESS
#pragma comment(lib,"RsProgress.lib")
#endif

#endif
