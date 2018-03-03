#ifndef MINIMIZED_MAIN_WINDOW_H
#define MINIMIZED_MAIN_WINDOW_H

#include <QMainWindow>

namespace Ui {
  class MinimizedMainWindow;
}

class MinimizedMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MinimizedMainWindow(QWidget *parent = 0);
  ~MinimizedMainWindow();

private:
  Ui::MinimizedMainWindow *ui;
};

#endif // MINIMIZED_MAIN_WINDOW_H
