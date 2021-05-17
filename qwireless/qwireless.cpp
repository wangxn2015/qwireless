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

    mQActionPointer = new QAction(QIcon(":/qrap/Data.png"),tr("Q-Rap Database Interface"), this);
    mSiteAction = new QAction(QIcon(":/qrap/Site.png"),tr("Q-Rap: Place a Site"), this);
    mSelectSiteAction = new QAction(QIcon(":/qrap/SiteSelect.png"),tr("Q-Rap: Select a Site"), this);
    mDeleteSiteAction = new QAction(QIcon(":/qrap/SiteDelete.png"),tr("Q-Rap: Delete a Site"), this);
    mRadioAction = new QAction(QIcon(":/qrap/Coverage.png"),tr("Q-Rap: Perform a Prediction"), this);
    mPreferencesAction = new QAction(QIcon(":/qrap/Preferences.png"),tr("Q-Rap Preferences"), this);
    mReadValueAction = new QAction(QIcon(":/qrap/Questionmark.jpg"),tr("read map layer value"), this);

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
    cout<<"open database connection"<<endl;



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
























