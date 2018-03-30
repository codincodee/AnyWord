#include "edit_book_window.h"
#include "ui_edit_book_window.h"
#include <QDebug>

EditBookWindow::EditBookWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::EditBookWindow)
{
  ui->setupUi(this);
  QListWidgetItem* item = new QListWidgetItem;
  item->setText("C");
  item->setCheckState(Qt::Checked);
  ui->listWidget->addItem(item);
  item = new QListWidgetItem;
  item->setText("D");
  item->setCheckState(Qt::Unchecked);
  ui->listWidget->addItem(item);
  item = new QListWidgetItem;
  item->setText("E");
  item->setCheckState(Qt::Unchecked);
  ui->listWidget->addItem(item);
  item = new QListWidgetItem;
  item->setText("F");
  item->setCheckState(Qt::Unchecked);
  ui->listWidget->addItem(item);
}

EditBookWindow::~EditBookWindow()
{
  delete ui;
}

void EditBookWindow::OnEditBook(const QString &book_name) {
  this->show();
}
