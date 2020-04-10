struct BloomFilter
{
    public:
        BloomFilter(int);
        ~BloomFilter();
        void initialize(int);
        void add(char*);
        void print();
        bool search(char *);
    private:
        int *mbits;
        int length_bit;
};