#include <iostream>
#include <initializer_list>
#include <utility>

template <typename T>
class Node
{
public:
    T m_data;
    Node<T> *m_next;
};

template <typename T>
class ForwardList
{
public:
    struct ForwardIterator
    {
        ForwardIterator(Node<T> *ptr) : m_ptr(ptr) {}
        Node<T> &operator*() const { return *m_ptr; }
        Node<T> *operator->() { return m_ptr; }
        ForwardIterator &operator++()
        {
            m_ptr = m_ptr->m_next;
            return *this;
        }
        friend bool operator==(const ForwardIterator &l, const ForwardIterator &r) { return l.m_ptr == r.m_ptr; }
        friend bool operator!=(const ForwardIterator &l, const ForwardIterator &r) { return l.m_ptr != r.m_ptr; }
        friend class ForwardList;

    private:
        Node<T> *m_ptr;
    };
    ForwardIterator begin() { return ForwardIterator(m_head); }
    ForwardIterator end() { return ForwardIterator(m_tail); }
    ForwardIterator erase_after(ForwardIterator pos)
    {
        Node<T> *current = pos.m_ptr;
        Node<T> *deleted = current->m_next;
        if (deleted != nullptr)
        {
            current->m_next = deleted->m_next;
            delete deleted;
            --m_size;
        }
        return ++pos;
    }
    ForwardIterator erase_after(ForwardIterator first, ForwardIterator last)
    {
        Node<T> *curr = first.m_ptr;
        Node<T> *temp;
        ++first;
        while (first != last && first != end())
        {
            temp = first.m_ptr;
            ++first;
            delete temp;
            --m_size;
        }
        curr->m_next = last.m_ptr;
        return last;
    }

public:
    ForwardList() : m_head(nullptr), m_tail(nullptr), m_size(0) {}

    ForwardList(const ForwardList<T> &other) : m_size(other.m_size)
    {
        m_head = new Node<T>();
        m_head->m_data = other.m_head->m_data;
        m_tail = new Node<T>();
        m_tail->m_data = other.m_tail->m_data;

        auto it = other.begin();
        Node<T> *first = m_head;
        Node<T> *current = m_head;

        // TODO: COPY REST
    }
    ForwardList(ForwardList<T> &&other) : m_head(std::move(other.m_head)), m_tail(std::move(other.m_tail)), m_size(other.m_size)
    {
        other.m_size = 0;
        other.m_head = nullptr;
        other.m_tail = nullptr;
    }

    ForwardList &operator=(const ForwardList &other)
    {
        if (this != &other)
        {
            m_head = new Node<T>();
            m_head->m_data = other.m_head->m_data;
            m_tail = new Node<T>();
            m_tail->m_data = other.m_tail->m_data;

            // TODO: COPY REST
        }
        return *this;
    }
    ForwardList &operator=(ForwardList &&other)
    {
        if (this != &other)
        {
            // TODO: DELETE OLD LIST
            delete m_head;
            delete m_tail;
            m_head = std::move(other.m_head);
            m_tail = std::move(other.m_tail);
            m_size = other.size;
        }
        return *this;
    }

    void push_front(const T &value)
    {
        Node<T> *temp = new Node<T>();
        temp->m_data = value;

        if (m_head == nullptr)
        {
            m_head = temp;
            if (m_tail == nullptr)
            {
                Node<T> *end_element = new Node<T>();
                m_tail = end_element;
            }
            m_head->m_next = m_tail;
        }
        else
        {
            temp->m_next = m_head;
            m_head = temp;
        }
        m_size++;
    }
    void push_front(T &&value)
    {
        Node<T> *temp = new Node<T>();
        temp->m_data = std::move(value);
        if (m_head == nullptr)
        {
            m_head = temp;
            if (m_tail == nullptr)
            {
                Node<T> *end_element = new Node<T>();
                m_tail = end_element;
            }
            m_head->m_next = m_tail;
        }
        else
        {
            temp->m_next = m_head;
            m_head = temp;
        }
        m_size++;
    }

    void pop_front()
    {
        if (empty())
            return;
        Node<T> *front = m_head;
        if (m_head->m_next == m_tail)
        {
            delete m_tail;
            delete m_head;
        }
        else if (m_head->m_next != m_tail)
        {
            m_head = m_head->m_next;
            delete front;
        }
        --m_size;
    }
    size_t size() const noexcept { return m_size; }
    bool empty() const noexcept { return m_size == 0 ? true : false; }

    ~ForwardList()
    {
        if (empty())
            return;

        Node<T> *curr = m_head;
        while (m_head != m_tail)
        {
            curr = m_head;
            m_head = m_head->m_next;
            delete curr;
        }
        delete m_tail;
    }

private:
    Node<T> *m_head;
    Node<T> *m_tail;
    size_t m_size;
};

int main()
{
    ForwardList<int> fl;
    fl.push_front(13);
    int x = 10;
    fl.push_front(x);
    fl.pop_front();
    fl.pop_front();
    fl.pop_front();
    fl.pop_front();
    std::cout << "List size: " << fl.size() << std::endl;
    std::cout << "empty() " << fl.empty() << std::endl;
    // My implementation allows pop_front() on empty list

    ForwardList<int> list2;
    list2.push_front(10);
    list2.push_front(9);
    list2.push_front(5);

    ForwardList<int> list3(std::move(list2));

    ForwardList<int> list4;
    list4.push_front(10);
    list4.push_front(9);
    list4.push_front(5);
    list4.erase_after(list4.begin(), list4.end());
    std::cout << "list4 empty() " << list4.empty() << std::endl;
}
