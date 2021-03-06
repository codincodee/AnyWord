#ifndef ADD_WORDS_MAIN_WINDOW_H
#define ADD_WORDS_MAIN_WINDOW_H

#include <QMainWindow>
#include <memory>
#include "word_entry.h"
#include <functional>

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
  void RegisterSearchBookCallback(
      std::function<WordEntry(const WordEntry&)> func);
  void RegisterWriteEntryCallback(
      std::function<bool(const WordEntry&)> func);
  void RegisterRecordExistsCallback(
      std::function<bool()> func);
  void RegisterBookInfoCallback(
      std::function<BookInfo()> func);
signals:
  void SearchBook(WordEntry& entry);
  // void WriteDatabase(const WordEntry& entry);
  void DeleteEntry(const QString& word);
  void StartRecord();
  void StopRecord();
  void PlayRecord();
  void ClearRecord();
  void DeleteRecord(const QString& word);
  void SaveRecord(const QString& word);
  void LoadRecord(const QString& word);
  void CloseBook();
  void SelectBook(const QString& book);

protected:
  void DisableWidgets(std::vector<QWidget*>& widgets, const bool& disable);
  void hideEvent(QHideEvent *event);

private slots:
  void on_OkPushButton_clicked();

  void on_WordLineEdit_editingFinished();

  void on_RecordRadioButton_clicked(bool checked);

  void on_PlayToolButton_clicked();

  void OnRecordRadioButtonClicked();

  void on_MeaningLineEdit_editingFinished();

  void on_DeletePushButton_clicked();

  void OnLoadEntry(const QString& word);

  void OnShow();
private:
  Ui::AddWordsMainWindow *ui;
  std::shared_ptr<Factory> factory_;
  std::vector<QWidget*> all_widgets_;
  std::function<WordEntry(const WordEntry&)> search_book_callback_;
  std::function<bool(const WordEntry&)> write_entry_callback_;
  std::function<BookInfo ()> book_info_callback_;
  std::function<bool()> record_exists_callback_;
};

#endif // ADD_WORDS_MAIN_WINDOW_H
