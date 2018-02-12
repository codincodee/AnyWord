#include "support_language.h"

QString SupportLanguageToString(const SupportLanguage& language) {
  switch (language) {
  case SupportLanguage::English: return "English"; break;
  case SupportLanguage::Korean: return "한국어"; break;
  default: return "Undefined";
  }
}

SupportLanguage StringToSupportLanguage(const QString& string) {
  if (string == SupportLanguageToString(SupportLanguage::English)) {
    return SupportLanguage::English;
  } else if (string == SupportLanguageToString(SupportLanguage::Korean)) {
    return SupportLanguage::Korean;
  } else {
    return SupportLanguage::Undefined;
  }
}

QStringList AllSupportingLanguagesString() {
  QStringList list;
  list.push_back(SupportLanguageToString(SupportLanguage::English));
  list.push_back(SupportLanguageToString(SupportLanguage::Korean));
  return list;
}
