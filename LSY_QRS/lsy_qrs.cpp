#include "lsy_qrs.h"
#include "qgisinterface.h"
#include <qaction.h>
#include <qmessagebox.h>
#include <qgsapplication.h>
#include <qgsmapcanvas.h>
#include <qmainwindow.h>
#include <qmenubar.h>
#include <qnamespace.h>

//#include "ogr_geometry.h "	//是不是OGRPoint的头文件？
//#include "ogr_feature.h "	//是不是oFiled的头文件？
//#include "ogrsf_frmts.h "	//GEtRegistrar的头文件？
#include "qgsvectorlayer.h "	//加载图框生成label用到的
#include "qgsrasterlayer.h"
#include"qgslabelattributes.h "
#include "qgslabel.h "
#include "qgsvectordataprovider.h "
#include "qgsmaplayerregistry.h "
#include "qgsmaplayer.h "

//#include "cpl_conv.h "
//#include <stdio.h>
//#include <iostream>

//#include "RasterIO.h"
//#include "stdafx.h"
//#include "CImgSegDlg.h"
#include "stdafx.h"
#include "SegExport.h"
//#define WINVER 0x0501

#ifdef WIN32
#define QGISEXTERN extern "C" __declspec( dllexport )
#else
#define QGISEXTERN extern "C"
#endif

//////////////////////////////////////////////////////////////////////////
//刘世永 modify 2014.03.09
OCPRJ		 	m_pPrj;

LSY_QRS::LSY_QRS(QgisInterface* iface):
mIface(iface),mAction1(0),mAction2(0),mAction3(0),mAction4(0),mAction0(0),mAction5(0),mAction6(0),mAction7(0),mAction8(0),mAction9(0),mAction10(0),mAction11(0),mAction12(0),mAction13(0),mAction14(0),mAction15(0),mAction16(0),mAction17(0),mAction18(0)
{
	mMenuImgSegObj=0;
	mMenuImgShow=0;
	mMenuImgClass=0;
	mToolBarImgShow=0;
	mToolBarImgSegObj=0;
	mToolBarImgClass=0;
	mAboutDlg=0;
}

LSY_QRS::~LSY_QRS()
{

}


//程序的初始化相关操作
void LSY_QRS::initGui()
{
	mpMainWindow=(QMainWindow *)mIface->mainWindow();
	mpMainWindow->setWindowTitle(QString::fromLocal8Bit("高分辨率遥感滑坡灾害识别系统-LSY_QRS"));
	
	//菜单汉化
	mIface->editMenu()->setTitle(QString::fromLocal8Bit("编辑"));
	mIface->rasterMenu()->setTitle(QString::fromLocal8Bit("栅格"));
	mIface->vectorMenu()->setTitle(QString::fromLocal8Bit("矢量"));
	mIface->databaseMenu()->setTitle(QString::fromLocal8Bit("数据库"));

	QIcon iconMain;
	iconMain.addFile(QString::fromUtf8("D:\\qgis\\qgis-release-1_8\\vs2005\\output\\bin\\relwithdebinfo\\Resources\\app.png"), QSize(), QIcon::Normal, QIcon::Off);
	mpMainWindow->setWindowIcon(iconMain);

	//创建新的菜单
	QMenuBar *menubar=mpMainWindow->menuBar();
	if(menubar)
	{
		mMenuImgSegObj = new QMenu(menubar);
		mMenuImgSegObj->setObjectName(QString::fromUtf8("mMenuImgSegObj"));
		mMenuImgSegObj->setTitle(QString::fromLocal8Bit("影像对象"));

		mMenuImgShow = new QMenu(menubar);
		mMenuImgShow->setObjectName(QString::fromUtf8("mMenuImgShow"));
		mMenuImgShow->setTitle(QString::fromLocal8Bit("显示"));

		
		mMenuImgClass = new QMenu(menubar);
		mMenuImgClass->setObjectName(QString::fromUtf8("mMenuImgClass"));
		mMenuImgClass->setTitle(QString::fromLocal8Bit("分类"));

	}

	mToolBarImgShow = new QToolBar(mpMainWindow);
	mToolBarImgShow->setObjectName(QString::fromUtf8("mToolBarImgShow"));
	mpMainWindow->addToolBar(Qt::TopToolBarArea, mToolBarImgShow);

	mToolBarImgSegObj = new QToolBar(mpMainWindow);
	mToolBarImgSegObj->setObjectName(QString::fromUtf8("mToolBarImgSegObj"));
	mpMainWindow->addToolBar(Qt::TopToolBarArea, mToolBarImgSegObj);

	mToolBarImgClass = new QToolBar(mpMainWindow);
	mToolBarImgClass->setObjectName(QString::fromUtf8("mToolBarImgClass"));
	mpMainWindow->addToolBar(Qt::TopToolBarArea, mToolBarImgClass);

	//创建菜单事件
	CreateAction(mAction1,QString::fromLocal8Bit("影像图层"),mMenuImgShow,QString::fromLocal8Bit("显示"),
		mToolBarImgShow,QString::fromLocal8Bit("显示"),QString::fromUtf8(":/new/prefix1/Resources/mActionAnalysis1.png"),SLOT(LayView()));

	CreateAction(mAction1,QString::fromLocal8Bit("影像图层"),mMenuImgShow,QString::fromLocal8Bit("显示"),
		mToolBarImgShow,QString::fromLocal8Bit("显示"),QString::fromUtf8(":/new/prefix1/Resources/mActionAnalysis1.png"),SLOT(LayView()));

	CreateAction(mAction2,QString::fromLocal8Bit("对象均值"),mMenuImgShow,QString::fromLocal8Bit("显示"),
		mToolBarImgShow,QString::fromLocal8Bit("显示"),QString::fromLocal8Bit(":/new/prefix1/Resources/mActionAnalysis1.png"),SLOT(ObjMeanView()));

	CreateAction(mAction3,QString::fromLocal8Bit("特征显示"),mMenuImgShow,QString::fromLocal8Bit("显示"),
		mToolBarImgShow,QString::fromLocal8Bit("显示"),QString::fromUtf8(":/new/prefix1/Resources/mActionAnalysis1.png"),SLOT(FeatureView()));

	CreateAction(mAction4,QString::fromLocal8Bit("分类结果显示"),mMenuImgShow,QString::fromLocal8Bit("显示"),
		mToolBarImgShow,QString::fromLocal8Bit("显示"),QString::fromUtf8(":/new/prefix1/Resources/mActionAnalysis1.png"),SLOT(ClassResultView()));

	CreateAction(mAction10,QString::fromLocal8Bit("对象边界显示"),mMenuImgShow,QString::fromLocal8Bit("显示"),
		mToolBarImgShow,QString::fromLocal8Bit("显示"),QString::fromUtf8(":/new/prefix1/Resources/mActionAnalysis1.png"),SLOT(ObjBorderView()));

	mMenuImgShow->addSeparator();

	CreateAction(mAction0,QString::fromLocal8Bit("多尺度分割"),mMenuImgSegObj,QString::fromLocal8Bit("分割"),
		mToolBarImgSegObj,QString::fromLocal8Bit("分割"),QString::fromUtf8(":/new/prefix1/Resources/mActionAnalysis1.png"),SLOT(MultiSegment()));

	CreateAction(mAction5,QString::fromLocal8Bit("选择对象层"),mMenuImgSegObj,QString::fromLocal8Bit("分割"),
		mToolBarImgSegObj,QString::fromLocal8Bit("分割"),QString::fromUtf8(":/new/prefix1/Resources/mActionAnalysis3.png"),SLOT(SelectObjLay()));

	CreateAction(mAction6,QString::fromLocal8Bit("删除对象层"),mMenuImgSegObj,QString::fromLocal8Bit("分割"),
		mToolBarImgSegObj,QString::fromLocal8Bit("分割"),QString::fromUtf8(":/new/prefix1/Resources/mActionAnalysis3.png"),SLOT(DelectObjLay()));

	CreateAction(mAction7,QString::fromLocal8Bit("基于分类的分割"),mMenuImgSegObj,QString::fromLocal8Bit("分割"),
		mToolBarImgSegObj,QString::fromLocal8Bit("分割"),QString::fromUtf8(":/new/prefix1/Resources/mActionAnalysis3.png"),SLOT(ClassSegment()));

	mMenuImgSegObj->addSeparator();

	CreateAction(mAction7,QString::fromLocal8Bit("分类"),mMenuImgClass,QString::fromLocal8Bit("影像分类"),
		mToolBarImgClass,QString::fromLocal8Bit("影像分类"),QString::fromUtf8(":/new/prefix1/Resources/mActionAnalysis3.png"),SLOT(Classification()));

	CreateAction(mAction7,QString::fromLocal8Bit("删除分类"),mMenuImgClass,QString::fromLocal8Bit("影像分类"),
		mToolBarImgClass,QString::fromLocal8Bit("影像分类"),QString::fromUtf8(":/new/prefix1/Resources/mActionAnalysis3.png"),SLOT(DeleteClassification()));

	CreateAction(mAction7,QString::fromLocal8Bit("分类后编辑"),mMenuImgClass,QString::fromLocal8Bit("影像分类"),
		mToolBarImgClass,QString::fromLocal8Bit("影像分类"),QString::fromUtf8(":/new/prefix1/Resources/mActionAnalysis3.png"),SLOT(EditClassification()));

	//在菜单栏添加子菜单
	if(menubar)
	{	
		menubar->insertMenu(mIface->pluginMenu()->menuAction(),mMenuImgShow);
		menubar->insertMenu(mIface->pluginMenu()->menuAction(),mMenuImgSegObj);
		menubar->insertMenu(mIface->pluginMenu()->menuAction(),mMenuImgClass);
	}


//	添加“读入数据”菜单
	if(menubar)
	{
		mAction12 = new QAction(QString::fromLocal8Bit("新建工程"), this);
		mAction19 = new QAction(QString::fromLocal8Bit("打开工程"), this);
		mAction20 = new QAction(QString::fromLocal8Bit("保存工程"), this);
		mAction21 = new QAction(QString::fromLocal8Bit("另存为工程"), this);
		mAction22 = new QAction(QString::fromLocal8Bit("关闭工程"), this);
		//QIcon icon1;
		//icon1.addFile(QString::fromUtf8("D:\\qgis\\qgis-release-1_8\\vs2005\\output\\bin\\relwithdebinfo\\Resources\\mActionAddRasterLayer.png"), QSize(), QIcon::Normal, QIcon::Off);
		//mAction12->setIcon(icon1);
		if(mIface->fileMenu())
		{
			mIface->fileMenu()->insertAction(mIface->actionNewProject(),mAction12);
			mIface->fileMenu()->insertAction(mIface->actionNewProject(),mAction19);
			mIface->fileMenu()->insertAction(mIface->actionNewProject(),mAction20);
			mIface->fileMenu()->insertAction(mIface->actionNewProject(),mAction21);
			mIface->fileMenu()->insertAction(mIface->actionNewProject(),mAction22);
			mIface->fileMenu()->insertAction(mIface->actionNewProject(),mIface->fileMenu()->addSeparator());
		}
		else
		{
			mMenuImgClass->addAction(mAction12);
			mMenuImgClass->addAction(mAction19);
			mMenuImgClass->addAction(mAction20);
			mMenuImgClass->addAction(mAction21);
			mMenuImgClass->addAction(mAction22);
		}
		connect(mAction12,SIGNAL(activated()),this,SLOT(CreateProject()));
	}


	//添加“关于”菜单
	if(menubar)
	{
		mAboutDlg = new QAction(QString::fromLocal8Bit("关于“高分辨率遥感影像滑坡检测系统”"), this);
		QIcon icon1;
		QString strPath=QgsApplication::iconsPath();
		icon1.addFile(strPath+QString::fromUtf8("/app.png"), QSize(), QIcon::Normal, QIcon::Off);
		mAboutDlg->setIcon(icon1);

		if(mIface->helpMenu())
		{
			mIface->helpMenu()->addAction(mAboutDlg);
			mIface->helpMenu()->removeAction(mIface->actionQgisHomePage());
			mIface->helpMenu()->removeAction(mIface->actionCheckQgisVersion());
			mIface->helpMenu()->removeAction(mIface->actionHelpContents());
			mIface->helpMenu()->removeAction(mIface->actionAbout());
		}
		else
		{
			mMenuImgClass->addAction(mAboutDlg);
		}
		connect(mAboutDlg,SIGNAL(activated()),this,SLOT(ThisAboutDlg()));
	}

	QWidget *dockWidgetContents_2;
	QGridLayout *gridLayout;

	//添加类层次视图
	dockWidget_2 = new QDockWidget(QString::fromLocal8Bit("类层次视图"),mpMainWindow);
	dockWidget_2->setObjectName(QString::fromUtf8("dockWidget_2"));
	dockWidget_2->setMinimumSize(QSize(290, 250));
	dockWidget_2->setFeatures( QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable );//可以移动

	dockWidgetContents_2 = new QWidget();//往类层次视图里面加东西
	dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));

	gridLayout = new QGridLayout(dockWidgetContents_2);//设置布局
	gridLayout->setSpacing(6);
	gridLayout->setContentsMargins(3, 3, 3, 3);
	gridLayout->setObjectName(QString::fromUtf8("gridLayout"));


	treeWidget_2 = new QTreeWidget(dockWidgetContents_2);
	QTreeWidgetItem *__qtreewidgetitem_2 = new QTreeWidgetItem();
	__qtreewidgetitem_2->setText(0, QString::fromUtf8(""));
	treeWidget_2->setHeaderItem(__qtreewidgetitem_2);
	treeWidget_2->setObjectName(QString::fromUtf8("treeWidget_2"));
	treeWidget_2->setHeaderHidden(true);

	gridLayout->addWidget(treeWidget_2, 0, 0, 1, 1);

	dockWidget_2->setWidget(dockWidgetContents_2);//把树目录加入类层次视图中
	dockWidget_2->setAllowedAreas( Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
	mpMainWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget_2);//把类层次视图加入主视图中
