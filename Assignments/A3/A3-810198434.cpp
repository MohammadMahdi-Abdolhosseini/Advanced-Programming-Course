#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

const int WORK_DAYS = 5;
const int COURSE_DAYS = 2;
const int CLASS_HOURS = 3;
const int NUM_OF_CLASS = 2;
const int BREAK_TIME = 30;
const int CLASS_TIME = 90;
const int FIRST_CLASS_HOUR_START = 7 * 60 + 30;
const int NON_VALID_INDEX = -1;

struct Teacher
{
	string name;
	vector<string> courses;
	vector<vector<bool>> availablity;
	Teacher() : availablity(WORK_DAYS, vector<bool>(CLASS_HOURS)) {};
};

struct AssignedTeacher
{
	string name;
	int classHour;
	bool notFound = true;
};

struct Course
{
	string name;
	vector<int> allowedDays;
	vector<bool> allowedHours;
	vector<AssignedTeacher> assignedTeacher;
	Course() : allowedDays(COURSE_DAYS), allowedHours(CLASS_HOURS), assignedTeacher(NUM_OF_CLASS) {};
};



int dayLabel(string day)
{
	if (day == "Saturday")
		return 0;
	if (day == "Sunday")
		return 1;
	if (day == "Monday")
		return 2;
	if (day == "Tuesday")
		return 3;
	if (day == "Wednesday")
		return 4;
	return 0;
}

vector<Teacher> getTeachersInput(int numOfTeachers)
{
	vector<Teacher> teachers(numOfTeachers);
	for (int n = 0; n < numOfTeachers; ++n)
	{
		cin >> teachers[n].name;
		int numOfAvailableDays;
		cin >> numOfAvailableDays;
		for (int i = 0; i < numOfAvailableDays; ++i)
		{
			string day;
			cin >> day;
			vector<bool> trueRow(CLASS_HOURS, true);
			teachers[n].availablity[dayLabel(day)] = trueRow;
		}
		int numOfCourses;
		cin >> numOfCourses;
		for (int j = 0; j < numOfCourses; ++j)
		{
			string course;
			cin >> course;
			teachers[n].courses.push_back(course);
		}
	}
	return teachers;
}

bool isInClassHour(int classHour, int startTime, int endTime)
{
	if (startTime <= classHour * (BREAK_TIME + CLASS_TIME) + FIRST_CLASS_HOUR_START
		&& endTime >= (classHour)*(BREAK_TIME + CLASS_TIME) + FIRST_CLASS_HOUR_START + CLASS_TIME)
	{
		return true;
	}
	else
	{
		return false;
	}
}

vector<bool> hourLabel(int startTime, int endTime)
{
	vector<bool> classHours(CLASS_HOURS);
	for (int i = 0; i < CLASS_HOURS; ++i)
	{
		classHours[i] = isInClassHour(i, startTime, endTime);
	}
	return classHours;
}

int toMinutes(string time)
{
	int hours = stoi(time.substr(0, time.find(":")));
	int minutes = stoi(time.substr(time.find(":") + 1));
	return hours * 60 + minutes;
}

vector<Course> getCoursesInput(int numOfCourses)
{
	vector<Course> courses(numOfCourses);
	for (int n = 0; n < numOfCourses; ++n)
	{
		cin >> courses[n].name;
		for (int i = 0; i < COURSE_DAYS; ++i)
		{
			string day;
			cin >> day;
			courses[n].allowedDays[i] = dayLabel(day);
		}
		string startTime, endTime;
		cin >> startTime >> endTime;
		courses[n].allowedHours = hourLabel(toMinutes(startTime), toMinutes(endTime));
	}
	return courses;
}

void printTeachersForDebuging(vector<Teacher> teachers)
{
	for (int i = 0; i < teachers.size(); ++i)
	{
		cout << teachers[i].name << endl;
		for (int j = 0; j < WORK_DAYS; ++j)
		{
			for (int k = 0; k < CLASS_HOURS; ++k)
			{
				cout << teachers[i].availablity[j][k] << " ";
			}
			cout << endl;
		}
		for (int j = 0; j < teachers[i].courses.size(); ++j)
		{
			cout << teachers[i].courses[j] << endl;
		}
	}
}

void printCoursesForDebuging(vector<Course> courses)
{
	for (int i = 0; i < courses.size(); ++i)
	{
		cout << courses[i].name << endl;
		for (int j = 0; j < courses[i].allowedDays.size(); ++j)
		{
			cout << courses[i].allowedDays[j] << endl;
		}
		for (int j = 0; j < courses[i].allowedHours.size(); ++j)
		{
			cout << courses[i].allowedHours[j] << endl;
		}
	}
}

