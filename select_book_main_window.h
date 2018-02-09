#ifndef SELECT_BOOK_MAIN_WINDOW_H
#define SELECT_BOOK_MAIN_WINDOW_H

#include <QMainWindow>
#include "book_info.h"

namespace Ui {
  class SelectBookMainWindow;
}

class SelectBookMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit SelectBookMainWindow(QWidget *parent = 0);
  ~SelectBookMainWindow();

signals:
  void SelectResult(const BookInfo& book);

private slots:
  void on_PickPushButton_clicked();

private:
  Ui::SelectBookMainWindow *ui;
};

#endif // SELECT_BOOK_MAIN_WINDOW_H
