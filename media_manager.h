#ifndef MEDIA_MANAGER_H
#define MEDIA_MANAGER_H

#include <QObject>
#include <memory>
#include <QAudioRecorder>
#include <QTemporaryDir>
#include <QSoundEffect>

class MediaManager : public QObject
{
  Q_OBJECT
public:
  MediaManager();
  bool Init();
  bool HasRecord();
  inline static QString AudioFileSuffix() {
    return ".wav";
  }
public slots:
  void OnStartRecord();
  void OnStopRecord();
  void OnPlayRecord();
  void OnPlayRecord(const QString& path);
  void OnSaveRecord(const QString& path);
  void OnClearRecord();
  void OnLoadRecord(const QString& path);
  void OnDeleteRecord(const QString& path);

private:
  QString TempAudioFilePath();
  std::unique_ptr<QAudioRecorder> q_audio_recorder_;
  std::unique_ptr<QSoundEffect> q_sound_effect_;
  QTemporaryDir temp_dir_;
};

#endif // MEDIA_MANAGER_H
