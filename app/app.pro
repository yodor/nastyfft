
QT       += core gui opengl

TARGET = nastyfft
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
nastyfft.cpp \
    pulseaudiomonitor.cpp\
spectrumanalyser.cpp\
frequencyspectrum.cpp\
utils.cpp \
    settingsdialog.cpp


HEADERS  += mainwindow.h\
nastyfft.h\
scenepreset.h \
    pulseaudiomonitor.h\
spectrumanalyser.h\
frequencyspectrum.h\
spectrum.h\
utils.h \
    settingsdialog.h

LIBS += -lpulse-simple -lpulse -lGLU

FORMS    += mainwindow.ui \
    settingsdialog.ui


fftreal_dir = ../fftreal

INCLUDEPATH += $${fftreal_dir}

LIBS += -L../
LIBS += -lfftreal

# If defined, superimpose the progress bar on the waveform
DEFINES += SUPERIMPOSE_PROGRESS_ON_WAVEFORM

# Perform spectrum analysis calculation in a separate thread
DEFINES += SPECTRUM_ANALYSER_SEPARATE_THREAD

#DEFINES += DUMP_SPECTRUMANALYSER

DESTDIR = ../

        linux-g++*: {
            # Provide relative path from application to fftreal library
            QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN
        }
