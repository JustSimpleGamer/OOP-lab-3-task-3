#include "Header.h"

using namespace std;

ofstream* global_stream;

void main_script(Client& cl, Client::Credit_card& cd, Product* pr, Administator& adm, ofstream& stream)
{
	//Client::Credit_card::number_of_operations;
	int acess_way, way_of_operation;

	global_stream = &stream;

	Print_in_center("<<Вас вітає система обробки платежів \"Платежі\">>");

	cout << endl << "Бажаєте ввійти як клієнт? (1)" << endl << "Бажаєте ввійти як адміністратор? (2)" << endl << "Бажаєте ввійти у режим тестування (3)" << endl << "Оберіть тип входу: ";

	acess_way = check_way(3, 0);

	if (acess_way == 1)
	{
		cout << "Дійсність вашої кредитної картки: ";

		if (cd.get_access() == true)
		{
			cout << "Дісна" << endl;
			if (cd.get_money_on_card() == NULL)
			{
				cout << "Увага! Рахунок онульований" << endl;
			}
			else
			{
				cout << "Кількість грошей на кредитній картці: " << cd.get_money_on_card() << endl;
			}
			cout << "Кредитний ліміт: " << cd.get_credit_limit() << endl;
			cout << "Кредит: " << cd.get_credit() << endl;
			cout << "Кількість проведений операцій: " << cd.get_number_of_operations() << endl << endl;

			cout << "Бажаєте здійснити покупку (1), перевести гроші на іншу картку (2), заблокувати картку (3) чи анулювати рахунок (4)?" << endl;
			cout << "Введіть цифру: ";

			way_of_operation = check_way(4, 0);

			if (way_of_operation == 1)
			{
				cl.pay_for_the_order(cd, pr);
			}

			if (way_of_operation == 2)
			{
				cl.make_payment_on_other_card(cd);
			}

			if (way_of_operation == 3)
			{
				cl.block_credit_card(cd);
			}

			if (way_of_operation == 4)
			{
				cl.annul_money(cd);
			}
		}
		else
		{
			cout << "Заблокована" << endl;
		}
	}

	if (acess_way == 2)
	{
		cout << "Бажаєте проініціалізувати картку клієнта (1), змінити стан доступу до картки (2), змінити список товарів (3) чи змінити один з товарів (4)?" << endl << endl;
		cout << "Ввеідть число: ";

		way_of_operation = check_way(4, 0);

		if (way_of_operation == 1)
		{
			adm.initialize_card(cd);
		}
		if (way_of_operation == 2)
		{
			adm.block_credit_card(cd);
		}
		if (way_of_operation == 3)
		{
			adm.initiliaze_products(pr);
		}
		if (way_of_operation == 4)
		{
			adm.change_product(pr);
		}
	}

	if (acess_way == 3)
	{
		cout << "Бажаєте відтестити додатковий метод в класі, який виділяє випадкову величину динамічної пам’ят, в якій буде розмзміщена множина значень на N елементів, після чого вони будуть відсортовані (1)?" << endl << endl;
		cout << "Бажаєте відтестити один з перевантажених методів (2) або (3), або відтестити метод, що повертає об'єкт класу Credit_card (4)" << endl << endl;
		cout << "Ввеідть число: ";

		way_of_operation = check_way(4, 0);

		if (way_of_operation == 1)
		{
			addtional_method();
		}
		if (way_of_operation == 2)
		{
			addtional_method(cd, 1);
		}
		if (way_of_operation == 3)
		{
			addtional_method(&cd, 1.0);
		}
		if (way_of_operation == 4)
		{
			Client::Credit_card temp = *new Client::Credit_card;
			temp = addtional_method(cd);
			//delete temp;
		}
	}
	//delete streambuf;f
	return_to_start(cl, cd, pr, adm, stream);
}