//	mpMainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_2);//把类层次视图加入主视图中

	ShowContextMenu(treeWidget_2);

	if(InitialDockTree2(treeWidget_2)!=0)
	{
		QMessageBox::about(0,QString::fromLocal8Bit("提示…"),
			QString::fromLocal8Bit("初始化类层次视图失败！\n")); 
	}
	connect(treeWidget_2,SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int )),this,SLOT(SelectXingZheng(QTreeWidgetItem *, int )));

	//添加特征列表视图
	QWidget *dockWidgetContents_3;
	QGridLayout *gridLayout1;
	dockWidget_3 = new QDockWidget(QString::fromLocal8Bit("特征列表视图"),mpMainWindow);
	dockWidget_3->setObjectName(QString::fromUtf8("dockWidget_3"));
	dockWidget_3->setMinimumSize(QSize(290, 250));
	dockWidget_3->setFeatures( QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetFloatable);//可以移动

	dockWidgetContents_3 = new QWidget();//往特征列表视图里面加东西
	dockWidgetContents_3->setObjectName(QString::fromUtf8("dockWidgetContents_3"));

	gridLayout1 = new QGridLayout(dockWidgetContents_3);//设置布局
	gridLayout1->setSpacing(6);
	gridLayout1->setContentsMargins(3, 3, 3, 3);
	gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));


	treeWidget_3 = new QTreeWidget(dockWidgetContents_3);
	QTreeWidgetItem *__qtreewidgetitem_3 = new QTreeWidgetItem();
	__qtreewidgetitem_3->setText(0, QString::fromUtf8(""));
	treeWidget_3->setHeaderItem(__qtreewidgetitem_3);
	treeWidget_3->setObjectName(QString::fromUtf8("treeWidget_3"));
	treeWidget_3->setHeaderHidden(true);

	gridLayout1->addWidget(treeWidget_3, 0, 0, 1, 1);

	dockWidget_3->setWidget(dockWidgetContents_3);//把树目录加入类层次视图中
	dockWidget_3->setAllowedAreas( Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
	mpMainWindow->addDockWidget(Qt::RightDockWidgetArea, dockWidget_3);//把类层次视图加入主视图中
//	mpMainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_3);//把特征列表视图加入主视图中

	QString strPath1=QgsApplication::prefixPath();
	if(InitialDockTree3(strPath1+QString::fromLocal8Bit("/data/system.mdb"),treeWidget_3)!=0)
	{
		QMessageBox::about(0,QString::fromLocal8Bit("提示…"),
			QString::fromLocal8Bit("初始化特征列表视图失败！\n")); 
	}

	connect(treeWidget_3,SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int )),this,SLOT(SelectXingZheng1(QTreeWidgetItem *, int )));
	connect(mAction0,SIGNAL(activated()),this,SLOT(MultiSegment()));
	//添加对象信息视图
	QWidget *dockWidgetContents_4;
	QGridLayout *gridLayout2;
	dockWidget_4 = new QDockWidget(QString::fromLocal8Bit("对象信息视图"),mpMainWindow);
	dockWidget_4->setObjectName(QString::fromUtf8("dockWidget_4"));
	dockWidget_4->setMinimumSize(QSize(290, 280));
	dockWidget_4->setFeatures( QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetFloatable);//可以移动

	dockWidgetContents_4 = new QWidget();//往对象信息视图里面加东西
	dockWidgetContents_4->setObjectName(QString::fromUtf8("dockWidgetContents_4"));

	gridLayout2 = new QGridLayout(dockWidgetContents_4);//设置布局
	gridLayout2->setSpacing(6);
	gridLayout2->setContentsMargins(3,3, 3, 3);
	gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
	/*QSplitter* splitter=new QSplitter(Qt::Horizontal,dockWidgetContents_4);
	splitter->setOpaqueResize(false);
	splitter->setHandleWidth(1);

	listWidget1_4 = new QListWidget(dockWidgetContents_4);
	listWidget1_4->setObjectName(QString::fromUtf8("listWidget1_4"));

	listWidget2_4 = new QListWidget(dockWidgetContents_4);
	listWidget2_4->setObjectName(QString::fromUtf8("listWidget2_4"));
	
	splitter->addWidget(listWidget1_4);
	splitter->addWidget(listWidget2_4);*/

	tableWidget=new QTableView(dockWidgetContents_4);
	IMG_model = new QStandardItemModel();//准备数据模型
	IMG_model->setHorizontalHeaderItem(0, new QStandardItem(QString::fromLocal8Bit("特征名")));
	IMG_model->setHorizontalHeaderItem(1, new QStandardItem(QString::fromLocal8Bit("特征值")));
	tableWidget->setObjectName(QString::fromUtf8("tableWidget_4"));
	tableWidget->setModel(IMG_model);//利用setModel()方法将数据模型与QTableView绑定
	//tableWidget->horizontalHeader()->setResizeMode(0, QHeaderView::Fixed); //设置列宽不可变动，即不能通过鼠标拖动增加列宽  
	//tableWidget->horizontalHeader()->setResizeMode(1, QHeaderView::Fixed); 
	tableWidget->verticalHeader()->hide();//隐藏行头
	tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置表格的单元为只读属性，即不能编辑
	tableWidget->setColumnWidth(0,180);
	tableWidget->setColumnWidth(1,150);
	tableWidget->setRowHeight(0,3);
	tableWidget->setShowGrid(false);
	tableWidget->verticalHeader()->hide();
	tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	gridLayout2->addWidget(tableWidget, 0, 0, 2, 2);
	//QTableWidgetItem* item =new QTableWidgetItem();
	//item->setText(QString::fromLocal8Bit("特征对象名"));
	//tableWidget->setHorizontalHeaderItem(0,item);
	//QTableWidgetItem* item1 =new QTableWidgetItem();
	//item1->setText(QString::fromLocal8Bit("特征对象值"));
	//tableWidget->setHorizontalHeaderItem(1,item1);
	dockWidget_4->setWidget(dockWidgetContents_4);//把树目录加入对象信息视图中
	dockWidget_4->setAllowedAreas( Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );//左右停靠
	mpMainWindow->addDockWidget(Qt::RightDockWidgetArea, dockWidget_4);//把类层次视图加入主视图中

	if(InitialDockTable(IMG_model,tableWidget)!=0)
	{
		QMessageBox::about(0,QString::fromLocal8Bit("提示…"),QString::fromLocal8Bit("初始化对象信息视图失败！\n")); 
	}

	m_statusBar=mpMainWindow->statusBar();
	if(m_statusBar)
	{
		mProgressBar = new QProgressBar(m_statusBar);
		mProgressBar->setMaximumWidth( 100 );
		mProgressBar->setMinimumSize(200,1);

		m_statusBar->insertPermanentWidget(0, mProgressBar, 1 );
		m_statusBar->setObjectName("statusbar");
		//初始化进度条
//		InitalProgressBar((void *)mProgressBar,(void *)m_statusBar,"QT");
	}
	////去除多余工具栏
	//mpMainWindow->removeToolBar(mIface->helpToolBar());
	//mpMainWindow->removeToolBar(mIface->databaseToolBar());
	//mpMainWindow->removeToolBar(mIface->webToolBar());
	//mpMainWindow->removeToolBar(mIface->databaseToolBar());
	//mpMainWindow->removeToolBar(mIface->rasterToolBar());
	//mpMainWindow->removeToolBar(mIface->vectorToolBar());
	//mpMainWindow->removeToolBar(mIface->layerToolBar());
	mIface->layerToolBar()->removeAction(mIface->actionAddPgLayer());
	mIface->layerToolBar()->removeAction(mIface->actionAddWmsLayer());
	
	//////////////////////////////////////////////////////////////////////////
	//添加启动qgs工程
	//暂时先屏蔽掉
