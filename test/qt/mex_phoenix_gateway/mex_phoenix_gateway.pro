#-------------------------------------------------
#
# Project created by QtCreator 2014-10-22T13:11:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mex_phoenix_gateway
TEMPLATE = app

QMAKE_CFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-parameter -Wno-sign-compare

INCLUDEPATH +=  ../../../libs/bsp/src/x86 \
                ../../../libs/bsp/inc \
                ../../../libs/bsp/inc/m4 \
                ../../../libs/hw_hcs12/inc \
                ../../../libs/hw_hcs12/src/bsp \
                ../../../sources \
                ../../../sources/bsp \
                ../../../model/functions \
                ../../../model/MX_Gtwy_Control_bobcat_ert_rtw


DEFINES += HCS12_BSP_EMU=1 \
           PORTABLE_WORDSIZES=1 \
           FALSE=false \
           TRUE=true \
           far=


SOURCES += main.cpp\
        mainwindow.cpp \
    ../../../libs/bsp/src/x86/timer.c \
    ../../../libs/bsp/src/x86/x86_bsp_adc.c \
    ../../../libs/bsp/src/x86/x86_bsp_can.c \
    ../../../libs/bsp/src/x86/x86_bsp_clock.c \
    ../../../libs/bsp/src/x86/x86_bsp_com.c \
    ../../../libs/bsp/src/x86/x86_bsp_din.c \
    ../../../libs/bsp/src/x86/x86_bsp_dout.c \
    ../../../libs/bsp/src/x86/x86_bsp_ecuid.c \
    ../../../libs/bsp/src/x86/x86_bsp_fin.c \
    ../../../libs/bsp/src/x86/x86_bsp_mcu.c \
    ../../../libs/bsp/src/x86/x86_bsp_nvm.c \
    ../../../libs/bsp/src/x86/x86_bsp_pwm.c \
    ../../../libs/bsp/src/x86/x86_bsp_rom.c \
    ../../../libs/bsp/src/x86/x86_bsp_rtc.c \
    ../../../libs/bsp/src/x86/x86_bsp_sdata.c \
    ../../../libs/hw_hcs12/src/emuBSP/hw_adc.cpp \
    ../../../libs/hw_hcs12/src/emuBSP/hw_can.cpp \
    ../../../libs/hw_hcs12/src/emuBSP/hw_clock.cpp \
    ../../../libs/hw_hcs12/src/emuBSP/hw_dio.cpp \
    ../../../libs/hw_hcs12/src/emuBSP/hw_fin.cpp \
    ../../../libs/hw_hcs12/src/emuBSP/hw_io.cpp \
    ../../../libs/hw_hcs12/src/emuBSP/hw_mcu.cpp \
    ../../../libs/hw_hcs12/src/emuBSP/hw_nvm.cpp \
    ../../../libs/hw_hcs12/src/emuBSP/hw_pwm.cpp \
    ../../../libs/hw_hcs12/src/emuBSP/nvm_ecuid.cpp \
    ../../../libs/hw_hcs12/src/hw_can_rx.cpp \
    ../../../libs/hw_hcs12/src/hw_can_tx.cpp \
    ../../../libs/hw_hcs12/src/hw_can_txq.cpp \
    ../../../libs/hw_hcs12/src/hw_gauge.cpp \
    ../../../libs/hw_hcs12/src/hw_timer.cpp \
    ../../../libs/hw_hcs12/src/J1939_msg.cpp \
    ../../../libs/hw_hcs12/src/J1939_TP.cpp \
    ../../../libs/hw_hcs12/src/J1939_TP_rx.cpp \
    ../../../libs/hw_hcs12/src/J1939_TP_tx.cpp \
    ../../../sources/ap_bservice.cpp \
    ../../../sources/ap_bservice_CAN04.cpp \
    ../../../sources/ap_bservice_dv.cpp \
    ../../../sources/ap_bservice_prog.cpp \
    ../../../sources/ap_can.cpp \
    ../../../sources/ap_deluxeG5.cpp \
    ../../../sources/ap_dv.cpp \
    ../../../sources/ap_eeprom.cpp \
    ../../../sources/ap_gateway.cpp \
    ../../../sources/ap_hwt.cpp \
    ../../../sources/ap_keylessstart.cpp \
    ../../../sources/ap_main.cpp \
    ../../../sources/ap_subs.cpp \
    ../../../sources/ap_tasks.cpp \
    ../../../sources/ap_version.cpp \
    ../../../sources/global.cpp \
    ../../../model/functions/SendMsgNow.cpp \
    ../../../model/MX_Gtwy_Control_bobcat_ert_rtw/mod_Inputs.cpp \
    ../../../model/MX_Gtwy_Control_bobcat_ert_rtw/mod_Library.cpp \
    ../../../model/MX_Gtwy_Control_bobcat_ert_rtw/mod_Outputs.cpp \
    ../../../model/MX_Gtwy_Control_bobcat_ert_rtw/mod_Panel.cpp \
    ../../../model/MX_Gtwy_Control_bobcat_ert_rtw/mod_System.cpp \
    ../../../model/MX_Gtwy_Control_bobcat_ert_rtw/MX_Gtwy_Control.cpp \
    ../../../model/MX_Gtwy_Control_bobcat_ert_rtw/MX_Gtwy_Control_data.cpp \
    ../../../sources/bsp/cdata.c \
    ../../../sources/bsp/ap_eeprom_bsp.cpp \
    ../../../sources/bsp/ap.cpp \
    ../../../sources/bsp/ap_bsp.cpp \
    ../../../sources/bsp/ap_cdata_noMap.cpp \
    ../../../sources/bsp/ap_schd.cpp

