# -------------------------------------------------
# Project created by QtCreator 2012-03-05T23:58:45
# -------------------------------------------------
# add -m64 to flags for 64-bit Intel
# CXXFLAGS=-g -DDEBUG -I../include -I. -c
# LDFLAGS=-g
CXXFLAGS = -O2 \
    -I../../ntl-5.5.2/include \
    -I. \
    -DNO_DEBUG \
    -DNO_TIMER
LDFLAGS = -O2 \
    -L../..//msys/1.0/local/lib/
QT -= core \
    gui
TARGET = AutomaticCryptanalisis
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
INCLUDEPATH += "WinNTL-5_5_2\include" \
    "WinNTL-5_5_2\src"

# LIBS += "WinNTL-5_5_2\lib\libNTL.a"
LIBS += "WinNTL-5_5_2\NTL\release\libNTL.a"
SOURCES += main.cpp \
    PolynomialIdeal.cpp \
    Polynomial.cpp \
    MonomialOrder.cpp \
    Monomial.cpp \
    Utility.cpp \
    SymbolicOctonion.cpp \
    PolynomialFraction.cpp \
    SymbolicMatrix.cpp \
    Variable.cpp \
    Cryptosystems/YagisavaCryptosystem.cpp \
    Cryptosystems/KipnisHibshooshCryptosystem.cpp \
    Cryptosystems/GavinCryptosystem.cpp
HEADERS += PolynomialIdeal.h \
    Polynomial.h \
    MonomialOrder.h \
    Monomial.h \
    Variable.h \
    Utility.h \
    SymbolicOctonion.h \
    PolynomialFraction.h \
    SymbolicMatrix.h \
    Variable.h \
    Cryptosystems/YagisavaCryptosystem.h \
    Cryptosystems/KipnisHibshooshCryptosystem.h \
    Cryptosystems/GavinCryptosystem.h
