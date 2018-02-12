#ifndef SUPPORT_LANGUAGE_H
#define SUPPORT_LANGUAGE_H

#include <QString>

enum class SupportLanguage {
  English, Korean, Undefined
};

QString SupportLanguageToString(const SupportLanguage& language);

#endif // SUPPORT_LANGUAGE_H
