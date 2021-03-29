#include "LinEqSolve.h"

namespace LinEqSolve
{
	int* lin_eq_solve(int a, int  b, int  c, int  d, int  e, int  f)
	{
		int ans[3] = { 0, 0, 0 };
		if ((a == 0) && (b == 0) && (c == 0) && (d == 0) && (e == 0) && (f == 0))
		{
			ans[0] = 5;
		}
		else if ((a * d - c * b != 0) && ((e * d - b * f != 0) || (a * f - c * e != 0)))
		{
			double y = (a * f - c * e) / (a * d - c * b);
			double x = (d * e - b * f) / (d * a - b * c);
			ans[0] = 2;
			ans[1] = x;
			ans[2] = y;
		}
		else if (((a * d - c * b == 0) && ((e * d - b * f != 0) || (a * f - c * e != 0))) ||
			(b != 0 && d != 0) && (a == 0 && c == 0 && e / b != f / d) ||
			(a != 0 && c != 0) && (b == 0 && d == 0 && e / a != f / c) ||
			(f != 0) && (a == 0 && b == 0 && c == 0 && d == 0 && (e / f > 0)))
		{
			if (((a == 0 && b == 0 && e == 0 && d != 0 && c == 0) ||
				(c == 0 && d == 0 && f == 0 && b != 0 && a == 0)))
			{
				double y;
				if (b == 0)
					y = f / d;
				else if (d == 0)
					y = e / b;
				else if (e == 0 || f == 0)
					y = 0;
				ans[0] = 4;
				ans[1] = y;
			}
			else if (((a == 0 && b == 0 && e == 0 && c != 0 && d == 0) ||
				(c == 0 && d == 0 && f == 0 && a != 0 && b == 0)))
			{
				double x;
				if (a == 0)
					x = f / c;
				else if (c == 0)
					x = e / a;
				else if (e == 0 || f == 0)
					x = 0;
				ans[0] = 3;
				ans[1] = x;
			}
			else
			{
				ans[0] = 0;
			}
		}
		else if (a == 0 && c == 0)
		{
			double y;
			if (e == 0)
				y = f / d;
			else if (f == 0)
				y = e / b;
			else
				y = e / b;
			ans[0] = 4;
			ans[1] = y;
		}
		else if (b == 0 && d == 0)
		{
			double x;
			if (e == 0 && c != 0)
				x = f / c;
			else if (f == 0 && a != 0)
				x = e / a;
			else
				x = e / a;
			ans[0] = 3;
			ans[1] = x;
		}
		else if (b == 0 && e == 0)
		{
			double k, n;
			k = -c / d;
			n = f / d;
			ans[0] = 1;
			ans[1] = k;
			ans[2] = n;
		}
		else if (d == 0 && f == 0)
		{
			double k, n;
			k = -a / b;
			n = e / b;
			ans[0] = 1;
			ans[1] = k;
			ans[2] = n;
		}
		else if (a == 0 && e == 0)
		{
			double k, n;
			k = -d / c;
			n = f / c;
			ans[0] = 1;
			ans[1] = k;
			ans[2] = n;
		}
		else if (c == 0 && f == 0)
		{
			double k, n;
			k = -b / a;
			n = e / a;
			ans[0] = 1;
			ans[1] = k;
			ans[2] = n;
		}
		else if ((a / b == c / d))
		{
			double k, n;
			k = -c / d;
			n = f / d;
			ans[0] = 1;
			ans[1] = k;
			ans[2] = n;
		}
		else
		{
			ans[0] = -1;
		}
		return ans;
	}
}