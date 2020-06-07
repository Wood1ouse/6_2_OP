#ifndef SORT_SMOOTH_SORT_H
#define SORT_SMOOTH_SORT_H
#include <cstring>

constexpr std::size_t leoSequence[] = { 1, 1, 3, 5, 9, 15, 25, 41, 67, 109, 177, 287, 465, 753, 1219, 1973, 3193, 5167, 8361, 13529, 21891, 35421u, 57313u, 92735u, 150049u, 242785u, 392835u, 635621u, 1028457u, 1664079u, 2692537u, 4356617u, 7049155u, 11405773u, 18454929u, 29860703u, 48315633u, 78176337u, 126491971u, 204668309u, 331160281u, 535828591u, 866988873u, 1402817465u, 2269806339u, 3672623805u, 5942430145u, 9615053951u, 15557484097u, 25172538049u, 40730022147u, 65902560197u, 106632582345u, 172535142543u, 279167724889u, 451702867433u, 730870592323u, 1182573459757u, 1913444052081u, 3096017511839u, 5009461563921u, 8105479075761u, 13114940639683u, 21220419715445u, 34335360355129u, 55555780070575u, 89891140425705u, 145446920496281u, 235338060921987u, 380784981418269u, 616123042340257u, 996908023758527u, 1613031066098785u, 2609939089857313u, 4222970155956099u, 6832909245813413u, 11055879401769513u, 17888788647582927u, 28944668049352441u, 46833456696935369u, 75778124746287811u, 122611581443223181u, 198389706189510993u, 321001287632734175u, 519390993822245169u, 840392281454979345u, 1359783275277224515u, 2200175556732203861u, 3559958832009428377u, 5760134388741632239u, 9320093220751060617u, 15080227609492692857u };

template<class T>
class LeoHeap {
    T* data;
    std::size_t N;

    std::size_t vectorTree;
    unsigned short int treeFirst;

public:
    LeoHeap(T* _data, std::size_t n);
    ~LeoHeap() = default;

    void deqMax(std::size_t obj);
    void insSort(std::size_t obj);

private:
    void swap(std::size_t first, std::size_t second);
    void heapConv(std::size_t root, std::size_t order);
    void filter(std::size_t obj, std::size_t order, bool test_children = true);
};

template<class T>
LeoHeap<T>::LeoHeap(T* _data, std::size_t n) : data(_data), N(n) {
    vectorTree = 3;
    treeFirst = 0;
    if (N > 1) {
        if constexpr (std::is_same_v<char*, T>) { // т.к. сортировка реализована на основе оператора >,
                                                 // который работает не аналогично типу std::string,
                                                 // используем разветвление этапа компиляции для типа char*,
                                                 //чтобы установить ему явный компаратор strcmp
            if (strcmp(data[0], data[1]) > 0) { swap(0, 1); }
        }
        else {
            if (data[0] > data[1])
            {
                swap(0, 1);
            }
        }
    }
    for (std::size_t i = 2; i < N; i++) { insSort(i); }
}


template<class T>
inline void LeoHeap<T>::insSort(std::size_t obj) {
    if ((vectorTree & 1) && (vectorTree & 2)) {
        vectorTree = (vectorTree >> 2) | 1;
        treeFirst += 2;
    }
    else if (treeFirst == 1) {
        vectorTree = (vectorTree << 1) | 1;
        treeFirst = 0;
    }
    else {
        vectorTree = (vectorTree << (treeFirst - 1)) | 1;
        treeFirst = 1;
    }
    filter(obj, treeFirst);
}

template<class T>
inline void LeoHeap<T>::deqMax(std::size_t obj) {
    if (treeFirst >= 2) {
        vectorTree = (vectorTree << 1) ^ 3;
        treeFirst -= 2;
        filter(obj - leoSequence[treeFirst] - 1, treeFirst + 1, false);
        vectorTree = (vectorTree << 1) | 1;
        filter(obj - 1, treeFirst, false);
    }
    else if (treeFirst == 0) {
        vectorTree >>= 1;
        treeFirst = 1;
    }
    else {
        vectorTree >>= 1;
        treeFirst++;
        for (; treeFirst < N + 1; treeFirst++, vectorTree >>= 1) { if (vectorTree & 1) { break; } }
    }
}

template<class T>
inline void LeoHeap<T>::filter(std::size_t obj, std::size_t order, bool test_children) {
    std::size_t current = obj;
    std::size_t currentOrder = order;
    std::size_t currentSize;
    std::size_t bitMask = 2;
    while (true) {

        currentSize = leoSequence[currentOrder];
        if (currentSize > current) { break; }

        if constexpr (std::is_same_v<char*, T>)
        {
            if (strcmp(data[current - currentSize], data[current]) < 0) {
                break;
            }
            else if ((currentSize == 1) || !test_children) {
                swap(current, current - currentSize);
            }
            else {
                if (strcmp(data[current - currentSize], data[current - 1]) > 0 &&
                    strcmp(data[current - currentSize], data[current - 1 - leoSequence[currentOrder - 2]]) > 0) {
                    swap(current, current - currentSize);
                }
                else {
                    break;
                }
            }
        }
        else {
            if (!(data[current - currentSize] > data[current])) {
                break;
            }
            else if ((currentSize == 1) || !test_children) {
                swap(current, current - currentSize);
            }
            else {
                if ((data[current - currentSize] > data[current - 1]) &&
                    (data[current - currentSize] > data[current - 1 - leoSequence[currentOrder - 2]])) {
                    swap(current, current - currentSize);
                }
                else {
                    break;
                }
            }
        }

        currentOrder++;
        for (; currentOrder < N + 1; currentOrder++, bitMask <<= 1) {
            if (vectorTree & bitMask) { bitMask <<= 1; break; }
        }
        current -= currentSize;
    }
    heapConv(current, currentOrder);
}