//	strPath=strPath.replace('/','\\');
//	mIface->addProject(QString::fromLocal8Bit("D:\qgis\data\lsy_qrs.qgs"));
}
//程序的析构卸载相关操作
void LSY_QRS::unload()
{
	//移除关于对话框
	if(mAboutDlg)
	{
		if(mIface->helpMenu())
		{
			mIface->helpMenu()->removeAction(mAboutDlg);
		}
		else
		{
			mMenuImgClass->removeAction(mAboutDlg);
		}
	}

	//移除工具栏
	if(mToolBarImgClass && mpMainWindow)
	{
		mpMainWindow->removeToolBar(mToolBarImgClass);
	}
	if(mToolBarImgSegObj && mpMainWindow)
	{
		mpMainWindow->removeToolBar(mToolBarImgSegObj);
	}
	if(mToolBarImgShow && mpMainWindow)
	{
		mpMainWindow->removeToolBar(mToolBarImgShow);
	}

	//清除显示菜单
	if(mMenuImgShow)
	{
		mMenuImgShow->clear();
		delete mMenuImgShow;
		mMenuImgShow=0;
	}
	else
	{
		mIface->removeToolBarIcon(mAction1);
		mIface->removePluginMenu(QString::fromLocal8Bit("显示"), mAction1);
		delete mAction1;
		mAction1=NULL;

		mIface->removeToolBarIcon(mAction2);
		mIface->removePluginMenu(QString::fromLocal8Bit("显示"), mAction2);
		delete mAction2;
		mAction2=NULL;

		mIface->removeToolBarIcon(mAction3);
		mIface->removePluginMenu(QString::fromLocal8Bit("显示"), mAction3);
		delete mAction3;
		mAction3=NULL;

		mIface->removeToolBarIcon(mAction4);
		mIface->removePluginMenu(QString::fromLocal8Bit("显示"), mAction4);
		delete mAction4;
		mAction4=NULL;

		mIface->removeToolBarIcon(mAction10);
		mIface->removePluginMenu(QString::fromLocal8Bit("显示"), mAction10);
		delete mAction10;
		mAction10=NULL;
	}
	//清除分割菜单
	if(mMenuImgSegObj)
	{
		mMenuImgSegObj->clear();
		delete mMenuImgSegObj;
		mMenuImgSegObj=0;
	}
	else
	{
		mIface->removeToolBarIcon(mAction0);
		mIface->removePluginMenu(QString::fromLocal8Bit("分割"), mAction0);
		delete mAction0;
		mAction0=NULL;

		mIface->removeToolBarIcon(mAction5);
		mIface->removePluginMenu(QString::fromLocal8Bit("分割"), mAction5);
		delete mAction5;
		mAction5=NULL;

		mIface->removeToolBarIcon(mAction6);
		mIface->removePluginMenu(QString::fromLocal8Bit("分割"), mAction6);
		delete mAction6;
		mAction6=NULL;

		mIface->removeToolBarIcon(mAction7);
		mIface->removePluginMenu(QString::fromLocal8Bit("分割"), mAction7);
		delete mAction7;
		mAction7=NULL;
	}
	//清除影像分类菜单
	if(mMenuImgClass)
	{
		mMenuImgClass->clear();
		delete mMenuImgClass;
		mMenuImgClass=0;
	}
	else
	{
		mIface->removeToolBarIcon(mAction8);
		mIface->removePluginMenu(QString::fromLocal8Bit("分割"), mAction8);
		delete mAction8;
		mAction8=NULL;

		mIface->removeToolBarIcon(mAction9);
		mIface->removePluginMenu(QString::fromLocal8Bit("分割"), mAction9);
		delete mAction9;
		mAction9=NULL;

		mIface->removeToolBarIcon(mAction11);
		mIface->removePluginMenu(QString::fromLocal8Bit("分割"), mAction11);
		delete mAction11;
		mAction11=NULL;
	}

	if(mpMainWindow) 
	{
		mpMainWindow->removeDockWidget(dockWidget_2);
		mpMainWindow->removeDockWidget(dockWidget_3);
		mpMainWindow->removeDockWidget(dockWidget_4);
	}
	ReleaseProgBar();
//	delete[] ImgArry;
}
void LSY_QRS::CreateAction(QAction*& action,QString name,QMenu*& mMenu,QString name1,QToolBar*& mToolBar,QString name2,QString icon,const char *receiverMember)
{	
	//创建action
	action = new QAction(name, this);
	QIcon icon1;
	icon1.addFile(icon, QSize(), QIcon::Normal, QIcon::Off);
	action->setIcon(icon1);

	//添加到菜单
	if(mMenu) 
	{
		mMenu->addAction(action);
	}
	else
	{
		mIface->addPluginToMenu(name1,action);//如果菜单不存在，则功能加在插件菜单下
	}

	//添加到工具条
	if(mToolBar)
	{
		mToolBar->addAction(action);
		mToolBar->setWindowTitle(name2);
	}
	else
	{
		mIface->addToolBarIcon(action);
	}

	connect(action, SIGNAL(activated()), this, receiverMember);//连接触发事件

	mActionList.push_back(action);
}

void LSY_QRS::ThisAboutDlg()
{
	/*QAboutDlg dlg;
	dlg.setModal(true);
	dlg.exec();*/
}


//获取系统栅格图层文件路径
QString LSY_QRS::inputFile() const
{
	QMap<QString, QgsMapLayer*> mapLayers = QgsMapLayerRegistry::instance()->mapLayers();
	QMap<QString, QgsMapLayer*>::iterator layer_it = mapLayers.begin();

	//insert available input layers
	QgsRasterLayer* rl = qobject_cast<QgsRasterLayer *>( layer_it.value() );
	if ( rl )
	{
		QgsMapLayer* inputLayer = QgsMapLayerRegistry::instance()->mapLayer((QVariant(rl->id())).toString() );
		if (!inputLayer )
		{
			return "";
		}
		else
		{
			QString inputFilePath = inputLayer->source();
			return inputFilePath;
		}
	}
	else
	{
		return "";
	}
}
//初始化树目录
long LSY_QRS::InitialDockTree2(QTreeWidget *treeWidget)
{
	QColor R(255,0,0);
	QColor	NULLColor(0,0,0,0);//初始化NULLColor

	XingZhTreeNode node(0,-1,QString::fromLocal8Bit("添加分类"),R);
	m_treeInfo.append(node);
	AddTreeItems(treeWidget,&m_treeInfo,NULL,&m_treeInfo[0]);
	return 0;
}
long LSY_QRS::InitialDockTree3(QString strIniFile,QTreeWidget *treeWidget)
{
	//if(ReadXingZhInfo(strIniFile,&m_treeInfo) !=0)
	//	return -1;

	//for (int iItem=0;iItem<m_treeInfo.count();iItem++)
	//{
	//	if( m_treeInfo[iItem].m_nParentID == -1 )
	//	{
	//		AddTreeItems(treeWidget,&m_treeInfo,NULL,&m_treeInfo[iItem]);
	//	}
	//}
	QColor	NULLColor(0,0,0,0);//初始化NULLColor

	XingZhTreeNode node(0,-1,QString::fromLocal8Bit("对象特征"),NULLColor);
	m_treeInfo1.append(node);
	XingZhTreeNode node1(1,0,QString::fromLocal8Bit("图层"),NULLColor);
	m_treeInfo1.append(node1);
	XingZhTreeNode node2(2,0,QString::fromLocal8Bit("形状"),NULLColor);
	m_treeInfo1.append(node2);
	XingZhTreeNode node3(3,0,QString::fromLocal8Bit("纹理"),NULLColor);
	m_treeInfo1.append(node3);
	XingZhTreeNode node4(4,-1,QString::fromLocal8Bit("类相关特征"),NULLColor);
	m_treeInfo1.append(node4);
	XingZhTreeNode node5(5,4,QString::fromLocal8Bit("与邻对象"),NULLColor);
	m_treeInfo1.append(node5);
	XingZhTreeNode node6(6,4,QString::fromLocal8Bit("与子对象"),NULLColor);
	m_treeInfo1.append(node6);
	for (int iItem=0;iItem<m_treeInfo1.count();iItem++)
	{	
		AddTreeItems(treeWidget,&m_treeInfo1,NULL,&m_treeInfo1[iItem]);
	}
	return 0;
}
long LSY_QRS::InitialDockTable(QStandardItemModel* model,QTableView* tableView)
{
	/*QTableWidgetItem* item=new QTableWidgetItem(QString::fromLocal8Bit("对象号："));
	item->setSizeHint(QSize(200,0));
	tableWidget->setItem(0,0,item);*/
	model->setItem(0, 0, new QStandardItem(QString::fromLocal8Bit("对象号：")));
	model->item(0, 0)->setTextAlignment(Qt::AlignLeft);//设置单元格文本居左
	model->item(0, 0)->setFont(QFont("宋体", 10, QFont::Black )); //将字体加粗
	return 0;
}

//读取外部文件初始化树目录
long LSY_QRS::ReadXingZhInfo(QString strIniFile,XingZhTreeInfo	*pTreeInfo)
{
	return 0;
}
//添加控件内容
long LSY_QRS::AddTreeItems(QTreeWidget *pTreeWidget,XingZhTreeInfo *pTreeInfo,QTreeWidgetItem *pParentItem,const XingZhTreeNode *pParentNode)
{
	if(pTreeInfo==NULL || pTreeWidget==NULL || pParentNode==NULL)
		return -1;
	QTreeWidgetItem  *item=NULL;//new QTreeWidgetItem(treeWidget,QStringList(LayerPath));
	QColor	NULLColor(0,0,0,0);//初始化NULLColor

	if(pParentItem==NULL && pParentNode->m_nParentID==-1)//没有父对象,添加新父对象
	{
		item=new QTreeWidgetItem(pTreeWidget,QStringList(pParentNode->m_strName));
		if (pParentNode->m_color!=NULLColor)
		{
			item->setData(0,1,pParentNode->m_color);
			item->setData(1,0,pParentNode->m_strName);		
			pTreeWidget->addTopLevelItem(item);
			return AddTreeItems(pTreeWidget,pTreeInfo,item,pParentNode);
		}
		else
		{
			item->setData(0,0,pParentNode->m_strName);		
			pTreeWidget->addTopLevelItem(item);
			return AddTreeItems(pTreeWidget,pTreeInfo,item,pParentNode);
		}
	}
	else if(pParentItem /* && pParentNode->m_nParentID >= 0*/)//有父对象，在父对象下添加子对象
	{
		int iItem=0;
		for (iItem=0;iItem<pTreeInfo->count();iItem++)
		{
			const XingZhTreeNode *pCurNode=&pTreeInfo->at(iItem);
			if(pCurNode->m_nParentID == pParentNode->m_nID)
			{		
				item=new QTreeWidgetItem(pParentItem,QStringList(pCurNode->m_strName));
				if (pParentNode->m_color!=NULLColor)
				{
					item->setData(0,1,pCurNode->m_color);
					item->setData(1,0,pCurNode->m_strName);		
					pParentItem->addChild(item);
					return AddTreeItems(pTreeWidget,pTreeInfo,item,pCurNode);
				}
				else
				{
					item->setData(0,0,pCurNode->m_strName);		
					pParentItem->addChild(item);
					return AddTreeItems(pTreeWidget,pTreeInfo,item,pCurNode);
				}
			}
		}
		if(iItem==pTreeInfo->count())
			return 0;
	}
	else
	{
		return -1;
	}
	return 0;
}
long LSY_QRS::AddTableItems(QStandardItemModel* model,QTableView* tableView,QString name,QString num)
{ 
	int rowCount=model->rowCount();
	model->setRowCount(rowCount+1);
	tableView->setRowHeight(1,3);
	model->setItem(rowCount+1, 0, new QStandardItem(name));
	model->setItem(rowCount+1, 1, new QStandardItem(num));
	model->item(rowCount+1, 0)->setTextAlignment(Qt::AlignLeft);//设置单元格文本居左
	model->item(rowCount+1, 1)->setTextAlignment(Qt::AlignLeft);//设置单元格文本居左
	return 0;
}

