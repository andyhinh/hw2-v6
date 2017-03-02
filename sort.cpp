#include <cmath>
#include <cstdio>
#include <iostream>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <ostream>
#include <map>

using namespace std;

#include "ArgumentManager.h"

struct Node
{
    long long num = 0;
    string str;
    Node* prev = 0;
    Node* next = 0;
};

class DoubleLinkedList
{
public:
    DoubleLinkedList() {}
    // Destructor
    ~DoubleLinkedList()
    {
        while (head != nullptr)
        {
            Node* deleteme = head;
            head = head->next;
            delete deleteme;
        }
    }
    // Copy constructor
    DoubleLinkedList(DoubleLinkedList const & list)
    {
        // cout << "copy" << endl;
    }
    // Build a Double Linked List
    DoubleLinkedList(const std::string& num, int digitsPerNode);

    void operator=(DoubleLinkedList & other)
    {
        // cout << "equal" << endl;
        head = other.head;
        other.head = nullptr;
    }

    void push_front(string parted)
    {
        Node*temp = new Node();
        temp->str = parted;
        stringstream ss(parted);
        ss >> temp->num;
        if (head == 0)
        {
            head = temp;
            tail = temp;
        }
        else
        {
            head->prev = temp;
            temp->next = head;
            head = temp;
        }
    }

    void push_back(string parted)
    {
        Node* temp = new Node();
        temp->str = parted;
        stringstream ss(parted);
        ss >> temp->num;
        if (head == 0)
        {
            head = temp;
            tail = temp;
        }
        else
        {
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
    }

    void print() const
    {
        Node* temp = head;
        while (temp != nullptr)
        {
            cout << temp->str;
            temp = temp->next;
        }
        cout << endl;
    }

    Node at(int index) const
    {
        int i = 0;
        Node* temp = head;
        while (i != index)
        {
            temp = temp->next;
            i++;
        }
        return *temp;
    }

    int size() const
    {
        int count = 0;
        Node* temp = head;
        while (temp != 0)
        {
            temp = temp->next;
            count++;
        }
        return count;
    }

    void swap(DoubleLinkedList & other)
    {
        Node* temp = head;
        head = other.head;
        other.head = temp;
    }

private:
    Node* head = 0;
    Node* tail = 0;
};

class BigNumber
{
public:
    BigNumber() {}
    BigNumber(string num, int digitsPerNode)
    {
        // cout << num << endl;
        if (num[0] == '-')
        {
            isNegative = true;
            num.erase(num.begin());
        }
        int startIndex = num.length() - digitsPerNode;
        while (startIndex >= 0)
        {
            data.push_front(num.substr(startIndex, digitsPerNode));
            startIndex -= digitsPerNode;
        }
        if (startIndex < 0)
        {
            data.push_front(num.substr(0, startIndex + digitsPerNode));
        }
    }
    BigNumber(BigNumber const & other)
    {
        // cout << "big copy" << endl;
    }
    BigNumber & operator= (BigNumber other)
    {
        // cout << "operator=" << endl;
        isNegative = other.isNegative;
        data = other.data;
        return *this;
    }
    bool operator< (BigNumber const & other) const
    {
        BigNumber const & a = *this;
        BigNumber const & b = other;

        if (a.isNegative && !b.isNegative)
        {
            return true;
        }
        if (!a.isNegative && b.isNegative)
        {
            return false;
        }

        bool result = false;
        if (a.data.size() < b.data.size())
        {
            //return true;
            result = true;
        }
        else
            if (a.data.size() > b.data.size())
            {
                //return false;
                result = false;
            }
            else
                if (a.data.size() == b.data.size())
                {
                    int index = 0;
                    while (index < a.data.size())
                    {
                        if (a.data.at(index).num < b.data.at(index).num)
                        {
                            //return true;
                            result = true;
                            break;
                        }
                        if (a.data.at(index).num > b.data.at(index).num)
                        {
                            //return false;
                            result = false;
                            break;
                        }
                        if (a.data.at(index).num == b.data.at(index).num)
                        {
                            //Go to the next node
                        }
                        index++;
                    }
                }
        if (isNegative)
        {
            result = !result;
        }
        return result;
    }

