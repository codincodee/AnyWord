#include "main_window.h"
#include "ui_main_window.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  QFont font = ui->WordLabel->font();
  font.setBold(true);
  font.setPointSize(30);
  ui->WordLabel->setFont(font);

  font = ui->IKnowTheWordPushButton->font();
  font.setBold(true);
  font.setPointSize(10);
  ui->IKnowTheWordPushButton->setFont(font);

  font = ui->IDontKnowTheWordPushButton->font();
  font.setBold(true);
  font.setPointSize(10);
  ui->IDontKnowTheWordPushButton->setFont(font);

  // ui->MeaningLabel->setText("");
  font = ui->MeaningLabel->font();
  font.setBold(true);
  font.setPointSize(20);
  ui->MeaningLabel->setFont(font);

  ui->IKnowTheWordPushButton->setFocus();

  ui->ProgressBar->setStyleSheet(
      "QProgressBar {"
          "border: 0px solid grey;"
          "border-radius: 0px;"
          "text-align: center;"
      "}"
      "QProgressBar::chunk {"
          "background-color: #05B8CC;"
          "width: 1px;"
      "}");
  ui->ProgressBar->setValue(50);

  QAction* action_add_words = new QAction("Add Words", this);
  connect(action_add_words, &QAction::triggered, this, &MainWindow::OnActionAddWordsTriggered);
  ui->SettingsToolButton->addAction(action_add_words);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_SettingsToolButton_clicked()
{
  ui->SettingsToolButton->showMenu();
}

void MainWindow::OnActionAddWordsTriggered(bool checked) {
  qDebug() << __LINE__;
}
