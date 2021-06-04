#include "qwireless.h"
#include <qgisinterface.h>
#include <qgisgui.h>


// Qt4 Related Includes
#include <QAction>
#include <QToolBar>
#include <QMessageBox>
#include <stdio.h>
//#include <qgsrasteridentifyresult.h> //added by wxn, using moving mouse event to read map value


#include "Qapp/_qgsmaptoolidentifyaction.h"


static const QString sPluginIcon = ":/qrap/Coverage.png";
static const QgisPlugin::PLUGINTYPE sPluginType = QgisPlugin::UI;
static const QString sCategory = QObject::tr("Database");
static const QString sName = QObject::tr("QWireless");
static const QString sDescription = QObject::tr("Radio Systems Planning Tool");
static const QString sPluginVersion = QObject::tr("Version 0.1");


QWireless::QWireless(QgisInterface* theInterface):
    QgisPlugin(sName, sDescription, sCategory, sPluginVersion, sPluginType ),
    mQgisMainWindow(theInterface->mainWindow()),
    mQGisIface(theInterface)
{

}

QWireless::~QWireless()
{

}

void QWireless::initGui()
{
    mToolBarPointer = 0;
    mPoints.clear();
    mMouseType = CLEAN;

    mQActionPointer = new QAction(QIcon(":/qrap/Data.png"),tr("QWireless Database Interface"), this);
    mSiteAction = new QAction(QIcon(":/qrap/Site.png"),tr("QWireless: Place a Site"), this);
    mSelectSiteAction = new QAction(QIcon(":/qrap/SiteSelect.png"),tr("QWireless: Select a Site"), this);
    mDeleteSiteAction = new QAction(QIcon(":/qrap/SiteDelete.png"),tr("QWireless: Delete a Site"), this);
    mRadioAction = new QAction(QIcon(":/qrap/Coverage.png"),tr("QWireless: Perform a Prediction"), this);
    mPreferencesAction = new QAction(QIcon(":/qrap/Preferences.png"),tr("QWireless Preferences"), this);
    mReadValueAction = new QAction(QIcon(":/qrap/Questionmark.jpg"),tr("QWireless: read map layer value"), this);

    connect(mQActionPointer, SIGNAL(activated()), this, SLOT(run()));
    connect(mSiteAction, SIGNAL(activated()), this, SLOT(PlaceSite()));
    connect(mSelectSiteAction, SIGNAL(activated()), this, SLOT(SelectSite()));
    connect(mDeleteSiteAction, SIGNAL(activated()), this, SLOT(DeleteSite()));
    connect(mPreferencesAction, SIGNAL(activated()), this, SLOT(Preferences()));
    connect(mRadioAction, SIGNAL(activated()), this, SLOT(Prediction()));
    connect(mReadValueAction, SIGNAL(activated()), this, SLOT(ReadMapValue()));

    mToolBarPointer = mQGisIface->addToolBar(tr("Q-Wireless"));
    mToolBarPointer->setIconSize(QSize(24,24));
    mToolBarPointer->setObjectName("Q-Wireless");
    mToolBarPointer->addAction(mSiteAction);
    mToolBarPointer->addAction(mSelectSiteAction);
    mToolBarPointer->addAction(mDeleteSiteAction);
    mToolBarPointer->addAction(mRadioAction);       //coverage
    mToolBarPointer->addAction(mPreferencesAction); //para
    mToolBarPointer->addAction(mQActionPointer); //database interface
    mToolBarPointer->addAction(mReadValueAction);

    mLoaded = true;

    openDatabaseConnection();

    //! 关联鼠标事件
    Mouse = new MouseEvents(mQGisIface->mapCanvas());
    cout << "create mouse event" << endl;
    connect(Mouse, SIGNAL(RightPoint(QgsPoint&)), this, SLOT(ReceivedRightPoint(QgsPoint&)));
    connect(Mouse, SIGNAL(LeftPoint(QgsPoint&)), this, SLOT(ReceivedLeftPoint(QgsPoint&)));




}



void QWireless::run()
{
    cout<<"run"<<endl;
    //    gMainWindow = new MainWindow(mQgisMainWindow); // param 'qgisMainWindow' is 0
    //    connect(gMainWindow, SIGNAL(SelectArea()),this,  SLOT(SelectArea()));//! not sure what's the use of this line. wxn
    //    gMainWindow->show();
    //    mQGisIface->mapCanvas()->refresh();
}

