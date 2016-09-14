#include "lsy_qrs.h"
#include "qgisinterface.h"
#include <qaction.h>
#include <qmessagebox.h>
#include <qgsapplication.h>
#include <qgsmapcanvas.h>
#include <qmainwindow.h>
#include <qmenubar.h>
#include <qnamespace.h>

//#include "ogr_geometry.h "	//�ǲ���OGRPoint��ͷ�ļ���
//#include "ogr_feature.h "	//�ǲ���oFiled��ͷ�ļ���
//#include "ogrsf_frmts.h "	//GEtRegistrar��ͷ�ļ���
#include "qgsvectorlayer.h "	//����ͼ������label�õ���
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
//������ modify 2014.03.09
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


//����ĳ�ʼ����ز���
void LSY_QRS::initGui()
{
	mpMainWindow=(QMainWindow *)mIface->mainWindow();
	mpMainWindow->setWindowTitle(QString::fromLocal8Bit("�߷ֱ���ң�л����ֺ�ʶ��ϵͳ-LSY_QRS"));
	
	//�˵�����
	mIface->editMenu()->setTitle(QString::fromLocal8Bit("�༭"));
	mIface->rasterMenu()->setTitle(QString::fromLocal8Bit("դ��"));
	mIface->vectorMenu()->setTitle(QString::fromLocal8Bit("ʸ��"));
	mIface->databaseMenu()->setTitle(QString::fromLocal8Bit("���ݿ�"));

	QIcon iconMain;
	iconMain.addFile(QString::fromUtf8("D:\\qgis\\qgis-release-1_8\\vs2005\\output\\bin\\relwithdebinfo\\Resources\\app.png"), QSize(), QIcon::Normal, QIcon::Off);
	mpMainWindow->setWindowIcon(iconMain);

	//�����µĲ˵�
	QMenuBar *menubar=mpMainWindow->menuBar();
	if(menubar)
	{
		mMenuImgSegObj = new QMenu(menubar);
		mMenuImgSegObj->setObjectName(QString::fromUtf8("mMenuImgSegObj"));
		mMenuImgSegObj->setTitle(QString::fromLocal8Bit("Ӱ�����"));

		mMenuImgShow = new QMenu(menubar);
		mMenuImgShow->setObjectName(QString::fromUtf8("mMenuImgShow"));
		mMenuImgShow->setTitle(QString::fromLocal8Bit("��ʾ"));

		
		mMenuImgClass = new QMenu(menubar);
		mMenuImgClass->setObjectName(QString::fromUtf8("mMenuImgClass"));
		mMenuImgClass->setTitle(QString::fromLocal8Bit("����"));

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

	//�����˵��¼�
	CreateAction(mAction1,QString::fromLocal8Bit("Ӱ��ͼ��"),mMenuImgShow,QString::fromLocal8Bit("��ʾ"),
		mToolBarImgShow,QString::fromLocal8Bit("��ʾ"),QString::fromUtf8(":/new/prefix1/Resources/mActionAnalysis1.png"),SLOT(LayView()));

	CreateAction(mAction1,QString::fromLocal8Bit("Ӱ��ͼ��"),mMenuImgShow,QString::fromLocal8Bit("��ʾ"),
		mToolBarImgShow,QString::fromLocal8Bit("��ʾ"),QString::fromUtf8(":/new/prefix1/Resources/mActionAnalysis1.png"),SLOT(LayView()));

	CreateAction(mAction2,QString::fromLocal8Bit("�����ֵ"),mMenuImgShow,QString::fromLocal8Bit("��ʾ"),
		mToolBarImgShow,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit(":/new/prefix1/Resources/mActionAnalysis1.png"),SLOT(ObjMeanView()));

	CreateAction(mAction3,QString::fromLocal8Bit("������ʾ"),mMenuImgShow,QString::fromLocal8Bit("��ʾ"),
		mToolBarImgShow,QString::fromLocal8Bit("��ʾ"),QString::fromUtf8(":/new/prefix1/Resources/mActionAnalysis1.png"),SLOT(FeatureView()));

	CreateAction(mAction4,QString::fromLocal8Bit("��������ʾ"),mMenuImgShow,QString::fromLocal8Bit("��ʾ"),
		mToolBarImgShow,QString::fromLocal8Bit("��ʾ"),QString::fromUtf8(":/new/prefix1/Resources/mActionAnalysis1.png"),SLOT(ClassResultView()));

	CreateAction(mAction10,QString::fromLocal8Bit("����߽���ʾ"),mMenuImgShow,QString::fromLocal8Bit("��ʾ"),
		mToolBarImgShow,QString::fromLocal8Bit("��ʾ"),QString::fromUtf8(":/new/prefix1/Resources/mActionAnalysis1.png"),SLOT(ObjBorderView()));

	mMenuImgShow->addSeparator();

	CreateAction(mAction0,QString::fromLocal8Bit("��߶ȷָ�"),mMenuImgSegObj,QString::fromLocal8Bit("�ָ�"),
		mToolBarImgSegObj,QString::fromLocal8Bit("�ָ�"),QString::fromUtf8(":/new/prefix1/Resources/mActionAnalysis1.png"),SLOT(MultiSegment()));

	CreateAction(mAction5,QString::fromLocal8Bit("ѡ������"),mMenuImgSegObj,QString::fromLocal8Bit("�ָ�"),
		mToolBarImgSegObj,QString::fromLocal8Bit("�ָ�"),QString::fromUtf8(":/new/prefix1/Resources/mActionAnalysis3.png"),SLOT(SelectObjLay()));

	CreateAction(mAction6,QString::fromLocal8Bit("ɾ�������"),mMenuImgSegObj,QString::fromLocal8Bit("�ָ�"),
		mToolBarImgSegObj,QString::fromLocal8Bit("�ָ�"),QString::fromUtf8(":/new/prefix1/Resources/mActionAnalysis3.png"),SLOT(DelectObjLay()));

	CreateAction(mAction7,QString::fromLocal8Bit("���ڷ���ķָ�"),mMenuImgSegObj,QString::fromLocal8Bit("�ָ�"),
		mToolBarImgSegObj,QString::fromLocal8Bit("�ָ�"),QString::fromUtf8(":/new/prefix1/Resources/mActionAnalysis3.png"),SLOT(ClassSegment()));

	mMenuImgSegObj->addSeparator();

	CreateAction(mAction7,QString::fromLocal8Bit("����"),mMenuImgClass,QString::fromLocal8Bit("Ӱ�����"),
		mToolBarImgClass,QString::fromLocal8Bit("Ӱ�����"),QString::fromUtf8(":/new/prefix1/Resources/mActionAnalysis3.png"),SLOT(Classification()));

	CreateAction(mAction7,QString::fromLocal8Bit("ɾ������"),mMenuImgClass,QString::fromLocal8Bit("Ӱ�����"),
		mToolBarImgClass,QString::fromLocal8Bit("Ӱ�����"),QString::fromUtf8(":/new/prefix1/Resources/mActionAnalysis3.png"),SLOT(DeleteClassification()));

	CreateAction(mAction7,QString::fromLocal8Bit("�����༭"),mMenuImgClass,QString::fromLocal8Bit("Ӱ�����"),
		mToolBarImgClass,QString::fromLocal8Bit("Ӱ�����"),QString::fromUtf8(":/new/prefix1/Resources/mActionAnalysis3.png"),SLOT(EditClassification()));

	//�ڲ˵�������Ӳ˵�
	if(menubar)
	{	
		menubar->insertMenu(mIface->pluginMenu()->menuAction(),mMenuImgShow);
		menubar->insertMenu(mIface->pluginMenu()->menuAction(),mMenuImgSegObj);
		menubar->insertMenu(mIface->pluginMenu()->menuAction(),mMenuImgClass);
	}


//	��ӡ��������ݡ��˵�
	if(menubar)
	{
		mAction12 = new QAction(QString::fromLocal8Bit("�½�����"), this);
		mAction19 = new QAction(QString::fromLocal8Bit("�򿪹���"), this);
		mAction20 = new QAction(QString::fromLocal8Bit("���湤��"), this);
		mAction21 = new QAction(QString::fromLocal8Bit("���Ϊ����"), this);
		mAction22 = new QAction(QString::fromLocal8Bit("�رչ���"), this);
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


	//��ӡ����ڡ��˵�
	if(menubar)
	{
		mAboutDlg = new QAction(QString::fromLocal8Bit("���ڡ��߷ֱ���ң��Ӱ���¼��ϵͳ��"), this);
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

	//���������ͼ
	dockWidget_2 = new QDockWidget(QString::fromLocal8Bit("������ͼ"),mpMainWindow);
	dockWidget_2->setObjectName(QString::fromUtf8("dockWidget_2"));
	dockWidget_2->setMinimumSize(QSize(290, 250));
	dockWidget_2->setFeatures( QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable );//�����ƶ�

	dockWidgetContents_2 = new QWidget();//��������ͼ����Ӷ���
	dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));

	gridLayout = new QGridLayout(dockWidgetContents_2);//���ò���
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

	dockWidget_2->setWidget(dockWidgetContents_2);//����Ŀ¼����������ͼ��
	dockWidget_2->setAllowedAreas( Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
	mpMainWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget_2);//��������ͼ��������ͼ��
//	mpMainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_2);//��������ͼ��������ͼ��

	ShowContextMenu(treeWidget_2);

	if(InitialDockTree2(treeWidget_2)!=0)
	{
		QMessageBox::about(0,QString::fromLocal8Bit("��ʾ��"),
			QString::fromLocal8Bit("��ʼ��������ͼʧ�ܣ�\n")); 
	}
	connect(treeWidget_2,SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int )),this,SLOT(SelectXingZheng(QTreeWidgetItem *, int )));

	//��������б���ͼ
	QWidget *dockWidgetContents_3;
	QGridLayout *gridLayout1;
	dockWidget_3 = new QDockWidget(QString::fromLocal8Bit("�����б���ͼ"),mpMainWindow);
	dockWidget_3->setObjectName(QString::fromUtf8("dockWidget_3"));
	dockWidget_3->setMinimumSize(QSize(290, 250));
	dockWidget_3->setFeatures( QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetFloatable);//�����ƶ�

	dockWidgetContents_3 = new QWidget();//�������б���ͼ����Ӷ���
	dockWidgetContents_3->setObjectName(QString::fromUtf8("dockWidgetContents_3"));

	gridLayout1 = new QGridLayout(dockWidgetContents_3);//���ò���
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

	dockWidget_3->setWidget(dockWidgetContents_3);//����Ŀ¼����������ͼ��
	dockWidget_3->setAllowedAreas( Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
	mpMainWindow->addDockWidget(Qt::RightDockWidgetArea, dockWidget_3);//��������ͼ��������ͼ��
//	mpMainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_3);//�������б���ͼ��������ͼ��

	QString strPath1=QgsApplication::prefixPath();
	if(InitialDockTree3(strPath1+QString::fromLocal8Bit("/data/system.mdb"),treeWidget_3)!=0)
	{
		QMessageBox::about(0,QString::fromLocal8Bit("��ʾ��"),
			QString::fromLocal8Bit("��ʼ�������б���ͼʧ�ܣ�\n")); 
	}

	connect(treeWidget_3,SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int )),this,SLOT(SelectXingZheng1(QTreeWidgetItem *, int )));
	connect(mAction0,SIGNAL(activated()),this,SLOT(MultiSegment()));
	//��Ӷ�����Ϣ��ͼ
	QWidget *dockWidgetContents_4;
	QGridLayout *gridLayout2;
	dockWidget_4 = new QDockWidget(QString::fromLocal8Bit("������Ϣ��ͼ"),mpMainWindow);
	dockWidget_4->setObjectName(QString::fromUtf8("dockWidget_4"));
	dockWidget_4->setMinimumSize(QSize(290, 280));
	dockWidget_4->setFeatures( QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetFloatable);//�����ƶ�

	dockWidgetContents_4 = new QWidget();//��������Ϣ��ͼ����Ӷ���
	dockWidgetContents_4->setObjectName(QString::fromUtf8("dockWidgetContents_4"));

	gridLayout2 = new QGridLayout(dockWidgetContents_4);//���ò���
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
	IMG_model = new QStandardItemModel();//׼������ģ��
	IMG_model->setHorizontalHeaderItem(0, new QStandardItem(QString::fromLocal8Bit("������")));
	IMG_model->setHorizontalHeaderItem(1, new QStandardItem(QString::fromLocal8Bit("����ֵ")));
	tableWidget->setObjectName(QString::fromUtf8("tableWidget_4"));
	tableWidget->setModel(IMG_model);//����setModel()����������ģ����QTableView��
	//tableWidget->horizontalHeader()->setResizeMode(0, QHeaderView::Fixed); //�����п��ɱ䶯��������ͨ������϶������п�  
	//tableWidget->horizontalHeader()->setResizeMode(1, QHeaderView::Fixed); 
	tableWidget->verticalHeader()->hide();//������ͷ
	tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //���ñ��ĵ�ԪΪֻ�����ԣ������ܱ༭
	tableWidget->setColumnWidth(0,180);
	tableWidget->setColumnWidth(1,150);
	tableWidget->setRowHeight(0,3);
	tableWidget->setShowGrid(false);
	tableWidget->verticalHeader()->hide();
	tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	gridLayout2->addWidget(tableWidget, 0, 0, 2, 2);
	//QTableWidgetItem* item =new QTableWidgetItem();
	//item->setText(QString::fromLocal8Bit("����������"));
	//tableWidget->setHorizontalHeaderItem(0,item);
	//QTableWidgetItem* item1 =new QTableWidgetItem();
	//item1->setText(QString::fromLocal8Bit("��������ֵ"));
	//tableWidget->setHorizontalHeaderItem(1,item1);
	dockWidget_4->setWidget(dockWidgetContents_4);//����Ŀ¼���������Ϣ��ͼ��
	dockWidget_4->setAllowedAreas( Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );//����ͣ��
	mpMainWindow->addDockWidget(Qt::RightDockWidgetArea, dockWidget_4);//��������ͼ��������ͼ��

	if(InitialDockTable(IMG_model,tableWidget)!=0)
	{
		QMessageBox::about(0,QString::fromLocal8Bit("��ʾ��"),QString::fromLocal8Bit("��ʼ��������Ϣ��ͼʧ�ܣ�\n")); 
	}

	m_statusBar=mpMainWindow->statusBar();
	if(m_statusBar)
	{
		mProgressBar = new QProgressBar(m_statusBar);
		mProgressBar->setMaximumWidth( 100 );
		mProgressBar->setMinimumSize(200,1);

		m_statusBar->insertPermanentWidget(0, mProgressBar, 1 );
		m_statusBar->setObjectName("statusbar");
		//��ʼ��������
//		InitalProgressBar((void *)mProgressBar,(void *)m_statusBar,"QT");
	}
	////ȥ�����๤����
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
	//�������qgs����
	//��ʱ�����ε�
