#include <iostream>
using namespace std;

void strcpy1(char* dest, const char* source)
{
	int i = 0;
	for (i = 0; source[i] != 0; i++)
		dest[i] = source[i];
	dest[i] = 0;
}
class Person
{
public:
	Person();
	Person(const char* fname, const char* lname, int a);
	char* get_first_name()
	{
		return first_name;
	}
	char* get_last_name()
	{
		return last_name;
	}
	int get_age()
	{
		return age;
	}
	void set_first_name(const char* fname)
	{
		first_name = new char[strlen(fname) + 1];
		strcpy1(first_name, fname);
	}
	void set_last_name(const char* lname)
	{
		last_name = new char[strlen(lname) + 1];
		strcpy1(last_name, lname);
	}
	void set_age(int a)
	{
		age = a;;
	}
	void printinformation()
	{
		cout << first_name << " " << last_name << " is " << age << " Years Old ";
	}
	~Person();

private:
	char* first_name;
	char* last_name;
protected:
	int age;
};

Person::Person()
{
	first_name = nullptr;
	last_name = nullptr;
	age = 0;
}
Person::Person(const char* fname, const char* lname, int a)
{
	cout << "Person() Called" << endl;
	first_name = new char[strlen(fname) + 1];
	strcpy1(first_name, fname);
	last_name = new char[strlen(lname) + 1];
	strcpy1(last_name, lname);
	age = a;
}
Person::~Person()
{
	cout << "~Person() Called" << endl;
	delete[] last_name;
	delete[] first_name;
	age = 0;
}
class Student :public Person
{
public:
	Student();
	Student(const char* fname, const char* lname, int a, float c);
	void set_cgpa(float c)
	{
		cgpa = c;
	}
	~Student();
	float get_cgpa()
	{
		return cgpa;
	}
	void printstudent()
	{
		Person::printinformation();
		cout << ",his cgpa is " << cgpa << endl;
	}

protected:
	float cgpa;
};

Student::Student() :Person()
{
	cgpa = 0;
}
Student::Student(const char* fname, const char* lname, int a, float c) : Person(fname, lname, a)
{
	cout << "Student() Called" << endl;
	cgpa = c;
}
Student::~Student()
{
	cout << "~Student() Called" << endl;
	cgpa = 0;
}

class Faculty :public Person
{
public:
	Faculty();
	Faculty(const char* fname, const char* lname, int a, int count, int ext) :Person(fname, lname, a)
	{
		cout << "Faculty() Called" << endl;
		course_count = count;
		txt_ext = ext;

	}
	int get_course_count()
	{
		return course_count;
	}
	int get_txt_ext()
	{
		return txt_ext;
	}
	void set_txt_ext(int ext)
	{
		txt_ext = ext;;
	}
	void set_course_count(int count)
	{
		course_count = count;
	}
	void printfaculty()
	{
		Person::printinformation();
		cout << ",Number of Courses: " << course_count << ",Ext: " << txt_ext << endl;
	}
	~Faculty();

private:
	int course_count;
	int txt_ext;
};

Faculty::Faculty() :Person()
{
	cout << "Faculty() Called" << endl;
	course_count = 0;
	txt_ext = 0;
}

Faculty::~Faculty()
{
	cout << "~Faculty() Called" << endl;
	course_count = 0;
	txt_ext = 0;
}
class Graduate :public Student
{
public:
	Graduate();
	Graduate(const char* fname, const char* lname, int a, float c, const char* fyp);
	void set_thesis_topic(const char* name)
	{
		thesis_topic = new char[strlen(name) + 1];
		strcpy1(thesis_topic, name);
	}
	char* get_thesis_topic()
	{
		return thesis_topic;
	}
	void printgraduate()
	{
		Student::printstudent();
		cout << "his thesis topic is " << thesis_topic << endl;
	}
	~Graduate();

private:
	char* thesis_topic;
};

Graduate::Graduate()
{
	thesis_topic = nullptr;
}
Graduate::Graduate(const char* fname, const char* lname, int a, float c, const char* topic) :Student(fname, lname, a, c)
{
	cout << "Graduate() Called" << endl;
	thesis_topic = new char[strlen(topic) + 1];
	strcpy1(thesis_topic, topic);
}
Graduate::~Graduate()
{

	cout << "~Graduate() Called" << endl;
	delete[]thesis_topic;
}

class UnderGraduate : private Student
{
public:
	UnderGraduate();
	UnderGraduate(const char* fname, const char* lname, int a, float c, const char* fyp);
	void set_fyp_name(const char* name)
	{
		fyp_name = new char[strlen(name) + 1];
		strcpy1(fyp_name, name);
	}
	char* get_fyp_name()
	{
		return fyp_name;
	}
	void printundergraduate()
	{
		Student::printstudent();
		cout << "his Final Year Project title is " << fyp_name << endl;
	}
	~UnderGraduate();

private:
	char* fyp_name;
};

UnderGraduate::UnderGraduate()
{
	fyp_name = nullptr;
}
UnderGraduate::UnderGraduate(const char* fname, const char* lname, int a, float c, const char* fyp) : Student(fname, lname, a, c)
{
	cout << "UnderGraduate() Called" << endl;
	fyp_name = new char[strlen(fyp) + 1];
	strcpy1(fyp_name, fyp);
}
UnderGraduate::~UnderGraduate()
{
	cout << "~UnderGraduate() Called" << endl;
	delete[]fyp_name;
}

int main()
{
	UnderGraduate u("John", "Cena", 25, 3.01f, " The Even Locator");

	Graduate g("Ali", "Hassan", 22, 3.51f, "Distributed Algorithms");


	u.printundergraduate();
	g.printgraduate();
	UnderGraduate l("Muhammad", "", 22, 3.91f, "");

	Faculty m("Ali", "", 45, 2, 420);

	l.printundergraduate();
	m.printfaculty();


}