void Client::pay_for_the_order(Credit_card& cd, Product* pr) //Метод оплати замовлення (купівля товара) клієнтом за допомогою кратки
{
	int type1, type2;

	pr->print(pr);

	cout << "Введіть номер товару, який ви бажаєте придбати" << endl << "Введіть число: ";

	type1 = check_way(5, 1);

	type1 -= 1;

	if (cd.get_money_on_card() == NULL)
	{
		cout << "Оплата з рахунку неможлива. Доступний варіант: в кредит (2)" << endl << "Оберіть тип оплати: ";
		type2 = check_way(1, 0);
	}
	else
	{
		cout << "Оплата з рахунку (1) чи в кредит (2)?" << endl << "Оберіть тип оплати: ";
		type2 = check_way(2, 0);
	}

	if (type2 == 0)
	{
		return;
	}

	if (type2 == 1)
	{
		if (cd.get_money_on_card() < pr[type1].get_price())
		{
			cout << "Помилка! На вашому рахунку не достатньо грошей для оплати. Операція не була проведена" << endl;
		}
		else
		{
			cd.change_money_on_card(pr[type1].get_price());
			cd.change_number_of_operations(1);

			show_results_of_operation(cd, pr[type1].get_price(), 1);
		}
		return;
	}

	if (type2 == 2)
	{
		if (!(cd.get_credit() > cd.get_credit_limit()))
		{
			if (cd.get_credit() + pr[type1].get_price() > cd.get_credit_limit())
			{
				cout << "Попередження! При оформленні даного замовлення до велечини вашого кредиту буде додано значення, що призведе до перевищення кредитного ліміту." << endl << endl;
				cout << "Все-одно продовжити? Так (1) Ні (2)" << endl << "Введіть цифру: ";

				type2 = check_way(2, 0);
				if (type2 == 1)
				{
					cd.change_credit(pr[type1].get_price());
					cd.change_number_of_operations(1);

					show_results_of_operation(cd, pr[type1].get_price(), 1.0);
				}
				if (type2 == 2)
				{
					cout << "Операція не була проведена";
				}
			}
			else
			{
				cd.change_credit(pr[type1].get_price());
				cd.change_number_of_operations(1);

				show_results_of_operation(cd, pr[type1].get_price(), 1.0);
			}
		}
		else
		{
			cout << "Попередження! Перевищення кредиту!" << endl << endl;
			cout << "Все-одно продовжити? Так (1) Ні (2)" << endl << "Введіть цифру: ";

			type2 = check_way(2, 0);

			if (type2 == 1)
			{
				cd.change_credit(pr[type1].get_price());
				cd.change_number_of_operations(1);

				show_results_of_operation(cd, pr[type1].get_price(), 1.0);
			}
			if (type2 == 2)
			{
				cout << "Операція не була проведена";
			}
		}

		return;
	}
}

void Client::make_payment_on_other_card(Credit_card& cd)
{
	string card_number;

	cout << "Введіть номер картки на яку ви хочете перевести гроші (16 цифр): ";
	cin >> card_number;

	if (card_number.size() < 16)
	{
		do
		{
			cout << endl << "Будь-ласка, введіть коректний номер картки." << endl << endl << "Введіть номер картки: ";
			cin >> card_number;
		} while (card_number.size() != 16);
		cout << endl;
	}
	else
	{
		cout << endl;
	}

	int type;

	if (cd.get_money_on_card() == NULL)
	{
		cout << "Оплата з рахунку неможлива. Доступний варіант: в кредит (2)" << endl << endl << "Оберіть тип оплати: ";
		type = check_way(1, 0);
	}
	else
	{
		cout << "Оплата з рахунку (1) чи в кредит (2)?" << endl << endl << "Оберіть тип оплати: ";
		type = check_way(2, 0);
	}


	int price;

	cout << "Введіть кількість грошей, яку ви хочете перевести на картку: " << endl;
	cout << "Введіть суму: ";
	price = check_int_corectness();
	cout << endl;

	if (type == 1)
	{
		if (cd.get_money_on_card() < price)
		{
			cout << "Помилка! На вашому рахунку не достатньо грошей для оплати. Операція не була проведена" << endl;
		}
		else
		{
			cd.change_money_on_card(price);
			cd.change_number_of_operations(1);

			show_results_of_operation(cd, price, 1);
		}
		return;
	}

	if (type == 2)
	{
		if (!(cd.get_credit() > cd.get_credit_limit()))
		{
			if (cd.get_credit() + price > cd.get_credit_limit())
			{
				cout << "Попередження! При оформленні даного замовлення до велечини вашого кредиту буде додано значення, що призведе до перевищення кредитного ліміту." << endl << endl;
				cout << "Все-одно продовжити? Так (1) Ні (2)" << endl << "Введіть цифру: ";

				type = check_way(2, 0);
				if (type == 1)
				{
					cd.change_credit(price);
					cd.change_number_of_operations(1);

					show_results_of_operation(cd, price, 1.0);
				}
				if (type == 2)
				{
					cout << "Операція не була проведена";
				}
			}
			else
			{
				cd.change_credit(price);

				show_results_of_operation(cd, price, 1.0);
			}
		}
		else
		{
			cout << "Попередження! Перевищення кредиту!" << endl << endl;
			cout << "Все-одно продовжити? Так (1) Ні (2)" << endl << "Введіть цифру: ";

			type = check_way(2, 0);

			if (type == 1)
			{
				cd.change_credit(price);
				cd.change_number_of_operations(1);

				show_results_of_operation(cd, price, 1.0);
			}
			if (type == 2)
			{
				cout << "Операція не була проведена";
			}
		}

		return;
	}
}

