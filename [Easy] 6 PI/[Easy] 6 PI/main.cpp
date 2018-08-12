#include <string>

using namespace std;

const float PIToThirtyPlaces = 3.1415926535897932384626433832795;

void CalcPie(float fPI, float fDivider, bool IsMinus, int tracker)
{
	IsMinus = !IsMinus;
	if (IsMinus)
	{
		fDivider += 2;
		fPI -= 4 / fDivider;
		CalcPie(fPI, fDivider, IsMinus, tracker);
	} else {
		fDivider += 2;
		fPI += 4 / fDivider;
		CalcPie(fPI, fDivider, IsMinus, tracker);
	}
}

int main()
{
	bool IsPlus = false;
	float divider = 1.0f;
	int tracker = 0;
	float pi = 4.0f/divider;
	float nPI = 4.0f / 1.0f;
	nPI = nPI - 4.0f / 3.0f;
	nPI = nPI + 4.0f / 5.0f;
	nPI = nPI - 4.0f / 7.0f;
	nPI = nPI + 4.0f / 9.0f;
	nPI = nPI - 4.0f / 11.0f;
	
	CalcPie(pi, divider, IsPlus, tracker);

	return 0;
}