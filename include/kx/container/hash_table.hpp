#ifndef KX_CONTAINER_HASH_TABLE_HPP_INCLUDED_
#   define KX_CONTAINER_HASH_TABLE_HPP_INCLUDED_

namespace kx
{
namespace container
{
    namespace detail
    {
        const int hash_table_size = 127;
    } // namespace detail

    <template typename T>
    class link
    {
    public:
        link (link * next, T value)
            : _next(next), _value(value) {}
        link *  next () const
        {
            return _next;
        }
        T       value () const
        {
            return _value;
        }
    private:
        T       _value;
        link *  _next;
    };

    template <class T>
    class list
    {
    public:
        list (): _head (nullptr) {}
        ~list ()
        {
            // free the list
            while (_head != nullptr)
            {
                link * link_ = _head;
                _head = _head->next ();
                delete link_;
            }
        }

        void prepend (T value)
        {
            link * link = new link (_head, value);
            _head = link;
        }

        link const * get_head () const
        {
            return _head;
        }
    private:
        link * _head;
    };

    template <class T>
    class hash_table
    {
    public:
        list<T> const &
        find (
            char const * str
        )
        const
        {
            int i = hash (str);
            return _list [i];
        }

        void
        add (
            char const * str,
            T id
        )
        {
            int i = hash (str);
            _list [i].prepend (id);
        }

        inline int capacity () const
        {
            return NUM_BUCKETS;
        }
    private:
        int
        hash (
            char const * str
        )
        const
        {
            // no empty strings
            assert (str != 0 && str [0] != 0);
            unsigned h = str [0];
            for (   int i = 1;
                    str [i] != 0;
                    ++i
                )
            {
                h = (h << 4) + str [i];
            }
            return h % NUM_BUCKETS; //reminder
        }

        enum {NUM_BUCKETS = 127};
        list<T> _list [NUM_BUCKETS]; // an array of (short) lists
    };
} // namespace container
} // namespace kx
#endif // KX_CONTAINER_HASH_TABLE_HPP_INCLUDED_
