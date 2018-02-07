#include "main_window_meaning_ui.h"

MainWindowMeaningUI::MainWindowMeaningUI()
{

}

void MainWindowMeaningUI::SetQtLabel(QLabel *label) {
  qt_label_ = label;
}

bool MainWindowMeaningUI::SetDefault() {
  if (!qt_label_) {
    return false;
  }
  QFont font = qt_label_->font();
  font.setBold(true);
  font.setPointSize(20);
  qt_label_->setFont(font);
  qt_label_->setText("Meaning");
  return true;
}
