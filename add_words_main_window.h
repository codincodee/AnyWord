#ifndef ADD_WORDS_MAIN_WINDOW_H
#define ADD_WORDS_MAIN_WINDOW_H

#include <QMainWindow>
#include <memory>
#include "word_entry.h"

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
  void SearchDatabase(WordEntry& entry);
  void WriteDatabase(std::shared_ptr<int>);

protected:
  void DisableWidgets(std::vector<QWidget*>& widgets, const bool& disable);

private slots:
  void on_OkPushButton_clicked();

  void on_WordLineEdit_editingFinished();

private:
  Ui::AddWordsMainWindow *ui;
  std::shared_ptr<Factory> factory_;
  std::vector<QWidget*> all_widgets_;
};

#endif // ADD_WORDS_MAIN_WINDOW_H
