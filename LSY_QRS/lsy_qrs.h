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
	//刘世永添加，QGIS操作交互指针
	QgisInterface* mIface;
	//刘世永添加，增加新建工程的菜单
	QAction* mAction12;
	//刘世永添加，增加打开工程的菜单
	QAction* mAction19;
	//刘世永添加，增加保存工程的菜单
	QAction* mAction20;
	//刘世永添加，增加另存为工程的菜单
	QAction* mAction21;
	//刘世永添加，增加关闭工程的菜单
	QAction* mAction22;

	//刘世永添加，增加图层显示的菜单
	QAction* mAction1;
	//刘世永添加，增加对象均值显示的菜单
	QAction* mAction2;
	//刘世永添加，增加特征显示的菜单
	QAction* mAction3;
	//刘世永添加，增加分类结果显示的菜单
	QAction* mAction4;
	//刘世永添加，增加对象边界显示的菜单
	QAction* mAction10;

	//刘世永添加，增加多尺度分割对话框的菜单
	QAction* mAction0;
	//刘世永添加，增加选择对象层对话框的菜单
	QAction* mAction5;
	//刘世永添加，增加删除对象层对话框的菜单
	QAction* mAction6;
	//刘世永添加，增加基于分类的分割对话框的菜单
	QAction* mAction7;

	//刘世永添加，增加分类对话框的菜单
	QAction* mAction8;
	//刘世永添加，增加删除分类对话框的菜单
	QAction* mAction9;
	//刘世永添加，增加分类后编辑的菜单
	QAction* mAction11;

	//刘世永添加，增加分类规则视图右键菜单
	QAction* mAction13;//编辑类
	QAction* mAction14;//插入类
	QAction* mAction15;//复制类
	QAction* mAction16;//删除类
	QAction* mAction17;//导出类规则
	QAction* mAction18;//导入类规则

	QAction* mAboutDlg;

	QMainWindow *mpMainWindow;

	QMenu  *mMenuImgSegObj;//刘世永添加，增加影像对象菜单
	QMenu  *mMenuImgShow;//刘世永添加，增加影像对象显示菜单
	QMenu  *mMenuImgClass;//刘世永添加，增加影像分类菜单

	QToolBar *mToolBarImgShow;//刘世永添加，增加影像对象显示工具栏
	QToolBar *mToolBarImgSegObj;//刘世永添加，增加影像对象分割工具栏
	QToolBar *mToolBarImgClass;//刘世永添加，增加影像对象分类工具栏
	QList<QAction*> mActionList;

//类层次视图
	QDockWidget *dockWidget_2;
	QTreeWidget *treeWidget_2;
	XingZhTreeInfo	m_treeInfo;

	QString			m_strCurRainAnalyArea;
//特征列表视图
	QDockWidget *dockWidget_3;
	QTreeWidget *treeWidget_3;
	XingZhTreeInfo	m_treeInfo1;

//对象信息视图
	QDockWidget *dockWidget_4;
	QTableView* tableWidget;
	QStandardItemModel *IMG_model;
	/*QListWidget *listWidget1_4;
	QListWidget *listWidget2_4;*/
	QStatusBar		*m_statusBar;
	QProgressBar	*mProgressBar;

	unsigned char* ImgArry;//影像数组
//	OCPRJ		 	m_pPrj;

private:
	void CreateAction(QAction*& action,QString name,QMenu*& mMenu,QString name1,QToolBar*& mToolBar,QString name2,QString icon,const char *receiverMember);
	QString inputFile() const;//获取输入文件路径
	long InitialDockTree2(QTreeWidget *treeWidget);//初始化类层次视图
	long InitialDockTree3(QString strIniFile,QTreeWidget *treeWidget);//初始化特征列表视图
	long InitialDockTable(QStandardItemModel* model,QTableView* tableView);//初始化对象信息视图
	long AddTreeItems(QTreeWidget *pTreeWidget,XingZhTreeInfo *pTreeInfo,QTreeWidgetItem *pParentItem,const XingZhTreeNode *pParentNode);
	long AddTableItems(QStandardItemModel* model,QTableView* tableView,QString name,QString num);
	long ReadXingZhInfo(QString strIniFile,XingZhTreeInfo *pTreeInfo);
	void InitalProgressBar(/*(void *)mProgressBar,(void *)m_statusBar,char**/);//初始化进度条
	void ReleaseProgBar();//销毁进度条
	void MapFrame(char* FilePath,char* MapName);//为栅格数据创立图幅框；传入参数：打开的栅格文件的路径,图幅的名字
	//专题图图例制作;传入参数：打开的栅格数据的路径FilePath，待分类别数ClassNum,类别的名字（分类的范围,可选参数，默认是空） FirstName， SecendName...
	void MapIllustration(char* FilePath,int ClassNum,char* FirstName/* =NULL */,char* SecendName/* =NULL */,char* ThirdName/* =NULL */,char* FourthName/* =NULL */,char* FivethName/* =NULL */,char* SixthName/* =NULL */);
	void ThisAboutDlg();
	void ShowContextMenu(QTreeWidget* moduleTree);//树控件右键菜单
	void ShowContextMenu(QWidget* moduleTree,QAction* Action,QString name);

private slots:
	void LayView();//图层显示
	void ObjMeanView();//对象均值显示
	void FeatureView();//特征显示
	void ClassResultView();//分类结果显示
//	void SampleView();//样本显示
	void ObjBorderView();//对象边界显示

	void MultiSegment();//多尺度分割
	void SelectObjLay();//选择对象层
	void DelectObjLay();//删除对象层
	void ClassSegment();//基于分类的分割

	void Classification();//分类
	void DeleteClassification();//删除分类
	void EditClassification();//分类后编辑

	void EditClassifie();//编辑类
	void InsertClassifie(QTreeWidget* moduleTree);//插入类
	void CopyClassifie();//复制类
	void DeletClassifie();//删除类
	void OutputClassifieRule();//导出类规则
	void InputClassifieRule();//导入类规则

	void SelectXingZheng(QTreeWidgetItem *item, int column);//分类
	void SelectXingZheng1(QTreeWidgetItem *item, int column);//特征
	void SelectXingZheng2(QTreeWidgetItem *item, int column);//对象信息
	//	void AddClassResultToMap(char *szFloodUrl,char *szAreaUrl,char *szTitle);//把分类结果导入到视图上
	void CreateProject(/*unsigned char* arry*/);//创建工程
	void OpenProject(/*unsigned char* arry*/);//打开工程
	void SaveProject(/*unsigned char* arry*/);//保存工程
	void SaveProjectAs(/*unsigned char* arry*/);//另存为工程
	void CloseProject(/*unsigned char* arry*/);//关闭工程

signals://自定义信号
//	void explains();//假如要自定义槽和信号, explains信号是必须的
	void ContextMenuShow(QTreeWidget* moduleTree);//自定义信号.
};

#endif // LSY_QRS_H