void Client::block_credit_card(Credit_card& cd)
{
	int way;

	cout << "Бажаєте заблокувати картку? " << "Так (1) Ні (2)" << endl;
	cout << "Введіть цифру: ";

	way = check_way(2, 0);

	if (way == 1)
	{
		cd.change_access(false);

		cout << "Картка була успішно заблокована!" << endl;

		return;
	}

	cout << "Стан картки клієнта залишився без змін" << endl;
}

void Client::annul_money(Credit_card& cd)
{
	cout << "Бажаєте анулювати рахунок? " << "Так (1) Ні (2)" << endl << endl;
	cout << "Введіть цифру: ";

	int way = check_way(2, 0);

	if (way == 1)
	{
		cd.set_money_on_card(NULL);

		cout << "Ваш рахунок було успішно онульовано!" << endl;
	}

	if (way == 2)
	{
		cout << "Стан рахунку залишився без змін";
	}

	return;
}

void Client::show_results_of_operation(Credit_card& cd, double price, int type)
{
	cout << "Операція пройшла успішно!" << endl << endl << "З вашого рахунку було знято " << price << " гривень" << endl;
	cout << "Кількість грошей на рахунку: " << cd.get_money_on_card() << " гривень" << endl;
	cout << "Величина кредиту складає: " << cd.get_credit() << " гривень" << endl << endl;
}

void Client::show_results_of_operation(Credit_card& cd, double price, double type)
{
	cout << "Операція пройшла успішно!" << endl << endl << "До вашого кредиту було додано " << price << " гривень" << endl;
	cout << "Кількість грошей на рахунку: " << cd.get_money_on_card() << " гривень" << endl;
	cout << "Величина кредиту складає: " << cd.get_credit() << " гривень" << endl << endl;
}

Client::~Client()
{
	cout << "Об'єкт класу \"Client\" був видалений" << endl;
}

bool Client::Credit_card::get_access()
{
	return this->access;
}

void Client::Credit_card::change_access(bool state)
{
	this->access = state;
}

string Client::Credit_card::get_card_number()
{
	return this->card_number;
}

void Client::Credit_card::set_card_number(string card_number)
{
	this->card_number = card_number;
}

double Client::Credit_card::get_money_on_card()
{
	return this->money_on_card;
}

void Client::Credit_card::set_money_on_card(double money)
{
	this->money_on_card = money;
}

void Client::Credit_card::change_money_on_card(double money)
{
	this->money_on_card = this->money_on_card - money;
}

unsigned int Client::Credit_card::get_credit_limit()
{
	return this->credit_limit;
}

void Client::Credit_card::set_credit_limit(int credit_limit)
{
	this->credit_limit = credit_limit;
}

double Client::Credit_card::get_credit()
{
	return this->credit;
}

void Client::Credit_card::set_credit(double credit)
{
	this->credit = credit;
}

void Client::Credit_card::change_credit(double price)
{
	this->credit += price;
}

int Client::Credit_card::get_number_of_operations()
{
	return number_of_operations;
}

void Client::Credit_card::change_number_of_operations(int size)
{
	this->number_of_operations += size;
}

