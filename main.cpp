#include <iostream>
#include <queue>
#include <exception>

struct emptyStack : std::exception {
    const char * what() const noexcept {
        return "Empty stack!";
    }
};

template<typename T>
class Stack {
  public:
    void push(T x) {
        if (!q1.empty())
            q1.push(x);
        else
            q2.push(x);
    }

    void pop() {
        if (!q1.empty()) {
            while (q1.size() > 1) {
                q2.push(q1.front());
                q1.pop();
            }
            q1.pop();
        }
        else if (!q2.empty()) {
            while (q2.size() > 1) {
                q1.push(q2.front());
                q2.pop();
            }
            q2.pop();
        }
        else
            throw emptyStack();
        
    }

    T top() {
        int rtn;
        if (!q1.empty()) {
            while (q1.size() > 1) {
                q2.push(q1.front());
                q1.pop();
            }
            rtn = q1.front();
            q2.push(rtn);
            q1.pop();
        }
        else if (!q2.empty()) {
            while (q2.size() > 1) {
                q1.push(q2.front());
                q2.pop();
            }
            rtn = q2.front();
            q1.push(rtn);
            q2.pop();
        }
        else
            throw emptyStack();
        return rtn;
    }

    bool empty() {
        return q1.empty() && q2.empty();
    }

  private:
    std::queue<T> q1, q2;
};


int main() {

Stack<int> st;
st.push(1);
st.push(2);
st.push(3);

Stack<int> st_back;
while (!st.empty()) {
std::cout << st.top() << std::endl;
st_back.push(st.top());
st.pop();
}

try  {
    st.top();
}
catch (std::exception & e) {
    std::cout << e.what() << std::endl;
}

while (!st_back.empty()) {
std::cout << st_back.top() << std::endl;
st.push(st_back.top());
st_back.pop();
}

}
