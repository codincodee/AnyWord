#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <memory>
#include <QProgressBar>
#include <QToolButton>
#include <QLabel>
#include <QPushButton>

class Factory;

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void SetFactory(std::shared_ptr<Factory> factory);

  QLabel* WordLabel();
  QLabel* MeaningLabel();
  QPushButton* IKnowPushButton();
  QPushButton* IDontKnowPushButton();
  QProgressBar* ProgressBar();
  QToolButton* PlaybackPushButton();
private slots:
  void on_SettingsToolButton_clicked();

  void OnActionAddWordsTriggered(bool checked);
private:
  Ui::MainWindow *ui;
  std::shared_ptr<Factory> factory_;
};

#endif // MAIN_WINDOW_H
