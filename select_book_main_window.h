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
      std::function<bool(const BookInfo& info)> func);
  void RegisterDeleteBookCallback(
      std::function<bool(const QString& name)> func);
signals:
  void SelectBook(const QString& book_name);
  void EditBook(const QString& book_name);

protected:
  void showEvent(QShowEvent *event);

private slots:
  void on_PickPushButton_clicked();

  void on_BookComboBox_currentTextChanged(const QString &arg1);

  void on_CreatePushButton_clicked();

  void on_DeletePushButton_clicked();

  void on_EditBookPushButton_clicked();

private:
  void RefreshBookList();

  Ui::SelectBookMainWindow *ui;
  std::function<std::vector<BookInfo>()> book_list_callback_;
  std::function<BookInfo(const QString& name)> book_info_callback_;
  std::function<bool(const BookInfo& info)> create_book_callback_;
  std::function<bool (const QString & name)> delete_book_callback_;
};

#endif // SELECT_BOOK_MAIN_WINDOW_H
