#include "qrestpreferencesdialog.h"

#include "../../settings/settings.h"
#include "../../helpers/widgetsizehelper.h"

////////////////////////////////////////////////////////////////////////////////
//
// INIT
//
////////////////////////////////////////////////////////////////////////////////
QrestPreferencesDialog::QrestPreferencesDialog(QWidget *parent)
: QDialog(parent) {

    ui.setupUi(this);

#ifdef Q_WS_MAC
    // set default font sizes
    WidgetSizeHelper::setDefaultFontSize( this );
#endif

    // update the 'remember window position' checkbox state according to saved prefs
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

    Settings::getInstance()->getSettings()
                    .setValue(Settings::REMEMBER_WINDOW_POSITION,
                              ui.chkRememberWindowPos->isChecked());

    Settings::getInstance()->getSettings().sync();

    QDialog::accept();
}
