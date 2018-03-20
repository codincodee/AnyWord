#ifndef FACTORY_H
#define FACTORY_H

#include <vector>
#include <QObject>
#include "bookshelf.h"

class Factory : public QObject
{
public:
  Factory();
  bool Construct();
  ~Factory();
private:
  QString ini_file_path_ = "settings.ini";
  std::vector<QObject*> recycle_objects_;
  std::vector<QWidget*> recycle_widgets_;
};

#endif // FACTORY_H
