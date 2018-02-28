#include "media_manager.h"
#include <QDebug>
#include <QUrl>
#include <QSoundEffect>

MediaManager::MediaManager()
{

}

bool MediaManager::Init() {
  q_audio_recorder_.reset(new QAudioRecorder);
  q_audio_recorder_->setOutputLocation(
      QUrl::fromLocalFile(TempAudioFilePath()));
  temp_dir_.setAutoRemove(true);
  q_sound_effect_.reset(new QSoundEffect);
  return true;
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
  return temp_dir_.path() + "/temp_audio.wav";
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
  q_sound_effect_->setSource(QUrl::fromLocalFile(""));
  q_sound_effect_->setSource(QUrl::fromLocalFile(path));
  q_sound_effect_->play();
}

void MediaManager::OnClearRecord() {
  if (q_sound_effect_->isPlaying()) {
    q_sound_effect_->stop();
  }
  QFile(TempAudioFilePath()).remove();
}

void MediaManager::OnSaveRecord(const QString &path) {
  auto real_path = path + ".wav";
  QFile::copy(TempAudioFilePath(), real_path);
  OnClearRecord();
}
