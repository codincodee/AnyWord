#ifndef UI_UTILS_H
#define UI_UTILS_H

#include <QString>
#include "object_base.h"

struct MessageBoxTitle {
  static QString Warning();
};

namespace ui {
void warn(const QString &message, QWidget* widget);
void info(const QString &message, QWidget* widget);
}

#endif // UI_UTILS_H
