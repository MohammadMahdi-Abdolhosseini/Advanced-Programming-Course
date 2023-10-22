#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <unordered_set>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

const char TIME_SEPARATOR = '-';
const char MEMBER_SEPARATOR = '$';
const string LINE_SEPARATOR = "---";
const int NON_VALID = -8888;
const int WORKING_DAYS = 30;
const string EMPLOYEE_NOT_FOUND = "EMPLOYEE_NOT_FOUND";
const string TEAM_NOT_FOUND = "TEAM_NOT_FOUND";
const string INVALID_LEVEL = "INVALID_LEVEL";
const string INVALID_ARGUMENTS = "INVALID_ARGUMENTS";
const string INVALID_INTERVAL = "INVALID_INTERVAL";
const string OK = "OK";
const char PLACEHOLDER = '-';

class SalaryConfig {
public:
	SalaryConfig(string _level, int _baseSalary, int _salaryPerHour, int _salaryPerExtraHour, int _officialWorkingHours, int _taxPercentage) {
		level = _level;
		baseSalary = _baseSalary;
		salaryPerHour = _salaryPerHour;
		salaryPerExtraHour = _salaryPerExtraHour;
		officialWorkingHours = _officialWorkingHours;
		taxPercentage = _taxPercentage;
	}

	string getLevel() {
		return level;
	}

	float calcTotalEarning(int hours) {
		return calcRawSalary(hours) * (100 - taxPercentage) / 100.0f;
	}

	float calcTax(int hours) {
		return calcRawSalary(hours) * taxPercentage / 100.0f;
	}

	int calcRawSalary(int hours)
	{
		int salary = baseSalary;
		if (hours < officialWorkingHours) {
			salary += hours * salaryPerHour;
		}
		else {
			salary += officialWorkingHours * salaryPerHour + (hours - officialWorkingHours) * salaryPerExtraHour;
		}

		return salary;
	}

	float getTaxPercentage() {
		return taxPercentage;
	}

	void printConfig() {
		cout << "Base Salary: " << baseSalary << endl;
		cout << "Salary Per Hour: " << salaryPerHour << endl;
		cout << "Salary Per Extra Hour: " << salaryPerExtraHour << endl;
		cout << "Official Working Hours: " << officialWorkingHours << endl;
		cout << "Tax: " << taxPercentage << "%" << endl;
	}

	void updateNewConfig(string _baseSalary, string _salaryPerHour, string _salaryPerExtraHour,
		string _officialWorkingHours, string _taxPercentage) {
		if (_baseSalary[0] != PLACEHOLDER) {
			baseSalary = stoi(_baseSalary);
		}
		if (_salaryPerHour[0] != PLACEHOLDER) {
			salaryPerHour = stoi(_salaryPerHour);
		}
		if (_salaryPerExtraHour[0] != PLACEHOLDER) {
			salaryPerExtraHour = stoi(_salaryPerExtraHour);
		}
		if (_officialWorkingHours[0] != PLACEHOLDER) {
			officialWorkingHours = stoi(_officialWorkingHours);
		}
		if (_taxPercentage[0] != PLACEHOLDER) {
			taxPercentage = stoi(_taxPercentage);
		}
	}

private:
	string level;
	int baseSalary;
	int salaryPerHour;
	int salaryPerExtraHour;
	int officialWorkingHours;
	int taxPercentage;

};

class WorkingHour {
public:
	WorkingHour(int _employee_id, int _day, string _working_interval) {
		day = _day;
		employee_id = _employee_id;
		extractInterval(_working_interval, startHour, endHour);
	}

	void printInfo() {
		cout << "employee_id: " << employee_id << endl;
		cout << "day: " << day << endl;
		cout << "working_interval: " << startHour << TIME_SEPARATOR << endHour << endl;
	}

	int getEployeeID() {
		return employee_id;
	}

	int getDay() {
		return day;
	}

	int getStartHour() {
		return startHour;
	}

	int getEndHour() {
		return endHour;
	}

	int getIntervalLength() {
		return endHour - startHour;
	}

