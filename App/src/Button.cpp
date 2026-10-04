#include "stdafx.h"
#include "Button.h"

/*	Start ButtonBase	********************************************************************************************************/

ButtonBase::ButtonBase(const ButtonCtx& ctx)
	: m_center(ctx.center)
	, m_size(ctx.size)
	, m_bodyColor(ctx.bodyColor)
	, m_text(ctx.text)
	, m_fontName(ctx.fontName)
{
	turnOffDraw();
	turnOffPerform();
}

/*	End ButtonBase		********************************************************************************************************/

/*	Start ButtonRect	********************************************************************************************************/

ButtonRect::ButtonRect(const ButtonCtx& ctx)
	: ButtonBase(ctx)
{
	m_body = RectF(Arg::center(m_center), m_size);
}

void ButtonRect::update(const double dt)
{
	if (m_canPerform && isReleased()) perform();
}

void ButtonRect::draw() const
{
	if (!m_isDrawing) return;

	constexpr double FrameWidth = 8.0;
	constexpr double FrameColorRate = 0.6;

	double darkness = 1.0;

	if (m_canPerform && m_body.mouseOver())
	{
		// カーソルを手の形にする.
		Cursor::RequestStyle(CursorStyle::Hand);

		if (MouseL.pressed()) darkness = 0.5;
		else darkness = 0.7;
	}
	else
	{
		darkness = 1.0;
	}

	m_body.drawFrame(FrameWidth, m_bodyColor * FrameColorRate).draw(m_bodyColor * darkness);
	FontAsset(m_fontName)(m_text).drawAt(textSize(), m_center, textColor());
}

const bool ButtonRect::isReleased() const
{
	return m_body.mouseOver() && MouseL.up();
}

/*	End ButtonRect		********************************************************************************************************/

/*	Start ButtonRectMove	********************************************************************************************************/

ButtonRectMove::ButtonRectMove(const ButtonCtx& ctx, const Vec2& from, const SecondsF delay, const Easing& easing)
	: ButtonRect(ctx)
	, m_from(from)
	, m_delay(delay)
	, m_easing(easing)
{
	// delay 秒だけ遅延させる.
	m_stopwatch.set(-delay);

	m_stopwatch.start();
}

void ButtonRectMove::update(const double dt)
{
	// イージング関数で移動させる.
	m_body.pos = m_from + m_easing(rate()) * (m_body.pos - m_from);

	// 移動した後で当たり判定を行う.
	ButtonRect::update(dt);
}

void ButtonRectMove::draw() const
{
	ButtonRect::draw();
}

const bool ButtonRectMove::isReleased() const
{
	return ButtonRect::isReleased();
}

/*	End ButtonRectMove		********************************************************************************************************/
