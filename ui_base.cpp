#include "ui_base.h"

UIBase::UIBase()
{

}

UIBase::~UIBase() {}

void UIBase::SetQtParentWidget(QWidget *widget) {
  qt_parent_widget_ = widget;
}

QWidget* UIBase::QtParentWidget() {
  return qt_parent_widget_;
}