	bool hasOverlap(int _startHour, int _endHour) {
		return !((_startHour < startHour && _endHour < startHour) || (_startHour > endHour && _endHour > endHour));
	}

private:
	int employee_id;
	int day;
	int startHour;
	int endHour;

	void extractInterval(string input_str, int& startHour, int& endHour) {
		stringstream ss(input_str);
		getline(ss, input_str, TIME_SEPARATOR);
		startHour = stoi(input_str);
		getline(ss, input_str);
		endHour = stoi(input_str);
	}
};

class Employee {
public:
	Employee(int _id, string _name, int _age, string _level) {
		id = _id;
		name = _name;
		age = _age;
		level = _level;
		teamID = -8888;
		bonus = 0;
	}

	void printMinimalReportSalary() {
		cout << "ID: " << id << endl;
		cout << "Name: " << name << endl;
		cout << "Total Working Hours: " << getTotalWorkingHours() << endl;
		cout << "Total Earning: " << getTotalEarning() << endl;
		cout << LINE_SEPARATOR << endl;
	}

	void printFullReportSalary() {
		cout << "ID: " << id << endl;
		cout << "Name: " << name << endl;
		cout << "Age: " << age << endl;
		cout << "Level: " << level << endl;
		if (teamID == NON_VALID) {
			cout << "Team ID: N/A" << endl;
		}
		else {
			cout << "Team ID: " << teamID << endl;
		}
		cout << "Total Working Hours: " << getTotalWorkingHours() << endl;
		cout << "Absent Days: " << getAbsentDays() << endl;
		cout << "Salary: " << getRawSalary() << endl;
		cout << "Bonus: " << int(round(getRawSalary() * (bonus / 100.0f))) << endl;
		cout << "Tax: " << int(round(getTax())) << endl;
		cout << "Total Earning: " << getTotalEarning() << endl;
	}

	void assignWorkingHour(WorkingHour* _workingHour) {
		if (_workingHour->getEployeeID() == id) {
			workingHours.push_back(_workingHour);
		}
	}

	bool hasIntervalOverlap(WorkingHour* _workingHour) {
		for (auto w : workingHours) {
			if (w->getDay() != _workingHour->getDay()) {
				continue;
			}

			if (w->hasOverlap(_workingHour->getStartHour(), _workingHour->getEndHour())) {
				return true;
			}
		}
		return false;
	}



	int getID() {
		return id;
	}

	int getTeamID() {
		return teamID;
	}

	void removeWorkingHoursForDay(int day) {
		for (auto it = workingHours.begin(); it != workingHours.end(); ) {
			if ((*it)->getDay() == day) {
				it = workingHours.erase(it);
			}
			else {
				++it;
			}
		}
	}

	string getName() {
		return name;
	}

	int getTotalWorkingHours() {
		int totalWorkingHours = 0;
		for (auto wh : workingHours) {
			totalWorkingHours += wh->getIntervalLength();
		}
		return totalWorkingHours;
	}

	void assignTeamID(int _teamID) {
		teamID = _teamID;
	}

	int getRawSalary() {
		return config->calcRawSalary(getTotalWorkingHours());
	}

	float getTax() {
		return config->calcTax(getTotalWorkingHours()) + getRawSalary() * bonus * config->getTaxPercentage() / 10000.0f;
	}

	float getNoBonusTotalEarning() {
		return config->calcTotalEarning(getTotalWorkingHours());
	}

	int getTotalEarning() {
		return round(getNoBonusTotalEarning() + getBonusAmount());
	}

	float getBonusAmount() {
		return getNoBonusTotalEarning() * (bonus / 100.0f);
	}

	void assignConfig(vector<SalaryConfig>& configs) {
		for (int c = 0; c < configs.size(); c++) {
			if (configs[c].getLevel() == level) {
				config = &configs[c];
			}
		}
	}

	void assignBonus(int _bonus) {
		bonus = _bonus;
	}

private:
	int id;
	string name;
	int age;
	string level;
	SalaryConfig* config;
	vector<WorkingHour*> workingHours;
	int teamID;
	int bonus;

