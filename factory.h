#ifndef FACTORY_H
#define FACTORY_H

#include <vector>
#include <QObject>

class Factory
{
public:
  Factory();
  ~Factory();
private:
  std::vector<QObject*> objects_;
};

#endif // FACTORY_H
