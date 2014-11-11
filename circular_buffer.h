#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <array>
#include <iterator>

// Forward declarations of iterator types
template <class T, std::size_t N> class circular_buffer_iter;
template <class T, std::size_t N> class const_circular_buffer_iter;

template<class T, std::size_t N> class circular_buffer {
    friend class circular_buffer_iter<T, N>;
    friend class const_circular_buffer_iter<T, N>;
public:
    typedef circular_buffer_iter<T, N>          iterator;
    typedef const_circular_buffer_iter<T, N>    const_iterator;
    typedef std::ptrdiff_t                      difference_type;
    typedef std::size_t                         size_type;
    typedef T                                   value_type;
    typedef T*                                  pointer;
    typedef T&                                  reference;
    typedef const T&                            const_reference;

    explicit circular_buffer() :
        m_buffer{},
        m_begin{0},
        m_size{0}
    {
        static_assert(N != 0, "Circular buffer size must be positive.");
    }

    bool empty() const {
        return m_size == 0;
    }

    bool full() const {
        return m_size == N;
    }

    constexpr size_type capacity() const {
        return N;
    }

    constexpr size_type size() const {
        return m_size;
    }

    void pop_front() {
        if (!empty()) {
            --m_size;
            increment_begin();
        }
    }

    void pop_back() {
        if (!empty()) {
            --m_size;
        }
    }

    reference front() {
        return m_buffer[m_begin];
    }

    const_reference front() const {
        return m_buffer[m_begin];
    }

    reference back() {
        return m_buffer[(m_begin + m_size  - 1) % N];
    }

    const_reference back() const {
        return m_buffer[(m_begin + m_size  - 1) % N];
    }

    void push_back(const_reference x) {
        m_buffer[m_end()] = x;
        if (full()) {
            increment_begin();
        } else {
            ++m_size;
        }
    }

    void push_front(const_reference x) {
        decrement_begin();
        m_buffer[m_begin] = x;
        if (!full()) {
            ++m_size;
        }
    }

    iterator begin() {
        return iterator(*this, 0);
    }

    const_iterator begin() const {
        return cbegin();
    }

    const_iterator cbegin() const {
        return const_iterator(*this, 0);
    }

    iterator end() {
        return iterator(*this, m_size);
    }

    const_iterator end() const {
        return cend();
    }

    const_iterator cend() const {
        return const_iterator(*this, m_size);
    }

    const_reference operator[](size_type i) const {
        return m_buffer[(m_begin + i) % N];
    }

    reference operator[](size_type i) {
        return m_buffer[(m_begin + i) % N];
    }

private:
    std::array<value_type, N> m_buffer;
    size_type m_begin;
    size_type m_size;

    constexpr size_type m_end() const {
        return (m_begin + m_size) % N;
    }

    void increment_begin() {
        m_begin = (m_begin + 1) % N;
    }

    void decrement_begin() {
        if (m_begin) {
            m_begin = (m_begin - 1) % N;
        } else {
            m_begin = N - 1;
        }
    }
};

template <class T, std::size_t N>
class circular_buffer_iter {
public:
    explicit circular_buffer_iter(circular_buffer<T, N>& cb, int offset)
        : m_circular_buffer(cb), m_offset{offset} { }

    bool operator==(const circular_buffer_iter<T, N>& rhs) const {
        return (&m_circular_buffer == &(rhs.m_circular_buffer))
            && m_offset == rhs.m_offset;
    }

    bool operator!=(const circular_buffer_iter<T, N>& rhs) const {
        return !operator==(rhs);
    }

    circular_buffer_iter& operator++() {
        ++m_offset;
        return *this;
    }

    circular_buffer_iter operator++(int) {
        circular_buffer_iter<T, N> clone(*this);
        ++m_offset;
        return clone;
    }

    typename circular_buffer<T, N>::reference operator*() const {
        return m_circular_buffer[m_offset];
    }

private:
    circular_buffer<T, N>& m_circular_buffer;
    int m_offset;
};

template <class T, std::size_t N>
class const_circular_buffer_iter {
public:
    explicit const_circular_buffer_iter(const circular_buffer<T, N>& cb,
            int offset) : m_circular_buffer(cb), m_offset{offset} { }

    bool operator==(const const_circular_buffer_iter<T, N>& rhs) const {
        return &m_circular_buffer == &(rhs.m_circular_buffer)
            && m_offset == rhs.m_offset;
    }

    bool operator!=(const const_circular_buffer_iter<T, N>& rhs) const {
        return !operator==(rhs);
    }

    const_circular_buffer_iter& operator++() {
        ++m_offset;
        return *this;
    }

    const_circular_buffer_iter operator++(int) {
        const_circular_buffer_iter<T, N> clone(*this);
        ++m_offset;
        return clone;
    }

    typename circular_buffer<T, N>::const_reference operator*() const {
        return m_circular_buffer[m_offset];
    }

private:
    const circular_buffer<T, N>& m_circular_buffer;
    int m_offset;
};

#endif