	int getAbsentDays() {
		unordered_set<int> workDays;
		for (auto wh : workingHours) {
			workDays.insert(wh->getDay());
		}
		return WORKING_DAYS - workDays.size();
	}

};

class Team {
public:
	Team(int _team_id, int _teamHeadID, string _memberIDs, int _bonus_min_working_hours = 0, float _bonus_working_hours_max_variance = 0) {
		team_id = _team_id;
		teamHeadID = _teamHeadID;
		memberIDs = extractMemberIDs(_memberIDs);
		bonus_min_working_hours = _bonus_min_working_hours;
		bonus_working_hours_max_variance = _bonus_working_hours_max_variance;
		bonus = 0;
	}

	void printReportSalary() {
		cout << "ID: " << team_id << endl;
		cout << "Head ID: " << teamHead->getID() << endl;
		cout << "Head Name: " << teamHead->getName() << endl;
		cout << "Team Total Working Hours: " << getTotalWorkingHours() << endl;
		cout << "Average Member Working Hours: " << fixed << setprecision(1) << round(getTotalWorkingHours() / (float)members.size() * 10) / 10.0f << endl;
		cout << "Bonus: " << bonus << endl;
		cout << LINE_SEPARATOR << endl;
		for (auto m : members) {
			cout << "Member ID: " << m->getID() << endl;
			cout << "Total Earning: " << m->getTotalEarning() << endl;
			cout << LINE_SEPARATOR << endl;
		}
	}

	int getTeamID() {
		return team_id;
	}

	void updateBonus(int _bonus) {
		bonus = _bonus;
		for (int m = 0; m < members.size(); m++) {
			members[m]->assignBonus(_bonus);
		}
	}

	void assignMembers(vector<Employee>& _employees) {
		for (int e = 0; e < _employees.size(); e++) {
			if (find(memberIDs.begin(), memberIDs.end(), _employees[e].getID()) != memberIDs.end()) {
				members.push_back(&_employees[e]);
				_employees[e].assignTeamID(team_id);
			}
			if (teamHeadID == _employees[e].getID()) {
				teamHead = &_employees[e];
			}
		}
	}

private:
	int team_id;
	int teamHeadID;
	Employee* teamHead;
	vector<int> memberIDs;
	vector<Employee*> members;
	int bonus_min_working_hours;
	float bonus_working_hours_max_variance;
	int bonus;

	vector<int> extractMemberIDs(string input_str) {
		vector<int> memberIDs;
		istringstream ss(input_str);
		string id;
		while (std::getline(ss, id, MEMBER_SEPARATOR)) {
			memberIDs.push_back(stoi(id));
		}
		return memberIDs;
	}

	int getTotalWorkingHours() {
		int totalWorkingHours = 0;
		for (auto m : members) {
			totalWorkingHours += m->getTotalWorkingHours();
		}
		return totalWorkingHours;
	}

};

vector<vector<string>> readCSV(string filename) {
	vector<vector<string>> data;
	ifstream file(filename);

	if (!file.is_open()) {
		cout << "Error opening file" << endl;
		return data;
	}

	string line;

	while (getline(file, line)) {
		stringstream ss(line);
		vector<string> row;

		while (getline(ss, line, ',')) {
			row.push_back(line);
		}

		data.push_back(row);
	}

	file.close();
	return data;
}

vector<Employee> initEmployees(const vector<vector<string>>& data, vector<SalaryConfig>& salaryConfigs) {
	vector<Employee> employees;
	for (int line = 1; line < data.size(); line++)
	{
		Employee e(stoi(data[line][0]), data[line][1], stoi(data[line][2]), data[line][3]);
		e.assignConfig(salaryConfigs);
		employees.push_back(e);
	}
	return employees;
}

vector<WorkingHour*> initWorkingHours(const vector<vector<string>>& data) {
	vector<WorkingHour*> workingHours;
	for (int line = 1; line < data.size(); line++)
	{
		WorkingHour* w = new WorkingHour(stoi(data[line][0]), stoi(data[line][1]), data[line][2]);
		workingHours.push_back(w);
	}
	return workingHours;
}

