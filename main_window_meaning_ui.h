#ifndef MAIN_WINDOW_MEANING_UI_H
#define MAIN_WINDOW_MEANING_UI_H

#include <QLabel>

class MainWindowMeaningUI
{
public:
  MainWindowMeaningUI();
  void SetQtLabel(QLabel* label);
  bool SetDefault();
private:
  QLabel* qt_label_;
};

#endif // MAIN_WINDOW_MEANING_UI_H