void Client::Credit_card::set_card_attributes(bool access, string card_number, double money_on_card, unsigned int credit_limit, double credit, int number_of_operations)
{
	this->access = access;
	this->card_number = card_number;
	this->money_on_card = money_on_card;
	this->credit_limit = credit_limit;
	this->credit = credit;
	this->number_of_operations = number_of_operations;
}

Client::Credit_card::Credit_card(bool access, string card_number, double money_on_card, unsigned int credit_limit, double credit, int number_of_operations)
{
	this->access = access;
	this->card_number = card_number;
	this->money_on_card = money_on_card;
	this->credit_limit = credit_limit;
	this->credit = credit;
	this->number_of_operations = number_of_operations;
}

Client::Credit_card::Credit_card()
{
	this->access = false;
	this->card_number = "";
	this->money_on_card = 0;
	this->credit_limit = 0;
	this->credit = 0;
	this->number_of_operations = 0;
}

Client::Credit_card::Credit_card(const Credit_card& cd)
{
	this->access = cd.access;
	this->card_number = cd.card_number;
	this->money_on_card = cd.money_on_card;
	this->credit_limit = cd.credit_limit;
	this->credit = cd.credit;
}

Client::Credit_card::~Credit_card()
{
	cout << "Об'єкт класу \"Credit_card\" був видалений" << endl;
}

void Administator::initialize_card(Client::Credit_card& cd)
{
	string card_number;
	unsigned int credit_limit;
	double money_on_card, credit;
	int number_of_operations;

	cout << "Введіть номер карти клієнта: ";
	cin >> card_number;
	//cd.set_card_number(*card_number);

	cout << "Введіть кількість грошей на картці клієнта: ";
	cin >> money_on_card;
	//cd.set_money_on_card(money);

	cout << "Введіть кредитний ліміт на картці клієнта: ";
	cin >> credit_limit;
	//cd.set_credit_limit(credit_limit);

	cout << "Введіть початкову кількість кредиту клієнта: ";
	cin >> credit;
	//cd.set_credit(credit);

	cout << "Введіть початкову кількість проведених операцій: ";
	cin >> number_of_operations;
	//cd.set_credit(number_of_operations);
	//cd.change_access(true);

	Client::Credit_card temp(true, card_number, money_on_card, credit_limit, credit, number_of_operations);

	cd = temp;

	cout << endl;

	return;
}

void Administator::block_credit_card(Client::Credit_card& cd)
{
	//read_data(cd);

	int type;
	if (cd.get_access() == true)
	{
		cout << "Стан картки: доступна" << endl << "Перевтищення кридету: ";

		if (cd.get_credit() > cd.get_credit_limit())
		{
			cout << "Так" << endl << "Перевищення кредиту складає " << (cd.get_credit() - cd.get_credit_limit()) << " гривень" << endl << endl;
		}
		else
		{
			cout << "Ні" << endl << endl;
		}

		cout << "Бажаєте заблокувати картку? " << "Так (1) Ні (2)" << endl;
		cout << "Введіть цифру: ";

		type = check_way(2, 0);

		if (type == 1)
		{
			cd.change_access(false);

			cout << "Картка була успішно заблокована!" << endl << endl;

			return;
		}

		cout << "Стан картки клієнта залишився без змін" << endl;
		return;
	}
	if (cd.get_access() == false)
	{
		cout << "Стан картки: заблокована" << endl << endl << "Бажаєте відновити картку? " << "Так (1) Ні (2)" << endl;
		cout << "Введіть число: ";

		type = check_way(2, 0);

		if (type == 1)
		{
			cd.change_access(true);

			cout << "Картка була успішно відновлена!" << endl << endl;

			return;
		}

		cout << "Стан картки клієнта залишився без змін" << endl;
	}
}

void addtional_method() //Додатковий метод
{
	cout << "Введіть кількість елементів у масиві: ";
	int size = check_int_corectness();

	int* array = new int[size];

	cout << "[ ";
	for (int i = 0; i < size; i++)
	{
		cout << (array[i] = rand() % 100);
		cout << " ";
	}
	cout << "]" << endl << endl;

	bool swapped;
	for (int i = 0; i < size - 1; i++)
	{
		swapped = false;
		for (int j = 0; j < size - i - 1; j++)
		{
			if (array[j] > array[j + 1]) {
				swap(array[j], array[j + 1]);
				swapped = true;
			}
		}
		if (swapped == false)
		{
			break;
		}
	}

	cout << "Відсортований масив" << endl << endl;

	cout << "[ ";
	for (int i = 0; i < size; i++)
	{
		cout << array[i];
		cout << " ";
	}
	cout << "]" << endl << endl;

	delete[] array;

	return;
}

