#ifndef ADD_WORDS_MAIN_WINDOW_H
#define ADD_WORDS_MAIN_WINDOW_H

#include <QMainWindow>
#include <memory>

class Factory;

namespace Ui {
  class AddWordsMainWindow;
}

class AddWordsMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit AddWordsMainWindow(QWidget *parent = 0);
  ~AddWordsMainWindow();

signals:
  void WriteDatabase(std::shared_ptr<int>);

private slots:
  void on_OkPushButton_clicked();

private:
  Ui::AddWordsMainWindow *ui;
  std::shared_ptr<Factory> factory_;
};

#endif // ADD_WORDS_MAIN_WINDOW_H