//void LSY_QRS::MapFrame(char* FilePath,char* MapName)
//{
//	QString		strFilePath = "",strFramePath = "";
//	char		szFramePath[512] = {0};
//	QTime		cunTime;
//	//QDateTime   cunTime;
//	OGRRegisterAll();      //注册格式
//	const char *pszDriverName = "ESRI Shapefile";
//	OGRSFDriver *poDriver;
//	poDriver = OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName(pszDriverName);//获取数据驱动
//	if(poDriver == NULL)
//	{
//		QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("驱动注册失败！！"));
//	}
//	GDALDataset *poDataset;                        //打开所需要的制作的专题图获取信息
//	GDALAllRegister();
//	/////////////////////////////////////////////////////////////////////////////////////////////调试用创建矢量正确与否
//	//QFileDialog dlg(this,QString::fromLocal8Bit("选择文件"));
//	//dlg.setAcceptMode(QFileDialog::AcceptOpen);
//	//QString LayerPath=dlg.getOpenFileName();
//	//QByteArray path= LayerPath.toLatin1();         //QString转char*
//	//const char *FilePath = path.data();
//	////////////////////////////////////////////////////////////////////////////////////////////////
//	poDataset = (GDALDataset*) GDALOpen(FilePath,GA_ReadOnly);
//	if(poDataset==NULL)
//		QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("读取数据失败！！"));
//	int ImgXSize=poDataset->GetRasterXSize();
//	int ImgYSize=poDataset->GetRasterYSize();
//	double Trans[6];                   //坐标转换参数数组,作为GetGeoTransform()函数的参数
//	poDataset->GetGeoTransform(Trans);
//
//
//	strFilePath = QString::fromLocal8Bit(FilePath);
//	int DirLen = strFilePath.lastIndexOf("/");
//	strFramePath = strFilePath.left(DirLen)+"/";
//	//cunTime.currentDateTime().toString()
//	strFramePath += cunTime.currentTime().toString("HHmmss");
//	strFramePath +="_Frame.shp";
//	strcpy(szFramePath,(const char*)strFramePath.toLocal8Bit());
//	OGRDataSource *poDS;       //创建矢量数据文件
//	//poDS = poDriver->CreateDataSource("FrameShapeFile.shp",NULL );    //创建在当前目录下的ShapeFile文件    需要改变一下
//	poDS = poDriver->CreateDataSource(szFramePath,NULL);
//	if(poDS == NULL)
//	{
//		QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("创建文件失败！！"));
//	}
//
//	OGRLayer *poLayer;
//	const char *prj=poDataset->GetProjectionRef();             //获取栅格影像的空间参考信息
//	OGRSpatialReference oSRS;  
//	oSRS.SetFromUserInput(prj);                                //将获得的空间参考信息字符串做为文本一次性赋给矢量数据的OGRSpatialReference对象
//	poLayer = poDS->CreateLayer(FilePath,&oSRS);               //创建图层（仅一层）
//	if( poLayer == NULL )
//	{
//		QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("创建图层失败！！"));
//	}
//
//	OGRFieldDefn oField( "Line", OFTString );    //创建属性字段point，其与坐标点（X,Y）有关
//	oField.SetWidth(126);                         //创建字段宽度
//	if( poLayer->CreateField( &oField ) != OGRERR_NONE )
//	{
//		QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("创建属性字段失败！！"));
//	}
//	OGRFeature *poFeature;          //创建feature并写入磁盘
//	poFeature = OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//	poFeature->SetField("Line",MapName);
//	//绘制外边框
//	//Trans[0]是左上角像元的东坐标；a1
//	//Trans[3]是左上角像元的北坐标；a2
//	//Trans[1]是影像宽度上的分辨率；b1
//	//Trans[5]是影像高度上的分辨率；c2
//	//Trans[2]是旋转, 0表示上面为北方； c1
//	//Trans[4]是旋转, 0表示上面为北方； b2
//	//相应的放射变换公式：
//	//Xpixel、YlineL图像坐标   Xp Yp 地理坐标
//	//1、图像坐标转地理坐标
//	//Xp = geoTransform [0] + Xpixel*geoTransform [1] + Yline*geoTransform [2];
//	//Yp = geoTransform [3] + Xpixel*geoTransform [4] + Yline*geoTransform [5];
//	OGRLineString Line;
//	/***********************修改***修改****修改***修改*****修改****修改****修改***修改***修改****修改***修改****修改*****************************/
//	OGRPoint Point1(Trans[0]-(ImgXSize*Trans[1]+ImgYSize*Trans[2])/3.4,Trans[3]-(ImgXSize*Trans[4]+ImgYSize*Trans[5])/8);        //以东北记录位置(四个角点)    其中为了将外边框外扩一些（各扩.1单位），将相应的点加上或者是减去.1.
//	OGRPoint Point2(Trans[0]+ImgXSize*Trans[1]+ImgYSize*Trans[2]+(ImgXSize*Trans[1]+ImgYSize*Trans[2])/3.8,Trans[3]-(ImgXSize*Trans[4]+ImgYSize*Trans[5])/8);
//	OGRPoint Point3(Trans[0]+ImgXSize*Trans[1]+ImgYSize*Trans[2]+(ImgXSize*Trans[1]+ImgYSize*Trans[2])/3.82,Trans[3]+ImgXSize*Trans[4]+ImgYSize*Trans[5]+(ImgXSize*Trans[4]+ImgYSize*Trans[5])/3);
//	OGRPoint Point4(Trans[0]-(ImgXSize*Trans[1]+ImgYSize*Trans[2])/3.4,Trans[3]+ImgXSize*Trans[4]+ImgYSize*Trans[5]+(ImgXSize*Trans[4]+ImgYSize*Trans[5])/3);
//	Line.addPoint(&Point4);              //1        2
//	Line.addPoint(&Point1);              //4        3
//	Line.addPoint(&Point2);
//	Line.addPoint(&Point3);  
//	Line.addPoint(&Point4);              //增加线的顶点并标明其位置	/*********************************************************************************************************************************************/	
//	poFeature->SetGeometryDirectly(&Line);
//	if (poLayer->CreateFeature(poFeature)!=OGRERR_NONE)
//	{
//		QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("在矢量数据中创建要素失败！！"));
//		exit(1);
//	}
//	OGRDataSource::DestroyDataSource( poDS );
//	//QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("生成图框成功！！"));
//
//	/*****************************************************************************************************************
//	显示生成的图例
//	*****************************************************************************************************************/
//
//	QgsMapCanvas *m_pMapCanvas= mIface->mapCanvas();
//	QList<QgsMapCanvasLayer> m_myLayerSet;
//	QgsMapLayerRegistry *m_pMapLayer;
//	m_pMapLayer=QgsMapLayerRegistry::instance();
//
//
//	QgsVectorLayer *pLayerV=new QgsVectorLayer(strFramePath,QString::fromLocal8Bit("FrameShapeFile.shp"),"ogr");
//
//	if (pLayerV->isValid())
//	{
//		//添加图层到图层集中
//		m_pMapLayer->addMapLayer(pLayerV,true);
//
//		//矢量数据放前面,顺序为点线面
//		int index=0;
//		/*for (;index<m_myLayerSet.count();index++)
//		{
//		QgsMapLayer::LayerType ltype=m_myLayerSet.at(index).layer()->type();
//		if(ltype!=QgsMapLayer::VectorLayer)
//		break;
//		else
//		{
//		QGis::GeometryType  gtype1=pLayerV->geometryType();
//		QgsVectorLayer *pLayerVec=(QgsVectorLayer *)m_myLayerSet.at(index).layer();
//		if(pLayerVec)
//		{
//		QGis::GeometryType  gtype2=pLayerVec->geometryType();
//		if(gtype1<=gtype2)
//		{
//		break;
//		}
//		}
//		}
//		}*/
//		if(index<m_myLayerSet.count())
//			m_myLayerSet.insert(index,QgsMapCanvasLayer(pLayerV));
//		else
//			m_myLayerSet.append(QgsMapCanvasLayer(pLayerV));
//
//		QgsLabel * mypLabel;  
//
//		mypLabel=pLayerV->label();                    //得到关联mylayer的label指针  
//		QgsLabelAttributes * mypLabelAttributes;  
//		mypLabelAttributes = mypLabel->layerAttributes();  
//
//		QgsFieldMap myFields = pLayerV->dataProvider()->fields();  //得到矢量图层的字段列表 
//
//		mypLabel->setLabelField(QgsLabel::Text,myFields.size()-1); 
//
//		mypLabelAttributes->setColor(Qt::black);                    //设置label
//		//mypLabelAttributes->setOffset(11,0,1);      //第一个和第二个参数是坐标位置（东北）
//		//mypLabelAttributes->setSize(7,1);
//
//
//		/***********************修改***修改****修改***修改*****修改****修改****修改***修改***修改****修改***修改****修改*****************************/
//		mypLabelAttributes->setBold(true);
//
//		mypLabelAttributes->setAlignment(6);//设置显示位置在线的正上方	
//
//		double PolyrangeX=(Point2.getX()-Point1.getX())/30;    //假设每行排列30个字
//		double PolyrangeY=-(Point3.getY()-Point2.getY())/5;
//
//		mypLabelAttributes->setOffset(-(ImgXSize*Trans[1]+ImgYSize*Trans[2]+(ImgXSize*Trans[1]+ImgYSize*Trans[2])/8.4)/1.55,0,0);    //以边框的第一字段加标题
//		if(PolyrangeX<PolyrangeY*0.15)
//		{
//			mypLabelAttributes->setSize(PolyrangeY*0.193,0);
//		}
//		else
//		{
//			mypLabelAttributes->setSize(PolyrangeX*0.95,0);
//		}
//
//		/*********************************************************************************************************************************************/
//
//		//启用标注  
//		pLayerV->enableLabels(true);
//		//将图层添加到图层列表中
//	}
//}
//
//void LSY_QRS::MapIllustration(char* FilePath,int ClassNum,char* FirstName/* =NULL */,char* SecendName/* =NULL */,
//							  char* ThirdName/* =NULL */,char* FourthName/* =NULL */,char* FivethName/* =NULL */,char* SixthName/* =NULL */)
//{
//	QString		strFilePath = "",strLablePath = "";
//	char		szLablePath[512] = {0};
//	QTime		cunTime;
//	QFile		FileFind;
//	strFilePath = QString::fromLocal8Bit(FilePath);
//	int len = strFilePath.lastIndexOf("/");
//	strLablePath  = strFilePath.left(len);
//	strLablePath += "/";
//	strLablePath  = strLablePath + cunTime.currentTime().toString("HHmmss");
//	strLablePath +="_PolyFile.shp";
//	if (FileFind.exists(strLablePath))
//	{
//		FileFind.remove(strLablePath);
//	}
//	QString	 strColorPath=QgsApplication::prefixPath();		//色标文件夹
//	strColorPath +="\\data\\shpcolor.map.qml";
//	OGRRegisterAll();      //注册格式
//	const char *pszDriverName = "ESRI Shapefile";
//	OGRSFDriver *poDriver;
//	poDriver = OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName(pszDriverName);//获取数据驱动
//	if(poDriver == NULL)
//	{
//		QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("驱动注册失败！！"));
//		exit(1);
//	}
//	GDALDataset *poDataset;                        //打开所需要的制作的专题图获取信息
//	GDALAllRegister();
//	/////////////////////////////////////////////////////////////////////////////////////////////调试用创建矢量正确与否
//	//QFileDialog dlg(this,QString::fromLocal8Bit("选择文件"));
//	//dlg.setAcceptMode(QFileDialog::AcceptOpen);
//	//QString LayerPath=dlg.getOpenFileName();
//	//QByteArray path= LayerPath.toLatin1();         //QString转char*
//	//const char *FilePath = path.data();
//	////////////////////////////////////////////////////////////////////////////////////////////////
//	poDataset = (GDALDataset*) GDALOpen(FilePath,GA_ReadOnly);
//	if(poDataset==NULL)
//		QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("读取数据失败！！"));
//	int ImgXSize=poDataset->GetRasterXSize();
//	int ImgYSize=poDataset->GetRasterYSize();
//	double Trans[6];                   //坐标转换参数数组,作为GetGeoTransform()函数的参数
//	poDataset->GetGeoTransform(Trans);
//	OGRDataSource *poDS;       //创建矢量数据文件
//	strcpy(szLablePath,(const char*)strLablePath.toLocal8Bit());
//	poDS = poDriver->CreateDataSource(szLablePath,NULL );    //创建在当前目录下的ShapeFile文件
//	if(poDS == NULL)
//	{
//		QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("创建文件失败！！"));
//		exit(1);
//	}
//	OGRLayer *poLayer;
//	const char *prj=poDataset->GetProjectionRef();             //获取栅格影像的空间参考信息
//	OGRSpatialReference oSRS;  
//	oSRS.SetFromUserInput(prj);                                //将获得的空间参考信息字符串做为文本一次性赋给矢量数据的OGRSpatialReference对象
//	poLayer = poDS->CreateLayer(FilePath,&oSRS,wkbPolygon);               //创建图层（仅一层）
//	if( poLayer == NULL )
//	{
//		QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("创建图层失败！！"));
//		exit(1);
//	}
//	//int *pafScanblock;//存放数据的内存
//	//GDALRasterBand *poBand=poDataset->GetRasterBand(1);
//	//GDALDataType  dType=poBand->GetRasterDataType();
//	////一个像元占用的字节数
//	//int nTypeSize=GDALGetDataTypeSize(dType)/8;
//	//pafScanblock = (int *) CPLMalloc(nTypeSize*ImgXSize*ImgYSize);
//	//poBand->RasterIO( GF_Read, 0, 0,ImgXSize,ImgYSize, 
//	//	pafScanblock,ImgXSize,ImgYSize, dType,0, 0 );
//	//int Scale=0;
//	//int min=255;
//	//int max=0;
//	//for (int i=0;i<ImgXSize*ImgYSize;i++)
//	//{
//	//	if ((max<*(pafScanblock+i))&&(*(pafScanblock+i)<=255)&&(*(pafScanblock+i)>=0))
//	//		max=*(pafScanblock+i);
//	//}
//	//for (int i=0;i<ImgYSize*ImgXSize;i++)  //获取影像的最大最小值
//	//{
//	//	if ((min>*(pafScanblock+i))&&(*(pafScanblock+i)<=255)&&(*(pafScanblock+i)>=0))
//	//		min=*(pafScanblock+i);
//	//}
//	/**************修改***修改****修改***修改*****修改****修改****修改***修改***修改****修改***修改****修改******修改***修改****修改***修改*****修改****修改****修改***修改***修改****修改***修改****修改****************/
//	//double FirstColor=0;
//	//double SecendColor=0;
//	//double ThirdColor=0;
//	//double FourthColor=0;
//	//double FivethColor=0;
//	//double SixthColor=0;  
//	//switch (ClassNum)
//	//{
//	//case 2:
//	//	Scale=(max-min)/2;   //图像色彩分层
//	//	FirstColor=min+Scale/2;
//	//	SecendColor=FirstColor+Scale;
//	//	break;
//	//case 3:
//	//	Scale=(max-min)/3;
//	//	FirstColor=min+Scale/2;
//	//	SecendColor=FirstColor+Scale;
//	//	ThirdColor=SecendColor+Scale;
//	//	break;
//	//case 4:
//	//	Scale=(max-min)/4;
//	//	FirstColor=min+Scale/2;
//	//	SecendColor=FirstColor+Scale;
//	//	ThirdColor=SecendColor+Scale;
//	//	FourthColor=ThirdColor+Scale;
//	//	break;
//	//case 5:
//	//	Scale=(max-min)/5;
//	//	FirstColor=min+Scale/2;
//	//	SecendColor=FirstColor+Scale;
//	//	ThirdColor=SecendColor+Scale;
//	//	FourthColor=ThirdColor+Scale;
//	//	FivethColor=FourthColor+Scale;
//	//	break;
//	//case 6:
//	//	Scale=(max-min)/6;   //图像色彩分层
//	//	FirstColor=min+Scale/2;
//	//	SecendColor=FirstColor+Scale;
//	//	ThirdColor=SecendColor+Scale;
//	//	FourthColor=ThirdColor+Scale;
//	//	FivethColor=FourthColor+Scale;
//	//	SixthColor=FivethColor+Scale;  
//	//	break;
//	//}
//	OGRPoint Point1(Trans[0]-(ImgXSize*Trans[1]+ImgYSize*Trans[2])/5,Trans[3]-(ImgXSize*Trans[4]+ImgYSize*Trans[5])/8);        //以东北记录位置(四个角点)    其中为了将外边框外扩一些（各扩.1单位），将相应的点加上或者是减去.1.
//	OGRPoint Point2(Trans[0]+ImgXSize*Trans[1]+ImgYSize*Trans[2]+(ImgXSize*Trans[1]+ImgYSize*Trans[2])/5,Trans[3]-(ImgXSize*Trans[4]+ImgYSize*Trans[5])/8);
//	OGRPoint Point3(Trans[0]+ImgXSize*Trans[1]+ImgYSize*Trans[2]+(ImgXSize*Trans[1]+ImgYSize*Trans[2])/5,Trans[3]+ImgXSize*Trans[4]+ImgYSize*Trans[5]+(ImgXSize*Trans[4]+ImgYSize*Trans[5])/3);
//	OGRPoint Point4(Trans[0]-(ImgXSize*Trans[1]+ImgYSize*Trans[2])/5,Trans[3]+ImgXSize*Trans[4]+ImgYSize*Trans[5]+(ImgXSize*Trans[4]+ImgYSize*Trans[5])/3);
//
//	double PolyrangeX=(Point2.getX()-Point1.getX())/30;
//	double PolyrangeY=-(Point3.getY()-Point2.getY())/5;
//
//	double Xp1=Point4.getX()+PolyrangeX/15;                          //定位图例框的位置信息
//	double Yp1=Point4.getY()+PolyrangeY*0.65;
//	double Xp2=Xp1+PolyrangeX;
//	double Yp3=Yp1-PolyrangeY*0.15;
//
//	double Poly1Xp1=Xp1+PolyrangeX*6.2;
//	double Poly1Yp1=Yp1;
//	double Poly1Xp2=Xp2+PolyrangeX*6.2;
//	double Poly1Yp3=Yp3;
//
//	double Poly2Xp1=Poly1Xp1+PolyrangeX*6.2;
//	double Poly2Yp1=Yp1;
//	double Poly2Xp2=Poly1Xp2+PolyrangeX*6.2;
//	double Poly2Yp3=Yp3;
//
//	double Poly3Xp1=Xp1;
//	double Poly3Yp1=Yp3-PolyrangeY*0.1;
//	double Poly3Xp2=Xp2;
//	double Poly3Yp3=Poly3Yp1-PolyrangeY*0.15;
//
//	double Poly4Xp1=Poly3Xp1+PolyrangeX*6.2;
//	double Poly4Yp1=Poly3Yp1;
//	double Poly4Xp2=Poly3Xp2+PolyrangeX*6.2;
//	double Poly4Yp3=Poly3Yp3;
//
//	double Poly5Xp1=Poly4Xp1+PolyrangeX*6.2;
//	double Poly5Yp1=Poly3Yp1;
//	double Poly5Xp2=Poly4Xp2+PolyrangeX*6.2;
//	double Poly5Yp3=Poly3Yp3;	/**********************************************************************************************************************************************************/
//
//	//int ClassNum=6;//测试
//
//	if(ClassNum==2)
//	{
//		OGRFieldDefn oField( "FirstCol", OFTInteger );    //创建属性字段，其位置与边框有关
//		oField.SetWidth(32);      //创建字段宽度
//		OGRFieldDefn oField_1( "PolyLabel", OFTString );    //创建属性字段，其位置与边框有关
//		oField_1.SetWidth(32);
//		if( (poLayer->CreateField( &oField ) != OGRERR_NONE )||(poLayer->CreateField( &oField_1 ) != OGRERR_NONE))
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("创建属性字段失败！！"));
//			exit(1);
//		}
//		OGRFeature *poFeature;          //创建feature并写入磁盘
//		poFeature = OGRFeature::CreateFeature( poLayer->GetLayerDefn() );    //和层对应的属性绑定
//
//		//和层对应的属性进行绑定，以得到feature的单独的field
//		poFeature->SetField("FirstCol",0);
//		poFeature->SetField( "PolyLabel",FirstName);
//
//		OGRPolygon poly;
//		OGRLinearRing ring;
//		ring.addPoint(Xp1,Yp1);
//		ring.addPoint(Xp2,Yp1);
//		ring.addPoint(Xp2,Yp3);
//		ring.addPoint(Xp1,Yp3);
//
//		poly.addRing(&ring);
//		poFeature->SetGeometryDirectly(&poly);
//		if (poLayer->CreateFeature(poFeature)!=OGRERR_NONE)
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("在矢量数据中创建要素(feature)失败！！"));
//			exit(1);
//		}
//
//		//OGRFieldDefn oField_2( "SeCol", OFTInteger );    //创建属性字段，其位置与边框有关
//		//oField_2.SetWidth(32);      //创建字段宽度 
//		//OGRFieldDefn oField_2_1( "PolyLabel2", OFTString );    //创建属性字段，其位置与边框有关
//		//oField_2_1.SetWidth(32);
//		//if( (poLayer->CreateField( &oField_2 ) != OGRERR_NONE)||(poLayer->CreateField( &oField_2_1 ) != OGRERR_NONE ))
//		//{
//		//	QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("创建属性字段失败！！"));
//		//	exit(1);
//		//}
//
//		OGRFeature *poFeature1=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature1);  //与layer相关联
//
//		poFeature1->SetField("Color",1);
//		poFeature1->SetField( "PolyLabel",SecendName);
//
//		OGRPolygon poly1;
//		OGRLinearRing polyring;
//
//		polyring.addPoint(Poly1Xp1,Poly1Yp1);
//		polyring.addPoint(Poly1Xp2,Poly1Yp1);
//		polyring.addPoint(Poly1Xp2,Poly1Yp3);
//		polyring.addPoint(Poly1Xp1,Poly1Yp3);
//		poly1.addRing(&polyring);
//		poFeature1->SetGeometryDirectly(&poly1);
//		if (poLayer->CreateFeature(poFeature1)!=OGRERR_NONE)
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("在矢量数据中创建要素(feature)失败！！"));
//			exit(1);
//		}
//	}
//	if(ClassNum==3)
//	{
//		OGRFieldDefn oField( "Color", OFTInteger );    //创建属性字段，其位置与边框有关
//		oField.SetWidth(32);      //创建字段宽度
//		OGRFieldDefn oField_1( "PolyLabel", OFTString );    //创建属性字段，其位置与边框有关
//		oField_1.SetWidth(32);
//		if( (poLayer->CreateField( &oField ) != OGRERR_NONE )||(poLayer->CreateField( &oField_1 ) != OGRERR_NONE))
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("创建属性字段失败！！"));
//			exit(1);
//		}
//		OGRFeature *poFeature;          //创建feature并写入磁盘
//		poFeature = OGRFeature::CreateFeature( poLayer->GetLayerDefn() );    //和层对应的属性绑定
//		//和层对应的属性进行绑定，以得到feature的单独的field
//		poFeature->SetField("Color",0);
//		poFeature->SetField( "PolyLabel",FirstName);
//		OGRPolygon poly;
//		OGRLinearRing ring;
//		ring.addPoint(Xp1,Yp1);
//		ring.addPoint(Xp2,Yp1);
//		ring.addPoint(Xp2,Yp3);
//		ring.addPoint(Xp1,Yp3);
//		poly.addRing(&ring);
//		poFeature->SetGeometryDirectly(&poly);
//		if (poLayer->CreateFeature(poFeature)!=OGRERR_NONE)
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("在矢量数据中创建要素(feature)失败！！"));
//			exit(1);
//		} 
//
//		OGRFeature *poFeature1=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature1);  //与layer相关联
//
//		poFeature1->SetField("Color",1);
//		poFeature1->SetField( "PolyLabel",SecendName);
//
//		OGRPolygon poly1;
//		OGRLinearRing polyring;
//		polyring.addPoint(Poly1Xp1,Poly1Yp1);
//		polyring.addPoint(Poly1Xp2,Poly1Yp1);
//		polyring.addPoint(Poly1Xp2,Poly1Yp3);
//		polyring.addPoint(Poly1Xp1,Poly1Yp3);
//		poly1.addRing(&polyring);
//		poFeature1->SetGeometryDirectly(&poly1);
//		if (poLayer->CreateFeature(poFeature1)!=OGRERR_NONE)
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("在矢量数据中创建要素(feature)失败！！"));
//			exit(1);
//		}
//
//		OGRFeature *poFeature2=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature2);  //与layer相关联
//
//		poFeature2->SetField("Color",2);
//		poFeature2->SetField( "PolyLabel",ThirdName);
//		OGRPolygon poly2;
//		OGRLinearRing polyring2;
//		polyring2.addPoint(Poly2Xp1,Poly2Yp1);
//		polyring2.addPoint(Poly2Xp2,Poly2Yp1);
//		polyring2.addPoint(Poly2Xp2,Poly2Yp3);
//		polyring2.addPoint(Poly2Xp1,Poly2Yp3);
//		poly2.addRing(&polyring2);
//		poFeature2->SetGeometryDirectly(&poly2);
//		if (poLayer->CreateFeature(poFeature2)!=OGRERR_NONE)
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("在矢量数据中创建要素(feature)失败！！"));
//			exit(1);
//		}
//	}
//	if(ClassNum==4)
//	{
//		OGRFieldDefn oField( "Color", OFTInteger );    //创建属性字段，其位置与边框有关
//		oField.SetWidth(32);      //创建字段宽度
//		OGRFieldDefn oField_1( "PolyLabel", OFTString );    //创建属性字段，其位置与边框有关
//		oField_1.SetWidth(32);
//		if( (poLayer->CreateField( &oField ) != OGRERR_NONE )||(poLayer->CreateField( &oField_1 ) != OGRERR_NONE))
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("创建属性字段失败！！"));
//			exit(1);
//		}
//		OGRFeature *poFeature;          //创建feature并写入磁盘
//		poFeature = OGRFeature::CreateFeature( poLayer->GetLayerDefn() );    //和层对应的属性绑定
//		//和层对应的属性进行绑定，以得到feature的单独的field
//		poFeature->SetField("Color",0);
//		poFeature->SetField( "PolyLabel",FirstName);
//		OGRPolygon poly;
//		OGRLinearRing ring;
//		ring.addPoint(Xp1,Yp1);
//		ring.addPoint(Xp2,Yp1);
//		ring.addPoint(Xp2,Yp3);
//		ring.addPoint(Xp1,Yp3);
//		poly.addRing(&ring);
//		poFeature->SetGeometryDirectly(&poly);
//		if (poLayer->CreateFeature(poFeature)!=OGRERR_NONE)
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("在矢量数据中创建要素(feature)失败！！"));
//			exit(1);
//		} 
//
//		OGRFeature *poFeature1=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature1);  //与layer相关联
//
//		poFeature1->SetField("Color",1);
//		poFeature1->SetField( "PolyLabel",SecendName);
//
//		OGRPolygon poly1;
//		OGRLinearRing polyring;
//		polyring.addPoint(Poly1Xp1,Poly1Yp1);
//		polyring.addPoint(Poly1Xp2,Poly1Yp1);
//		polyring.addPoint(Poly1Xp2,Poly1Yp3);
//		polyring.addPoint(Poly1Xp1,Poly1Yp3);
//		poly1.addRing(&polyring);
//		poFeature1->SetGeometryDirectly(&poly1);
//		if (poLayer->CreateFeature(poFeature1)!=OGRERR_NONE)
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("在矢量数据中创建要素(feature)失败！！"));
//			exit(1);
//		}
//
//		OGRFeature *poFeature2=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature2);  //与layer相关联
//
//		poFeature2->SetField("Color",2);
//		poFeature2->SetField( "PolyLabel",ThirdName);
//		OGRPolygon poly2;
//		OGRLinearRing polyring2;
//		polyring2.addPoint(Poly2Xp1,Poly2Yp1);
//		polyring2.addPoint(Poly2Xp2,Poly2Yp1);
//		polyring2.addPoint(Poly2Xp2,Poly2Yp3);
//		polyring2.addPoint(Poly2Xp1,Poly2Yp3);
//		poly2.addRing(&polyring2);
//		poFeature2->SetGeometryDirectly(&poly2);
//		if (poLayer->CreateFeature(poFeature2)!=OGRERR_NONE)
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("在矢量数据中创建要素(feature)失败！！"));
//			exit(1);
//		}
//
//		OGRFeature *poFeature3=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature3);  //与layer相关联
//		poFeature3->SetField("Color",3);
//		poFeature3->SetField( "PolyLabel",FourthName);
//		OGRPolygon poly3;
//		OGRLinearRing polyring3;
//		polyring3.addPoint(Poly3Xp1,Poly3Yp1);
//		polyring3.addPoint(Poly3Xp2,Poly3Yp1);
//		polyring3.addPoint(Poly3Xp2,Poly3Yp3);
//		polyring3.addPoint(Poly3Xp1,Poly3Yp3);
//		poly3.addRing(&polyring3);
//		poFeature3->SetGeometryDirectly(&poly3);
//		if (poLayer->CreateFeature(poFeature3)!=OGRERR_NONE)
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("在矢量数据中创建要素(feature)失败！！"));
//			exit(1);
//		}
//	}
//	if(ClassNum==5)
//	{
//		OGRFieldDefn oField( "Color", OFTInteger );    //创建属性字段，其位置与边框有关
//		oField.SetWidth(32);      //创建字段宽度
//		OGRFieldDefn oField_1( "PolyLabel", OFTString );    //创建属性字段，其位置与边框有关
//		oField_1.SetWidth(32);
//		if( (poLayer->CreateField( &oField ) != OGRERR_NONE )||(poLayer->CreateField( &oField_1 ) != OGRERR_NONE))
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("创建属性字段失败！！"));
//			exit(1);
//		}
//		OGRFeature *poFeature;          //创建feature并写入磁盘
//		poFeature = OGRFeature::CreateFeature( poLayer->GetLayerDefn() );    //和层对应的属性绑定
//		//和层对应的属性进行绑定，以得到feature的单独的field
//		poFeature->SetField("Color",0);
//		poFeature->SetField( "PolyLabel",FirstName);
//		OGRPolygon poly;
//		OGRLinearRing ring;
//		ring.addPoint(Xp1,Yp1);
//		ring.addPoint(Xp2,Yp1);
//		ring.addPoint(Xp2,Yp3);
//		ring.addPoint(Xp1,Yp3);
//		poly.addRing(&ring);
//		poFeature->SetGeometryDirectly(&poly);
//		if (poLayer->CreateFeature(poFeature)!=OGRERR_NONE)
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("在矢量数据中创建要素(feature)失败！！"));
//			exit(1);
//		} 
//
//		OGRFeature *poFeature1=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature1);  //与layer相关联
//
//		poFeature1->SetField("Color",1);
//		poFeature1->SetField( "PolyLabel",SecendName);
//
//		OGRPolygon poly1;
//		OGRLinearRing polyring;
//		polyring.addPoint(Poly1Xp1,Poly1Yp1);
//		polyring.addPoint(Poly1Xp2,Poly1Yp1);
//		polyring.addPoint(Poly1Xp2,Poly1Yp3);
//		polyring.addPoint(Poly1Xp1,Poly1Yp3);
//		poly1.addRing(&polyring);
//		poFeature1->SetGeometryDirectly(&poly1);
//		if (poLayer->CreateFeature(poFeature1)!=OGRERR_NONE)
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("在矢量数据中创建要素(feature)失败！！"));
//			exit(1);
//		}
//
//		OGRFeature *poFeature2=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature2);  //与layer相关联
//
//		poFeature2->SetField("Color",2);
//		poFeature2->SetField( "PolyLabel",ThirdName);
//		OGRPolygon poly2;
//		OGRLinearRing polyring2;
//		polyring2.addPoint(Poly2Xp1,Poly2Yp1);
//		polyring2.addPoint(Poly2Xp2,Poly2Yp1);
//		polyring2.addPoint(Poly2Xp2,Poly2Yp3);
//		polyring2.addPoint(Poly2Xp1,Poly2Yp3);
//		poly2.addRing(&polyring2);
//		poFeature2->SetGeometryDirectly(&poly2);
//		if (poLayer->CreateFeature(poFeature2)!=OGRERR_NONE)
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("在矢量数据中创建要素(feature)失败！！"));
//			exit(1);
//		}
//
//		OGRFeature *poFeature3=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature3);  //与layer相关联
//		poFeature3->SetField("Color",3);
//		poFeature3->SetField( "PolyLabel",FourthName);
//		OGRPolygon poly3;
//		OGRLinearRing polyring3;
//		polyring3.addPoint(Poly3Xp1,Poly3Yp1);
//		polyring3.addPoint(Poly3Xp2,Poly3Yp1);
//		polyring3.addPoint(Poly3Xp2,Poly3Yp3);
//		polyring3.addPoint(Poly3Xp1,Poly3Yp3);
//		poly3.addRing(&polyring3);
//		poFeature3->SetGeometryDirectly(&poly3);
//		if (poLayer->CreateFeature(poFeature3)!=OGRERR_NONE)
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("在矢量数据中创建要素(feature)失败！！"));
//			exit(1);
//		}
//
//		OGRFeature *poFeature4=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature4);  //与layer相关联
//		poFeature4->SetField("Color",4);
//		poFeature4->SetField( "PolyLabel",FivethName);
//		OGRPolygon poly4;
//		OGRLinearRing polyring4;
//		polyring4.addPoint(Poly4Xp1,Poly4Yp1);
//		polyring4.addPoint(Poly4Xp2,Poly4Yp1);
//		polyring4.addPoint(Poly4Xp2,Poly4Yp3);
//		polyring4.addPoint(Poly4Xp1,Poly4Yp3);
//		poly4.addRing(&polyring4);
//		poFeature4->SetGeometryDirectly(&poly4);
//		if (poLayer->CreateFeature(poFeature4)!=OGRERR_NONE)
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("在矢量数据中创建要素(feature)失败！！"));
//			exit(1);
//		}
//
//	}
//	if(ClassNum==6)
//	{
//		OGRFieldDefn oField( "Color", OFTInteger );    //创建属性字段，其位置与边框有关
//		oField.SetWidth(32);      //创建字段宽度
//		OGRFieldDefn oField_1( "PolyLabel", OFTString );    //创建属性字段，其位置与边框有关
//		oField_1.SetWidth(32);
//		if( (poLayer->CreateField( &oField ) != OGRERR_NONE )||(poLayer->CreateField( &oField_1 ) != OGRERR_NONE))
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("创建属性字段失败！！"));
//			exit(1);
//		}
//		OGRFeature *poFeature;          //创建feature并写入磁盘
//		poFeature = OGRFeature::CreateFeature( poLayer->GetLayerDefn() );    //和层对应的属性绑定
//		//和层对应的属性进行绑定，以得到feature的单独的field
//		poFeature->SetField("Color",0);
//		poFeature->SetField( "PolyLabel",FirstName);
//		OGRPolygon poly;
//		OGRLinearRing ring;
//		ring.addPoint(Xp1,Yp1);
//		ring.addPoint(Xp2,Yp1);
//		ring.addPoint(Xp2,Yp3);
//		ring.addPoint(Xp1,Yp3);
//		poly.addRing(&ring);
//		poFeature->SetGeometryDirectly(&poly);
//		if (poLayer->CreateFeature(poFeature)!=OGRERR_NONE)
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("在矢量数据中创建要素(feature)失败！！"));
//			exit(1);
//		} 
//
//		OGRFeature *poFeature1=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature1);  //与layer相关联
//
//		poFeature1->SetField("Color",1);
//		poFeature1->SetField( "PolyLabel",SecendName);
//
//		OGRPolygon poly1;
//		OGRLinearRing polyring;
//		polyring.addPoint(Poly1Xp1,Poly1Yp1);
//		polyring.addPoint(Poly1Xp2,Poly1Yp1);
//		polyring.addPoint(Poly1Xp2,Poly1Yp3);
//		polyring.addPoint(Poly1Xp1,Poly1Yp3);
//		poly1.addRing(&polyring);
//		poFeature1->SetGeometryDirectly(&poly1);
//		if (poLayer->CreateFeature(poFeature1)!=OGRERR_NONE)
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("在矢量数据中创建要素(feature)失败！！"));
//			exit(1);
//		}
//
//		OGRFeature *poFeature2=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature2);  //与layer相关联
//
//		poFeature2->SetField("Color",2);
//		poFeature2->SetField( "PolyLabel",ThirdName);
//		OGRPolygon poly2;
//		OGRLinearRing polyring2;
//		polyring2.addPoint(Poly2Xp1,Poly2Yp1);
//		polyring2.addPoint(Poly2Xp2,Poly2Yp1);
//		polyring2.addPoint(Poly2Xp2,Poly2Yp3);
//		polyring2.addPoint(Poly2Xp1,Poly2Yp3);
//		poly2.addRing(&polyring2);
//		poFeature2->SetGeometryDirectly(&poly2);
//		if (poLayer->CreateFeature(poFeature2)!=OGRERR_NONE)
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("在矢量数据中创建要素(feature)失败！！"));
//			exit(1);
//		}
//
//		OGRFeature *poFeature3=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature3);  //与layer相关联
//		poFeature3->SetField("Color",3);
//		poFeature3->SetField( "PolyLabel",FourthName);
//		OGRPolygon poly3;
//		OGRLinearRing polyring3;
//		polyring3.addPoint(Poly3Xp1,Poly3Yp1);
//		polyring3.addPoint(Poly3Xp2,Poly3Yp1);
//		polyring3.addPoint(Poly3Xp2,Poly3Yp3);
//		polyring3.addPoint(Poly3Xp1,Poly3Yp3);
//		poly3.addRing(&polyring3);
//		poFeature3->SetGeometryDirectly(&poly3);
//		if (poLayer->CreateFeature(poFeature3)!=OGRERR_NONE)
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("在矢量数据中创建要素(feature)失败！！"));
//			exit(1);
//		}
//
//		OGRFeature *poFeature4=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature4);  //与layer相关联
//		poFeature4->SetField("Color",4);
//		poFeature4->SetField( "PolyLabel",FivethName);
//		OGRPolygon poly4;
//		OGRLinearRing polyring4;
//		polyring4.addPoint(Poly4Xp1,Poly4Yp1);
//		polyring4.addPoint(Poly4Xp2,Poly4Yp1);
//		polyring4.addPoint(Poly4Xp2,Poly4Yp3);
//		polyring4.addPoint(Poly4Xp1,Poly4Yp3);
//		poly4.addRing(&polyring4);
//		poFeature4->SetGeometryDirectly(&poly4);
//		if (poLayer->CreateFeature(poFeature4)!=OGRERR_NONE)
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("在矢量数据中创建要素(feature)失败！！"));
//			exit(1);
//		}
//
//		OGRFeature *poFeature5=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature5);  //与layer相关联
//		poFeature5->SetField("Color",5);
//		poFeature5->SetField( "PolyLabel",SixthName);
//		OGRPolygon poly5;
//		OGRLinearRing polyring5;
//		polyring5.addPoint(Poly5Xp1,Poly5Yp1);
//		polyring5.addPoint(Poly5Xp2,Poly5Yp1);
//		polyring5.addPoint(Poly5Xp2,Poly5Yp3);
//		polyring5.addPoint(Poly5Xp1,Poly5Yp3);
//		poly5.addRing(&polyring5);
//		poFeature5->SetGeometryDirectly(&poly5);
//		if (poLayer->CreateFeature(poFeature5)!=OGRERR_NONE)
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("在矢量数据中创建要素(feature)失败！！"));
//			exit(1);
//		}
//	}	
//
//	OGRDataSource::DestroyDataSource( poDS );   
//
//	/*****************************************************************************************************************
//	显示生成的图例
//	*****************************************************************************************************************/
//
//	QgsMapCanvas *m_pMapCanvas= mIface->mapCanvas();
//	QList<QgsMapCanvasLayer> m_myLayerSet;
//	QgsMapLayerRegistry *m_pMapLayer;
//	m_pMapLayer=QgsMapLayerRegistry::instance();
//
//	QgsVectorLayer *pLayerV=new QgsVectorLayer(strLablePath,QString::fromLocal8Bit("MapIllustrationShapeFile.shp"),"ogr");
//
//	if (pLayerV->isValid())
//	{
//		//添加图层到图层集中
//		m_pMapLayer->addMapLayer(pLayerV,true);
//
//		QList<QgsMapLayer*> m_layerSet=m_pMapCanvas->layers();
//		QgsMapLayer* pMapLayer=NULL;
//		pMapLayer = m_layerSet.at(0);		//目前只是将第一个图层放置为淹没水深图
//		bool theResultFlag=false;
//		pMapLayer->loadNamedStyle(strColorPath,theResultFlag);
//
//
//		//矢量数据放前面,顺序为点线面
//		int index=0;
//		/*for (;index<m_myLayerSet.count();index++)
//		{
//		QgsMapLayer::LayerType ltype=m_myLayerSet.at(index).layer()->type();
//		if(ltype!=QgsMapLayer::VectorLayer)
//		break;
//		else
//		{
//		QGis::GeometryType  gtype1=pLayerV->geometryType();
//		QgsVectorLayer *pLayerVec=(QgsVectorLayer *)m_myLayerSet.at(index).layer();
//		if(pLayerVec)
//		{
//		QGis::GeometryType  gtype2=pLayerVec->geometryType();
//		if(gtype1<=gtype2)
//		{
//		break;
//		}
//		}
//		}
//		}*/
//		if(index<m_myLayerSet.count())
//			m_myLayerSet.insert(index,QgsMapCanvasLayer(pLayerV));
//		else
//			m_myLayerSet.append(QgsMapCanvasLayer(pLayerV));
//
//		QgsLabel * mypLabel;  
//		mypLabel=pLayerV->label();                    //得到关联mylayer的label指针  
//
//		//QString str=pLayerV->name();                //得到shape文件的存储路径
//		QgsLabelAttributes * mypLabelAttributes;  
//		mypLabelAttributes = mypLabel->layerAttributes();  
//
//		QgsFieldMap myFields = pLayerV->dataProvider()->fields();  //得到矢量图层的字段列表 
//
//		mypLabel->setLabelField(QgsLabel::Text,1);    //设置成为标签的字段
//
//		mypLabelAttributes->setColor(Qt::black);                    //设置label
//		/*****修改****修改****修改****修改****修改****修改****修改***修改***修改****修改***修改****修改******修改***修改****修改***修改*****修改****修改****修改***修改***修改****修改***修改****修改***/
//		if(PolyrangeX<=PolyrangeY*0.15)
//		{
//			if(PolyrangeY*0.15/PolyrangeX>2.5)
//			{
//				mypLabelAttributes->setOffset(PolyrangeX*3,0,0);      //第一个和第二个参数是坐标位置（东北）
//				mypLabelAttributes->setSize(PolyrangeX*1.1,0);
//			}
//			else
//			{
//				mypLabelAttributes->setOffset(PolyrangeX*3,0,0);      //第一个和第二个参数是坐标位置（东北）
//				mypLabelAttributes->setSize(PolyrangeX*0.95,0);
//			}
//		}
//		else
//		{
//			if(PolyrangeX/(PolyrangeY*0.15)>2.5)
//			{
//				mypLabelAttributes->setOffset(PolyrangeY*0.45,0,0);      //第一个和第二个参数是坐标位置（东北）
//				mypLabelAttributes->setSize(PolyrangeY*0.16,0);
//			} 
//			else
//			{
//				mypLabelAttributes->setOffset(PolyrangeY*0.45,0,0);      //第一个和第二个参数是坐标位置（东北）
//				mypLabelAttributes->setSize(PolyrangeY*0.11,0);
//			}
//		}
//
//		/******************************************************************************************************/
//		//启用标注  
//		pLayerV->enableLabels(true);
//	}
//}


