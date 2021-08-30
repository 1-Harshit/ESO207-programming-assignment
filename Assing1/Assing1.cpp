#include <iostream>
using namespace std;

// The polynomial which has everything class
class Polynomial
{
private:
    // Size of the Linked List
    long long int size;

    // Structure of each node
    typedef struct Node
    {
        long long int coeff;
        long long int exp;
        struct Node *next;
        struct Node *prev;
    } node;

    // Creading a node and returning it
    node *createNode(long long int coeff, long long int exp)
    {
        node *newNode = new node;
        newNode->coeff = coeff;
        newNode->exp = exp;
        newNode->next = NULL;
        newNode->prev = NULL;
        return newNode;
    }

    // Update the coefficient of the node with the given exponent or create a new node if not found
    node *updateNode(long long int coeff, long long int exp, node *curr)
    {
        // loop thru the list to find appropriate place for the given exponent
        while (true)
        {
            // if the exponent is greater than the max exponent of the list then append the node
            if (curr == head)
            {
                appendNode(coeff, exp);
                return head;
            }
            else
            {
                // if the exponent is equal to the current node's exponent then update the coefficient
                if (curr->exp == exp)
                {
                    curr->coeff += coeff;

                    node *next = curr->next;

                    // if the coefficient is 0 then remove the node
                    if (curr->coeff == 0)
                        deleteNode(curr);

                    return next;
                }
                // if the exponent is greater than the current node's exponent then move to the next node
                else if (curr->exp < exp)
                {
                    curr = curr->next;
                }
                else
                {
                    // if the exponent is less than the current node's exponent then insert the node in between
                    node *newNode = createNode(coeff, exp);
                    size++;

                    newNode->next = curr;
                    newNode->prev = curr->prev;
                    curr->prev->next = newNode;
                    curr->prev = newNode;

                    return curr;
                }
            }
        }
    }

    // Append a node in the end of the list
    void appendNode(long long int coeff, long long int exp)
    {
        // if coeff is 0 then do not append
        if (coeff == 0)
            return;
        // creating and appending the node
        node *newNode = createNode(coeff, exp);
        node *last = head->prev;

        last->next = newNode;
        newNode->prev = last;
        newNode->next = head;
        head->prev = newNode;

        size++;
    }

    // Delete the node
    void deleteNode(node *curr)
    {
        node *prev = curr->prev;
        node *next = curr->next;
        prev->next = next;
        next->prev = prev;

        // free the memory
        delete curr;

        size--;
    }

public:
    node *head; // Sentinal node

    // Constructor intializing the sentinal node
    Polynomial()
    {
        head = new node;
        head->next = head;
        head->prev = head;
        head->coeff = 0;
        head->exp = -1;
    }

    // input values to the list from standard input
    void input(long long int n)
    {
        size = n;
        for (long long int i = 0; i < n; i++)
        {
            long long int coeff, exp;
            cin >> coeff >> exp;
            appendNode(coeff, exp);
        }
    }

    // print the list
    void print()
    {
        node *temp = head->next;

        // loop thru the list and print the values
        while (temp != head)
        {
            cout << temp->coeff << " " << temp->exp << " ";
            temp = temp->next;
        }
    }

    // add two polynomials
    void add(Polynomial p1, Polynomial p2)
    {
        // loop thru the list of p1 and add the values to the list of p2
        node *temp1 = p1.head->next;
        node *temp2 = p2.head->next;

        while (temp1 != p1.head && temp2 != p2.head)
        {
            // If exponent is same then add the coefficients
            if (temp1->exp == temp2->exp)
            {
                appendNode(temp1->coeff + temp2->coeff, temp1->exp);
                temp1 = temp1->next;
                temp2 = temp2->next;
            }
            // If exponent of p2 is greater than p1 then add the node of p1
            else if (temp1->exp < temp2->exp)
            {
                appendNode(temp1->coeff, temp1->exp);
                temp1 = temp1->next;
            }
            // If exponent of p1 is greater than p2 then add the node of p2
            else
            {
                appendNode(temp2->coeff, temp2->exp);
                temp2 = temp2->next;
            }
        }
        // when only p1 is left keep adding p1
        while (temp1 != p1.head)
        {
            appendNode(temp1->coeff, temp1->exp);
            temp1 = temp1->next;
        }
        // when only p2 is left keep adding p2
        while (temp2 != p2.head)
        {
            appendNode(temp2->coeff, temp2->exp);
            temp2 = temp2->next;
        }
    }

    // multiply two polynomials
    void multiply(Polynomial p1, Polynomial p2)
    {
        // loop thru the list of p1 and multiply the values to the list of p2
        node *temp1 = p1.head->next;
        node *temp2 = p2.head->next;
        while (temp1 != p1.head)
        {
            node *temp = head->next;
            while (temp2 != p2.head)
            {
                // temp to keep pointer in this->list
                // keep updating nodes as required
                temp = updateNode(temp1->coeff * temp2->coeff, temp1->exp + temp2->exp, temp);
                temp2 = temp2->next;
            }
            // start p2 from the beginning
            temp2 = p2.head->next;
            temp1 = temp1->next;
        }
    }

    // delete the list
    void deleteList()
    {
        node *temp = head->next;
        while (temp != head)
        {
            node *next = temp->next;
            delete temp;
            temp = next;
        }
        head->next = head->prev = head;
    }
};

// Driver Code
int main()
{
    // Input polynomials
    Polynomial p, q;

    // size of the polynomials
    long long int n, m;
    cin >> n >> m;

    // input
    p.input(n);
    q.input(m);

    // resultant polynomial
    Polynomial result;

    // Toggle Additon and Multiplication per test case
    /* result.add(p, q); */
    result.multiply(p, q);

    // print the resultant polynomial
    result.print();

    // delete the polynomials
    p.deleteList();
    q.deleteList();
    result.deleteList();

    return 0;
}