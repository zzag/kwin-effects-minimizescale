set (kcm_SRCS
    MinimizeScaleEffectKCM.cc
    plugin.cc
)

kconfig_add_kcfg_files (kcm_SRCS
    ../MinimizeScaleConfig.kcfgc
)

include (PkgConfigGetVar)
pkgconfig_getvar (dbus-1 interfaces_dir INTERFACES_DIR)
qt5_add_dbus_interface (kcm_SRCS ${INTERFACES_DIR}/org.kde.kwin.Effects.xml kwineffects_interface)
qt5_wrap_ui (kcm_SRCS MinimizeScaleEffectKCM.ui)

add_library (kwin_minimizescale_config MODULE ${kcm_SRCS})

target_link_libraries (kwin_minimizescale_config
    Qt5::Core
    Qt5::DBus
    Qt5::Gui
    KF5::ConfigCore
    KF5::ConfigGui
    KF5::ConfigWidgets
    KF5::Service
)

install (
    TARGETS
        kwin_minimizescale_config

    DESTINATION
        ${PLUGIN_INSTALL_DIR}/kwin/effects/configs
)