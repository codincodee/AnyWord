#include "media_manager.h"
#include <QDebug>
#include <QUrl>
#include <QSoundEffect>

MediaManager::MediaManager()
{

}

bool MediaManager::Init() {
  q_audio_recorder_.reset(new QAudioRecorder);
  QAudioEncoderSettings settings;

  // TODO: On Windows, a suffix ".wav" is automatically
  // added to the output audio file, which may cause compatibility issues.
  settings.setCodec("audio/amr");
  settings.setQuality(QMultimedia::HighQuality);

  q_audio_recorder_->setAudioSettings(settings);
  q_audio_recorder_->setOutputLocation(
      QUrl::fromLocalFile(TempAudioFilePath()));
  temp_dir_.setAutoRemove(true);
  q_sound_effect_.reset(new QSoundEffect);
  return true;
}

bool MediaManager::HasRecord() {
  return QFile(TempAudioFilePath()).exists();
}

void MediaManager::OnStartRecord() {
  auto devices = q_audio_recorder_->audioInputs();
  if (devices.isEmpty()) {
    return;
  }
  q_audio_recorder_->setAudioInput(devices[0]);
  q_audio_recorder_->record();
}

void MediaManager::OnStopRecord() {
  q_audio_recorder_->stop();
}

QString MediaManager::TempAudioFilePath() {
  return temp_dir_.path() + "/temp_audio" + AudioFileSuffix();
}

void MediaManager::OnPlayRecord() {
  if (q_sound_effect_->isPlaying()) {
    q_sound_effect_->stop();
  }
  auto file = TempAudioFilePath();
  if (!QFile(file).exists()) {
    return;
  }
  q_sound_effect_->setSource(QUrl::fromLocalFile(""));
  q_sound_effect_->setSource(QUrl::fromLocalFile(file));
  q_sound_effect_->play();
}

void MediaManager::OnPlayRecord(const QString& path) {
  if (q_sound_effect_->isPlaying()) {
    q_sound_effect_->stop();
  }
  auto file = path + AudioFileSuffix();
  if (!QFile(file).exists()) {
    return;
  }
  q_sound_effect_->setSource(QUrl::fromLocalFile(""));
  q_sound_effect_->setSource(QUrl::fromLocalFile(file));
  q_sound_effect_->play();
}

void MediaManager::OnClearRecord() {
  if (q_sound_effect_->isPlaying()) {
    q_sound_effect_->stop();
  }
  QFile(TempAudioFilePath()).remove();
}

void MediaManager::OnLoadRecord(const QString &path) {
  if (q_sound_effect_->isPlaying()) {
    q_sound_effect_->stop();
  }
  auto real_path = path + AudioFileSuffix();
  QFile::copy(real_path, TempAudioFilePath());
}

void MediaManager::OnDeleteRecord(const QString &path) {
  if (q_sound_effect_->isPlaying()) {
    q_sound_effect_->stop();
  }
  auto real_path = path + AudioFileSuffix();
  QFile(real_path).remove();
}

void MediaManager::OnSaveRecord(const QString &path) {
  auto real_path = path + AudioFileSuffix();
  QFile(real_path).remove();
  if (!QFile::copy(TempAudioFilePath(), real_path)) {
    qDebug() << "Fail to copy audio record";
  }
  OnClearRecord();
}
