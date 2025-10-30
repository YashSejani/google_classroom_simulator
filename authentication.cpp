#include "classes.h"
#include <exception>

bool userexists(string name, string email, string pass, string role)
{
    // Check if user already exists during signup
    string filename;
    if (role == "Student")
        filename = "student_data.txt";
    else if (role == "Teacher")
        filename = "teacher_data.txt";
    else
        return false;

    try {
        ifstream file(filename);
        if (!file.is_open())
            return false;

        string line;
        while (getline(file, line))
    {
        stringstream ss(line);
        string u, e, p, r; // username, email, password, role

        getline(ss, u, '|');
        getline(ss, e, '|');
        getline(ss, p, '|');
        getline(ss, r, '|');

        if (role == "Student") {
            student s1(name, email, pass);
            student s2(u, e, p);
            if (s1 == s2 && r == role)
            {
                file.close();
                return true;
            }
        } else if (role == "Teacher") {
            teacher t1(name, email, pass);
            teacher t2(u, e, p);
            if (t1 == t2 && r == role)
            {
                file.close();
                return true;
            }
        }
    }

        file.close();
        return false;
    }
    catch (const exception &e) {
        cerr << "Error checking user existence: " << e.what() << "\n";
        return false;
    }
}

bool check_email(string email)
{
    // Email validation function
    if (email.size() >= 10 && email.substr(email.size() - 10) == "@gmail.com")
        return true;
    else
        return false;
}

void signup(string role)
{
    // Create new account
    string user, email, pass;

    cout << "Enter Name: ";
    getline(cin, user);
    
    do
    {
        cout << "Enter Email: ";
        getline(cin, email);
        if (!check_email(email))
            cout << "Invalid Email! Try again.\n";
    } while (!check_email(email));
    
    cout << "Enter Pass: ";
    getline(cin, pass);

    try {
        if (role == "Student" && !userexists(user, email, pass, role))
        {
            student s(user, email, pass);
            s.save();
            show_student(s);
            cout << "Student Registration Done!\n";
        }
        else if (role == "Teacher" && !userexists(user, email, pass, role))
        {
            teacher t(user, email, pass);
            t.save();
            show_teacher(t);
            cout << "Teacher Registration Done!\n";
        }
        else
        {
            cout << "User already exists!\n";
        }
    }
    catch (const exception &e) {
        cerr << "Error during signup: " << e.what() << "\n";
    }
}

bool login(string role)
{
    string user, email, pass;
    bool ok = false;

    cout << "Enter Name: ";
    getline(cin, user);

    cout << "Enter Email: ";
    getline(cin, email);
    if (!check_email(email))
    {
        cout << "Invalid Email! Returning to auth menu.\n";
        return false;
    }

    cout << "Enter Pass: ";
    getline(cin, pass);

    string filename;
    if (role == "Student")
        filename = "student_data.txt";
    else
        filename = "teacher_data.txt";

    try {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "No User Found!\n";
            return false;
        }

        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string u, e, p, r; // username, email, password, role

            getline(ss, u, '|');
            getline(ss, e, '|');
            getline(ss, p, '|');
            getline(ss, r, '|');

            if (u == user && e == email && p == pass && r == "Student")
            {
                ok = true;
                student s(u, e, p);
                cout << "Login OK!\n";
                show_student(s);
                s.display();
                student_menu(s);
            }
            else if (u == user && e == email && p == pass && r == "Teacher")
            {
                ok = true;
                teacher t(u, e, p);
                cout << "Login OK!\n";
                show_teacher(t);
                t.display();
                teacher_menu(t);
            }
        }
        file.close();

        if (!ok)
        {
            cout << "No User Found!\n";
            return false;
        }

        return true;
    }
    catch (const exception &e) {
        cerr << "Error during login: " << e.what() << "\n";
        return false;
    }
}