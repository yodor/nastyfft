#ifndef PULSEAUDIOMONITOR_H
#define PULSEAUDIOMONITOR_H


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <pulse/simple.h>
#include <pulse/error.h>
#include <QByteArray>

#include <QThread>


class PulseAudioMonitor : public QThread
{
    Q_OBJECT

public:
     PulseAudioMonitor(QObject *parent = 0);
     ~PulseAudioMonitor();


public:
    void run();


signals:
    void dataReady(const QByteArray& data, const pa_sample_spec& spec );

public slots:
    void stop();

private:
    QByteArray buffer;

    bool running;
};

#endif // PULSEAUDIOMONITOR_H
