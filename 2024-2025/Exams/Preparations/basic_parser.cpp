#include <iostream>
#include <string>
#include <stack>
using namespace std;

string parse(const string& str)
{
	stack<char> result;

	for (char ch : str)
	{
		if (ch >= 'a' && ch <= 'z')
			result.push(ch);

		else if (ch == '*' && !result.empty()) 
		{
			result.pop();
		}
		else if (ch == '$' && !result.empty()) 
		{
			result.push(result.top());
		}
	}

	string finalResult;

	while (!result.empty())
	{
		finalResult = result.top() + finalResult;
		result.pop();
	}

	return finalResult;
}

int main()
{
	string sample1 = "abc*$$*d$a$$zz*";
	string sample2 = "aaa***";
	string sample3 = "aaa$";

	string res1 = parse(sample1);
	string res2 = parse(sample2);
	string res3 = parse(sample3);

	cout << res1 << endl;
	cout << res2 << endl;
	cout << res3 << endl;

}