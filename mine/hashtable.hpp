#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

namespace cop4530 
{
    // returns largest prime number <= n or zero if input is too large
    // This is likely to be more efficient than prime_above(), because
    // it only needs a vector of size n
    template <typename K, typename V>
    unsigned long HashTable<K, V>::prime_below(unsigned long n)
    {
        if (n > max_prime)
        {
            std::cerr << "** input too large for prime_below()\n";
            return 0;
        }
        if (n == max_prime)
        {
            return max_prime;
        }
        if (n <= 1)
        {
            std::cerr << "** input too small \n";
            return 0;
        }

        // now: 2 <= n < max_prime
        std::vector<unsigned long> v(n + 1);
        setPrimes(v);
        while (n > 2)
        {
            if (v[n] == 1)
                return n;
            --n;
        }
        return 2;
    }

    // Sets all prime number indexes to 1. Called by method prime_below(n) 
    template <typename K, typename V>
    void HashTable<K, V>::setPrimes(std::vector<unsigned long> &vprimes)
    {
        int i = 0;
        int j = 0;

        vprimes[0] = 0;
        vprimes[1] = 0;
        int n = vprimes.capacity();

        for (i = 2; i < n; ++i)
            vprimes[i] = 1;

        for (i = 2; i * i < n; ++i)
        {
            if (vprimes[i] == 1)
            {
                for (j = i + i; j < n; j += i)
                    vprimes[j] = 0;
            }
        }
    }

    // ------------------------------------------------------------------

    template <typename K, typename V>
    HashTable<K, V>::HashTable(size_t size) : table(prime_below(size)), currentSize(0) {}

    template <typename K, typename V>
    HashTable<K, V>::~HashTable() 
    {
        clear();
    }

    template <typename K, typename V>
    bool HashTable<K, V>::contains(const K &k) const 
    {
        auto &list = table[myhash(k)];
        for (const auto &pair : list) 
        {
            if (pair.first == k)
                return true;
        }
        return false;
    }

    template <typename K, typename V>
    bool HashTable<K, V>::match(const std::pair<K, V> &kv) const 
    {
        auto &list = table[myhash(kv.first)];
        for (const auto &pair : list) 
        {
            if (pair == kv)
                return true;
        }
        return false;
    }

    template <typename K, typename V>
    bool HashTable<K, V>::insert(const std::pair<K, V> &kv) 
    {
        auto &list = table[myhash(kv.first)];
        for (auto &pair : list) 
        {
            if (pair.first == kv.first) 
            {
                pair.second = kv.second;
                return true;
            }
        }
        list.push_back(kv);
        if (++currentSize > table.size())
            rehash();
        return true;
    }

    template <typename K, typename V>
    bool HashTable<K, V>::insert(std::pair<K, V> &&kv) 
    {
        auto &list = table[myhash(kv.first)];
        for (auto &pair : list) 
        {
            if (pair.first == kv.first) 
            {
                pair.second = std::move(kv.second);
                return true;
            }
        }
        list.push_back(std::move(kv));
        if (++currentSize > table.size())
            rehash();
        return true;
    }

    template <typename K, typename V>
    bool HashTable<K, V>::remove(const K &k) 
    {
        auto &list = table[myhash(k)];
        for (auto it = list.begin(); it != list.end(); ++it) 
        {
            if (it->first == k) 
            {
                list.erase(it);
                --currentSize;
                return true;
            }
        }
        return false;
    }

    template <typename K, typename V>
    void HashTable<K, V>::clear() 
    {
        makeEmpty();
    }

    template <typename K, typename V>
    bool HashTable<K, V>::load(const char *filename) 
    {
        std::ifstream infile(filename);
        if (!infile)
            return false;

        K key;
        V value;
        while (infile >> key >> value) 
        {
            insert(std::make_pair(key, value));
        }
        return true;
    }

    template <typename K, typename V>
    void HashTable<K, V>::dump() const 
    {
        for (size_t i = 0; i < table.size(); ++i) 
        {
            std::cout << "[" << i << "]: ";
            for (const auto &pair : table[i]) 
            {
                std::cout << pair.first << ":" << pair.second << " ";
            }
            std::cout << std::endl;
        }
    }

    template <typename K, typename V>
    size_t HashTable<K, V>::size() const 
    {
        return currentSize;
    }

    template <typename K, typename V>
    bool HashTable<K, V>::write_to_file(const char* filename) const 
    {
        std::ofstream outfile(filename);
        if (!outfile)
            return false;

        for (const auto &list : table) 
        {
            for (const auto &pair : list) 
            {
                outfile << pair.first << " " << pair.second << std::endl;
            }
        }
        return true;
    }

    template <typename K, typename V>
    void HashTable<K, V>::makeEmpty() 
    {
        for (auto &list : table)
            list.clear();
        currentSize = 0;
    }

    template <typename K, typename V>
    void HashTable<K, V>::rehash() 
    {
        auto oldTable = table;
        table.resize(prime_below(2 * table.size()));
        for (auto &list : table)
            list.clear();
        currentSize = 0;
        for (auto &list : oldTable) 
        {
            for (auto &pair : list)
                insert(std::move(pair));
        }
    }

    template <typename K, typename V>
    size_t HashTable<K, V>::myhash(const K &k) const 
    {
        static std::hash<K> hashFunction;
        return hashFunction(k) % table.size();
    }
}
#endif

