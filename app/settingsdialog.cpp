#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QMutexLocker>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)

{

    ui->setupUi(this);

    presets << "Standard" << "Hero" <<  "Flames";

    initDefault();
presetChanged();

    connect(ui->sldScale, SIGNAL(valueChanged(int)), this, SLOT(settingChanged()));
    connect(ui->chkMagnitude, SIGNAL(stateChanged(int)), this, SLOT(settingChanged()));
    connect(ui->chkMovingCamera, SIGNAL(stateChanged(int)), this, SLOT(settingChanged()));
    //connect(ui->sldFloorX, SIGNAL(valueChanged(int)),this,SLOT(settingChanged()));
    connect(ui->sldStepZ,SIGNAL(valueChanged(int)), this, SLOT(settingChanged()));
    connect(ui->chkFlashlight,SIGNAL(stateChanged(int)),this, SLOT(settingChanged()));
    connect(ui->sldObjectSlices,SIGNAL(valueChanged(int)), this, SLOT(settingChanged()));


}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

int SettingsDialog::presetCount()
{
    return presets.count();
}
QString SettingsDialog::presetName(int pos)
{
    return presets.value(pos);
}
void SettingsDialog::loadPreset(int pos)
{

    cout << "NastyFFT: Loading PresetIndex: " << pos << endl;

    initDefault();

    switch (pos)
    {

        case 1: //Hero

//            priv.cam_coords.y = 4.0f;
//            priv.cam_coords.z = 15;
	    priv.scale=1;
            priv.flatten = true;
            priv.step_z = 1.3f;
            priv.shiness = 1.0;
            priv.name = "Hero";
            preset_index = 1;
            break;

        case 2:

//            priv.cam_coords.y = 4.0f;
//            priv.cam_coords.z = 15;
            priv.flatten = false;
            priv.step_z = 0.1f;
            priv.shiness = 1.0;
            priv.name = "Flames";
            preset_index = 2;
            break;
    }


}
void SettingsDialog::initDefault()
{



        priv.fdist_z=-30.0f;

        priv.light_x=(NUM_BANDS/2);
        priv.light_dir=1;


// 		preset.cam_y=1.0f;
        priv.rot_x=0.0f;
        priv.step_z=1.3f;


        priv.shiness = 0.0f;

        priv.scale=3.0f;
        priv.cinvert=false;
        priv.cammove=false;
        priv.tranzient=false;
        priv.flatten = false;

        priv.beat=0.0f;
        priv.step_x=1.15;
        priv.cam_coords.x=0;//((NUM_BANDS*priv.step_x)/2.0f)-(priv.step_x/2.0f);
        priv.cam_coords.y = 1.0f;
        priv.cam_coords.z = 24;



        priv.cam_focus.x=0;//((NUM_BANDS*priv.step_x)/2.0f)-(priv.step_x/2.0f);
        priv.cam_focus.y=0.0f;
        priv.cam_focus.z=18;
        priv.cam_dir=+1;

        priv.use_magnitude = true;

        priv.obj_slices = 16;

        priv.name = "Standard";
        preset_index = 0;

}
int SettingsDialog::presetIndex()
{
    return preset_index;

}
ScenePreset* SettingsDialog::scenePreset()
{
    return &priv;

}
void SettingsDialog::presetChanged()
{


    ui->sldScale->setValue(priv.scale);
    ui->chkMagnitude->setChecked(priv.use_magnitude);
    ui->chkMovingCamera->setChecked(priv.cammove);
    //ui->sldFloorX->setValue(priv.rot_x);
    ui->sldStepZ->setValue(priv.step_z*10.0f);
    ui->chkFlashlight->setChecked(priv.cinvert);
    ui->sldObjectSlices->setValue(priv.obj_slices);
}

void SettingsDialog::settingChanged()
{

    priv.use_magnitude = ui->chkMagnitude->isChecked();
    priv.scale = ui->sldScale->value();
    priv.cammove = ui->chkMovingCamera->isChecked();
    //priv.rot_x = ui->sldFloorX->value();
    priv.step_z = ui->sldStepZ->value()/10.0f;
    priv.cinvert = ui->chkFlashlight->isChecked();
    priv.obj_slices = ui->sldObjectSlices->value();
}
