#include<iostream>
#include <vector>
#include <fstream>
using namespace std;
vector<string> name(3);
vector<int> indexVector(3);
ifstream input("WarAndPeace.txt");
string str, firstNm1 = "Makar", lastNm1 = "Alexeevich", firstNm2 = "Joseph",
		lastNm2 = "Bazdeev", firstNm3 = "Boris", lastNm3 = "Drubetskoy";
int addVector(string str, string firstNm, string lastNm, int i) {
	int found = str.find(firstNm);

	if (found != std::string::npos) {

		if ((found + 1 + firstNm.length() + lastNm.length()) < str.length()) {

			if ((lastNm.compare(
					str.substr(found + 1 + firstNm.length(), lastNm.length())))
					== 0) {

				name.resize(i + 1);
				indexVector.resize(i + 1);
				indexVector.at(i) = found + 1;
				name.at(i) = firstNm + " " + lastNm;

				i++;
			}
		} else {
			getline(input, str);
			if ((lastNm.compare(str.substr(0, lastNm.length()))) == 0) {
				name.resize(i + 1);
				indexVector.resize(i + 1);
				indexVector.at(i) = found + 1;
				name.at(i) = firstNm + " " + lastNm;
				i = 0;
				i = addVector(str, firstNm1, lastNm1, i);
				i = addVector(str, firstNm2, lastNm2, i);
				i = addVector(str, firstNm3, lastNm3, i);
			}
		}
	}
	return i;
}
int main() {

	ifstream input("WarAndPeace.txt");

	size_t found;

	int i = 0, line = 0, j = 0;

	cout<< "LINE   " <<"POSITION  "<<"NAME";

	while (getline(input, str)) {

		line++;
		i = 0;
		j = 0;

		i = addVector(str, firstNm1, lastNm1, i);
		i = addVector(str, firstNm2, lastNm2, i);
		i = addVector(str, firstNm3, lastNm3, i);
		if (name.size() != 0) {
			for (int k = 0; k < name.size(); k++) {
				cout << line << " " << indexVector.at(k) << " " << name.at(k)
						<< endl;
			}
		}
		name.clear();
		indexVector.clear();

	}
}
