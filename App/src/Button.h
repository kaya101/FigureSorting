#pragma once

struct ButtonCtx
{
	Vec2 center;

	SizeF size;

	ColorF bodyColor;

	String text;

	String fontName;

	ButtonCtx(const Vec2& c, const SizeF& s, const ColorF& bc, const String& t, const String& fn)
		: center(c), size(s), bodyColor(bc), text(t), fontName(fn) {}

	ButtonCtx(const RectF& rect, const ColorF& bc, const String& t, const String& fn)
		: center(rect.center()), size(rect.size), bodyColor(bc), text(t), fontName(fn) {}
};

class ButtonBase
{
public:
	using Work = std::function<void()>;

	explicit ButtonBase(const ButtonCtx& ctx);

	~ButtonBase() = default;

	void virtual update() = 0;

	void virtual draw() const = 0;

	const bool virtual isReleased() const = 0;

	void turnOnDraw() { m_isDrawing = true; }
	void turnOffDraw() { m_isDrawing = false; }

	void turnOnPerform() { m_canPerform = true; }
	void turnOffPerform() { m_canPerform = false; }

	void setText(const String& text) { m_text = text; }
	void setWorkCallBack(const Work& cb) { m_workCallBack = cb; }

	const bool isDrawing() const { return m_isDrawing; }
	const bool canPerform() const { return m_canPerform; }

protected:
	Vec2 m_center;

	SizeF m_size;

	ColorF m_bodyColor;

	String m_text;

	String m_fontName;

	Work m_workCallBack;

	bool m_isDrawing;

	bool m_canPerform;

	const ColorF textColor() const { return (m_bodyColor.grayscale() < 0.5) ? Palette::White : Palette::Black; }

	const double textSize() const { return m_size.minComponent() * 0.5; }

	void perform() const { m_workCallBack(); }
};

// 静止した四角いボタン.
class ButtonRect : public ButtonBase
{
public:
	explicit ButtonRect(const ButtonCtx& ctx);

	~ButtonRect() = default;

	void update() override;

	void draw() const override;

	const bool isReleased() const override;

protected:
	RectF m_body;
};

// 動く四角いボタン.
class ButtonRectMove : public ButtonRect
{
public:
	using Easing = std::function<double(double)>;

	explicit ButtonRectMove(const ButtonCtx& ctx, const Vec2& from, const SecondsF delay, const Easing& easing);

	~ButtonRectMove() = default;

	void update() override;

	void draw() const override;

	const bool isReleased() const override;

	const double rate() const { return Min(1.0, Max(0.0, m_stopwatch.sF())); }

	void startStopwatch() { m_stopwatch.start(); }

private:
	Vec2 m_from;	// 出現点.

	SecondsF m_delay;

	Easing m_easing;

	Stopwatch m_stopwatch{ StartImmediately::No };
};
