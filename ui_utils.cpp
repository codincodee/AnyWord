#include "ui_utils.h"
#include <QMessageBox>

QString MessageBoxTitle::Warning() {
  return "Warning";
}

namespace ui {
void warn(const QString &message, QWidget *widget) {
  if (widget) {
    QMessageBox::warning(widget, "Warning", message);
  }
}

void info(const QString &message, QWidget* widget) {
  if (widget) {
    QMessageBox::information(widget, "Information", message);
  }
}
}
