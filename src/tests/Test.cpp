#include "..\Test.h"


namespace test {
	TestMenu::TestMenu(Test*& current_test_pointer)
		: current_test_(current_test_pointer)
	{

	}

	TestMenu::~TestMenu()
	{
	}

	void TestMenu::OnImGuiRender()
	{
	}
}
