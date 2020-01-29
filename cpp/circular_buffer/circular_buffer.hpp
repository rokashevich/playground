#ifndef CIRCULAR_BUFFER_HPP
#define CIRCULAR_BUFFER_HPP
// https://github.com/JustasMasiulis/circular_buffer
#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include <type_traits>

template <class size_type, size_type N>
struct cb_index_wrapper {
  inline static constexpr size_type increment(size_type value) noexcept {
    return (value + 1) % N;
  }

  inline static constexpr size_type decrement(size_type value) noexcept {
    return (value + N - 1) % N;
  }
};

template <class T, bool = ::std::is_trivially_destructible<T>::value>
union optional_storage {
  struct empty_t {};

  empty_t _empty;
  T _value;

  ~optional_storage() {}
};

template <class S, class TC, std::size_t N>
class cb_iterator {
  template <class, class, std::size_t>
  friend class cb_iterator;

  S* _buf;
  std::size_t _pos;
  std::size_t _left_in_forward;

  typedef cb_index_wrapper<std::size_t, N> wrapper_t;

 public:
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef TC value_type;
  typedef std::ptrdiff_t difference_type;
  typedef value_type* pointer;
  typedef value_type& reference;

  explicit constexpr cb_iterator(S* buf, std::size_t pos,
                                 std::size_t left_in_forward) noexcept
      : _buf(buf), _pos(pos), _left_in_forward(left_in_forward) {}

  constexpr reference operator*() const noexcept {
    return (_buf + _pos)->_value;
  }

  cb_iterator& operator++() noexcept {
    _pos = wrapper_t::increment(_pos);
    --_left_in_forward;
    return *this;
  }

  template <class Tx, class Ty>
  constexpr bool operator==(const cb_iterator<Tx, Ty, N>& lhs) const noexcept {
    return lhs._left_in_forward == _left_in_forward && lhs._pos == _pos &&
           lhs._buf == _buf;
  }

  template <class Tx, class Ty>
  constexpr bool operator!=(const cb_iterator<Tx, Ty, N>& lhs) const noexcept {
    return !(operator==(lhs));
  }
};

template <typename T, std::size_t N>
class circular_buffer {
 public:
  typedef T value_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef T& reference;
  typedef T* pointer;
  typedef cb_iterator<optional_storage<T>, T, N> iterator;

 private:
  typedef cb_index_wrapper<size_type, N> wrapper_t;
  typedef optional_storage<T> storage_type;

  size_type _head;
  size_type _tail;
  size_type _size;
  storage_type _buffer[N];

  inline void destroy(size_type idx) noexcept { _buffer[idx]._value.~T(); }

 public:
  constexpr explicit circular_buffer()
      : _head(1), _tail(0), _size(0), _buffer() {}

  ~circular_buffer() {
    while (_size != 0) {
      size_type old_tail = _tail;
      --_size;
      _tail = wrapper_t::decrement(_tail);
      destroy(old_tail);
    }

    _head = 1;
    _tail = 0;
  }

  /// modifiers
  void push_back(const value_type& value) {
    size_type new_tail;
    if (_size == N) {
      new_tail = _head;
      _head = wrapper_t::increment(_head);
      --_size;
      _buffer[new_tail]._value = value;
    } else {
      new_tail = wrapper_t::increment(_tail);
      new (::std::addressof(_buffer[new_tail]._value)) T(value);
    }

    _tail = new_tail;
    ++_size;
  }

  /// iterators
  iterator begin() noexcept {
    if (_size == 0) return end();
    return iterator(_buffer, _head, _size);
  }

  iterator end() noexcept {
    return iterator(_buffer, wrapper_t::increment(_tail), 0);
  }
};
#endif
