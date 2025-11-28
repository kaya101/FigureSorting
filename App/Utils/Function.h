#pragma once
#include "Common.h"


//お気に入りの乱数生成.
static unsigned int randInt() {
	static unsigned int tx = 123456789, ty = 362436069, tz = 521288629, tw = 88675123;
	unsigned int tt = (tx ^ (tx << 11));
	tx = ty; ty = tz; tz = tw;
	return (tw = (tw ^ (tw >> 19)) ^ (tt ^ (tt >> 8)));
}
//リンク「https://qiita.com/drken/items/7c6ff2aa4d8fce1c9361#9-xorshift」.



//イージング.
//何度か跳ねるやつ.
static double easeOutBounce(double t) {
	const double n1 = 7.5625;
	const double d1 = 2.75;

	if (t < 1 / d1) {
		return n1 * t * t;
	}
	else if (t < 2 / d1) {
		return n1 * (t -= 1.5 / d1) * t + 0.75;
	}
	else if (t < 2.5 / d1) {
		return n1 * (t -= 2.25 / d1) * t + 0.9375;
	}
	else {
		return n1 * (t -= 2.625 / d1) * t + 0.984375;
	}
}
//ぎゅっと最初に動く.
static double easeOutExpo(double t) {
	return t == 1 ? 1 : 1 - pow(2, -10 * t);
}
//大体一定の速度で動く.
static double easeOutQuad(double t) {
	return 1 - (1 - t) * (1 - t);
}



//ボタン.
static bool button(const RectF& rectf, const ColorF& colorf, const Font& font, const String& text, const ColorF& textcolor, const uint8& size, const ColorF& framecolor, const bool& enabled, const bool& notover) {

	rectf.drawFrame(haba, framecolor);
	if (enabled) {
		if (not notover && rectf.mouseOver()) {
			Cursor::RequestStyle(CursorStyle::Hand);
			if (MouseL.pressed()) {
				rectf.draw(colorf * 0.7 * 0.7);
				font(text).drawAt(size, (rectf.x + rectf.w / 2), (rectf.y + rectf.h / 2), textcolor);
			}
			else {
				rectf.draw(colorf * 0.7);
				font(text).drawAt(size, (rectf.x + rectf.w / 2), (rectf.y + rectf.h / 2), textcolor);
			}
		}
		else {
			rectf.draw(colorf);
			font(text).drawAt(size, (rectf.x + rectf.w / 2), (rectf.y + rectf.h / 2), textcolor);
		}
	}
	else {
		rectf.draw(haiiro);
		font(text).drawAt(size, (rectf.x + rectf.w / 2), (rectf.y + rectf.h / 2), textcolor * 0.8);
	}

	return enabled && not notover && rectf.mouseOver() && MouseL.up();
}

//左上頂点表示を変換して利用するタイプ.
//四角の中心座標( x, y )を求める関数.
static double culc_x(const RectF& rectf) {
	return rectf.x + (rectf.w / 2);
}
static double culc_y(const RectF& rectf) {
	return rectf.y + (rectf.h / 2);
}
//中心座標から四角の左上座標を求める関数.
static int16 culc_lx(const Figure& figure) {
	return figure.center.x - (figure.size / 2);
}
static int16 culc_ly(const Figure& figure) {
	return figure.center.y - (figure.size / 2);
}
//正三角形の 3 頂点から辺の長さを求める関数.
//実際は 2 点で足りるけど.
static double culc_Length(const Triangle& triangle) {
	return sqrt(pow(triangle.p1.x - triangle.p0.x, 2) + pow(triangle.p1.y - triangle.p0.y, 2));
}

//任意の座標成分より,図形の中心がはみ出ないようにする関数.
static double check_wallx(const Array<uint16>& wall, const int16& point_x, const Figure& figure) {
	if (point_x - figure.size/2 <= wall[0]) {
		return wall[0] + figure.size/2;
	}
	else if (wall[1] <= point_x + figure.size/2) {
		return wall[1] - figure.size / 2;
	}
	else {
		return point_x;
	}
}
static double check_wally(const Array<uint16>& wall, const int16& point_y, const Figure& figure) {
	if (point_y - figure.size/2 <= wall[0]) {
		return wall[0] + figure.size / 2;
	}
	else if (wall[1] <= point_y + figure.size/2) {
		return wall[1] - figure.size / 2;
	}
	else {
		return point_y;
	}
}

//図形の色を決める関数.
static void decide_color(Figure& figure, const uint8& stageNum, const bool& colorchange) {

	//そのステージで使える色は何種類あるうちのどれか.
	uint8 num = randInt() % kinds[stageNum][COLOR];
	//色を変更しているとき.
	if (colorchange) {
		figure.color = colorchangecolor[stageNum][num];
	}
	//最初の状態のまま.
	else {
		figure.color = color[stageNum][num];
	}
}
//図形の文字を決める関数.
static void decide_text(Figure& figure, const uint8& stageNum, const bool& colorchange) {

	//そのステージで使える文字は何種類あるうちのどれか.
	uint8 num = randInt() % kinds[stageNum][TEXT];

	//色を変更しているとき.
	if (colorchange && stageNum == STAGEMAX) {
		figure.text = colorchangetext[num];
	}
	//最初のまま.
	else {
		figure.text = teXt[stageNum][num];
	}
}

