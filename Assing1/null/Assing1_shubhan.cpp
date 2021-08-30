#include <iostream>
using namespace std;
class node
{
public:
    long long int coeff;
    long long int pow;
    node *next;
    node *prev;
};
node *create(long long int cf, long long int pw)
{
    node *a = (node *)malloc(sizeof(node));
    a->next = a;
    a->prev = a;
    a->coeff = cf;
    a->pow = pw;
    return a;
}
void append(node *s, node *a)
{
    s->prev->next = a;
    a->prev = s->prev;
    a->next = s;
    s->prev = a;
}
void printpoly(node *a)
{
    int ctr = 0;
    node *ptr = a;
    while (ptr->pow != -1)
    {
        if (ptr->coeff == 0)
        {
            ptr = ptr->next;
            continue;
        }
        cout << ptr->coeff << ' ' << ptr->pow << ' ';
        ptr = ptr->next;
        ctr++;
    }
    if (ctr == 0)
    {
        cout << 0;
    }
}
void printrand(node *a)
{
    node *ptr = a;
    int i = 0;
    while (i < 15)
    {
        cout << ptr->coeff << ' ' << ptr->pow << ' ';
        ptr = ptr->next;
        i++;
    }
}
int main()
{
    node *a, *b, *s;
    a = create(0, -1);
    b = create(0, -1);
    s = create(0, -1);
    int n, m;
    cin >> n >> m;
    int cf, pw;
    node *nd;
    for (int i = 0; i < n; i++)
    {
        cin >> cf >> pw;
        nd = create(cf, pw);
        append(a, nd);
    }
    for (int i = 0; i < m; i++)
    {
        cin >> cf >> pw;
        nd = create(cf, pw);
        append(b, nd);
    }
    a = a->next;
    b = b->next;
    node *temp;
    while ((a->pow != -1) || (b->pow != -1))
    {
        if (a->pow > b->pow)
        {
            if (b->pow != -1)
            {
                temp = create(b->coeff, b->pow);
                append(s, temp);
                b = b->next;
            }
            else if (a->pow != -1)
            {
                temp = create(a->coeff, a->pow);
                append(s, temp);
                a = a->next;
            }
        }
        else if (a->pow < b->pow)
        {
            if (a->pow != -1)
            {
                temp = create(a->coeff, a->pow);
                append(s, temp);
                a = a->next;
            }
            else if (b->pow != -1)
            {
                temp = create(b->coeff, b->pow);
                append(s, temp);
                b = b->next;
            }
        }
        else if (a->pow == b->pow)
        {
            if (a->coeff + b->coeff != 0)
            {
                temp = create(a->coeff + b->coeff, b->pow);
                append(s, temp);
            }
            a = a->next;
            b = b->next;
        }
    }
    s = s->next;
    printpoly(s);
}