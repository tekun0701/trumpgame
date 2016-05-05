#ifndef __TrumpGame__MainScene__
#define __TrumpGame__MainScene__

#include "cocos2d.h"

class MainScene :public cocos2d::Layer
{
protected:
	MainScene();
	virtual ~MainScene();
	bool init() override;

public:
	enum class HighLow
	{
		HIGH,
		LOW
	};
	static cocos2d::Scene* createScene();
	void update(float dt);
	CC_SYNTHESIZE(int, _cardNum, CardNum);
	CC_SYNTHESIZE(float, _second, Second);
	CC_SYNTHESIZE_RETAIN(cocos2d::Sprite *, _cardLeft, CardLeft);
	CC_SYNTHESIZE_RETAIN(cocos2d::Sprite *, _cardRight, CardRight);
	CC_SYNTHESIZE_RETAIN(cocos2d::Label *, _titleLabel, TitleLabel);
	CC_SYNTHESIZE_RETAIN(cocos2d::Menu *, _selectMenu, SelectMenu);
	CREATE_FUNC(MainScene);

private:
	// カードを開けるときに呼び出す
	void openCard(HighLow highLow);
	// カード変更
	void changeCard();
};

#endif