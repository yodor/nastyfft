#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glview.h"


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <pulse/simple.h>
#include <pulse/error.h>

#include "spectrumanalyser.h"
#include "pulseaudiomonitor.h"


#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent, Qt::Window),
    ui(new Ui::MainWindow),
    dialog(0)
{
    ui->setupUi(this);

    //setAttribute(Qt::WA_TranslucentBackground,true);


    //QMenu *menu_presets = new QMenu(this);



    //ui->actionPresets->setMenu(menu_presets);


    dialog = new SettingsDialog(this);

    int num_presets =  dialog->presetCount();
    for (int a=0;a<num_presets;a++) {
        QAction *act = new QAction(this);
        act->setText(dialog->presetName(a));
        act->setData(QVariant(a));

        connect(act, SIGNAL(triggered()), this, SLOT(changePreset()));

        ui->menuBar->addAction(act);
        //menu_presets->addAction(act);

    }

    QAction *unlock = new QAction(this);
    unlock->setText("Lock");
    connect(unlock, SIGNAL(triggered()), this, SLOT(toggleLock()));

    connect(ui->actionSettings, SIGNAL(triggered()), this, SLOT(showSettings()));
     ui->menuBar->addAction(unlock);

//    connect(plugin, SIGNAL(presetChanged()), dialog, SLOT(presetChanged()));

    plugin = new NastyFFT(dialog->scenePreset());
    plugin->setParent(ui->centralWidget);
    connect(plugin, SIGNAL(needUnlock()), this, SLOT(toggleLock()) );




    Qt::WindowFlags f1 = this->windowFlags();


    cout << "CTR WindowFlags: " << f1 << endl;
    this->ctor_wflags = f1;
    this->resize(640,450);

    setWindowTitle("NastyFFT");
}

MainWindow::~MainWindow()
{
    delete plugin;

    delete dialog;

    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    QSize size = ui->centralWidget->size();
    plugin->resize(size);

}

NastyFFT* MainWindow::glView()
{
    return plugin;
}

void MainWindow::changePreset()
{
    QAction *act = (QAction*)QObject::sender();
    QVariant data = act->data();
    dialog->loadPreset(data.toInt());
}
void MainWindow::showSettings()
{

    dialog->show();


}
void MainWindow::toggleLock()
{
    Qt::WindowFlags f1 = this->windowFlags();


    cout << "Current WindowFlags: " << f1 << endl;

    //(Qt::WindowFlags)134279169
    if (f1 == this->ctor_wflags) {


        hide();

        this->setWindowFlags( Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );

//        this->setWindowOpacity(0.90);

        plugin->setLocked(true);
        ui->mainToolBar->hide();
        ui->menuBar->hide();

this->setAttribute( Qt::WA_TranslucentBackground, true);
plugin->setAttribute( Qt::WA_TranslucentBackground, true);

        Qt::WindowFlags f2 = this->windowFlags();

        cout << "Frameless WindowFlags: " << f2 << endl;

        QSize new_size(width()+1, height()+1);
        this->resize(new_size);
    }
    else {


        hide();

        cout << "Setting CTOR WindowFlags: " << this->ctor_wflags << endl;
//        this->setWindowOpacity(1.0);
        this->setWindowFlags( this->ctor_wflags );

        plugin->setAttribute( Qt::WA_TranslucentBackground, true);

        plugin->setLocked(false);
        ui->mainToolBar->show();
        ui->menuBar->show();



        QSize new_size(width()-1, height()-1);
        this->resize(new_size);

    }

    this->show();

}
