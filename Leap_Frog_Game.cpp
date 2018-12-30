#include <iostream>

using namespace std;
template<typename T>
struct DLList_Node
{
    T data;
    DLList_Node<T>* previous;
    DLList_Node<T>* next;
    DLList_Node(const T& _data, DLList_Node<T>* _previous = nullptr, DLList_Node<T>* _next = nullptr)
    {
        data = _data;
        previous = _previous;
        next = _next;
    }
};

template<typename T>
class DLList
{
public:
    DLList()
    {
        this->first = nullptr;
        this->last = nullptr;
        this->size = 0;
    }
    DLList(const DLList& other)
    {
        this->copy(other);
    }
    DLList& operator=(const DLList& other)
    {
        if(this != &other)
        {
            this->erase();
            this->copy(other);
        }
        return *this;
    }
    DLList_Node<T>* getLast() const
    {
        return this->last;
    }
    DLList_Node<T>* getFirst() const
    {
        return this->first;
    }
    size_t getSize() const
    {
        return this->size;
    }
    bool isEmpty() const
    {
        return this->first == nullptr && this->last == nullptr;
    }
    void push(const T& _data)
    {
        DLList_Node<T>* toAdd = new DLList_Node<T>(_data);
        if(isEmpty())
        {
            this->first = toAdd;
            this->last = toAdd;
            this->size++;
        }
        else
        {
            this->last->next = toAdd;
            toAdd->previous = this->last;
            this->last = this->last->next;
            this->size++;
        }
    }
    void pop()
    {
        DLList_Node<T>* toDel = this->last;
        this->last = this->last->previous;
        delete toDel;
        this->size--;
    }
    void print() const
    {
        DLList_Node<T>* temp = this->first;
        for(size_t i=0; i<this->size; i++)
        {
            cout<<temp->data;
            temp=temp->next;
        }
        //cout<<"Size: "<<this->size<<endl;
    }
    ~DLList()
    {
        this->erase();
    }
private:
    DLList_Node<T>* first;
    DLList_Node<T>* last;
    size_t size;
    void copy(const DLList& other)
    {
        if(other.isEmpty())
        {
            this->first = nullptr;
            this->last = nullptr;
            this->size = 0;
        }
        else
        {
            DLList_Node<T>* temp = other.getFirst();
            this->push(temp->data);
            while(temp->next)
            {
                temp = temp->next;
                this->push(temp->data);
            }
            this->size = other.getSize();
        }
    }
    void erase()
    {
        while(this->size > 0)
        {
            this->pop();
        }
    }
};

void  fillUp(DLList<char>& field,int n)
{
    for(int i=0; i<(n*2+1); i++)
    {
        if(i == n)
        {
            field.push('_');
        }
        else if(i < n)
        {
            field.push('>');
        }
        else
        {
            field.push('<');
        }
    }

}
void swapElementsData(DLList_Node<char>*& firstElement,DLList_Node<char>*& secondElement)
{
    char temp = firstElement->data;
    firstElement->data = secondElement->data;
    secondElement->data = temp;
}
bool isNearEnd(DLList_Node<char>* node, char _data)
{
    bool flag = true;
    while(node)
    {
        if(node->data == _data || node->data == '_')
        {
            node = node->next;
        }
        else
        {
            flag = false;
            break;
        }
    }
    return flag;
}
void playGame(DLList<char>& field, int n)
{
    int movesNeeded = ((n+1)*(n+1))-1;
    field.print();
    cout<<endl;
    for(int i=0; i<movesNeeded; i++)
    {
        DLList_Node<char>* temp = field.getFirst();
        while(temp)
        {
            if(temp->data == '>')
            {
                if(temp->next && temp->next->data == '_')
                {
                    if(temp->next->next && temp->next->next->data == '<')
                    {
                        if(temp->previous && temp->previous->data == '>')
                        {
                            swapElementsData(temp,temp->next);
                            field.print();
                            cout<<" I: "<<i<<endl;
                            temp = field.getLast()->next;
                        }
                        else if(temp == field.getFirst())
                        {
                            swapElementsData(temp,temp->next);
                            field.print();
                            cout<<" I: "<<i<<endl;
                            temp = field.getLast()->next;
                        }
                        else temp = temp->next;
                    }
                    else if(isNearEnd(temp,temp->data))
                    {
                        swapElementsData(temp,temp->next);
                        field.print();
                        cout<<" I: "<<i<<endl;
                        temp = field.getLast()->next;
                    }
                    else if(i == movesNeeded-1)
                    {
                        swapElementsData(temp,temp->next);
                        field.print();
                        cout<<" I: "<<i<<endl;
                        temp = field.getLast()->next;
                    }
                    else if(temp->next == field.getLast())
                    {
                        swapElementsData(temp,temp->next);
                        field.print();
                        cout<<" I: "<<i<<endl;
                        temp = field.getLast()->next;
                    }
                    else if(temp->next->next && temp->next->next == field.getLast())
                    {
                        swapElementsData(temp,temp->next);
                        field.print();
                        cout<<" I: "<<i<<endl;
                        temp = field.getLast()->next;
                    }
                    else temp = temp->next;
                }
                else if(temp->next && temp->next->data == '<')
                {
                    if(temp->next->next && temp->next->next->data == '_')
                    {
                        swapElementsData(temp,temp->next->next);
                        field.print();
                        cout<<" I: "<<i<<endl;
                        temp = field.getLast()->next;
                    }
                    else temp = temp->next;
                }
                else temp = temp->next;
            }
            else if(temp->data == '<')
            {
                if(temp->previous && temp->previous->data == '_')
                {
                    if(temp->previous->previous && temp->previous->previous->data == '>')
                    {
                        swapElementsData(temp,temp->previous);
                        field.print();
                        cout<<" I: "<<i<<endl;
                        temp = field.getLast()->next;
                    }
                    else if(temp->previous->previous && temp->previous->previous->data == '<')
                    {
                        swapElementsData(temp,temp->previous);
                        field.print();
                        cout<<" I: "<<i<<endl;
                        temp = field.getLast()->next;
                    }
                    else if(temp->previous == field.getFirst())
                    {
                        swapElementsData(temp,temp->previous);
                        field.print();
                        cout<<" I: "<<i<<endl;
                        temp = field.getLast()->next;
                    }
                    else temp = temp->next;
                }
                else if(temp->previous && temp->previous->data == '>')
                {
                    if(temp->previous->previous && temp->previous->previous->data == '_')
                    {
                        swapElementsData(temp,temp->previous->previous);
                        field.print();
                        cout<<" I: "<<i<<endl;
                        temp = field.getLast()->next;
                    }
                    else temp = temp->next;
                }
                else temp = temp->next;
            }
            else temp = temp->next;
        }
    }
}


int main()
{
    DLList<char> playField;
    int numberOfFrogs;
    cin>>numberOfFrogs;
    fillUp(playField,numberOfFrogs);
    playGame(playField,numberOfFrogs);
    cout<<endl;
    return 0;
}
