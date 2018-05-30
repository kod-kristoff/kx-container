#ifndef KX_STACK_HPP_
#   define KX_STACK_HPP_

#include <cassert>

namespace kx
{
    template<class Stack> class stack_range;

    template<typename T>
    class base_stack
    {
        friend class stack_range<base_stack<T>>;
    public:
        // ===========================
        // member types
        // ===========================

        typedef unsigned int                size_type;
        typedef T                           value_type;
        typedef T &                         reference;
        typedef T const &                   const_reference;
        typedef stack_range<base_stack<T>>  range;

        // ===========================
        // lifecycle
        // ===========================
        explicit base_stack ()
            :   _data (nullptr)
            ,   _capacity (0)
            ,   _size (0)
        {}
        ~base_stack () {}

        // ===========================
        // element access
        // ===========================
        reference       top ()
        {
            return _data [_size - 1];
        }
        const_reference top ()   const
        {
            return _data [_size - 1];
        }

        // ===========================
        // capacity
        // ===========================
        bool            is_empty () const
        {
            return (0 == _size);
        }

        inline
        size_type       size ()  const
        {
            return _size;
        }

        size_type       capacity ()  const
        {
            return _capacity;
        }

        // ===========================
        // modifiers
        // ===========================
        void            push (value_type value)
        {
            assert (_size + 1 < _capacity);
            _data [_size] = value;
            ++_size;
        }
        void            pop ()
        {
            assert (_size > 0);
            --_size;
        }
        void            clear ()
        {
            _size = 0;
        }

    protected:
        void
        set_data (
            value_type *    data,
            size_type       capacity
        )
        {
            _data = data;
            _capacity = capacity;
        }

        value_type *
        get_data ()
        {
            return _data;
        }

        value_type const *
        get_data ()
        const
        {
            return _data;
        }
    private: // data
        value_type *    _data;
        size_type       _size;
        size_type       _capacity;
    };

    template<typename T>
    bool
    is_empty (base_stack<T> const & stack)
    {
        return 0 == stack.size ();
    }

    template<class T>
    class stack_fixed_rt : public base_stack<T>
    {
        friend class stack_range<stack_fixed_rt<T>>;
    public:
        // ===========================
        // member types
        // ===========================

        typedef base_stack<T>       base_type;
        typedef typename base_type::size_type  size_type;
        typedef T                   value_type;
        typedef T &                 reference;
        typedef T const &           const_reference;
        typedef stack_range<stack_fixed_rt<T>>   range;
        // ===========================
        // lifecycle
        // ===========================
        explicit stack_fixed_rt (size_type capacity)
            :   base_type ()
        {
            base_type::set_data(
                new T[capacity],
                capacity
            );
        }
        ~stack_fixed_rt ()
        {
            delete [] base_type::get_data();
        }

        // ===========================
        // element access
        // ===========================

        // ===========================
        // capacity
        // ===========================
        bool            is_full () const
        {
            return base_type::size () == base_type::capacity ();
        }

    };

    template<typename T>
    bool
    is_full (base_stack<T> const & stack)
    {
        return stack.size () == stack.capacity ();
    }

    template<class Stack>
    class stack_range
    {
    public:
        // ===========================
        // member types
        // ===========================
        typedef Stack                                   stack_type;
        typedef typename stack_type::const_reference    const_reference;
        typedef typename stack_type::size_type          size_type;
        // ===========================
        // lifecycle
        // ===========================
        stack_range (stack_type const & stack)
            :   _stack (stack)
            ,   _current (0)
        {}

        // ===========================
        // access
        // ===========================
        const_reference get () const
        {
            return _stack.get_data () [_current];
        }

        // ===========================
        // traversal
        // ===========================
        bool at_end () const
        {
            return _current == _stack.size ();
        }

        void advance ()
        {
            assert (!at_end ());
            ++_current;
        }
    private:
        stack_type const &  _stack;
        size_type           _current;
    };

    template<class T>
    stack_range<stack_fixed_rt<T>> begin (stack_fixed_rt<T> const & stack)
    {
        return stack_range<stack_fixed_rt<T>> (stack);
    }

} // namespace kx
#endif // KX_STACK_HPP_