void QWireless::PlaceSite()
{
    cout<<"place site"<<endl;

    cout << " in QRap::PlaceSite() " << endl;
    mMouseType = PLACESITE;
    mQGisIface->mapCanvas()->setMapTool(Mouse);


}

void QWireless::SelectSite()
{
    cout<<"select site"<<endl;


}


void QWireless::DeleteSite()
{
    cout<<"delete site"<<endl;


}


void QWireless::Preferences()
{
    cout<<"preference"<<endl;


}


void QWireless::Prediction()
{
    cout<<"prediction"<<endl;


}

void QWireless::ReadMapValue()
{
    cout<<"readmap"<<endl;


}

void QWireless::help()
{

}


void QWireless::unload()
{
    if (mLoaded)
    {
        // remove the GUI

        mToolBarPointer->removeAction(mSiteAction);
        mToolBarPointer->removeAction(mSelectSiteAction);
        mToolBarPointer->removeAction(mDeleteSiteAction);
        mToolBarPointer->removeAction(mRadioAction);
        mToolBarPointer->removeAction(mPreferencesAction);
        mToolBarPointer->removeAction(mQActionPointer);
        mToolBarPointer->removeAction(mReadValueAction);

        delete mQActionPointer;
        delete mSelectSiteAction;
        delete mDeleteSiteAction;
        delete mSiteAction;
        delete mRadioAction;
        delete mPreferencesAction;

        delete mToolBarPointer;


        mLoaded =false;

    }
    cout << "QRap::unload(): leaving" << endl;
}


//******************************************************************************
bool QWireless::openDatabaseConnection()
{
    cout<<"QWireless::open database connection"<<endl;

    if(!gSettings.LoadFromFile("/usr/lib/qgis/plugins/settings.xml"))
    {
        cout<<"Error loading settings when connecting to DB..."<<endl;
        exit(1);
    }

    cout << "QWireless::Na Load Settings file in QRap::openDatabaseConnection() " << endl;
    LoginDialog* loginDialog;

    loginDialog = new LoginDialog(0);

    cout<<"QWireless::qgisMainWindow:"<<(void*)mQgisMainWindow<<endl;
    cout<< "QWireless::open database connection finished"<<endl;

}










QGISEXTERN QgisPlugin * classFactory(QgisInterface * theQgisInterfacePointer)
{
    return new QWireless(theQgisInterfacePointer);
}

//******************************************************************************
// Return the name of the plugin - note that we do not user class members as
// the class may not yet be insantiated when this method is called.
QGISEXTERN QString name()
{
    return sName;
}

//*******************************************************************************
// Return the description
QGISEXTERN QString description()
{
    return sDescription;
}

//********************************************************************************
// Return the type (either UI or MapLayer plugin)
QGISEXTERN int type()
{
    return sPluginType;
}

//********************************************************************************
// Return the version number for the plugin
QGISEXTERN QString version()
{
    return sPluginVersion;
}

//********************************************************************************
// Return the Icon for the plugin
QGISEXTERN QString icon()
{
  return sPluginIcon;
}

//********************************************************************************
// Return the category
QGISEXTERN QString category()
{
  return sCategory;
}

//*******************************************************************************
// Delete ourself
QGISEXTERN void unload( QgisPlugin * thePluginPointer )
{
    delete thePluginPointer;
}





