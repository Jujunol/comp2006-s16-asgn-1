#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

const string quizFilename("quiz.txt"), namesFilename("names.txt");

struct User {
	string fname;
	string lname;
	int score;
	bool saved;
};

User fetchUser(ifstream& fs, string& fname, string& lname) {
	string t_fname, t_lname;
	int t_score;

	while (fs >> t_fname >> t_lname >> t_score) {
		if (t_fname == fname && t_lname == lname) {
			return User{ fname, lname, t_score, true };
		}
	}
	return User{ fname, lname, 0, false };
}

void saveUser(ifstream& ifs, User& user) {
	if (!user.saved) {
		ofstream ofs(namesFilename, fstream::out | fstream::app);
		ofs << user.fname << " " << user.lname << " " << user.score << endl;
		ofs.close();
	}
	else {
		stringstream buffer;
		string t_fname, t_lname;
		int t_score;

		while (ifs >> t_fname >> t_lname >> t_score) {
			if (t_fname == user.fname && t_lname == user.lname) {
				buffer << user.fname << " " << user.lname << " " << user.score << endl;
			}
			else {
				buffer << t_fname << " " << t_lname << " " << t_score << endl;
			}
		}
		
		ofstream ofs(namesFilename, fstream::trunc);
		while (buffer >> t_fname >> t_lname >> t_score) {
			ofs << t_fname << " " << t_lname << " " << t_score << endl;
		}
		ofs.close();
	}
}

int main() {
	string fname, lname;

	cout << "Enter your Firstname and Lastname (eg. John Smith) then press enter: ";
	cin >> fname >> lname; cin.ignore();

	ifstream ifs(namesFilename);
	User user = fetchUser(ifs, fname, lname);

	cout << (!user.saved ? "Welcome, " : "Hello again, ") << user.fname << endl;

	saveUser(ifs, user);

	ifs.close();

	getchar();
	return 0;
}