/*=========================================================================

  Program:   Monteverdi2
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See Copyright.txt for details.

  Monteverdi2 is distributed under the CeCILL licence version 2. See
  Licence_CeCILL_V2-en.txt or
  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt for more details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef __mvdMainWindow_h
#define __mvdMainWindow_h

//
// Configuration include.
//// Included at first position before any other ones.
#include "ConfigureMonteverdi2.h"

// #if (defined( _DEBUG ) && FORCE_DISABLE) || FORCE_ENABLE
#define USE_ICE_IMAGE_VIEW ((defined( _DEBUG ) && 1) || 0)
#define USE_OLD_IMAGE_VIEW ((!USE_ICE_IMAGE_VIEW  && 1) || 0)

/*****************************************************************************/
/* INCLUDE SECTION                                                           */

//
// Qt includes (sorted by alphabetic order)
//// Must be included before system/custom includes.
#include <QtOpenGL>

//
// System includes (sorted by alphabetic order)

//
// ITK includes (sorted by alphabetic order)

//
// OTB includes (sorted by alphabetic order)

//
// Monteverdi includes (sorted by alphabetic order)
#include "Core/mvdTypes.h"
//
#include "Gui/mvdI18nMainWindow.h"


/*****************************************************************************/
/* PRE-DECLARATION SECTION                                                   */

//
// External class pre-declaration.
namespace
{
}

namespace mvd
{
//
// Internal class pre-declaration.
// Core
class DatasetModel;
// Gui
class FilenameDragAndDropEventFilter;
#if USE_OLD_IMAGE_VIEW
class GLImageWidget1;
#endif // USE_OLD_IMAGE_VIEW
#if USE_ICE_IMAGE_VIEW
class ImageViewWidget;
#endif // USE_ICE_IMAGE_VIEW
class StatusBarWidget;

namespace Ui
{
class MainWindow;
}

/*****************************************************************************/
/* CLASS DEFINITION SECTION                                                  */

/**
 * \class MainWindow
 *
 * \brief The application main-widow widget.
 */
class Monteverdi2_EXPORT MainWindow
  : public I18nMainWindow
{

  /*-[ QOBJECT SECTION ]-----------------------------------------------------*/

  Q_OBJECT;

  /*-[ PUBLIC SECTION ]------------------------------------------------------*/

//
// Public types.
public:

//
// Public methods.
public:
  /** \brief Constructor. */
  MainWindow( QWidget* Parent =0, Qt::WindowFlags flags =0 );

  /** \brief Destructor. */
  virtual ~MainWindow();

  /*-[ SIGNALS SECTION ]-----------------------------------------------------*/

//
// SIGNALS.
signals:

  void UserCoordinatesEditingFinished(const QString&);

  void UserScaleEditingFinished(const QString &);

  void UserZoomIn();

  void UserZoomOut();

  void UserZoomExtent();

  void UserZoomFull();

  /*-[ PROTECTED SECTION ]---------------------------------------------------*/

//
// Protected methods.
protected:

  /**
   */
  void ImportImage( const QString& filename, bool forceCreate );

  using I18nMainWindow::ImportImage;

  //
  // QMainWindow overrides.

  void closeEvent( QCloseEvent* event );

//
// Protected attributes.
protected:

  /*-[ PROTECTED SLOTS SECTION ]---------------------------------------------*/

//
// Protected slots.
protected slots:

  /**
   */
  void OnAboutToChangeModel( const AbstractModel* );

  /**
   */
  void OnModelChanged( AbstractModel* );

  /**
   */
  void OnAboutToChangeSelectedDatasetModel( const DatasetModel* );

  /**
   */
  void OnSelectedDatasetModelChanged( DatasetModel* );

  /**
   */
  void OnApplicationToLaunchSelected( const QString & appName, const QString & docName );

  /**
   */
  void OnTabCloseRequested( int index );

  /**
   */
  void OnTabCloseRequested();

  /** */
  void OnOTBApplicationOutputImageChanged( const QString & appName, const QString & outfname);

  /**
   */
  void OnExecutionDone( int status );

  /*-[ PRIVATE SECTION ]-----------------------------------------------------*/

//
// Private types.
private:


//
// Private methods.
private:

#if USE_OLD_IMAGE_VIEW
  /**
   */
  GLImageWidget1* CreateImageWidget1( QGLWidget* sharedGlWidget =NULL );

  /**
   */
  GLImageWidget1* CreateQuicklookWidget1( QGLWidget* sharedGlWidget =NULL );
#endif // USE_OLD_IMAGE_VIEW

#if USE_ICE_IMAGE_VIEW
  /**
   */
  ImageViewWidget* CreateImageViewWidget( QGLWidget* sharedGlWidget =NULL );

  /**
   */
  ImageViewWidget* CreateQuicklookViewWidget( QGLWidget* sharedGlWidget =NULL );
#endif // USE_ICE_IMAGE_VIEW

  /**
   */
  void InitializeDockWidgets();

  /**
   */
  void InitializeCentralWidget();

  /**
   */
  void InitializeStatusBarWidgets();

#if USE_OLD_IMAGE_VIEW
  /**
   */
  inline
    const GLImageWidget1* GetQuicklookView1() const;

  /**
   */
  inline
    GLImageWidget1* GetQuicklookView1();

  /**
   */
  void ConnectImageViews1();
#endif // USE_OLD_IMAGE_VIEW

#if USE_ICE_IMAGE_VIEW
  /**
   */
  inline
    const ImageViewWidget* GetQuicklookView() const;
  /**
   */
  inline
    ImageViewWidget* GetQuicklookView();

  /**
   */
  void ConnectImageViews();
#endif // USE_OLD_IMAGE_VIEW

  /**
   */
  void ConnectViewMenu();

  /**
   */
  void ConnectStatusBar(DatasetModel * model);
  void DisconnectStatusBar(const DatasetModel * model);

  /**
   */
  void ConnectPixelDescriptionWidget(DatasetModel * model);
  void DisconnectPixelDescriptionWidget(const DatasetModel * model);

  //
  // I18nMainWindow overrides.

  virtual void virtual_SetupUI();

  virtual void virtual_ConnectUI();

//
// Private attributes.
private:
  /**
   * \brief uic generated.
   */
  Ui::MainWindow* m_UI;

  /**
   * \brief Color dynamicsk-view dock-widget.
   */
  QDockWidget* m_ColorDynamicsDock;

  /**
   * \brief Color setup dock-widget.
   */
  QDockWidget* m_ColorSetupDock;

  /**
   * \brief Database-browser dock-widget.
   */
  QDockWidget* m_DatabaseBrowserDock;

  /**
   * \brief Dataset-properties dock-widget.
   */
  QDockWidget* m_DatasetPropertiesDock;

  /**
   * \brief Current Pixel Description dock-widget.
   */
  QDockWidget* m_PixelDescriptionDock;

  /**
   * \brief Histogram dock-widget.
   */
  QDockWidget* m_HistogramDock;


#ifdef OTB_WRAP_QT
  /**
   *  \brief OTB-applications browser dock-widget.
   */
  QDockWidget* m_OtbApplicationsBrowserDock;
#endif

#if USE_OLD_IMAGE_VIEW
  /**
   * \brief Image-view dock-widget.
   */
  GLImageWidget1* m_ImageView1;

  /**
   * \brief Quicklook-view dock-widget.
   */
  QDockWidget* m_QuicklookViewDock1;
#endif // USE_OLD_IMAGE_VIEW

#if USE_ICE_IMAGE_VIEW
  /**
   * \brief Image-view page.
   */
  ImageViewWidget* m_ImageView;

  /**
   * \brief Quicklook-view dock.
   */
  QDockWidget* m_QuicklookViewDock;

#endif

  /**
   */
  QTabWidget* m_CentralTabWidget;

  /**
   */
  StatusBarWidget* m_StatusBarWidget;

  /**
   */
  FilenameDragAndDropEventFilter* m_FilenameDragAndDropEventFilter;

  /*-[ PRIVATE SLOTS SECTION ]-----------------------------------------------*/

//
// Private slots.
private slots:
  /**
   * \brief Qt auto-connected slot which is called when 'File/Open
   * image' menu action is triggered.
   */
  void on_action_ImportImage_triggered();

  /**
   * \brief Qt auto-connected slot which is called when
   * 'File/Preferences' menu action is activated.
   */
  void on_action_Preferences_activated();

  /**
   * \brief Qt auto-connected slot which is called when zoom-in button
   * is pressed.
   */
  void on_action_ZoomIn_triggered();

  /**
   * \brief Qt auto-connected slot which is called when zoom-out button
   * is pressed.
   */
  void on_action_ZoomOut_triggered();

  /**
   * \brief Qt auto-connected slot which is called when zoom-extent button
   * is pressed.
   */
  void on_action_ZoomExtent_triggered();

  /**
   * \brief Qt auto-connected slot which is called when zoom-full button
   * is pressed.
   */
  void on_action_ZoomFull_triggered();

  /** */
  void OnUserCoordinatesEditingFinished();

  /** */
  void OnUserScaleEditingFinished();

  /**
   */
  void OnFilenameDropped( const QString& filename );

};

} // end namespace 'mvd'

