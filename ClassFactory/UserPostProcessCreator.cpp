#include "pch.h"
#include "UserPostProcessCreator.h"

void Creator::UserPostProcess(std::ofstream& cpp, std::ofstream& h, const std::string& className, const std::string& parentName)
{
	/// Preprocess
	std::string parentHeader = parentName;
	if (parentHeader.empty())
		parentHeader = "<DWEngine2D\\UserPostProcess.h>";
	else
		parentHeader = '"' + parentHeader + ".h" + '"';

	std::string parentClass = parentName;
	if (parentClass.empty())
		parentClass = "DW::UserPostProcess";

	/// === Headers ===
	// Header Write
	h << "#pragma once\n" << std::endl;
	h << "#include " << parentHeader << std::endl;
	h << std::endl;

	// Begin NameSpace
	h << "BEGIN(Client)" << std::endl << std::endl;

	// Sample Constant Buffer
	h << "/*" << std::endl;
	h << "CBuffer SampleBuffer" << std::endl;
	h << "{" << std::endl;
	h << "\t" << std::endl;
	h << "}" << std::endl;
	h << "*/" << std::endl << std::endl;

	// Declartion Class with inhertiance
	h << "class CLIENT_DLL " << className << ": public " << parentClass << std::endl;
	h << "{" << std::endl;
	h << "public:" << std::endl;
	// Contructor, deconstructor
	h << "\t" << className << "();" << std::endl;
	h << "\t~" << className << "() override;" << std::endl << std::endl;
	// Virtual functions
	h << "\tvoid Init() override;" << std::endl;
	h << "\tvoid WindowSizeChanged(int width, int height) override;" << std::endl;
	h << "\tvoid PreProcess() override;" << std::endl;
	h << "\tvoid Render() override;" << std::endl;
	// End NameSpace
	h << "};\nEND" << std::endl;

	/// === cpp files ===
	// include Headers
	cpp << "#include \"pch.h\"" << std::endl;
	cpp << "#include " << '"' << className << ".h\"" << std::endl << std::endl;

	// using namespace
	cpp << "USING(Client)" << std::endl << std::endl;

	// implement macros (Reflect)
	cpp << "Implement_UserPostProcess( /*Priority*/ ," << className << ")" << std::endl;


	// Constrctuor
	cpp << className << "::" << className << "()" << std::endl;
	cpp << "{\n\t/*m_IsBeforeUI = false; // rendering sequence */\n}\n";

	cpp << className << "::~" << className << "()" << std::endl;
	cpp << "{\n\t\n}\n";

	// virtual functions
	cpp << "void " << className << "::Init()" << std::endl;
	cpp << "{\n\t\n}\n" << std::endl;

	cpp << "void " << className << "::WindowSizeChanged(int width, int height)" << std::endl;
	cpp << "{\n\tif(0 == width || 0 == height) return;\t\n\n}\n" << std::endl;

	cpp << "void " << className << "::PreProcess()" << std::endl;
	cpp << "{\n\t\n}\n" << std::endl;

	cpp << "void " << className << "::Render()" << std::endl;
	cpp << "{\n\t\n}\n" << std::endl;

	cpp << className << "* Get()" << std::endl;
	cpp << "{" << std::endl;
	cpp << "\t static " << className << "* p" << className << " = nullptr;" << std::endl;
	cpp << "if(!p" << className << ")" << std::endl;
	cpp << "\t\tp" << className << " = (" << className << "*)DW::UserPostProcess::Find((int)/*Priority*/);" << std::endl;
	cpp << "\treturn p" << className << ";" << std::endl;
	cpp << "}\n" << std::endl;

}