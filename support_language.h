#ifndef SUPPORT_LANGUAGE_H
#define SUPPORT_LANGUAGE_H

#include <QString>
#include <QStringList>

enum class SupportLanguage {
  English, Korean, Undefined
};

QString SupportLanguageToString(const SupportLanguage& language);

SupportLanguage StringToSupportLanguage(const QString& string);

QStringList AllSupportingLanguagesString();

#endif // SUPPORT_LANGUAGE_H