HEADERS  += mainwindow.h \
    ../../../libs/bsp/inc/bsp_adc.h \
    ../../../libs/bsp/inc/bsp_can.h \
    ../../../libs/bsp/inc/bsp_clock.h \
    ../../../libs/bsp/inc/bsp_com.h \
    ../../../libs/bsp/inc/bsp_common.h \
    ../../../libs/bsp/inc/bsp_din.h \
    ../../../libs/bsp/inc/bsp_dout.h \
    ../../../libs/bsp/inc/bsp_ecuid.h \
    ../../../libs/bsp/inc/bsp_fin.h \
    ../../../libs/bsp/inc/bsp_mcu.h \
    ../../../libs/bsp/inc/bsp_nvm.h \
    ../../../libs/bsp/inc/bsp_pwm.h \
    ../../../libs/bsp/inc/bsp_rom.h \
    ../../../libs/bsp/inc/bsp_rtc.h \
    ../../../libs/bsp/inc/bsp_sdata.h \
    ../../../libs/bsp/src/x86/timer.h \
    ../../../libs/bsp/src/x86/x86_bsp_adc.h \
    ../../../libs/bsp/src/x86/x86_bsp_can.h \
    ../../../libs/bsp/src/x86/x86_bsp_clock.h \
    ../../../libs/bsp/src/x86/x86_bsp_com.h \
    ../../../libs/bsp/src/x86/x86_bsp_din.h \
    ../../../libs/bsp/src/x86/x86_bsp_dout.h \
    ../../../libs/bsp/src/x86/x86_bsp_ecuid.h \
    ../../../libs/bsp/src/x86/x86_bsp_fin.h \
    ../../../libs/bsp/src/x86/x86_bsp_mcu.h \
    ../../../libs/bsp/src/x86/x86_bsp_nvm.h \
    ../../../libs/bsp/src/x86/x86_bsp_pwm.h \
    ../../../libs/bsp/src/x86/x86_bsp_rom.h \
    ../../../libs/bsp/src/x86/x86_bsp_rtc.h \
    ../../../libs/bsp/src/x86/x86_bsp_sdata.h \
    ../../../libs/hw_hcs12/inc/Hw_adc.h \
    ../../../libs/hw_hcs12/inc/hw_can.h \
    ../../../libs/hw_hcs12/inc/hw_can_msg.h \
    ../../../libs/hw_hcs12/inc/hw_can_rx.h \
    ../../../libs/hw_hcs12/inc/hw_can_tx.h \
    ../../../libs/hw_hcs12/inc/hw_can_txq.h \
    ../../../libs/hw_hcs12/inc/hw_clock.h \
    ../../../libs/hw_hcs12/inc/Hw_dio.h \
    ../../../libs/hw_hcs12/inc/hw_fin.h \
    ../../../libs/hw_hcs12/inc/hw_fps.h \
    ../../../libs/hw_hcs12/inc/hw_gauge.h \
    ../../../libs/hw_hcs12/inc/hw_io.h \
    ../../../libs/hw_hcs12/inc/hw_io_GetSet.h \
    ../../../libs/hw_hcs12/inc/hw_mcu.h \
    ../../../libs/hw_hcs12/inc/hw_nvm.h \
    ../../../libs/hw_hcs12/inc/hw_pwm.h \
    ../../../libs/hw_hcs12/inc/hw_reset.h \
    ../../../libs/hw_hcs12/inc/hw_timer.h \
    ../../../libs/hw_hcs12/inc/J1939_msg.h \
    ../../../libs/hw_hcs12/inc/J1939_TP.h \
    ../../../libs/hw_hcs12/inc/J1939_TP_rx.h \
    ../../../libs/hw_hcs12/inc/J1939_TP_tx.h \
    ../../../libs/hw_hcs12/inc/nvm_ecuid.h \
    ../../../sources/af_main.h \
    ../../../sources/ap_bservice.h \
    ../../../sources/ap_bservice_CAN04.h \
    ../../../sources/ap_bservice_dv.h \
    ../../../sources/ap_bservice_prog.h \
    ../../../sources/ap_can.h \
    ../../../sources/ap_deluxeG5.h \
    ../../../sources/ap_dv.h \
    ../../../sources/ap_eeprom.h \
    ../../../sources/ap_gateway.h \
    ../../../sources/ap_hwt.h \
    ../../../sources/ap_keylessstart.h \
    ../../../sources/ap_main.h \
    ../../../sources/ap_MXGWcontrol_defs.h \
    ../../../sources/ap_subs.h \
    ../../../sources/ap_tasks.h \
    ../../../sources/ap_version.h \
    ../../../sources/defines.h \
    ../../../sources/global.h \
    ../../../sources/hw_can_cfg.h \
    ../../../model/functions/SendMsgNow.h \
    ../../../model/MX_Gtwy_Control_bobcat_ert_rtw/mod_Inputs.h \
    ../../../model/MX_Gtwy_Control_bobcat_ert_rtw/mod_Library.h \
    ../../../model/MX_Gtwy_Control_bobcat_ert_rtw/mod_Outputs.h \
    ../../../model/MX_Gtwy_Control_bobcat_ert_rtw/mod_Panel.h \
    ../../../model/MX_Gtwy_Control_bobcat_ert_rtw/mod_System.h \
    ../../../model/MX_Gtwy_Control_bobcat_ert_rtw/MX_Gtwy_Control.h \
    ../../../model/MX_Gtwy_Control_bobcat_ert_rtw/MX_Gtwy_Control_private.h \
    ../../../model/MX_Gtwy_Control_bobcat_ert_rtw/MX_Gtwy_Control_types.h \
    ../../../model/MX_Gtwy_Control_bobcat_ert_rtw/rtwtypes.h \
    ../../../sources/bsp/ap.h \
    ../../../sources/bsp/ap_bsp.h \
    ../../../sources/bsp/ap_cdata.h \
    ../../../sources/bsp/ap_schd.h

FORMS    += mainwindow.ui
