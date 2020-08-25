#include "Test.h"
#include "imgui/imgui.h"


namespace test {
	TestMenu::TestMenu(Test*& current_test_pointer)
		: current_test_(current_test_pointer) {

	}

	void TestMenu::OnImGuiRender()
	{
		for (const auto& test : tests_) {
			if (ImGui::Button(test.first.c_str())) {
				current_test_ = test.second();
			}
		}
	}
}