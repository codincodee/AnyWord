#ifndef FACTORY_H
#define FACTORY_H

#include <vector>
#include <QObject>

class Factory : public QObject
{
public:
  Factory();
  bool Construct();
  ~Factory();
private:
  std::vector<QObject*> recycle_objects_;
  std::vector<QWidget*> recycle_widgets_;
};

#endif // FACTORY_H
