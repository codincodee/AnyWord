#ifndef FACTORY_H
#define FACTORY_H

#include <memory>
#include "main_window_word_ui.h"
#include "main_window_meaning_ui.h"

class MainWindow;

class Factory
{
public:
  Factory();
  void SetMainWindow(MainWindow* win);
  bool Init();
private:
  MainWindow* qt_main_window_;
  std::shared_ptr<MainWindowWordUI> main_window_word_ui_;
  std::shared_ptr<MainWindowMeaningUI> main_window_meaning_ui_;
};

#endif // FACTORY_H
