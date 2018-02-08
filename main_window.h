#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <memory>
#include <QProgressBar>
#include <QToolButton>
#include <QLabel>
#include <QPushButton>
#include "add_words_main_window.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  bool Init();

protected:
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
  AddWordsMainWindow* add_words_main_window_;
};

#endif // MAIN_WINDOW_H
