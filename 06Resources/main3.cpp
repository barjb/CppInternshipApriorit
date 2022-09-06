#include <iostream>
#include <memory>
#include <atomic>

template <typename T>
class shared_ptr
{
public:
    shared_ptr(T *pointer = nullptr);
    shared_ptr(const shared_ptr &r) noexcept;
    shared_ptr &operator=(const shared_ptr &r) noexcept;
    shared_ptr(shared_ptr &&r) noexcept;
    shared_ptr &operator=(shared_ptr &&r) noexcept;
    T *get() const;
    void reset(T *ptr) noexcept;
    explicit operator bool() const noexcept;
    long use_count() const noexcept;
    T &operator*() const;
    T *operator->() const;
    ~shared_ptr();

private:
    T *m_ptr;
    int *m_reference_count;
};

template <typename T>
shared_ptr<T>::shared_ptr(T *pointer) : m_ptr(pointer)
{
    if (m_ptr != nullptr)
        m_reference_count = new int(1);
    else
        m_reference_count = new int(0);
}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr &r) noexcept : m_ptr(r.m_ptr), m_reference_count(r.m_reference_count)
{
    if (m_ptr != nullptr)
    {
        (*m_reference_count)++;
    }
}
template <typename T>
shared_ptr<T> &shared_ptr<T>::operator=(const shared_ptr<T> &r) noexcept
{
    if (*m_reference_count == 1)
        delete m_ptr;
    m_ptr = r.m_ptr;
    m_reference_count = r.m_reference_count;
    if (m_ptr != nullptr)
    {
        ++(*m_reference_count);
    }
}
template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr<T> &&r) noexcept : m_ptr(r.m_ptr), m_reference_count(r.m_reference_count)
{
    r.m_ptr = nullptr;
    r.m_reference_count = nullptr;
}
template <typename T>
shared_ptr<T> &shared_ptr<T>::operator=(shared_ptr<T> &&r) noexcept
{
    if (*m_reference_count == 1)
        delete m_ptr;

    m_ptr = r.m_ptr;
    m_reference_count = r.m_reference_count;
    r.m_ptr = nullptr;
    r.m_reference_count = nullptr;
}

template <typename T>
T *shared_ptr<T>::get() const
{
    return m_ptr;
}

template <typename T>
void shared_ptr<T>::reset(T *ptr) noexcept
{
    if (*m_reference_count == 1)
        delete m_ptr;
    m_ptr = ptr;
    *m_reference_count = 1;
}

template <typename T>
shared_ptr<T>::operator bool() const noexcept
{
    if (m_ptr == nullptr)
        return false;
    else
        return true;
}

template <typename T>
long shared_ptr<T>::use_count() const noexcept
{
    return *m_reference_count;
}

template <typename T>
T &shared_ptr<T>::operator*() const
{
    return *m_ptr;
}
template <typename T>

T *shared_ptr<T>::operator->() const
{
    return m_ptr;
}

template <typename T>
shared_ptr<T>::~shared_ptr()
{
    if (m_reference_count == nullptr)
        return;
    if (*m_reference_count == 0 || --(*m_reference_count) == 0)
    {
        if (m_reference_count != nullptr)
            delete m_reference_count;
        delete m_ptr;
    }
}

template <typename T>
class weak_ptr
{
public:
    weak_ptr(const std::shared_ptr<T> &r);
    weak_ptr(const weak_ptr &r);
    weak_ptr<T> &operator=(const weak_ptr<T> &r);
    weak_ptr<T> &operator=(const std::shared_ptr<T> &r);
    void reset();
    bool expired() const;
    std::shared_ptr<T> lock() const noexcept;
    ~weak_ptr() noexcept;

private:
    std::shared_ptr<T> m_ptr;
    int *m_strong_reference_count;
};

template <typename T>
weak_ptr<T>::weak_ptr(const std::shared_ptr<T> &r) : m_ptr(r), m_strong_reference_count(new int(r.use_count()))
{
}

template <typename T>
weak_ptr<T>::weak_ptr(const weak_ptr<T> &r) : m_ptr(r.lock()), m_strong_reference_count(new int(0))
{
}
template <typename T>
weak_ptr<T> &weak_ptr<T>::operator=(const weak_ptr<T> &r)
{
    m_ptr = r.m_ptr;
    m_strong_reference_count = r.m_strong_reference_count;
}
template <typename T>
weak_ptr<T> &weak_ptr<T>::operator=(const std::shared_ptr<T> &r)
{
    m_ptr = r;
    m_strong_reference_count = new int(r.use_count());
}
template <typename T>
void weak_ptr<T>::reset()
{
    delete m_ptr;
}
template <typename T>
bool weak_ptr<T>::expired() const
{
    if (*m_strong_reference_count == 0)
        return true;
    else
        return false;
}
template <typename T>
std::shared_ptr<T> weak_ptr<T>::lock() const noexcept
{
    if (expired())
        return shared_ptr<T>();
    else
        return m_ptr;
}
template <typename T>
weak_ptr<T>::~weak_ptr() noexcept
{
    if (*m_strong_reference_count == 0)
    {
        if (m_ptr.get() != nullptr)
        {
            delete m_ptr;
            delete m_strong_reference_count;
        }
    }
}

int main()
{
    // shared_ptr<T> suffers from memory leaks
    // weak_ptr<T> wasn't tested at all; I wanted to finish shared_ptr at first

    shared_ptr<int> u{};
    shared_ptr<int> n(new int(3));

    shared_ptr<int> b = n;
    shared_ptr<int> m(std::move(n));

    // Leaks detected on both assignment operator overloads
    shared_ptr<int> op;
    op = b;
    shared_ptr<int> k;
    shared_ptr<int> l(new int(5));
    k = std::move(l);
}