//	strPath=strPath.replace('/','\\');
//	mIface->addProject(QString::fromLocal8Bit("D:\qgis\data\lsy_qrs.qgs"));
}
//���������ж����ز���
void LSY_QRS::unload()
{
	//�Ƴ����ڶԻ���
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

	//�Ƴ�������
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

	//�����ʾ�˵�
	if(mMenuImgShow)
	{
		mMenuImgShow->clear();
		delete mMenuImgShow;
		mMenuImgShow=0;
	}
	else
	{
		mIface->removeToolBarIcon(mAction1);
		mIface->removePluginMenu(QString::fromLocal8Bit("��ʾ"), mAction1);
		delete mAction1;
		mAction1=NULL;

		mIface->removeToolBarIcon(mAction2);
		mIface->removePluginMenu(QString::fromLocal8Bit("��ʾ"), mAction2);
		delete mAction2;
		mAction2=NULL;

		mIface->removeToolBarIcon(mAction3);
		mIface->removePluginMenu(QString::fromLocal8Bit("��ʾ"), mAction3);
		delete mAction3;
		mAction3=NULL;

		mIface->removeToolBarIcon(mAction4);
		mIface->removePluginMenu(QString::fromLocal8Bit("��ʾ"), mAction4);
		delete mAction4;
		mAction4=NULL;

		mIface->removeToolBarIcon(mAction10);
		mIface->removePluginMenu(QString::fromLocal8Bit("��ʾ"), mAction10);
		delete mAction10;
		mAction10=NULL;
	}
	//����ָ�˵�
	if(mMenuImgSegObj)
	{
		mMenuImgSegObj->clear();
		delete mMenuImgSegObj;
		mMenuImgSegObj=0;
	}
	else
	{
		mIface->removeToolBarIcon(mAction0);
		mIface->removePluginMenu(QString::fromLocal8Bit("�ָ�"), mAction0);
		delete mAction0;
		mAction0=NULL;

		mIface->removeToolBarIcon(mAction5);
		mIface->removePluginMenu(QString::fromLocal8Bit("�ָ�"), mAction5);
		delete mAction5;
		mAction5=NULL;

		mIface->removeToolBarIcon(mAction6);
		mIface->removePluginMenu(QString::fromLocal8Bit("�ָ�"), mAction6);
		delete mAction6;
		mAction6=NULL;

		mIface->removeToolBarIcon(mAction7);
		mIface->removePluginMenu(QString::fromLocal8Bit("�ָ�"), mAction7);
		delete mAction7;
		mAction7=NULL;
	}
	//���Ӱ�����˵�
	if(mMenuImgClass)
	{
		mMenuImgClass->clear();
		delete mMenuImgClass;
		mMenuImgClass=0;
	}
	else
	{
		mIface->removeToolBarIcon(mAction8);
		mIface->removePluginMenu(QString::fromLocal8Bit("�ָ�"), mAction8);
		delete mAction8;
		mAction8=NULL;

		mIface->removeToolBarIcon(mAction9);
		mIface->removePluginMenu(QString::fromLocal8Bit("�ָ�"), mAction9);
		delete mAction9;
		mAction9=NULL;

		mIface->removeToolBarIcon(mAction11);
		mIface->removePluginMenu(QString::fromLocal8Bit("�ָ�"), mAction11);
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
	//����action
	action = new QAction(name, this);
	QIcon icon1;
	icon1.addFile(icon, QSize(), QIcon::Normal, QIcon::Off);
	action->setIcon(icon1);

	//��ӵ��˵�
	if(mMenu) 
	{
		mMenu->addAction(action);
	}
	else
	{
		mIface->addPluginToMenu(name1,action);//����˵������ڣ����ܼ��ڲ���˵���
	}

	//��ӵ�������
	if(mToolBar)
	{
		mToolBar->addAction(action);
		mToolBar->setWindowTitle(name2);
	}
	else
	{
		mIface->addToolBarIcon(action);
	}

	connect(action, SIGNAL(activated()), this, receiverMember);//���Ӵ����¼�

	mActionList.push_back(action);
}

void LSY_QRS::ThisAboutDlg()
{
	/*QAboutDlg dlg;
	dlg.setModal(true);
	dlg.exec();*/
}


//��ȡϵͳդ��ͼ���ļ�·��
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
//��ʼ����Ŀ¼
long LSY_QRS::InitialDockTree2(QTreeWidget *treeWidget)
{
	QColor R(255,0,0);
	QColor	NULLColor(0,0,0,0);//��ʼ��NULLColor

	XingZhTreeNode node(0,-1,QString::fromLocal8Bit("��ӷ���"),R);
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
	QColor	NULLColor(0,0,0,0);//��ʼ��NULLColor

	XingZhTreeNode node(0,-1,QString::fromLocal8Bit("��������"),NULLColor);
	m_treeInfo1.append(node);
	XingZhTreeNode node1(1,0,QString::fromLocal8Bit("ͼ��"),NULLColor);
	m_treeInfo1.append(node1);
	XingZhTreeNode node2(2,0,QString::fromLocal8Bit("��״"),NULLColor);
	m_treeInfo1.append(node2);
	XingZhTreeNode node3(3,0,QString::fromLocal8Bit("����"),NULLColor);
	m_treeInfo1.append(node3);
	XingZhTreeNode node4(4,-1,QString::fromLocal8Bit("���������"),NULLColor);
	m_treeInfo1.append(node4);
	XingZhTreeNode node5(5,4,QString::fromLocal8Bit("���ڶ���"),NULLColor);
	m_treeInfo1.append(node5);
	XingZhTreeNode node6(6,4,QString::fromLocal8Bit("���Ӷ���"),NULLColor);
	m_treeInfo1.append(node6);
	for (int iItem=0;iItem<m_treeInfo1.count();iItem++)
	{	
		AddTreeItems(treeWidget,&m_treeInfo1,NULL,&m_treeInfo1[iItem]);
	}
	return 0;
}
long LSY_QRS::InitialDockTable(QStandardItemModel* model,QTableView* tableView)
{
	/*QTableWidgetItem* item=new QTableWidgetItem(QString::fromLocal8Bit("����ţ�"));
	item->setSizeHint(QSize(200,0));
	tableWidget->setItem(0,0,item);*/
	model->setItem(0, 0, new QStandardItem(QString::fromLocal8Bit("����ţ�")));
	model->item(0, 0)->setTextAlignment(Qt::AlignLeft);//���õ�Ԫ���ı�����
	model->item(0, 0)->setFont(QFont("����", 10, QFont::Black )); //������Ӵ�
	return 0;
}

//��ȡ�ⲿ�ļ���ʼ����Ŀ¼
long LSY_QRS::ReadXingZhInfo(QString strIniFile,XingZhTreeInfo	*pTreeInfo)
{
	return 0;
}
//��ӿؼ�����
long LSY_QRS::AddTreeItems(QTreeWidget *pTreeWidget,XingZhTreeInfo *pTreeInfo,QTreeWidgetItem *pParentItem,const XingZhTreeNode *pParentNode)
{
	if(pTreeInfo==NULL || pTreeWidget==NULL || pParentNode==NULL)
		return -1;
	QTreeWidgetItem  *item=NULL;//new QTreeWidgetItem(treeWidget,QStringList(LayerPath));
	QColor	NULLColor(0,0,0,0);//��ʼ��NULLColor

	if(pParentItem==NULL && pParentNode->m_nParentID==-1)//û�и�����,����¸�����
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
	else if(pParentItem /* && pParentNode->m_nParentID >= 0*/)//�и������ڸ�����������Ӷ���
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
	model->item(rowCount+1, 0)->setTextAlignment(Qt::AlignLeft);//���õ�Ԫ���ı�����
	model->item(rowCount+1, 1)->setTextAlignment(Qt::AlignLeft);//���õ�Ԫ���ı�����
	return 0;
}

//void LSY_QRS::MapFrame(char* FilePath,char* MapName)
//{
//	QString		strFilePath = "",strFramePath = "";
//	char		szFramePath[512] = {0};
//	QTime		cunTime;
//	//QDateTime   cunTime;
//	OGRRegisterAll();      //ע���ʽ
//	const char *pszDriverName = "ESRI Shapefile";
//	OGRSFDriver *poDriver;
//	poDriver = OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName(pszDriverName);//��ȡ��������
//	if(poDriver == NULL)
//	{
//		QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("����ע��ʧ�ܣ���"));
//	}
//	GDALDataset *poDataset;                        //������Ҫ��������ר��ͼ��ȡ��Ϣ
//	GDALAllRegister();
//	/////////////////////////////////////////////////////////////////////////////////////////////�����ô���ʸ����ȷ���
//	//QFileDialog dlg(this,QString::fromLocal8Bit("ѡ���ļ�"));
//	//dlg.setAcceptMode(QFileDialog::AcceptOpen);
//	//QString LayerPath=dlg.getOpenFileName();
//	//QByteArray path= LayerPath.toLatin1();         //QStringתchar*
//	//const char *FilePath = path.data();
//	////////////////////////////////////////////////////////////////////////////////////////////////
//	poDataset = (GDALDataset*) GDALOpen(FilePath,GA_ReadOnly);
//	if(poDataset==NULL)
//		QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("��ȡ����ʧ�ܣ���"));
//	int ImgXSize=poDataset->GetRasterXSize();
//	int ImgYSize=poDataset->GetRasterYSize();
//	double Trans[6];                   //����ת����������,��ΪGetGeoTransform()�����Ĳ���
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
//	OGRDataSource *poDS;       //����ʸ�������ļ�
//	//poDS = poDriver->CreateDataSource("FrameShapeFile.shp",NULL );    //�����ڵ�ǰĿ¼�µ�ShapeFile�ļ�    ��Ҫ�ı�һ��
//	poDS = poDriver->CreateDataSource(szFramePath,NULL);
//	if(poDS == NULL)
//	{
//		QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("�����ļ�ʧ�ܣ���"));
//	}
//
//	OGRLayer *poLayer;
//	const char *prj=poDataset->GetProjectionRef();             //��ȡդ��Ӱ��Ŀռ�ο���Ϣ
//	OGRSpatialReference oSRS;  
//	oSRS.SetFromUserInput(prj);                                //����õĿռ�ο���Ϣ�ַ�����Ϊ�ı�һ���Ը���ʸ�����ݵ�OGRSpatialReference����
//	poLayer = poDS->CreateLayer(FilePath,&oSRS);               //����ͼ�㣨��һ�㣩
//	if( poLayer == NULL )
//	{
//		QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("����ͼ��ʧ�ܣ���"));
//	}
//
//	OGRFieldDefn oField( "Line", OFTString );    //���������ֶ�point����������㣨X,Y���й�
//	oField.SetWidth(126);                         //�����ֶο��
//	if( poLayer->CreateField( &oField ) != OGRERR_NONE )
//	{
//		QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("���������ֶ�ʧ�ܣ���"));
//	}
//	OGRFeature *poFeature;          //����feature��д�����
//	poFeature = OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//	poFeature->SetField("Line",MapName);
//	//������߿�
//	//Trans[0]�����Ͻ���Ԫ�Ķ����ꣻa1
//	//Trans[3]�����Ͻ���Ԫ�ı����ꣻa2
//	//Trans[1]��Ӱ�����ϵķֱ��ʣ�b1
//	//Trans[5]��Ӱ��߶��ϵķֱ��ʣ�c2
//	//Trans[2]����ת, 0��ʾ����Ϊ������ c1
//	//Trans[4]����ת, 0��ʾ����Ϊ������ b2
//	//��Ӧ�ķ���任��ʽ��
//	//Xpixel��YlineLͼ������   Xp Yp ��������
//	//1��ͼ������ת��������
//	//Xp = geoTransform [0] + Xpixel*geoTransform [1] + Yline*geoTransform [2];
//	//Yp = geoTransform [3] + Xpixel*geoTransform [4] + Yline*geoTransform [5];
//	OGRLineString Line;
//	/***********************�޸�***�޸�****�޸�***�޸�*****�޸�****�޸�****�޸�***�޸�***�޸�****�޸�***�޸�****�޸�*****************************/
//	OGRPoint Point1(Trans[0]-(ImgXSize*Trans[1]+ImgYSize*Trans[2])/3.4,Trans[3]-(ImgXSize*Trans[4]+ImgYSize*Trans[5])/8);        //�Զ�����¼λ��(�ĸ��ǵ�)    ����Ϊ�˽���߿�����һЩ������.1��λ��������Ӧ�ĵ���ϻ����Ǽ�ȥ.1.
//	OGRPoint Point2(Trans[0]+ImgXSize*Trans[1]+ImgYSize*Trans[2]+(ImgXSize*Trans[1]+ImgYSize*Trans[2])/3.8,Trans[3]-(ImgXSize*Trans[4]+ImgYSize*Trans[5])/8);
//	OGRPoint Point3(Trans[0]+ImgXSize*Trans[1]+ImgYSize*Trans[2]+(ImgXSize*Trans[1]+ImgYSize*Trans[2])/3.82,Trans[3]+ImgXSize*Trans[4]+ImgYSize*Trans[5]+(ImgXSize*Trans[4]+ImgYSize*Trans[5])/3);
//	OGRPoint Point4(Trans[0]-(ImgXSize*Trans[1]+ImgYSize*Trans[2])/3.4,Trans[3]+ImgXSize*Trans[4]+ImgYSize*Trans[5]+(ImgXSize*Trans[4]+ImgYSize*Trans[5])/3);
//	Line.addPoint(&Point4);              //1        2
//	Line.addPoint(&Point1);              //4        3
//	Line.addPoint(&Point2);
//	Line.addPoint(&Point3);  
//	Line.addPoint(&Point4);              //�����ߵĶ��㲢������λ��	/*********************************************************************************************************************************************/	
//	poFeature->SetGeometryDirectly(&Line);
//	if (poLayer->CreateFeature(poFeature)!=OGRERR_NONE)
//	{
//		QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("��ʸ�������д���Ҫ��ʧ�ܣ���"));
//		exit(1);
//	}
//	OGRDataSource::DestroyDataSource( poDS );
//	//QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("����ͼ��ɹ�����"));
//
//	/*****************************************************************************************************************
//	��ʾ���ɵ�ͼ��
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
//		//���ͼ�㵽ͼ�㼯��
//		m_pMapLayer->addMapLayer(pLayerV,true);
//
//		//ʸ�����ݷ�ǰ��,˳��Ϊ������
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
//		mypLabel=pLayerV->label();                    //�õ�����mylayer��labelָ��  
//		QgsLabelAttributes * mypLabelAttributes;  
//		mypLabelAttributes = mypLabel->layerAttributes();  
//
//		QgsFieldMap myFields = pLayerV->dataProvider()->fields();  //�õ�ʸ��ͼ����ֶ��б� 
//
//		mypLabel->setLabelField(QgsLabel::Text,myFields.size()-1); 
//
//		mypLabelAttributes->setColor(Qt::black);                    //����label
//		//mypLabelAttributes->setOffset(11,0,1);      //��һ���͵ڶ�������������λ�ã�������
//		//mypLabelAttributes->setSize(7,1);
//
//
//		/***********************�޸�***�޸�****�޸�***�޸�*****�޸�****�޸�****�޸�***�޸�***�޸�****�޸�***�޸�****�޸�*****************************/
//		mypLabelAttributes->setBold(true);
//
//		mypLabelAttributes->setAlignment(6);//������ʾλ�����ߵ����Ϸ�	
//
//		double PolyrangeX=(Point2.getX()-Point1.getX())/30;    //����ÿ������30����
//		double PolyrangeY=-(Point3.getY()-Point2.getY())/5;
//
//		mypLabelAttributes->setOffset(-(ImgXSize*Trans[1]+ImgYSize*Trans[2]+(ImgXSize*Trans[1]+ImgYSize*Trans[2])/8.4)/1.55,0,0);    //�Ա߿�ĵ�һ�ֶμӱ���
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
//		//���ñ�ע  
//		pLayerV->enableLabels(true);
//		//��ͼ����ӵ�ͼ���б���
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
//	QString	 strColorPath=QgsApplication::prefixPath();		//ɫ���ļ���
//	strColorPath +="\\data\\shpcolor.map.qml";
//	OGRRegisterAll();      //ע���ʽ
//	const char *pszDriverName = "ESRI Shapefile";
//	OGRSFDriver *poDriver;
//	poDriver = OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName(pszDriverName);//��ȡ��������
//	if(poDriver == NULL)
//	{
//		QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("����ע��ʧ�ܣ���"));
//		exit(1);
//	}
//	GDALDataset *poDataset;                        //������Ҫ��������ר��ͼ��ȡ��Ϣ
//	GDALAllRegister();
//	/////////////////////////////////////////////////////////////////////////////////////////////�����ô���ʸ����ȷ���
//	//QFileDialog dlg(this,QString::fromLocal8Bit("ѡ���ļ�"));
//	//dlg.setAcceptMode(QFileDialog::AcceptOpen);
//	//QString LayerPath=dlg.getOpenFileName();
//	//QByteArray path= LayerPath.toLatin1();         //QStringתchar*
//	//const char *FilePath = path.data();
//	////////////////////////////////////////////////////////////////////////////////////////////////
//	poDataset = (GDALDataset*) GDALOpen(FilePath,GA_ReadOnly);
//	if(poDataset==NULL)
//		QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("��ȡ����ʧ�ܣ���"));
//	int ImgXSize=poDataset->GetRasterXSize();
//	int ImgYSize=poDataset->GetRasterYSize();
//	double Trans[6];                   //����ת����������,��ΪGetGeoTransform()�����Ĳ���
//	poDataset->GetGeoTransform(Trans);
//	OGRDataSource *poDS;       //����ʸ�������ļ�
//	strcpy(szLablePath,(const char*)strLablePath.toLocal8Bit());
//	poDS = poDriver->CreateDataSource(szLablePath,NULL );    //�����ڵ�ǰĿ¼�µ�ShapeFile�ļ�
//	if(poDS == NULL)
//	{
//		QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("�����ļ�ʧ�ܣ���"));
//		exit(1);
//	}
//	OGRLayer *poLayer;
//	const char *prj=poDataset->GetProjectionRef();             //��ȡդ��Ӱ��Ŀռ�ο���Ϣ
//	OGRSpatialReference oSRS;  
//	oSRS.SetFromUserInput(prj);                                //����õĿռ�ο���Ϣ�ַ�����Ϊ�ı�һ���Ը���ʸ�����ݵ�OGRSpatialReference����
//	poLayer = poDS->CreateLayer(FilePath,&oSRS,wkbPolygon);               //����ͼ�㣨��һ�㣩
//	if( poLayer == NULL )
//	{
//		QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("����ͼ��ʧ�ܣ���"));
//		exit(1);
//	}
//	//int *pafScanblock;//������ݵ��ڴ�
//	//GDALRasterBand *poBand=poDataset->GetRasterBand(1);
//	//GDALDataType  dType=poBand->GetRasterDataType();
//	////һ����Ԫռ�õ��ֽ���
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
//	//for (int i=0;i<ImgYSize*ImgXSize;i++)  //��ȡӰ��������Сֵ
//	//{
//	//	if ((min>*(pafScanblock+i))&&(*(pafScanblock+i)<=255)&&(*(pafScanblock+i)>=0))
//	//		min=*(pafScanblock+i);
//	//}
//	/**************�޸�***�޸�****�޸�***�޸�*****�޸�****�޸�****�޸�***�޸�***�޸�****�޸�***�޸�****�޸�******�޸�***�޸�****�޸�***�޸�*****�޸�****�޸�****�޸�***�޸�***�޸�****�޸�***�޸�****�޸�****************/
//	//double FirstColor=0;
//	//double SecendColor=0;
//	//double ThirdColor=0;
//	//double FourthColor=0;
//	//double FivethColor=0;
//	//double SixthColor=0;  
//	//switch (ClassNum)
//	//{
//	//case 2:
//	//	Scale=(max-min)/2;   //ͼ��ɫ�ʷֲ�
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
//	//	Scale=(max-min)/6;   //ͼ��ɫ�ʷֲ�
//	//	FirstColor=min+Scale/2;
//	//	SecendColor=FirstColor+Scale;
//	//	ThirdColor=SecendColor+Scale;
//	//	FourthColor=ThirdColor+Scale;
//	//	FivethColor=FourthColor+Scale;
//	//	SixthColor=FivethColor+Scale;  
//	//	break;
//	//}
//	OGRPoint Point1(Trans[0]-(ImgXSize*Trans[1]+ImgYSize*Trans[2])/5,Trans[3]-(ImgXSize*Trans[4]+ImgYSize*Trans[5])/8);        //�Զ�����¼λ��(�ĸ��ǵ�)    ����Ϊ�˽���߿�����һЩ������.1��λ��������Ӧ�ĵ���ϻ����Ǽ�ȥ.1.
//	OGRPoint Point2(Trans[0]+ImgXSize*Trans[1]+ImgYSize*Trans[2]+(ImgXSize*Trans[1]+ImgYSize*Trans[2])/5,Trans[3]-(ImgXSize*Trans[4]+ImgYSize*Trans[5])/8);
//	OGRPoint Point3(Trans[0]+ImgXSize*Trans[1]+ImgYSize*Trans[2]+(ImgXSize*Trans[1]+ImgYSize*Trans[2])/5,Trans[3]+ImgXSize*Trans[4]+ImgYSize*Trans[5]+(ImgXSize*Trans[4]+ImgYSize*Trans[5])/3);
//	OGRPoint Point4(Trans[0]-(ImgXSize*Trans[1]+ImgYSize*Trans[2])/5,Trans[3]+ImgXSize*Trans[4]+ImgYSize*Trans[5]+(ImgXSize*Trans[4]+ImgYSize*Trans[5])/3);
//
//	double PolyrangeX=(Point2.getX()-Point1.getX())/30;
//	double PolyrangeY=-(Point3.getY()-Point2.getY())/5;
//
//	double Xp1=Point4.getX()+PolyrangeX/15;                          //��λͼ�����λ����Ϣ
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
//	//int ClassNum=6;//����
//
//	if(ClassNum==2)
//	{
//		OGRFieldDefn oField( "FirstCol", OFTInteger );    //���������ֶΣ���λ����߿��й�
//		oField.SetWidth(32);      //�����ֶο��
//		OGRFieldDefn oField_1( "PolyLabel", OFTString );    //���������ֶΣ���λ����߿��й�
//		oField_1.SetWidth(32);
//		if( (poLayer->CreateField( &oField ) != OGRERR_NONE )||(poLayer->CreateField( &oField_1 ) != OGRERR_NONE))
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("���������ֶ�ʧ�ܣ���"));
//			exit(1);
//		}
//		OGRFeature *poFeature;          //����feature��д�����
//		poFeature = OGRFeature::CreateFeature( poLayer->GetLayerDefn() );    //�Ͳ��Ӧ�����԰�
//
//		//�Ͳ��Ӧ�����Խ��а󶨣��Եõ�feature�ĵ�����field
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
//			QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("��ʸ�������д���Ҫ��(feature)ʧ�ܣ���"));
//			exit(1);
//		}
//
//		//OGRFieldDefn oField_2( "SeCol", OFTInteger );    //���������ֶΣ���λ����߿��й�
//		//oField_2.SetWidth(32);      //�����ֶο�� 
//		//OGRFieldDefn oField_2_1( "PolyLabel2", OFTString );    //���������ֶΣ���λ����߿��й�
//		//oField_2_1.SetWidth(32);
//		//if( (poLayer->CreateField( &oField_2 ) != OGRERR_NONE)||(poLayer->CreateField( &oField_2_1 ) != OGRERR_NONE ))
//		//{
//		//	QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("���������ֶ�ʧ�ܣ���"));
//		//	exit(1);
//		//}
//
//		OGRFeature *poFeature1=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature1);  //��layer�����
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
//			QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("��ʸ�������д���Ҫ��(feature)ʧ�ܣ���"));
//			exit(1);
//		}
//	}
//	if(ClassNum==3)
//	{
//		OGRFieldDefn oField( "Color", OFTInteger );    //���������ֶΣ���λ����߿��й�
//		oField.SetWidth(32);      //�����ֶο��
//		OGRFieldDefn oField_1( "PolyLabel", OFTString );    //���������ֶΣ���λ����߿��й�
//		oField_1.SetWidth(32);
//		if( (poLayer->CreateField( &oField ) != OGRERR_NONE )||(poLayer->CreateField( &oField_1 ) != OGRERR_NONE))
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("���������ֶ�ʧ�ܣ���"));
//			exit(1);
//		}
//		OGRFeature *poFeature;          //����feature��д�����
//		poFeature = OGRFeature::CreateFeature( poLayer->GetLayerDefn() );    //�Ͳ��Ӧ�����԰�
//		//�Ͳ��Ӧ�����Խ��а󶨣��Եõ�feature�ĵ�����field
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
//			QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("��ʸ�������д���Ҫ��(feature)ʧ�ܣ���"));
//			exit(1);
//		} 
//
//		OGRFeature *poFeature1=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature1);  //��layer�����
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
//			QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("��ʸ�������д���Ҫ��(feature)ʧ�ܣ���"));
//			exit(1);
//		}
//
//		OGRFeature *poFeature2=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature2);  //��layer�����
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
//			QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("��ʸ�������д���Ҫ��(feature)ʧ�ܣ���"));
//			exit(1);
//		}
//	}
//	if(ClassNum==4)
//	{
//		OGRFieldDefn oField( "Color", OFTInteger );    //���������ֶΣ���λ����߿��й�
//		oField.SetWidth(32);      //�����ֶο��
//		OGRFieldDefn oField_1( "PolyLabel", OFTString );    //���������ֶΣ���λ����߿��й�
//		oField_1.SetWidth(32);
//		if( (poLayer->CreateField( &oField ) != OGRERR_NONE )||(poLayer->CreateField( &oField_1 ) != OGRERR_NONE))
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("���������ֶ�ʧ�ܣ���"));
//			exit(1);
//		}
//		OGRFeature *poFeature;          //����feature��д�����
//		poFeature = OGRFeature::CreateFeature( poLayer->GetLayerDefn() );    //�Ͳ��Ӧ�����԰�
//		//�Ͳ��Ӧ�����Խ��а󶨣��Եõ�feature�ĵ�����field
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
//			QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("��ʸ�������д���Ҫ��(feature)ʧ�ܣ���"));
//			exit(1);
//		} 
//
//		OGRFeature *poFeature1=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature1);  //��layer�����
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
//			QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("��ʸ�������д���Ҫ��(feature)ʧ�ܣ���"));
//			exit(1);
//		}
//
//		OGRFeature *poFeature2=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature2);  //��layer�����
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
//			QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("��ʸ�������д���Ҫ��(feature)ʧ�ܣ���"));
//			exit(1);
//		}
//
//		OGRFeature *poFeature3=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature3);  //��layer�����
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
//			QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("��ʸ�������д���Ҫ��(feature)ʧ�ܣ���"));
//			exit(1);
//		}
//	}
//	if(ClassNum==5)
//	{
//		OGRFieldDefn oField( "Color", OFTInteger );    //���������ֶΣ���λ����߿��й�
//		oField.SetWidth(32);      //�����ֶο��
//		OGRFieldDefn oField_1( "PolyLabel", OFTString );    //���������ֶΣ���λ����߿��й�
//		oField_1.SetWidth(32);
//		if( (poLayer->CreateField( &oField ) != OGRERR_NONE )||(poLayer->CreateField( &oField_1 ) != OGRERR_NONE))
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("���������ֶ�ʧ�ܣ���"));
//			exit(1);
//		}
//		OGRFeature *poFeature;          //����feature��д�����
//		poFeature = OGRFeature::CreateFeature( poLayer->GetLayerDefn() );    //�Ͳ��Ӧ�����԰�
//		//�Ͳ��Ӧ�����Խ��а󶨣��Եõ�feature�ĵ�����field
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
//			QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("��ʸ�������д���Ҫ��(feature)ʧ�ܣ���"));
//			exit(1);
//		} 
//
//		OGRFeature *poFeature1=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature1);  //��layer�����
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
//			QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("��ʸ�������д���Ҫ��(feature)ʧ�ܣ���"));
//			exit(1);
//		}
//
//		OGRFeature *poFeature2=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature2);  //��layer�����
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
//			QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("��ʸ�������д���Ҫ��(feature)ʧ�ܣ���"));
//			exit(1);
//		}
//
//		OGRFeature *poFeature3=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature3);  //��layer�����
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
//			QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("��ʸ�������д���Ҫ��(feature)ʧ�ܣ���"));
//			exit(1);
//		}
//
//		OGRFeature *poFeature4=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature4);  //��layer�����
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
//			QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("��ʸ�������д���Ҫ��(feature)ʧ�ܣ���"));
//			exit(1);
//		}
//
//	}
//	if(ClassNum==6)
//	{
//		OGRFieldDefn oField( "Color", OFTInteger );    //���������ֶΣ���λ����߿��й�
//		oField.SetWidth(32);      //�����ֶο��
//		OGRFieldDefn oField_1( "PolyLabel", OFTString );    //���������ֶΣ���λ����߿��й�
//		oField_1.SetWidth(32);
//		if( (poLayer->CreateField( &oField ) != OGRERR_NONE )||(poLayer->CreateField( &oField_1 ) != OGRERR_NONE))
//		{
//			QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("���������ֶ�ʧ�ܣ���"));
//			exit(1);
//		}
//		OGRFeature *poFeature;          //����feature��д�����
//		poFeature = OGRFeature::CreateFeature( poLayer->GetLayerDefn() );    //�Ͳ��Ӧ�����԰�
//		//�Ͳ��Ӧ�����Խ��а󶨣��Եõ�feature�ĵ�����field
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
//			QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("��ʸ�������д���Ҫ��(feature)ʧ�ܣ���"));
//			exit(1);
//		} 
//
//		OGRFeature *poFeature1=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature1);  //��layer�����
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
//			QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("��ʸ�������д���Ҫ��(feature)ʧ�ܣ���"));
//			exit(1);
//		}
//
//		OGRFeature *poFeature2=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature2);  //��layer�����
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
//			QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("��ʸ�������д���Ҫ��(feature)ʧ�ܣ���"));
//			exit(1);
//		}
//
//		OGRFeature *poFeature3=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature3);  //��layer�����
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
//			QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("��ʸ�������д���Ҫ��(feature)ʧ�ܣ���"));
//			exit(1);
//		}
//
//		OGRFeature *poFeature4=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature4);  //��layer�����
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
//			QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("��ʸ�������д���Ҫ��(feature)ʧ�ܣ���"));
//			exit(1);
//		}
//
//		OGRFeature *poFeature5=OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
//		poLayer->CreateFeature(poFeature5);  //��layer�����
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
//			QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("��ʸ�������д���Ҫ��(feature)ʧ�ܣ���"));
//			exit(1);
//		}
//	}	
//
//	OGRDataSource::DestroyDataSource( poDS );   
//
//	/*****************************************************************************************************************
//	��ʾ���ɵ�ͼ��
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
//		//���ͼ�㵽ͼ�㼯��
//		m_pMapLayer->addMapLayer(pLayerV,true);
//
//		QList<QgsMapLayer*> m_layerSet=m_pMapCanvas->layers();
//		QgsMapLayer* pMapLayer=NULL;
//		pMapLayer = m_layerSet.at(0);		//Ŀǰֻ�ǽ���һ��ͼ�����Ϊ��ûˮ��ͼ
//		bool theResultFlag=false;
//		pMapLayer->loadNamedStyle(strColorPath,theResultFlag);
//
//
//		//ʸ�����ݷ�ǰ��,˳��Ϊ������
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
//		mypLabel=pLayerV->label();                    //�õ�����mylayer��labelָ��  
//
//		//QString str=pLayerV->name();                //�õ�shape�ļ��Ĵ洢·��
//		QgsLabelAttributes * mypLabelAttributes;  
//		mypLabelAttributes = mypLabel->layerAttributes();  
//
//		QgsFieldMap myFields = pLayerV->dataProvider()->fields();  //�õ�ʸ��ͼ����ֶ��б� 
//
//		mypLabel->setLabelField(QgsLabel::Text,1);    //���ó�Ϊ��ǩ���ֶ�
//
//		mypLabelAttributes->setColor(Qt::black);                    //����label
//		/*****�޸�****�޸�****�޸�****�޸�****�޸�****�޸�****�޸�***�޸�***�޸�****�޸�***�޸�****�޸�******�޸�***�޸�****�޸�***�޸�*****�޸�****�޸�****�޸�***�޸�***�޸�****�޸�***�޸�****�޸�***/
//		if(PolyrangeX<=PolyrangeY*0.15)
//		{
//			if(PolyrangeY*0.15/PolyrangeX>2.5)
//			{
//				mypLabelAttributes->setOffset(PolyrangeX*3,0,0);      //��һ���͵ڶ�������������λ�ã�������
//				mypLabelAttributes->setSize(PolyrangeX*1.1,0);
//			}
//			else
//			{
//				mypLabelAttributes->setOffset(PolyrangeX*3,0,0);      //��һ���͵ڶ�������������λ�ã�������
//				mypLabelAttributes->setSize(PolyrangeX*0.95,0);
//			}
//		}
//		else
//		{
//			if(PolyrangeX/(PolyrangeY*0.15)>2.5)
//			{
//				mypLabelAttributes->setOffset(PolyrangeY*0.45,0,0);      //��һ���͵ڶ�������������λ�ã�������
//				mypLabelAttributes->setSize(PolyrangeY*0.16,0);
//			} 
//			else
//			{
//				mypLabelAttributes->setOffset(PolyrangeY*0.45,0,0);      //��һ���͵ڶ�������������λ�ã�������
//				mypLabelAttributes->setSize(PolyrangeY*0.11,0);
//			}
//		}
//
//		/******************************************************************************************************/
//		//���ñ�ע  
//		pLayerV->enableLabels(true);
//	}
//}


