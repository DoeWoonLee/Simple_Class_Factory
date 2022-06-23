#include "pch.h"
#include "PixelShaderCreator.h"

void Creator::PixelShader(std::ofstream& cpp, std::ofstream& h, const std::string& className, const std::string& parentName)
{
	/// Preprocess
	std::string parentHeader = parentName;
	if (parentHeader.empty())
		parentHeader = "<DWEngine2D\\PixelShader.h>";
	else
		parentHeader = '"' + parentHeader + ".h" + '"';

	std::string parentClass = parentName;
	if (parentClass.empty())
		parentClass = "DW::PixelShader";

	/// === Headers ===
	// Header Write
	h << "#pragma once\n" << std::endl;
	h << "#include " << parentHeader << std::endl;
	h << std::endl;

	// Begin NameSpace
	h << "BEGIN(Client)" << std::endl << std::endl;

	// Sample Constant Buffer
	h << "/*" << std::endl;
	h << "CBuffer SampleBuffer : DW::ConstantBuffer" << std::endl;
	h << "{" << std::endl; 
	h << "\tDeclareReflect(SampleBuffer)" << std::endl;
	h << "\tDeclare_ConstantBuffer(SampleBuffer)" << std::endl;
	h << "public:" << std::endl;
	h << "\tvoid Update() override;" << std::endl;
	h << "public:" << std::endl;
	h << "\t//uint32_t * 2 vtable paddings" << std::endl;
	h << "\tLA::Vector2 sampleValue; // 16bytes" << std::endl;
	h << "}" << std::endl ;
	h << "*/" << std::endl << std::endl;

	// Declartion Class with inhertiance
	h << "class CLIENT_DLL " << className << ": public " << parentClass << std::endl;
	h << "{" << std::endl;
	// Declartion Macros
	h << "\tDeclare_Shader(" << className << ")" << std::endl;
	h << "public:" << std::endl;
	// Contructor, deconstructor
	h << "\t" << className << "();" << std::endl;
	h << "\t~" << className << "() override;" << std::endl << std::endl;

	// Creator
	h << "\tstatic DW::Shader* Create();" << std::endl;
	h << "protected:\n\tvoid Init();\n\tprivate:\n" << std::endl;
	// End NameSpace
	h << "};\nEND" << std::endl;

	/// === cpp files ===
	// include Headers
	cpp << "#include \"pch.h\"" << std::endl;
	cpp << "#include " << '"' << className << ".h\"" << std::endl << std::endl;

	// using namespace
	cpp << "USING(Client)" << std::endl << std::endl;

	// Sample ConstantBuffer
	cpp << "/*" << std::endl;
	cpp << "Implement_ConstantBuffer(SampleBuffer)" << std::endl;
	cpp << "ReflectBeginDefault(SampleBuffer, DW::ConstantBuffer)" << std::endl;
	cpp << "ReflectMember(sampleValue)" << std::endl;
	cpp << "ReflectEnd " << std::endl;
	cpp << std::endl;
	cpp << "void SampleBuffer::Update()" << std::endl;
	cpp << "{" << std::endl;
	cpp << "	" << std::endl;
	cpp << "}" << std::endl;
	cpp << "*/" << std::endl;
	cpp << std::endl;

	// implement macros (Reflect)
	cpp << "Implement_Shader(" << className << ")" << std::endl;


	// Constrctuor
	cpp << className << "::" << className << "()" << std::endl;
	cpp << "{\n\t\n}\n";

	cpp << className << "::~" << className << "()" << std::endl;
	cpp << "{\n\t\n}\n";

	// Creator implement
	cpp << "DW::Shader* " << className << "::Create()" << std::endl;
	cpp << "{\n\t" << className << "* p" << className << " = new " << className << "();" << std::endl;
	cpp << "\tp" << className << "->Init();" << std::endl << std::endl;

	cpp << "\t return p" << className << ";\n}\n" << std::endl;

	// Init
	cpp << "void " << className << "::Init()" << std::endl;
	cpp << "{\n\tLoadShader(L\"" << className << ".cso\");\n\t\n}" << std::endl;

}