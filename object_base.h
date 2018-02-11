#ifndef OBJECT_BASE_H
#define OBJECT_BASE_H

#include <QObject>

class ObjectBase : public QObject
{
  Q_OBJECT
public:
  ObjectBase();
  virtual ~ObjectBase();
  void SetWidget(QWidget* widget);
  void warn(const QString& message);
private:
  QWidget* widget_ = nullptr;
};

#endif // OBJECT_BASE_H