Administator::~Administator()
{
	cout << "Об'єкт класу \"Administator\" був видалений" << endl;
}

void save_data(Client::Credit_card& cd)
{
	ofstream file("files/Client.txt");

	//file.write(reinterpret_cast<char*>(&cd), sizeof(Client::Credit_card));
	file << cd.get_access() << endl << cd.get_card_number() << endl << cd.get_money_on_card() << endl << cd.get_credit_limit() << endl << cd.get_credit() << endl << cd.get_number_of_operations();

	file.close();
}

void read_data(Client::Credit_card& cd)
{
	bool access;
	string card_number;
	double money_on_card;
	unsigned int credit_limit;
	double credit;
	int number_of_operations;

	ifstream file("files/Client.txt");

	//file.read(reinterpret_cast<char*>(&cd), sizeof(Client::Credit_card));

	file >> access >> card_number >> money_on_card >> credit_limit >> credit >> number_of_operations;

	cd.set_card_attributes(access, card_number, money_on_card, credit_limit, credit, number_of_operations);

	file.close();
}

void save_data(Product* pr)
{
	ofstream file("files/Products.txt");
	for (int i = 0; i < 5; i++)
	{
		//file.write((char*)&pr[i], sizeof(Product));
		file << pr[i].get_product_name() << endl << pr[i].get_price() << endl;
	}
	file.close();
}

void read_data(Product* pr)
{
	string name;
	double price;
	ifstream file("files/Products.txt");
	for (int i = 0; i < 5; i++)
	{
		//file.read((char*)&pr[i], sizeof(Product));
		file >> name >> price;
		pr[i].set_product(name, price);
	}
	file.close();
}

Product::~Product()
{
	cout << "Об'єкт класу \"Product\" був видалений" << endl;
}

int check_way(int way, int sub_way)
{
	global_stream->close();

	int type = 0;
	bool missed = false;

	if (!(cin >> type))
	{
		do
		{
			missed = true;

			cout << endl << "Будь-ласка, введіть коректне число" << endl << "Введіть число: ";
			cin.clear();
			cin.ignore(1000, '\n');
		} while (!(cin >> type));
	}

	if (type == 0)
	{
		return 0;
	}

	if (way == 1)
	{
		if (type != 2)
		{
			do
			{
				missed = true;

				cout << endl;
				cout << "Оплата з рахунку неможлива. Доступний варіант: в кредит (2)" << endl << endl << "Оберіть тип оплати: ";
				cin >> type;
			} while (type != 2);
			cout << endl;
		}
		else
		{
			cout << endl;
		}
	}

	if (way == 2)
	{
		if (type != 1 && type != 2)
		{
			do
			{
				missed = true;

				cout << endl;
				cout << "Будь-ласка, введіть коректне число" << endl << "Введіть число: ";
				cin >> type;
			} while (type != 1 && type != 2);
			cout << endl;
		}
		else
		{
			cout << endl;
		}
	}

	if (way == 3)
	{
		if (type != 1 && type != 2 && type != 3)
		{
			do
			{
				missed = true;

				cout << endl;
				cout << "Будь-ласка, введіть коректне число" << endl << "Введіть число: ";
				cin >> type;
			} while (type != 1 && type != 2 && type != 3);
			cout << endl;
		}
		else
		{
			cout << endl;
		}
	}

	if (way == 4)
	{
		if (type != 1 && type != 2 && type != 3 && type != 4)
		{
			do
			{
				missed = true;

				cout << endl;
				cout << "Будь-ласка, введіть коректне число" << endl << "Введіть число: ";
				cin >> type;
			} while (type != 1 && type != 2 && type != 3 && type != 4);
			cout << endl;
		}
		else
		{
			cout << endl;
		}
	}

	if (way == 5 && sub_way == 0)
	{
		if (type != 1 && type != 2 && type != 3 && type != 4 && type != 5)
		{
			do
			{
				missed = true;

				cout << endl;
				cout << "Будь-ласка, введіть коректне число" << endl << "Введіть число: ";
				cin >> type;
			} while (type != 1 && type != 2 && type != 3 && type != 4 && type != 5);
			cout << endl;
		}
		else
		{
			cout << endl;
		}
	}

	if (way == 5 && sub_way == 1)
	{
		if (type != 1 && type != 2 && type != 3 && type != 4 && type != 5)
		{
			do
			{
				missed = true;

				cout << endl;
				cout << "Товару під таким номером не існує. Будь-ласка, введіть коректне число" << endl << "Введіть число: ";
				cin >> type;
			} while (type != 1 && type != 2 && type != 3 && type != 4 && type != 5);
			cout << endl;
		}
		else
		{
			cout << endl;
		}
	}
	cin.clear();
	cin.ignore(1000, '\n');

		global_stream->open("ConsoleOutput.txt", ios::app);
		cout << type << endl << endl;
		global_stream->close();

		global_stream->open("ConsoleOutput.txt", ios::in);
		ofstream temp1("temp.txt");
		temp1 << global_stream->rdbuf();
		temp1.close();
		global_stream->close();

		system("cls");

		ifstream temp2("temp.txt");
		string line;
		while (getline(temp2, line))
		{
			cout << line << endl;
		}
		
		temp2.close();
	

	global_stream->open("ConsoleOutput.txt", ios::app);
	return type;
}

