#ifndef SELECT_BOOK_MAIN_WINDOW_H
#define SELECT_BOOK_MAIN_WINDOW_H

#include <QMainWindow>
#include "book_info.h"
#include <functional>

namespace Ui {
  class SelectBookMainWindow;
}

class SelectBookMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit SelectBookMainWindow(QWidget *parent = 0);
  ~SelectBookMainWindow();
  void RegisterBookListCallback(std::function<std::vector<BookInfo>()> func);

signals:
  void SelectBook(const QString& book_name);

private slots:
  void on_PickPushButton_clicked();

private:
  Ui::SelectBookMainWindow *ui;
  std::function<std::vector<BookInfo>()> book_list_callback_;
};

#endif // SELECT_BOOK_MAIN_WINDOW_H
