#include <iostream>
#include <stack>
#include <vector>
#include <cctype>

using namespace std;

int p(char a)
{
    if (a == '+' || a == '-')
    {
        return 1;
    }

    if (a == '*' || a == '/')
    {
        return 2;
    }

    return 0;
}

bool op(char a)
{
    if (a == '+' || a == '-' ||
        a == '*' || a == '/')
    {
        return true;
    }

    return false;
}

bool match(char a, char b)
{
    if (a == '(' && b == ')')
    {
        return true;
    }

    if (a == '[' && b == ']')
    {
        return true;
    }

    if (a == '{' && b == '}')
    {
        return true;
    }

    return false;
}

bool found(string a[], int b, string c)
{
    for (int i = 0; i < b; i++)
    {
        if (a[i] == c)
        {
            return true;
        }
    }

    return false;
}

int value(string a[], int b[], int c, string d)
{
    for (int i = 0; i < c; i++)
    {
        if (a[i] == d)
        {
            return b[i];
        }
    }

    return 0;
}


vector<string> postfix(string a)
{
    vector<string> b;

    stack<char> c;

    int i = 0;

    while (i < a.length())
    {
        if (a[i] == ' ')
        {
            i++;
        }

        else if (isdigit(a[i]))
        {
            string d = "";

            while (i < a.length() &&
                   isdigit(a[i]))
            {
                d += a[i];
                i++;
            }

            b.push_back(d);
        }

        else if (isalpha(a[i]) ||
                 a[i] == '_')
        {
            string d = "";

            while (i < a.length() &&
                  (isalnum(a[i]) ||
                   a[i] == '_'))
            {
                d += a[i];
                i++;
            }

            b.push_back(d);
        }

        else if (a[i] == '(' ||
                 a[i] == '[' ||
                 a[i] == '{')
        {
            c.push(a[i]);
            i++;
        }

        else if (a[i] == ')' ||
                 a[i] == ']' ||
                 a[i] == '}')
        {
            while (!c.empty() &&
                   c.top() != '(' &&
                   c.top() != '[' &&
                   c.top() != '{')
            {
                string d = "";

                d += c.top();

                b.push_back(d);

                c.pop();
            }

            if (c.empty())
            {
                cerr << "Syntax Error";
                exit(1);
            }

            if (!match(c.top(), a[i]))
            {
                cerr << "Syntax Error";
                exit(1);
            }

            c.pop();
            i++;
        }

        else if (op(a[i]))
        {
            while (!c.empty() &&
                   p(c.top()) >= p(a[i]))
            {
                if (c.top() == '(' ||
                    c.top() == '[' ||
                    c.top() == '{')
                {
                    break;
                }

                string d = "";

                d += c.top();

                b.push_back(d);

                c.pop();
            }

            c.push(a[i]);
            i++;
        }

        else
        {
            cerr << "Syntax Error";
            exit(1);
        }
    }

    while (!c.empty())
    {
        if (c.top() == '(' ||
            c.top() == '[' ||
            c.top() == '{')
        {
            cerr << "Syntax Error";
            exit(1);
        }

        string d = "";

        d += c.top();

        b.push_back(d);

        c.pop();
    }

    return b;
}

int solve(vector<string> a)
{
    stack<int> b;

    string c[100];

    int d[100];

    int e = 0;

    for (int i = 0; i < a.size(); i++)
    {
        string f = a[i];

        if (f == "+" ||
            f == "-" ||
            f == "*" ||
            f == "/")
        {
            if (b.size() < 2)
            {
                cerr << "Logical Error";
                exit(3);
            }

            int g = b.top();
            b.pop();

            int h = b.top();
            b.pop();

            int j = 0;

            if (f == "+")
            {
                j = h + g;
            }

            else if (f == "-")
            {
                j = h - g;
            }

            else if (f == "*")
            {
                j = h * g;
            }

            else if (f == "/")
            {
                if (g == 0)
                {
                    cerr << "Runtime Error that not possible";
                    exit(2);
                }

                j = h / g;
            }

            b.push(j);
        }

        else if (isdigit(f[0]))
        {
            int g = 0;

            for (int i = 0; i < f.length(); i++)
            {
                g = g * 10 + (f[i] - '0');
            }

            b.push(g);
        }

        else
        {
            if (!found(c, e, f))
            {
                int g;

                cerr << "Enter value for "
                     << f << ": ";

                cin >> g;

                c[e] = f;

                d[e] = g;

                e++;
            }

            int g = value(c, d, e, f);

            b.push(g);
        }
    }

    if (b.size() != 1)
    {
        cerr << "Logical Error";
        exit(3);
    }

    return b.top();
}


int main()
{
    string a;

    getline(cin, a);

    vector<string> b;

    b = postfix(a);

    cerr << "Postfix Expression: ";

    for (int i = 0; i < b.size(); i++)
    {
        cerr << b[i] << " ";
    }

    cerr << endl;

    int c;

    c = solve(b);
    cout<<c<<endl;
    return 0;
}   