//��������
void LSY_QRS::CreateProject()
{
	//QSettings settings;
	//QString lastUsedDir = settings.value( "/UI/lastProjectDir", "." ).toString();
	//QString fullPath = QFileDialog::getOpenFileName( mIface->mainWindow(),
	//	QString::fromLocal8Bit( "������ʵ����Ӱ��·��" ),
	//	lastUsedDir,
	//	QString::fromLocal8Bit( "Ӱ��" ) + " (*.*)" );
	//if ( fullPath.isNull() )
	//{
	//	return;
	//}

	//QFileInfo myRasterFileInfo( fullPath );
	//QByteArray ba = myRasterFileInfo.absoluteFilePath().toLatin1();
	//const char *c_str2 = ba.data();

	//GDALDataset* poDataset;//GDAL���ݼ�
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
	//mIface->addRasterLayer( myRasterFileInfo.absoluteFilePath(), myRasterFileInfo.completeBaseName());//��Ӱ����ʾ����ͼ��ͼ��
	//return;

	ocCreateProject(&m_pPrj);
	QString fullPath = m_pPrj->m_pOrgImgName;
	fullPath.toLocal8Bit();
	QFileInfo myRasterFileInfo( fullPath );
	QByteArray ba = myRasterFileInfo.absoluteFilePath().toLatin1();
	//const char *c_str2 = ba.data();
	mIface->addRasterLayer( myRasterFileInfo.absoluteFilePath(), myRasterFileInfo.completeBaseName());//��Ӱ����ʾ����ͼ��ͼ��

}