vector<SalaryConfig> initSalaryConfig(const vector<vector<string>>& data) {
	vector<SalaryConfig> salaryConfigs;
	for (int line = 1; line < data.size(); line++)
	{
		SalaryConfig s(data[line][0], stoi(data[line][1]), stoi(data[line][2]), stoi(data[line][3]), stoi(data[line][4]), stoi(data[line][5]));
		salaryConfigs.push_back(s);
	}
	return salaryConfigs;
}

void assignWorkingHoursToEmployees(vector<Employee>& employees, vector<WorkingHour*>& workingHours) {
	for (int e = 0; e < employees.size(); e++) {
		for (int w = 0; w < workingHours.size(); w++) {
			employees[e].assignWorkingHour(workingHours[w]);
		}
	}
}

vector<Team> initTeams(const vector<vector<string>>& data, vector<Employee>& employees) {
	vector<Team> teams;
	for (int line = 1; line < data.size(); line++)
	{
		Team t(stoi(data[line][0]), stoi(data[line][1]), data[line][2], stoi(data[line][3]), stof(data[line][4]));
		t.assignMembers(employees);
		teams.push_back(t);
	}
	return teams;
}

vector<string> splitToWords(string line)
{
	vector<string> words;
	stringstream sLine(line);
	string word;
	while (sLine >> word)
	{
		words.push_back(word);
	}
	return words;
}

void reportSalaries(const vector<Employee>& employees) {
	for (auto e : employees)
	{
		e.printMinimalReportSalary();
	}
}

void reportEmployeeSalary(const vector<Employee>& employees, int id) {
	bool isFound = false;
	for (auto e : employees) {
		if (e.getID() == id) {
			e.printFullReportSalary();
			isFound = true;
		}
	}
	if (!isFound) {
		cout << EMPLOYEE_NOT_FOUND << endl;
	}
}

void reportTeamSalary(const vector<Team>& teams, int teamID) {
	bool isFound = false;
	for (auto t : teams) {
		if (t.getTeamID() == teamID) {
			t.printReportSalary();
			isFound = true;
		}
	}
	if (!isFound) {
		cout << TEAM_NOT_FOUND << endl;
	}
}

int calcTotalHoursInDay(vector<WorkingHour*> workingHours, int day) {
	int totalHours = 0;
	for (auto wh : workingHours) {
		if (wh->getDay() == day) {
			totalHours += wh->getIntervalLength();
		}
	}
	return totalHours;
}

vector<int> getMaxIndices(vector<float> v) {
	float maxValue = v[0];
	vector<int> maxIndices = { 0 };

	for (int i = 1; i < v.size(); i++) {
		if (v[i] > maxValue) {
			maxValue = v[i];
			maxIndices.clear();
			maxIndices.push_back(i);
		}
		else if (v[i] == maxValue) {
			maxIndices.push_back(i);
		}
	}
	return maxIndices;
}

vector<int> getMinIndices(vector<float> v) {
	float minValue = v[0];
	vector<int> minIndices = { 0 };

	for (int i = 1; i < v.size(); i++) {
		if (v[i] < minValue) {
			minValue = v[i];
			minIndices.clear();
			minIndices.push_back(i);
		}
		else if (v[i] == minValue) {
			minIndices.push_back(i);
		}
	}
	return minIndices;


}

void showSalaryConfig(const vector<SalaryConfig>& salaryConfigs, string level) {
	bool isFound = false;
	for (auto sc : salaryConfigs) {
		if (sc.getLevel() == level) {
			sc.printConfig();
			isFound = true;
		}
	}
	if (!isFound) {
		cout << INVALID_LEVEL << endl;

	}

}

