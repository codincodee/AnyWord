#include "object_base.h"
#include <QMessageBox>

ObjectBase::ObjectBase()
{

}

ObjectBase::~ObjectBase() {}

void ObjectBase::SetWidget(QWidget *widget) {
  widget_ = widget;
}

void ObjectBase::ShowWarning(const QString &message) {
  if (widget_) {
    QMessageBox::warning(widget_, "Warning", message);
  }
}