//�򿪹���
void LSY_QRS::OpenProject()
{
	if(NULL != m_pPrj) 
	{
//		OnProjectClose();
	}
	ocOpenProject(&m_pPrj);
}

//���湤��
void LSY_QRS::SaveProject()
{
}

//���Ϊ����
void LSY_QRS::SaveProjectAs()
{
}

//�رչ���
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
	//QLibrary mylib("E:\\c++\\LSY_QRS\\LSY_QRS\\TestDll.dll");   //�������õ���dll�ļ�
	//if (mylib.load())              //�ж��Ƿ���ȷ����
	//{
	//	typedef BOOL(*Fun)(char*);
	//	Fun open=(Fun)mylib.resolve("MultiScaleSegment");
	//	if (open)                  //�Ƿ�ɹ������� add() ����
	//	{
	//		open("E:\\c++\\TestDllApp\\debug\\1.tif");      //���ﺯ��ָ�����dll�е� add() ����
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
	mIface->addVectorLayer( myRasterFileInfo.absoluteFilePath(), myRasterFileInfo.completeBaseName(),"ogr");//��Ӱ����ʾ����ͼ��ͼ��


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

void LSY_QRS::EditClassifie()//�༭��
{
	/*QMessageBox::about(0,QString::fromLocal8Bit("��ʾ��"),
		QString::fromLocal8Bit("����\n")); */
	QTreeWidget* moduleTree=new QTreeWidget;
	emit ContextMenuShow(moduleTree);
}
void LSY_QRS::InsertClassifie(QTreeWidget* moduleTree)//������
{
	QMessageBox::about(0,QString::fromLocal8Bit("��ʾ��"),
		QString::fromLocal8Bit("����\n")); 
}
void LSY_QRS::CopyClassifie()//������
{

}
void LSY_QRS::DeletClassifie()//ɾ����
{
}
void LSY_QRS::OutputClassifieRule()//���������
{
}
void LSY_QRS::InputClassifieRule()//���������
{
}

