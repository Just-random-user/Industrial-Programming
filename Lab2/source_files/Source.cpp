#include <iostream>
#include <cmath>
#include "LinEqSolve.h"

using namespace std;
using namespace LinEqSolve;

int main()
{
	double a, b, c, d, e, f;
	cin >> a >> b >> c >> d >> e >> f;
	int* ans;
	ans = lin_eq_solve(a, b, c, d, e, f);
	switch (ans[0])
	{
	case 0:
	case 5:
	{
		cout << ans[0];
		break;
	}
	case 3:
	case 4:
	{
		cout << ans[0] << ' ' << ans[1];
		break;
	}
	case 1:
	case 2:
	{
		cout << ans[0] << ' ' << ans[1] << ' ' << ans[2];
		break;
	}
	default:
	{
		cout << "Are you kidding me?";
		break;
	}
	}
	cout << endl;
	return 0;
}