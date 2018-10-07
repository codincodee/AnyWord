#ifndef BOOK_H
#define BOOK_H

#include <QObject>
#include "book_info.h"
#include "vocabulary.h"
#include <memory>
#include "object_base.h"

class Book : public ObjectBase
{
  Q_OBJECT
public:
  Book();
  bool Init();
  BookInfo GetBookInfo();
  static BookInfo Check(const QString& path);
  static bool Create(const QString& path, const BookInfo& info);
  void Clone(const Book& obj);
  bool Load(const QString &path);
  Vocabulary& GetVocabulary();
  bool WriteEntry(const WordEntry& entry);
  static bool Delete(const QString& path);
  bool MarkWord(const QString& word, const bool& know);
  bool MarkWord(const QString& word, const MarkWordOperation& operation);
  bool ResetWord(const QString& word);
  WordEntry LookUp(const QString& word);
  bool GetBookProgress(int& memorized, int& total);
signals:
  void SaveRecord(const QString& path);
  void PlayRecord(const QString& path);
  void LoadRecord(const QString& path);
  void DeleteRecord(const QString& path);

public slots:
  void OnChange(std::shared_ptr<Book> new_book);
  void OnPlayRecord(const QString& word);
  void OnSaveRecord(const QString& word);
  void OnLoadRecord(const QString& word);
  void OnDeleteRecord(const QString& word);

  void OnDeleteEntry(const QString& word);

  void OnCloseSignal();
private:
  QString LoadVolume(const QString& path);
  bool BuildVolume(const QString& book_path, const QString& volumes_path);
  std::shared_ptr<Vocabulary> vocabulary_;
  BookInfo information_;
  QString path_;
  const QString kVolumeFolderName;
};

#endif // BOOK_H