void LSY_QRS::SelectXingZheng(QTreeWidgetItem *item, int column)
{
	/*QMessageBox::about(0,QString::fromLocal8Bit("��ʾ��"),
		QString::fromLocal8Bit("����\n")); */
	QLibrary mylib("E:\\c++\\LSY_QRS\\LSY_QRS\\TestDll.dll");   //�������õ���dll�ļ�
//	QLibrary mylib("CImgSegDlg.dll");   //�������õ���dll�ļ�
	if (mylib.load())              //�ж��Ƿ���ȷ����
	{
		QMessageBox::information(NULL,"OK","DLL load is OK!!!!!!!");

//		typedef void(*Fun)(); //���庯��ָ�룬�Ա�����
		typedef BOOL(*Fun)(char*);

//		Fun open=(Fun)mylib.resolve("Show");    //Ԯ�� Show() ����
		Fun open=(Fun)mylib.resolve("MultiScaleSegment");

		if (open)                  //�Ƿ�ɹ������� add() ����
		{
			QMessageBox::information(NULL,"OK","Link to Function is OK!");
			open("E:\\c++\\TestDllApp\\debug\\1.tif");      //���ﺯ��ָ�����dll�е� add() ����				
		}
		else
		{
			 QMessageBox::information(NULL,"NO","Linke to Function is not OK!!!!");
		}

	}
	else
		QMessageBox::information(NULL,"NO","DLL is not loaded!");

	//typedef void (*Fun)(); //���庯��ָ�룬�Ա�����
	//QLibrary mylib("CImgSegDlg.dll");   //�������õ���dll�ļ�
	//int result;
	//if (mylib.load())              //�ж��Ƿ���ȷ����
	//{
	//	QMessageBox::information(NULL,"OK","DLL load is OK!");
	//	Fun open=(Fun)mylib.resolve("SetXmlPrjDlg");    //Ԯ�� add() ����
	//	if (open)                  //�Ƿ�ɹ������� add() ����
	//	{
	//		QMessageBox::information(NULL,"OK","Link to Function is OK!");
	//		open();      //���ﺯ��ָ�����dll�е� add() ����
	//	}
	//	else
	//		QMessageBox::information(NULL,"NO","Linke to Function is not OK!!!!");
	//}
	//else
	//	QMessageBox::information(NULL,"NO","DLL is not loaded!");
//	MultiScaleSegment("E:\\c++\\TestDllApp\\debug\\1.tif");

//	return 0;  //����ʧ�����˳�
}
void LSY_QRS::SelectXingZheng1(QTreeWidgetItem *item, int column)
{
	QMessageBox::about(0,QString::fromLocal8Bit("��ʾ��"),
		QString::fromLocal8Bit("����\n")); 
}
void LSY_QRS::SelectXingZheng2(QTreeWidgetItem *item, int column)
{
	/*QAboutDlg dlg;
	dlg.setModal(true);
	dlg.exec();*/
}
void LSY_QRS::ShowContextMenu(QTreeWidget* moduleTree)
{
	mAction13=new QAction(QString::fromLocal8Bit("�༭��"), this);//�༭��
	mAction14=new QAction(QString::fromLocal8Bit("������"), this);//������
	mAction15=new QAction(QString::fromLocal8Bit("������"), this);//������
	mAction16=new QAction(QString::fromLocal8Bit("ɾ����"), this);//ɾ����
	mAction17=new QAction(QString::fromLocal8Bit("���������"), this);//���������
	mAction18=new QAction(QString::fromLocal8Bit("���������"), this);//���������
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
	Action=new QAction(name, this);//�༭��
	moduleTree->addAction(mAction18);
	moduleTree->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void LSY_QRS::InitalProgressBar(/*(void *)mProgressBar,(void *)m_statusBar,char**/)//��ʼ��������
{

}
void LSY_QRS::ReleaseProgBar()//����
{

}
QGISEXTERN QgisPlugin* classFactory(QgisInterface* iface)
{
	return new LSY_QRS(iface);
}
QGISEXTERN QString name()
{
#ifdef WIN_XP
	return QString::fromLocal8Bit("�߷ֱ���ң��Ӱ���¼��ϵͳ-XP");
#else
	return QString::fromLocal8Bit("�߷ֱ���ң��Ӱ���¼��ϵͳ");
#endif
}
QGISEXTERN QString description()
{
#ifdef WIN_XP
	return QString::fromLocal8Bit("���ڸ߷ֱ���ң��Ӱ��Ļ��µ����ֺ���Ϣʶ������ȡ���ϵͳ-XP");
#else
	return QString::fromLocal8Bit("���ڸ߷ֱ���ң��Ӱ��Ļ��µ����ֺ���Ϣʶ������ȡ���ϵͳ");
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
