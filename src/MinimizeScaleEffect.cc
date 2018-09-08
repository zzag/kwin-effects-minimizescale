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
#include "MinimizeScaleEffect.h"

// KConfigSkeleton
#include "MinimizeScaleConfig.h"

MinimizeScaleEffect::MinimizeScaleEffect()
{
    initConfig<MinimizeScaleConfig>();
    reconfigure(ReconfigureAll);

    connect(KWin::effects, &KWin::EffectsHandler::windowMinimized,
        this, &MinimizeScaleEffect::slotWindowMinimized);
    connect(KWin::effects, &KWin::EffectsHandler::windowUnminimized,
        this, &MinimizeScaleEffect::slotWindowUnminimized);
    connect(KWin::effects, &KWin::EffectsHandler::windowDeleted,
        this, &MinimizeScaleEffect::slotWindowDeleted);
}

MinimizeScaleEffect::~MinimizeScaleEffect()
{
}

void MinimizeScaleEffect::reconfigure(ReconfigureFlags flags)
{
    Q_UNUSED(flags);

    MinimizeScaleConfig::self()->read();

    m_duration = std::chrono::milliseconds(
        animationTime<MinimizeScaleConfig>(160));
}

void MinimizeScaleEffect::prePaintScreen(KWin::ScreenPrePaintData& data, int time)
{
    const std::chrono::milliseconds delta(time);

    auto animationIt = m_animations.begin();
    while (animationIt != m_animations.end()) {
        (*animationIt).timeLine.update(delta);
        ++animationIt;
    }

    data.mask |= PAINT_SCREEN_WITH_TRANSFORMED_WINDOWS;

    KWin::effects->prePaintScreen(data, time);
}

void MinimizeScaleEffect::prePaintWindow(KWin::EffectWindow* w, KWin::WindowPrePaintData& data, int time)
{
    if (m_animations.contains(w)) {
        data.setTransformed();
        w->enablePainting(KWin::EffectWindow::PAINT_DISABLED_BY_MINIMIZE);
    }

    KWin::effects->prePaintWindow(w, data, time);
}

void MinimizeScaleEffect::paintWindow(KWin::EffectWindow* w, int mask, QRegion region, KWin::WindowPaintData& data)
{
    auto animationIt = m_animations.constFind(w);
    if (animationIt == m_animations.constEnd()) {
        KWin::effects->paintWindow(w, mask, region, data);
        return;
    }

    const qreal t = (*animationIt).timeLine.value();

    data.multiplyOpacity(interpolate((*animationIt).fromOpacity, (*animationIt).toOpacity, t));

    KWin::effects->paintWindow(w, mask, region, data);
}

void MinimizeScaleEffect::postPaintScreen()
{
    auto animationIt = m_animations.begin();
    while (animationIt != m_animations.end()) {
        if ((*animationIt).timeLine.done()) {
            animationIt = m_animations.erase(animationIt);
        } else {
            ++animationIt;
        }
    }

    KWin::effects->addRepaintFull();
    KWin::effects->postPaintScreen();
}

bool MinimizeScaleEffect::isActive() const
{
    return !m_animations.isEmpty();
}

bool MinimizeScaleEffect::supported()
{
    return KWin::effects->animationsSupported();
}

void MinimizeScaleEffect::slotWindowMinimized(KWin::EffectWindow* w)
{
    if (KWin::effects->activeFullScreenEffect() != nullptr) {
        return;
    }

    if (!w->iconGeometry().isValid()) {
        return;
    }

    Animation& animation = m_animations[w];
    animation.kind = AnimationKind::Minimize;
    animation.timeLine.reset();
    animation.timeLine.setDirection(TimeLine::Forward);
    animation.timeLine.setDuration(m_duration);
    animation.timeLine.setEasingCurve(QEasingCurve::InOutSine);

    animation.fromOpacity = 1.0;
    animation.toOpacity = 0.0;

    w->addRepaintFull();
}

void MinimizeScaleEffect::slotWindowUnminimized(KWin::EffectWindow* w)
{
    if (KWin::effects->activeFullScreenEffect() != nullptr) {
        return;
    }

    if (!w->iconGeometry().isValid()) {
        return;
    }

    Animation& animation = m_animations[w];
    animation.kind = AnimationKind::Unminimize;
    animation.timeLine.reset();
    animation.timeLine.setDirection(TimeLine::Forward);
    animation.timeLine.setDuration(m_duration);
    animation.timeLine.setEasingCurve(QEasingCurve::InOutSine);

    animation.fromOpacity = 0.0;
    animation.toOpacity = 1.0;

    w->addRepaintFull();
}

void MinimizeScaleEffect::slotWindowDeleted(KWin::EffectWindow* w)
{
    m_animations.remove(w);
}
