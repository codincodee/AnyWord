#ifndef MINIMIZED_MAIN_WINDOW_H
#define MINIMIZED_MAIN_WINDOW_H

#include <QWidget>

namespace Ui {
  class MinimizedMainWindow;
}

class MinimizedMainWindow : public QWidget
{
  Q_OBJECT

public:
  explicit MinimizedMainWindow(QWidget *parent = 0);
  ~MinimizedMainWindow();

public slots:
  void OnSwitchWindow();

protected:
  void mousePressEvent(QMouseEvent *event);

private:
  void SetAllWidgetsVisible(const bool& visable);

  std::vector<QWidget*> widgets_;
  Ui::MinimizedMainWindow *ui;
};

#endif // MINIMIZED_MAIN_WINDOW_H
