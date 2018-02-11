#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <memory>
#include <QProgressBar>
#include <QToolButton>
#include <QLabel>
#include <QPushButton>
#include "add_words_main_window.h"
#include "book_info.h"

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

signals:
  void ShowAddWordsMainWindow();
  void ShowSelectBookMainWindow();

private slots:
  void on_SettingsToolButton_clicked();

  void OnActionAddWordsTriggered(bool checked);
  void OnActionSelectBookTriggered(bool checked);

  void OnBookSelection(const BookInfo& book);
private:
  Ui::MainWindow *ui;
  AddWordsMainWindow* add_words_main_window_;
};

#endif // MAIN_WINDOW_H
