#ifndef UI_BASE_H
#define UI_BASE_H

#include <QWidget>

class UIBase
{
public:
  UIBase();
  virtual ~UIBase();
  void SetQtParentWidget(QWidget* widget);
  QWidget* QtParentWidget();
private:
  QWidget* qt_parent_widget_;
};

#endif // UI_BASE_H
