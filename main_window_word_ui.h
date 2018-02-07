#ifndef MAIN_WINDOW_WORD_UI_H
#define MAIN_WINDOW_WORD_UI_H

#include <QLabel>

class MainWindowWordUI
{
public:
  MainWindowWordUI();
  void SetQtLabel(QLabel* label);
  bool SetDefault();
private:
  QLabel* qt_label_;
};

#endif // MAIN_WINDOW_WORD_UI_H
