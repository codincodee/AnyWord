#include "main_window.h"
#include "ui_main_window.h"

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
}

MainWindow::~MainWindow()
{
  delete ui;
}
