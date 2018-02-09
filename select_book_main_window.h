#ifndef SELECT_BOOK_MAIN_WINDOW_H
#define SELECT_BOOK_MAIN_WINDOW_H

#include <QMainWindow>

namespace Ui {
  class SelectBookMainWindow;
}

class SelectBookMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit SelectBookMainWindow(QWidget *parent = 0);
  ~SelectBookMainWindow();

private:
  Ui::SelectBookMainWindow *ui;
};

#endif // SELECT_BOOK_MAIN_WINDOW_H