bool hasDay(vector<int> allowedDays, int day)
{
	for (int i = 0; i < COURSE_DAYS; ++i)
	{
		if (allowedDays[i] == day)
		{
			return true;
		}
	}
	return false;
}

vector<int> findCoursesIndexes(vector<Course> courses, int classNum, int day, int hour)
{
	vector<int> coursesIndexes;
	for (int i = 0; i < courses.size(); ++i)
	{
		if (hasDay(courses[i].allowedDays, day) && courses[i].allowedHours[hour] && courses[i].assignedTeacher[classNum].notFound)
		{
			coursesIndexes.push_back(i);
		}
	}
	if (coursesIndexes.size() == 0)
	{
		return { NON_VALID_INDEX };
	}
	return coursesIndexes;
}

vector<int> haveThisCourse(Course course, vector<Teacher> teachers)
{
	vector<int> teachersIndexes;
	for (int i = 0; i < teachers.size(); ++i)
	{
		for (int j = 0; j < teachers[i].courses.size(); ++j)
		{
			if (teachers[i].courses[j] == course.name)
			{
				teachersIndexes.push_back(i);
				break;
			}
		}
	}
	if (teachersIndexes.size() == 0)
	{
		return { NON_VALID_INDEX };
	}
	return teachersIndexes;
}

vector<int> availableAtThisTime(vector<int> teachersIndexes, vector<Teacher> teachers,
	vector<int> allowedDays, int hour)
{
	if (teachersIndexes[0] == NON_VALID_INDEX && teachersIndexes.size() == 1)
	{
		return { NON_VALID_INDEX };
	}
	vector<int> newTeachersIndexes;
	for (int i = 0; i < teachersIndexes.size(); ++i)
	{
		vector<bool> available(COURSE_DAYS, false);
		for (int d = 0; d < COURSE_DAYS; ++d)
		{
			available[d] = teachers[teachersIndexes[i]].availablity[allowedDays[d]][hour];
		}
		if (all_of(available.begin(), available.end(), [](bool v) { return v; }))
		{
			newTeachersIndexes.push_back(teachersIndexes[i]);
		}
	}
	if (newTeachersIndexes.size() == 0)
	{
		return { NON_VALID_INDEX };
	}
	return newTeachersIndexes;
}

int theSmallestTeacher(vector<int> teachersIndexes, vector<Teacher> teachers)
{
	int theSmallestTeacherIndex = teachersIndexes[0];
	string theSmallestTeacherName = teachers[theSmallestTeacherIndex].name;
	for (int i = 0; i < teachersIndexes.size(); ++i)
	{
		if (theSmallestTeacherName > teachers[teachersIndexes[i]].name)
		{
			theSmallestTeacherIndex = teachersIndexes[i];
			theSmallestTeacherName = teachers[teachersIndexes[i]].name;
		}
	}
	return theSmallestTeacherIndex;
}

vector<int> findTheBestTeacheresIndexes(vector<int> coursesIndexes, vector<Course> courses,
	vector<Teacher> teachers, int hour)
{
	if (coursesIndexes[0] == NON_VALID_INDEX && coursesIndexes.size() == 1)
	{
		return { NON_VALID_INDEX };
	}
	vector<int> theBestTeachersIndexes;
	for (int i = 0; i < coursesIndexes.size(); ++i)
	{
		vector<int> teachersIndexes = availableAtThisTime(haveThisCourse(courses[coursesIndexes[i]], teachers),
			teachers, courses[coursesIndexes[i]].allowedDays, hour);
		if (teachersIndexes[0] == NON_VALID_INDEX && teachersIndexes.size() == 1)
		{
			theBestTeachersIndexes.push_back(NON_VALID_INDEX);
		}
		else
		{
			theBestTeachersIndexes.push_back(theSmallestTeacher(teachersIndexes, teachers));
		}
	}
	return theBestTeachersIndexes;
}

