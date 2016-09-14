//�Լ������Ż��ڴ�����ģ����
//�ڴ������Ĳ����ɼ���ó���
//ר��Ϊ��ֲդ��תʸ�����㷨��ƣ�������Щ����Ĵ���
//2002-11-26�����Լ����ڴ��쳣�������⣬������쳣����
//AfxThrowMemoryException();�ں�����

//˳�������ڴ����ģ����,
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
	long  m_lTotalLength;	//��ǰ���ܳ���
	long  m_lCurLength;		//��ǰ�Ѿ�ʹ�õĳ���
	long  m_lTotalProc;		//�ܹ�Ҫ������
	long  m_lCurProc;		//��ǰ�Ѿ������������(���ڼ�������������
	long  m_lMaxStep;		//�������󲽳�
	T*	  m_pArry;			//����ָ��
public:
	void  SetSize(long lSize);		//���ô�С
	long  SetMaxStep(long lMaxStep);
	long  SetTotalProc(long lTotal);//�����ܹ�Ҫ�����������
	void  AddProc(long lProc);	//���ӵĴ�����
	long  GetSize();			//�õ���ǰʹ�õĳ���
	T     GetAt(long lPos);		//�õ�ֵ
	void  SetAt(long lPos,T &newElement);//����ֵ
	void  ReMoveAll();			//�ͷ����е�����,���ñ��
	void  CopyTo(T *pArry,long lSize);//��������
};

template<class T>
CMyArray<T>::CMyArray()
{
	m_pArry=NULL;
	m_lTotalLength=0;
	m_lTotalProc=m_lCurProc=0;
	m_lMaxStep=100;	//ȱʡ����󲽳�
}


//�����ڴ��С���ڴ�������ȫ����գ���ǰ���Ȼ�0
template<class T>
void CMyArray<T>::SetSize(long lSize)
{
	if(lSize<=0)//����ڴ�
	{
		ReMoveAll();
		return;
	}
	if(m_pArry==NULL)
	{
		m_pArry=(T *)malloc(sizeof(T)*lSize);
		if(m_pArry==NULL)	AfxThrowMemoryException();
		m_lTotalLength=lSize;//��ǰ�ܳ���
		m_lCurLength=0;		 //��ǰָ��λ��
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

//�����ܹ�Ҫ�����������
template<class T>
long  CMyArray<T>::SetTotalProc(long lTotal)
{
	if(lTotal<0) lTotal=0;
	m_lTotalProc=lTotal;
	return 1;
}

//���ӵĴ�����
template<class T>
inline void CMyArray<T>::AddProc(long lProc)
{
	m_lCurProc+=lProc;
}


//�õ�ֵ
template<class T>
inline T CMyArray<T>::GetAt(long lPos)
{
	ASSERT(lPos>=0 && lPos<m_lTotalLength);//�Ա��������ж�
		
	return m_pArry[lPos];
}


//����ֵ,��չ��������Ĺ��ܣ��ڳ�����Χʱ���������
template<class T>
inline void  CMyArray<T>::SetAt(long lPos,T &newElement)
	{
	ASSERT(lPos>=0);//�Ա��������ж�

	long lStep;

	if(m_pArry==NULL)//�ڴ滹û�з���
	{
		m_pArry=(T *)malloc(sizeof(T)*m_lMaxStep);//��ʼֵ������󲽳�
		if(m_pArry==NULL)	AfxThrowMemoryException();
		m_lTotalLength=m_lMaxStep;//��ǰ�ܳ���
	}

	if(lPos>=m_lTotalLength)
	{
		//����Ҫ���ӵĲ���
		if(m_lCurProc<=0 || m_lTotalProc<=0 ||m_lCurProc>=m_lTotalProc)
			lStep=m_lMaxStep;
		else
			{
			lStep=long(((m_lTotalProc-m_lCurProc)/((double)(m_lCurProc)))*m_lTotalLength);
			if(lStep<10) lStep=10;
			if(lStep>m_lMaxStep) lStep=m_lMaxStep;
			}
		//���·����ڴ�
		m_lTotalLength+=lStep;
		m_pArry=(T *)realloc(m_pArry,sizeof(T)*m_lTotalLength);
		if(m_pArry==NULL)	AfxThrowMemoryException();
	}	
	m_pArry[lPos]=newElement;
	}


//�õ���ǰʹ�õĳ���
template<class T>
inline long  CMyArray<T>::GetSize()
{
	return(m_lCurLength);
}

//�ͷ����е�����,�ص���ʼ״̬
template<class T>
void  CMyArray<T>::ReMoveAll()
{
	if(m_pArry!=NULL)
	{
		free(m_pArry);
		m_pArry=NULL;
	}

	memset(this,'\0',sizeof(this));
	m_lMaxStep=100;	//ȱʡ����󲽳�

	return;
}

//��������
//2002-7-19��lSize<m_lTotalLength=��lSize<=m_lTotalLength
//sizeof(T)���÷�ҪС�ģ����T�к���ָ�룬���ܻ��������
template<class T>
void  CMyArray<T>::CopyTo(T *pArry,long lSize)
{
	ASSERT(lSize>0 && lSize<=m_lTotalLength);
	memcpy(pArry,m_pArry,sizeof(T)*lSize);
}
