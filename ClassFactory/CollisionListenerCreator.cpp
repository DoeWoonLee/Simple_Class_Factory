#include "pch.h"
#include "CollisionListenerCreator.h"


void Creator::CollisionListener(std::ofstream& cpp, std::ofstream& h, const std::string& className, const std::string& parentName)
{
	bool inheritance = !parentName.empty();
	/// Preprocess
	std::string parentHeader = parentName;
	if (parentHeader.empty())
		parentHeader = "<DWEngine2D\\CollisionListener.h>";
	else
		parentHeader = '"' + parentHeader + ".h" + '"';

	std::string parentClass = parentName;
	if (parentClass.empty())
		parentClass = "DW::CollisionListener";

	/// === Headers ===
	// Header Write
	h << "#pragma once\n" << std::endl;
	h << "#include " << parentHeader << std::endl;
	h << std::endl;

	// Begin NameSpace
	h << "BEGIN(Client)" << std::endl;

	// Declartion Class with inhertiance
	h << "class CLIENT_DLL " << className << ": public " << parentClass << std::endl;
	h << "{" << std::endl;
	// Declartion Macros
	h << "\tDeclareReflect(" << className << ")" << std::endl;
	if (inheritance)
	{
		h << "\tDeclare_CollisionListenerDefault(" << className << ")" << std::endl;
	}
	else
	{
		h << "\tDeclare_CollisionListenerDefault(" << className << ")" << std::endl;
	}
	h << "public:" << std::endl;
	// Contructor, copy constructor, deconstructor
	h << "\t" << className << "();" << std::endl;
	h << "\t" << className << "( const " << className << "& equal) noexcept;" << std::endl;
	h << "\t~" << className << "() override;" << std::endl << std::endl;
	h << "\t//void Init() override;\n" << std::endl;
	h << "\t//void OnHitStart(DW::CollisionMapKey& collisionMapKey) override;\n" << std::endl;
	h << "\t//void OnHit(DW::CollisionMapKey& collisionMapKey) override;\n" << std::endl;
	h << "\t//void OnHitFinish(DW::CollisionMapKey& collisionMapKey) override;\n" << std::endl;

	// End NameSpace
	h << "};\nEND" << std::endl;

	/// === cpp files ===
	// include Headers
	cpp << "#include \"pch.h\"" << std::endl;
	cpp << "#include " << '"' << className << ".h\"" << std::endl << std::endl;

	// using namespace
	cpp << "USING(Client)" << std::endl << std::endl;

	// implement macros (Reflect)
	if (inheritance)
		cpp << "Implement_CollisionListenerDefault(" << className << ")" << std::endl;
	else
		cpp << "Implement_CollisionListenerDefault(" << className << ")" << std::endl;

	cpp << "ReflectBeginDefault(" << className << "," << parentClass << ")" << std::endl;
	cpp << "ReflectEnd" << std::endl << std::endl;

	// Constrctuor
	cpp << className << "::" << className << "()" << std::endl;
	cpp << "{\n\t\n}\n";

	cpp << className << "::" << className << "(const " << className << "& equal) noexcept" << std::endl;
	cpp << "{\n\t\n}\n";

	cpp << className << "::~" << className << "()" << std::endl;
	cpp << "{\n\t\n}\n";

	cpp << "//void " << className << "::" << "Init()" << std::endl;
	cpp << "//{\n//\t\n//}\n";

	cpp << "//void " << className << "::" << "OnHitStart(DW::CollisionMapKey& collisionMapKey)" << std::endl;
	cpp << "//{\n//\t\n//}\n";

	cpp << "//void " << className << "::" << "OnHit(DW::CollisionMapKey& collisionMapKey)" << std::endl;
	cpp << "//{\n//\t\n//}\n";

	cpp << "//void " << className << "::" << "OnHitFinish(DW::CollisionMapKey& collisionMapKey)" << std::endl;
	cpp << "//{\n//\t\n//}\n";

}