template<class T>
inline void LeoHeap<T>::heapConv(std::size_t root, std::size_t order) {
    std::size_t comp, orderCompare;
    while (true) {
        if (order <= 1) { break; }
        if constexpr (std::is_same_v<char*, T>)
        {
            if (strcmp(data[root - 1], data[root - 1 - leoSequence[order - 2]]) > 0) {
                comp = root - 1;
                orderCompare = order - 2;
            }
            else {
                comp = root - 1 - leoSequence[order - 2];
                orderCompare = order - 1;
            }
        }
        else {
            if (data[root - 1] > data[root - 1 - leoSequence[order - 2]]) {
                comp = root - 1;
                orderCompare = order - 2;
            }
            else {
                comp = root - 1 - leoSequence[order - 2];
                orderCompare = order - 1;
            }
        }
        if constexpr (std::is_same_v<char*, T>)
        {
            if (strcmp(data[comp], data[root]) > 0) { swap(root, comp); }
            else { break; }
        }
        else { if (data[comp] > data[root]) { swap(root, comp); } else { break; } }
        root = comp;
        order = orderCompare;
    }
}

template<class T>
inline void LeoHeap<T>::swap(std::size_t first, std::size_t second) {
    std::swap(data[first], data[second]);
}

template<class T>
struct smoothPointer {
    T* obj;

    smoothPointer(T* obj) : obj(obj) {}
    smoothPointer() : obj(nullptr) {}

    T& operator=(const smoothPointer<T>& smPointer) { obj = smPointer.obj; }
    T& operator=(T* const smPointer) { obj = smPointer; }
    bool operator>(smoothPointer<T>& smPointer) { return (*obj > * (smPointer.obj)); }
    T& operator*() { return *obj; }
};


template<class T>
struct sortedArrayPointer {
    smoothPointer<T>* arrPointer;
    std::size_t N;
    sortedArrayPointer() : N(0), arrPointer(nullptr) {}
    sortedArrayPointer(T* data, std::size_t n) : arrPointer(nullptr), N(n) { assign(data, N); sort(); }
    template<class Container>
    sortedArrayPointer(Container& data) { assign<Container>(data); sort(); }

    ~sortedArrayPointer() {
        if (arrPointer != nullptr) { delete[] arrPointer; }
        arrPointer = nullptr;
    }

    void operator()(T* data, std::size_t N) { assign(data, N); sort(); }

    template<class Container>
    void operator()(Container& data) { assign(data); sort(); }

    void assign(T* data, std::size_t n) {
        if (arrPointer != nullptr) { delete[] arrPointer; }
        N = n;
        arrPointer = new smoothPointer<T>[N];
        for (std::size_t i = 0; i < N; i++) { arrPointer[i] = &data[i]; }
        sort();
    }

    template<class Container>
    void assign(Container& data) {
        if (arrPointer != nullptr) { delete[] arrPointer; }
        N = data.size();
        arrPointer = new smoothPointer<T>[N];
        auto it_end = data.end();
        unsigned int i = 0;
        for (auto it = data.begin(); it != it_end; ++it) {
            if (i == N) { break; }
            arrPointer[i] = &(*it);
            i++;
        }
        sort();
    }

    void sort() {
        assert(arrPointer != nullptr);
        LeoHeap< smoothPointer<T> > LH(arrPointer, N);
        for (std::size_t i = 1; i < N - 1; i++) { LH.deqMax(N - i); }
    }

    T& operator[](const std::size_t indx) { return *(arrPointer[indx]); }

    struct iterator {
        smoothPointer<T>* currentPointer;

        iterator() : currentPointer(nullptr) {}
        iterator(smoothPointer<T>* currentPointer) : currentPointer(currentPointer) {}

        iterator& operator++() { currentPointer++; return *this; }
        iterator& operator--() { currentPointer--; return *this; }
        T& operator*() { return **currentPointer; }
        bool operator==(const iterator& smPointer) { return smPointer.currentPointer == currentPointer; }
        bool operator!=(const iterator& smPointer) { return smPointer.currentPointer != currentPointer; }
    };

    iterator begin() { return iterator(&arrPointer[0]); }
    iterator end() { return iterator(&arrPointer[N]); }
};

template<class T>
void smoothSort(T* data, std::size_t N) {
    LeoHeap<T> LH(data, N);
    for (std::size_t i = 1; i < N - 1; i++) { LH.deqMax(N - i); }
}

template<class T, std::size_t N>
void smoothSort(T(&data)[N])
{
    LeoHeap<T> LH(data, N);
    for (std::size_t i = 1; i < N - 1; i++) { LH.deqMax(N - i); }
}

#endif //SORT_SMOOTH_SORT_H
