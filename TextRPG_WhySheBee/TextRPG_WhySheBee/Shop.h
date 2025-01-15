#pragma once
class Shop
{
private:
	ItemManager _ItemManager;
	Inventory* PInventory;
	const int UPGRADE_MAX_LEVEL = 4;
	const int ARMOR_UPGRADE_AMOUNT = 15;
	const int ARMOR_UPGRADE_COST = 150;
	const int SWORD_UPGRADE_AMOUNT = 5;
	const int SWORD_UPGRADE_COST = 200;

	/** UI 관련 **/
	ColorPrinter Color;
	ConsoleManager Console;
	
	/** 대사 **/
	const string GREETINGS = "(수염이 덥수룩하고 허리가 살짝 굽어 애처로운 모습의 상점 주인이 힙겹게 인사를 건넨다.)\n상점 주인: 어서...오세요...콜록...오늘은...무슨 일로...?";
	const string FAREWELL = "(상점 주인이 아쉬운 듯 내 얼굴을 흘끔 바라본다.)\n상점 주인: 그렇군요...갈 길이 바쁘시겠지요...그럼...행운을 빕니다...\n(상점 주인의 응원에 힘입어 가벼운 마음으로 상점을 나섰다.)";
	const string SHOP_MENU = "(아래 번호를 입력해 원하는 메뉴로 진입하세요.)\n1 : 아이템 구매\n2 : 아이템 판매\n3 : 장비 강화\n4 : 상점 주인과 차 마시기\n0 : 상점 나가기";
	const string BUY_MENU = "[아이템 구매]\n(현재 소지 골드 : " + to_string(PlayerCharacter::GetPlayer()->GetGold()) + ")\n0 : 상점 메뉴로 돌아가기";

public:
	/** UI 기본 수치 **/
	static const int WINDOW_WIDTH = 118;
	static const int WINDOW_HEIGHT = 28;
	static const int DIALOG_WIDTH = 118;
	static const int DIALOG_HEIGHT = 6;
	static const int CHOICE_WIDTH = 60;
	static const int CHOICE_HEIGHT = 10;
	static const int MENU_NAME_HEIGHT = 5;
	static const int OFFSET = 2;

	// 입력 시 커서 위치
	static const int INPUT_CURSOR_X = 1;
	static const int INPUT_CURSOR_Y = WINDOW_HEIGHT - 1;

	Shop();

	// 상점 기본 관리
	void StartShop();

	// 정해진 위치에 스트링 출력 (+테두리)
	//void DisplayDialogue(const string& dialogue, int startX, int startY, int width, int height, int offsetX, int offsetY);

	void UpgradeEquipment();
	void UpgradeEquipment(Equipment* e, int index);
	int UpgradeSuccessRate(Equipment* e);
	void BuyItems();
	void SellItems();
	void DrinkTea();
};

