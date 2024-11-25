## The cleanup problem

Let’s say that you are writing a program that needs to send some data over a network. However, establishing a connection to the server is expensive, so you want to collect a bunch of data and then send it all at once. Such a class might be structured like this:
```cpp
class NetworkData
{
private:
    std::string m_serverName{};
    DataStore m_data{};

public:
	NetworkData(std::string_view serverName)
		: m_serverName { serverName }
	{
	}

	void addData(std::string_view data)
	{
		m_data.add(data);
	}

	void sendData()
	{
		// connect to server
		// send all data
		// clear data
	}
};

int main()
{
    NetworkData n("someipAddress");

    n.addData("somedata1");
    n.addData("somedata2");

    n.sendData();

    return 0;
}
```

However, this `NetworkData` has a potential issue. It relies on `sendData()` being explicitly called before the program is shut down. If the user of `NetworkData` forgets to do this, the data will not be sent to the server, and will be lost when the program exits. Now, you might say, “well, it’s not hard to remember to do this!”, and in this particular case, you’d be right. But consider a slightly more complex example, like this function:
```cpp
bool someFunction()
{
    NetworkData n("someipAddress");

    n.addData("somedata1");
    n.addData("somedata2");

    if (someCondition)
        return false;

    n.sendData();
    return true;
}
```

In this case, we may not get to send our data.

## Destructors

Constructors are special member functions that are called when an object of a non-aggregate class type is created and are used to initialize member variables, and do any other setup tasks required to ensure objects of the class are ready for use.

Classes also have another special member function that is called automatically when an object of a non-aggregate class type is destroyed called **destructors**. Destructors allow a class to do any cleanup before an object of the class is destroyed.

Like constructors, destructors have naming rules:
1. The destructor must have the same name as the class, preceded by a tilde (~)
2. The destructor cannot take arguments
3. The destructor has no return type
- A class can only have a single destructor

Generally you don't call a destructor explicitly since it's automatically called when the object is destroyed, and there's rarely cases where you'd want to clean up an object more than once.

Also, destructors may safely call other member functions, since the object isn't destroyed until the destructor finishes executing.

Let's see an example:
```cpp
#include <iostream>

class Simple
{
private:
    int m_id {};

public:
    Simple(int id)
        : m_id { id }
    {
        std::cout << "Constructing Simple " << m_id << '\n';
    }

    ~Simple() // here's our destructor
    {
        std::cout << "Destructing Simple " << m_id << '\n';
    }

    int getID() const { return m_id; }
};

int main()
{
    // Allocate a Simple
    Simple simple1{ 1 };
    {
        Simple simple2{ 2 };
    } // simple2 dies here

    return 0;
} // simple1 dies here
```

```
Constructing Simple 1
Constructing Simple 2
Destructing Simple 2
Destructing Simple 1
```

## Improving the NetworkData program

Original:
```cpp
class NetworkData
{
private:
    std::string m_serverName{};
    DataStore m_data{};

public:
	NetworkData(std::string_view serverName)
		: m_serverName { serverName }
	{
	}

	void addData(std::string_view data)
	{
		m_data.add(data);
	}

	void sendData()
	{
		// connect to server
		// send all data
		// clear data
	}
};

int main()
{
    NetworkData n("someipAddress");

    n.addData("somedata1");
    n.addData("somedata2");

    n.sendData();

    return 0;
}
```

Optimized with a destructor explicitly calling `sendData()`:
```cpp
class NetworkData
{
private:
    std::string m_serverName{};
    DataStore m_data{};

public:
	NetworkData(std::string_view serverName)
		: m_serverName { serverName }
	{
	}

	~NetworkData()
	{
		sendData(); // make sure all data is sent before object is destroyed
	}

	void addData(std::string_view data)
	{
		m_data.add(data);
	}

	void sendData()
	{
		// connect to server
		// send all data
		// clear data
	}
};

int main()
{
    NetworkData n("someipAddress");

    n.addData("somedata1");
    n.addData("somedata2");

    return 0;
}
```

With this destructor, now our `NetworkData` object will always send whatever data it has before the object is destroyed automatically.