/*****************************************************************************/
/* INLINE SECTION                                                            */

//
// System includes (sorted by alphabetic order)

//
// ITK includes (sorted by alphabetic order)

//
// OTB includes (sorted by alphabetic order)

//
// Monteverdi includes (sorted by alphabetic order)
#if USE_OLD_IMAGE_VIEW
#include "Gui/mvdGLImageWidget1.h"
#endif
#if USE_ICE_IMAGE_VIEW
#include "Gui/mvdImageViewWidget.h"
#endif

//
// Some constants.

namespace mvd
{

#if USE_OLD_IMAGE_VIEW

/*****************************************************************************/
inline
const GLImageWidget1*
MainWindow
::GetQuicklookView1() const
{
  return qobject_cast< const GLImageWidget1* >( m_QuicklookViewDock1->widget() );
}

/*****************************************************************************/
inline
GLImageWidget1*
MainWindow
::GetQuicklookView1()
{
  return qobject_cast< GLImageWidget1* >( m_QuicklookViewDock1->widget() );
}

#endif // USE_OLD_IMAGE_VIEW

#if USE_ICE_IMAGE_VIEW

/*****************************************************************************/
inline
const ImageViewWidget*
MainWindow
::GetQuicklookView() const
{
  return qobject_cast< const ImageViewWidget* >( m_QuicklookViewDock->widget() );
}

/*****************************************************************************/
inline
ImageViewWidget*
MainWindow
::GetQuicklookView()
{
  return qobject_cast< ImageViewWidget* >( m_QuicklookViewDock->widget() );
}

#endif // USE_ICE_IMAGE_VIEW

} // end namespace 'mvd'

#endif // __MainWindow_h
