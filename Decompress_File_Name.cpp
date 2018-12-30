#include <iostream>
#include <string>
#include <cstring>
using namespace std;


template<typename T>
struct Node
{
    T data;
    Node<T>* next;
    Node(const T& _data,Node<T>* _next=nullptr)
    {
        this->data = _data;
        this->next = _next;
    }
};

template<typename T>
class Stack
{
private:
    Node<T>* topElement;
    size_t size;
    void copy(const Stack<T>& other)
    {
        if(other.topElement == nullptr)
        {
            this->topElement = nullptr;
            this->size =0;
        }
        else
        {

            this->topElement = new Node<T>(other.topElement->data,other.topElement->next);
            Node<T>* temp1 = this->topElement;
            Node<T>* temp2 = other.topElement;
            while(temp2->next)
            {
                temp1->next = new Node<T>(temp2->next->data,temp2->next->next);
                temp2 = temp2->next;
                temp1 = temp1->next;
            }
            this->size = other.size;
        }
    }
    void erase()
    {
        if(!this->isEmpty())
        {
            this->pop();
        }
    }
public:
    Stack()
    {
        this->topElement = nullptr;
        this->size = 0;
    }
    Stack(const Stack& other)
    {
        this->copy(other);
    }
    Stack& operator=(const Stack& other)
    {
        if(this != &other)
        {
            this->erase();
            this->copy(other);
        }
        return *this;
    }
    ~Stack()
    {
        this->erase();
    }
    bool isEmpty()
    {
        return this->size == 0;
    }
    size_t getSize() const
    {
        return this->size;
    }
    void pop()
    {
        if(!this->isEmpty())
        {
            Node<T>* temp = this->topElement;
            this->topElement = this->topElement->next;
            delete temp;
            this->size--;
        }
        else throw "Empty stack";
    }
    void push(const T& element)
    {
        Node<T>* addElement = new Node<T>(element);
        if(this->isEmpty())
        {
            this->topElement = addElement;
        }
        else
        {
            addElement->next = this->topElement;
            this->topElement = addElement;
        }
        this->size++;
    }
    void print()
    {
        Node<T>* temp = this->topElement;
        while(temp)
        {
            cout<<temp->data;
            temp = temp->next;
        }
        //cout<<"Size : "<<this->getSize()<<endl;
    }
    const T& top() const
    {
        return this->topElement->data;
    }
};

string reverseString(string other)
{
    string temp;
    int n=other.length();
    for(int i=n-1; i>=-1; i--)
    {
        temp += other[i];
    }
    return temp;
}

bool containsDigit(string str)
{
    bool flag = false;
    for(size_t i=0; i<str.length(); i++)
    {
        if(isdigit(str[i]))
        {
            flag = true;
        }
    }
    return flag;
}

string normalize(string other)
{
    string normalized;
    for(size_t i=1; i<other.length()-1; i++)
    {
        if(isdigit(other[i]) && other[i+1] == '(')
        {
            int j = i+2;
            int n = other[i] - '0';
            string temp;
            while(other[j] != ')')
            {
                temp +=other[j];
                j++;
            }
            i = j;
            for(int k=0; k < n; k++)
            {
                normalized += temp;
            }

        }
        else if(other[i] != '\\')
        {
            normalized += other[i];
        }
    }
    return normalized;
}

void decompress(string str)
{
    Stack<int> counts;
    Stack<string> subStrs;
    Stack<string> normalized;
    string toReverse;
    for(size_t i=0; i<str.length(); i++)
    {
        if(isdigit(str[i]))
        {
            if(isdigit(str[i+1]))
            {
                counts.push((str[i] - '0') * 10 +(str[i+1] - '0'));
                i++;
            }
            else if(str[i+1] == '(')
            {
                counts.push((str[i] - '0'));
            }
        }
        else if(str[i] == '(')
        {
            string temp = "(";
            int j = i+1;
            int countOpen = 1, countClosed = 0;
            while(countOpen != countClosed)
            {
                if(str[j] == '(')
                {
                    countOpen++;
                    temp += str[j];
                    j++;
                }
                else if(str[j] == ')')
                {
                    countClosed++;
                    temp += str[j];
                    j++;
                }
                else
                {
                    temp += str[j];
                    j++;
                }
            }
            subStrs.push(temp);
            i = j-1;
        }

        else
        {
            cout<<str[i];
        }
    }

    while(subStrs.getSize() > 0)
    {
        for(int i=0; i<counts.top(); i++)
        {
            normalized.push(normalize(subStrs.top()));
        }
        subStrs.pop();
        counts.pop();
    }
    normalized.print();
}


int main()
{
    string str;
    cin>>str;
    decompress(str);
    return 0;
}
