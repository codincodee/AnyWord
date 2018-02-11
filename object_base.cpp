#include "object_base.h"
#include <QMessageBox>
#include "ui_utils.h"

ObjectBase::ObjectBase()
{

}

ObjectBase::~ObjectBase() {}

void ObjectBase::SetWidget(QWidget *widget) {
  widget_ = widget;
}

void ObjectBase::warn(const QString &message) {
  ui::warn(message, widget_);
}
