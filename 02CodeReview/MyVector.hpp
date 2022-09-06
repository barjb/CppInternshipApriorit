#ifndef CODEREVIEWTASK_MYVECTORR_HPP
#define CODEREVIEWTASK_MYVECTORR_HPP
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <memory>

/*
 * MyVector stores a collection of objects with their names.
 *
 * For each object T, MyVector stores T`s name as std::string.
 * Several objects can have similar name.
 * operator[](const std::string& name) should return the first object
 * with the given name.
 *
 * Your task is to find as many mistakes and drawbacks in this code
 * (according to the presentation) as you can.
 * Annotate these mistakes with comments.
 *
 * Once you have found all the mistakes, rewrite the code
 * so it would not change its original purpose
 * and it would contain no mistakes.
 * Try to make the code more efficient without premature optimization.
 *
 * You can change MyVector interface completely, but there are several rules:
 * 1) you should correctly and fully implement copy-on-write idiom.
 * 2) std::pair<const T&, const std::string&> operator[](int index) const must take constant time
at worst.
 * 3) const T& operator[](const std::string& name) const should be present.
 * 4) both operator[] should have non-const version.
 * 5) your implementation should provide all the member types of std::vector.
 * 6) your implementation should provide the following functions:
 * 1) begin(), cbegin(), end(), cend()
 * 2) empty(), size()
 * 3) reserve(), clear()
 */

namespace cnntrs
{
    template <typename T>
    class MyVector : public std::vector<T>
    {
        using const_iterator = typename std::vector<T>::const_iterator;
        using size_type = typename std::vector<T>::size_type;

    public:
        MyVector() : std::vector<T>(), m_names(std::make_shared<std::vector<std::string>>(std::vector<std::string>())) {}
        MyVector(const MyVector &other) : std::vector<T>(other), m_names(other.m_names) {}
        ~MyVector() {}
        void push_back(const T &obj, const std::string &name)
        {
            copy_names();
            std::vector<T>::push_back(obj);
            m_names->push_back(name);
        }

        std::pair<const T &, const std::string &> operator[](int index) const
        {
            if (index < 0 || index >= std::vector<T>::size())
            {
                throw std::out_of_range("Index is out of range");
            }
            return std::pair<const T &, const std::string &>(std::vector<T>::operator[](index),
                                                             m_names->at(index));
        }

        const T &operator[](const std::string &name) const
        {
            std::vector<std::string>::const_iterator iter = std::find(m_names->begin(), m_names->end(),
                                                                      name);
            if (iter == m_names->end())
            {
                throw std::invalid_argument(name + " is not found in the MyVector");
            }
            return std::vector<T>::operator[](iter - m_names->begin());
        }

        const std::string &operator[](const int index)
        {
            if (index < 0 || index >= std::vector<T>::size())
            {
                throw std::out_of_range("Index is out of range");
            }
            return m_names->at(index);
        }
        T &operator[](const std::string &name)
        {
            std::vector<std::string>::const_iterator iter = std::find(m_names->begin(), m_names->end(),
                                                                      name);
            if (iter == m_names->end())
            {
                throw std::invalid_argument(name + " is not found in the MyVector");
            }
            return std::vector<T>::operator[](iter - m_names->begin());
        }

        const_iterator begin() const noexcept
        {
            return std::vector<T>::begin();
        }
        const_iterator cbegin() const noexcept
        {
            return std::vector<T>::cbegin();
        }
        const_iterator end() const noexcept
        {
            return std::vector<T>::end();
        }
        const_iterator cend() const noexcept
        {
            return std::vector<T>::cend();
        }
        bool empty() const noexcept
        {
            return std::vector<T>::empty();
        }
        size_type size() const noexcept
        {
            return std::vector<T>::size();
        }
        void clear() noexcept
        {
            std::vector<T>::clear();
            m_names->clear();
        }
        void reserve(size_t new_cap)
        {
            std::vector<T>::reserve(new_cap);
            m_names->reserve(new_cap);
        }

    private:
        void copy_names()
        {
            if (m_names.use_count() == 1)
            {
                return;
            }
            std::shared_ptr<std::vector<std::string>> temp_names = std::make_shared<std::vector<std::string>>(*m_names);
            m_names = temp_names;
        }

    private:
        // Use copy-on-write idiom for efficiency (not a premature optimization)
        std::shared_ptr<std::vector<std::string>> m_names;
    };
}
#endif // CODEREVIEWTASK_MYVECTOR_HPP