int check_int_corectness()
{
	global_stream->close();

	int variable;

	if (!(cin >> variable))
	{
		do
		{
			cout << endl << "Будь-ласка, введіть коректне число" << endl << "Введіть число: ";
			cin.clear();
			cin.ignore(1000, '\n');
		} while (!(cin >> variable));
	}

	global_stream->open("ConsoleOutput.txt", ios::app);
	cout << variable << endl << endl;
	global_stream->close();

	global_stream->open("ConsoleOutput.txt", ios::in);
	ofstream temp1("temp.txt");
	temp1 << global_stream->rdbuf();
	temp1.close();
	global_stream->close();

	system("cls");

	ifstream temp2("temp.txt");
	string line;
	while (getline(temp2, line))
	{
		cout << line << endl;
	}

	temp2.close();

	return variable;
}

void return_to_start(Client& cl, Client::Credit_card& cd, Product* pr, Administator& adm, ofstream& stream)
{
	int type;

	//restart_cin();

	cout << "Бажаєте повернутися на початок?" << endl << "Так (1) Ні (2)" << endl << endl;
	cout << "Введіть цифру: ";

	type = check_way(2, 0);
	if (type == 0)
	{
		return;
	}

	if (type == 1)
	{
		system("cls");
		global_stream->close();
		global_stream->open("ConsoleOutput.txt", ios::out);
		main_script(cl, cd, pr, adm, stream);
	}
	if (type == 2)
	{
		system("cls");
		cout << "Роботу програми було закінчено" << endl << endl;
	}
}

void restart_cin()
{
	cin.clear();
	cin.ignore(1000, '\n');
}

void Administator::initiliaze_products(Product* pr) //Метод роботи з масивом об'єктів
{
	string name;
	int price;
	for (int i = 0; i < 5; i++)
	{
		global_stream->open("ConsoleOutput.txt", ios::app);

		cout << "Введіть назву " << i + 1 << "-го товару: ";
		getline(cin, name);
		//
		global_stream->close();

		global_stream->open("ConsoleOutput.txt", ios::app);
		cout << name << endl;
		global_stream->close();

		global_stream->open("ConsoleOutput.txt", ios::in);
		ofstream temp1("temp.txt");
		temp1 << global_stream->rdbuf();
		temp1.close();
		global_stream->close();

		system("cls");

		ifstream temp2("temp.txt");
		
		string line;
		while (getline(temp2, line))
		{
			cout << line << endl;
		}

		temp2.close();
		global_stream->open("ConsoleOutput.txt", ios::app);
		//
		cout << "Введіть ціну " << i + 1 << "-го товару: ";
		price = check_int_corectness();
		
		pr[i].set_product(name, price);
		restart_cin();
	}

	return;
}

