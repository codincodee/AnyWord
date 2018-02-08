#ifndef FACTORY_H
#define FACTORY_H

#include <vector>
#include <QObject>

class Factory : public QObject
{
public:
  Factory();
  ~Factory();
private:
  std::vector<QObject*> recycle_objects_;
};

#endif // FACTORY_H
