#pragma once
#include <vector>
#include <string>
#include <functional>

namespace test {
	class Test {
	public:
		Test() = default;
		virtual ~Test() = default;

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

	class TestMenu : public Test {
	public:
		TestMenu(Test*& current_test_pointer);
		~TestMenu();

		void OnImGuiRender() override;
	private:
		Test*& current_test_;
		std::vector<std::pair<std::string, std::function<Test* ()>>> tests_;
	};
}