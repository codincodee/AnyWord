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
  void RegisterMarkWordCallback(
      std::function<bool(const QString& word, const bool& know)> func);
protected:
  QLabel* WordLabel();
  QLabel* MeaningLabel();
  QPushButton* IKnowPushButton();
  QPushButton* IDontKnowPushButton();
  QProgressBar* ProgressBar();
  QToolButton* PlaybackPushButton();
  void closeEvent(QCloseEvent* event);

signals:
  void ShowAddWordsMainWindow();
  void ShowSelectBookMainWindow();
  void MarkWord(const QString& word, const bool& know);
  bool Destroyed();
  void SwitchMiniWindowOnOff();
  void DisplayWordMeaningSignal(const WordEntry &word, const bool &know);
  void DisplayWordSignal(const WordEntry& word);
  void PlayRecord(const QString& word);

private slots:
  void on_SettingsToolButton_clicked();

  void OnActionAddWordsTriggered(bool checked);
  void OnActionSelectBookTriggered(bool checked);
  void OnActionMinimizeWindowTriggered(bool checked);

  void OnBookSelection(const QString& book);
  void OnCurrentBookChanged(const BookInfo& book);
  void on_IKnowTheWordPushButton_clicked();

  void on_IDontKnowTheWordPushButton_clicked();

  void on_PassPushButton_clicked();

  void on_PlaybackToolButton_clicked();

private:
  void DisplayWordMeaning(const WordEntry& word, const bool& know);
  void DisplayWordNote(const WordEntry& word);
  void SetUIFocus(const WordEntry& word);
  void PassCurrentWord();

  Ui::MainWindow *ui;
  AddWordsMainWindow* add_words_main_window_;

  std::function<WordEntry()> get_word_callback_;
  std::function<bool(const QString& word, const bool& know)> mark_word_callback_;
  WordEntry current_word_;
  bool i_know_current_word_;
};

#endif // MAIN_WINDOW_H
