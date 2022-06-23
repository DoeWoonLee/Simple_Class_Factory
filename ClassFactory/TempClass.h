#include "TestClass.h"

BEGIN(Client)
class CLIENT_DLL TempClass: public TestClass
{
	DeclareReflect(TempClass)
	Declare_DObjectCreate(TempClass)
public:
	TempClass();
	TempClass( const TempClass& equal) noexcept;
	~TempClass() override;
};
END
