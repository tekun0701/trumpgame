#include "MainScene.h"

USING_NS_CC;

MainScene::MainScene()
:_cardNum(0)
,_second(0)
,_titleLabel(NULL)
, _selectMenu(NULL)

{

}

MainScene::~MainScene()
{

}

Scene* MainScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainScene::create();
	scene->addChild(layer);
	return scene;
}

bool MainScene::init()
{
	if (!Layer::init()){
		return false;
	}
	//乱数初期化
	srand((unsigned int)time(NULL));
	
	// directorを取り出す
	auto director = Director::getInstance();
	// 画面サイズを取り出す
	auto size = director->getWinSize();

	// カード(左)を表示する
	int cardNum = rand() % 13 + 1;
	this->setCardNum(cardNum);
	std::string filename = StringUtils::format("trump/c%02d.png", cardNum);
	auto cardLeft = Sprite::create(filename);
	cardLeft->setPosition(Vec2(size.width / 3.0, size.height / 2.0));
	this->setCardLeft(cardLeft);
	this->addChild(cardLeft);

	// カード(右)を表示する
	auto cardRight = Sprite::create("trump/z01.png");
	cardRight->setPosition(Vec2(size.width / 3.0 * 2.0, size.height / 2.0));
	this->setCardRight(cardRight);
	this->addChild(cardRight);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event){
		return true;
	};

	// タイトルラベルの表示
	auto titleLabel = Label::createWithSystemFont("High and Low", "Market Felt", 48);
	this->setTitleLabel(titleLabel);
	titleLabel->setPosition(Vec2(size.width / 2.0, size.height / 5.0 * 4.0));
	this->addChild(titleLabel);

	// メニューの表示
	auto highButtonLabel = LabelTTF::create("High", "Market Felt", 48);
	auto highButton = MenuItemLabel::create(highButtonLabel, [this](Ref* ref){
		this->openCard(HighLow::HIGH);
	});
	auto lowButtonLabel = LabelTTF::create("Low", "Market Felt", 48);
	auto lowButton = MenuItemLabel::create(lowButtonLabel, [this](Ref* ref){
		this->openCard(HighLow::LOW);
	});

	auto menu = Menu::create(highButton, lowButton, NULL);
	menu->alignItemsHorizontallyWithPadding(60);
	menu->setPosition(Vec2(size.width/2.0, size.height/ 5.0));
	this->setSelectMenu(menu);
	this->addChild(menu);

	this->scheduleUpdate();
	
	return true;
}

void MainScene::update(float dt){
}

void MainScene::openCard(HighLow highLow){
	auto director = Director::getInstance();
	auto size = director->getWinSize();
	// カード(右)を表示する
	int cardNum = rand() % 13 + 1;
	std::string filename = StringUtils::format("trump/c%02d.png", cardNum);
	_cardRight->setTexture(filename);
	// メニューの表示消す
	_selectMenu->setVisible(false);

	std::string status = "";
	if (highLow == HighLow::HIGH && this->getCardNum() < cardNum || 
		highLow == HighLow::LOW && this->getCardNum() > cardNum) {
		status = "WIN!!";
	}
	else{
		status = "LOSE...";
	}
	// 勝敗を表示
	_titleLabel->setString(status);
	// カード番号保存
	this->setCardNum(cardNum);

	//アニメーションを作成
	_cardRight->runAction(Sequence::create(DelayTime::create(2.0),
		CallFunc::create([this]{
		this->changeCard();
	}), NULL));


};

void MainScene::changeCard(){
	std::string filename = StringUtils::format("trump/c%02d.png", this->getCardNum());
	_cardLeft->setTexture(filename);
	_cardRight->setTexture("trump/z01.png");
	_selectMenu->setVisible(true);
	_titleLabel->setString("");
}