//创建工程
void LSY_QRS::CreateProject()
{
	//QSettings settings;
	//QString lastUsedDir = settings.value( "/UI/lastProjectDir", "." ).toString();
	//QString fullPath = QFileDialog::getOpenFileName( mIface->mainWindow(),
	//	QString::fromLocal8Bit( "请输入实验区影像路径" ),
	//	lastUsedDir,
	//	QString::fromLocal8Bit( "影像" ) + " (*.*)" );
	//if ( fullPath.isNull() )
	//{
	//	return;
	//}

	//QFileInfo myRasterFileInfo( fullPath );
	//QByteArray ba = myRasterFileInfo.absoluteFilePath().toLatin1();
	//const char *c_str2 = ba.data();

	//GDALDataset* poDataset;//GDAL数据集
	//GDALAllRegister();
	//CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");

	//poDataset=(GDALDataset*)GDALOpen(c_str2,GA_ReadOnly);

	//if(poDataset==NULL)
	//{
	//	return;
	//}

	//int nImageSizeX=poDataset->GetRasterXSize();
	//int nImageSizeY=poDataset->GetRasterYSize();
	//int bandCount=poDataset->GetRasterCount();
	//ImgArry = new BYTE[nImageSizeX*nImageSizeY*bandCount];
	//poDataset->RasterIO( GF_Read, 0, 0,nImageSizeX,nImageSizeY, ImgArry ,nImageSizeX,nImageSizeY, GDT_Byte,bandCount, NULL,0,0,0 );
	//mIface->addRasterLayer( myRasterFileInfo.absoluteFilePath(), myRasterFileInfo.completeBaseName());//把影像显示到地图视图中
	//return;

	ocCreateProject(&m_pPrj);
	QString fullPath = m_pPrj->m_pOrgImgName;
	fullPath.toLocal8Bit();
	QFileInfo myRasterFileInfo( fullPath );
	QByteArray ba = myRasterFileInfo.absoluteFilePath().toLatin1();
	//const char *c_str2 = ba.data();
	mIface->addRasterLayer( myRasterFileInfo.absoluteFilePath(), myRasterFileInfo.completeBaseName());//把影像显示到地图视图中

}

