#include "add_words_main_window.h"
#include "ui_add_words_main_window.h"

AddWordsMainWindow::AddWordsMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::AddWordsMainWindow)
{
  ui->setupUi(this);
  this->setWindowModality(Qt::WindowModal);
  ui->DeletePushButton->setVisible(true);
}

AddWordsMainWindow::~AddWordsMainWindow()
{
  delete ui;
}

void AddWordsMainWindow::on_OkPushButton_clicked()
{

}
