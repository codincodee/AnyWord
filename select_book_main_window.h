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
  void RegisterBookInfoCallback(
      std::function<BookInfo(const QString& name)> func);
  void RegisterCreateBookCallback(
      std::function<bool(const QString& name)> func);
signals:
  void SelectBook(const QString& book_name);

protected:
  void showEvent(QShowEvent *event);

private slots:
  void on_PickPushButton_clicked();

  void on_BookComboBox_currentTextChanged(const QString &arg1);

  void on_CreatePushButton_clicked();

private:
  void FreshBookList();

  Ui::SelectBookMainWindow *ui;
  std::function<std::vector<BookInfo>()> book_list_callback_;
  std::function<BookInfo(const QString& name)> book_info_callback_;
  std::function<bool(const QString& name)> create_book_callback_;
};

#endif // SELECT_BOOK_MAIN_WINDOW_H
