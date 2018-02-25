#include "main_window.h"
#include "ui_main_window.h"
#include <QDebug>
#include "ui_utils.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
}

MainWindow::~MainWindow()
{
  delete ui;
}

bool MainWindow::Init() {
  ui->setupUi(this);

  // Word Label
  auto word_label = WordLabel();
  QFont font = word_label->font();
  font.setBold(true);
  font.setPointSize(30);
  word_label->setFont(font);
  word_label->setText("Welcome");

  // Meaning Label
  auto meaning_label = MeaningLabel();
  font = meaning_label->font();
  font.setBold(true);
  font.setPointSize(20);
  meaning_label->setFont(font);
  QSizePolicy sp_retain = meaning_label->sizePolicy();
  sp_retain.setRetainSizeWhenHidden(true);
  meaning_label->setSizePolicy(sp_retain);

  // "I know" Button
  auto i_know_push_button = IKnowPushButton();
  font = i_know_push_button->font();
  font.setBold(true);
  font.setPointSize(10);
  i_know_push_button->setFont(font);
  i_know_push_button->setFocus();

  // "I Don't Know" Button
  auto i_dont_know_push_button = IDontKnowPushButton();
  font = i_dont_know_push_button->font();
  font.setBold(true);
  font.setPointSize(10);
  i_dont_know_push_button->setFont(font);

  auto pass_push_button = ui->PassPushButton;
  font = pass_push_button->font();
  font.setBold(true);
  font.setPointSize(10);
  pass_push_button->setFont(font);

  // Progress
  auto progress_bar = ProgressBar();
  progress_bar->setStyleSheet(
      "QProgressBar {"
          "border: 0px solid grey;"
          "border-radius: 0px;"
          "text-align: center;"
      "}"
      "QProgressBar::chunk {"
          "background-color: #05B8CC;"
          "width: 1px;"
      "}");
  progress_bar->setValue(0);

  // Playback
  auto play_back_push_button = PlaybackPushButton();
  sp_retain = play_back_push_button->sizePolicy();
  sp_retain.setRetainSizeWhenHidden(true);
  play_back_push_button->setSizePolicy(sp_retain);
  play_back_push_button->setVisible(true);

  QAction* action_add_words = new QAction("Add Words", this);
  connect(
      action_add_words,
      &QAction::triggered,
      this,
      &MainWindow::OnActionAddWordsTriggered);
  ui->SettingsToolButton->addAction(action_add_words);

  QAction* action_select_book = new QAction("Pick Book", this);
  connect(
      action_select_book,
      &QAction::triggered,
      this,
      &MainWindow::OnActionSelectBookTriggered);
  ui->SettingsToolButton->addAction(action_select_book);

  QAction* action_minimize_window = new QAction("Minimize", this);
  connect(
      action_minimize_window,
      &QAction::triggered,
      this,
      &MainWindow::OnActionMinimizeWindowTriggered);
  ui->SettingsToolButton->addAction(action_minimize_window);

  ui->ModifyWordToolButton->setDisabled(true);
  return true;
}

void MainWindow::RegisterGetWordCallback(std::function<WordEntry ()> func) {
  get_word_callback_ = func;
}

void MainWindow::RegisterMarkWordCallback(
    std::function<bool (const QString &, const bool &)> func) {
  mark_word_callback_ = func;
}

QLabel* MainWindow::WordLabel() {
  return ui->WordLabel;
}

QLabel* MainWindow::MeaningLabel() {
  return ui->MeaningLabel;
}

QPushButton* MainWindow::IKnowPushButton() {
  return ui->IKnowTheWordPushButton;
}

QPushButton* MainWindow::IDontKnowPushButton() {
  return ui->IDontKnowTheWordPushButton;
}

QToolButton* MainWindow::PlaybackPushButton() {
  return ui->PlaybackToolButton;
}

QProgressBar* MainWindow::ProgressBar() {
  return ui->ProgressBar;
}