//打开工程
void LSY_QRS::OpenProject()
{
	if(NULL != m_pPrj) 
	{
//		OnProjectClose();
	}
	ocOpenProject(&m_pPrj);
}

//保存工程
void LSY_QRS::SaveProject()
{
}

//另存为工程
void LSY_QRS::SaveProjectAs()
{
}

//关闭工程
void LSY_QRS::CloseProject()
{
	if(m_pPrj) 
		ocCloseProject(m_pPrj);
}

void LSY_QRS::LayView()
{
	/*QAboutDlg dlg;
	dlg.setModal(true);
	dlg.exec();*/
}

void LSY_QRS::ObjMeanView()
{
	/*QAboutDlg dlg;
	dlg.setModal(true);
	dlg.exec();*/
}
void LSY_QRS::FeatureView()
{
	/*QAboutDlg dlg;
	dlg.setModal(true);
	dlg.exec();*/
}
void LSY_QRS::ClassResultView()
{
	/*QAboutDlg dlg;
	dlg.setModal(true);
	dlg.exec();*/
}
void LSY_QRS::ObjBorderView()
{
	/*QAboutDlg dlg;
	dlg.setModal(true);
	dlg.exec();*/
}


void LSY_QRS::MultiSegment()
{
	//QLibrary mylib("E:\\c++\\LSY_QRS\\LSY_QRS\\TestDll.dll");   //声明所用到的dll文件
	//if (mylib.load())              //判断是否正确加载
	//{
	//	typedef BOOL(*Fun)(char*);
	//	Fun open=(Fun)mylib.resolve("MultiScaleSegment");
	//	if (open)                  //是否成功连接上 add() 函数
	//	{
	//		open("E:\\c++\\TestDllApp\\debug\\1.tif");      //这里函数指针调用dll中的 add() 函数
	//	}
	//	else
	//	{
	//		QMessageBox::information(NULL,"NO","Linke to Function is failed!!!!");
	//	}

	//}
	//else
	//	QMessageBox::information(NULL,"NO","DLL is not loaded!");
	ocMultiScaleSegment(m_pPrj);
	/*QString fullPath =QString::fromWCharArray((LPCTSTR)m_pPrj->m_PrjThemeUrl,m_pPrj->m_PrjThemeUrl.GetLength());*/
	char* fullPath =(LPSTR)(LPCTSTR)m_pPrj->m_PrjThemeUrl;
	QFileInfo myRasterFileInfo( fullPath );
	//QByteArray ba = myRasterFileInfo.absoluteFilePath().toLatin1();
	//const char *c_str2 = ba.data();
	mIface->addVectorLayer( myRasterFileInfo.absoluteFilePath(), myRasterFileInfo.completeBaseName(),"ogr");//把影像显示到地图视图中


}
void LSY_QRS::SelectObjLay()
{
	/*QAboutDlg dlg;
	dlg.setModal(true);
	dlg.exec();*/
}
void LSY_QRS::DelectObjLay()
{
	/*QAboutDlg dlg;
	dlg.setModal(true);
	dlg.exec();*/
}
void LSY_QRS::ClassSegment()
{
	/*QAboutDlg dlg;
	dlg.setModal(true);
	dlg.exec();*/
}


