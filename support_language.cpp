#include "support_language.h"

QString SupportLanguageToString(const SupportLanguage& language) {
  switch (language) {
  case SupportLanguage::English: return "English"; break;
  case SupportLanguage::Korean: return "한국어"; break;
  default: return "Undefined";
  }
}