void MainWindow::on_SettingsToolButton_clicked()
{
  ui->SettingsToolButton->showMenu();
}

void MainWindow::OnActionAddWordsTriggered(bool checked) {
  Q_UNUSED(checked);
  emit ShowAddWordsMainWindow();
}

void MainWindow::OnActionSelectBookTriggered(bool checked) {
  Q_UNUSED(checked);
  emit ShowSelectBookMainWindow();
}

void MainWindow::OnActionMinimizeWindowTriggered(bool checked) {
  qDebug() << "Minimizing";
}

void MainWindow::OnBookSelection(const QString &book) {
  auto text = ui->InformationLabel->text();
  ui->InformationLabel->setText("Loading book, please wait ...");
  qApp->processEvents();
  ui->InformationLabel->setText(text);
}

void MainWindow::OnCurrentBookChanged(const BookInfo &book) {
  ui->InformationLabel->setText(book.name + " (" + SupportLanguageToString(book.language) + ")");
//  if (get_word_callback_) {
//    current_word_ = get_word_callback_();
//    i_know_current_word_ = false;
//  }
  SetUIFocus(current_word_);
  current_word_.Clear();
  PassCurrentWord();
}

void MainWindow::SetUIFocus(const WordEntry &word) {
  if (word.require_spelling) {
    ui->SpellingLineEdit->setFocus();
  } else {
    ui->IKnowTheWordPushButton->setFocus();
  }
}

void MainWindow::PassCurrentWord() {
  if (mark_word_callback_ && !current_word_.Empty()) {
    mark_word_callback_(current_word_.word, i_know_current_word_);
  }
  ui->IKnowTheWordPushButton->setDisabled(false);
  ui->IDontKnowTheWordPushButton->setDisabled(false);
  ui->PassPushButton->setDisabled(true);
  if (get_word_callback_) {
    current_word_ = get_word_callback_();
    i_know_current_word_ = false;
  }
  if (current_word_.Empty()) {
    ui::info("No word pending", this);
  } else {
    ui->WordLabel->clear();
    ui->MeaningLabel->clear();
    ui->NoteTextEdit->clear();
    ui->WordLabel->setText(current_word_.word);
    SetUIFocus(current_word_);
  }
}

void MainWindow::DisplayWordMeaning(const WordEntry& word, const bool &know) {
  if (know) {
    ui->MeaningLabel->setStyleSheet(QStringLiteral("QLabel{color: green}"));
  } else {
    ui->MeaningLabel->setStyleSheet(QStringLiteral("QLabel{color: red}"));
  }
  ui->MeaningLabel->setText(word.meaning);
}

void MainWindow::DisplayWordNote(const WordEntry& word) {
  if (word.Empty()) {
    ui->NoteTextEdit->clear();
    return;
  }
  auto note =
      word.note +
      "\nhit: " + QString::number(word.hit) +
      "\nhit_ts: " + current_word_.hit_ts +
      "\nmiss: " + QString::number(word.miss) +
      "\nmiss_ts: " + current_word_.miss_ts;
  ui->NoteTextEdit->setText(note);
}

void MainWindow::on_IKnowTheWordPushButton_clicked()
{
  ui->IKnowTheWordPushButton->setDisabled(true);
  ui->PassPushButton->setDisabled(false);
  i_know_current_word_ = true;
  DisplayWordMeaning(current_word_, i_know_current_word_);
  DisplayWordNote(current_word_);
}

void MainWindow::on_IDontKnowTheWordPushButton_clicked()
{
  ui->IKnowTheWordPushButton->setDisabled(true);
  ui->IDontKnowTheWordPushButton->setDisabled(true);
  ui->PassPushButton->setDisabled(false);
  i_know_current_word_ = false;
  DisplayWordMeaning(current_word_, i_know_current_word_);
  DisplayWordNote(current_word_);
}

void MainWindow::on_PassPushButton_clicked()
{
  PassCurrentWord();
}
