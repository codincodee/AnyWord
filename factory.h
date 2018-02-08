#ifndef FACTORY_H
#define FACTORY_H

#include <memory>
#include "main_window_ui_control.h"
#include "main_window.h"
#include "add_words_main_window.h"

class Factory
{
public:
  Factory();
  void SetMainWindow(MainWindow* win);
  bool Init();
  AddWordsMainWindow* GetAddWordsMainWindow();
private:
  MainWindow* qt_main_window_ = nullptr;
  std::shared_ptr<MainWindowUIControl> main_window_ui_control_;
  AddWordsMainWindow* add_words_main_window_;
};

#endif // FACTORY_H