//*************************************************************************************
void QWireless::ReceivedRightPoint(QgsPoint &Point)
{
    cout << " in QRap::ReceivedRIGHTPoint(QgsPoint &Point) " << endl;
    if (mMouseType != CLEAN)
    {
        if (mMouseType == PLACESITE) //! cancel the  action of place site
        {
            mMouseType = CLEAN;
            mQGisIface->mapCanvas()->setCursor(Qt::OpenHandCursor);
        }
//        if (mMouseType == SELECTLINK)
//        {
//            mMouseType = CLEAN;
//            mQGisIface->mapCanvas()->setCursor(Qt::OpenHandCursor);
//        }
//        if (mMouseType == DELETELINK)
//        {
//            mMouseType = CLEAN;
//            mQGisIface->mapCanvas()->setCursor(Qt::OpenHandCursor);
//        }
//        if (mMouseType == LINK1 || mMouseType == LINK2)
//        {
//            DesRubberBand();
//            mQGisIface->mapCanvas()->setCursor(Qt::OpenHandCursor);
//        }
        if (mMouseType == AREA) //! 预测处理
        {
            mPoints.append(Point);

            mRubberBand->addPoint(Point); // the polygon drawing by mouse
            DesRubberBand(); // destroy the polygon area when choosing area since it's finished
            PerformPrediction(); //!

            mQGisIface->mapCanvas()->setCursor(Qt::OpenHandCursor);
            mMouseType = CLEAN;
        }
//        if (mMouseType == FILTERAREA)
//        {
//            mPoints.append(Point);
//            mRubberBand->addPoint(Point);
//            DesRubberBand();
//            FilterArea();
//            mQGisIface->mapCanvas()->setCursor(Qt::OpenHandCursor);
//            mMouseType = CLEAN;
//        }
//        if (mMouseType == SPECTRAL)
//        {
//            mPoints.append(Point);
//            mRubberBand->addPoint(Point);
//            DesRubberBand();
//            PerformSpectral();
//            mQGisIface->mapCanvas()->setCursor(Qt::OpenHandCursor);
//            mMouseType = CLEAN;
//        }
//        if (mMouseType == MULTILINK)
//        {
//            mPoints.append(Point);
//            mRubberBand->addPoint(Point);
//            DesRubberBand();
//            PerformMultiLink();
//            mQGisIface->mapCanvas()->setCursor(Qt::OpenHandCursor);
//            mMouseType = CLEAN;
//        }
//        if (mMouseType == OPTIMISATION)
//        {
//            mPoints.append(Point);
//            mRubberBand->addPoint(Point);
//            DesRubberBand();
//            PerformOptimisation();
//            mQGisIface->mapCanvas()->setCursor(Qt::OpenHandCursor);
//            mMouseType = CLEAN;
//        }
    }
}


