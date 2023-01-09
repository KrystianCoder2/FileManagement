#include <iostream>
#include <fstream>
#include <filesystem>

class User
{
private:
	std::string username;
	std::string password;
	std::string filename;

	std::fstream file;

	std::vector<std::string> lines;

public:
	void CreateAccount()
	{
		std::cout << "Create Account" << std::endl;

		std::cout << "Enter username: ";
		std::cin >> username;
		std::cout << "Enter password: ";
		std::cin >> password;

		lines.push_back(username);
		lines.push_back(password);

		file.open("./data/" + username + ".dfs", std::ios::in | std::ios::out | std::ios::trunc);

		for (std::string line : lines)
		{
			file << line;
			file << "\n";
		}

		username = "";
		password = "";
	}
	
	void Login()
	{
		std::cout << "Login" << std::endl;

		std::cout << "Enter username: ";
		std::cin >> username;
		std::cout << "Enter password: ";
		std::cin >> password;

		if (!std::filesystem::exists("./data/" + username + ".dfs"))
		{
			std::cout << "Account Does not exists!!" << std::endl;
		}
		else
		{
			file.open("./data/" + username + ".dfs", std::ios::in | std::ios::out);
			std::string str;
			while (file >> str)
			{
				lines.push_back(str);
				if (file.eof())
				{
					break;
				}
			}
			if (username == lines.at(0) && password == lines.at(1))
			{
				std::cout << "Login succesful!" << std::endl;
			}
			else
			{
				std::cout << "Could not login!" << std::endl;
			}
		}
	}
};

int main()
{
	system("md data");

	User* user = new User;

	int choice = 0;

	std::cout << "Login system" << std::endl;
	std::cout << "1. Login" << std::endl;
	std::cout << "2. Create Account" << std::endl;

	std::cin >> choice;

	switch (choice)
	{
	case 1:
		user->Login();
		break;
	case 2:
		user->CreateAccount();
		break;
	default:
		std::cout << "ERROR::COMMAND:DOES:NOT:EXISTS!" << std::endl;
		break;
	}
	
	delete user;

	return 0;
}