vector<int> theSmallestCourse(vector<int> coursesIndexes, vector<Course> courses,
	vector<int> theBestTeachersIndexes, vector<Teacher> teachers)
{
	if (coursesIndexes[0] == NON_VALID_INDEX && coursesIndexes.size() == 1)
	{
		return { NON_VALID_INDEX };
	}
	vector<int> theSmallestCourseIndex = { coursesIndexes[0], 0 };
	string theSmallestCourseName = courses[theSmallestCourseIndex[0]].name;
	for (int i = 0; i < coursesIndexes.size(); ++i)
	{
		if (theBestTeachersIndexes[i] != NON_VALID_INDEX)
		{
			if (theSmallestCourseName > courses[coursesIndexes[i]].name)
			{
				theSmallestCourseIndex[0] = coursesIndexes[i];
				theSmallestCourseIndex[1] = i;
				theSmallestCourseName = courses[coursesIndexes[i]].name;
			}
		}
	}
	return theSmallestCourseIndex;
}

bool isFreeHour(vector<Course> courses, int classNum, int day, int hour)
{
	for (int n = 0; n < courses.size(); n++)
	{
		if (courses[n].assignedTeacher[classNum].notFound == false &&
			courses[n].assignedTeacher[classNum].classHour == hour)
		{
			for (int d = 0; d < COURSE_DAYS; d++)
			{
				if (courses[n].allowedDays[d] == day)
				{
					return false;
				}
			}
		}
	}
	return true;
}

Course updateCourseInfo(Course course, Teacher teacher, int classNum, int hour)
{
	course.assignedTeacher[classNum].name = teacher.name;
	course.assignedTeacher[classNum].classHour = hour;
	course.assignedTeacher[classNum].notFound = false;
	return course;
}

Teacher setTeacherNotAvailable(Teacher teacher, vector<int> allowedDays, int hour)
{
	for (int i = 0; i < COURSE_DAYS; ++i)
	{
		teacher.availablity[allowedDays[i]][hour] = false;
	}
	return teacher;
}

vector<Course> setWeeklySchedule(vector<Course> courses, vector<Teacher> teachers)
{
	for (int classNum = 0; classNum < NUM_OF_CLASS; ++classNum)
	{
		for (int day = 0; day < WORK_DAYS; ++day)
		{
			for (int hour = 0; hour < CLASS_HOURS; ++hour)
			{
				vector<int> coursesIndexes = findCoursesIndexes(courses, classNum, day, hour);
				vector<int> theBestTeachersIndexes = findTheBestTeacheresIndexes(coursesIndexes, courses, teachers, hour);
				vector<int> theBestCourseIndex = theSmallestCourse(coursesIndexes, courses, theBestTeachersIndexes, teachers);
				if (theBestCourseIndex[0] != NON_VALID_INDEX)
				{
					int theBestTeacherIndex = theBestTeachersIndexes[theBestCourseIndex[1]];
					if (theBestTeacherIndex != NON_VALID_INDEX && isFreeHour(courses, classNum, day, hour))
					{
						courses[theBestCourseIndex[0]] = updateCourseInfo(courses[theBestCourseIndex[0]],
							teachers[theBestTeacherIndex], classNum, hour);
						teachers[theBestTeacherIndex] = setTeacherNotAvailable(teachers[theBestTeacherIndex],
							courses[theBestCourseIndex[0]].allowedDays, hour);
					}
				}
			}
		}
	}
	return courses;
}

bool compareByName(Course a, Course b) {
	return a.name < b.name;
}

vector<Course> sortByName(vector<Course> courses)
{
	sort(courses.begin(), courses.end(), compareByName);
	return courses;
}

string setTime(int hour)
{
	if (hour == 0)
		return "07:30 09:00";
	if (hour == 1)
		return "09:30 11:00";
	if (hour == 2)
		return "11:30 13:00";
	return "error in time format";
}

void printResult(vector<Course> courses)
{
	courses = sortByName(courses);
	for (int i = 0; i < courses.size(); ++i)
	{
		cout << courses[i].name << endl;
		for (int classNum = 0; classNum < NUM_OF_CLASS; ++classNum)
		{
			if (courses[i].assignedTeacher[classNum].notFound)
			{
				cout << "Not Found" << endl;
			}
			else
			{
				cout << courses[i].assignedTeacher[classNum].name << ": "
					<< setTime(courses[i].assignedTeacher[classNum].classHour) << endl;
			}
		}
	}
}

int main()
{
	int numOfTeachers;
	cin >> numOfTeachers;
	vector<Teacher> teachers = getTeachersInput(numOfTeachers);

	int numOfCourses;
	cin >> numOfCourses;
	vector<Course> courses = getCoursesInput(numOfCourses);

	//printTeachersForDebuging(teachers);
	//printCoursesForDebuging(courses);

	printResult(setWeeklySchedule(courses, teachers));

	return 0;
}
