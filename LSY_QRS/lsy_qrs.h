#ifndef LSY_QRS_H
#define LSY_QRS_H

#include "qgisplugin.h"
#include <qobject.h>
#include <qmenu.h>
#include <qlist.h>
#include <QToolBar.h>
#include <qdockwidget.h>
#include <QWidget.h>
#include <QGridLayout.h>
#include <QTreeWidget.h>
#include <QListWidget.h>
#include <qlist.h>
#include <QProgressBar.h>
#include <QStatusBar.h>
#include <QColor.h>
#include <QSplitter.h>
#include <QTableView.h>
#include <QStandardItemModel>
#include <QHeaderView>
#include <qgsmapcanvas.h>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QLibrary>

//#include "gdal.h "
//#include "gdal_priv.h"
#include "lsy_qrs_global.h"

struct XingZhTreeNode
{
	int			m_nID;
	int			m_nParentID;
	QString		m_strName;
	QColor 		m_color;
	XingZhTreeNode(int nID,int nParentID,QString strName,QColor nColor)
	{
		m_nID=nID;
		m_nParentID=nParentID;
		m_strName=strName;
		m_color=nColor;
	}
};
typedef QList<XingZhTreeNode> XingZhTreeInfo;


class  LSY_QRS:
	public QObject, public QgisPlugin
{
	Q_OBJECT
public:
	LSY_QRS(QgisInterface* iface);
	~LSY_QRS();
	void initGui();
	void unload();
private:
	//��������ӣ�QGIS��������ָ��
	QgisInterface* mIface;
	//��������ӣ������½����̵Ĳ˵�
	QAction* mAction12;
	//��������ӣ����Ӵ򿪹��̵Ĳ˵�
	QAction* mAction19;
	//��������ӣ����ӱ��湤�̵Ĳ˵�
	QAction* mAction20;
	//��������ӣ��������Ϊ���̵Ĳ˵�
	QAction* mAction21;
	//��������ӣ����ӹرչ��̵Ĳ˵�
	QAction* mAction22;

	//��������ӣ�����ͼ����ʾ�Ĳ˵�
	QAction* mAction1;
	//��������ӣ����Ӷ����ֵ��ʾ�Ĳ˵�
	QAction* mAction2;
	//��������ӣ�����������ʾ�Ĳ˵�
	QAction* mAction3;
	//��������ӣ����ӷ�������ʾ�Ĳ˵�
	QAction* mAction4;
	//��������ӣ����Ӷ���߽���ʾ�Ĳ˵�
	QAction* mAction10;

	//��������ӣ����Ӷ�߶ȷָ�Ի���Ĳ˵�
	QAction* mAction0;
	//��������ӣ�����ѡ������Ի���Ĳ˵�
	QAction* mAction5;
	//��������ӣ�����ɾ�������Ի���Ĳ˵�
	QAction* mAction6;
	//��������ӣ����ӻ��ڷ���ķָ�Ի���Ĳ˵�
	QAction* mAction7;

	//��������ӣ����ӷ���Ի���Ĳ˵�
	QAction* mAction8;
	//��������ӣ�����ɾ������Ի���Ĳ˵�
	QAction* mAction9;
	//��������ӣ����ӷ����༭�Ĳ˵�
	QAction* mAction11;

	//��������ӣ����ӷ��������ͼ�Ҽ��˵�
	QAction* mAction13;//�༭��
	QAction* mAction14;//������
	QAction* mAction15;//������
	QAction* mAction16;//ɾ����
	QAction* mAction17;//���������
	QAction* mAction18;//���������

	QAction* mAboutDlg;

	QMainWindow *mpMainWindow;

	QMenu  *mMenuImgSegObj;//��������ӣ�����Ӱ�����˵�
	QMenu  *mMenuImgShow;//��������ӣ�����Ӱ�������ʾ�˵�
	QMenu  *mMenuImgClass;//��������ӣ�����Ӱ�����˵�

	QToolBar *mToolBarImgShow;//��������ӣ�����Ӱ�������ʾ������
	QToolBar *mToolBarImgSegObj;//��������ӣ�����Ӱ�����ָ����
	QToolBar *mToolBarImgClass;//��������ӣ�����Ӱ�������๤����
	QList<QAction*> mActionList;

//������ͼ
	QDockWidget *dockWidget_2;
	QTreeWidget *treeWidget_2;
	XingZhTreeInfo	m_treeInfo;

	QString			m_strCurRainAnalyArea;
//�����б���ͼ
	QDockWidget *dockWidget_3;
	QTreeWidget *treeWidget_3;
	XingZhTreeInfo	m_treeInfo1;

//������Ϣ��ͼ
	QDockWidget *dockWidget_4;
	QTableView* tableWidget;
	QStandardItemModel *IMG_model;
	/*QListWidget *listWidget1_4;
	QListWidget *listWidget2_4;*/
	QStatusBar		*m_statusBar;
	QProgressBar	*mProgressBar;

	unsigned char* ImgArry;//Ӱ������
//	OCPRJ		 	m_pPrj;

private:
	void CreateAction(QAction*& action,QString name,QMenu*& mMenu,QString name1,QToolBar*& mToolBar,QString name2,QString icon,const char *receiverMember);
	QString inputFile() const;//��ȡ�����ļ�·��
	long InitialDockTree2(QTreeWidget *treeWidget);//��ʼ��������ͼ
	long InitialDockTree3(QString strIniFile,QTreeWidget *treeWidget);//��ʼ�������б���ͼ
	long InitialDockTable(QStandardItemModel* model,QTableView* tableView);//��ʼ��������Ϣ��ͼ
	long AddTreeItems(QTreeWidget *pTreeWidget,XingZhTreeInfo *pTreeInfo,QTreeWidgetItem *pParentItem,const XingZhTreeNode *pParentNode);
	long AddTableItems(QStandardItemModel* model,QTableView* tableView,QString name,QString num);
	long ReadXingZhInfo(QString strIniFile,XingZhTreeInfo *pTreeInfo);
	void InitalProgressBar(/*(void *)mProgressBar,(void *)m_statusBar,char**/);//��ʼ��������
	void ReleaseProgBar();//���ٽ�����
	void MapFrame(char* FilePath,char* MapName);//Ϊդ�����ݴ���ͼ���򣻴���������򿪵�դ���ļ���·��,ͼ��������
	//ר��ͼͼ������;����������򿪵�դ�����ݵ�·��FilePath�����������ClassNum,�������֣�����ķ�Χ,��ѡ������Ĭ���ǿգ� FirstName�� SecendName...
	void MapIllustration(char* FilePath,int ClassNum,char* FirstName/* =NULL */,char* SecendName/* =NULL */,char* ThirdName/* =NULL */,char* FourthName/* =NULL */,char* FivethName/* =NULL */,char* SixthName/* =NULL */);
	void ThisAboutDlg();
	void ShowContextMenu(QTreeWidget* moduleTree);//���ؼ��Ҽ��˵�
	void ShowContextMenu(QWidget* moduleTree,QAction* Action,QString name);

private slots:
	void LayView();//ͼ����ʾ
	void ObjMeanView();//�����ֵ��ʾ
	void FeatureView();//������ʾ
	void ClassResultView();//��������ʾ
//	void SampleView();//������ʾ
	void ObjBorderView();//����߽���ʾ

	void MultiSegment();//��߶ȷָ�
	void SelectObjLay();//ѡ������
	void DelectObjLay();//ɾ�������
	void ClassSegment();//���ڷ���ķָ�

	void Classification();//����
	void DeleteClassification();//ɾ������
	void EditClassification();//�����༭

	void EditClassifie();//�༭��
	void InsertClassifie(QTreeWidget* moduleTree);//������
	void CopyClassifie();//������
	void DeletClassifie();//ɾ����
	void OutputClassifieRule();//���������
	void InputClassifieRule();//���������

	void SelectXingZheng(QTreeWidgetItem *item, int column);//����
	void SelectXingZheng1(QTreeWidgetItem *item, int column);//����
	void SelectXingZheng2(QTreeWidgetItem *item, int column);//������Ϣ
	//	void AddClassResultToMap(char *szFloodUrl,char *szAreaUrl,char *szTitle);//�ѷ��������뵽��ͼ��
	void CreateProject(/*unsigned char* arry*/);//��������
	void OpenProject(/*unsigned char* arry*/);//�򿪹���
	void SaveProject(/*unsigned char* arry*/);//���湤��
	void SaveProjectAs(/*unsigned char* arry*/);//���Ϊ����
	void CloseProject(/*unsigned char* arry*/);//�رչ���

signals://�Զ����ź�
//	void explains();//����Ҫ�Զ���ۺ��ź�, explains�ź��Ǳ����
	void ContextMenuShow(QTreeWidget* moduleTree);//�Զ����ź�.
};

#endif // LSY_QRS_H
