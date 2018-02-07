#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "add_words_main_window.h"
#include <memory>
#include "factory.h"

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
private slots:
  void on_SettingsToolButton_clicked();

  void OnActionAddWordsTriggered(bool checked);
private:
  Ui::MainWindow *ui;
  AddWordsMainWindow* add_words_main_window_;
  std::shared_ptr<Factory> factory_;
};

#endif // MAIN_WINDOW_H
