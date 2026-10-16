#pragma once
#include "Enums.h"

struct SortedShapeCtx
{
	Vec2 center;

	double size;

	ColorF bodyColor;

	String text;

	SortingShapeType type;

	explicit SortedShapeCtx(const Vec2& c, const double s, const ColorF& bc, const String& t, const SortingShapeType ty)
		: center(c), size(s), bodyColor(bc), text(t), type(ty)
	{}

	explicit SortedShapeCtx(const Circle& c, const ColorF& bc, const String& t, const SortingShapeType ty)
		: center(c.center), size(c.r), bodyColor(bc), text(t), type(ty)
	{}

	explicit SortedShapeCtx(const RectF& r, const ColorF& bc, const String& t, const SortingShapeType ty)
		: center(r.center()), size(r.size.minComponent()), bodyColor(bc), text(t), type(ty)
	{}

	explicit SortedShapeCtx(const Triangle& tri, const ColorF& bc, const String& t, const SortingShapeType ty)
		: center(tri.centroid()), size(tri.side(0).length()), bodyColor(bc), text(t), type(ty)
	{}
};

class SortedShapeBase
{
public:
	explicit SortedShapeBase(const SortedShapeCtx& ctx)
		: m_bodyColor(ctx.bodyColor)
		, m_text(ctx.text)
		, m_type(ctx.type)
	{
		m_textSize = 0.0;
	}

	virtual ~SortedShapeBase() = default;

	void virtual update() = 0;

	void virtual draw() const = 0;

	const virtual bool isMouseOver() const = 0;

	const virtual Vec2& center() const = 0;

	void virtual move(const Vec2& to) = 0;

	const virtual Vec2 size() const = 0;

	const virtual bool isIntersects(const RectF& area) const = 0;

	const ColorF& color() const { return m_bodyColor; }

	const String& text() const { return m_text; }

	const SortingShapeType type() const { return m_type; }

protected:
	static constexpr ColorF m_TextColor = Palette::Black;

	static constexpr ColorF m_FrameColor = Palette::Black;

	static constexpr double m_FrameWidth = 8.0;

	const String m_FontName = U"FontText";

	ColorF m_bodyColor;

	String m_text;

	SortingShapeType m_type;

	double m_textSize;
};

class SortedCricle : public SortedShapeBase
{
public:
	explicit SortedCricle(const SortedShapeCtx& ctx)
		: SortedShapeBase(ctx)
	{
		m_body = Circle(ctx.center, ctx.size);

		m_textSize = m_body.r * 0.5;
	}

	~SortedCricle() {}

	void update() override {}

	void draw() const override
	{
		m_body.drawFrame(m_FrameWidth, m_FrameColor).draw(m_bodyColor);

		FontAsset(m_FontName)(m_text).drawAt(m_textSize, m_body.center, m_TextColor);
	}

	const bool isMouseOver() const override { return m_body.mouseOver(); }

	const Vec2& center() const override { return m_body.center; }

	void move(const Vec2& to) override { m_body.center = to; }

	const Vec2 size() const override { return Vec2(m_body.r, m_body.r); }

	const bool isIntersects(const RectF& area) const override { return m_body.intersects(area); }

private:
	//const double m_TextSize = m_body.r * 0.5;

	Circle m_body;
};

class SortedSquare : public SortedShapeBase
{
public:
	explicit SortedSquare(const SortedShapeCtx& ctx)
		: SortedShapeBase(ctx)
	{
		m_body = RectF(ctx.center, ctx.size);

		m_textSize = ctx.size * 0.5;
	}

	~SortedSquare() {}

	void update() override {}

	void draw() const override
	{
		m_body.drawFrame(m_FrameWidth, m_FrameColor).draw(m_bodyColor);

		FontAsset(m_FontName)(m_text).drawAt(m_textSize, m_body.center(), m_TextColor);
	}

	const bool isMouseOver() const override { return m_body.mouseOver(); }

	const Vec2& center() const override { return m_body.center(); }

	void move(const Vec2& to) override { m_body.center() = to; }

	const Vec2 size() const override { return m_body.size; }

	const bool isIntersects(const RectF& area) const override { return m_body.intersects(area); }

private:
	//const double m_TextSize = m_body.size.minComponent() * 0.5;

	RectF m_body;
};

class SortedTriangle : public SortedShapeBase
{
public:
	explicit SortedTriangle(const SortedShapeCtx& ctx)
		: SortedShapeBase(ctx)
	{
		m_body = Triangle(ctx.center, ctx.size);

		m_textSize = ctx.size * 0.5;
	}

	~SortedTriangle() {}

	void update() override {}

	void draw() const override
	{
		m_body.drawFrame(m_FrameWidth, m_FrameColor).draw(m_bodyColor);

		FontAsset(m_FontName)(m_text).drawAt(m_textSize, m_body.centroid(), m_TextColor);
	}

	const bool isMouseOver() const override { return m_body.mouseOver(); }

	const Vec2& center() const override { return m_body.centroid(); }

	void move(const Vec2& to) override { m_body.centroid() = to; }

	const Vec2 size() const override { return Vec2(m_body.side(0).length(), m_body.side(0).length()); }

	const bool isIntersects(const RectF& area) const override { return m_body.intersects(area); }

private:
	Triangle m_body;
};
