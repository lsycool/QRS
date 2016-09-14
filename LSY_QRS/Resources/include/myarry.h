//自己做的优化内存分配的模板类
//内存增长的步长由计算得出。
//专门为移植栅格转矢量的算法设计，所以有些特殊的处理。
//2002-11-26根据自己对内存异常处理的理解，添加了异常处理
//AfxThrowMemoryException();在函数中

//顺序增量内存管理模板类,
template<class T>
class CMyArray
{
public:
	CMyArray();
	~CMyArray()
	{
		ReMoveAll();
	}
public:
	long  m_lTotalLength;	//当前的总长度
	long  m_lCurLength;		//当前已经使用的长度
	long  m_lTotalProc;		//总共要处理量
	long  m_lCurProc;		//当前已经处理的数据量(用于计算增长步长）
	long  m_lMaxStep;		//允许的最大步长
	T*	  m_pArry;			//数组指针
public:
	void  SetSize(long lSize);		//设置大小
	long  SetMaxStep(long lMaxStep);
	long  SetTotalProc(long lTotal);//设置总共要处理的数据量
	void  AddProc(long lProc);	//增加的处理量
	long  GetSize();			//得到当前使用的长度
	T     GetAt(long lPos);		//得到值
	void  SetAt(long lPos,T &newElement);//设置值
	void  ReMoveAll();			//释放所有的数据,设置标记
	void  CopyTo(T *pArry,long lSize);//复制数据
};

template<class T>
CMyArray<T>::CMyArray()
{
	m_pArry=NULL;
	m_lTotalLength=0;
	m_lTotalProc=m_lCurProc=0;
	m_lMaxStep=100;	//缺省的最大步长
}


//设置内存大小，内存中数据全部清空，当前长度回0
template<class T>
void CMyArray<T>::SetSize(long lSize)
{
	if(lSize<=0)//清空内存
	{
		ReMoveAll();
		return;
	}
	if(m_pArry==NULL)
	{
		m_pArry=(T *)malloc(sizeof(T)*lSize);
		if(m_pArry==NULL)	AfxThrowMemoryException();
		m_lTotalLength=lSize;//当前总长度
		m_lCurLength=0;		 //当前指针位置
	}
	else
	{
		m_pArry=(T *)realloc(m_pArry,sizeof(T)*lSize);
		if(m_pArry==NULL)	AfxThrowMemoryException();
		m_lTotalLength=lSize;
		m_lCurLength=0;
	}

	return;
}

template<class T>
long CMyArray<T>::SetMaxStep(long lMaxStep)
{
	if(lMaxStep<=0) return 0;

	m_lMaxStep=lMaxStep;
	return 1;
}

//设置总共要处理的数据量
template<class T>
long  CMyArray<T>::SetTotalProc(long lTotal)
{
	if(lTotal<0) lTotal=0;
	m_lTotalProc=lTotal;
	return 1;
}

//增加的处理量
template<class T>
inline void CMyArray<T>::AddProc(long lProc)
{
	m_lCurProc+=lProc;
}


//得到值
template<class T>
inline T CMyArray<T>::GetAt(long lPos)
{
	ASSERT(lPos>=0 && lPos<m_lTotalLength);//对变量进行判断
		
	return m_pArry[lPos];
}


//设置值,扩展这个函数的功能，在超出范围时，进行添加
template<class T>
inline void  CMyArray<T>::SetAt(long lPos,T &newElement)
	{
	ASSERT(lPos>=0);//对变量进行判断

	long lStep;

	if(m_pArry==NULL)//内存还没有分配
	{
		m_pArry=(T *)malloc(sizeof(T)*m_lMaxStep);//初始值分配最大步长
		if(m_pArry==NULL)	AfxThrowMemoryException();
		m_lTotalLength=m_lMaxStep;//当前总长度
	}

	if(lPos>=m_lTotalLength)
	{
		//计算要增加的步长
		if(m_lCurProc<=0 || m_lTotalProc<=0 ||m_lCurProc>=m_lTotalProc)
			lStep=m_lMaxStep;
		else
			{
			lStep=long(((m_lTotalProc-m_lCurProc)/((double)(m_lCurProc)))*m_lTotalLength);
			if(lStep<10) lStep=10;
			if(lStep>m_lMaxStep) lStep=m_lMaxStep;
			}
		//重新分配内存
		m_lTotalLength+=lStep;
		m_pArry=(T *)realloc(m_pArry,sizeof(T)*m_lTotalLength);
		if(m_pArry==NULL)	AfxThrowMemoryException();
	}	
	m_pArry[lPos]=newElement;
	}


//得到当前使用的长度
template<class T>
inline long  CMyArray<T>::GetSize()
{
	return(m_lCurLength);
}

//释放所有的数据,回到初始状态
template<class T>
void  CMyArray<T>::ReMoveAll()
{
	if(m_pArry!=NULL)
	{
		free(m_pArry);
		m_pArry=NULL;
	}

	memset(this,'\0',sizeof(this));
	m_lMaxStep=100;	//缺省的最大步长

	return;
}

//复制数据
//2002-7-19对lSize<m_lTotalLength=》lSize<=m_lTotalLength
//sizeof(T)的用法要小心，如果T中含有指针，可能会出现问题
template<class T>
void  CMyArray<T>::CopyTo(T *pArry,long lSize)
{
	ASSERT(lSize>0 && lSize<=m_lTotalLength);
	memcpy(pArry,m_pArry,sizeof(T)*lSize);
}
