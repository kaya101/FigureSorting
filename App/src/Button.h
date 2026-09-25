#pragma once

struct ButtonCtx
{
	Vec2 center;

	SizeF size;

	ColorF bodyColor;

	String text;

	String fontName;

	std::function<void()> work;
};

class ButtonBase
{
public:
	explicit ButtonBase(const ButtonCtx& ctx);

	~ButtonBase() = default;

	void virtual update(const double dt, const bool isCovered = false) = 0;

	void virtual draw(const bool isCovered = false) const = 0;

	const bool virtual isReleased() const = 0;

protected:
	Vec2 m_center;

	SizeF m_size;

	ColorF m_bodyColor;

	String m_text;

	String m_fontName;

	std::function<void()> m_work;

	bool m_canPerform;

	const ColorF textColor() const { return (m_bodyColor.grayscale() < 0.5) ? Palette::White : Palette::Black; }

	const double textSize() const { return m_size.minComponent() * 0.5; }

	void perform() const { m_work(); }
};

// 静止した四角いボタン.
class ButtonRect : public ButtonBase
{
public:
	explicit ButtonRect(const ButtonCtx& ctx);

	~ButtonRect() = default;

	void update(const double dt, const bool isCovered) override;

	void draw(const bool isCovered) const override;

	const bool isReleased() const override;

protected:
	RectF m_body;
};

// 動く四角いボタン.
class ButtonRectMove : public ButtonRect
{
public:
	explicit ButtonRectMove(const ButtonCtx& ctx, const Vec2& from, const SecondsF delay, const std::function<double(double)> easing);

	~ButtonRectMove() = default;

	void update(const double dt, const bool isCovered) override;

	void draw(const bool isCovered) const override;

	const bool isReleased() const override;

	const double rate() const { return Min(1.0, Max(0.0, m_stopwatch.sF())); }

private:
	Vec2 m_from;	// 出現点.

	SecondsF m_delay;

	std::function<double(double)> m_easing;

	Stopwatch m_stopwatch{ StartImmediately::No };
};
