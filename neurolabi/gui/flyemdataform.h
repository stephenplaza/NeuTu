#ifndef FLYEMDATAFORM_H
#define FLYEMDATAFORM_H

#include <QWidget>
#include <QProgressBar>
#include <QImage>

#include "flyem/zflyemneuronlistmodel.h"
#include "zprogressable.h"
#include "zqtbarprogressreporter.h"

class ZFlyEmNeuronPresenter;
class QStatusBar;
class QMenu;
class ZFlyEmDataFrame;
class ZFlyEmQueryView;
class ZImageWidget;

namespace Ui {
class FlyEmDataForm;
}

class FlyEmDataForm : public QWidget, ZProgressable
{
  Q_OBJECT
  
public:
  explicit FlyEmDataForm(QWidget *parent = 0);
  ~FlyEmDataForm();
  
  virtual QSize sizeHint() const;

  void appendOutput(const QString &text);
  void setQueryOutput(const ZFlyEmNeuron *neuron);
  void appendQueryOutput(const ZFlyEmNeuron *neuron);

  QProgressBar* getProgressBar();

  void setPresenter(ZFlyEmNeuronPresenter *presenter);

  inline void setStatusBar(QStatusBar *bar) { m_statusBar = bar; }

  ZFlyEmDataFrame* getParentFrame() const;

  /*!
   * \brief Create all context menus
   */
  void createContextMenu();

  /*!
   * \brief Create all actions
   */
  void createAction();

  /*!
   * \brief Update the view of query table
   */
  void updateQueryTable();

  void updateSlaveQueryTable();

signals:
  void showSummaryTriggered();
  void processTriggered();
  void queryTriggered();
  void testTriggered();
  void generalTriggered();
  void optionTriggered();
  void volumeTriggered(const QString&);
  void saveBundleTriggered(int, const QString&);
  void showNearbyNeuronTriggered(const ZFlyEmNeuron *neuron);

private slots:
  void on_pushButton_clicked();

  void on_processPushButton_clicked();

  void on_queryPushButton_clicked();

  void on_testPushButton_clicked();

  void on_generalPushButton_clicked();

  void on_optionPushButton_clicked();

  void on_addDataPushButton_clicked();

  void on_savePushButton_clicked();

  void updateStatusBar(const QModelIndex &index);
  void updateInfoWindow(const QModelIndex &index);
  void viewModel(const QModelIndex &index);
  void showSelectedModel();
  void showNearbyNeuron();
  void updateSlaveQuery(const QModelIndex &index);
  void showSecondarySelectedModel();

  /*!
   * \brief Change class of selected neurons
   *
   * Only the selected neuron keys are taken as input
   */
  void changeNeuronClass();

  /*!
   * \brief Assign class to a neuron
   *
   * The function only work on the primary neuron.
   *
   * \param index Model index.
   */
  void assignClass(const QModelIndex &index);

  void on_showModelPushButton_clicked();

  void on_saveSwcPushButton_clicked();

  void on_exportPushButton_clicked();

private:
  void showViewSelectedModel(ZFlyEmQueryView *view);

private:
  Ui::FlyEmDataForm *ui;
  ZFlyEmNeuronListModel *m_neuronList;
  ZFlyEmNeuronListModel *m_secondaryNeuronList;
  QStatusBar *m_statusBar;

  QMenu *m_neuronContextMenu;
  QAction *m_showSelectedModelAction;
  QAction *m_changeClassAction;
  QAction *m_neighborSearchAction;

  QMenu *m_secondaryNeuronContextMenu;
  QAction *m_showSecondarySelectedModelAction;

  ZQtBarProgressReporter m_specialProgressReporter;

  QImage *m_thumbnailImage;
  ZImageWidget *m_thumbnailWidget;
};

#endif // FLYEMDATAFORM_H
