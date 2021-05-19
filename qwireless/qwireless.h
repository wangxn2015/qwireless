#ifndef QWIRELESS_H
#define QWIRELESS_H

using namespace std;


#include <QObject>
#include <QMessageBox>
#include <QApplication>
//#include <QPixmap>
//#include <QSplashScreen>
//#include <QBitmap>
//#include <QTimer>
#include <QCursor>
#include <QString>
#include <QObject>
#include <QMouseEvent>

//QGIS includes
#include <qgisplugin.h>
#include <qgisinterface.h>
#include <qgisgui.h>
#include <qgspoint.h>
#include <qgsmapcanvas.h>
#include <qgsmaptool.h>
//#include <qgsmaptopixel.h>
//#include <qgsmaptoolemitpoint.h>
//#include <qgscolorrampshader.h>
#include <qgsrubberband.h>
#include <qgsmaplayer.h>
#include <qgsrasterlayer.h>
//#include <qgsproject.h>


//
// Radio Planning Tool Includes
#include "DataBase/Config.h"
#include "DataBase/MainWindow.h"
#include "DataBase/LoginDialog.h"
//#include "Prediction/cSpectralPlot.h"
//#include "Prediction/cPlotTask.h"
//#include "Prediction/cLink.h"
//#include "cMouseEvents.h"
//#include "Interface/cPlaceSite.h"
//#include "Interface/cDeleteObject.h"
//#include "Interface/cConfirmLink.h"
//#include "Interface/cConfirmPrediction.h"
//#include "Interface/cConfirmSpectral.h"
//#include "Interface/cConfirmMultiLink.h"
//#include "Interface/cLinkAnalysis.h"
//#include "Interface/cSpectralAnalysis.h"
//#include "Interface/cColourManager.h"
//#include "Interface/cFilterDialog.h"
//#include "DataBase/PreferencesDialog.h"
//#include "Interface/cMeasurementAnalysis.h"
//#include "Interface/cBackup.h"
//#include "Interface/Optimisation.h"
//#include "Interface/cImportExportMenu.h"
//#include "Interface/cUpdateToServer.h"
//#include "Interface/cCreateUpdateFile.h"
//#include "Interface/cImportUpdateFile.h"



class QAction;
class QToolBar;

class QgisInterface;
class QgisApp;
class QgsRubberBand;

//----start-------here------


enum MouseActionType
{
    CLEAN,
    PLACESITE,
    DELETESITE,
    AREA,

};

class QWireless: public QObject, public QgisPlugin
{
    Q_OBJECT
public:
    QWireless(QgisInterface* QGisIface);
    virtual ~QWireless();

public slots:
    //! init the gui
    virtual void initGui();
    //! Show the dialog box
    void run();
        //! unload the plugin
    void unload();
    //! show the help document
    void help();
    void Help();
    void PlaceSite();
    void Prediction();
    void SelectSite();
//  	void SelectArea();
//      void MoveSiteClicked();
    void Preferences();
//  	void ColourManager();
    void DeleteSite();
//  	void ImportExport();
//  	void Test();
//  	void MakeUpdateFile();

//    void ReceivedRightPoint(QgsPoint &);
//    void ReceivedLeftPoint(QgsPoint &);
//    void ReceiveMouseMove(QgsPoint &);
//    void ReadMap(QgsPoint &);
    void ReadMapValue();

private:
    //! Pointer to our toolbar
    QToolBar *mToolBarPointer;
    //! Pointer to the QGIS interface object
    QgisInterface *mQGisIface;
    //!pointer to the qaction for this plugin
    QAction * mQActionPointer;
    //! Pionter to QGIS main application object
    QWidget *mQgisMainWindow;

    // Actions
    QAction *mSiteAction;
    QAction *mSelectSiteAction;
    QAction *mDeleteSiteAction;
    QAction *mPreferencesAction;
    QAction *mRadioAction;
    QAction *mReadValueAction; //added by wxn

    QWidget *mQGisApp;

//    void PlaceSiteDialog(double lat, double lon,bool IsOld);
//    void MoveSiteDialog(double lat, double lon);
//    void UpdateSiteLayer();
//    void InitRubberBand(bool IsArea);
//    void DesRubberBand();
    bool openDatabaseConnection();
//    bool PerformPrediction();

//    MouseEvents *Mouse;
//    QString Action;
    MouseActionType mMouseType;
    QList<QgsPoint> mPoints;
//    QgsRubberBand *mRubberBand;
//    cPlaceSite *mPlacedSite;
    bool mLoaded;
    // the username and password for the database login.
//    string machinename;
//    //! add this
//    _QgsMapToolIdentifyAction *mMapToolIdentify;
//    cConfirmPrediction *mConfirmPrediction;

};

#endif // QWIRELESS_H
