#include <iostream>
#include <bitset>
#include <vector>
#include <sstream>

using namespace std;

const int timeStep = 4;

struct Pair {
	bitset<6> firstEl;
	bitset<6> secondEl;
};

template <typename T>
string to_string(T Number)
{
	ostringstream sstr;
	sstr << Number;
	return sstr.str();
}

template <unsigned int N>
bitset<N> binarySum(bitset<N> firstNumber, bitset<N> secondNumber) {
	firstNumber = firstNumber >> 1;
	bool additionalOne = false;
	bitset<N> resultSet("0");
	for (unsigned int i = 0; i < N; i++) {
		resultSet[i] = (firstNumber[i] ^ secondNumber[i])
			^ additionalOne;
		additionalOne = (firstNumber[i] && secondNumber[i]) ||
			(firstNumber[i] && additionalOne) ||
			(secondNumber[i] && additionalOne);
	}
	return resultSet;
}

template <unsigned int N, unsigned int R = 2 * N>
bitset<R> binaryConversion(bitset<N> number, bool element) {
	if (!element)
	{
		return bitset<R>("0");
	}
	else {
		return bitset<R>(number.to_ulong());
	}
}


template <unsigned int N = 6, unsigned int R = 2 * N>
void binaryMultiplyCout(vector<Pair> pairs) {
	int currentTime = 0;
	vector <bitset<R>> rezTempSet;
	vector <int> rezCurrentTime;
	for (int i = 0; i < pairs.size(); i++) {
		cout << i + 1 << " Decimal " << to_string(pairs[i].firstEl.to_ulong()) << ' ' << to_string(pairs[i].secondEl.to_ulong()) << endl;
	}
	vector<vector<string>> statuses(pairs.size());
	for (int i = 0; i < pairs.size(); i++, currentTime += timeStep * (i)) {

		string status = "";
		bitset<R> tempSet("0");

		cout << "\nI|Before shift|After shift | temp. sum  |Time\n---------------------------------------------\n";
		for (int k = N - 1; k >= 0; k--) {
			status += to_string(i + 1) + " ";

			bitset<R> secEl = binaryConversion(pairs[i].secondEl, pairs[i].firstEl[N-1-k]);	
			status += secEl.to_string() + " ";
			secEl = secEl << N - 1;
			status += secEl.to_string() + " ";

			tempSet = binarySum(tempSet,secEl);
			status += tempSet.to_string() + " ";
			status += to_string(currentTime) + "\n";
			currentTime += timeStep;		
		}
		rezTempSet.push_back(tempSet);
		rezCurrentTime.push_back(currentTime);
		currentTime = 0;
		statuses[i].push_back(status);
		cout << status << endl;
		cout << "---------------------------------------------\n";
	}
	for (int i = 0; i < pairs.size(); i++) {
		cout << i + 1 << " Decimal " << to_string(rezTempSet[i].to_ulong()) << "  Time = " << to_string(rezCurrentTime[i]) << endl;
	}
}

int main()
{
	vector<Pair> pairs;
	Pair pair;
	pair.firstEl = bitset<6>("110011");
	pair.secondEl = bitset<6>("110011");
	pairs.push_back(pair);

	pair.firstEl = bitset<6>("101101");
	pair.secondEl = bitset<6>("111111");
	pairs.push_back(pair);

	pair.firstEl = bitset<6>("101001");
	pair.secondEl = bitset<6>("101000");
	pairs.push_back(pair);

	binaryMultiplyCout(pairs);
	system("pause");
}
