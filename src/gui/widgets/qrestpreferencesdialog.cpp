#include "qrestpreferencesdialog.h"

#include "../../settings/settings.h"

////////////////////////////////////////////////////////////////////////////////
//
// INIT
//
////////////////////////////////////////////////////////////////////////////////
QrestPreferencesDialog::QrestPreferencesDialog(QWidget *parent) :
    QDialog(parent) {
    ui.setupUi(this);

    ui.chkRememberWindowPos->setChecked(
            Settings::getInstance()->getSettings() .value(
                    Settings::REMEMBER_WINDOW_POSITION,
                    Settings::REMEMBER_WINDOW_POSITION_DEFAULT).toBool());

    // we don't want the "what's this" button on this dialog
    this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

QrestPreferencesDialog::~QrestPreferencesDialog() {

}

////////////////////////////////////////////////////////////////////////////////
//
// SLOTS
//
////////////////////////////////////////////////////////////////////////////////
void QrestPreferencesDialog::accept() {

    Settings::getInstance()->getSettings() .setValue(
            Settings::REMEMBER_WINDOW_POSITION,
            ui.chkRememberWindowPos->isChecked());

    Settings::getInstance()->getSettings().sync();

    QDialog::accept();
}
