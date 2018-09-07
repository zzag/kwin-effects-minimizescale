find_package (Qt5 REQUIRED COMPONENTS
    Core
    Gui
)

find_package (KF5 REQUIRED COMPONENTS
    Config
    CoreAddons
    WindowSystem
)

find_package (KWinEffects REQUIRED)

set (effect_SRCS
    plugin.cc
    MinimizeScaleEffect.cc
)

kconfig_add_kcfg_files (effect_SRCS
    MinimizeScaleConfig.kcfgc
)

add_library (kwin4_effect_minimizescale SHARED ${effect_SRCS})

target_link_libraries (kwin4_effect_minimizescale
    PUBLIC
        Qt5::Core
        Qt5::Gui
        KF5::ConfigCore
        KF5::ConfigGui
        KF5::CoreAddons
        KF5::WindowSystem
        KWinEffects::KWinEffects
)

install (
    TARGETS
        kwin4_effect_minimizescale

    DESTINATION
        ${PLUGIN_INSTALL_DIR}/kwin/effects/plugins/
)