void reportTotalHoursPerDay(vector<WorkingHour*> workingHours, int startDay, int endDay) {

	if (startDay < 1 || startDay > WORKING_DAYS || endDay < 1 || endDay > WORKING_DAYS || startDay > endDay) {
		cout << INVALID_ARGUMENTS << endl;
		return;
	}

	vector<float> results;
	for (int day = startDay; day <= endDay; day++) {
		results.push_back(calcTotalHoursInDay(workingHours, day));

	}

	int i = 0;
	for (int day = startDay; day <= endDay; day++) {
		cout << "Day #" << day << ": " << (int)results[i] << endl;
		i++;
	}

	cout << LINE_SEPARATOR << endl;

	vector<int> minDays = getMinIndices(results);
	vector<int> maxDays = getMaxIndices(results);
	cout << "Day(s) with Max Working Hours: ";
	for (int i : maxDays) {
		cout << i + startDay;
		if (i != maxDays[maxDays.size() - 1]) {
			cout << ' ';
		}
	}
	cout << endl;

	cout << "Day(s) with Min Working Hours: ";
	for (int i : minDays) {
		cout << i + startDay;
		if (i != minDays[minDays.size() - 1]) {
			cout << ' ';
		}
	}
	cout << endl;

}

int calcTotalEmployeesInHour(vector<WorkingHour*> workingHours, int hour) {
	int totalEmployees = 0;
	for (auto wh : workingHours) {
		if (hour >= wh->getStartHour() && hour + 1 <= wh->getEndHour()) {
			totalEmployees++;
		}
	}

	return totalEmployees;
}

void reportEmployeePerHour(vector<WorkingHour*> workingHours, int startHour, int endHour) {

	if (startHour < 0 || startHour > 24 || endHour < 0 || endHour > 24 || startHour > endHour) {
		cout << INVALID_ARGUMENTS << endl;
		return;
	}

	vector<float> avgs;
	for (int hour = startHour; hour < endHour; hour++) {
		avgs.push_back(round((calcTotalEmployeesInHour(workingHours, hour) / 30.0f) * 10) / 10.0f);

	}

	int i = 0;
	for (int hour = startHour; hour < endHour; hour++) {
		cout << hour << TIME_SEPARATOR << hour + 1 << ": " << avgs[i] << endl;
		i++;
	}

	cout << LINE_SEPARATOR << endl;

	vector<int> minHours = getMinIndices(avgs);
	vector<int> maxHours = getMaxIndices(avgs);
	cout << "Period(s) with Max Working Employees: ";
	for (int i : maxHours) {
		cout << i + startHour << TIME_SEPARATOR << i + startHour + 1 << " ";
	}
	cout << endl;

	cout << "Period(s) with Min Working Employees: ";
	for (int i : minHours) {
		cout << i + startHour << TIME_SEPARATOR << i + startHour + 1 << " ";
	}
	cout << endl;

}

void updateSalaryConfig(vector<SalaryConfig>& salaryConfig, string level, string baseSalary,
	string salaryPerHour, string salaryPerExtraHour, string officialWorkingHours, string taxPercentage) {
	bool isFound = false;
	for (int i = 0; i < salaryConfig.size(); i++) {
		if (salaryConfig[i].getLevel() == level) {
			salaryConfig[i].updateNewConfig(baseSalary, salaryPerHour, salaryPerExtraHour, officialWorkingHours, taxPercentage);
			isFound = true;
		}
	}
	if (!isFound) {
		cout << INVALID_LEVEL << endl;
	}
	else {
		cout << OK << endl;
	}
}

bool isValidPersentage(int persentage) {
	if (persentage > 100 || persentage < 0) {
		return false;
	}
	else {
		return true;
	}
}


void updateTeamBonus(vector<Team>& teams, int teamID, int bonusPercentage) {
	if (!isValidPersentage(bonusPercentage)) {
		cout << INVALID_ARGUMENTS << endl;
		return;
	}
	bool isFound = false;
	for (int t = 0; t < teams.size(); t++) {
		if (teams[t].getTeamID() == teamID) {
			teams[t].updateBonus(bonusPercentage);
			isFound = true;
		}
	}
	if (!isFound) {
		cout << TEAM_NOT_FOUND << endl;
	}
	else {
		cout << OK << endl;
	}
}


