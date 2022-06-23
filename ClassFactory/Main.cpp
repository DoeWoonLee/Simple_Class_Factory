#include "pch.h"

#include "EventCreator.h"
#include "DObjectCreator.h"
#include "GlobalObjectCreator.h"
#include "LogicComponentCreator.h"
#include "AIStateLogicCreator.h"
#include "AILogicConditionCreator.h"
#include "CollisionListenerCreator.h"
#include "VertexShaderCreator.h"
#include "PixelShaderCreator.h"
#include "UserPostProcessCreator.h"


using CreatorFunc = std::function<void(std::ofstream& cpp, std::ofstream& h, const std::string& className, const std::string& parentName)>;
static const std::map<std::string, CreatorFunc> s_CreatorMap = {
	{"-d" , Creator::DObject},
	{"-l" , Creator::LogicComponent},
	{"-g" , Creator::GlobalObject},
	{"-asl" , Creator::AIStateLogicCreator},
	{"-alc" , Creator::AILogicCondition},
	{"-e", Creator::Event},
	{"-cl", Creator::CollisionListener},
	{"-vs", Creator::VertexShader},
	{"-ps", Creator::PixelShader},
	{"-up", Creator::UserPostProcess},
};

char* GetCmdOption(char** begin, char** end, const std::string& option)
{
	char** itr = std::find(begin, end, option);
	if (itr != end)
	{
		return *itr;
	}
	return 0;
}

int main(int argc, char* argv[])
{
	if (GetCmdOption(argv, argv + argc, "-help"))
	{
		std::cout << "==== Script Class Types ====" << std::endl;
		std::cout << "-d : DObject" << std::endl;
		std::cout << "-l : LogicComponent" << std::endl;
		std::cout << "-g : GlobalObject" << std::endl;
		std::cout << "-asl : AIStateLogic" << std::endl;
		std::cout << "-alc : AILogicCondition" << std::endl;
		std::cout << "-e : Event" << std::endl;
		std::cout << "-cl : CollisionListener" << std::endl;
		std::cout << "-vs : VertexShader" << std::endl;
		std::cout << "-ps : PixelShader" << std::endl;

		std::cout << std::endl;

		std::cout << "=== If you want to inherit class! ====" << std::endl;
		std::cout << "make -d -ParentClassName NewClassName" << std::endl;
		std::cout << std::endl;
		return 1;
	}
	if (argc < 3)
	{
		std::cout << "Please input command!" << std::endl;
		std::cout << "check -help command!" << std::endl;
		return 1;
	}
	// input format
	// Make -DObject -ParentClass ClassName

	std::string command = argv[1];
	std::string type = argv[2];
	std::string fileName = "";
	std::string parent = "";
	CreatorFunc creatorFunc = nullptr;

	int argIdx = -1;

	// Find Creator func
	auto find = s_CreatorMap.end();
	for (int i = 0; i < argc; ++i)
	{
		find = s_CreatorMap.find(argv[i]);
		if (find != s_CreatorMap.end())
		{
			argIdx = i;
			creatorFunc = find->second;
			break;
		}
	}

	/// Exceptions
	if (argIdx == argc - 1)
	{
		std::cout << "The New class Name has to be set to last!" << std::endl;
		std::cout << "check -help command!" << std::endl;

		return 1;
	}
	if (find == s_CreatorMap.end())
	{
		std::cout << "This command do not has class type option!" << std::endl;
		std::cout << "check -help command!" << std::endl;
		return 1;
	}

	// Do not use inherit option
	if (argc == 3)
	{
		fileName = argv[2];
	}
	else if (argc == 4)
	{
		if (argIdx == 1)
			parent = argv[2];
		else if (argIdx == 2)
			parent = argv[1];

		fileName = argv[3];
		
		if (fileName.data()[0] == '-')
		{
			std::cout << "Inherit class name has to be set before the New class name!" << std::endl;
			std::cout << "check -help command!" << std::endl;

			return 1;
		}

		parent = &parent[1];
	}

	std::string cppName = fileName + ".cpp";
	std::string hName = fileName + ".h";

	std::ofstream cppOut(cppName, std::ios_base::binary | std::ios_base::_Noreplace);
	std::ofstream hOut(hName, std::ios_base::binary | std::ios_base::_Noreplace);

	creatorFunc(cppOut, hOut, fileName, parent);

	cppOut.close();
	hOut.close();

	std::cout << cppName << " file is created!" << std::endl;
	std::cout << hName << " file is created!" << std::endl;

	return 0;
}