

#include <QApplication>
#include "mainwindow.h"
#include "pulseaudiomonitor.h"
#include "spectrumanalyser.h"

int main(int argc, char*argv[]) {
    /* The sample type to use */
    QApplication app(argc, argv);

    qRegisterMetaType<FrequencySpectrum>("FrequencySpectrum");
    qRegisterMetaType<WindowFunction>("WindowFunction");
    qRegisterMetaType<pa_sample_spec>("pa_sample_spec");



    MainWindow m;

    m.show();


    PulseAudioMonitor monitor(&app);


    SpectrumAnalyser spectrum(&app);

    QObject::connect(&monitor, SIGNAL(dataReady(const QByteArray&, const pa_sample_spec& )), &spectrum,SLOT(calculate(const QByteArray&, const pa_sample_spec&)));

    QObject::connect(&spectrum,SIGNAL(spectrumChanged(FrequencySpectrum)), m.glView(), SLOT(scopeEvent(FrequencySpectrum)));

    QObject::connect(&app, SIGNAL(lastWindowClosed()), &monitor, SLOT(stop()));

    monitor.start();

    return app.exec();
}