void deleteWorkingHours(vector<Employee>& employees, vector <WorkingHour*>& workingHours, int ID, int day) {
	if (day > WORKING_DAYS || day < 1) {
		cout << INVALID_ARGUMENTS << endl;
		return;
	}
	bool isFound = false;
	for (int i = 0; i < employees.size(); i++) {
		if (employees[i].getID() == ID) {
			employees[i].removeWorkingHoursForDay(day);
			isFound = true;
		}
	}

	if (!isFound) {
		cout << EMPLOYEE_NOT_FOUND << endl;
		return;
	}

	vector<WorkingHour*>::iterator it;
	it = workingHours.begin();
	while (it != workingHours.end()) {
		if ((*it)->getDay() == day) {
			it = workingHours.erase(it);
		}
		else {
			it++;
		}
	}

	cout << OK << endl;

}

void addWorkingHours(vector<Employee>& employees, vector<WorkingHour*>& workingHours, int ID,
	int day, int startHour, int endHour) {

	if (day > WORKING_DAYS || day < 1 || startHour < 0 || startHour > 24 ||
		endHour < 0 || endHour > 24 || startHour > endHour) {
		cout << INVALID_ARGUMENTS << endl;
		return;
	}

	int isFound = false;
	for (int i = 0; i < employees.size(); i++) {
		if (employees[i].getID() == ID) {
			WorkingHour* w = new WorkingHour(ID, day, to_string(startHour) + "-" + to_string(endHour));
			if (employees[i].hasIntervalOverlap(w)) {
				cout << INVALID_INTERVAL << endl;
				return;
			}

			employees[i].assignWorkingHour(w);
			workingHours.push_back(w);
			isFound = true;

		}
	}

	if (!isFound) {
		cout << EMPLOYEE_NOT_FOUND << endl;
		return;
	}

	cout << OK << endl;

}

void commandHandler(vector<Employee>& employees, vector<Team>& teams,
	vector<WorkingHour*>& workingHours, vector<SalaryConfig>& salaryConfigs) {
	string line;
	while (getline(cin, line))
	{
		vector<string> words = splitToWords(line);

		if (words[0] == "report_salaries")
		{
			reportSalaries(employees);
		}
		else if (words[0] == "report_employee_salary")
		{
			reportEmployeeSalary(employees, stoi(words[1]));
		}
		else if (words[0] == "report_team_salary")
		{
			reportTeamSalary(teams, stoi(words[1]));
		}
		else if (words[0] == "report_total_hours_per_day")
		{
			reportTotalHoursPerDay(workingHours, stoi(words[1]), stoi(words[2]));
		}
		else if (words[0] == "report_employee_per_hour")
		{
			reportEmployeePerHour(workingHours, stoi(words[1]), stoi(words[2]));
		}
		else if (words[0] == "show_salary_config")
		{
			showSalaryConfig(salaryConfigs, words[1]);
		}
		else if (words[0] == "update_salary_config")
		{
			updateSalaryConfig(salaryConfigs, words[1], words[2],
				words[3], words[4], words[5], words[6]);
		}
		else if (words[0] == "add_working_hours")
		{
			addWorkingHours(employees, workingHours, stoi(words[1]), stoi(words[2]),
				stoi(words[3]), stoi(words[4]));
		}
		else if (words[0] == "delete_working_hours")
		{
			deleteWorkingHours(employees, workingHours, stoi(words[1]), stoi(words[2]));
		}
		else if (words[0] == "update_team_bonus")
		{
			updateTeamBonus(teams, stoi(words[1]), stoi(words[2]));
		}
		else if (words[0] == "find_teams_for_bonus")
		{
			//find_teams_for_bonus(teams);
		}
		else
		{
			cerr << "Error: invalid command" << endl;
		}
	}
}

int main() {
	vector<SalaryConfig> salaryConfigs = initSalaryConfig(readCSV("assets/salary_configs.csv"));
	vector<Employee> employees = initEmployees(readCSV("assets/employees.csv"), salaryConfigs);
	vector<WorkingHour*> workingHours = initWorkingHours(readCSV("assets/working_hours.csv"));
	assignWorkingHoursToEmployees(employees, workingHours);
	vector<Team> teams = initTeams(readCSV("assets/teams.csv"), employees);

	commandHandler(employees, teams, workingHours, salaryConfigs);

	return 0;
}