//分類箱.
static void box_under(const Rect& box, const ColorF& colorf) {
	box.draw(colorf * 0.8);
	box.drawFrame(haba, kuro);
}
static void box_over(const Rect& box, const ColorF& colorf, const Font& font, const String& string) {
	box.draw(colorf);
	box.drawFrame(haba, kuro);
	font(U"{}"_fmt(string)).drawAt((box.x + box.w / 2), (box.y + box.h / 2), kuro);
}


//ゲーム結果画面の幕が下りるやつ.
static void m_boxOutQuad_adu(double t, const Rect& rect, const ColorF& colorf) {
	RectF{ rect.x, rect.y, rect.w, rect.h * (1 - easeOutQuad(t))}.draw(colorf);
}
//ゲーム結果画面の幕が下りるやつ.
static void m_boxBounce_aud(double t, const Rect& rect, const ColorF& colorf) {
	RectF{ rect.x, rect.y, rect.w, rect.h * easeOutBounce(t) }.draw(colorf);
}
static void m_textBounce_aud(double t, const Vec2& vec2, const Font& font, const String& text, const uint8& size) {
	font(text).drawAt(size, vec2.x, vec2.y *easeOutBounce(t), kuro);
}
//結果画面でテキストが任意の座標から出てくるやつ.
static void m_textOutExpo_aap(double t, const Vec2& from, const Vec2& vec2, const ColorF& colorf, const Font& font, const String& text, const uint8& size) {
	//左上座標準拠.
	font(text).draw(size, from.x + easeOutExpo(t) * (vec2.x - from.x), from.y + easeOutExpo(t) * (vec2.y - from.y), colorf);
}
//それのボタンバージョン, 当たり判定付き.
static bool m_buttonOutExpo_aap(double t, const Vec2& vec2, const RectF& rectf, const ColorF& colorf, const Font& font, const String& text, const uint8& size, const ColorF& framecolor) {

	if (rectf.mouseOver()) {
		Cursor::RequestStyle(CursorStyle::Hand);
		//長押し判定.
		if (MouseL.pressed()) {
			//左上座標準拠.
			RectF{ vec2.x + easeOutExpo(t) * (rectf.x - vec2.x), vec2.y + easeOutExpo(t) * (rectf.y - vec2.y), rectf.w, rectf.h }.draw(colorf * 0.8 * 0.8);
			RectF{ vec2.x + easeOutExpo(t) * (rectf.x - vec2.x), vec2.y + easeOutExpo(t) * (rectf.y - vec2.y), rectf.w, rectf.h }.drawFrame(haba, framecolor);
			font(text).drawAt(size, (vec2.x + easeOutExpo(t) * (rectf.x - vec2.x) + rectf.w/2), (vec2.y + easeOutExpo(t) * (rectf.y - vec2.y) + rectf.h/2));
		}
		else {
			RectF{ vec2.x + easeOutExpo(t) * (rectf.x - vec2.x), vec2.y + easeOutExpo(t) * (rectf.y - vec2.y), rectf.w, rectf.h }.draw(colorf * 0.8);
			RectF{ vec2.x + easeOutExpo(t) * (rectf.x - vec2.x), vec2.y + easeOutExpo(t) * (rectf.y - vec2.y), rectf.w, rectf.h }.drawFrame(haba, framecolor);
			font(text).drawAt(size, (vec2.x + easeOutExpo(t) * (rectf.x - vec2.x) + rectf.w / 2), (vec2.y + easeOutExpo(t) * (rectf.y - vec2.y) + rectf.h / 2));
		}
	}
	else {
		RectF{ vec2.x + easeOutExpo(t) * (rectf.x - vec2.x), vec2.y + easeOutExpo(t) * (rectf.y - vec2.y), rectf.w, rectf.h }.draw(colorf);
		RectF{ vec2.x + easeOutExpo(t) * (rectf.x - vec2.x), vec2.y + easeOutExpo(t) * (rectf.y - vec2.y), rectf.w, rectf.h }.drawFrame(haba, framecolor);
		font(text).drawAt(size, (vec2.x + easeOutExpo(t) * (rectf.x - vec2.x) + rectf.w / 2), (vec2.y + easeOutExpo(t) * (rectf.y - vec2.y) + rectf.h / 2));
	}
	return t >= 1 && rectf.mouseOver() && MouseL.up();
}

//正誤判定のエフェクト.
static void effect_TrueOrFalse(double t, const uint8& comboNum, const ColorF& colorf, const Font& font, const uint8& textsize) {

	const String combo3 = U"Perfect!!!";
	const String combo2 = U"Great!!";
	const String combo1 = U"Good!";
	const String combo0 = U"Miss";
	constexpr uint16 effect_X = 400;
	constexpr uint16 effect_Y = 570;
	if (comboNum >= 3) {
		font(combo3.substr(0, t)).drawAt(textsize, effect_X, effect_Y, colorf);
	}
	else if (comboNum == 2) {
		font(combo2.substr(0, t)).drawAt(textsize, effect_X, effect_Y, colorf);
	}
	else if (comboNum == 0) {
		font(combo0.substr(0, t)).drawAt(textsize, effect_X, effect_Y, colorf);
	}
	else {
		font(combo1.substr(0, t)).drawAt(textsize, effect_X, effect_Y, colorf);
	}
}