void Administator::change_product(Product* pr) //Метод роботи з масивом об'єктів
{
	pr->print(pr);

	cout << "Введіть номер товару, який ви бажаєте змінити: " << endl;
	cout << "Введіть цифру: ";

	int type = check_way(5, 1);

	string name;
	int price;

	cout << "Введіть нову назву " << type << "-го товару: ";
	getline(cin, name);

	global_stream->close();
	
	global_stream->open("ConsoleOutput.txt", ios::app);
	cout << name << endl << endl;
	global_stream->close();

	global_stream->open("ConsoleOutput.txt", ios::in);
	ofstream temp1("temp.txt");
	temp1 << global_stream->rdbuf();
	temp1.close();
	global_stream->close();

	system("cls");

	ifstream temp2("temp.txt");
	string line;
	while (getline(temp2, line))
	{
		cout << line << endl;
	}

	temp2.close();

	global_stream->open("ConsoleOutput.txt", ios::app);

	cout << "Введіть нову ціну " << type << "-го товару: ";
	price = check_int_corectness();

	pr[type - 1].set_product(name, price);

	cout << type << "-ий товар був успішно змінений!" << endl << endl;
}

void Product::set_product(string name, double price)
{
	this->name = name;
	this->price = price;
}

double Product::get_price()
{
	return this->price;
}

string Product::get_product_name()
{
	return this->name;
}

void Product::print(Product* pr)
{
	size_t length = 0;

	for (int i = 0; i < 5; i++)
	{
		if ((pr[i].name).length() > length)
		{
			length = (pr[i].name).length();
		}
	}

	cout << "Перелік товарів:" << endl;

	cout << setw(3) << left << "N" << setw(length + 3) << "Назва" << "Ціна" << endl << endl;

	for (int i = 0; i < 5; i++)
	{
		cout << setw(3) << i + 1 << setw(length + 3) << pr[i].name << pr[i].price << endl << endl;
	}
}

void addtional_method(Client::Credit_card& cd, int a)
{
	//Провести певні обчислення
	cout << "Результат \"певних обчислень\": " << cd.get_money_on_card() + cd.get_credit_limit() + cd.get_credit() + cd.get_number_of_operations() << endl;
}

void addtional_method(Client::Credit_card* cd, double a)
{
	//Провести певні обчислення
	cout << "Результат \"певних обчислень\": " << cd->get_money_on_card() + cd->get_credit_limit() + cd->get_credit() + cd->get_number_of_operations() << endl;
	//Помилка при передачі копії?
}

Client::Credit_card addtional_method(Client::Credit_card& cd)
{
	cout << "Результат \"певних обчислень\": " << cd.get_money_on_card() + cd.get_credit_limit() + cd.get_credit() + cd.get_number_of_operations() << endl;
	return cd;
}

void MoveWindow(int posx, int posy)
{
	RECT rectClient, rectWindow;
	HWND hWnd = GetConsoleWindow();
	GetClientRect(hWnd, &rectClient);
	GetWindowRect(hWnd, &rectWindow);
	MoveWindow(hWnd, posx, posy, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE);
}

void MoveCenter()
{
	RECT rectClient, rectWindow;
	HWND hWnd = GetConsoleWindow();
	GetClientRect(hWnd, &rectClient);
	GetWindowRect(hWnd, &rectWindow);
	int posx, posy;
	posx = GetSystemMetrics(SM_CXSCREEN) / 2 - (rectWindow.right - rectWindow.left) / 2;
	posy = GetSystemMetrics(SM_CYSCREEN) / 2 - (rectWindow.bottom - rectWindow.top) / 2;

	MoveWindow(hWnd, posx, posy, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE);
}

void Print_in_center(const string& s) 
{
	int width_field = 128;
	string v(width_field, ' ');
	string v1;

	int l_word = s.size();
	int l_field = v.size();
	int step = (l_field - l_word) / 2;

	for (int i = 0; i < l_word; i++) {
		v1.push_back(s[i]);
	}
	copy(v1.begin(), v1.end(), v.begin() + step);
	for (auto x : v) {
		cout << x;
	}
	cout << endl;
}

MyStreambuf::~MyStreambuf()
{	
	cout << "Об'єкт класу \"MyStreambuf\" був видалений";
	cin.get();
}