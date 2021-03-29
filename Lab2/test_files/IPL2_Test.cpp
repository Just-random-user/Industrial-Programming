#include "pch.h"
#include "CppUnitTest.h"
#include "..\IndustrialProgrammingL2\LinEqSolve.cpp"

using namespace LinEqSolve;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IPL2Test
{
	TEST_CLASS(IPL2Test)
	{
	public:
		TEST_METHOD(CastingFive)
		{
			int* ans = LinEqSolve::lin_eq_solve(0, 0, 0, 0, 0, 0);
			int actual = ans[0];
			Assert::AreEqual(5, actual);
		}
		TEST_METHOD(CastingZero)
		{
			int* ans = LinEqSolve::lin_eq_solve(0, 0, 0, 5, 2, 1);
			int actual = ans[0];
			Assert::AreEqual(0, actual);
		}
		TEST_METHOD(CastingFour)
		{
			int* ans = LinEqSolve::lin_eq_solve(0, 0, 0, 5, 0, 5);
			int actual = ans[0];
			int y = ans[1];
			Assert::AreEqual(4, actual);
			Assert::AreEqual(1, y);
		}
		TEST_METHOD(CastingFourTheRest)
		{
			int* ans = LinEqSolve::lin_eq_solve(0, 5, 0, 4, 5, 4);
			int actual = ans[0];
			int y = ans[1];
			Assert::AreEqual(4, actual);
			Assert::AreEqual(1, y);
		}
		TEST_METHOD(CastingTwo)
		{
			int* ans = LinEqSolve::lin_eq_solve(1, 1, 2, 5, 0, 5);
			int actual = ans[0];
			int x = ans[1];
			int y = ans[2];
			Assert::AreEqual(2, actual);
			Assert::AreEqual(-1, x);
			Assert::AreEqual(1, y);
		}
		TEST_METHOD(CastingThree)
		{
			int* ans = LinEqSolve::lin_eq_solve(12, 0, 0, 0, 0, 0);
			int actual = ans[0];
			int x = ans[1];
			Assert::AreEqual(3, actual);
			Assert::AreEqual(0, x);
		}
		TEST_METHOD(CastingThreeTheRest)
		{
			int* ans = LinEqSolve::lin_eq_solve(0, 0, 10, 0, 0, 10);
			int actual = ans[0];
			int x = ans[1];
			Assert::AreEqual(3, actual);
			Assert::AreEqual(1, x);
		}
		TEST_METHOD(CastingOneAB_CD)
		{
			int* ans = LinEqSolve::lin_eq_solve(1, 1, 1, 1, 1, 1);
			int actual = ans[0];
			int k = ans[1];
			int n = ans[2];
			Assert::AreEqual(1, actual);
			Assert::AreEqual(-1, k);
			Assert::AreEqual(1, n);
		}
		TEST_METHOD(CastingOneDF)
		{
			int* ans = LinEqSolve::lin_eq_solve(9, 9, 0, 0, 0, 0);
			int actual = ans[0];
			int k = ans[1];
			int n = ans[2];
			Assert::AreEqual(1, actual);
			Assert::AreEqual(-1, k);
			Assert::AreEqual(0, n);
		}
		TEST_METHOD(CastingOneCF)
		{
			int* ans = LinEqSolve::lin_eq_solve(45, 2, 0, 45, 0, 0);
			int actual = ans[0];
			int k = ans[1];
			int n = ans[2];
			Assert::AreEqual(1, actual);
			Assert::AreEqual(0, k);
			Assert::AreEqual(0, n);
		}
		TEST_METHOD(CastingOneAE)
		{
			int* ans = LinEqSolve::lin_eq_solve(0, 45, 45, 45, 0, 0);
			int actual = ans[0];
			int k = ans[1];
			int n = ans[2];
			Assert::AreEqual(1, actual);
			Assert::AreEqual(-1, k);
			Assert::AreEqual(0, n);
		}
		TEST_METHOD(CastingOneBE)
		{
			int* ans = LinEqSolve::lin_eq_solve(0, 0, 15, 40, 0, 0);
			int actual = ans[0];
			int k = ans[1];
			int n = ans[2];
			Assert::AreEqual(1, actual);
			Assert::AreEqual(0, k);
			Assert::AreEqual(0, n);
		}
	};
}
