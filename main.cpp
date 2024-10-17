#include <iostream>

#include <catch2/catch_test_macros.hpp>

#include <cstdint>


struct ListNode
{
public:
    ListNode(int value, ListNode* prev = nullptr, ListNode* next = nullptr)
        : value(value), prev(prev), next(next)
    {
        if (prev != nullptr) prev->next = this;
        if (next != nullptr) next->prev = this;
    }

public:
    int value;
    ListNode* prev;
    ListNode* next;
};


class List
{
public:
    List()
        : m_head(new ListNode(static_cast<int>(0))), m_size(0),
        m_tail(new ListNode(0, m_head))
    {
    }

    virtual ~List()
    {
        Clear();
        delete m_head;
        delete m_tail;
    }

    bool Empty() { return m_size == 0; }

    unsigned long Size() { return m_size; }

    void PushFront(int value)
    {
        new ListNode(value, m_head, m_head->next);
        ++m_size;
    }

    void PushBack(int value)
    {
        new ListNode(value, m_tail->prev, m_tail);
        ++m_size;
    }

    int PopFront()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_head->next->next);
        int ret = node->value;
        delete node;
        return ret;
    }

    int PopBack()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_tail);
        int ret = node->value;
        delete node;
        return ret;
    }

    void Clear()
    {
        auto current = m_head->next;
        while (current != m_tail)
        {
            current = current->next;
            delete extractPrev(current);
        }
    }

private:
    ListNode* extractPrev(ListNode* node)
    {
        auto target = node->prev;
        target->prev->next = target->next;
        target->next->prev = target->prev;
        --m_size;
        return target;
    }

private:
    ListNode* m_head;
    ListNode* m_tail;
    unsigned long m_size;
};



TEST_CASE("First task")
{
    List list;
    list.PushBack(5);
    list.PushBack(10);
    SECTION("Empty")
    {
        INFO("list is not empty, something is wrong");
        CHECK(list.Empty() != true);
    }
    SECTION("SIZE")
    {
        INFO("Incorrect size");
        CHECK(list.Size() == 2);
    }
    list.Clear();
    SECTION("CLEAR")
    {
        INFO("After clear list is not empty");
        CHECK(list.Empty() == true);
        //CHECK(list.m_head->next == list.m_tail);
    }
}

TEST_CASE("Second task")
{
    List list;
    list.PushBack(5);
    SECTION("PUSH_BACK")
    {
        INFO("Incorrect size");
        CHECK(list.Size() == 1);
    }
    list.PushFront(6);
    SECTION("PUSH_FRONT")
    {
        INFO("Incorrect size");
        CHECK(list.Size() == 2);
    }
    list.Clear();
    SECTION("POP_BACK")
    {
        bool error = false;
        try {
            list.PopBack();
        }
        catch (std::runtime_error ex)
        {
            error = true;
        }
        INFO("The function pop_back doesn't work correctly");
        CHECK(error);
    }
    SECTION("POP_FRONT")
    {
        bool error = false;
        try {
            list.PopFront();
        }
        catch (std::runtime_error ex)
        {
            error = true;
        }
        INFO("The function pop_front doesn't work correctly");
        CHECK(error);
    }
}