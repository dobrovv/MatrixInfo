QT += widgets

SOURCES += \
    main.cpp \
    CMatrix.cpp \
    CNumber.cpp \
    CNumberVector.cpp \
    QMatrixWidget.cpp \
    QMatrixWidgetElement.cpp \
    MainWindow.cpp

HEADERS += \
    CMatrix.h \
    CNumber.h \
    CNumberVector.h \
    QMatrixWidget.h \
    QMatrixWidgetElement.h \
    MainWindow.h

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
