#pragma once

#include "Minimal.h"

#include <vector>
#include <functional>
#include <tuple>

namespace test {
	
	class Test
	{
	public:
		Test() {};
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
		virtual void Input() {}
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTestPointer);

		void OnImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			print("Registering Test: " << name);
			m_Tests.push_back(std::make_pair(name, []() { return new T; }));
		}

	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
	};
}