void LSY_QRS::Classification()
{
	/*QAboutDlg dlg;
	dlg.setModal(true);
	dlg.exec();*/
}
void LSY_QRS::DeleteClassification()
{
	/*QAboutDlg dlg;
	dlg.setModal(true);
	dlg.exec();*/
}
void LSY_QRS::EditClassification()
{
	/*QAboutDlg dlg;
	dlg.setModal(true);
	dlg.exec();*/
}

void LSY_QRS::EditClassifie()//编辑类
{
	/*QMessageBox::about(0,QString::fromLocal8Bit("提示…"),
		QString::fromLocal8Bit("新增\n")); */
	QTreeWidget* moduleTree=new QTreeWidget;
	emit ContextMenuShow(moduleTree);
}
void LSY_QRS::InsertClassifie(QTreeWidget* moduleTree)//插入类
{
	QMessageBox::about(0,QString::fromLocal8Bit("提示…"),
		QString::fromLocal8Bit("新增\n")); 
}
void LSY_QRS::CopyClassifie()//复制类
{

}
void LSY_QRS::DeletClassifie()//删除类
{
}
void LSY_QRS::OutputClassifieRule()//导出类规则
{
}
void LSY_QRS::InputClassifieRule()//导入类规则
{
}

void LSY_QRS::SelectXingZheng(QTreeWidgetItem *item, int column)
{
	/*QMessageBox::about(0,QString::fromLocal8Bit("提示…"),
		QString::fromLocal8Bit("新增\n")); */
	QLibrary mylib("E:\\c++\\LSY_QRS\\LSY_QRS\\TestDll.dll");   //声明所用到的dll文件
//	QLibrary mylib("CImgSegDlg.dll");   //声明所用到的dll文件
	if (mylib.load())              //判断是否正确加载
	{
		QMessageBox::information(NULL,"OK","DLL load is OK!!!!!!!");

//		typedef void(*Fun)(); //定义函数指针，以备调用
		typedef BOOL(*Fun)(char*);

//		Fun open=(Fun)mylib.resolve("Show");    //援引 Show() 函数
		Fun open=(Fun)mylib.resolve("MultiScaleSegment");

		if (open)                  //是否成功连接上 add() 函数
		{
			QMessageBox::information(NULL,"OK","Link to Function is OK!");
			open("E:\\c++\\TestDllApp\\debug\\1.tif");      //这里函数指针调用dll中的 add() 函数				
		}
		else
		{
			 QMessageBox::information(NULL,"NO","Linke to Function is not OK!!!!");
		}

	}
	else
		QMessageBox::information(NULL,"NO","DLL is not loaded!");

	//typedef void (*Fun)(); //定义函数指针，以备调用
	//QLibrary mylib("CImgSegDlg.dll");   //声明所用到的dll文件
	//int result;
	//if (mylib.load())              //判断是否正确加载
	//{
	//	QMessageBox::information(NULL,"OK","DLL load is OK!");
	//	Fun open=(Fun)mylib.resolve("SetXmlPrjDlg");    //援引 add() 函数
	//	if (open)                  //是否成功连接上 add() 函数
	//	{
	//		QMessageBox::information(NULL,"OK","Link to Function is OK!");
	//		open();      //这里函数指针调用dll中的 add() 函数
	//	}
	//	else
	//		QMessageBox::information(NULL,"NO","Linke to Function is not OK!!!!");
	//}
	//else
	//	QMessageBox::information(NULL,"NO","DLL is not loaded!");
//	MultiScaleSegment("E:\\c++\\TestDllApp\\debug\\1.tif");

//	return 0;  //加载失败则退出
}
void LSY_QRS::SelectXingZheng1(QTreeWidgetItem *item, int column)
{
	QMessageBox::about(0,QString::fromLocal8Bit("提示…"),
		QString::fromLocal8Bit("新增\n")); 
}
void LSY_QRS::SelectXingZheng2(QTreeWidgetItem *item, int column)
{
	/*QAboutDlg dlg;
	dlg.setModal(true);
	dlg.exec();*/
}
void LSY_QRS::ShowContextMenu(QTreeWidget* moduleTree)
{
	mAction13=new QAction(QString::fromLocal8Bit("编辑类"), this);//编辑类
	mAction14=new QAction(QString::fromLocal8Bit("插入类"), this);//插入类
	mAction15=new QAction(QString::fromLocal8Bit("复制类"), this);//复制类
	mAction16=new QAction(QString::fromLocal8Bit("删除类"), this);//删除类
	mAction17=new QAction(QString::fromLocal8Bit("导出类规则"), this);//导出类规则
	mAction18=new QAction(QString::fromLocal8Bit("导入类规则"), this);//导入类规则
	moduleTree->addAction(mAction13);
	moduleTree->addAction(mAction14);
	moduleTree->addAction(mAction15);
	moduleTree->addAction(mAction16);
	moduleTree->addAction(mAction17);
	moduleTree->addAction(mAction18);
	moduleTree->setContextMenuPolicy(Qt::ActionsContextMenu);

	connect(mAction13,SIGNAL(activated()),this,SLOT(EditClassifie()));
	connect(this,SIGNAL(ContextMenuShow(QTreeWidget* )),this,SLOT(InsertClassifie(QTreeWidget* )));

	//connect(mAction14,SIGNAL(activated()),this,SLOT(ShowContextMenu(QWidget* moduleTree,QAction* Action,QString name)));
	//connect(mAction15,SIGNAL(activated()),this,SLOT(ShowContextMenu(QWidget* moduleTree,QAction* Action,QString name)));
	//connect(mAction16,SIGNAL(SIGNAL(activated()),this,SLOT(ShowContextMenu(QWidget* moduleTree,QAction* Action,QString name)));
	//connect(mAction17,SIGNAL(SIGNAL(activated()),this,SLOT(ShowContextMenu(QWidget* moduleTree,QAction* Action,QString name)));
	//connect(mAction18,SIGNAL(SIGNAL(activated()),this,SLOT(ShowContextMenu(QWidget* moduleTree,QAction* Action,QString name)));
}
void LSY_QRS::ShowContextMenu(QWidget* moduleTree,QAction* Action,QString name)
{
	Action=new QAction(name, this);//编辑类
	moduleTree->addAction(mAction18);
	moduleTree->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void LSY_QRS::InitalProgressBar(/*(void *)mProgressBar,(void *)m_statusBar,char**/)//初始化进度条
{

}
void LSY_QRS::ReleaseProgBar()//析构
{

}
QGISEXTERN QgisPlugin* classFactory(QgisInterface* iface)
{
	return new LSY_QRS(iface);
}
QGISEXTERN QString name()
{
#ifdef WIN_XP
	return QString::fromLocal8Bit("高分辨率遥感影像滑坡检测系统-XP");
#else
	return QString::fromLocal8Bit("高分辨率遥感影像滑坡检测系统");
#endif
}
QGISEXTERN QString description()
{
#ifdef WIN_XP
	return QString::fromLocal8Bit("基于高分辨率遥感影像的滑坡地质灾害信息识别与提取检测系统-XP");
#else
	return QString::fromLocal8Bit("基于高分辨率遥感影像的滑坡地质灾害信息识别与提取检测系统");
#endif
}
QGISEXTERN QString version()
{
	return "1.0.1";
}
QGISEXTERN int type()
{
	return QgisPlugin::UI;
}
QGISEXTERN QString icon()
{
	return QString::fromUtf8("D:\\qgis\\qgis-release-1_8\\vs2005\\output\\bin\\relwithdebinfo\\Resources\\app.png");
}

QGISEXTERN void unload(QgisPlugin* theLSY_QRSPointer)
{
	delete theLSY_QRSPointer;
}
