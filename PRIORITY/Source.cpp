#include <iostream>
#include <string>

using namespace std;

struct PrintRequest 
{
    string username;
    string requestTime;
    int priority;
};

class PrinterQueue 
{
    PrintRequest queue[100];
    int numTasks;
    void sortQueue();

public:
    PrinterQueue() : numTasks(0) {}

    void addPrintRequest(const string& username, int priority, const string& requestTime);

    PrintRequest extractPrintRequest();

    bool isEmpty() const;
};

void PrinterQueue::addPrintRequest(const string& username, int priority, const string& requestTime) 
{
    if (numTasks < 100) 
    {
        queue[numTasks].username = username;
        queue[numTasks].requestTime = requestTime;
        queue[numTasks].priority = priority;
        numTasks++;
        sortQueue(); 
    }
    else 
    {
        cout << "Printer queue is full. Unable to add print request." << endl;
    }
}

PrintRequest PrinterQueue::extractPrintRequest() 
{
    if (numTasks > 0)
    {
        PrintRequest temp = queue[0];
        for (int i = 1; i < numTasks; i++) 
        {
            queue[i - 1] = queue[i];
        }
        numTasks--;
        return temp;
    }
    else 
    {
        cout << "Printer queue is empty. No print request to extract." << endl;
        return PrintRequest();
    }
}

bool PrinterQueue::isEmpty() const 
{
    return numTasks == 0;
}

void PrinterQueue::sortQueue() 
{
    for (int i = 1; i < numTasks; i++) 
    {
        PrintRequest key = queue[i];
        int j = i - 1;
        while (j >= 0 && queue[j].priority < key.priority) 
        {
            queue[j + 1] = queue[j];
            j = j - 1;
        }
        queue[j + 1] = key;
    }
}

int main() 
{
    PrinterQueue printer;

    while (true) 
    {
        string username;
        int priority;
        string requestTime;

        cout << "Enter username (or 'exit' to quit): ";
        getline(cin, username);
        if (username == "exit") 
        {
            break;
        }

        cout << "Enter priority: ";
        cin >> priority;
        if (priority < 0) 
        {
            cout << "Priority must be a non-negative integer." << endl;
            cin.ignore();
            continue;
        }
        else if (priority > 11) 
        {
            cout << "Priority must be under/equal 11." << endl;
            cin.ignore();
            continue;
        }
        cout << "Enter request time: ";
        cin.ignore();
        getline(cin, requestTime);
        printer.addPrintRequest(username, priority, requestTime);
    }

    while (!printer.isEmpty()) 
    {
        PrintRequest request = printer.extractPrintRequest();
        cout << "Printing: User - " << request.username << ", Priority - " << request.priority << ", Time - " << request.requestTime << endl;
    }

    return 0;
}