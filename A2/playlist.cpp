// Array-based List Class for Playlists
// Max Luttrell CS 110C
// Kevin Morris
#include <string>
#include <iostream>
#include <stdexcept>
#include <limits>
using namespace std;

// Value swap
template<typename T>
void swap(T *p1, T *p2)
{
    T tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

// Pointer swap
template<typename T>
void swap(T **p1, T **p2)
{
    T *tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

template<class ItemType>
class List
{
private:
    // CHUNK_SIZE == 2 for alloc testing purposes
    static const int CHUNK_SIZE = 2;
    ItemType *list;
    int numItems;
    int maxItems;

public:
    // default constructor and destructor
    List() : numItems(0), maxItems(CHUNK_SIZE)
    {
        list = new ItemType[maxItems];
    }

    ~List()
    {
        delete [] list;
    }

    // list member functions
    bool isEmpty() { return numItems == 0; }
    int getLength() { return numItems; }
    bool insert(int pos, const ItemType& item);
    bool remove(int pos);
    
    // clear can simply set numItems to zero.  The array list may still contain
    // items already inserted into the list, but since numItems is zero, there 
    // isn't any way to get at them using getEntry() or setEntry()
    void clear() { numItems = 0; }

    // throw invalid_argument if pos<1 or pos>getLength()
    const ItemType& getEntry(int pos) const throw(invalid_argument);

    // throw invalid_argument if pos<1 or pos>getLength()
    void setEntry(int pos, const ItemType& item) throw(invalid_argument);

private:
    void copy(ItemType *original, ItemType *dest)
    {
        for(int i = 0; i < numItems; ++i)
            dest[i] = original[i];
    }
};

/* TODO
Reimplement insert to allocate for CHUNK_SIZE without wasteful
allocations (=> change bool test)
*/
template<class ItemType>
bool List<ItemType>::insert(int pos, const ItemType& item)
{
    bool canAdd;

    canAdd = ((pos > 0) && (pos <= numItems + 1) && (numItems < maxItems));
    if (canAdd)
    {
        // first, we have to move everything after our insertion point over one
        // position to make room for our new item.  start at the back of the list.
        // don't forget arrays start at postion zero and our list ADT starts at
        // position 1.
        for(int i = numItems; i >= pos; i--)
            list[i] = list[i - 1];

        // now put our item at position pos-1
        list[pos - 1] = item;

        numItems++;
    }
    else
    {
        maxItems += CHUNK_SIZE;
        ItemType *newArray = new ItemType[maxItems];
        copy(list, newArray);
        swap(&list, &newArray); // Pointer swap

        delete [] newArray;

        // Recursive call to insert after allocating a new chunk
        cout << "Allocated new chunk of size: " << CHUNK_SIZE << endl;
        return insert(pos, item);
    }

    return canAdd;
}

template<class ItemType>
bool List<ItemType>::remove(int pos)
{
    if(pos < 1 || pos > numItems)
        return false;

    // Shift everything over one to the right [pos .. n - 1]
    for(int i = pos; i < numItems - 1; ++i)
        list[i] = list[i + 1];
    --numItems;

    return true;
}

template<class ItemType>
const ItemType& List<ItemType>::getEntry(int pos) const
throw(invalid_argument)
{
    if(pos < 1 || pos > numItems)
    {
        throw invalid_argument("ERROR: getEntry() using invalid position");
    }
    return list[pos - 1];
}

// TODO: add implementations for setEntry() and remove() functions
template<class ItemType>
void List<ItemType>::setEntry(int pos, const ItemType& item)
throw(invalid_argument)
{
    if(pos < 1 || pos > getLength())
    {
        throw invalid_argument("ERROR: setEntry() given invalid position");
    }
    list[pos - 1] = item;
}

// Utility function to input a track number with some input checking 
// to make sure it's a number
int getTrack()
{
    bool inputCheck;
    int trackNumber;

    do
    {
        inputCheck = true;
        cout << "Please enter the track number you'd like to view: ";
        if (!(cin >> trackNumber))
        {
            cout << "Please enter numbers only.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            inputCheck = false;
        }
    } while(!inputCheck);

    return trackNumber;
}

int main()
{
    List<string> songs;
    char goAgain = 'y';
    int trackNumber;
    string trackName;

    // Insert some songs into our list
    songs.insert(1, "One More Saturday Night");
    songs.insert(1, "Friday I'm in Love");
    songs.insert(3, "Sunday Morning Coming Down");
    songs.insert(1, "California Love");
    songs.insert(1, "YOLO");
    songs.insert(2, "Give It To Me");
    songs.insert(3, "HEHE");

    songs.remove(1);
    songs.remove(1);
    songs.remove(3);

    cout << "Welcome!  There are " << songs.getLength() << " tracks.\n";
    while(goAgain != 'n')
    {
        trackNumber = getTrack();
        try
        {
            trackName = songs.getEntry(trackNumber);
        }
        catch(invalid_argument& arg)
        {
            cout << arg.what() << endl;
            trackName = "No Track";
        }
        cout << "Your track name is " << trackName << endl;
        cout << "Go again? (y/n) ";
        cin >> goAgain;
    }

    cout << "Rock on!\n";
    return 0; 
}

