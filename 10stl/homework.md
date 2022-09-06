# Homework
## Task1
```c++
void func(int[] A, int low, int high)
{
    int i = low;
    int j = high;
    int x = A[(low + high) / 2];
    do
    {
        while (A[i] < x)
            ++i;
        while (A[j] > x)
            --j;
        if (i <= j)
        {
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            i++;
            j--;
        }
    } while (i < j);
    if (low < j) // recursion
        func(A, low, j);
    if (i < high) // recursion
        func(A, i, high);
}
```
1. Do {...} while loop is O(n) complexity at most when i and j meet exactly in the middle
2. Then we have two recursion calls. Dividing array this way is O(log(n))

Combined complexity is O(n*log(n))

## Task2
```text
Pick the container for storing data of telephone book.
It should allow to search the data about a person by his
phone number. Explain why you chose this container.
Explanation should contain list of container operations
and their complexity in O notation.
```
Firstly I want to describe characteristics of telephone book:
1. Each entry consists of phone number + personal data. For the simplicity I'm going to skip the fact, that for each country phone numbers have distinct area code.
2. The most frequent used operation is searching numbers, so we want to choose structure with quick access to the elements.
3. Inserting and deleting numbers isn't done as frequently as searching. Preffered structure doesn't need to have best time complexity in these operations. 

In old-school printed telephone books data was printed by contacts' surnames in ascending order. There is no such requirement, so usage of data structure like heap would be convenient, but it isn't necessary.

First structure which comes to mind is hash table. It provides O(1) complexity for insertion, deletion and search. Space complexity at worst is O(n).
Phone numbers are unique, so they would serve as a key, and contact information would be stored as a value.
The problem is huge amount of data. Effectivnes of hash table depends on load factor (which is equal to number of entries/number of buckets). If we have bad hashing function number of buckets doesn't grow (result of hashing function for numbers collide) and numbers of entries grows on each insertion. Load factor should stay in range between 0.6 and 0.75

Good hashing function should "spread" data, so each contact is in separate bucket. In this case we can use phone number to get specific contact. If there are more items in bucket they are stored as an array, so there is additional complexity.