#include "stdafx.h"
# include <Siv3D.hpp> // Siv3D v0.6.14
#include "Utils/Common.h"
#include "Utils/Function.h"
#include "Utils/Color.h"
#include "GameScene.h"

//図形を仕分けてスコアを競うゲーム.

void Main()
{
	App manager;
	manager.add<Title>(SceneSwitch::Title);
	manager.add<Stage>(SceneSwitch::Stage);
	manager.add<LetsPlay>(SceneSwitch::Letsplay);
	manager.add<Result>(SceneSwitch::Result);

	manager.init(SceneSwitch::Title, 0s);// Title シーンから始めて, 0s 後に開始.

	// ゲームシーンから開始したい場合はこのコメントを外す
	//manager.init(State::Game);

	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
	}

	////背景.
	//Scene::SetBackground(bg_shiro);
	////全体の進行.
	//SceneSwitch ss = SceneSwitch::Title;
	////色が見づらいかどうか.
	//ColorSwitch cos = ColorSwitch::Saisyo;
	////説明をスキップするかどうか.
	//ExplainSkip es = ExplainSkip::Saisyo;
	//中断するかどうか.
	//PauseSwitch ps = PauseSwitch::BackButton;
	////説明とカウントダウンの振興.
	//CountSwitch cs = CountSwitch::ExplainRule;
	////図形操作の画面の信仰.
	//FigureSwitch fs = FigureSwitch::Break;
	////得点計算.
	//ScoreSwitch scs = ScoreSwitch::ShapeRule;
	////正誤判定.
	//TrueOrFalse tof = TrueOrFalse::WaitSort;
	////タイトルフォント.
	//FontAsset::Register(U"TitleFont", 60, Typeface::Heavy);
	////フォント.
	//const Font text{ FontMethod::SDF, 30, Typeface::Bold };
	////ゲーム開始のカウントダウン.
	//Stopwatch countdown{ StartImmediately::Yes };
	////制限時間.
	//Stopwatch playtime{ StartImmediately::No };
	////正誤判定のエフェクト.
	//Stopwatch truefalse{ StartImmediately::Yes };
	////結果発表の画面の閉幕.
	//Stopwatch resultwindow{ StartImmediately::Yes };
	////結果発表で遅れて文字が出てくるやつ.
	//Stopwatch resulttext01{ StartImmediately::No };
	//Stopwatch resulttext02{ StartImmediately::No };
	//Stopwatch resulttext03{ StartImmediately::No };

	////見本の図形たち.
	////まる.
	//Circle mihon_circle{};
	////さんかく.
	//Triangle mihon_triangle{};
	////しかく.
	//Rect mihon_rect{};
	////見本の図形の色.
	//Array<ColorF> mihon_color;
	////見本の文字.
	//Array<String> mihon_text;

	////動かす図形の素材の受け皿.
	//Figure figure;
	////まる.
	//Circle circle{};
	////さんかく.
	//Triangle triangle{};
	////しかく.
	//Rect rect{};
	////色.
	//Array<ColorF> Fcolor;
	////文字.
	//Array<String> Ftext;

	////図形を持ち運ぶときの図形の中心とカーソルの距離を保持する.
	//int16 distance_x = 0;
	//int16 distance_y = 0;
	////どのステージか.
	//uint8 stageNum = 0;
	////合計スコア.
	//int16 score = 0;
	////ハイスコア.
	//Array<int16> highscore = { 0, 0, 0 };
	////仕分けた個数.
	//uint8 classifyNum = 0;
	////正解した個数.
	//uint8 correctNum = 0;
	////間違えた個数.
	//uint8 missNum = 0;
	////連続正解数をカウント.
	//uint8 comboNum = 0;
	////カウントダウンの時間.
	//double t_cd = 0.0;
	////制限時間.
	//uint8 timelimit = 15;
	////制限時間のカウントダウン時間.
	//uint8 gt = 0;
	////仕分けルールの表示.
	//bool ruletext = false;
	////一時停止.
	//bool pause = false;
	////記録を更新したかどうか.
	//bool newrecord = false;
	////色が見づらかったかどうか.
	//bool colorchange = false;
	////見づらいマーク.
	//String colorchangeMark = U"";
	////説明をスキップするかどうか.
	//bool explainSkip = false;
	////説明スキップマーク.
	//String explainskipMark = U"";

	//while (System::Update()) {

	//	//switch (ss) {
	//	//case SceneSwitch::Title: //タイトル画面.

	//	//	////タイトルテキスト.
	//	//	//FontAsset(U"TitleFont")(U"仕分けゲーム").drawAt(400, 100, ColorF{ 0.2 });

	//	//	////はじめる.
	//	//	//if (button(hajimeru, botan*1.4, text, U"はじめる", shiro, 36, midori, true, false)) {
	//	//	//	//見本の図形の素材を流し込む.
	//	//	//	mihon_circle = { stage01textback.x + stage01textback.w / 2, stage01textback.y - stage01textback.w / 4 - 10 , stage01textback.w / 4 };
	//	//	//	mihon_triangle = { (double)(stage02textback.x + stage02textback.w / 2), (double)(stage02textback.y - stage02textback.w / 2 + 66) , (double)(stage02textback.w / 2) };
	//	//	//	mihon_rect = { Arg::center(stageMAXtextback.x + stageMAXtextback.w / 2, stageMAXtextback.y - stageMAXtextback.w / 2 + 40) , stageMAXtextback.w / 2 };
	//	//	//	mihon_color = { aka, midori, ao };
	//	//	//	mihon_text = { U"あか", U"みどり", U"あお" };

	//	//	//	ss = SceneSwitch::Stage;
	//	//	//}
	//	//	////やめる.
	//	//	//if (button(yameru, botan*1.4, text, U"やめる", shiro, 36, midori, true, false)) {
	//	//	//	System::Exit();
	//	//	//}

	//	//	break;

	//	//case SceneSwitch::Stage: //ステージ選択.

	//	//	////ステージの説明背景.
	//	//	//text(U"ステージ選択").draw(48, 50, 30, kuro);
	//	//	////01.
	//	//	//stage01textback.draw(haiiro);
	//	//	//stage01textback.drawFrame(haba, kuro);
	//	//	//text(U"Lv.1").drawAt(stagetextSize, stage01text);
	//	//	//text(U"High Score:{}\n\n・形でわける"_fmt(highscore[STAGE01])).draw(stagetextsubSize, stage01textsub);
	//	//	////02.
	//	//	//stage02textback.draw(haiiro);
	//	//	//stage02textback.drawFrame(haba, kuro);
	//	//	//text(U"Lv.2").drawAt(stagetextSize, stage02text);
	//	//	//text(U"High Score:{}\n\n・形でわける\n・色でわける"_fmt(highscore[STAGE02])).draw(stagetextsubSize, stage02textsub);
	//	//	////MAX.
	//	//	//stageMAXtextback.draw(haiiro);
	//	//	//stageMAXtextback.drawFrame(haba, kuro);
	//	//	//text(U"Lv.3").drawAt(stagetextSize, stageMAXtext);
	//	//	//text(U"High Score:{}\n\n・形でわける\n・色でわける\n・文字でわける"_fmt(highscore[STAGEMAX])).draw(stagetextsubSize, stageMAXtextsub);

	//	//	////図形の見本.
	//	//	//mihon_circle.draw(mihon_color[0]);
	//	//	//mihon_circle.drawFrame(haba, kuro);
	//	//	//mihon_triangle.draw(mihon_color[1]);
	//	//	//mihon_triangle.drawFrame(haba, kuro);
	//	//	//mihon_rect.draw(mihon_color[2]);
	//	//	//mihon_rect.drawFrame(haba, kuro);

	//	//	////色が見づらいかどうか.
	//	//	//text(U"色が見づらい場合:").drawAt(16, colorchangeText, kuro);
	//	//	//switch (cos) {
	//	//	//case ColorSwitch::Saisyo: //はじめの色彩設定のまま.
	//	//	//	// on にする.
	//	//	//	if (button(colorchangeBox, bg_shiro, text, U"", toumei, 0, kuro, true, false)) {
	//	//	//		colorchange = true;
	//	//	//		colorchangeMark = U"〆";
	//	//	//		mihon_color = { red, yelow, blue };
	//	//	//		mihon_text = { U"まる", U"さんかく", U"しかく" };
	//	//	//		cos = ColorSwitch::ColorChange;
	//	//	//	}
	//	//	//	break;
	//	//	//case ColorSwitch::ColorChange: //色を変えたとき.
	//	//	//	// off にする.
	//	//	//	if (button(colorchangeBox, bg_shiro, text, U"", toumei, 0, kuro, true, false)) {
	//	//	//		colorchange = false;
	//	//	//		colorchangeMark = U"";
	//	//	//		mihon_color = { aka, midori, ao };
	//	//	//		mihon_text = { U"あか", U"みどり", U"あお" };
	//	//	//		cos = ColorSwitch::Saisyo;
	//	//	//	}
	//	//	//	break;
	//	//	//default:
	//	//	//	break;
	//	//	//}
	//	//	////今どっちに切り替えたかの印.
	//	//	//text(U"{}"_fmt(colorchangeMark)).drawAt(16, colorchangeBox.x + colorchangeBox.w / 2, colorchangeBox.y + colorchangeBox.h / 2, kuro);

	//	//	////説明をスキップするかどうか.
	//	//	//explainskipBox.drawFrame(haba, kuro);
	//	//	//text(U"説明を飛ばすとき:").drawAt(16, explainskipText, kuro);
	//	//	//switch (es) {
	//	//	//case ExplainSkip::Saisyo: //説明し続ける場合.
	//	//	//	//スキップしたい.
	//	//	//	if (button(explainskipBox, bg_shiro, text, U"", toumei, 0, kuro, true, false)) {
	//	//	//		explainSkip = true;
	//	//	//		explainskipMark = U"〆";
	//	//	//		cs = CountSwitch::Start;
	//	//	//		es = ExplainSkip::Skip;
	//	//	//	}
	//	//	//	break;
	//	//	//case ExplainSkip::Skip: //説明をスキップする場合.
	//	//	//	//スキップしない.
	//	//	//	if (button(explainskipBox, bg_shiro, text, U"", toumei, 0, kuro, true, false)) {
	//	//	//		explainSkip = false;
	//	//	//		explainskipMark = U"";
	//	//	//		cs = CountSwitch::ExplainRule;
	//	//	//		es = ExplainSkip::Saisyo;
	//	//	//	}
	//	//	//	break;
	//	//	//default:
	//	//	//	break;
	//	//	//}
	//	//	////今どっちに切り替えたかの印.
	//	//	//text(U"{}"_fmt(explainskipMark)).drawAt(16, explainskipBox.x + explainskipBox.w / 2, explainskipBox.y + explainskipBox.h / 2, kuro);

	//	//	////難易度01.
	//	//	//if (button(stage01botan, botan*1.4, text, U"これ!!", shiro, stagebotantextSize, midori, true, false)) {
	//	//	//	//ここのステージで使える素材の受け取り.
	//	//	//	if (colorchange) {
	//	//	//		Fcolor = colorchangecolor_Lv01;
	//	//	//	}
	//	//	//	else {
	//	//	//		Fcolor = color_Lv01;
	//	//	//	}
	//	//	//	Ftext = text_Lv01;
	//	//	//	stageNum = STAGE01;
	//	//	//	//形でわける.
	//	//	//	scs = ScoreSwitch::ShapeRule;
	//	//	//	ss = SceneSwitch::Letsplay;
	//	//	//}
	//	//	////難易度02.
	//	//	//if (button(stage02botan, botan*1.4, text, U"これ!!", shiro, stagebotantextSize, midori, true, false)) {
	//	//	//	//ここのステージで使える素材の受け取り.
	//	//	//	if (colorchange) {
	//	//	//		Fcolor = colorchangecolor_Lv02;
	//	//	//	}
	//	//	//	else {
	//	//	//		Fcolor = color_Lv02;
	//	//	//	}
	//	//	//	Ftext = text_Lv02;
	//	//	//	stageNum = STAGE02;

	//	//	//	//ルール決め.
	//	//	//	if (randInt() % 2) {
	//	//	//		//色でわける.
	//	//	//		scs = ScoreSwitch::ColorRule;
	//	//	//		ss = SceneSwitch::Letsplay;
	//	//	//		break;
	//	//	//	}
	//	//	//	//形でわける.
	//	//	//	scs = ScoreSwitch::ShapeRule;
	//	//	//	ss = SceneSwitch::Letsplay;
	//	//	//}
	//	//	////難易度MAX.
	//	//	//if (button(stageMAXbotan, botan*1.4, text, U"これ!!", shiro, stagebotantextSize, midori, true, false)) {
	//	//	//	//ここのステージで使える素材の受け取り.
	//	//	//	stageNum = STAGEMAX;
	//	//	//	if (colorchange) {
	//	//	//		Fcolor = colorchangecolor_LvMAX;
	//	//	//		Ftext = colorchangetext;
	//	//	//	}
	//	//	//	else {
	//	//	//		Fcolor = color_LvMAX;
	//	//	//		Ftext = text_LvMAX;
	//	//	//	}

	//	//	//	//ルール決め.
	//	//	//	uint8 ruleNum = randInt() % 3;
	//	//	//	if (ruleNum == 0) {
	//	//	//		//文字でわける.
	//	//	//		scs = ScoreSwitch::TextRule;
	//	//	//		ss = SceneSwitch::Letsplay;
	//	//	//		break;
	//	//	//	}
	//	//	//	else if (ruleNum == 1) {
	//	//	//		//色でわける.
	//	//	//		scs = ScoreSwitch::ColorRule;
	//	//	//		ss = SceneSwitch::Letsplay;
	//	//	//		break;
	//	//	//	}
	//	//	//	else {
	//	//	//		//形でわける.
	//	//	//		scs = ScoreSwitch::ShapeRule;
	//	//	//		ss = SceneSwitch::Letsplay;
	//	//	//		break;
	//	//	//	}
	//	//	//}

	//	//	break;

	//	//case SceneSwitch::Letsplay: // play 画面.
	//	//{
	//	//	////分別はこ下側.
	//	//	//box_under(ubox_left, Fcolor[left]);
	//	//	//box_under(ubox_mdle, Fcolor[mdle]);
	//	//	//box_under(ubox_rght, Fcolor[rght]);

	//	//	////正誤判定.
	//	//	////時間という概念？の取得.
	//	//	//int32 t_tf = (truefalse.ms() / 30);
	//	//	//switch (tof) {
	//	//	//case TrueOrFalse::WaitSort: //仕分け待ち.
	//	//	//	break;

	//	//	//case TrueOrFalse::TrueSort: //正解した時.
	//	//	//{
	//	//	//	//正解したエフェクト.
	//	//	//	effect_TrueOrFalse(t_tf, comboNum, kuro, text, 30);
	//	//	//	//時間経過で消す.
	//	//	//	if (t_tf > 20) {
	//	//	//		truefalse.reset();
	//	//	//		tof = TrueOrFalse::WaitSort;
	//	//	//	}
	//	//	//	break;
	//	//	//}
	//	//	//case TrueOrFalse::FalseSort: //間違えたとき.
	//	//	//{
	//	//	//	//間違えた時のエフェクト.
	//	//	//	effect_TrueOrFalse(t_tf, comboNum, kuro, text, 30);
	//	//	//	if (t_tf > 20) {
	//	//	//		truefalse.reset();
	//	//	//		tof = TrueOrFalse::WaitSort;
	//	//	//	}
	//	//	//	break;
	//	//	//}
	//	//	//default:
	//	//	//	break;
	//	//	//}

	//	//	////動かす図形.
	//	//	//switch (fs) {
	//	//	//case FigureSwitch::Break: //待機画面.
	//	//	//	break;

	//	//	//case FigureSwitch::MakeFigure: //図形生成.
	//	//	//{
	//	//	//	//生成した回数の記録.
	//	//	//	++classifyNum;

	//	//	//	//図形の出現座標と大きさの代入.
	//	//	//	figure.center = center;
	//	//	//	figure.size = size;
	//	//	//	figure.textSize = textSize;
	//	//	//	figure.textcolor = kuro;
	//	//	//	//図形の色と文字を決める.
	//	//	//	decide_color(figure, stageNum, colorchange);
	//	//	//	decide_text(figure, stageNum, colorchange);
	//	//	//	//図形の形を決める.
	//	//	//	uint8 shapeNum = randInt() % 3;
	//	//	//	if (shapeNum == 0) { //まる.
	//	//	//		circle = { figure.center, figure.size / 2 };
	//	//	//		//さんかく,しかくはなんもなし描画をする.
	//	//	//		triangle = { figure.center.x, figure.center.y, 0 };
	//	//	//		rect = { Arg::center(center_X, center_Y), 0 };
	//	//	//		fs = FigureSwitch::Release;
	//	//	//		break;
	//	//	//	}
	//	//	//	else if (shapeNum == 1) { //さんかく.
	//	//	//		//ちょっと大きくする.
	//	//	//		figure.size *= 1.3;
	//	//	//		triangle = { center_X, center_Y, (double)figure.size };
	//	//	//		//まる,しかくはなんもなし描写をする.
	//	//	//		circle = { figure.center, 0 };
	//	//	//		rect = { Arg::center(center_X, center_Y), 0 };
	//	//	//		//さんかくの時だけ文字の大きさを小さくする.
	//	//	//		figure.textSize *= 0.8;
	//	//	//		fs = FigureSwitch::Release;
	//	//	//		break;
	//	//	//	}
	//	//	//	else if (shapeNum == 2) { //しかく.
	//	//	//		rect = { Arg::center(center_X, center_Y), figure.size };
	//	//	//		//まる,さんかくはなんもなし描写をする.
	//	//	//		circle = { figure.center, 0 };
	//	//	//		triangle = { figure.center.x, figure.center.y, 0 };
	//	//	//		fs = FigureSwitch::Release;
	//	//	//		break;
	//	//	//	}

	//	//	//	break;
	//	//	//}


	//	//	//case FigureSwitch::Release: //図形をつかんでないとき.

	//	//	//	//落とした場所に図形を描写する.
	//	//	//	circle.draw(figure.color);
	//	//	//	circle.drawFrame(haba, kuro);
	//	//	//	triangle.draw(figure.color);
	//	//	//	triangle.drawFrame(haba, kuro);
	//	//	//	rect.draw(figure.color);
	//	//	//	rect.drawFrame(haba, kuro);
	//	//	//	text(figure.text).drawAt(figure.textSize, figure.center, figure.textcolor);

	//	//	//	//図形をつかんだとき.
	//	//	//	/*Print <<U"circle" << circle.mouseOver();
	//	//	//	Print << U"triangle" << triangle.mouseOver();
	//	//	//	Print << U"rectr" << rect.mouseOver();*/
	//	//	//	// triangle の一辺が 0 だと,当たり判定が常に true になるバグあり.
	//	//	//	if ((circle.mouseOver() || (triangle.mouseOver() && culc_Length(triangle) != 0) || rect.mouseOver()) && not pause) {
	//	//	//		//手にする.
	//	//	//		Cursor::RequestStyle(CursorStyle::Hand);

	//	//	//		if (MouseL.pressed()) {

	//	//	//			//カーソルと図形の中心座標の差をとる.
	//	//	//			distance_x = figure.center.x - Cursor::Pos().x;
	//	//	//			distance_y = figure.center.y - Cursor::Pos().y;

	//	//	//			fs = FigureSwitch::Catch;
	//	//	//		}
	//	//	//	}

	//	//	//	break;

	//	//	//case FigureSwitch::Catch: //図形をつかんで運ぶとき.

	//	//	//	Cursor::RequestStyle(CursorStyle::Hand);
	//	//	//	//移動させる.
	//	//	//	if (MouseL.pressed()) {
	//	//	//		Circle{ check_wallx(wallx, Cursor::Pos().x + distance_x, figure), check_wally(wally, Cursor::Pos().y + distance_y, figure), circle.r }.draw(figure.color);
	//	//	//		Circle{ check_wallx(wallx, Cursor::Pos().x + distance_x, figure), check_wally(wally, Cursor::Pos().y + distance_y, figure), circle.r }.drawFrame(haba, kuro);
	//	//	//		Triangle{ (double)check_wallx(wallx, Cursor::Pos().x + distance_x, figure), (double)check_wally(wally, Cursor::Pos().y + distance_y, figure), culc_Length(triangle) }.draw(figure.color);
	//	//	//		Triangle{ (double)check_wallx(wallx, Cursor::Pos().x + distance_x, figure), (double)check_wally(wally, Cursor::Pos().y + distance_y, figure), culc_Length(triangle) }.drawFrame(haba, kuro);
	//	//	//		RectF{ Arg::center(check_wallx(wallx, Cursor::Pos().x + distance_x, figure), check_wally(wally, Cursor::Pos().y + distance_y, figure)), rect.size }.draw(figure.color);
	//	//	//		RectF{ Arg::center(check_wallx(wallx, Cursor::Pos().x + distance_x, figure), check_wally(wally, Cursor::Pos().y + distance_y, figure)), rect.size }.drawFrame(haba, kuro);
	//	//	//		text(figure.text).drawAt(figure.textSize, check_wallx(wallx, Cursor::Pos().x + distance_x, figure), check_wally(wally, Cursor::Pos().y + distance_y, figure), figure.textcolor);
	//	//	//	}
	//	//	//	//図形を離したとき.
	//	//	//	if (MouseL.up()) {
	//	//	//		//図形を書いて穴埋め.
	//	//	//		Circle{ check_wallx(wallx, Cursor::Pos().x + distance_x, figure), check_wally(wally, Cursor::Pos().y + distance_y, figure), circle.r }.draw(figure.color);
	//	//	//		Circle{ check_wallx(wallx, Cursor::Pos().x + distance_x, figure), check_wally(wally, Cursor::Pos().y + distance_y, figure), circle.r }.drawFrame(haba, kuro);
	//	//	//		Triangle{ (double)check_wallx(wallx, Cursor::Pos().x + distance_x, figure), (double)check_wally(wally, Cursor::Pos().y + distance_y, figure), culc_Length(triangle) }.draw(figure.color);
	//	//	//		Triangle{ (double)check_wallx(wallx, Cursor::Pos().x + distance_x, figure), (double)check_wally(wally, Cursor::Pos().y + distance_y, figure), culc_Length(triangle) }.drawFrame(haba, kuro);
	//	//	//		RectF{ Arg::center(check_wallx(wallx, Cursor::Pos().x + distance_x, figure), check_wally(wally, Cursor::Pos().y + distance_y, figure)), rect.size }.draw(figure.color);
	//	//	//		RectF{ Arg::center(check_wallx(wallx, Cursor::Pos().x + distance_x, figure), check_wally(wally, Cursor::Pos().y + distance_y, figure)), rect.size }.drawFrame(haba, kuro);
	//	//	//		text(figure.text).drawAt(figure.textSize, check_wallx(wallx, Cursor::Pos().x + distance_x, figure), check_wally(wally, Cursor::Pos().y + distance_y, figure), figure.textcolor);
	//	//	//		//図形の中心座標を離した座標に更新.
	//	//	//		figure.center.x = check_wallx(wallx, Cursor::Pos().x + distance_x, figure);
	//	//	//		figure.center.y = check_wally(wally, Cursor::Pos().y + distance_y, figure);
	//	//	//		circle.center = figure.center;
	//	//	//		triangle = { figure.center, culc_Length(triangle) };
	//	//	//		rect.x = culc_lx(figure);
	//	//	//		rect.y = culc_ly(figure);
	//	//	//		fs = FigureSwitch::Release;
	//	//	//		break;
	//	//	//	}

	//	//	//	break;

	//	//	//default:
	//	//	//	break;
	//	//	//}

	//	//	////分別はこ上側.
	//	//	//box_over(obox_left, Fcolor[left], text, U"●");
	//	//	//text(U"\n{}"_fmt(Ftext[left])).drawAt(obox_left.x + obox_left.w / 2, obox_left.y + obox_left.h * 3 / 5, kuro);
	//	//	//box_over(obox_mdle, Fcolor[mdle], text, U"▲");
	//	//	//text(U"\n{}"_fmt(Ftext[mdle])).drawAt(obox_mdle.x + obox_mdle.w / 2, obox_mdle.y + obox_mdle.h * 3 / 5, kuro);
	//	//	//box_over(obox_rght, Fcolor[rght], text, U"■");
	//	//	//text(U"\n{}"_fmt(Ftext[rght])).drawAt(obox_rght.x + obox_rght.w / 2, obox_rght.y + obox_rght.h * 3 / 5, kuro);
	//	//	////制限時間.
	//	//	//gt = playtime.s();
	//	//	//text(U"time(s):{}"_fmt(timelimit - gt)).draw(20, 60, kuro);
	//	//	////時間切れになったとき.
	//	//	//if (timelimit - gt <= 0) {
	//	//	//	playtime.reset();
	//	//	//	gt = 0;
	//	//	//	ss = SceneSwitch::Result;
	//	//	//	resultwindow.restart();
	//	//	//	//ハイスコアを更新したかどうかの記録.
	//	//	//	if (highscore[stageNum] < score) {
	//	//	//		highscore[stageNum] = score;
	//	//	//		newrecord = true;
	//	//	//	}
	//	//	//	//得点がマイナスになっていた場合 0 にする.
	//	//	//	if (score < 0) {
	//	//	//		score = 0;
	//	//	//	}
	//	//	//	break;
	//	//	//}

	//	//	////スコア.
	//	//	//switch (scs) {
	//	//	//case ScoreSwitch::ShapeRule: //形で分ける.

	//	//	//	if (ruletext) {
	//	//	//		text(U"かたちで仕分け!!").drawAt(siwakesize, siwakerule, kuro);
	//	//	//	}

	//	//	//	// left は,まる.
	//	//	//	if (circle.intersects(ubox_left) || rect.intersects(ubox_left) || triangle.intersects(ubox_left)) {
	//	//	//		if (circle.r != 0) {
	//	//	//			//加点する.
	//	//	//			score += Score[stageNum][plus];
	//	//	//			//正解の回数の記録.
	//	//	//			++correctNum;
	//	//	//			//連続正解の回数を記録.
	//	//	//			++comboNum;
	//	//	//			//正解エフェクトを出す.
	//	//	//			tof = TrueOrFalse::TrueSort;
	//	//	//		}
	//	//	//		else {
	//	//	//			//減点する.
	//	//	//			score += Score[stageNum][minus];
	//	//	//			//ミスした回数の記録.
	//	//	//			++missNum;
	//	//	//			//連続正解の回数を 0 に戻す.
	//	//	//			comboNum = 0;
	//	//	//			//間違えたエフェクトを出すへ.
	//	//	//			tof = TrueOrFalse::FalseSort;
	//	//	//		}
	//	//	//		//新たに図形を作る.
	//	//	//		fs = FigureSwitch::MakeFigure;
	//	//	//		//正誤判定の動きの再始動.
	//	//	//		truefalse.restart();
	//	//	//		break;
	//	//	//	}
	//	//	//	// mdle は,さんかく.
	//	//	//	if (circle.intersects(ubox_mdle) || rect.intersects(ubox_mdle) || triangle.intersects(ubox_mdle)) {
	//	//	//		if (culc_Length(triangle) != 0) {
	//	//	//			score += Score[stageNum][plus];
	//	//	//			++correctNum;
	//	//	//			++comboNum;
	//	//	//			tof = TrueOrFalse::TrueSort;
	//	//	//		}
	//	//	//		else {
	//	//	//			score += Score[stageNum][minus];
	//	//	//			++missNum;
	//	//	//			comboNum = 0;
	//	//	//			tof = TrueOrFalse::FalseSort;
	//	//	//		}
	//	//	//		fs = FigureSwitch::MakeFigure;
	//	//	//		//正誤判定の動きの再始動.
	//	//	//		truefalse.restart();
	//	//	//		break;
	//	//	//	}
	//	//	//	// right は,しかく.
	//	//	//	if (circle.intersects(ubox_rght) || rect.intersects(ubox_rght) || triangle.intersects(ubox_rght)) {
	//	//	//		if (rect.w != 0) {
	//	//	//			score += Score[stageNum][plus];
	//	//	//			++correctNum;
	//	//	//			++comboNum;
	//	//	//			tof = TrueOrFalse::TrueSort;
	//	//	//		}
	//	//	//		else {
	//	//	//			score += Score[stageNum][minus];
	//	//	//			++missNum;
	//	//	//			comboNum = 0;
	//	//	//			tof = TrueOrFalse::FalseSort;
	//	//	//		}
	//	//	//		fs = FigureSwitch::MakeFigure;
	//	//	//		//正誤判定の動きの再始動.
	//	//	//		truefalse.restart();
	//	//	//		break;
	//	//	//	}

	//	//	//	break;
	//	//	//case ScoreSwitch::ColorRule: //色で分ける.

	//	//	//	if (ruletext) {
	//	//	//		text(U"いろで仕分け!!").drawAt(siwakesize, siwakerule, kuro);
	//	//	//	}

	//	//	//	// left は,赤.
	//	//	//	if (circle.intersects(ubox_left) || rect.intersects(ubox_left) || triangle.intersects(ubox_left)) {
	//	//	//		if (figure.color == aka || (colorchange && figure.color == red)) {
	//	//	//			score += Score[stageNum][plus];
	//	//	//			++correctNum;
	//	//	//			++comboNum;
	//	//	//			tof = TrueOrFalse::TrueSort;
	//	//	//		}
	//	//	//		else {
	//	//	//			score += Score[stageNum][minus];
	//	//	//			++missNum;
	//	//	//			comboNum = 0;
	//	//	//			tof = TrueOrFalse::FalseSort;
	//	//	//		}
	//	//	//		fs = FigureSwitch::MakeFigure;
	//	//	//		//正誤判定の動きの再始動.
	//	//	//		truefalse.restart();
	//	//	//		break;
	//	//	//	}
	//	//	//	// mdle は,緑.
	//	//	//	if (circle.intersects(ubox_mdle) || rect.intersects(ubox_mdle) || triangle.intersects(ubox_mdle)) {
	//	//	//		if (figure.color == midori || (colorchange && figure.color == yelow)) {
	//	//	//			score += Score[stageNum][plus];
	//	//	//			++correctNum;
	//	//	//			++comboNum;
	//	//	//			tof = TrueOrFalse::TrueSort;
	//	//	//		}
	//	//	//		else {
	//	//	//			score += Score[stageNum][minus];
	//	//	//			++missNum;
	//	//	//			comboNum = 0;
	//	//	//			tof = TrueOrFalse::FalseSort;
	//	//	//		}
	//	//	//		fs = FigureSwitch::MakeFigure;
	//	//	//		//正誤判定の動きの再始動.
	//	//	//		truefalse.restart();
	//	//	//		break;
	//	//	//	}
	//	//	//	// right は,青.
	//	//	//	if (circle.intersects(ubox_rght) || rect.intersects(ubox_rght) || triangle.intersects(ubox_rght)) {
	//	//	//		if (figure.color == ao || (colorchange && figure.color == blue)) {
	//	//	//			score += Score[stageNum][plus];
	//	//	//			++correctNum;
	//	//	//			++comboNum;
	//	//	//			tof = TrueOrFalse::TrueSort;
	//	//	//		}
	//	//	//		else {
	//	//	//			score += Score[stageNum][minus];
	//	//	//			++missNum;
	//	//	//			comboNum = 0;
	//	//	//			tof = TrueOrFalse::FalseSort;
	//	//	//		}
	//	//	//		fs = FigureSwitch::MakeFigure;
	//	//	//		//正誤判定の動きの再始動.
	//	//	//		truefalse.restart();
	//	//	//		break;
	//	//	//	}

	//	//	//	break;

	//	//	//case ScoreSwitch::TextRule: //文字で分ける.

	//	//	//	if (ruletext) {
	//	//	//		text(U"もじで仕分け!!").drawAt(siwakesize, siwakerule, kuro);
	//	//	//	}

	//	//	//	// left は,"あか".
	//	//	//	if (circle.intersects(ubox_left) || rect.intersects(ubox_left) || triangle.intersects(ubox_left)) {
	//	//	//		if (figure.text == U"あか" || (colorchange && figure.text == U"まる")) {
	//	//	//			score += Score[stageNum][plus];
	//	//	//			++correctNum;
	//	//	//			++comboNum;
	//	//	//			tof = TrueOrFalse::TrueSort;
	//	//	//		}
	//	//	//		else {
	//	//	//			score += Score[stageNum][minus];
	//	//	//			++missNum;
	//	//	//			comboNum = 0;
	//	//	//			tof = TrueOrFalse::FalseSort;
	//	//	//		}
	//	//	//		fs = FigureSwitch::MakeFigure;
	//	//	//		//正誤判定の動きの再始動.
	//	//	//		truefalse.restart();
	//	//	//		break;
	//	//	//	}
	//	//	//	// mdle は,"みどり".
	//	//	//	if (circle.intersects(ubox_mdle) || rect.intersects(ubox_mdle) || triangle.intersects(ubox_mdle)) {
	//	//	//		if (figure.text == U"みどり" || (colorchange && figure.text == U"さんかく")) {
	//	//	//			score += Score[stageNum][plus];
	//	//	//			++correctNum;
	//	//	//			++comboNum;
	//	//	//			tof = TrueOrFalse::TrueSort;
	//	//	//		}
	//	//	//		else {
	//	//	//			score += Score[stageNum][minus];
	//	//	//			++missNum;
	//	//	//			comboNum = 0;
	//	//	//			tof = TrueOrFalse::FalseSort;
	//	//	//		}
	//	//	//		fs = FigureSwitch::MakeFigure;
	//	//	//		//正誤判定の動きの再始動.
	//	//	//		truefalse.restart();
	//	//	//		break;
	//	//	//	}
	//	//	//	// right は,"あお".
	//	//	//	if (circle.intersects(ubox_rght) || rect.intersects(ubox_rght) || triangle.intersects(ubox_rght)) {
	//	//	//		if (figure.text == U"あお" || (colorchange && figure.text == U"しかく")) {
	//	//	//			score += Score[stageNum][plus];
	//	//	//			++correctNum;
	//	//	//			++comboNum;
	//	//	//			tof = TrueOrFalse::TrueSort;
	//	//	//		}
	//	//	//		else {
	//	//	//			score += Score[stageNum][minus];
	//	//	//			++missNum;
	//	//	//			comboNum = 0;
	//	//	//			tof = TrueOrFalse::FalseSort;
	//	//	//		}
	//	//	//		fs = FigureSwitch::MakeFigure;
	//	//	//		//正誤判定の動きの再始動.
	//	//	//		truefalse.restart();
	//	//	//		break;
	//	//	//	}

	//	//	//	break;

	//	//	//default:
	//	//	//	break;
	//	//	//}

	//	//	////説明とカウントダウン画面.
	//	//	//switch (cs) {
	//	//	//case CountSwitch::Break: //待機画面.
	//	//	//	break;
	//	//	//case CountSwitch::ExplainRule: //仕分けルール説明.
	//	//	//	//ちょっと暗くする.
	//	//	//	makuSize.draw(makuColor);
	//	//	//	//説明窓.
	//	//	//	explainWindow.draw(shiro);
	//	//	//	explainWindow.drawFrame(haba, kuro);
	//	//	//	text(U"-ルール説明-").draw(30, explainMain, kuro);
	//	//	//	text(U"「かたち」は\n図形の形").drawAt(26, explainSubShape, kuro);
	//	//	//	text(U"「いろ」は\n図形の色").drawAt(26, explainSubColor, kuro);
	//	//	//	text(U"「もじ」は\n図形の文字").drawAt(26, explainSubText, kuro);

	//	//	//	//区切りの線.
	//	//	//	Line{ explainLineLeftBegin, explainLineLeftEnd }.draw(haba, kuro);
	//	//	//	Line{ explainLineRightBegin, explainLineRightEnd }.draw(haba, kuro);

	//	//	//	//飾りの図形.
	//	//	//	explainShapeCircle.draw(mihon_color[1]);
	//	//	//	explainShapeCircle.drawFrame(haba, kuro);
	//	//	//	explainShapeTriangle.draw(mihon_color[1]);
	//	//	//	explainShapeTriangle.drawFrame(haba, kuro);
	//	//	//	explainShapeRect.draw(mihon_color[1]);
	//	//	//	explainShapeRect.drawFrame(haba, kuro);

	//	//	//	explainColorCircle.draw(mihon_color[0]);
	//	//	//	explainColorCircle.drawFrame(haba, kuro);
	//	//	//	explainColorTriangle.draw(mihon_color[1]);
	//	//	//	explainColorTriangle.drawFrame(haba, kuro);
	//	//	//	explainColorRect.draw(mihon_color[2]);
	//	//	//	explainColorRect.drawFrame(haba, kuro);

	//	//	//	text(mihon_text[0]).draw(30, explainTextmaru, kuro);
	//	//	//	text(mihon_text[1]).draw(30, explainTextsankaku, kuro);
	//	//	//	text(mihon_text[2]).draw(30, explainTextshikaku, kuro);

	//	//	//	//次のページに進みたいとき.
	//	//	//	if (button(explainNextButton, makuColor, text, U"→", kuro, 30, kuro, true, pause)) {
	//	//	//		cs = CountSwitch::ExplainSousa;
	//	//	//	}

	//	//	//	break;

	//	//	//case CountSwitch::ExplainSousa: //図形の動かし方の説明.
	//	//	//	//ちょっと暗くする.
	//	//	//	makuSize.draw(makuColor);
	//	//	//	//説明窓.
	//	//	//	explainWindow.draw(shiro);
	//	//	//	explainWindow.drawFrame(haba, kuro);
	//	//	//	text(U"-操作方法-").draw(30, explainMain, kuro);
	//	//	//	text(U"左クリックでつかんで移動!!").drawAt(30, 400, 300, kuro);

	//	//	//	// OK ボタンを押したとき.
	//	//	//	if (button(explainOK, makuColor, text, U"OK", shiro, 30, kuro, true, pause)) {
	//	//	//		cs = CountSwitch::Start;
	//	//	//	}
	//	//	//	//仕訳ルールの説明に戻りたいとき.
	//	//	//	if (button(explainBackButton, makuColor, text, U"←", kuro, 30, kuro, true, pause)) {
	//	//	//		cs = CountSwitch::ExplainRule;
	//	//	//	}

	//	//	//	break;

	//	//	//case CountSwitch::Start: //スタートボタンを押す.
	//	//	//	//ちょっと暗くする.
	//	//	//	makuSize.draw(makuColor);
	//	//	//	// START ボタンがクリックできることを分かりやすく.
	//	//	//	text(U"クリックしてスタート").drawAt(16, 400, 340, kuro);
	//	//	//	// START ボタン.
	//	//	//	if (button(startbotan, kuro, text, U"START", shiro, 30, kuro, true, pause)) {
	//	//	//		//仕訳ルールを表示する.
	//	//	//		ruletext = true;
	//	//	//		countdown.restart();
	//	//	//		playtime.reset();
	//	//	//		//スコアの初期化.
	//	//	//		score = 0;
	//	//	//		//仕分けた個数.
	//	//	//		classifyNum = 0;
	//	//	//		//正解した個数.
	//	//	//		correctNum = 0;
	//	//	//		//間違えた個数.
	//	//	//		missNum = 0;
	//	//	//		//連続正解の回数.
	//	//	//		comboNum = 0;
	//	//	//		//記録を更新するか.
	//	//	//		newrecord = false;
	//	//	//		cs = CountSwitch::Countdown;
	//	//	//		break;
	//	//	//	}
	//	//	//	break;

	//	//	//case CountSwitch::Countdown: //スタートのカウントダウン.
	//	//	//{
	//	//	//	t_cd = countdown.sF();
	//	//	//	const double t_cdmaku = Min(countdown.sF() / 2, 1.0);
	//	//	//	//開幕演出.
	//	//	//	m_boxOutQuad_adu(t_cdmaku, makuSize, makuColor);
	//	//	//	if (t_cd <= 1) {
	//	//	//		text(U"3").drawAt(countdownsize, countdownpoint, kuro);
	//	//	//		//ルールの読み忘れを無くす矢印.
	//	//	//		text(U"↑").drawAt(50, yondeyoLeft, kuro);
	//	//	//		text(U"↑").drawAt(50, yondeyoRight, kuro);
	//	//	//		break;
	//	//	//	}
	//	//	//	else if (1 < t_cd && t_cd <= 2) {
	//	//	//		text(U"2").drawAt(countdownsize, countdownpoint, kuro);
	//	//	//		break;
	//	//	//	}
	//	//	//	else if (2 < t_cd && t_cd <= 3) {
	//	//	//		text(U"1").drawAt(countdownsize, countdownpoint, kuro);
	//	//	//		//ルールの読み忘れを無くす矢印.
	//	//	//		text(U"↑").drawAt(50, yondeyoLeft, kuro);
	//	//	//		text(U"↑").drawAt(50, yondeyoRight, kuro);
	//	//	//		break;
	//	//	//	}
	//	//	//	else if (3 < t_cd && t_cd <= 4) {
	//	//	//		text(U"START!!").drawAt(countdownsize, countdownpoint, kuro);
	//	//	//	}
	//	//	//	if (4 < t_cd) {
	//	//	//		countdown.reset();
	//	//	//		t_cd = 0.0;
	//	//	//		cs = CountSwitch::Break;
	//	//	//		fs = FigureSwitch::MakeFigure;
	//	//	//		//制限時間の開始.
	//	//	//		playtime.restart();
	//	//	//		break;
	//	//	//	}
	//	//	//	break;
	//	//	//}
	//	//	//default:
	//	//	//	break;
	//	//	//}

	//	//	////中断するボタン.
	//	//	//switch (ps) {
	//	//	//case PauseSwitch::BackButton: //一時停止ボタン.
	//	//	//	if (button(stopbotan, murasaki, text, U"←", shiro, 30, kuro, true, false)) {
	//	//	//		playtime.pause();
	//	//	//		countdown.pause();
	//	//	//		pause = true;
	//	//	//		ps = PauseSwitch::PauseWindow;
	//	//	//		break;
	//	//	//	}
	//	//	//	break;
	//	//	//case PauseSwitch::PauseWindow: //中断ボタンを押したとき.

	//	//	//	//一時停止のウィンドウ.
	//	//	//	pauseWindow.draw(ColorF{ 0.7, 0.7, 0.7, 0.8 });
	//	//	//	pauseWindow.drawFrame(haba, kuro);
	//	//	//	text(U"--PAUSE--").drawAt(40, (pauseWindow.x + pauseWindow.w / 2), (pauseWindow.y + pauseWindow.h / 3), kuro);
	//	//	//	//やめる.
	//	//	//	if (button(pauseRetire, daidai, text, U"ステージに戻る", kuro, 20, kuro, true, false)) {
	//	//	//		ss = SceneSwitch::Stage;
	//	//	//		if (explainSkip) {
	//	//	//			cs = CountSwitch::Start;
	//	//	//		}
	//	//	//		else {
	//	//	//			cs = CountSwitch::ExplainRule;
	//	//	//		}
	//	//	//		fs = FigureSwitch::Break;
	//	//	//		score = 0;
	//	//	//		gt = 0;
	//	//	//		comboNum = 0;
	//	//	//		playtime.reset();
	//	//	//		countdown.reset();
	//	//	//		ruletext = false;
	//	//	//		pause = false;
	//	//	//		ps = PauseSwitch::BackButton;
	//	//	//		break;
	//	//	//	}
	//	//	//	//再開する.
	//	//	//	//もう一回 ← ボタンを押して戻れてもいいよね.
	//	//	//	if (button(pauseContinue, daidai, text, U"つづける", kuro, 20, kuro, true, false) || button(stopbotan, murasaki, text, U"←", kuro, 30, kuro, true, false)) {
	//	//	//		playtime.resume();
	//	//	//		countdown.resume();
	//	//	//		pause = false;
	//	//	//		ss = SceneSwitch::Letsplay;
	//	//	//		ps = PauseSwitch::BackButton;
	//	//	//		break;
	//	//	//	}
	//	//	//	break;
	//	//	//default:
	//	//	//	break;
	//	//	//}

	//	//	//break; // play 画面の break.
	//	//}

	//	//case SceneSwitch::Result: //結果発表画面.
	//	//{
	//	//		////時間という概念？の取得.
	//	//		//const double t_rw = Min(resultwindow.sF(), 1.0);
	//	//		//const double t_rt01 = Min(resulttext01.sF(), 1.0);
	//	//		//const double t_rt02 = Min(resulttext02.sF(), 1.0);
	//	//		//const double t_rt03 = Min(resulttext03.sF(), 1.0);
	//	//		//if (t_rw < 1.0) {
	//	//		//	resulttext01.restart();
	//	//		//}
	//	//		//if (t_rt01 < 0.1) {
	//	//		//	resulttext02.restart();
	//	//		//}
	//	//		//if (t_rt02 < 0.1) {
	//	//		//	resulttext03.restart();
	//	//		//}

	//	//		////さっきまでの背景たち.
	//	//		////分別はこ下側.
	//	//		//box_under(ubox_left, Fcolor[left]);
	//	//		//box_under(ubox_mdle, Fcolor[mdle]);
	//	//		//box_under(ubox_rght, Fcolor[rght]);
	//	//		////図形たち.
	//	//		//circle.draw(figure.color);
	//	//		//circle.drawFrame(haba, kuro);
	//	//		//triangle.draw(figure.color);
	//	//		//triangle.drawFrame(haba, kuro);
	//	//		//rect.draw(figure.color);
	//	//		//rect.drawFrame(haba, kuro);
	//	//		//text(figure.text).drawAt(figure.textSize, figure.center, figure.textcolor);
	//	//		////分別はこ上側.
	//	//		//box_over(obox_left, Fcolor[left], text, U"●");
	//	//		//text(U"\n{}"_fmt(Ftext[left])).drawAt(obox_left.x + obox_left.w / 2, obox_left.y + obox_left.h * 3 / 5, kuro);
	//	//		//box_over(obox_mdle, Fcolor[mdle], text, U"▲");
	//	//		//text(U"\n{}"_fmt(Ftext[mdle])).drawAt(obox_mdle.x + obox_mdle.w / 2, obox_mdle.y + obox_mdle.h * 3 / 5, kuro);
	//	//		//box_over(obox_rght, Fcolor[rght], text, U"■");
	//	//		//text(U"\n{}"_fmt(Ftext[rght])).drawAt(obox_rght.x + obox_rght.w / 2, obox_rght.y + obox_rght.h * 3 / 5, kuro);

	//	//		////幕を下ろす.
	//	//		//m_boxBounce_aud(t_rw, makuSize, makuColor);

	//	//		////結果表示.
	//	//		////結果.
	//	//		//m_textBounce_aud(t_rw, resultText, text, U"★RESULT★", 80);
	//	//		////獲得スコア.
	//	//		//m_textBounce_aud(t_rw, yourscoreText, text, U"Your Score:{}"_fmt(score), 36);
	//	//		////ハイスコア.
	//	//		//m_textBounce_aud(t_rw, highscoreText, text, U"High Score:{}"_fmt(highscore[stageNum]), 20);
	//	//		////記録を更新したか.
	//	//		//if (newrecord) {
	//	//		//	m_textBounce_aud(t_rw, newrecordText, text, U"New Record!!", 20);
	//	//		//}
	//	//		////最大コンボ数.
	//	//		////m_textOutExpo_aap(t_rt01, sortedTextAppearPoint, sortedText, kuro, text, U"combo:{}"_fmt(comboNum), 30);
	//	//		////何個仕分けをしたか.
	//	//		//m_textOutExpo_aap(t_rt01, sortedTextAppearPoint, sortedText, kuro, text, U"sorted:{}"_fmt(classifyNum - 1), 30);
	//	//		////何個仕分けを正しくできたか.
	//	//		//m_textOutExpo_aap(t_rt02, trueTextAppearPoint, trueText, kuro, text, U"true:{}"_fmt(correctNum), 30);
	//	//		////何個ミスをしたか.
	//	//		//m_textOutExpo_aap(t_rt03, missTextAppearPoint, missText, kuro, text, U"miss:{}"_fmt(missNum), 30);

	//	//		////もう一度.
	//	//		//if (m_buttonOutExpo_aap(t_rt01, onemoreAppearPoint, onemore, kiiro, text, U"もう一回", 30, kiiro*0.9)) {
	//	//		//	ss = SceneSwitch::Letsplay;
	//	//		//	if (explainSkip) {
	//	//		//		cs = CountSwitch::Start;
	//	//		//	}
	//	//		//	else {
	//	//		//		cs = CountSwitch::ExplainRule;
	//	//		//	}
	//	//		//	fs = FigureSwitch::Break;
	//	//		//	score = 0;
	//	//		//	ruletext = false;
	//	//		//	resultwindow.reset();
	//	//		//	resulttext01.reset();
	//	//		//	resulttext02.reset();
	//	//		//	resulttext03.reset();
	//	//		//	break;
	//	//		//}
	//	//		////ステージを選び直す.
	//	//		//if (m_buttonOutExpo_aap(t_rt02, backstageAppearPoint, backstage, kiiro, text, U"ステージへ", 30, kiiro*0.9)) {
	//	//		//	ss = SceneSwitch::Stage;
	//	//		//	if (explainSkip) {
	//	//		//		cs = CountSwitch::Start;
	//	//		//	}
	//	//		//	else {
	//	//		//		cs = CountSwitch::ExplainRule;
	//	//		//	}
	//	//		//	fs = FigureSwitch::Break;
	//	//		//	score = 0;
	//	//		//	ruletext = false;
	//	//		//	resultwindow.reset();
	//	//		//	resulttext01.reset();
	//	//		//	resulttext02.reset();
	//	//		//	resulttext03.reset();
	//	//		//	break;
	//	//		//}
	//	//		////タイトルに戻る.
	//	//		//if (m_buttonOutExpo_aap(t_rt03, backtitleAppearPoint, backtitle, murasaki*1.4, text, U"タイトルへ", 30, murasaki)) {
	//	//		//	ss = SceneSwitch::Title;
	//	//		//	if (explainSkip) {
	//	//		//		cs = CountSwitch::Start;
	//	//		//	}
	//	//		//	else {
	//	//		//		cs = CountSwitch::ExplainRule;
	//	//		//	}
	//	//		//	fs = FigureSwitch::Break;
	//	//		//	score = 0;
	//	//		//	ruletext = false;
	//	//		//	resultwindow.reset();
	//	//		//	resulttext01.reset();
	//	//		//	resulttext02.reset();
	//	//		//	resulttext03.reset();
	//	//		//	break;
	//	//		//}

	//	//		break;
	//	//}

	//	//default:
	//	//	break;
	//	//}
	//}
}