    void print() const
    {
        if (isNegative)
        {
            cout << "-";
        }
        data.print();
    }

    void swap(BigNumber & other)
    {
        std::swap(isNegative, other.isNegative);
        data.swap(other.data);
    }

private:
    bool isNegative = false;
    DoubleLinkedList data;
};

class Sort
{
public:
    Sort(){}
    ~Sort(){}
    void selectionSort(BigNumber *a,int size)
    {
      //cout << "Entering Selection Sort" << endl;
      int comparisons = 0;
      int countSwap = 0;
      int iSmallest;
      for (int  i = 0; i < size-1; i++)
      {
          iSmallest = i;
          for (int j = i + 1; j < size; j++)
          {
              if (a[j] < a[iSmallest])
              {
                  iSmallest = j;
              }

          }
          if (iSmallest!=i) {
            countSwap++;
            a[iSmallest].swap(a[i]);
          }
          comparisons++;
      }
      countSwap=countSwap-1;

      //print(a, size);
      bigO<< "select" <<"                        "<< comparisons<< "            "<<countSwap<<endl;
    }

    bool open_the_bigO()
    {
        // this checks if file exists
        bigO.open("bigO.txt");
        if (!bigO)
        {
            // file does not exist
            bigO.open("bigO.txt", ifstream::app);
            if (!bigO.is_open())
            {
                cout << "Could not open" << endl;
                return false;
            }

        }
        bigO << "algorithm   #numbers(n)  #Comparisons   #Swaps"<<endl;

        return true;
    }

    void close_the_file()
    {
        // bigO.close;
    }
    // void primer_selection()
    // {
    //     int i - 0;
    //     int iSmallest = 0;
    //     j = 0;
    //     selectionSort(i, iSmallest, j);
    // }

private:
    fstream bigO;

};

void print(BigNumber *a, int size)
{
    for (int i = 0; i < size; i++)
    {
        a[i].print();
    }
}

int count_lines(string & filename, int digitsPerNode)
{
    std::ifstream ifs(filename.c_str());

    int counter = 0;
    while (!ifs.eof())
    {
        string line;
        ifs >> line;
        counter++;
    }
    return counter;
}
void input(BigNumber *a, string & filename, int digitsPerNode)
{
    std::ifstream ifs(filename.c_str());

    int counter = 0;
    while (!ifs.eof())
    {
        string line;
        ifs >> line;
        if(line.size()!=0){
        a[counter] = BigNumber(line, digitsPerNode);
        counter++;
    }
  }
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        //std::cerr("Usage: infinitearithmetic \"input=xyz.txt;digitsPerNode=<number>\"\n");
        return 1;
    }
    ArgumentManager am(argc, argv);
    std::string filename = am.get("input");
    std::string algorithm = am.get("algorithm");
    int digitsPerNode = std::stoi(am.get("digitsPerNode"));

    // std::string filename = "1.txt";
    // int digitsPerNode = 3;

    int size = count_lines(filename, digitsPerNode);
    BigNumber *a = new BigNumber[size];
    input(a, filename, digitsPerNode);

    Sort sort;
    sort.open_the_bigO();

    if (algorithm == "selection")
    {
      print(a, size);
      sort.selectionSort(a,size);
      print(a, size);
    }
    if (algorithm == "insertion")
    {

    }
    if (algorithm == "quick")
    {

    }
    if (algorithm == "merge")
    {

    }
    if (algorithm == "heap")
    {

    }

    /****************Insertion Sort - Working****************/
    // for (int i = 0; i < size - 1; i++)
    // {
    //     for (int j = i; j < size; j++)
    //     {
    //         if (a[j] < a[i])
    //         {
    //             a[i].swap(a[j]);
    //         }
    //     }
    // }
    return 0;
}