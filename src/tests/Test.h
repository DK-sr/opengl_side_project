#pragma once
#include <vector>
#include <iostream>
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
		~TestMenu() {}

		void OnImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string& name) {
			std::cout << "Registering test " << name << std::endl;
			tests_.push_back(std::make_pair(name, []() { return new T();  }));
		}

	private:
		Test*& current_test_;
		std::vector<std::pair<std::string, std::function<Test* ()>>> tests_;
	};
}