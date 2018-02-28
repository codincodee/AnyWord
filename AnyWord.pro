#-------------------------------------------------
#
# Project created by QtCreator 2018-02-06T00:20:10
#
#-------------------------------------------------

QT       += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AnyWord
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    main_window.cpp \
    add_words_main_window.cpp \
    factory.cpp \
    database.cpp \
    word_entry.cpp \
    select_book_main_window.cpp \
    book_info.cpp \
    bookshelf.cpp \
    book.cpp \
    ui_utils.cpp \
    object_base.cpp \
    support_language.cpp \
    vocabulary.cpp \
    media_manager.cpp

HEADERS += \
    main_window.h \
    add_words_main_window.h \
    factory.h \
    database.h \
    word_entry.h \
    select_book_main_window.h \
    book_info.h \
    bookshelf.h \
    book.h \
    ui_utils.h \
    object_base.h \
    support_language.h \
    vocabulary.h \
    media_manager.h

FORMS += \
    main_window.ui \
    add_words_main_window.ui \
    select_book_main_window.ui

RC_ICONS = icon.ico
