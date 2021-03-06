#ifndef MINIMIZED_MAIN_WINDOW_H
#define MINIMIZED_MAIN_WINDOW_H

#include <QWidget>
#include "word_entry.h"

namespace Ui {
  class MinimizedMainWindow;
}

class MinimizedMainWindow : public QWidget
{
  Q_OBJECT

public:
  explicit MinimizedMainWindow(QWidget *parent = 0);
  ~MinimizedMainWindow();

signals:
  void CheckPushButtonClicked();
  void PassPushButtonClicked();
  void CrossPushButtonClicked();
  void IDontKnowPreviousWord();

public slots:
  void OnSwitchWindow();
  void OnDisplayWord(const WordEntry& word);
  void OnDisplayWordMeaning(const WordEntry& word, const bool& know);
  void OnShowHideSwitch();
  void OnIDontKnowPreviousWord();
  void OnWordResetCallback(const WordEntry& entry);

protected:
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent* event);

private slots:
  void on_PassPushButton_clicked();

  void on_CheckPushButton_clicked();

  void on_CrossPushButton_clicked();

private:
  void SetAllWidgetsVisible(const bool& visable);

  std::vector<QWidget*> widgets_;
  Ui::MinimizedMainWindow *ui;
};

#endif // MINIMIZED_MAIN_WINDOW_H
