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

#pragma once

// own
#include "TimeLine.h"

// kwineffects
#include <kwineffects.h>

// Qt
#include <QHash>

class MinimizeScaleEffect : public KWin::Effect {
    Q_OBJECT
    Q_PROPERTY(int duration READ duration)

public:
    MinimizeScaleEffect();
    ~MinimizeScaleEffect() override;

    void reconfigure(ReconfigureFlags flags) override;

    void prePaintScreen(KWin::ScreenPrePaintData& data, int time) override;
    void prePaintWindow(KWin::EffectWindow* w, KWin::WindowPrePaintData& data, int time) override;
    void paintWindow(KWin::EffectWindow* w, int mask, QRegion region, KWin::WindowPaintData& data) override;
    void postPaintScreen() override;

    bool isActive() const override;
    int requestedEffectChainPosition() const override;

    int duration() const;

public:
    static bool supported();

private slots:
    void slotWindowMinimized(KWin::EffectWindow* w);
    void slotWindowUnminimized(KWin::EffectWindow* w);
    void slotWindowDeleted(KWin::EffectWindow* w);

private:
    std::chrono::milliseconds m_duration;

    enum class AnimationKind {
        Minimize,
        Unminimize
    };

    struct Animation {
        AnimationKind kind;
        TimeLine timeLine;
        qreal fromScale;
        qreal toScale;
        qreal fromOpacity;
        qreal toOpacity;
    };

    QHash<const KWin::EffectWindow*, Animation> m_animations;
};

inline int MinimizeScaleEffect::requestedEffectChainPosition() const
{
    return 50;
}

inline int MinimizeScaleEffect::duration() const
{
    return m_duration.count();
}
