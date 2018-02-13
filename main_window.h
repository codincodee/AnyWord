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
#include <functional>

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
  void RegisterGetWordCallback(std::function<WordEntry()> func);
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

  void OnBookSelection(const QString& book);
  void OnCurrentBookChanged(const BookInfo& book);
  void on_IKnowTheWordPushButton_clicked();

  void on_IDontKnowTheWordPushButton_clicked();

  void on_PassPushButton_clicked();

private:
  void ChangeWordUI(const WordEntry& word);
  Ui::MainWindow *ui;
  AddWordsMainWindow* add_words_main_window_;

  std::function<WordEntry()> get_word_callback_;
};

#endif // MAIN_WINDOW_H
