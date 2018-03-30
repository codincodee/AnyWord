#ifndef EDIT_BOOK_WINDOW_H
#define EDIT_BOOK_WINDOW_H

#include <QMainWindow>

namespace Ui {
  class EditBookWindow;
}

class EditBookWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit EditBookWindow(QWidget *parent = 0);
  ~EditBookWindow();

public slots:
  void OnEditBook(const QString& book_name);

private:
  Ui::EditBookWindow *ui;
};

#endif // EDIT_BOOK_WINDOW_H
