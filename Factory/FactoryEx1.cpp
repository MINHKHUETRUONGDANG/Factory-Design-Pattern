#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

constexpr int MAX = 3;

class Person{
    private:
        string name;
        string lastname;
        char middleInitial = '\0';
        string title;
    protected:
        void modifyTitle(const string &);
    public: 
        Person() = default;
        Person(const string &, const string &, char, const string &);
        virtual ~Person() = default;
        
    
        const string &getName() const { return name; };
        const string &getLastName() const { return lastname; };
        const string &getTitle() const { return title; };
        char getMiddle() const { return middleInitial; }
        
        virtual void print() const {
            cout << title << " " << name << " ";
            cout << middleInitial << ". " << lastname << endl;
        };
        virtual string isA() const { return "Person"; };
        virtual void greeting(const string &msg) const { cout << msg << endl; };
};
Person::Person(const string &fn, const string &ln, char mi, const string &t)
            : name(fn), lastname(ln), middleInitial(mi), title(t){};
void Person::modifyTitle(const string &t){ title = t; }


class Student : public Person{
    private:
        float gpa = 0.0;
        string currentCourse;
        const string id;
        static int numStudents;
    public:
        Student();
        Student(const string &fn, const string &ln, char mi, const string &t, 
            float agpa, const string &course, const string &ID) :
                Person(fn, ln, mi, t), gpa(agpa), currentCourse(course), id(ID){
                    numStudents++;
                };
        Student(const Student &);
        ~Student();
        
        float getGPA(){ return gpa; }
        const string &getCurrentCourse(){ return currentCourse; }
        const string &getId(){ return id; }
        void setCurrentCourse(const string &course){ currentCourse = course; }
        
        virtual void print() const override;
        virtual string isA() const override{ return "Student"; }
        
        virtual void Graduate() = 0;
        
        static Student *MatriculateStudent(const string &, const string &, const string &, char, 
                                       const string &, float, const string &, const string &);
                                       
        static int getNumStudents() { return numStudents; }                        
};

int Student::numStudents = 0;

Student::Student() : id(to_string(numStudents + 100) + "id") { numStudents++; }
Student::Student(const Student &s) : Person(s), gpa(s.gpa), currentCourse(s.currentCourse), id(s.id){
    numStudents++;
}
Student::~Student(){
    numStudents--;  
}

void Student::print() const{
    cout << "  " << getTitle() << " " << getName() << " ";
    cout << getMiddle() << ". " << getLastName();
    cout << " with id: " << id << " GPA: ";
    cout << setprecision(3) <<  " " << gpa;
    cout << " Course: " << currentCourse << endl;
}


class GradStudent : public Student{
    private:
        string degree;
    public:
        GradStudent() = default;
        GradStudent(const string &deg, const string &fn, const string &ln, char mi, 
                const string &t, float agpa, const string &course, const string &ID)
            : Student(fn, ln, mi, t, agpa, course, ID), degree(deg){};
            
        void earnPhD(){ if(!degree.compare("PhD")) { modifyTitle("Dr"); }}
        
        virtual string isA() const override { return "GradStudent"; }
        
        virtual void Graduate() override { earnPhD(); cout << "GradStudent::Graduate()" << endl; }
};


class UngradStudent : public Student{
    private:
        string degree;
    public:
        UngradStudent() = default;
        UngradStudent(const string &deg, const string &fn, const string &ln, char mi, 
                const string &t, float agpa, const string &course, const string &ID)
            : Student(fn, ln, mi, t, agpa, course, ID), degree(deg){};
        
        virtual string isA() const override { return "UngradStudent"; }
        
        virtual void Graduate() override { cout << "UngradStudent::Graduate()" << endl; }
};


class NonDegreeStudent : public Student{
    private:
    public:
        NonDegreeStudent() = default;
        NonDegreeStudent(const string &fn, const string &ln, char mi, 
                const string &t, float agpa, const string &course, const string &ID)
            : Student(fn, ln, mi, t, agpa, course, ID){};
            
        virtual string isA() const override { return "NonDegreeStudent"; }
        
        virtual void Graduate() override { cout << "NonDegreeStudent::Graduate()" << endl; }
};

Student *Student::MatriculateStudent(const string &deg, const string &fn, const string &ln, char mi, 
                const string &t, float agpa, const string &course, const string &ID){
    
    if(!deg.compare("PhD") || !deg.compare("MA") || !deg.compare("MS")){
        return new GradStudent(deg, fn, ln, mi, t, agpa, course, ID);
    } else if(!deg.compare("BS") || !deg.compare("BA")){
        return new UngradStudent(deg, fn, ln, mi, t, agpa, course, ID);
    } else if(!deg.compare("none")){
        return new NonDegreeStudent(fn, ln, mi, t, agpa, course, ID);
    }
    
    return nullptr;                    
}

int main()
{
    Student *scholars[MAX] = {};
    
    scholars[0] = Student::MatriculateStudent("PhD", "Sara", "Kato", 'B', "Ms.", 3.9, "C++", "272PSU");
    scholars[1] = Student::MatriculateStudent("BS", "Ana", "Sato", 'U', "Ms.", 3.8, "C++", "178PSU");
    scholars[2] = Student::MatriculateStudent("none", "Elle", "LeBrun", 'R', "Miss", 3.5, "C++", "111BU");
    
    for(auto *scholar : scholars){
        scholar->Graduate();
        scholar->print();
    }
    
    for(auto *scholar: scholars){
        delete scholar;
    }
        
    return 0;
}
