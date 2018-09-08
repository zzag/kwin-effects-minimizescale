/*
 * Copyright (C) 2018 Vlad Zagorodniy <vladzzag@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

// own
#include "MinimizeScaleEffectKCM.h"

// Auto-generated
#include "MinimizeScaleConfig.h"
#include "kwineffects_interface.h"

// KF5
#include <KAboutData>

MinimizeScaleEffectKCM::MinimizeScaleEffectKCM(QWidget* parent, const QVariantList& args)
    : KCModule(KAboutData::pluginData(QStringLiteral("kwin4_effect_minimizescale")), parent, args)
    , m_ui(new Ui::MinimizeScaleEffectKCM)
{
    m_ui->setupUi(this);
    addConfig(MinimizeScaleConfig::self(), this);
    load();
}

MinimizeScaleEffectKCM::~MinimizeScaleEffectKCM()
{
    delete m_ui;
}

void MinimizeScaleEffectKCM::save()
{
    KCModule::save();
    OrgKdeKwinEffectsInterface interface(QStringLiteral("org.kde.KWin"),
        QStringLiteral("/Effects"),
        QDBusConnection::sessionBus());
    interface.reconfigureEffect(QStringLiteral("kwin4_effect_minimizescale"));
}
