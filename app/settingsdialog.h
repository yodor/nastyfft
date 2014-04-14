#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QMutex>

#include "scenepreset.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
    
    int presetCount();

    QString presetName(int pos);

    void loadPreset(int pos);
    void initDefault();

    int presetIndex();

    ScenePreset* scenePreset();

public slots:
    void presetChanged();

private:
    Ui::SettingsDialog *ui;

    ScenePreset priv;
    int preset_index;
    QStringList presets;


private slots:

    void settingChanged();
};

#endif // SETTINGSDIALOG_H
