#include <bangtal>
#include <iostream>
#include <vector>
using namespace bangtal;
using namespace std;

struct Product {

	string name;
	int price;
};

void pick_client(ObjectPtr object) {
	int type = rand() % 6 + 1;
	string client = "images/손님" + to_string(type) + ".png";
	object->setImage(client);
}

int pick_cash(ObjectPtr object, int num) {
	int return_value = 0;
	vector <int> Vector_cash{ 2000, 3000, 5000, 10000, 15000, 20000 };
	for (int v_num = 0; v_num < 6; v_num++) {
		if (num > Vector_cash[v_num]) {
			continue;
		}
		else {
			return_value = Vector_cash[v_num];
			string cash_name = "images/돈/" + to_string(return_value) + "원.png";
			object->setImage(cash_name);
			cout << "cash: " << Vector_cash[v_num] << endl;
			break;
		}

	}
	object->show();
	return return_value;
}

void showingStatus(int num) {
	string showChange = "지금은 " + to_string(num) + "원입니다.";
	showMessage(showChange);
}


int main() {

	struct Product product[25]{

		{"bread0", 1600},
		{"bread1", 1500},
		{"bread2", 2000},
		{"bread3", 2300},
		{"bread4", 1800},
		{"bread5", 2000},
		{"bread6", 2900},
		{"bread7", 2100},
		{"bread8", 1200},
		{"bread9", 2800},
		{"bread10", 1400},
		{"bread11", 4500},
		{"bread12", 5500},
		{"bread13", 6500},
		{"bread14", 3500},
		{"bread15", 5500},
		{"bread16", 2000},
		{"bread17", 6000},
		{"bread18", 1800},
		{"bread19", 2500},
		{"bread20", 2500},
		{"bread21", 1500},
		{"bread22", 3000},
		{"bread23", 2000},
		{"bread24", 2000}


	};

	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

	/*Scene 선언부*/
	auto scene_main = Scene::create("", "images/메인화면.png");
	auto scene_select = Scene::create("", "images/난이도선택.png");
	auto scene_game = Scene::create("", "images/game_play.png");
	auto scene_guide = Scene::create("", "images/게임설명판.png");
	auto scene_menu = Scene::create("", "images/메뉴판.png");


	/*scene_main*/
	auto button_start = Object::create("images/게임시작.png", scene_main, 200, 310);
	button_start->setScale(0.8f);
	auto button_guide = Object::create("images/게임설명.png", scene_main, 500, 310);
	button_guide->setScale(0.8f);
	auto button_end = Object::create("images/게임종료.png", scene_main, 800, 310);
	button_end->setScale(0.8f);

	button_start->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene_select->enter();
		return true;
		});

	button_guide->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene_guide->enter();
		return true;
		});

	/*scene_guide*/
	auto exit_guide = Object::create("images/exit.png", scene_guide, 1100, 100);
	exit_guide->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene_main->enter();
		return true;
		});

	/*scene_menu*/
	auto bread_menu = Object::create("images/빵메뉴판.png", scene_menu, 115, 62);
	auto bread_button = Object::create("images/빵버튼.png", scene_menu, 60, 420);
	auto sand_button = Object::create("images/샌드버튼.png", scene_menu, 60, 350);
	auto other_button = Object::create("images/기타버튼.png", scene_menu, 60, 270);
	auto menu_board = Object::create("images/메뉴팻말.png", scene_menu, 454, 534);
	auto exit_menu = Object::create("images/exit.png", scene_menu, 1100, 100);

	bread_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		bread_menu->setImage("images/빵메뉴판.png");
		return true;
		});

	sand_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		bread_menu->setImage("images/샌드위치메뉴판.png");
		return true;
		});

	other_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		bread_menu->setImage("images/기타메뉴판.png");
		return true;
		});

	exit_menu->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene_game->enter();
		return true;
		});

	/*guest*/
	auto ano_guest = Object::create("images/익명.png", scene_game, 200, 600);
	auto text_ballon = Object::create("images/말풍선.png", scene_game, 500, 450);

	/*cash*/
	auto cash_image = Object::create("images/돈.png", scene_game, 500, 600);

	/*scene_select*/
	auto easy_select = Object::create("images/easy.png", scene_select, 400, 400);
	easy_select->setScale(1.5f);
	auto normal_select = Object::create("images/normal.png", scene_select, 400, 250);
	normal_select->setScale(1.5f);
	auto hard_select = Object::create("images/hard.png", scene_select, 400, 100);
	hard_select->setScale(1.5f);

	/*mode value*/
	int selected_num;
	int loop_easy = 10;
	int loop_normal = 20;
	int loop_hard = 30;

	/*price computation value*/
	int cash = 0; //손님이 내는 돈
	int change = 0; //거스름돈
	int total = 0; //내야하는 돈(빵 값)
	vector <int> bread_price[3];
	vector <ObjectPtr> bread_image[3];

	easy_select->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		selected_num = 0;
		scene_game->enter();
		loop_easy--;

		/*client*/
		pick_client(ano_guest);

		/*빵개수 랜덤*/
		const int iter = rand() % 3 + 1;

		/*빵 15개 종류 중 랜덤하게 받은 개수만큼 vector에 넣어줌*/
		for (int i = 0; i < iter; i++) {
			int type = rand() % 15;//빵:0.png~14.png
			auto bread = Object::create("images/빵/" + product[type].name + ".png", scene_game, 130 + i * 150, 200, true);
			bread_image->push_back(bread);
			bread_price->push_back(product[type].price);

		}

		/*total*/
		for (int i = 0; i < iter; i++) {
			total += bread_price->back();
			bread_price->pop_back();
		}
		std::cout << "total: " << total << endl;

		/*cash*/
		cash = pick_cash(cash_image, total);

		return true;
		});


	normal_select->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		selected_num = 1;
		return true;
		scene_game->enter();
		});

	hard_select->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		selected_num = 2;
		scene_game->enter();
		return true;
		});

	/*button*/
	auto menu_button = Object::create("images/메뉴확인.png", scene_game, 1150, 100);
	menu_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene_menu->enter();
		return true;
		});

	auto up_for_5000 = Object::create("images/up_button.png", scene_game, 932, 273);
	auto down_for_5000 = Object::create("images/down_button.png", scene_game, 932, 238);
	auto up_for_1000 = Object::create("images/up_button.png", scene_game, 984, 273);
	auto down_for_1000 = Object::create("images/down_button.png", scene_game, 984, 238);
	auto up_for_500 = Object::create("images/up_button.png", scene_game, 1036, 273);
	auto down_for_500 = Object::create("images/down_button.png", scene_game, 1036, 238);
	auto up_for_100 = Object::create("images/up_button.png", scene_game, 1088, 273);
	auto down_for_100 = Object::create("images/down_button.png", scene_game, 1088, 238);
	auto done = Object::create("images/done.png", scene_game, 1040, 210);
	auto reset = Object::create("images/reset.png", scene_game, 930, 210);


	done->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (loop_easy > 0 || loop_normal > 0 || loop_hard > 0) {
			if (change == cash - total) {
				loop_easy--;
				showMessage("계산 성공!");
			}
			else {
				showMessage("계산 실패!");
			}

			/*초기화*/
			cash_image->hide();
			cash = 0;
			change = 0;
			total = 0;
			while (!bread_image->empty()) {
				bread_image->back()->hide();
				bread_image->pop_back();
			}

			pick_client(ano_guest);//손님 이미지 랜덤으로 보이게

			/*빵 오브젝트, 가격 저장*/
			vector <int> bread_price[3];
			const int iter = rand() % 3 + 1;
			std::cout << "iter: " << iter << endl;
			for (int i = 0; i < iter; i++) {
				int type = 0;
				if (selected_num == 0) type = rand() % 11;
				else if (selected_num == 1) type = rand() % 18;
				else if (selected_num == 2) type = rand() % 25;
				string name = "images/빵/bread" + to_string(type) + ".png";
				auto bread = Object::create("images/빵/" + product[type].name + ".png", scene_game, 130 + i * 150, 200, true);
				bread_image->push_back(bread);
				bread_price->push_back(product[type].price);
			}

			for (int i = 0; i < iter; i++) {
				total += bread_price->back();
				bread_price->pop_back();
			}

			/*빵 가격에 맞는 돈 제시*/
			cash = pick_cash(cash_image, total);
			std::cout << "total: " << total << endl;
		}
		else {
			loop_easy = 10;
			loop_normal = 20;
			loop_hard = 30;
			endGame();
		}

		///*빵 오브젝트, 가격 저장*/
		vector <int> bread_price[3];
		const int iter = rand() % 3 + 1;
		std::cout << "iter: " << iter << endl;
		for (int i = 0; i < iter; i++) {
			int type = rand() % 25;
			auto bread = Object::create("images/빵/" + product[type].name + ".png", scene_game, 130 + i * 150, 200);
			bread_image->push_back(bread);
			bread_price->push_back(product[type].price);
		}

		for (int i = 0; i < iter; i++) {
			total += bread_price->back();
			bread_price->pop_back();

		}
		return true;
		});

	up_for_100->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		change += 100;
		showingStatus(change);
		return true;
		});
	up_for_500->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		change += 500;
		showingStatus(change);
		return true;
		});
	up_for_1000->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		change += 1000;
		showingStatus(change);
		return true;
		});
	up_for_5000->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		change += 5000;
		showingStatus(change);
		return true;
		});
	down_for_100->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		change -= 100;
		showingStatus(change);
		return true;
		});
	down_for_500->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		change -= 500;
		showingStatus(change);
		return true;
		});
	down_for_1000->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		change -= 1000;
		showingStatus(change);
		return true;
		});
	down_for_5000->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		change -= 5000;
		showingStatus(change);
		return true;
		});

	startGame(scene_main);
	return 0;
}
