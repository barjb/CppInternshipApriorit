#include <iostream>

class CFGuard
{
public:
    CFGuard(HANDLE handle) : m_handle(handle) {}
    ~CFGuard()
    {
        CloseHandle(m_handle);
    }

private:
    HANDLE m_handle;
};

int main()
{
}