//******************************************************************************************
void QWireless::ReceivedLeftPoint(QgsPoint &Point)
{
    cout << " in QRap::ReceivedLeftPoint(QgsPoint &Point) " << endl;
    if (mMouseType != CLEAN)
    {
        if (mMouseType == PLACESITE) //!
        {
            cout << " placesite " << endl;
//            QMessageBox::information(mQGisIface->mainWindow(), "Q-Rap", "Wait: getting height data at point");

            QMessageBox *box = new QMessageBox(QMessageBox::Information,tr("Q-rap"), tr("Wait: getting height data at point..."));
            box->addButton(QMessageBox::Ok);
            box->button(QMessageBox::Ok)->hide();
            QTimer::singleShot(1000,box,SLOT(accept()));
            box->exec();

            PlaceSiteDialog((Point.y()),(Point.x()),false); //! 在函数中，打开对话窗口. y is weidu (latitude), x is jingdu (longtitude)
            if (mMouseType!=MOVESITE)
            {
                mMouseType = CLEAN;
                mQGisIface->mapCanvas()->setCursor(Qt::OpenHandCursor);
                mQGisIface->mapCanvas()->refresh();
            }
        }
//        else if (mMouseType == MOVESITE)
//        {
//            cout << " movesite " << endl;
//            QMessageBox::information(mQGisIface->mainWindow(), "Q-Rap", "Wait: getting height data at point");
//            MoveSiteDialog((Point.y()),(Point.x()));
//            mMouseType = CLEAN;
//            mQGisIface->mapCanvas()->setCursor(Qt::OpenHandCursor);
//            mQGisIface->mapCanvas()->refresh();
//        }

          //! need this function //wxn
//        else if (mMouseType == SELECTSITE)
//        {
//            cout << " selectsite " << endl;
//            PlaceSiteDialog((Point.y()),(Point.x()),true);
//            if (mMouseType!=MOVESITE)
//            {
//                mMouseType = CLEAN;
//                mQGisIface->mapCanvas()->setCursor(Qt::OpenHandCursor);
//            }
//        }
            //!-------------------------------------
//        if (mMouseType == LINK2)
//        {
//            cout << " Link2 " << endl;
//            mPoints.append(Point);
//            mRubberBand->addPoint(Point);
//            DesRubberBand();
//            PerformLink();
//            mQGisIface->mapCanvas()->setCursor(Qt::OpenHandCursor);
//        }
//        if (mMouseType == LINK1)
//        {
//            cout << " Link1 " << endl;
//            mPoints.append(Point);
//            mRubberBand->addPoint(Point);
//            mMouseType = LINK2;
//        }
        if (mMouseType == AREA) //! 选取预测区域
        {
            cout << " Area " << endl;
            mPoints.append(Point);
            mRubberBand->addPoint(Point);
        }
//        if (mMouseType == FILTERAREA)
//        {
//            cout << " Filter Area " << endl;
//            mPoints.append(Point);
//            mRubberBand->addPoint(Point);
//        }
//        if (mMouseType == SELECTLINK)
//        {
//            cout << " Select Link " << endl;
//            GetLink((Point.y()),(Point.x()));
//            mMouseType = CLEAN;
//            mQGisIface->mapCanvas()->setCursor(Qt::OpenHandCursor);
//        }
//        if (mMouseType == SPECTRAL)
//        {
//            cout << " spectral " << endl;
//            mPoints.append(Point);
//            mRubberBand->addPoint(Point);
//        }
//        if (mMouseType == MULTILINK)
//        {
//            cout << " multilink " << endl;
//            mPoints.append(Point);
//            mRubberBand->addPoint(Point);
//        }
//        if (mMouseType == OPTIMISATION)
//        {
//            cout << " optimisation " << endl;
//            mPoints.append(Point);
//            mRubberBand->addPoint(Point);
//        }

          //! need this function . //wxn
//        if (mMouseType == DELETESITE)
//        {
//            cout << "Deleting site we hope ..." << endl;
//            cDeleteObject *Delete = new cDeleteObject(mQGisIface->mainWindow(), QgisGui::ModalDialogFlags);
//            cout << "After delete object constructer" << endl;
//            QString Lat = QString("%1").arg(Point.y());
//            QString Lon = QString("%1").arg(Point.x());
//            if (Delete->SetParameters(Lat,Lon,true,mQGisIface->mapCanvas()->scale()))
//            {
//                if (Delete->exec()==1)
//                {
//                    mQGisIface->mapCanvas()->refresh();
//                }
//            }
//            mMouseType = CLEAN;
//            mQGisIface->mapCanvas()->setCursor(Qt::OpenHandCursor);
//        }
        //!-------------------------------------

//        if (mMouseType == DELETELINK)
//        {
//            cout << " delete link " << endl;
//            cDeleteObject *Delete;
//            Delete = new cDeleteObject(mQGisIface->mainWindow(), QgisGui::ModalDialogFlags);
//            QString Lat = QString("%1").arg(Point.y());
//            QString Lon = QString("%1").arg(Point.x());
//            if (Delete->SetParameters(Lat,Lon,false,mQGisIface->mapCanvas()->scale()))
//            {
//                if (Delete->exec()==1)
//                {
//                    mQGisIface->mapCanvas()->refresh();
//                }
//            }
//            mMouseType = CLEAN;
//            mQGisIface->mapCanvas()->setCursor(Qt::OpenHandCursor);
//        }
    }
    else  cout << " mouse clean " << endl;
}



void QWireless::PlaceSiteDialog(double lat, double lon,bool IsOld) //! 纬度前，经度. point.y; point.x
{
    cout << " In QRap::PlaceSiteDialog" << endl;
    QString Lat = QString("%1").arg(lat);
    QString Lon = QString("%1").arg(lon);
    mPlacedSite = new cPlaceSite(mQGisIface, mQGisIface->mainWindow(), QgisGui::ModalDialogFlags);//! ui
//    connect(mPlacedSite, SIGNAL(MoveSiteClicked()),this,  SLOT(MoveSiteClicked())); // wxn

    // place the site // IsOld = false
    if (mPlacedSite->SetParameters(Lat,Lon,IsOld,mQGisIface->mapCanvas()->scale())) //! 显示选点处的参数
    {
        if (mPlacedSite->exec()==1)
        {
            mQGisIface->mapCanvas()->refresh();
        }
    }
}














